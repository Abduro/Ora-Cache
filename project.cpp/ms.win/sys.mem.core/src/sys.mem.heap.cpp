/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Apr-2010 at 2:03:22am, GMT+3, Rostov-on-Don, Thursday;
	This is Shared Lite Library raw data class implementation file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack on 28-May-2018 at 12:00:40p, UTC+7, Phuket, Rawai, Monday;
	Adopted to Geometry Curve project on 17-Feb-2024 at 23:45:52.1982136, UTC+7, Novosibirsk, Saturday;
*/
#include "sys.mem.heap.h"

using namespace shared::common;
using namespace shared::memory;

/////////////////////////////////////////////////////////////////////////////

bool  CHeap::Is_alloca (const void* const _p_ptr) {
	_p_ptr;
	bool b_it_is = false;

	if (nullptr == _p_ptr)
		return b_it_is;
#if (0)
	b_it_is = ::_CrtIsValidHeapPointer(_p_ptr); // https://learn.microsoft.com/en-us/previous-versions/ys6cfhhh(v=vs.140) ;
	if (false == b_it_is)
		return b_it_is;
#else
	b_it_is = false == CHeap::Is_stack(_p_ptr);
#endif
	return b_it_is;
}

/*
// // https://learn.microsoft.com/en-us/windows/win32/api/winnt/nf-winnt-ntcurrentteb ;
BOOL InsideStackHack(LPVOID p)
{
	PVOID pStackTop = NULL;
	PVOID pStackBottom = NULL;
	__asm
	{
		push    eax
		push    ebx
		mov     ebx,fs:[18h]
		mov     eax,dword ptr [ebx+4h]
		mov     pStackTop, eax
		mov     eax,dword ptr [ebx+0xe0c] //Undocumented... probably subject to change! -David Delaune
		mov     pStackBottom, eax
		pop     eax
		pop     ebx
	}
	return (pStackBottom < p && p <= pStackTop);
}
*/

bool  CHeap::Is_stack  (const void* const _p_ptr) {
	_p_ptr;
	bool b_is_in = false;

	if (nullptr == _p_ptr)
		return b_is_in;

	// https://learn.microsoft.com/en-us/windows/win32/api/winnt/nf-winnt-ntcurrentteb ;
	PNT_TIB lTeb = (PNT_TIB)::NtCurrentTeb();
	if (nullptr == lTeb)
		return b_is_in;

	PVOID pStackTop = lTeb->StackBase;
	if (nullptr == pStackTop)
		return b_is_in;

	MEMORY_BASIC_INFORMATION MemoryBasicInformation = {0};
	::VirtualQueryEx(::GetCurrentProcess(), _p_ptr, &MemoryBasicInformation, sizeof MemoryBasicInformation);

	PVOID pStackBottom = MemoryBasicInformation.AllocationBase;
	b_is_in = (pStackBottom < _p_ptr && _p_ptr <= pStackTop);

	return b_is_in;
}

/////////////////////////////////////////////////////////////////////////////

