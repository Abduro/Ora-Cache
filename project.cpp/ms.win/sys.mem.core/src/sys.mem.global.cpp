/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Apr-2024 at 22:44:16.8665685, UTC+7, Novosibirsk, Sunday;
	This is Ebo Pack shared global memory allocator interface implementation file;
*/
#include "sys.mem.global.h"

using namespace shared::memory;

/////////////////////////////////////////////////////////////////////////////

shared_data:: shared_data (void) : p_data(0), n_size(0) {}
shared_data:: shared_data (dword _size, const void* _p_data) : p_data(_p_data), n_size(_size) {}

shared_data:: shared_data (const shared_data& _ref) : shared_data() { *this = _ref; }

shared_data&  shared_data::operator = (const shared_data& _ref) { *this << _ref.p_data << _ref.n_size; return *this; }
shared_data&  shared_data::operator <<(const void* _p_data) { this->p_data = _p_data; return *this; }
shared_data&  shared_data::operator <<(const dword _n_size) { this->n_size = _n_size; return *this; }

bool shared_data::operator != (const shared_data& _data) const { return (this->n_size != _data.n_size) || (this->p_data != _data.p_data); }
bool shared_data::operator == (const shared_data& _data) const { return !(*this != _data); }

#if defined(_DEBUG)
CString   shared_data::Print(void) const {

	static _pc_sz lp_sz_pat = _T("struct::[%s]>>{p_data=%s;n_size=%u}");

	CString cs_this;
	cs_this.Format(lp_sz_pat, (_pc_sz)__CLASS__, TString().__address_of(this->p_data), this->n_size);
	return  cs_this;

}
#endif

/////////////////////////////////////////////////////////////////////////////

shared_flags:: shared_flags (DWORD _flags) : m_is_set(_flags) {}

err_code shared_flags::Get (global _p_mem) const {
	_p_mem;
	err_code e_result = TErrCodes::no_error;

	if (!_p_mem)
		return e_result = __e_inv_arg;
	// https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-globalflags ;
	// https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/gflags-examples ;
	UINT u_flags = ::GlobalFlags(_p_mem);
	if ( u_flags == GMEM_INVALID_HANDLE )
		e_result = __LastErrToHresult();
	else
		this->m_is_set = u_flags;

	return e_result;
}

bool shared_flags::Has (const e_flags _flag) const { return 0 != (this->m_is_set & _flag); }

shared_flags::operator DWORD (void) const { return this->m_is_set; }

shared_flags& shared_flags::operator = (const shared_flags& _flags) { this->m_is_set = _flags.m_is_set; return *this; }
shared_flags& shared_flags::operator+= (const e_flags _flag) { this->m_is_set |= _flag; return *this; }
shared_flags& shared_flags::operator-= (const e_flags _flag) { this->m_is_set &=~_flag; return *this; }

#if defined(_DEBUG)
CString   shared_flags::Print(void) const {

	static _pc_sz lp_sz_pat = _T("struct::[%s]>>{flags=%s}");

	CString cs_flags;
	if (false) cs_flags = _T("#not_set");
	if (this->Has(e_flags::e_movable) == false)
		if (!cs_flags.IsEmpty()) { cs_flags += _T("|"); cs_flags += _T("e_fixed"); }

	if (this->Has(e_flags::e_modify )) { if (!cs_flags.IsEmpty()) cs_flags += _T("|"); cs_flags += _T("e_modify" ); }
	if (this->Has(e_flags::e_movable)) { if (!cs_flags.IsEmpty()) cs_flags += _T("|"); cs_flags += _T("e_movable"); }
	if (this->Has(e_flags::e_to_zero)) { if (!cs_flags.IsEmpty()) cs_flags += _T("|"); cs_flags += _T("e_to_zero"); }

	CString cs_this;
	cs_this.Format(lp_sz_pat, (_pc_sz)__CLASS__, (_pc_sz)cs_flags);
	return  cs_this;
}
#endif

