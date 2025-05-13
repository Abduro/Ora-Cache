/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Mar-2024 at 15:18:03.6008149, UTC+7, Omsk, Saturday; [Thai timezone is kept]
	This is Ebo pack UIX color library generic definition implementation file; 
*/
#include "color._defs.h"

using namespace ex_ui::color;
using namespace ex_ui::color::rgb;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace color { namespace rgb { namespace _impl {

	static long _get_multiplier (const uint8_t _n_digits)  {

		uint32_t u_multi = 1;

		for (uint8_t i_ = 0; i_ < _n_digits && i_ < CPercent_F::n_max_digits; i_++)
			u_multi *= 10;

		return u_multi;
	}

}}}}
using namespace ex_ui::color::rgb::_impl;

/////////////////////////////////////////////////////////////////////////////

CPercent_F:: CPercent_F (const CPercent_F& _src) : CPercent_F() { *this = _src; }

CPercent_F:: CPercent_F (const float _f_value) : m_value(_f_value) {}
CPercent_F:: CPercent_F (const int32_t _n_value) : CPercent_F() { *this << _n_value; }

/////////////////////////////////////////////////////////////////////////////

float    CPercent_F::Get (void) const { return this->m_value; }
int32_t  CPercent_F::GetAsInt (bool _no_round) const {
	return _no_round ? static_cast<int32_t>(this->Get()) : static_cast<int32_t>(::std::round(this->Get())); }

bool     CPercent_F::Set(const float _f_value) {
	_f_value;

	bool b_changed = false == this->Is_equal (_f_value);
	if ( b_changed )
		this->m_value = _f_value;

	return b_changed;
}

bool     CPercent_F::Set(const int32_t _n_value) {
	_n_value;

	bool b_changed = false == this->Is_equal (_n_value);
	if ( b_changed )
		this->m_value = float(_n_value);

	return b_changed;
}

bool    CPercent_F::Is_equal (const float  _f_value, const uint8_t _n_digits) const {
	_f_value; _n_digits;
	// https://stackoverflow.com/questions/17333/how-do-you-compare-float-and-double-while-accounting-for-precision-loss ;
	// the code below is one of the simplifications of the comparison for percentage use;

	const uint32_t u_multi = _get_multiplier(_n_digits);

	return (static_cast<long>(this->Get() * u_multi) == static_cast<long>(_f_value * u_multi));
}

bool    CPercent_F::Is_equal (const int32_t _n_value, const uint8_t _n_digits) const {
	_n_value; _n_digits;

	if (0 == _n_digits) // only integer part of the number is taken into account;
		return (_n_value == this->GetAsInt(true)); // no round method is applied;

	const uint32_t u_multi = _get_multiplier(_n_digits);

	const int32_t n_left  = static_cast<int32_t>(this->Get() * u_multi);
	const int32_t n_right = _n_value * u_multi;

	return (n_left == n_right);
}

#if defined(_DEBUG)
CString CPercent_F::Print (const e_print_f _e_opt_f, const e_print) const {
	_e_opt_f;
	static _pc_sz pc_sz_pat_ns = _T("cls::[%s]>>{value=%s%%}");

	CString cs_out;
	if (e_print_f::e_as_is  == _e_opt_f) cs_out.Format(pc_sz_pat_ns, (_pc_sz)__CLASS__, TStringEx().Float(this->Get()));
	if (e_print_f::e_as_int == _e_opt_f) cs_out.Format(pc_sz_pat_ns, (_pc_sz)__CLASS__, TStringEx().Long(this->GetAsInt()));

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt_f);

	return  cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////

CPercent_F&  CPercent_F::operator = (const CPercent_F& _src) { *this << _src.Get(); return *this; }

CPercent_F&  CPercent_F::operator <<(const float   _f_value) { this->Set(_f_value); return *this; }
CPercent_F&  CPercent_F::operator <<(const int32_t _n_value) { this->Set(_n_value); return *this; }

CPercent_F&  CPercent_F::operator+= (const CPercent_F& _f_inc) { this->m_value += _f_inc.Get(); return *this; }
CPercent_F&  CPercent_F::operator-= (const CPercent_F& _f_dec) { this->m_value -= _f_dec.Get(); return *this; }

CPercent_F&  CPercent_F::operator+= (const float _f_inc) { this->m_value += _f_inc; return *this; }
CPercent_F&  CPercent_F::operator-= (const float _f_dec) { this->m_value -= _f_dec; return *this; }

CPercent_F&  CPercent_F::operator+= (const int32_t _n_inc) { this->m_value += float(_n_inc); return *this; }
CPercent_F&  CPercent_F::operator-= (const int32_t _n_dec) { this->m_value -= float(_n_dec); return *this; }