CRawBuffer:: CRawBuffer (void) : m_pData(nullptr), m_dwSize(0) { m_error >> __CLASS__ << __METHOD__ << OLE_E_BLANK; }
#if (0) // this class is not intended for managing data in heap memory sta
CRawBuffer:: CRawBuffer (const CRawBuffer& _src) : CRawBuffer() { *this = _src; }
CRawBuffer:: CRawBuffer (CRawBuffer&& _victim) : CRawBuffer() { *this = _victim; } // calling a default constructor looks like unnecessary;
#endif
CRawBuffer::~CRawBuffer (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code CRawBuffer::Clear (void) {
	m_error << __METHOD__ << TErrCodes::no_error;

	if (this->IsValid() == false) {
		return (m_error << (err_code) TErrCodes::eExecute::eState);
	}
	// IsValid() property returns true for validity the pointer in the heap, so invoking this method can be successful; 
	::memset(m_pData, 0, sizeof(byte) * m_dwSize);

	return m_error;
}

TError&  CRawBuffer::Error (void) const { return this->m_error; }

bool     CRawBuffer::IsEmpty(void) const {

	if (nullptr == this->m_pData) // in case when pointer is not initialized, the result is still to be pseudo-false;
		return false;
	// it works, but maybe there is better way of playing with it:
#if (false != true)
	for (dword i_ = 0; i_ < m_dwSize; i_ ++) {
		if (this->m_pData[i_] != 0)
			return false;
	}
#elif (false == true)
	if (this->m_dwSize == 0 && !this->m_pData[0])
		return (false);

	using word = WORD;
	// >> a very good discussion and supposed solutions:
	// https://stackoverflow.com/questions/6938219/how-to-check-whether-all-bytes-in-a-memory-block-are-zero ;
	byte* const p_data = this->m_pData;
	word w_spec = 0;
	const dword n_step = sizeof(word); // https://en.wikipedia.org/wiki/Data_structure_alignment ; perhaps the word data type is suitable;
	const dword n_el_count = this->m_dwSize / n_step;
	for ( dword i_ = 0; i_ < n_el_count - 1; i_ += n_step) {
		if (w_spec |= p_data[i_]) {
			return false;
		}
	}
	// the code block above requires check of alignment: if calculated number of steps does not cover the memory block (as a result of round)
	// and several bytes (that are less than a step length) at the end remain to be unchecked;
	// ToDo:
	// it is helpful to use MEMORY_ALLOCATION_ALIGNMENT that is defined in winnt.h:
	// https://learn.microsoft.com/en-us/windows/win32/api/heapapi/nf-heapapi-heapalloc ;
#else
	unsigned char* p_data = (unsigned char*)this->m_pData[0];
#endif
	return (true);
}

bool     CRawBuffer::IsValid (bool _verify) const {
	// ToDo: below is not good approach, if m_pData does not equal to null, the size value must be ignored;
	bool b_valid = (nullptr != m_pData/* && 0 != m_dwSize*/);
	if (!b_valid)
		return b_valid;

	if (_verify) {
		byte* p_req = nullptr; // no needs to validate the specific range or block of memoty within the heap;
		// https://learn.microsoft.com/en-us/windows/win32/api/heapapi/nf-heapapi-heapvalidate ;
		b_valid = !!::HeapValidate(this->m_pData, 0/*HEAP_NO_SERIALIZE*/, p_req); // *important*: throws a breakpoint in debug mode;
		if (!b_valid) {
			// unfortunately, there is no error code in the last error because this function does not set it in case of failing;
			(this->m_error << __METHOD__ << (err_code) TErrCodes::eObject::eHandle) = _T("Heap memory block validation failed;");
		}
	}
	else b_valid = !!this->m_dwSize;

	return (b_valid);
}

/////////////////////////////////////////////////////////////////////////////
#if (0) // these operators are disabled;
CRawBuffer& CRawBuffer::operator = (const CRawBuffer& _src) { _src; return *this; }
CRawBuffer& CRawBuffer::operator = (CRawBuffer&& _victim) { _victim; return *this; }
#endif
/////////////////////////////////////////////////////////////////////////////

CRawData:: CRawData (void) : TBase() { TBase::m_error >> __CLASS__; }
CRawData:: CRawData (const CRawData& raw_ref) : CRawData() { *this = raw_ref; }
#if (0)
CRawData:: CRawData (const _variant_t& _data) : CRawData() {
	_data ;
	if (_data.vt == VT_BSTR)
	{
		this->Create(
				reinterpret_cast<p_byte>(_data.bstrVal),
				static_cast<dword>(::SysStringByteLen(_data.bstrVal))
			);
	}
}
#endif
CRawData:: CRawData (const dword dwSize) : CRawData() { this->Create(dwSize); }
#if (0)
CRawData:: CRawData (const LPSAFEARRAY __psa, const VARTYPE __v_type) : CRawData() { this->Create(__psa, __v_type); }
#endif
CRawData:: CRawData (const byte* pData, const dword dwSize) : CRawData() { this->Create(pData, dwSize); }
CRawData::~CRawData (void) { this->Free(); }

/////////////////////////////////////////////////////////////////////////////

err_code   CRawData::Append (const CRawData&  _raw_data) {
	return this->Append( _raw_data.GetData(), _raw_data.GetSize());
}

err_code   CRawData::Append (const byte* pData, const dword dwSize) {
	pData; dwSize;
	TBase::m_error << __METHOD__ << TErrCodes::no_error;

	if (nullptr == pData || 0 == dwSize) // error C2446: '==': no conversion from 'int' to 'nullptr' in case of using nullptr;
		return (m_error << __e_invalid_arg);

	byte* pLocator = nullptr; // error C2440: cannot convert from 'nullptr' to 'shared::sys_core::p_byte';

	// https://learn.microsoft.com/en-us/windows/win32/memory/low-fragmentation-heap >> is not accessible directly and is used by system only;
	// the flag 'HEAP_NO_SERIALIZE' is required to verify this memory block faster;
	if (this->IsValid())
	{
		// https://learn.microsoft.com/en-us/windows/win32/api/heapapi/nf-heapapi-heaprealloc ;
		const dword dwNewSize = m_dwSize + dwSize;
		pLocator = reinterpret_cast<byte*>( ::HeapReAlloc(::GetProcessHeap(), HEAP_NO_SERIALIZE, m_pData, dwNewSize) );
		if (pLocator)
		{
			m_pData  = pLocator ; // this the beginning of the memory block, it is just updated;
			pLocator+= m_dwSize ; // is set for copying input data;
			m_dwSize = dwNewSize;
		}
		else
			m_error = __e_no_memory;
	}
	else {
		// https://learn.microsoft.com/en-us/windows/win32/api/heapapi/nf-heapapi-heapalloc ;
		m_dwSize = dwSize;
		m_pData  = reinterpret_cast<byte*>( ::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY|HEAP_NO_SERIALIZE, dwSize));
		if (m_pData)
			pLocator = m_pData;
		else
			m_error = __e_no_memory; // the function does not set error code to the last error one;
	}

	if (m_error == false)
	{
		const errno_t err_ = ::memcpy_s(pLocator, dwSize, pData, dwSize);
		if (err_)
			m_error = __e_no_memory;
	}
	return m_error;
}