/////////////////////////////////////////////////////////////////////////////

TPsuedoBuilder:: CBuilder (CSharedPsuedo& _psuedo) : m_psuedo(_psuedo) { m_error >> __CLASS__ << __METHOD__; }
TPsuedoBuilder::~CBuilder (void) { this->Destroy(); }

/////////////////////////////////////////////////////////////////////////////

err_code TPsuedoBuilder::Create (void) {
	m_error << __METHOD__ << TErrCodes::no_error;

	if (this->m_psuedo.Is()) {
		return (m_error << (err_code) TErrCodes::eObject::eExists);
	}
	//  https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-globalalloc ;
	this->m_psuedo.m_handle = ::GlobalAlloc(this->m_psuedo.Flags(), this->m_psuedo.Data().n_size);
	if (!this->m_psuedo.Handle()) {
		m_error.Last();
	}
	else if (OLE_E_BLANK == this->m_psuedo.Content().Error().Result()) {
		this->m_psuedo.Content().m_error << TErrCodes::no_error; // ToDo: stupid approach, but it temporarily is kept;
	}

	if (this->m_psuedo.Data().p_data && !this->Error()) {
		m_error = this->m_psuedo.Content().Write(this->m_psuedo.Data());
	}

	return this->Error();
}

err_code TPsuedoBuilder::Destroy (void) {
	m_error << __METHOD__ << TErrCodes::no_error;

	if (false == this->m_psuedo.Is())
		return m_error << (err_code) TErrCodes::eExecute::eState;

	global h_result = ::GlobalFree(m_psuedo.m_handle);
	if (h_result)
		this->m_error.Last();
	else
		this->m_psuedo.m_handle = NULL;

	return this->Error();
}

TError&  TPsuedoBuilder::Error (void) const { return this->m_error; }

err_code TPsuedoBuilder::Update(const shared_data& _data) {
	_data;
	m_error << __METHOD__ << TErrCodes::no_error;

	if (this->m_psuedo.Is() == false) { // not created yet;
		this->m_psuedo.Data(_data);
		return this->Create();
	}
#if (0)
	else {
		this->Destroy();
		this->m_psuedo.Data(_data);
		return this->Create();
	}
#else
	if (this->m_psuedo.Data() == _data) // nothing to change;
		return this->Error();

	const bool b_data = this->m_psuedo.Data().p_data != _data.p_data;
	const bool b_size = this->m_psuedo.Data().n_size != _data.n_size;

	const bool b_modify = this->m_psuedo.Flags().Has(shared_flags::e_modify);
	const bool b_zeroed = this->m_psuedo.Flags().Has(shared_flags::e_to_zero);

	if (b_modify) {
		global p_new = ::GlobalReAlloc(this->m_psuedo.Handle(), 0, this->m_psuedo.Flags().m_is_set); // the new size is ignored;
		if (!p_new)
			this->m_error.Last();
		else {
			this->m_psuedo.m_handle = p_new;
		}
	}
	else if (b_size) {  // reallocation must be made first regardless a part of existing content may be lost in case if new size is less than existing one;
		if (!b_zeroed)
			this->m_psuedo.Flags().m_is_set |= shared_flags::e_to_zero;

		global p_new = ::GlobalReAlloc(this->m_psuedo.Handle(), _data.n_size, this->m_psuedo.Flags().m_is_set);
		if (!p_new)
			this->m_error.Last();
		else {
			this->m_psuedo.m_handle = p_new;
			this->m_psuedo.m_data.n_size = _data.n_size;
		}
	}

	if (b_data && !b_modify) { // content data cannot be changed when memory block attribute(s) modified;
		this->m_error = this->m_psuedo.Content().Write(_data);
	}

	return this->Error();
#endif
}

err_code TPsuedoBuilder::Update(const shared_flags& _flags) {
	_flags;
	m_error <<__METHOD__ << TErrCodes::no_error;

	if (this->m_psuedo.Flags(_flags))
		m_error = _T("Current flag set is changed;");

	return this->Error();
} 

