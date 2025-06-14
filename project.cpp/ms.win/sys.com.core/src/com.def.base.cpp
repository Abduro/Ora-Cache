/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Mar-2025 at 18:56:27.5305473, UTC+4, Batumi, Sunday;
	This is Ebo Pack shared system comp-obj-model wrapper library base interface implementation file;
*/
#include "com.def.base.h"

using namespace shared::sys_core::com;

namespace shared { namespace sys_core { namespace com { namespace _impl {

	void __warning_lnk_4221(void) {}

}}}}

/////////////////////////////////////////////////////////////////////////////

CClsId:: CClsId (_pc_sz _p_cls_id) : m_cls_id{0}{ *this << _p_cls_id; }
CClsId:: CClsId (const _guid& _cls_id) : CClsId() { *this << _cls_id; }
CClsId:: CClsId (const CClsId& _src) : CClsId() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////

CString  CClsId::Get (void) const { return CString(TStringEx().Guid(this->Raw())); }
bool     CClsId::Set (_pc_sz _p_cls_id) {
	_p_cls_id;
	const _guid cls_id = TStringEx(_p_cls_id).Guid();
	const bool b_changed = cls_id != this->Raw();

	if (b_changed)
		this->Raw() = cls_id;

	return b_changed;
}

bool     CClsId::Set (const _guid& _cls_id) {
	_cls_id;
	const bool b_changed = (_cls_id != this->Raw());
	if (b_changed)
		this->Raw() = _cls_id;

	return b_changed;
}

bool     CClsId::Is_valid (void) const { return !!this->Get().Compare(TStringEx().Guid(__guid_null)); }

CString  CClsId::ProgId (void) const { return CString(CProgId(this->Raw()).Get()); }

#if defined(_DEBUG)
CString  CClsId::Print (const e_print e_opt) const {
	e_opt;

	static _pc_sz pc_sz_a = _T("cls::[%s::%s]>>{value=%s}");
	static _pc_sz pc_sz_n = _T("cls::[%s]>>{value=%s}");
	static _pc_sz pc_sz_r = _T("{value=%s}");

	CString cs_cls_id = TStringEx().Guid(this->Raw());
	CString cs_out;

	if (e_print::e_all   == e_opt) { cs_out.Format(pc_sz_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_cls_id); }
	if (e_print::e_no_ns == e_opt) { cs_out.Format(pc_sz_n, (_pc_sz)__CLASS__, (_pc_sz) cs_cls_id); }
	if (e_print::e_req   == e_opt) { cs_out.Format(pc_sz_r, (_pc_sz) cs_cls_id); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%d)"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

	return  cs_out;
}
#endif

const
_guid&   CClsId::Raw (void) const { return this->m_cls_id; }
_guid&   CClsId::Raw (void)       { return this->m_cls_id; }

/////////////////////////////////////////////////////////////////////////////

CClsId&  CClsId::operator = (const CClsId& _src) { *this << _src.Raw(); return *this; }

CClsId&  CClsId::operator <<(_pc_sz _p_cls_id) { this->Set(_p_cls_id); return *this; }
CClsId&  CClsId::operator <<(const CString& _cls_id) { this->Set((_pc_sz)_cls_id); return *this; }

CClsId&  CClsId::operator <<(const _guid& _cls_id) { this->Set(_cls_id); return *this; }

CClsId::operator const _guid&  (void) const { return this->Raw(); }
CClsId::operator const CString (void) const { return this->Get(); }

/////////////////////////////////////////////////////////////////////////////
_guid CClsId::Get (_pc_sz _p_prog_id) {
	_p_prog_id;
	// https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-clsidfromprogid ;
	_guid cls_id = { 0 };
	const err_code n_result = ::CLSIDFromProgID(_p_prog_id, &cls_id);
	if (__failed(n_result)) {
		cls_id = __guid_null;
	}
	return cls_id;
}
bool  CClsId::Has (_pc_sz _p_prog_id) {
	_p_prog_id;
	// it is not necessary to use TStringEx capability to convert guid to string and vice versa;
	CString cs_prog_id(_p_prog_id); cs_prog_id.Trim(); // does not care of null value, string class is designed good for making that;
	bool b_has = false == cs_prog_id.IsEmpty();
	if (!b_has)
		return b_has;

	_guid cls_id = { 0 };

	err_code n_result = ::CLSIDFromProgID(cs_prog_id.GetString(), &cls_id);
	b_has = (__is_okay(n_result));

	return b_has;
}

/////////////////////////////////////////////////////////////////////////////

CProgId:: CProgId (_pc_sz _p_val) { *this << _p_val; }
CProgId:: CProgId (const _guid& _cls_id) : CProgId() { *this << _cls_id; }
CProgId:: CProgId (const CProgId& _src) : CProgId() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////

