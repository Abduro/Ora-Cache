/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Sep-2024 at 10:07:22.197, UTC+4, Batumi, Thursday;
	This is Ebo Pack system comp-obj-model generic guid interface implementation file;
*/
#include "com.guid.h"

using namespace shared::sys_core::com;

/////////////////////////////////////////////////////////////////////////////

CGuid:: CGuid (void) : m_guid{0}/*(__guid_null)*/ {}
CGuid:: CGuid (_pc_sz _p_guid) : CGuid() { *this << _p_guid; }
CGuid:: CGuid (const CGuid& _src) : CGuid() { *this = _src; }
CGuid:: CGuid (const GUID& _guid) : CGuid() { *this << _guid; }
CGuid::~CGuid (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code CGuid::Create (void) {
	return ::CoCreateGuid(&this->m_guid);
}

const
GUID&   CGuid::Get (void) const { return this->m_guid; }

bool    CGuid::Set (_pc_sz _p_guid) {

	TStringEx t_str(_p_guid);

	return  this->Set(t_str.Guid());
}

bool    CGuid::Set (const GUID& _guid) {
	_guid;
	bool b_changed = this->Is_equal(_guid);
	if ( b_changed )
		this->m_guid = _guid;

	return b_changed;
}

bool    CGuid::Is_equal (const GUID& _guid) const {
	return !!::IsEqualGUID(this->Get(), _guid);
}

bool    CGuid::Is_null (void) const {
	return CGuid::Is_null(this->Get());
}

bool    CGuid::Is_valid (void) const {
#if (0)
	return false == this->Is_null() && false == CGuid::Is_null(TStringEx(this->To_string()).Guid());
#else
	return CGuid::Is_valid(this->Get());
#endif
}

#if defined(_DEBUG)
CString CGuid::Print (const e_print e_opt) const {

	static _pc_sz pc_sz_pat_a = _T("cls::[%s] >> {value=%s; valid=%s; is_null=%s}");
	static _pc_sz pc_sz_pat_r = _T("cls::[%s].value=%s;");

	CString cs_out;
	if (e_print::e_all == e_opt) cs_out.Format(pc_sz_pat_a, (_pc_sz)__CLASS__, TStringEx().Guid(this->Get()), TStringEx().Bool(this->Is_valid()), TStringEx().Bool(this->Is_null()));
	if (e_print::e_req == e_opt) cs_out.Format(pc_sz_pat_r, (_pc_sz)__CLASS__, TStringEx().Guid(this->Get()));
	return  cs_out;
}
#endif

CString CGuid::To_string (void) const { return TStringEx().Guid(this->Get()); }

/////////////////////////////////////////////////////////////////////////////

namespace shell { namespace ext { namespace core {

	// https://learn.microsoft.com/en-us/windows/win32/api/guiddef/nf-guiddef-isequalguid ;
#if (0)
	bool operator == (const GUID& _lhv, const GUID& _rhv) {
		_lhv; _rhv;
		return !!::IsEqualGUID(_lhv, _rhv);
	}
	bool operator != (const GUID& _lhv, const GUID& _rhv) {
		_lhv; _rhv;
		return 0 == ::IsEqualGUID(_lhv, _rhv);
	}
#endif
}}}

/////////////////////////////////////////////////////////////////////////////

CGuid&  CGuid::operator = (const CGuid& _src) { *this << _src.Get(); return *this; }
CGuid&  CGuid::operator <<(const GUID& _guid) {  this->Set(_guid)  ; return *this; }
CGuid&  CGuid::operator <<(_pc_sz _p_guid)    {  this->Set(_p_guid); return *this; }

#pragma warning(disable: 4227)
CGuid::operator const GUID  (void) const { return this->Get(); }
CGuid::operator const GUID& (void) const { return this->Get(); }
#pragma warning(default: 4227)

bool CGuid::operator == (const CGuid& _guid) const { return this->Is_equal(_guid.Get()); }
bool CGuid::operator != (const CGuid& _guid) const { return false == this->Is_equal(_guid.Get()); }

/////////////////////////////////////////////////////////////////////////////

CGuid& CGuid::Ref (void) {

	static CGuid stat_guid;
	return stat_guid;
}

bool  CGuid::Is_null (const GUID& _guid) {
	return !!::IsEqualGUID(_guid,__guid_null);
}

bool  CGuid::Is_valid (const GUID& _guid) {
	return false == CGuid::Is_null(_guid) && nullptr != TStringEx().Guid(_guid);
}