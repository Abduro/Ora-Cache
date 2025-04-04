/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Jan-2010 at 9:43:43pm, GMT+3, Rostov-on-Don, Thursday;
	This is Row27 project data model error class implementation file.
	-----------------------------------------------------------------------------
	Adopted to Pulspay server project on 15-May-2012 at 9:44:59pm, GMT+3, Rostov-on-Don, Tuesday; 
	Adopted to Platinum project on 19-Mar-2014 at 7:06:34am, GMT+4, Taganrog, Wednesday;
	Adopted to File Watcher (thefileguardian.com) on 9-Jul-2018 at 7:56:12p, UTC+7, Phuket, Rawai, Monday;
	-----------------------------------------------------------------------------
	Adopted to FakeGPS driver project on 13-Dec-2019 at 10:20:24a, UTC+7, Novosibirsk, Friday;
*/
#include "sys.error.h"

using namespace shared::common;
using namespace shared::sys_core;

#include "sys.err.format.h"
using namespace shared::sys_core::_impl;

/////////////////////////////////////////////////////////////////////////////

CErr_Base::CErr_Base(void) : m_code(__s_ok), m_result(__s_ok), m_lang() {
}
CErr_Base::CErr_Base(const dword  dwError, const CLang& _lng_id) : m_code(dwError), m_lang(_lng_id)  {
	m_result = __DwordToHresult(dwError);
}
CErr_Base::CErr_Base(const err_code hError, const CLang& _lng_id) :
	m_code(__HresultToDword(hError)), m_result(hError), m_lang(_lng_id) {
}
/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
CString CErr_Base::Print (void) const {

	static _pc_sz lp_sz_pat = _T("cls::[%s]>>{code=%u;result=0x%x}");

	CString cs_out; cs_out.Format(lp_sz_pat, (_pc_sz)__CLASS__, this->m_code, this->m_result);
	return  cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////

CErr_Base& CErr_Base::operator = (const dword _code) {
	SAFE_LOCK(m_lock);
	m_code = _code;
	m_result = __DwordToHresult(_code);
	return *this;
}
CErr_Base& CErr_Base::operator= (const err_code _hres) {
	SAFE_LOCK(m_lock);
	m_code   = __HresultToDword(_hres);
	m_result = _hres;
	return *this;
}
CErr_Base& CErr_Base::operator= (TLangRef _lang) {
	SAFE_LOCK(m_lock);
	m_lang = _lang;
	return *this;
}

/////////////////////////////////////////////////////////////////////////////

CErr_Base::operator dword    (void) const { SAFE_LOCK(m_lock); return (m_code)  ; }
CErr_Base::operator err_code (void) const { SAFE_LOCK(m_lock); return (m_result); }
CErr_Base::operator TLangRef (void) const { SAFE_LOCK(m_lock); return (m_lang)  ; }
CErr_Base::operator TSyncRef (void)       { return   (m_lock); }

/////////////////////////////////////////////////////////////////////////////
#if(0)
CErr_Source:: CErr_Source (void) { this->Class() = __CLASS__; this->Method() = __METHOD__; this->NameSp() = __SP_NAME__; }
CErr_Source:: CErr_Source (const CErr_Source& _ref) : CErr_Source() { *this = _ref; }
CErr_Source:: CErr_Source (_pc_sz _lp_sz_cls, _pc_sz _lp_sz_method, _pc_sz _lp_sz_name_sp) : CErr_Source() {
	this->Set(_lp_sz_cls, _lp_sz_method, _lp_sz_name_sp);
}
CErr_Source::~CErr_Source (void) {}

/////////////////////////////////////////////////////////////////////////////

_pc_sz  CErr_Source::Class (void) const { return this->m_class.GetString() ; }
CString& CErr_Source::Class (void)       { return this->m_class ; }
_pc_sz  CErr_Source::Method(void) const { return this->m_method.GetString(); }
CString& CErr_Source::Method(void)       { return this->m_method; }
_pc_sz  CErr_Source::NameSp(void) const { return this->m_space.GetString() ; }
CString& CErr_Source::NameSp(void)       { return this->m_space ; }

/////////////////////////////////////////////////////////////////////////////
#include "sys.std.seh.h"

CString  CErr_Source::Get (_pc_sz _lp_sz_format/* = _T("Class = %s; Func = %s;")*/) const {

	CString cs_formatted;

	shared::sys_core::seh::CTranslator trans;

	try {
		cs_formatted.Format(_lp_sz_format, this->Class(), this->Method());
	}
	catch (const shared::sys_core::seh::CException&) {
		cs_formatted = _T("#sys.seh is handled");
	}
	return  cs_formatted;
}

bool CErr_Source::Set (_pc_sz _lp_sz_cls, _pc_sz _lp_sz_method, _pc_sz _lp_sz_name_sp) {

	bool b_changed = false;
	if (!b_changed) { b_changed = (_lp_sz_cls != this->Class()); } this->Class() = _lp_sz_cls; // setting a value ignors changing flag;
	if (!b_changed) { b_changed = (_lp_sz_method != this->Method()); } this->Method() = _lp_sz_method;
	if (!b_changed) { b_changed = (_lp_sz_name_sp != this->NameSp()); } this->NameSp() = _lp_sz_name_sp;

	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

CErr_Source& CErr_Source::operator = (const CErr_Source& _ref) { this->Set(_ref.Class(), _ref.Method(), _ref.NameSp()); return *this; }
#endif
/////////////////////////////////////////////////////////////////////////////

CErr_State:: CErr_State(void) : TBase() {}
CErr_State:: CErr_State(const CErr_State& _state) : TBase() { *this = _state; }
CErr_State::~CErr_State(void) {}

/////////////////////////////////////////////////////////////////////////////

_pc_sz   CErr_State::Get (void) const { SAFE_LOCK(TBase::m_lock); return m_buffer.GetString(); }
void     CErr_State::Set (const bool _reset) {
	_reset;
	SAFE_LOCK(TBase::m_lock);

	if (_reset) {
		this->m_code    = __HresultToDword(OLE_E_BLANK);
		this->m_result  = OLE_E_BLANK;
		this->m_buffer  = CErr_Details() << this->m_result;
	}
	else {
		this->m_code    = ERROR_SUCCESS;
		this->m_result  = S_OK;
		this->m_buffer  = _T("No error");
	}
}

void     CErr_State::Set (const dword _err_code) {
	_err_code;

	SAFE_LOCK(TBase::m_lock) ;

	TBase::m_code   =  _err_code;
	TBase::m_result = __DwordToHresult(_err_code);

	m_buffer = (_pc_sz)(CErr_Details() << TBase::m_lang << TBase::m_code);
}

void     CErr_State::Set (const dword _err_code, _pc_sz _lp_sz_desc, ...) {
	_err_code; _lp_sz_desc;

	SAFE_LOCK(TBase::m_lock) ;

	TBase::m_code   =  _err_code;
	TBase::m_result = __DwordToHresult(_err_code);

	va_list  args_;
	va_start(args_, _lp_sz_desc);

	m_buffer = (_pc_sz)(CErr_Details() << TBase::m_lang << _lp_sz_desc << args_);

	va_end(args_);
}

void     CErr_State::Set (const dword _err_code, const UINT resId) {
	_err_code; resId;

	CString cs_desc;
	cs_desc.LoadString(resId);

	this->Set(_err_code, cs_desc.GetString());
}

void     CErr_State::Set (const err_code _err_code) {
	_err_code;

	SAFE_LOCK(TBase::m_lock);

	TBase::m_code   = __HresultToDword(_err_code);
	TBase::m_result =  _err_code;

	if (SUCCEEDED(_err_code))
		this->m_buffer  = _T("No error");
	else
		this->m_buffer  = CErr_Details() << this->m_result;
}

void     CErr_State::Set (const err_code _err_code, _pc_sz _lp_sz_desc, ...) {
	_err_code; _lp_sz_desc;

	SAFE_LOCK(TBase::m_lock);

	TBase::m_code   = __HresultToDword(_err_code);
	TBase::m_result =  _err_code;

	va_list  args_;
	va_start(args_, _lp_sz_desc);

	m_buffer = (_pc_sz)(CErr_Details() << TBase::m_lang << _lp_sz_desc << args_);

	va_end(args_);
}

void     CErr_State::Set (const err_code _err_code, const UINT resId) {
	_err_code; resId;
	CString cs_desc;

	cs_desc.LoadString(resId);
	this->Set(_err_code, cs_desc.GetString());
}

void     CErr_State::Set (_pc_sz  _sz_desc) {
	_sz_desc;
	SAFE_LOCK(TBase::m_lock);
	m_buffer = _sz_desc;
}

void     CErr_State::Set (_pc_sz  _sz_desc, ...) {
	_sz_desc;
	SAFE_LOCK(TBase::m_lock);
	va_list  args_;
	va_start(args_, _sz_desc);

	m_buffer = (_pc_sz)(CErr_Details() << TBase::m_lang << _sz_desc << args_);

	va_end(args_);
}

#if defined(_DEBUG)
CString CErr_State::Print (void) const {

	static _pc_sz lp_sz_pat = _T("cls::[%s]>>{base=[%s];state=%s}");

	CString cs_out; cs_out.Format(lp_sz_pat, (_pc_sz)__CLASS__, (_pc_sz)TBase::Print(), this->Get());
	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CErr_State::operator bool    (void) const { SAFE_LOCK(TBase::m_lock); return __failed(TBase::m_result); }
CErr_State::operator _pc_sz  (void) const { return this->Get(); }

/////////////////////////////////////////////////////////////////////////////

CErr_State&   CErr_State::operator= (const bool _reset) { this->Set(_reset); return *this; }
CErr_State&   CErr_State::operator= (const CErr_State& _state) {
	SAFE_LOCK(TBase::m_lock);
	this->m_buffer  = _state.m_buffer;
	this->m_code    = _state.m_code  ;
	this->m_result  = _state.m_result;
	this->m_lang    = _state.m_lang  ;
	return *this;
}
CErr_State&   CErr_State::operator= (_pc_sz  _sz_desc) {
	SAFE_LOCK(TBase::m_lock);
	this->m_buffer = _sz_desc;
	return *this;
}

bool CErr_State::operator == (err_code _value) const { return TBase::m_result == _value; }
bool CErr_State::operator != (err_code _value) const { return TBase::m_result != _value; }

/////////////////////////////////////////////////////////////////////////////

namespace shared { namespace sys_core {
	bool operator==(const bool _lhs, const CErr_State& _rhs) { return (_lhs == (bool)_rhs); }
	bool operator!=(const bool _lhs, const CErr_State& _rhs) { return (_lhs != (bool)_rhs); }
	bool operator==(const CErr_State& _lhs, const bool _rhs) { return ((bool)_lhs == _rhs); }
	bool operator!=(const CErr_State& _lhs, const bool _rhs) { return ((bool)_lhs != _rhs); }
}}

/////////////////////////////////////////////////////////////////////////////

namespace shared { namespace sys_core { namespace _impl {
}}}
using namespace shared::sys_core::_impl;

/////////////////////////////////////////////////////////////////////////////

CError:: CError(void) { m_state = false; }
CError:: CError(const CError& _err) {*this = _err;}
CError::~CError(void) { }

/////////////////////////////////////////////////////////////////////////////

_pc_sz  CError::Class (void) const      { SAFE_LOCK(m_state); return m_class.GetString(); }
void     CError::Class (_pc_sz _pClass) { SAFE_LOCK(m_state); m_class = _pClass;  }
void     CError::Class (_pc_sz _lp_sz_val, const bool bFormatted) {
	_lp_sz_val;
	SAFE_LOCK(m_state);
	m_class = _lp_sz_val;
	if (bFormatted) {
		const INT n_pos = m_class.ReverseFind(_T(':'));
		if (-1 != n_pos)
			m_class = m_class.Mid(0, n_pos - 1); // it is assumed that we remove colon symbols '::';
	}
}

/////////////////////////////////////////////////////////////////////////////

void      CError::Clear (void)           { m_state = false; }
dword     CError::Code  (void) const     { return (dword)m_state; }
void      CError::Code  (const dword _v) { ((CErr_Base&)m_state) = _v;
	this->State() = (_pc_sz)(CErr_Fmt() << (CErr_Pattern() << CErr_Pattern::e_line) << *this);
}
_pc_sz    CError::Desc  (void) const     { return m_state; }
bool      CError::Is    (void) const { return ((bool)m_state == true); }
err_code  CError::Last  (void)       { m_state.Set(::GetLastError()) ;  return *this; }
TLangRef& CError::Lang  (void) const { return m_state;   }
_pc_sz    CError::Method(void) const { SAFE_LOCK(m_state); return m_method.GetString(); }
void      CError::Method(_pc_sz _v)  { SAFE_LOCK(m_state); m_method = _v;}
void      CError::Reset (void)       { m_state = true;   }
err_code  CError::Result(void) const { return  m_state;  }
err_code  CError::Result(const err_code _new)
{
	if (_new == (err_code)m_state)
		return _new;

	if (SUCCEEDED(_new)) {
		m_state = false; return m_state;
	}
	SAFE_LOCK(m_state);

	::ATL::CString    cs_module = m_method; // saves an original;
	::ATL::CString    cs_source;

	_com_error com_err(_new);
	// https://docs.microsoft.com/en-us/windows/win32/api/oleauto/nf-oleauto-geterrorinfo
	::ATL::CComPtr<IErrorInfo> sp;
	if (S_OK == ::GetErrorInfo(0, &sp))
	{
		_com_error err(_new, sp, true);
		 com_err = err;

		if (com_err.Description().length()) this->State() = (_pc_sz)com_err.Description();
		if (com_err.Source().length()) m_class  = (_pc_sz)com_err.Source();
	}
	else {
		*this = _new;
		CErr_Details desc_;
		desc_ << _new;
		this->m_state = (_pc_sz)desc_;
	}

	if (m_class.IsEmpty())
		m_class = CErr_Msg().Na ();
	if (NULL == this->State().Get())
		this->State() = (CErr_Fmt() << (CErr_Pattern() << CErr_Pattern::e_line) << *this);

	return this->Result();
}

dword     CError::Show  (const HWND _h_owner) const {

	CString  cs_desc =(_pc_sz)(CErr_Fmt() << (CErr_Pattern() << CErr_Pattern::e_box) << *this);
	const dword d_resp = static_cast<dword>(
		::MessageBox(_h_owner, cs_desc.GetString(), _T("Error"), MB_OK | MB_ICONEXCLAMATION)
		);
	return d_resp;
}

/////////////////////////////////////////////////////////////////////////////

CErr_State& CError::State (void)       { return m_state; }
TErr_State& CError::State (void) const { return m_state; }

#if defined(_DEBUG)
CString CError::Print (const e_print e_opt) const {

	static _pc_sz lp_sz_pat_a = _T("cls::[%s]>>{state=[%s];context=[%s::%s()]}");
	static _pc_sz lp_sz_pat_b = _T("cls::[%s]>>{code=%u;result=0x%x;desc='%s'}");
	static _pc_sz lp_sz_pat_c = _T("cls::[%s]>>{context=[%s::%s()]}");
	static _pc_sz lp_sz_pat_r = _T("cls::[%s]>>{code=%u;result=0x%x;desc='%s';context=%s::%s()}");

	CString cs_out;
	if (e_print::e_all == e_opt) cs_out.Format(lp_sz_pat_a, (_pc_sz)__CLASS__, (_pc_sz)this->State().Print(), this->Class(), this->Method());
	if (e_print::e_base == e_opt) cs_out.Format(lp_sz_pat_b, (_pc_sz)__CLASS__, this->Code(), this->Result(), this->Desc());
	if (e_print::e_ctx == e_opt) cs_out.Format(lp_sz_pat_c, (_pc_sz)__CLASS__, this->Class(), this->Method());
	if (e_print::e_req == e_opt) cs_out.Format(lp_sz_pat_r, (_pc_sz)__CLASS__, this->Code(), this->Result(), this->Desc(), this->Class(), this->Method());
	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CError& CError::operator<<(const err_code _hr)  {  this->Result(_hr);       return *this; }
CError& CError::operator<<(const CString& _method) { *this << _method.GetString(); return *this; }
CError& CError::operator<<(_pc_sz _p_method)  {  this->Method(_p_method); return *this; }

CError& CError::operator= (const _com_error& err_ref) {
	err_ref;
	this->State().Set( // TODO: what is about this one: this->State() << _com_error()?
		err_ref.Error(), (_pc_sz) err_ref.Description()
	);
	SAFE_LOCK(m_state);
	this->m_class = (_pc_sz)err_ref.Source();
	return *this;
}

CError& CError::operator= (const CError& _err) {
	_err;
	this->State()   = _err.State();

	SAFE_LOCK(m_state);

	this->m_method  = _err.m_method;

	if (_err.m_class.IsEmpty() == false)
		this->m_class  = _err.m_class;

	return *this;
}
CError& CError::operator= (const dword  _code) { (m_state).Set(_code); return *this; }
CError& CError::operator= (const err_code  _hr) { (m_state).Set(_hr); return *this; }
CError& CError::operator= (_pc_sz  _p_desc  ) { this->State() = _p_desc; return *this; }
CError& CError::operator>>(_pc_sz  _p_class ) { this->Class(_p_class, true); return *this; }
CError& CError::operator>>(const CString& _class) { *this >> _class.GetString(); return *this; }

/////////////////////////////////////////////////////////////////////////////

CError::operator const bool(void) const { return this->Is();     }
CError::operator err_code   (void) const { return this->Result(); }
CError::operator _pc_sz   (void) const { return this->Desc();   }

/////////////////////////////////////////////////////////////////////////////

CError::operator CErr_State& (void)       { return m_state; }
CError::operator TErr_State& (void) const { return m_state; }

/////////////////////////////////////////////////////////////////////////////

namespace shared { namespace sys_core {
//
// important: operator must return true in cases when error object does not provide success;
//
bool operator==(const bool _lhs, const CError& _rhs) { return (_lhs != SUCCEEDED(_rhs.Result())); }
bool operator!=(const bool _lhs, const CError& _rhs) { return (_lhs == SUCCEEDED(_rhs.Result())); }
bool operator==(const CError& _lhs, const bool _rhs) { return (SUCCEEDED(_lhs.Result()) != _rhs); }
bool operator!=(const CError& _lhs, const bool _rhs) { return (SUCCEEDED(_lhs.Result()) == _rhs); }

}}
#if (1)
/////////////////////////////////////////////////////////////////////////////

CErr_Format:: CErr_Format(const CError& _err) : m_error_ref(_err) {}
CErr_Format::~CErr_Format(void) {}

/////////////////////////////////////////////////////////////////////////////

CString     CErr_Format::Do  (_pc_sz _lp_sz_sep) const {
	return CString((_pc_sz)(CErr_Fmt() << (CErr_Pattern() << CErr_Pattern::e_line) << _lp_sz_sep << m_error_ref));
}

CString     CErr_Format::Do_2(_pc_sz _lp_sz_sep) const {
	return CString((_pc_sz)(CErr_Fmt() << (CErr_Pattern() << CErr_Pattern::e_state) << _lp_sz_sep << m_error_ref));
}

CString     CErr_Format::Do_4(_pc_sz _lp_sz_sep) const {
	return CString((_pc_sz)(CErr_Fmt() << (CErr_Pattern() << CErr_Pattern::e_state) << _lp_sz_sep << m_error_ref));
}

CString     CErr_Format::Do_6(_pc_sz _lp_sz_pattern) const {
	if (NULL == _lp_sz_pattern || 0 == ::lstrlenW(_lp_sz_pattern))
		return CString();

	CString cs_fmt(_lp_sz_pattern);

	typedef enum _markers {
		e_none   = -1,
		e_result =  0,
		e_code   =  1,
		e_desc   =  2,
		e_module =  3,
		e_src    =  4,
	} _markers;

	static _pc_sz lp_sz_markers[] = {
		_T("$(x)"), _T("$(c)"), _T("$(d)"), _T("$(m)"), _T("$(s)")
	};

	typedef ::std::map<INT, _markers> TIndex;

	TIndex t_index;
	INT n_pos = 0;

	for (INT i_ = 0; i_ < _countof(lp_sz_markers); i_++) {
		n_pos = cs_fmt.Find(lp_sz_markers[i_], 0);
		if (-1 == n_pos)
			continue;
		switch (i_) {
		case 0: { t_index[n_pos] = _markers::e_result; } break;
		case 1: { t_index[n_pos] = _markers::e_code  ; } break;
		case 2: { t_index[n_pos] = _markers::e_desc  ; } break;
		case 3: { t_index[n_pos] = _markers::e_module; } break;
		case 4: { t_index[n_pos] = _markers::e_src   ; } break;
		}
		cs_fmt.Replace(lp_sz_markers[i_], _T(""));
	}
	return cs_fmt;
}
#endif