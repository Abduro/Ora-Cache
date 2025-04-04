/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Mar-2011 at 00:00:32am, GMT+3, Rostov-on-Don, Tuesday;
	This is Row27 project shared library generic handle class(es) implementation file. [voluntary project]
	-----------------------------------------------------------------------------
	Adopted to Platinum project on 29-Nov-2014 at 0:42:03am, GMT+3, Taganrog, Saturday; (https://platinumpayroll.co.nz) [oDesk.com]
	Adopted to File Guardian project on 27-May-2018 at 3:22:22p, UTC+7, Phuket, Rawai, Sunday; (https://thefileguardian.com/) [Upwork.com]
	Adopted to Ebo Pack solution on 25-Jul-2018 at 9:44:02p, UTC+7, Novosibirsk, Wednesday; [voluntary project]
	Adopted to Geometry Curve project on 17-Feb-2024 at 13:06:53.0334264, UTC+7, Novosibirsk, Saturday; [trying to find work in software ]
*/
#include "sys.mem.handle.h"

using namespace shared::memory;

/////////////////////////////////////////////////////////////////////////////

namespace shared { namespace memory { namespace _impl {

	_pc_sz Handle_2_str(const handle _handle) {

		static CString cs_handle;

		if (false){}
		else if (nullptr == _handle) { cs_handle = _T("#nullptr"); }
		else if (0 == _handle) { cs_handle = _T("#not_set"); }
		else if (__inv_handle_val == _handle) { cs_handle = _T("#inv_val"); }
		else { cs_handle.Format(_T("0x%8.8x"), _handle); }

		return cs_handle.GetString();
	}

}}}
using namespace shared::memory::_impl;
/////////////////////////////////////////////////////////////////////////////

THandle:: CHandle (const handle _value, bool _b_managed) : m_value(_value), m_managed(_b_managed) { m_error >> __CLASS__ << __METHOD__ << OLE_E_BLANK; }
THandle:: CHandle (const CHandle& _ref) : CHandle() { *this = _ref; }
THandle:: CHandle (THandle&& _victim) { *this = _victim; }
THandle::~CHandle (void) { if (this->Is()) this->Close(); }

/////////////////////////////////////////////////////////////////////////////

err_code  THandle::Attach(const handle _handle, bool _manage) {
	_handle; _manage;
	err_code e_result = TErrCodes::no_error;

	if (this->Is())
		e_result = this->Close();
	// the this->Is() property may rewrite the error state if it is called before attaching to new handle;
	m_error << __METHOD__ << S_OK;

	if (FAILED(THandle::Is(_handle)))
		return e_result = E_INVALIDARG;

	if (FAILED(e_result))
		return e_result;

	this->m_value = _handle;
	this->m_managed = _manage;

	return e_result;
}

handle    THandle::Detach(void) {

	m_error << __METHOD__ << S_OK;

	if (false == this->Is()) {
		m_error << TErrCodes::eObject::eHandle;
		return nullptr;
	}

	handle h_result = this->Value();
	this->m_value = __inv_handle_val;
	this->m_managed = false;

	return h_result;
}

/////////////////////////////////////////////////////////////////////////////

err_code  THandle::Clone (const handle _h_source) {
	_h_source;
	// the this->Is() property may rewrite the error state if it is called before cloning input handle;
	if (this->Is()) {
		const err_code e_result = this->Close();
		if (FAILED(e_result))
			return e_result; // the error object is alredy set to appropriate state;
	}
#if (0)
	if (this->Error())       // it is not necessary to check error object here, because if the handle of this class is not set, there is no Close() operation called;
		return this->Error();
#endif
	m_error <<__METHOD__ << TErrCodes::no_error;

	if (FAILED(THandle::Is(_h_source)))
		return m_error << E_INVALIDARG;

	// https://learn.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-duplicatehandle ;
	if (!::DuplicateHandle(
	     ::GetCurrentProcess(), const_cast<handle>(_h_source),
	     ::GetCurrentProcess(), &this->m_value, 0, FALSE, DUPLICATE_SAME_ACCESS))
		m_error.Last();
	else
		this->Managed(true);

	return this->Error();
}

err_code  THandle::Close (void) {
	m_error << __METHOD__ << TErrCodes::no_error;
	if (false == this->Managed()) {
		this->m_value = __inv_handle_val;
	}
	else if (TErrCodes::no_error == THandle::Close(this->m_value)) {
		this->Managed(false); // the handle is closed, i.e. it is destroyed, so the management flag is set to false;
	}
	return m_error;
}

TError&   THandle::Error (void) const { return this->m_error; }
#if (0)
const
bool      THandle::Is (void) const {return !(m_error << __METHOD__ << THandle::Is(this->Value())); }
#else
const bool THandle::Is (void) const {
	this->m_error << __METHOD__ << TErrCodes::no_error;

	const err_code e_result = THandle::Is(this->Value());
	this->m_error << e_result;

	return !this->Error();
}
#endif
const bool THandle::Managed (void) const { return this->m_managed; }  
const bool THandle::Managed (bool _yes_or_no) {
	_yes_or_no;
	const bool b_changed = this->Managed() != _yes_or_no;

	if (b_changed)
		this->m_managed = _yes_or_no;

	return b_changed;
}

const
handle&   THandle::Value (void) const { return this->m_value; }
err_code  THandle::Value (const handle& _handle, bool _b_clone) {
	_handle; _b_clone;
	return m_error << __METHOD__ << (_b_clone ? this->Clone(_handle) : this->Attach(_handle));
}
#if defined(_DEBUG)
CString   THandle::Print (const bool _error) const {

	static _pc_sz lp_sz_pat_n = _T("cls::[%s]>>{handle=%s;valid=%s}");
	static _pc_sz lp_sz_pat_e = _T("cls::[%s]>>{handle=%s;valid=%s;error=[%s]}");

	CString cs_handle; if (this->Value()) cs_handle.Format(_T("0x%8.8x"), this->Value()); else cs_handle = _T("#inv_handler");

	CString cs_this;
	if (!_error) cs_this.Format(lp_sz_pat_n, (_pc_sz)__CLASS__, Handle_2_str(this->Value()), TString().Bool(this->Is()));
	if ( _error) cs_this.Format(lp_sz_pat_e, (_pc_sz)__CLASS__, Handle_2_str(this->Value()), TString().Bool(this->Is()), this->Error().Print(TError::e_req).GetString());
	return  cs_this;
}
#endif
/////////////////////////////////////////////////////////////////////////////

THandle&  THandle::operator = (const THandle& _ref) { *this = _ref.Value(); *this << _ref.Managed(); return *this; }
THandle&  THandle::operator = (const handle& _hand) {  this->Value(_hand, true); return *this; }
THandle&  THandle::operator <<(const handle& _hand) {  this->Attach(_hand); return *this; }
THandle&  THandle::operator >>(handle& _out) {  _out = this->Detach(); return *this; }

THandle&  THandle::operator <<(const bool _b_manage) { this->Managed(_b_manage); return *this; }

THandle::operator handle (void) const { return this->Value(); }
THandle::operator bool (void) const { return this->Managed(); }

PHANDLE   THandle::operator & (void)  { return &m_value; }

THandle&  THandle::operator = (THandle&& _victim) {

	if (this->Is()) // it is the rare case in this context, but it must be taken into account anyway;
		this->Close();

	this->m_error = _victim.Error();
	this->m_value = _victim.m_value; _victim.m_value = __inv_handle_val;
	this->m_managed = _victim.Managed(); _victim.Managed(false);

	return *this;
}

/////////////////////////////////////////////////////////////////////////////

err_code THandle::Close (handle& _handle) {
	_handle;
	err_code e_result = THandle::Is(_handle);
	if (TErrCodes::no_error != e_result)
		return e_result;

	// https://learn.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-closehandle ;
	if (!::CloseHandle(_handle))
		e_result = __LastErrToHresult();
	else
		_handle = __inv_handle_val;

	return e_result;
}

err_code THandle::Is (const handle _handle) {
	_handle;
	err_code e_result = TErrCodes::no_error;

	if (!_handle || __inv_handle_val == _handle)
		return (e_result = TErrCodes::eObject::eHandle);
	// https://learn.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-gethandleinformation ;
	dword dw_flags = 0;
	if (!::GetHandleInformation(_handle, &dw_flags))
		e_result = __LastErrToHresult();

	return e_result;
}

/////////////////////////////////////////////////////////////////////////////

namespace shared { namespace sys_core { namespace _impl {}}}
using namespace shared::sys_core::_impl;

/////////////////////////////////////////////////////////////////////////////
#if (0)
CAutoHandleArray:: CAutoHandleArray(const dword dwSize) : m_handles(NULL), m_size(0)
{
	m_error.Reset();
	if (dwSize)
	{
		try
		{
			m_handles = new handle[dwSize];
			m_size = dwSize;
			m_error.Clear();
		}
		catch(::std::bad_alloc&){ m_error = E_OUTOFMEMORY; }
	}
	else
		m_error = E_INVALIDARG;
}

CAutoHandleArray::~CAutoHandleArray(void)
{
	if (m_handles)
	{
		try { delete [] m_handles; m_handles = NULL; } catch(...){}
	}
	m_size = 0;
}

/////////////////////////////////////////////////////////////////////////////

TErrorRef  CAutoHandleArray::Error  (void)const { return m_error; }
bool       CAutoHandleArray::Is     (void)const { return (NULL != m_handles && m_size); }
PHANDLE    CAutoHandleArray::Handles(void)const { return m_handles; }
dword      CAutoHandleArray::Size   (void)const { return m_size; }

/////////////////////////////////////////////////////////////////////////////

handle     CAutoHandleArray::operator[] (const INT nIndex) const
{
	return (!this->Is() || 0 > nIndex || INT(m_size - 1) < nIndex ? 0 : m_handles[nIndex]);
}

handle&    CAutoHandleArray::operator[] (const INT nIndex)
{
	return (!this->Is() || 0 > nIndex || INT(m_size - 1) < nIndex ? CHandle_Guard::Invalid() : m_handles[nIndex]);
}
#endif
/////////////////////////////////////////////////////////////////////////////
#if (0)
#define SAFE_LOCK_HANDLE() SAFE_LOCK(this->m_sync_obj)
/////////////////////////////////////////////////////////////////////////////

CHandleSafe:: CHandleSafe(const handle _handle) : m_value(_handle) { }
CHandleSafe::~CHandleSafe(void)
{
	SAFE_LOCK_HANDLE();
	ATLASSERT(INVALID_HANDLE_VALUE == m_value);
}

/////////////////////////////////////////////////////////////////////////////

CHandleSafe& CHandleSafe::operator=(const handle _handle)
{
	SAFE_LOCK_HANDLE();
	CHandle_Guard(m_value).Close_safe();
	m_value = _handle;
	return *this;
}

CHandleSafe::operator handle(void)
{
	SAFE_LOCK_HANDLE();
	handle handle_ = m_value;
	return handle_;
}

CHandleSafe::operator handle(void) const
{
	SAFE_LOCK_HANDLE();
	handle handle_ = m_value;
	return handle_;
}

/////////////////////////////////////////////////////////////////////////////

PHANDLE    CHandleSafe::operator&(void)
{
	SAFE_LOCK_HANDLE();
	PHANDLE p_handle_ = &m_value;
	return  p_handle_;
}

/////////////////////////////////////////////////////////////////////////////

handle     CHandleSafe::Handle(void) const
{
	SAFE_LOCK_HANDLE();
	handle handle_ = m_value;
	return handle_;
}

bool       CHandleSafe::Is(void) const
{
	handle handle_ = this->Handle();
	return (NULL != handle_ && INVALID_HANDLE_VALUE != handle_);
}

VOID       CHandleSafe::Reset(void)
{
	SAFE_LOCK_HANDLE();
	CHandle_Guard(m_value).Close_safe();
}
#endif
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
#if (0)
CStdHandle:: CStdHandle(const dword _handle_type) : THandle(), m_std_type(_handle_type) { m_error >> __CLASS__ << __METHOD__; 
	switch (m_std_type) {
	case STD_OUTPUT_HANDLE: { THandle::m_value = ::GetStdHandle(m_std_type); } break;
	case STD_ERROR_HANDLE : { THandle::m_value = ::GetStdHandle(m_std_type); } break;
	}
	if (this->Is() == false)
		m_error = __LastErrToHresult();
}
CStdHandle::~CStdHandle(void) {
	this->Close();
}

/////////////////////////////////////////////////////////////////////////////

HRESULT   CStdHandle::Close(void) {
	m_error << __METHOD__ << S_OK;
	if (this->Is()) {
		if (::SetStdHandle(m_std_type, THandle::m_value) == FALSE)
			m_error = __LastErrToHresult(); THandle::m_value = NULL;
	}
	return m_error;
}
TErrorRef CStdHandle::Error(void) const { return m_error; }
dword     CStdHandle::Type (void) const { return m_std_type; }

/////////////////////////////////////////////////////////////////////////////

CStdHandle& CStdHandle::operator=(const handle _handle) { _handle;
	m_error.State().Set(__DwordToHresult(ERROR_INVALID_OPERATION), _T("Standard handler cannot be replaced"));
	
	return *this;
}
#endif