/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
	CString TPsuedoBuilder::Print (void) const {

		static _pc_sz lp_sz_pat = _T("cls::[%s]>>{error=%s}");
		
		CString cs_out; cs_out.Format(lp_sz_pat, (_pc_sz)__CLASS__, this->Error().Print(CError::e_req).GetString());
		return  cs_out;
	}
#endif
/////////////////////////////////////////////////////////////////////////////

TPsuedoContent:: CContent (CSharedPsuedo& _psuedo) : m_psuedo(_psuedo) { m_error >> __CLASS__ << __METHOD__ << OLE_E_BLANK; }
TPsuedoContent::~CContent (void) {}

/////////////////////////////////////////////////////////////////////////////

TError&  TPsuedoContent::Error (void) const { return this->m_error; }
cbool    TPsuedoContent::Is  (void) const { return !!m_psuedo.Data().n_size && !!m_psuedo.Data().p_data && m_psuedo.Is(); }

CString  TPsuedoContent::Read (void) const {
	m_error << __METHOD__ << TErrCodes::no_error;

	CString cs_out;

	if (m_psuedo.Is() == false) {
		m_error << (err_code) TErrCodes::eObject::eHandle;
		return cs_out;
	}

	const bool b_movable = this->m_psuedo.Flags().Has(shared_flags::e_movable);

	PVOID p_data = nullptr;

	if (b_movable) {
		p_data = ::GlobalLock(this->m_psuedo.Handle());
		if ( !p_data ) {
			this->m_error.Last();
			return cs_out;
		}
	}
	else
		p_data = this->m_psuedo.Handle();

	cs_out.Append(static_cast<_pc_sz>(p_data), this->m_psuedo.Data().n_size); // ToDo: it very looks like this operation requires catching possible error;

	if (b_movable) {
		if (0 == ::GlobalUnlock(this->m_psuedo.Handle()))
			this->m_error.Last();
	}

	return cs_out;
}

err_code TPsuedoContent::Write(const shared_data& _data) {
	_data;
	this->m_error << __METHOD__ << TErrCodes::no_error;

	if (!_data.p_data) return m_error << E_POINTER;
	if (!_data.n_size) return m_error << (err_code) TErrCodes::eData::eInvalid = _T("Target data size cannot be zero;");
#if (0)
	if ( _data.p_data == this->m_psuedo.Data().p_data) return m_error << E_INVALIDARG =_T("Unable to copy data from the pointer to itself;");
#endif
	if (!m_psuedo.Is())
		return m_error << (err_code) TErrCodes::eObject::eHandle;

	const bool b_data = this->m_psuedo.Data().p_data != _data.p_data;
	const bool b_movable = this->m_psuedo.Flags().Has(shared_flags::e_movable);

	if (false == b_data || true) { // data pointers are still the same, but data content may change;
	}

	PVOID p_data = nullptr;
	/*
		*Important* : if access to data is not correct, i.e. when memory block is movable, but data of block is accessed directly, but not through
		              GlobalLock(), destroying this memory by GlobalFree() will throw system error 347 that means 'Invalid Handle';
	*/
	if (b_movable) {
		p_data = ::GlobalLock(this->m_psuedo.Handle()); // https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-globallock ;
		if ( !p_data )
			return this->m_error.Last();
	}
	else
		p_data = this->m_psuedo.Handle();

	const errno_t t_result = ::memcpy_s(p_data, this->m_psuedo.Data().n_size, _data.p_data, _data.n_size);
	if (TErrCodes::no_error != t_result)
		this->m_error << (err_code) TErrCodes::eData::eBuffer;
	// a possible error of unlock operation will overwrite the previous one, i.e. the error above;
	if (b_movable) {
		if (0 == ::GlobalUnlock(this->m_psuedo.Handle())) // https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-globalunlock ;
			this->m_error.Last(); // if reference count equals to zero (unlocked) the last error returns TErrCodes::no_error;
	}

	return this->Error();
}