_guid     CProgId::Cls (void) const {
   return CProgId::Cls (this->Get());
}
_pc_sz    CProgId::Get (void) const { return (_pc_sz)this->p_prog_id; }
bool      CProgId::Set (_pc_sz _p_val) {
	_p_val;
	const bool b_changed = (!!this->p_prog_id.Compare(_p_val));
	if (b_changed)
		this->p_prog_id = _p_val;

	return b_changed;
}
bool      CProgId::Set (const _guid& _value) {
	_value;
	return this->Set((_pc_sz)CProgId::Get(_value));
}

bool      CProgId::Is_valid (void) const { return false == this->p_prog_id.IsEmpty(); }

#if defined(_DEBUG)
CString   CProgId::Print (const e_print e_opt) const {
	e_opt;
	
	static _pc_sz pc_sz_a = _T("cls::[%s::%s]>>{value=%s}");
	static _pc_sz pc_sz_n = _T("cls::[%s]>>{value=%s}");
	static _pc_sz pc_sz_r = _T("{value=%s}");

	CString cs_value = (this->p_prog_id.IsEmpty() ? _T("#not_set") : (_pc_sz)this->p_prog_id);
	CString cs_out;

	if (e_print::e_all   == e_opt) { cs_out.Format(pc_sz_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)cs_value); }
	if (e_print::e_no_ns == e_opt) { cs_out.Format(pc_sz_n, (_pc_sz)__CLASS__, (_pc_sz)cs_value); }
	if (e_print::e_req   == e_opt) { cs_out.Format(pc_sz_r, (_pc_sz)cs_value); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%d)"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

	return  cs_out;
}
#endif

const
CString&  CProgId::Raw (void) const { return this->p_prog_id; }
CString&  CProgId::Raw (void) { return this->p_prog_id; }

/////////////////////////////////////////////////////////////////////////////

CProgId&  CProgId::operator = (const CProgId& _src) { *this << _src.Get(); return *this; }
CProgId&  CProgId::operator <<(_pc_sz _p_val) { this->Set(_p_val);  return *this; }
CProgId&  CProgId::operator <<(const _guid& _cls_id) { this->Set(_cls_id); return *this; }
CProgId&  CProgId::operator <<(const CString& _cs_val) { *this << _cs_val.GetString(); return *this; }

CProgId::operator _pc_sz (void) const { return this->Get(); }

/////////////////////////////////////////////////////////////////////////////

_guid   CProgId::Cls (_pc_sz _p_prog_id) {
	_p_prog_id;
	// https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-clsidfromprogid ;
	_guid cls_id = { 0 };
	const err_code n_result = ::CLSIDFromProgID(_p_prog_id, &cls_id);
	if (__failed(n_result)) {
		cls_id = __guid_null;
	}
	return cls_id;
}

CString CProgId::Get (_pc_sz _p_cls_id) {
	_p_cls_id;
	return CProgId::Get(TStringEx(_p_cls_id).Guid());
}

CString CProgId::Get (const _guid& _value) {
	_value;
	wchar_t* p_prog_id = 0;

	const err_code n_result = ::ProgIDFromCLSID(_value, &p_prog_id);
	if (__succeeded(n_result))
		return CString(p_prog_id);
	else
		return CString();
}

bool  CProgId::Has (_pc_sz _p_cls_id) {
	_p_cls_id;
	return CProgId::Has(TStringEx(_p_cls_id).Guid());
}

bool  CProgId::Has (const _guid& _cls_id) {
	_cls_id;

	bool b_has = false;
	wchar_t* p_prog_id = 0;

	const err_code n_result = ::ProgIDFromCLSID(_cls_id, &p_prog_id);
	return (b_has = (false == __failed(n_result)));
}

/////////////////////////////////////////////////////////////////////////////

CCoItemIdList:: CCoItemIdList (void) : m_p_list(nullptr) {}
CCoItemIdList::~CCoItemIdList (void) {
	if (this->Is_valid()) {
		::CoTaskMemFree(this->m_p_list); this->m_p_list = nullptr;
	}
}

/////////////////////////////////////////////////////////////////////////////

bool  CCoItemIdList::Is_valid (void) const { return !!this->m_p_list; }

const
LPITEMIDLIST*  CCoItemIdList::Ptr (void) const { return &this->m_p_list; }
LPITEMIDLIST*  CCoItemIdList::Ptr (void)       { return &this->m_p_list; }
const
LPITEMIDLIST&  CCoItemIdList::Ref (void) const { return  this->m_p_list; }
LPITEMIDLIST&  CCoItemIdList::Ref (void)       { return  this->m_p_list; }

/////////////////////////////////////////////////////////////////////////////

CCoItemIdList::operator const LPITEMIDLIST* (void) const { return this->Ptr(); }
CCoItemIdList::operator       LPITEMIDLIST* (void)       { return this->Ptr(); }

CCoItemIdList::operator const LPITEMIDLIST& (void) const { return this->Ref(); }
CCoItemIdList::operator       LPITEMIDLIST& (void)       { return this->Ref(); }