err_code   CRawData::Attach (const byte* pData, const dword dwSize, const bool _reset) {
	pData; dwSize;
	TBase::m_error << __METHOD__ << TErrCodes::no_error;

	if (nullptr == pData)
		return (m_error << E_POINTER);

	if (0 == dwSize)
		return (m_error << __e_invalid_arg);

	if (this->IsValid()) {
		if (_reset == false)
			return (m_error << (err_code) TErrCodes::eObject::eInited);
		else if (__failed(this->Free()))
			return (m_error);
	}

	m_pData  = const_cast<byte*>(pData); // error C2440: '=': cannot convert from 'const byte *' to 'shared::sys_core::byte *';
	m_dwSize = dwSize;

	return TBase::Error();
}
#if (0)
err_code   CRawData::CopyToVariantAsArray(_variant_t& v_data) const {
	v_data;
	m_error << __METHOD__ << TErrCodes::no_error;

	if (!this->IsValid())
		return (m_error << OLE_E_BLANK);

	if (VT_EMPTY != v_data.vt)v_data.Clear();

	v_data.vt     = VT_ARRAY|VT_UI1;
	v_data.parray = NULL;

	SAFEARRAYBOUND bound[1] ={0};
	bound[0].lLbound        = 0;
	bound[0].cElements      = m_dwSize;

	v_data.parray = ::SafeArrayCreate(VT_UI1, 1, bound);
	if (!v_data.parray)
		return (m_error = __e_no_memory);

	UCHAR HUGEP* pData = nullptr;
	err_code hr_ = ::SafeArrayAccessData(v_data.parray, (void HUGEP**)&pData);
	if (__succeeded(hr_))
	{
		const errno_t err_no = ::memcpy_s((void*)pData, m_dwSize, (const void*)v_data.parray, m_dwSize);
		if (err_no)
			m_error = __e_no_memory;
		::SafeArrayUnaccessData(v_data.parray);
		pData = nullptr;
	}

	if (m_error == true) {
		::SafeArrayDestroy(v_data.parray);
		v_data.parray = nullptr;
		v_data.vt = VT_EMPTY;
	}

	return TBase::Error();
}