err_code TPsuedoContent::Write(_pc_sz _p_sz_str ) {
	_p_sz_str;
	m_error << __METHOD__ << TErrCodes::no_error;

	if (!_p_sz_str || 0 == ::_tcslen(_p_sz_str))
		return m_error << E_INVALIDARG;

	if (m_psuedo.Is() == false)
		return m_error << (err_code) TErrCodes::eObject::eHandle;

	DWORD n_req = TString(_p_sz_str).Bytes();

	if (n_req > this->m_psuedo.Data().n_size) {
		n_req = this->m_psuedo.Data().n_size;
		m_error = _T("[truncated]"); // overwritten by this->Write(const shared_data& _data);
	}

	const shared_data data(
		n_req, static_cast<const void*>(_p_sz_str)
	);

	return this->Write(data);
}

/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
CString  TPsuedoContent::Print (void) const {

	static _pc_sz lp_sz_pat = _T("cls::[%s]>>{valid=%s}");

	CString cs_this;
	cs_this.Format(lp_sz_pat, (_pc_sz)__CLASS__, TString().Bool(this->Is()));
	return  cs_this;

}
#endif
/////////////////////////////////////////////////////////////////////////////

CSharedPsuedo:: CSharedPsuedo (void) : m_handle(0), m_builder(*this), m_content(*this) { m_error >> __CLASS__ << __METHOD__ << OLE_E_BLANK; }
CSharedPsuedo::~CSharedPsuedo (void) {}

/////////////////////////////////////////////////////////////////////////////
const
TPsuedoBuilder& CSharedPsuedo::Builder (void) const { return this->m_builder; }
TPsuedoBuilder& CSharedPsuedo::Builder (void)       { return this->m_builder; }
const
TPsuedoContent& CSharedPsuedo::Content (void) const { return this->m_content; }
TPsuedoContent& CSharedPsuedo::Content (void)       { return this->m_content; }

const shared_data&  CSharedPsuedo::Data (void) const { return this->m_data; }
const shared_flags& CSharedPsuedo::Flags(void) const { return this->m_flags; }

bool  CSharedPsuedo::Data (const shared_data& _data) {
	_data;
	bool b_changed = this->Data() != _data;
	if ( b_changed )
		this->m_data = _data;

	return b_changed;
}

bool  CSharedPsuedo::Flags (const shared_flags& _flags) {
	_flags;
	bool b_changed = _flags.m_is_set != this->Flags().m_is_set;
	if ( b_changed )
		this->m_flags = _flags;
	return b_changed;
}

TError& CSharedPsuedo::Error (void) const { return this->m_error; }

DWORD   CSharedPsuedo::Size  (void) const {

	m_error << __METHOD__ << TErrCodes::no_error;

	DWORD n_size = 0;

	if (!this->Is()) {
		m_error << (err_code) TErrCodes::eObject::eHandle;
		return n_size;
	}
	// https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-globalsize ;
	n_size = static_cast<DWORD>(::GlobalSize(this->Handle()));
	if (!n_size)
		m_error.Last();
	
	return n_size;
}

const global CSharedPsuedo::Handle (void) const { return this->m_handle; }

