/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Jun-2025 at 05:01:15.706, UTC+4, Batume, Saturday;
	This is Ebo Pack generic property interface implementation file;
*/
#include "shared.props.h"

using namespace shared::common;

#ifndef __s_ok
#define __s_ok (0L)
#endif

/////////////////////////////////////////////////////////////////////////////

CProperty:: CProperty (const uint32_t _n_value, _pc_sz _p_name, IProperty_Events* _p_callee) : m_value(_n_value), m_name(_p_name), m_callee(_p_callee) {}
CProperty:: CProperty (const CProperty& _src) : CProperty() { *this = _src; }
CProperty::~CProperty (void) {}

/////////////////////////////////////////////////////////////////////////////

bool  CProperty::Has (const uint32_t _v) const { return (0 != (_v & m_value)); }
bool  CProperty::Modify (const uint32_t _v, const bool _bApply)
{
#if (0)
	bool b_result = (this->Has(_v));
	if (!b_result)
		return b_result;
#else
	// if b_result is true that means the actual value of this property is going to be changed; i.e.:
	// rules:
	//   (a) this property has input value and the value must be removed (not applied);
	//   (b) this property has *no* input value and the value must be applied;
	bool b_result = (this->Has(_v) && !_bApply) || (!this->Has(_v) && _bApply);
#endif
	// does not care about containing input value;
	if (_bApply) m_value |=  _v;
	else         m_value &= ~_v;

	if (nullptr != this->Events() && b_result)
		this->m_callee->IProperty_IsChanged();  // no return value evaluation this time;
#if (0)
	return (b_result = true);
#else
	return (b_result);
#endif
}

_pc_sz   CProperty::Name  (void) const  { return this->m_name.GetString(); }
bool     CProperty::Name  (_pc_sz _p_name) {
	_p_name;
	bool b_changed = !!this->m_name.Compare(_p_name);
	if ( b_changed )
		this->m_name = _p_name;

	return b_changed;
}

#if defined(_DEBUG)
CString  CProperty::Print (const e_print _e_opt) const {
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{name=%s;value=%d}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{name=%s;value=%d}");
	static _pc_sz pc_sz_pat_r = _T("{name=%s;value=%d}");

	CString cs_out;
	if (e_print::e_all   == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, this->Name(), this->Value());
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, this->Name(), this->Value());
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, this->Name(), this->Value()); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

const
uint32_t& CProperty::Value(void) const { return m_value; }
uint32_t& CProperty::Value(void)       { return m_value; }

uint32_t  CProperty::Get (void) const { return this->Value(); }
bool      CProperty::Set (uint32_t _value)
{
	bool b_result = (this->Value() != _value);

	if (!b_result)
		return b_result;

	this->Value() =  _value;
	if (nullptr !=  this->Events())
		this->m_callee->IProperty_IsChanged();

	return b_result;
}

IProperty_Events* CProperty::Events (void) const { return this->m_callee; }
HRESULT           CProperty::Events (IProperty_Events* _p_events) { this->m_callee = _p_events; return __s_ok; }

/////////////////////////////////////////////////////////////////////////////

CProperty::operator const uint32_t (void) const { return this->Value(); }

CProperty&   CProperty::operator = (const CProperty& _ref) { *this << _ref.Events() << _ref.Value() << _ref.Name(); return *this; }

CProperty&   CProperty::operator<< (const uint32_t _value) { this->Set(_value); return *this; }
CProperty&   CProperty::operator+= (const uint32_t _value) { this->Modify(_value, true); return *this; }
CProperty&   CProperty::operator-= (const uint32_t _value) { this->Modify(_value, false); return *this; }

CProperty&   CProperty::operator<< (IProperty_Events* _p_events) { this->Events(_p_events); return *this; }
CProperty&   CProperty::operator<< (_pc_sz _p_name) { this->Name(_p_name);  return *this; }

/////////////////////////////////////////////////////////////////////////////

bool CProperty::operator != (const CProperty& _ref) const { return *this != _ref.Value(); }
bool CProperty::operator == (const CProperty& _ref) const { return *this == _ref.Value(); }

bool CProperty::operator != (uint32_t _value) const { return this->Value() != _value; }
bool CProperty::operator == (uint32_t _value) const { return this->Value() == _value; }