err_code   CRawData::CopyToVariantAsUtf16(_variant_t& v_data) const {
	v_data;
	m_error << __METHOD__ << TErrCodes::no_error;

	if (!this->IsValid())
		return (m_error << OLE_E_BLANK);

	if (VT_EMPTY != v_data.vt)v_data.Clear();

	USES_CONVERSION;
	v_data.Clear();
	v_data.vt = VT_BSTR;
	v_data.bstrVal = ::SysAllocStringLen(
				::A2BSTR(reinterpret_cast<LPCSTR>(m_pData)),
				static_cast<UINT>(m_dwSize)
			);
	if (nullptr == v_data.bstrVal) {
		v_data.vt = VT_EMPTY; m_error = __e_no_memory;
	}
	return m_error;
}

err_code   CRawData::CopyToVariantAsUtf8 (_variant_t& v_data)const {
	v_data;
	m_error << __METHOD__ << TErrCodes::no_error;

	if (!this->IsValid())
		return (m_error << OLE_E_BLANK);

	if (VT_EMPTY != v_data.vt)v_data.Clear();

	v_data.vt = VT_BSTR;
	v_data.bstrVal = ::SysAllocStringByteLen((LPCSTR)m_pData, m_dwSize);

	if (v_data.bstrVal)
		m_error = TErrCodes::no_error;
	else {
		v_data.vt = VT_EMPTY; m_error = __e_no_memory;
	}
	return m_error;
}
#endif
err_code   CRawData::Create (const dword dwSize) {
	dwSize;
	TBase::m_error << __METHOD__ << TErrCodes::no_error;

	if (0 == dwSize)
		return (TBase::m_error << __e_invalid_arg);

	if (this->IsValid())
		this->Free();

	if (dwSize) {
		TBase::m_pData = reinterpret_cast<PBYTE>(
					::HeapAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, dwSize)
				);
		if (nullptr == TBase::m_pData)
			m_error.Last();
		else {
			TBase::m_dwSize = dwSize;
		}
	}
	return TBase::m_error;
}

err_code   CRawData::Create (const byte* pData, const dword dwSize) {
	dwSize;
	this->Free(); // it is necessary for creating new memory block, otherwise the Append() will extend the existing memory block to new size;
	              // ToDo:: it is required to check new size of the memory block, because if it is less than existing one, a shrink operation is needed;
	return this->Append(pData, dwSize);
}
#if (0)
err_code    CRawData::Create (const LPSAFEARRAY _lp_array, const VARTYPE _v_expected) {
	_lp_array;
	m_error << __METHOD__ << S_OK;
	this->Free();

	CSfaAccessor sfa_acc(_lp_array);
	if (sfa_acc.Error())
		return (m_error = sfa_acc.Error());

	if (sfa_acc.Elements().Count() == 0)
		return (m_error << OLE_E_BLANK) = _T("The input array has no element;");

	const VARTYPE v_type = sfa_acc.Elements().Type();
	if (v_type != _v_expected)
		return (m_error << DISP_E_BADVARTYPE);
	
	LONG n_req_sz = 0;
	err_code hr_ = sfa_acc.Size(n_req_sz);
	if (FAILED(hr_))
		return (m_error = sfa_acc.Error());

	if (0 == n_req_sz)
		return (m_error << OLE_E_BLANK) = _T("The input array returns zero size;");

	return this->Append(sfa_acc.Data(), static_cast<DWORD>(n_req_sz));
}
#endif
err_code   CRawData::Create (_pc_sz _lp_sz_file) {
	_lp_sz_file;
	m_error << __METHOD__ << TErrCodes::no_error;

	if (nullptr == _lp_sz_file || 0 == ::_tcslen(_lp_sz_file))
		return (m_error << __e_invalid_arg);

	CFile the_file;
	err_code e_result = the_file.Create(_lp_sz_file, FILE_READ_DATA, FILE_SHARE_READ, OPEN_EXISTING);
	if (__failed(e_result))
		return  (m_error << e_result);

	ULONGLONG u_size = 0;
	e_result = the_file.Seek(0, FILE_BEGIN);
	if (__failed(e_result))
		return  (m_error << e_result);
		
	e_result = the_file.GetSize(u_size);
	if (__failed(e_result))
		return  (m_error << e_result);

	if (u_size & 0x0000ffff)
	{
		const dword  n_sz_req  = (dword) u_size;
		this->Create(n_sz_req);

		if (this->IsValid() == false)
			return TBase::Error();

		e_result = the_file.Read((LPVOID)this->GetData(), n_sz_req);
		if (__failed(e_result))
			m_error << e_result;
	}
	
	return TBase::Error();
}