CPercent_F::operator float   (void) const { return this->Get(); }
CPercent_F::operator int32_t (void) const { return this->GetAsInt(); }

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace color { namespace rgb {

	clr_value get_a_value (const clr_type _color) { return clr_value((uint32_t(_color) >> 24) & 0xff); }
	clr_value get_b_value (const clr_type _color) { return clr_value((uint32_t(_color) >> 16) & 0xff); }
	clr_value get_g_value (const clr_type _color) { return clr_value((uint16_t(_color) >>  8) & 0xff); }
	clr_value get_r_value (const clr_type _color) { return clr_value(_color & 0xff); }

}}}

/////////////////////////////////////////////////////////////////////////////

float CConvert::ToFloat (const clr_value _value) {
	const float f_invert = 1.0f / 255.0f; 
	return _value * f_invert; 
}

clr_value CConvert::ToValue (const float _value) {
	int32_t n_value = static_cast<int32_t>(_value * 256.0f);
	return static_cast<clr_value>(::std::clamp(n_value, 0, 255));
}

/////////////////////////////////////////////////////////////////////////////

CType:: CType (const clr_type _type) : m_type(_type) {}
CType:: CType (const CType& _src) : CType() { *this = _src; }
CType:: CType (CType&& _victim) { *this = _victim; }
CType::~CType (void) { /*nothing*/ }

/////////////////////////////////////////////////////////////////////////////

clr_type CType::Get (void) const { return this->m_type; }
bool CType::Set (clr_type _type) {
	_type;
	const bool b_changed = this->EqualTo(_type);

	if (b_changed)
		this->m_type = _type;

	return b_changed;
}

bool CType::EqualTo (const clr_type _type) const { return this->m_type != _type; }

#if defined(_DEBUG)
CString CType::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{type=%u};");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{type=%u};");
	static _pc_sz pc_sz_pat_r = _T("type=%u");

	CString cs_out;
	if (e_print::e_all   == _e_opt) cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, this->Get());
	if (e_print::e_no_ns == _e_opt) cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, this->Get());
	if (e_print::e_req   == _e_opt) cs_out.Format(pc_sz_pat_r, this->Get());

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////

CType& CType::operator = (const CType& _src) { *this << _src.Get(); return *this; }
CType& CType::operator = (CType&& _victim) {
	*this << _victim.Get(); _victim.Set(0); return *this;
}

CType& CType::operator <<(clr_type _type) { this->Set(_type); return *this; }

/////////////////////////////////////////////////////////////////////////////

CType::operator clr_type (void) const { return this->Get(); }

bool CType::operator == (const CType& _rhv) const { return this->EqualTo(_rhv); }
bool CType::operator != (const CType& _rhv) const { return this->EqualTo(_rhv) == false; }

bool CType::operator == (clr_type _type) const { return this->EqualTo(_type); }
bool CType::operator != (clr_type _type) const { return this->EqualTo(_type) == false; }

/////////////////////////////////////////////////////////////////////////////
#if (0)
bool operator == (const TRgbType& _lhv, const TRgbType& _rhv) { return _lhv != _rhv; }
#endif

bool Is_equal (const rgb_color _lhs, const rgb_color _rhs, const bool _b_compare_alpha) {
	_lhs; _rhs; _b_compare_alpha;
#if (1)
	if (false == _b_compare_alpha) {
		return (_lhs == _rhs);
	}
	else {
		static
		const uint32_t u_mask = 0x00ffffff; // alpha value is excluded;

		return (_lhs & u_mask) == (_rhs & u_mask) && (::get_a_value(_lhs) == ::get_a_value(_rhs));
	}
#else
	static
	const uint32_t u_mask = 0x00ffffff; // alpha value is excluded;

#if defined(_DEBUG)
	const rgb_color clr_l = (_lhs & u_mask);
	const rgb_color clr_r = (_rhs & u_mask);

	const rgb_value alpha_l = ::get_a_value(_lhs);
	const rgb_value alpha_r = ::get_a_value(_rhs);

	return (clr_l == clr_r) && (!_b_compare_alpha ? true : alpha_l== alpha_r);
#else
	return (_lhs & u_mask) == (_rhs & u_mask) && (!_b_compare_alpha ? true : ::get_a_value(_lhs) == ::get_a_value(_rhs));
#endif
#endif
}

bool Is_equal (const float _f_lhv, const float _f_rhv, const float _f_threshold) {
	return (::std::fabs(_f_lhv-_f_rhv) < _f_threshold);
}