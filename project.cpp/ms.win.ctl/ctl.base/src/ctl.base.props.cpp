/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Dec-2021 at 00:39:58.7375024, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack UIX generic property collection interface implementation file;
*/
#include "ctl.base.props.h"

using namespace ex_ui::controls::properties;

#ifndef __H
#define __H(_rc) (_rc.bottom - _rc.top)
#endif

#ifndef __W
#define __W(_rc) (_rc.right - _rc.left)
#endif

/////////////////////////////////////////////////////////////////////////////

CAlign_Horz:: CAlign_Horz (const _value _n_value, _pc_sz _p_name, IProperty_Events* _p_events) : TBase (_n_value, _p_name, _p_events) {}
CAlign_Horz:: CAlign_Horz (const CAlign_Horz& _src) : CAlign_Horz() { *this = _src; }
CAlign_Horz::~CAlign_Horz (void) {}

/////////////////////////////////////////////////////////////////////////////

CAlign_Horz::operator uint32_t (void) const
{
	if (TBase::Has(_value::eRight))  return _value::eRight ;
	if (TBase::Has(_value::eCenter)) return _value::eCenter;

	return _value::eLeft;
}

CAlign_Horz&  CAlign_Horz::operator = (const CAlign_Horz& _src) { (TBase&)*this = (const TBase&)_src; return *this; }

/////////////////////////////////////////////////////////////////////////////

CAlign_Vert:: CAlign_Vert (const _value _n_value, _pc_sz _p_name, IProperty_Events* _p_events) : TBase (_n_value, _p_name, _p_events) {}
CAlign_Vert:: CAlign_Vert (const CAlign_Vert& _src) : CAlign_Vert() { *this = _src; }
CAlign_Vert::~CAlign_Vert (void) {}

/////////////////////////////////////////////////////////////////////////////

CAlign_Vert::operator uint32_t (void) const
{
	if (TBase::Has(_value::eMiddle)) return _value::eMiddle ;
	if (TBase::Has(_value::eBottom)) return _value::eBottom ;

	return _value::eTop;
}

CAlign_Vert&  CAlign_Vert::operator = (const CAlign_Vert& _src) { (TBase&)*this = (const TBase&)_src; return *this; }

/////////////////////////////////////////////////////////////////////////////

CAlign:: CAlign (void) {}
CAlign:: CAlign (const CAlign& _ref) : CAlign() { *this = _ref; }
CAlign:: CAlign (const CAlign_Horz& _horz, const CAlign_Vert& _vert) : CAlign() { *this << _horz << _vert; }
CAlign::~CAlign (void) {}

/////////////////////////////////////////////////////////////////////////////

void CAlign::ApplyTo (const t_rect& _rc_available, const t_size& _sz_accept, t_rect& _rc_aligned) const {
	_rc_available; _sz_accept; _rc_aligned;
	// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-copyrect
	if (FALSE == ::CopyRect(&_rc_aligned, &_rc_available))
		return;
	switch (this->Horz().Value()) {
	case CAlign_Horz::eLeft  :  { _rc_aligned.right = _rc_aligned.left + _sz_accept.cx; } break;
	case CAlign_Horz::eCenter:  { 
			_rc_aligned.left += (__W(_rc_aligned) - _sz_accept.cx)/2; 
			_rc_aligned.right = _rc_aligned.left + _sz_accept.cx;
		} break;
	case CAlign_Horz::eRight :  { _rc_aligned.left = _rc_aligned.right - _sz_accept.cx; } break;
	}

	switch (this->Vert().Value()) {
	case CAlign_Vert::eMiddle:  {
			_rc_aligned.top   += (__H(_rc_aligned) - _sz_accept.cy)/2; 
			_rc_aligned.bottom = _rc_aligned.top + _sz_accept.cy;
		} break;
	case CAlign_Vert::eTop   :  { _rc_aligned.bottom = _rc_aligned.top + _sz_accept.cy; } break;
	case CAlign_Vert::eBottom:  { _rc_aligned.top = _rc_aligned.bottom - _sz_accept.cy; } break;
	}
}
const
CAlign_Horz& CAlign::Horz(void) const { return m_horz; }
CAlign_Horz& CAlign::Horz(void)       { return m_horz; }
const
CAlign_Vert& CAlign::Vert(void) const { return m_vert; }
CAlign_Vert& CAlign::Vert(void)       { return m_vert; }

/////////////////////////////////////////////////////////////////////////////

CAlign& CAlign::operator = (const CAlign& _ref ) {*this << _ref.Horz() << _ref.Vert(); return *this; }
CAlign& CAlign::operator <<(const CAlign_Horz& _horz) { this->Horz() = _horz; return *this; }
CAlign& CAlign::operator <<(const CAlign_Vert& _vert) { this->Vert() = _vert; return *this; }
CAlign& CAlign::operator <<(IProperty_Events* _p_events) { this->Horz().Events(_p_events);  this->Vert().Events(_p_events); return *this; }