err_code   CRawData::Extend (const dword _n_to_add) {
	_n_to_add;
	TBase::m_error << __METHOD__ << TErrCodes::no_error;

	if (0 == _n_to_add)
		return (m_error << __e_invalid_arg);

	if (this->IsValid() == false)
		this->Create (_n_to_add);
	else {
		const dword n_req = this->m_dwSize + _n_to_add;
		byte* pLocator = reinterpret_cast<byte*>(
					::HeapReAlloc(::GetProcessHeap(), HEAP_ZERO_MEMORY, TBase::m_pData, n_req)
				);
		if (pLocator)
		{
			m_pData  = pLocator;
			m_dwSize = n_req;
		}
		else
			m_error << __e_no_memory;
	}

	return TBase::Error();
}

p_byte     CRawData::Detach (void) {
	TBase::m_error << __METHOD__ << TErrCodes::no_error;

	if (this->IsValid() == false) {
		m_error << OLE_E_BLANK; return nullptr;
	}
	p_byte p_ret = TBase::m_pData; TBase::m_pData = nullptr; TBase::m_dwSize = 0; TBase::m_error << OLE_E_BLANK;
	return p_ret;
}

err_code   CRawData::Free   (void) {
	TBase::m_error << __METHOD__ << TErrCodes::no_error;

	m_dwSize = 0;

	if (this->m_pData) {
		if (!::HeapFree(::GetProcessHeap(), HEAP_NO_SERIALIZE, this->m_pData))
			TBase::m_error.Last();

		this->m_pData = nullptr;
		if (m_error)
			return m_error;
	}
	(TBase::m_error << OLE_E_BLANK) = _T("No data");

	return TErrCodes::no_error;
}
const
byte*      CRawData::GetData(void) const { return this->m_pData ; }
byte*      CRawData::GetData(void)       { return this->m_pData ; }
dword      CRawData::GetSize(void) const { return this->m_dwSize; }

