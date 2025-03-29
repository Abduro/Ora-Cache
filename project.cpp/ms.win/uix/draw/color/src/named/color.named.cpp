/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Sep-2021 at 10:38:09.705 pm, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack UIX named color interface implementation file.
*/
#include "color.named.h"

using namespace ex_ui::color::rgb;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace color { namespace rgb { namespace _impl {
}}}}
using namespace ex_ui::color::rgb::_impl;

/////////////////////////////////////////////////////////////////////////////

CNamed:: CNamed (void) {}
CNamed:: CNamed (const CNamed& _ref) : CNamed() { *this = _ref; }
CNamed:: CNamed (const CColor& _clr, _pc_sz _lp_sz_name) : CNamed() { *this << _clr << _lp_sz_name; }
CNamed::~CNamed (void) {}

/////////////////////////////////////////////////////////////////////////////
const
CColor&  CNamed::Color (void) const { return this->m_color; }
CColor&  CNamed::Color (void)       { return this->m_color; }

_pc_sz   CNamed::Name  (void) const { return this->m_name.GetString(); }
bool     CNamed::Name  (_pc_sz _lp_sz_name) {
	_lp_sz_name;
	bool b_is_set = false;

	CString cs_name(_lp_sz_name);
	if (cs_name.IsEmpty())
		return b_is_set;

	cs_name.Trim();
	if (cs_name.IsEmpty())
		return b_is_set;

	this->m_name = cs_name;

	return (b_is_set = true);
}

/////////////////////////////////////////////////////////////////////////////

const bool CNamed::Is (void) const { return (this->Color().Is() && false == this->m_name.IsEmpty()); }

#if defined(_DEBUG)
CString  CNamed::Print (const e_print e_opt) const {
	e_opt;

	static _pc_sz pc_sz_pat_a = _T("cls::[%s]>>{clr=%s;name=%s}");
	static _pc_sz pc_sz_pat_r = _T("%s;%s");

	CString cs_out;

	if (e_print::e_all == e_opt) { cs_out.Format(pc_sz_pat_a,
	                                       (_pc_sz)__CLASS__, (_pc_sz)CHex::Print(this->Color().ToRgbA()), this->Name()); }
	if (e_print::e_req == e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz)CHex::Print(this->Color().ToRgbA()), this->Name()); }

	return  cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CNamed&  CNamed::operator = (const CNamed&  _src) {*this << _src.Color() << _src.Name(); return *this; }
CNamed&  CNamed::operator <<(const CColor&  _clr) { this->Color() = _clr; return *this; }
CNamed&  CNamed::operator <<(_pc_sz  _lp_sz_name) { this->Name(_lp_sz_name); return *this; }

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace color { namespace rgb { namespace _impl {
#if (0)
	
#else
	TNamedClrRaw& _get_named(void) {
		static TNamedClrRaw clr_raw; return clr_raw;
	}
#endif
}}}}
using namespace ex_ui::color::rgb::_impl;
/////////////////////////////////////////////////////////////////////////////

CNamed_Enum:: CNamed_Enum (void) {}
CNamed_Enum::~CNamed_Enum (void) {}

/////////////////////////////////////////////////////////////////////////////
const
TNamedColor&  CNamed_Enum::Get (const uint32_t _u_id) const {
	_u_id;
	TNamedClrRaw::const_iterator it_ = _get_named().find(_u_id);
	if (it_ == _get_named().end ())
	{
		static TNamedColor clr_undef(0, _T("#undef"));
		return clr_undef;
	}
	else
		return it_->second;
}

/////////////////////////////////////////////////////////////////////////////
const
TNamedClrRaw&  CNamed_Enum::Raw (void) const { return _get_named(); }