const bool CSharedPsuedo::Is (void) const {

	m_error << __METHOD__ << TErrCodes::no_error;

	if (!this->Handle())
		return !(m_error << OLE_E_BLANK);

	UINT u_flags = ::GlobalFlags(this->Handle());
	if ( u_flags == GMEM_INVALID_HANDLE )
		m_error.Last();
	return !this->Error();
}
/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
CString  CSharedPsuedo::Print (const e_print e_opt) const {

	static _pc_sz lp_sz_pat_a = _T("cls::[%s]>>{build=%s;content=%s;error=[%s]}");
	static _pc_sz lp_sz_pat_c = _T("cls::[%s]>>{build=%s;content=%s}");
	static _pc_sz lp_sz_pat_e = _T("cls::[%s]>>{error=[%s];state=%s}");
	static _pc_sz lp_sz_pat_d = _T("cls::[%s]>>{data=%s;flags=%s}");

	CString cs_out;
	if (e_print::e_all ==e_opt) cs_out.Format(lp_sz_pat_a, (_pc_sz)__CLASS__, 
		(_pc_sz)this->Builder().Print(), (_pc_sz)this->Content().Print(), (_pc_sz)this->Error().Print(CError::e_req)
	);
	if (e_print::e_att ==e_opt) cs_out.Format(lp_sz_pat_d, (_pc_sz)__CLASS__, (_pc_sz)this->Data().Print()   , (_pc_sz)this->Flags().Print());
	if (e_print::e_comp==e_opt) cs_out.Format(lp_sz_pat_c, (_pc_sz)__CLASS__, (_pc_sz)this->Builder().Print(), (_pc_sz)this->Content().Print());
	if (e_print::e_err ==e_opt) cs_out.Format(lp_sz_pat_e, (_pc_sz)__CLASS__, (_pc_sz)this->Error().Print(CError::e_req), TString().Bool(this->Is()));

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s]>>{state=#undef}"), (_pc_sz)__CLASS__);

	return  cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////

CSharedPsuedo& CSharedPsuedo::operator <<(const shared_data& _data) { this->Data(_data); return *this; }
CSharedPsuedo& CSharedPsuedo::operator <<(const shared_flags& _flags) { this->Flags(_flags); return *this; }

/////////////////////////////////////////////////////////////////////////////

TPage:: CPage (CSharedNamed& _named) : m_named(_named), m_handle(0) { m_error >> __CLASS__ << __METHOD__ << OLE_E_BLANK; }
TPage::~CPage (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code TPage::Create (void) {
	m_error << __METHOD__ << TErrCodes::no_error;

	if (this->Is())
		return m_error << (err_code) TErrCodes::eObject::eExists;

	if (this->m_named.Is() == false)
		return this->m_error = this->m_named.Error();

	// https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-createfilemappinga ;
	HANDLE h_new = ::CreateFileMapping(INVALID_HANDLE_VALUE, 0, PAGE_READWRITE, 0, m_named.Data().n_size, this->m_named.Name());
	this->m_error.Last();

	if (TErrCodes::ePath::eExists == this->m_error.Result()) // ToDo: the returned handle can be checked with existing one by value;
		return m_error << (err_code) TErrCodes::eObject::eExists = _T("Object with the same name is already created;");

	this->m_handle = h_new;
	this->m_named.m_error << this->Error().Result();

	return this->Error();
}

err_code TPage::Destroy(void) {
	m_error << __METHOD__ << TErrCodes::no_error;

	if (!this->Is())
		return m_error << (err_code) TErrCodes::eObject::eHandle = _T("The object is not created or already destroyed;");

	this->m_error << THandle::Close(this->m_handle);
	this->m_named.m_error << OLE_E_BLANK;

	return this->Error();
}

TError& TPage::Error (void) const { return this->m_error; }

const HANDLE TPage::Handle (void) const { return this->m_handle; }

const bool TPage::Is (void) const { return TErrCodes::no_error == THandle::Is(this->Handle()); }

/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
CString TPage::Print (void) const {

	static _pc_sz p_sz_pat = _T("cls::[%s]>>{error=[%s];valid=%s}");

	CString cs_out;
	cs_out.Format(p_sz_pat, (_pc_sz)__CLASS__, (_pc_sz)this->Error().Print(CError::e_req), TString().Bool(this->Is()));
	return  cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////

TPage::operator const HANDLE (void) const { return this->Handle(); }
TPage::operator       HANDLE (void)       { return this->Handle(); }

/////////////////////////////////////////////////////////////////////////////

TSecurity:: CSecurity (void) {}
TSecurity::~CSecurity (void) {}

/////////////////////////////////////////////////////////////////////////////

TView:: CView (CSharedNamed& _named) : m_named(_named), m_p_data(0) { m_error >> __CLASS__ << __METHOD__ << OLE_E_BLANK; }
TView::~CView (void) {}

/////////////////////////////////////////////////////////////////////////////

TError&  TView::Error(void) const { return this->m_error; }

err_code TView::Close(void) {

	m_error << __METHOD__ << TErrCodes::no_error;

	if (this->m_p_data == 0)
		return m_error << (err_code) TErrCodes::eExecute::eState;

	if (!this->m_named.Is()) {
		return m_error << OLE_E_BLANK;
	}
	else { // https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-unmapviewoffile ;
		if (!::UnmapViewOfFile(this->m_p_data))
			this->m_error.Last();
		else
			this->m_p_data = 0;
	}

	return this->Error();
}

const bool TView::Is (void) const { return !!this->m_p_data; }

err_code TView::Open (void) {

	m_error << __METHOD__ << TErrCodes::no_error;

	if (this->m_p_data != 0)
		return m_error << (err_code) TErrCodes::eObject::eInited;

	if (!this->m_named.Is()) {
		return m_error << OLE_E_BLANK;
	}
	else { // https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-mapviewoffile ;
		this->m_p_data = static_cast<byte*>(
			::MapViewOfFile(this->m_named.Page().Handle(), FILE_MAP_ALL_ACCESS, 0, 0, this->m_named.Data().n_size)
		);
		if (!this->m_p_data)
			m_error.Last();
	}
	return this->Error();
}

#if defined(_DEBUG)
CString  TView::Print (void) const {

	static _pc_sz p_sz_pat = _T("cls::[%s]>>{error=[%s];valid=%s}");

	CString cs_out;
	cs_out.Format(p_sz_pat, (_pc_sz)__CLASS__, (_pc_sz)this->Error().Print(CError::e_req), TString().Bool(this->Is()));
	return  cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////

CString  TView::Read (void)  {

	m_error << __METHOD__ << TErrCodes::no_error;

	CString cs_out;

	if (this->m_named.Page().Is() == false) {
		this->m_error << (err_code) TErrCodes::eObject::eHandle;
		return cs_out;
	}
	if (this->Is() == false) {
		this->m_error << OLE_E_BLANK;
		return cs_out;
	}
	const UINT n_req = this->m_named.Data().n_size / sizeof(t_char); // it is supposed the buffer handles zero-terminate character;
	if (n_req < 2) {
		m_error << (err_code) TErrCodes::eData::eInvalid = _T("The length of string must be at least one character;");
		return cs_out;
	}
	// https://learn.microsoft.com/en-us/windows/win32/memory/reading-and-writing-from-a-file-view ; :( does not work;

	TSehTrans trans;

	try {
		_pc_sz p_str = reinterpret_cast< _pc_sz>(const_cast<byte*>(this->m_p_data));
		cs_out.Append(p_str, n_req);
	}
	catch (const TSehExcept& _ex) {
		this->m_error << __e_no_memory = (_pc_sz)_ex.ToString();
	}
	return  cs_out;
}

err_code  TView::Write (void) {
	return this->Write (this->m_named.Data());
}

err_code  TView::Write (const shared_data& _data) {
	_data;
	m_error << __METHOD__ << TErrCodes::no_error;

	if (!_data.p_data) return this->m_error << __e_inv_arg = _T("Data source pointer is invalid;");
	if (!_data.n_size) return this->m_error << __e_inv_arg = _T("Invalid length of source data buffer;");

	TSehTrans trans;
	// https://learn.microsoft.com/en-us/previous-versions/windows/desktop/legacy/aa366535(v=vs.85)
	try {
		const errno_t e_result = ::memcpy_s(const_cast<byte*>(this->m_p_data), this->m_named.Data().n_size, _data.p_data, _data.n_size);
		if (TErrCodes::no_error != e_result)
			this->m_error << (err_code) TErrCodes::eData::eBuffer;
	}
	catch (const TSehExcept& _ex) {
		this->m_error << __e_no_memory = (_pc_sz)_ex.ToString();
	}

	return this->Error();
}

err_code  TView::Write(_pc_sz _p_sz_str ) {
	_p_sz_str;
	m_error << __METHOD__ << TErrCodes::no_error;

	if (!_p_sz_str || 0 == ::_tcslen(_p_sz_str))
		return m_error << E_INVALIDARG;

	if (this->Is() == false)
		return m_error << OLE_E_BLANK;

	DWORD n_req = TString(_p_sz_str).Bytes();

	if (n_req > this->m_named.Data().n_size) {
		n_req = this->m_named.Data().n_size;
		m_error = _T("$truncated"); // overwritten by this->Write(const shared_data& _data);
	}

	const shared_data data(
		n_req, static_cast<const void*>(_p_sz_str)
	);

	return this->Write(data);
}

/////////////////////////////////////////////////////////////////////////////

CSharedNamed:: CSharedNamed (void) : m_page(*this), m_view(*this) { m_error >> __CLASS__ << __METHOD__ << OLE_E_BLANK; }
CSharedNamed::~CSharedNamed (void) {}

/////////////////////////////////////////////////////////////////////////////
const
shared_data&   CSharedNamed::Data (void) const { return this->m_data; }
const bool     CSharedNamed::Data (const shared_data& _data) {
	_data;
	bool b_changed = this->Data() != _data;
	if ( b_changed )
		this->m_data = _data;

	return b_changed;
}

TError&  CSharedNamed::Error(void) const { return this->m_error; }

_pc_sz   CSharedNamed::Name (void) const { return (_pc_sz)this->m_name; }
err_code CSharedNamed::Name (_pc_sz _p_name) {
	_p_name;
	m_error << __METHOD__ << TErrCodes::no_error;

	if (!_p_name || 0 == ::_tcslen(_p_name))
		return m_error << E_INVALIDARG;

	if (0 == this->m_name.CompareNoCase(_p_name))
		return m_error << E_INVALIDARG = _T("Such name is already set;");

	if (this->Page().Is()) {
		const err_code e_result = this->Page().Destroy();
		if (FAILED(e_result))
			return this->Page().Error();
	}

	this->m_name = _p_name;

	return this->Error();
}

const
TPage&  CSharedNamed::Page (void) const { return this->m_page; }
TPage&  CSharedNamed::Page (void)       { return this->m_page; }

#if defined(_DEBUG)
CString CSharedNamed::Print (void) const {

	static _pc_sz p_sz_pat = _T("cls::[%s]>>{name='%s';error=[%s];valid=%s}");

	CString cs_out;
	cs_out.Format(p_sz_pat, (_pc_sz)__CLASS__, this->Name(), (_pc_sz)this->Error().Print(CError::e_req), TString().Bool(!this->Error()));
	return  cs_out;
}
#endif

const
TSecurity& CSharedNamed::Security (void) const { return this->m_sec; }
TSecurity& CSharedNamed::Security (void)       { return this->m_sec; }

const
TView& CSharedNamed::View (void) const { return this->m_view; }
TView& CSharedNamed::View (void)       { return this->m_view; }

const
bool   CSharedNamed::Is (void) const {

	bool b_is = false;

	if (this->m_name.IsEmpty()) {
		this->m_error << (err_code) TErrCodes::eData::eInvalid = _T("Object name is not set;");
		return b_is;
	}

	if (this->Data().n_size == 0) {
		this->m_error << (err_code) TErrCodes::eData::eInvalid = _T("Memory block size cannot be zero;");
		return b_is;
	}

	return b_is = true;
}

/////////////////////////////////////////////////////////////////////////////

CString    CSharedNamed::Name_Auto(void) {
	return TString().Format(_T("Global\\%s"), (_pc_sz)TRandom::GuidAsText(false));
}

/////////////////////////////////////////////////////////////////////////////

CSharedNamed& CSharedNamed::operator <<(const shared_data& _data) { this->Data(_data); return *this; }