err_code   CRawData::ToFile (_pc_sz _lp_sz_path) const {
	_lp_sz_path;
	TBase::m_error << __METHOD__ << TErrCodes::no_error;

	if (nullptr ==_lp_sz_path || !::_tcslen(_lp_sz_path))
		return (TBase::m_error << __e_invalid_arg) = _T("File path is invalid");

	CFile a_target;
	err_code e_result  = a_target.Create(_lp_sz_path, FILE_WRITE_DATA, FILE_SHARE_READ, CREATE_ALWAYS);
	if (__failed(e_result))
		return (TBase::m_error << e_result);

	e_result = a_target.Write((LPVOID)this->GetData(), this->GetSize());
	if (__succeeded(e_result))
		e_result = a_target.Flush();
		
	return (TBase::m_error << e_result);
}
#if (0) // moved to sys.com.core adapter class;
err_code    CRawData::ToSafeArray (LPSAFEARRAY& _out_array, const VARTYPE _v_expected) const {
	_out_array; _v_expected;
	m_error << __METHOD__ << S_OK;

	if (_v_expected != VT_UI1)
		return (m_error << __DwordToHresult(ERROR_UNSUPPORTED_TYPE));

	TSafeBytes sfa_arr;

	err_code hr_ = sfa_arr.Create(this->GetSize());
	if (FAILED(hr_))
		return (m_error << hr_);

	CSfaAccessor sfa_acc(sfa_arr);

	PBYTE p_data = sfa_acc.Data();
	LONG  l_size = 0;

	hr_ = sfa_acc.Size(l_size);
	if (FAILED(hr_))
		return (m_error = sfa_acc.Error());
	
	const errno_t e_result = ::memcpy_s(p_data, static_cast<rsize_t>(l_size), this->GetData(), static_cast<rsize_t>(this->GetSize()));
	if (NOERROR != e_result)
		m_error << __e_no_memory;

	return m_error;
}
#endif
err_code   CRawData::ToStringUtf16(CStringW& _utf16) const {
	_utf16;
	TBase::m_error << __METHOD__ << TErrCodes::no_error;

	if (this->IsValid() == false)
		return (m_error << OLE_E_BLANK);

	_utf16.Append(
			reinterpret_cast<_pc_sz>(this->GetData()),
			static_cast<int>(this->GetSize()/sizeof(wchar_t))
		);

	return TBase::Error();
}

err_code   CRawData::ToStringUtf8 (CAtlStringA& _utf8) const {
	_utf8;
	TBase::m_error << __METHOD__ << TErrCodes::no_error;

	if (this->IsValid() == false)
		return (TBase::m_error << OLE_E_BLANK);

	_utf8.Append(
			reinterpret_cast<const char*>(this->GetData()),
			static_cast<int>(this->GetSize())
		);

	return TBase::Error();
}

/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
CString    CRawData::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz p_sz_pat_a = _T("cls::[%s::%s] >> {size=%u(byte(s));valid=%s}");
	static _pc_sz p_sz_pat_n = _T("cls::[%s] >> {size=%u(byte(s));valid=%s}");
	static _pc_sz p_sz_pat_r = _T("size=%u(byte(s));valid=%s");

	CString cs_valid = TStringEx().Bool(TBase::IsValid());
	CString cs_out;

	if (e_print::e_all   == _e_opt) { cs_out.Format (p_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, this->GetSize(), (_pc_sz) cs_valid); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (p_sz_pat_n, (_pc_sz)__CLASS__, this->GetSize(), (_pc_sz) cs_valid); }
	if (e_print::e_req   == _e_opt) { cs_out.Format (p_sz_pat_r, this->GetSize(), (_pc_sz) cs_valid); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////

CRawData::operator const    bool  (void)const { return this->IsValid(); }
CRawData::operator const    dword (void)const { return TBase::m_dwSize; }
CRawData::operator const    p_byte(void)const { return TBase::m_pData ; }
CRawData::operator          p_byte(void)      { return TBase::m_pData ; }

/////////////////////////////////////////////////////////////////////////////

CRawData& CRawData::operator+=(const CRawData& raw_ref) { this->Append( raw_ref ); return *this; }
CRawData& CRawData::operator= (const CRawData& raw_ref) { this->Create( raw_ref.GetData(), raw_ref.GetSize()); return *this; }
#if (0) // moved to sys.com.core adapter class;
CRawData& CRawData::operator= (const _variant_t& _data) {
	_data;
	if (_data.vt == VT_BSTR)
	{
		this->Create(
				reinterpret_cast<pc_byte>(_data.bstrVal),
				static_cast<dword>(::SysStringByteLen(_data.bstrVal))
			);
	}
	return *this;
}
#endif
CRawData& CRawData::operator= (const ::std::vector<byte>& _vec) {

	if (_vec.empty() == true)
		return *this;

	this->Create(
			(pc_byte)_vec.data(), static_cast<dword>(_vec.size()) * sizeof(byte)
		);
	return *this;
}