/////////////////////////////////////////////////////////////////////////////
#if (0)
CAlign& CAlign::operator <<(_pc_sz _lp_sz_style) {
	if (NULL == _lp_sz_style || 0 == ::lstrlen(_lp_sz_style))
		return *this;

	CString cs_low_case(_lp_sz_style);

	static const _pc_sz lp_sz_pat_horz[] = { _T("left"), _T("center"), _T("right")};
	for (INT i_ = 0; i_ < _countof(lp_sz_pat_horz); i_++) {
		if (-1 != cs_low_case.CompareNoCase(lp_sz_pat_horz[i_])) {
			if (i_ == 0) this->Horz() = CAlign_Horz::eLeft;
			if (i_ == 1) this->Horz() = CAlign_Horz::eCenter;
			if (i_ == 2) this->Horz() = CAlign_Horz::eRight;
		}
	}

	static const _pc_sz lp_sz_pat_vert[] = { _T("top"), _T("middle"), _T("bottom")};
	for (INT i_ = 0; i_ < _countof(lp_sz_pat_vert); i_++) {
		if (-1 != cs_low_case.CompareNoCase(lp_sz_pat_vert[i_])) {
			if (i_ == 0) this->Vert() = CAlign_Vert::eTop;
			if (i_ == 1) this->Vert() = CAlign_Vert::eMiddle;
			if (i_ == 2) this->Vert() = CAlign_Vert::eBottom;
		}
	}
	return *this;
}
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

/////////////////////////////////////////////////////////////////////////////

CState:: CState (const uint32_t _n_value, _pc_sz _p_name, IProperty_Events* _p_events) : TBase(_n_value, _p_name, _p_events) {}
CState:: CState (const CState& _src ) : TBase() { *this = _src; }
CState::~CState (void) {}

/////////////////////////////////////////////////////////////////////////////

bool  CState::IsDisabled(void)    const { return this->Has(e_states::eDisabled); }
bool  CState::IsHovered (void)    const { return this->Has(e_states::eHovered);  }
bool  CState::IsPressed (void)    const { return this->Has(e_states::ePressed);  }
bool  CState::IsSelected(void)    const { return this->Has(e_states::eSelected); }

/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
CString  CState::Print (void)    const {
	CString cs_state = (
		this->IsDisabled() ? _T("disabled") : (
			this->IsHovered() ? _T("hovered") : (
				this->IsPressed() ? _T("pressed") : (
					this->IsSelected() ? _T("selected") : _T("normal")))));
	return cs_state;
}
#endif
/////////////////////////////////////////////////////////////////////////////

uint32_t CState::Get (void) const { return TBase::m_value; }
uint32_t CState::Set (const CState::e_states _value)
{ 
	const DWORD d_prev = this->m_value;
	switch (_value)
	{
	case e_states::eDisabled: { TBase::m_value = e_states::eDisabled; } break; // removes all states on setting disabled state;
	case e_states::eHovered :
		if (this->IsDisabled() == false) {
			TBase::Modify(_value, true);    // if not in disabled state it is okay to set hovered one;
		} break;
	case e_states::eNormal: {
			TBase::Modify(e_states::eDisabled, false);
			TBase::Modify(e_states::eNormal  , true );
		} break;
	case e_states::ePressed:
		if (this->IsDisabled() == false) {
			TBase::Modify(e_states::ePressed, true);
		} break;
	case e_states::eSelected:
		if (this->IsDisabled() == false) {
			TBase::Modify(_value, true);    // if not in disabled state it is okay to set selected one;
		} break;
	}
	 return d_prev;
}

/////////////////////////////////////////////////////////////////////////////

CState& CState::operator = (const CState& _ref) { (TBase&)*this = (const TBase&)_ref; return *this; }
CState& CState::operator <<(const CState::e_states _curr) { this->Set(_curr); return *this; }

/////////////////////////////////////////////////////////////////////////////

size_t  CState::EnumToIndex(const CState::e_states _value) {

	size_t ndx_ = 0;

	switch(_value) {
	case CState::eDisabled: { ndx_ = 1; } break;
	case CState::eHovered : { ndx_ = 3; } break;
	case CState::eNormal  : { ndx_ = 0; } break;
	case CState::ePressed : { ndx_ = 4; } break;
	case CState::eSelected: { ndx_ = 2; } break;
	}
	return ndx_;	
}

CString CState::EnumToName(const CState::e_states _value) {

	CString cs_name(_T("#Undef"));

	switch(_value) {
	case CState::eDisabled: { cs_name = _T("Disabled"); } break;
	case CState::eHovered : { cs_name = _T("Hovered" ); } break;
	case CState::eNormal  : { cs_name = _T("Normal"  ); } break;
	case CState::ePressed : { cs_name = _T("Pressed" ); } break;
	case CState::eSelected: { cs_name = _T("Selected"); } break;
	}
	return cs_name;
}

CState::e_states CState::IndexToEnum(const size_t _ndx) {

	// stupid approach is going here:
	if (0 == _ndx) return CState::eNormal;
	if (1 == _ndx) return CState::eDisabled;
	if (2 == _ndx) return CState::eSelected;
	if (3 == _ndx) return CState::eHovered;
	if (4 == _ndx) return CState::ePressed;

	return CState::eNormal;
}

/////////////////////////////////////////////////////////////////////////////

CStyle:: CStyle(const uint32_t _n_value, _pc_sz _p_name, IProperty_Events* _p_events) : TBase(_n_value, _p_name, _p_events) {}
CStyle::~CStyle(void) {}

/////////////////////////////////////////////////////////////////////////////

bool   CStyle::IsBordered(void)   const  { return TBase::Has(e_styles::eBorder); }
bool   CStyle::IsBordered(const bool _v) { return TBase::Modify(e_styles::eBorder, _v); }