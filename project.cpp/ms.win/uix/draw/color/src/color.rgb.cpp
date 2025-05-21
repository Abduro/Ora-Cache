/*
	Created by Tech_dog (ebontrop@gmail.com) on 9-Mar-2012 at 11:13:38am, GMT+3, Rostov-on-Don, Friday;
	This is SfxSOA Client Drawing Service Colour Quad class implementation file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack color project on 10-Oct-2021 at 5:20:32.8287634 am, UTC+7, Novosibirsk, Sunday;
*/
#include "color.rgb.h"

using namespace ex_ui::color::rgb;

/////////////////////////////////////////////////////////////////////////////

CQuad:: CQuad (clr_value _r, clr_value _g, clr_value _b, clr_value _a) : m_value{_r, _g, _b, _a}, m_valid(true){}
CQuad:: CQuad (clr_type _color) : CQuad() { this->Set(_color); }
CQuad:: CQuad (clr_type _color , clr_value _alpha) : CQuad() {
	*this << _color << _alpha;
}
CQuad:: CQuad (const CQuad& _src) : CQuad() { *this = _src; }
CQuad:: CQuad (CQuad&& _victim) : CQuad() { *this = _victim; }
CQuad::~CQuad (void) {}

/////////////////////////////////////////////////////////////////////////////

clr_value CQuad::A (void) const { return this->m_value[channel::a]; }
clr_value CQuad::B (void) const { return this->m_value[channel::b]; }
clr_value CQuad::G (void) const { return this->m_value[channel::g]; }
clr_value CQuad::R (void) const { return this->m_value[channel::r]; }

clr_value CQuad::Get (channel _channel) const { return this->m_value[_channel]; }

bool CQuad::A (clr_value _value) { return this->Set(channel::a, _value); }
bool CQuad::B (clr_value _value) { return this->Set(channel::b, _value); }
bool CQuad::G (clr_value _value) { return this->Set(channel::g, _value); }
bool CQuad::R (clr_value _value) { return this->Set(channel::r, _value); }

bool CQuad::Set (channel _channel, clr_value _value) {
	_channel; _value;
	const
	bool b_changed = _value != this->Get(_channel);
	if ( b_changed ) {
		this->m_value[_channel] = _value;
	}
	return b_changed;
}

bool CQuad::Set (rgb_color _color , bool _valid) {
	_color; _valid;
	const // inversion or opposition, expressed by the sign "!", very often leads to a logical error, because it (the sign) is barely noticeable;
	bool b_changed = false == ::Is_equal(this->ToRgbA(), _color, true); // no color channel value change maynn occur, but only alpha;
	if ( b_changed ) {
		this->A(::get_a_value(_color));
		this->B(::get_b_value(_color));
		this->G(::get_g_value(_color));
		this->R(::get_r_value(_color));
	}
	this->Is() = _valid; // does not care regarding possible color value change; just sets the validity flag;
	return b_changed;
}

bool CQuad::Set (rgb_color _color, clr_value _alpha, bool _valid) {
	_color; _alpha; _valid;
	const
	bool b_changed = !::Is_equal(this->ToRgbA(), _color, false); // just checks equality without taking into accont the alpha values;
	// does not care about setting sequence yet;
	if ( b_changed ) {
		this->A(_alpha);
		this->B(get_b_value(_color));
		this->G(get_g_value(_color));
		this->R(get_r_value(_color));
	}
	this->Is() = _valid; // the validity flag of this quad is not dependable from color difference, it is just set in any case;

	return b_changed;
}

bool CQuad::Set (clr_value _r, clr_value _g, clr_value _b, clr_value _a) {
	_r; _g; _b; _a;
	const bool b_changed = (this->R() != _r || this->G() != _g || this->B() != _b || this->A() != _a);
	// does not care about setting sequence yet;
	if (true == b_changed) {
		this->A(_a);
		this->B(_b);
		this->G(_g);
		this->R(_r);
	}
	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

clr_type CQuad::ToRgb  (void) const { return _r_g_b   (this->R(), this->G(), this->B()); }
clr_type CQuad::ToRgbA (void) const { return _r_g_b_a (this->R(), this->G(), this->B(), this->A()); }

/////////////////////////////////////////////////////////////////////////////

bool CQuad::Is_equal_to (const rgb_color _clr) const {
	_clr;
#if (0)
	// a comparing does not care about color channel bytes' position in input value, i.e, maybe red color needs to be checked first for higher performance;
	return (get_a_value(_clr) == this->A() && get_b_value(_clr) == this->B() && get_g_value(_clr) == this->G() && get_r_value(_clr) == this->R());
#else
	return ::Is_equal(this->ToRgbA(), _clr, true);
#endif
}

#if (0)
bool CQuad::Is (void) const { return this->ToRgbA() != clr_max; }
#else
const bool  CQuad::Is(void) const {
	return this->m_valid;
}
      bool& CQuad::Is(void)       { return this->m_valid; }
#endif
#ifdef _DEBUG
CString CQuad::Print (const e_print e_opt) const {
	e_opt;
	static _pc_sz pc_sz_pat_a  = _T("cls::[%s::%s]>>{value:[r=%u;g=%u;b=%u;a=%u];valid=%s}");
	static _pc_sz pc_sz_pat_n  = _T("[%s]>>{value:[r=%u;g=%u;b=%u;a=%u];valid=%s}");
	static _pc_sz pc_sz_pat_r  = _T("[r=%u;g=%u;b=%u;a=%u]");

	CString cs_valid = TStringEx().Bool(this->Is());
	CString cs_out;
	if (e_print::e_all == e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
		this->R(), this->G(), this->B(), this->A(), (_pc_sz)cs_valid);
	}
	if (e_print::e_no_ns == e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__,
			this->R(), this->G(), this->B(), this->A(), (_pc_sz)cs_valid);
	}
	if (e_print::e_req == e_opt) {
		cs_out.Format(pc_sz_pat_r, this->R(), this->G(), this->B(), this->A()/*, (_pc_sz)cs_valid*/);
	}
	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

	return  cs_out;
} 
#endif

void    CQuad::Reset (void) {
	::memset((void*)m_value[0], 0, sizeof(uint32_t) * channel::_count); this->m_valid = false;
} 

/////////////////////////////////////////////////////////////////////////////

CQuad&  CQuad::operator = (const CQuad& _ref) { *this << _ref.Is() << _ref.ToRgb() << _ref.A(); return *this; }
CQuad&  CQuad::operator = (CQuad&& _victim) { *this = _victim; _victim.Reset(); return *this; }

CQuad&  CQuad::operator <<(bool _valid) { this->Is() = _valid; return *this; }
CQuad&  CQuad::operator <<(rgb_color _color) { this->Set(_color, value_max); return *this; }
CQuad&  CQuad::operator <<(clr_value _alpha) { this->A(_alpha); return *this; }

/////////////////////////////////////////////////////////////////////////////

CQuad::operator bool (void) const { return this->Is(); }
CQuad::operator rgb_color (void) const { return this->ToRgb(); }

bool CQuad::operator == (rgb_color _color) const { return this->Is_equal_to(_color) == true ; } 
bool CQuad::operator != (rgb_color _color) const { return this->Is_equal_to(_color) == false; }

bool CQuad::operator == (const CQuad& _quad) const { return this->Is_equal_to(_quad) == true ; }
bool CQuad::operator != (const CQuad& _quad) const { return this->Is_equal_to(_quad) == false; }

/////////////////////////////////////////////////////////////////////////////

CColor:: CColor (void) : TBase() {}
CColor:: CColor (clr_type _color) : TBase(_color) {}
CColor:: CColor (clr_type _color , clr_value _alpha) : TBase(_color, _alpha) {}

/////////////////////////////////////////////////////////////////////////////

float CColor::Chroma (void) const {
	
	const float f_r = float(this->R()) / float(_Opaque);
	const float f_g = float(this->G()) / float(_Opaque);
	const float f_b = float(this->B()) / float(_Opaque);
	const
	float  f_saturation = ::sqrt(f_r * f_r + f_g * f_g + f_b * f_b);
	return f_saturation;
}

bool  CColor::Darken (const uint8_t _percent) {
	_percent;
#if (0)
	const bool b_is_set = TPercent::Is(_percent);
#else
	const bool b_is_set = TPercent::e_max >= _percent;
#endif
	if (!b_is_set)
		return b_is_set;

	const
	float factor = float(_percent)/ 100.0f;

	const clr_value b_dark = static_cast<clr_value>(::std::floorf(float(this->B()) * factor));
	const clr_value g_dark = static_cast<clr_value>(::std::floorf(float(this->G()) * factor));
	const clr_value r_dark = static_cast<clr_value>(::std::floorf(float(this->R()) * factor));

	if (b_dark > this->B()) this->B(0); else this->B(this->B() - b_dark);
	if (g_dark > this->G()) this->G(0); else this->G(this->G() - g_dark);
	if (r_dark > this->R()) this->R(0); else this->R(this->R() - r_dark);

	return (b_is_set);
}

bool  CColor::Darken (const TPercent& _percent) {
	_percent;
	return this->Darken((uint8_t)_percent.GetAsInt());
}

bool  CColor::Differ (const clr_type _src, const int8_t _percent) {
	_src; _percent;

	bool b_result = false;

	if (rgb_clr_none == _src)
		return b_result;

	float chroma_0 = this->Chroma();
	float chroma_1 = CColor(_src).Chroma();

	float differ_  = (chroma_0 < chroma_1 ? chroma_1 - chroma_0 : chroma_0 - chroma_1);
#if (0)
	*this << _src;    // this operator makes alpha value is max, i.e. >> 255; it is not acceptable, because the alpha must remain the same;
#else
	TBase::Set(_src); // the alpha value is kept the same, i.e. its value is copied;
#endif
	if ( int(differ_ * 100) < abs(_percent) )
	{
		if (_percent < 0)
			b_result = this->Darken (-_percent);
		else
			b_result = this->Lighten(+_percent);
	}
	return  b_result;
}

bool  CColor::Lighten(const uint8_t _percent) {
	_percent;
#if (0)
	const bool b_is_set = TPercent::Is(_percent);
#else
	const bool b_is_set = TPercent::e_max >= _percent;
#endif
	if (!b_is_set)
		return b_is_set;

	const
	float factor = float(_percent)/ 100.0f;

	const clr_value b_light = static_cast<clr_value>(::std::ceilf(float(this->B()) * factor));
	const clr_value g_light = static_cast<clr_value>(::std::ceilf(float(this->G()) * factor));
	const clr_value r_light = static_cast<clr_value>(::std::ceilf(float(this->R()) * factor));

	if (b_light + this->B() > value_max) this->B(value_max); else this->B(this->B() + b_light);
	if (g_light + this->G() > value_max) this->G(value_max); else this->G(this->G() + g_light);
	if (r_light + this->R() > value_max) this->R(value_max); else this->R(this->R() + r_light);

	return (b_is_set);
}

bool  CColor::Lighten(const TPercent& _percent) {
	_percent;
	return this->Lighten((uint8_t)_percent.GetAsInt()); // rude data type cast, but it is okay for this version of the implementation;
}

/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
CString CColor::Print (const e_print e_opt) const {
	e_opt;
#if (0)
	if (e_print::e_req == e_opt)
		return TBase::Print(e_opt);
#endif
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{rgba=%u:%u:%u:%u;(0x%x)}");
	static _pc_sz pc_sz_pat_r = _T("rgba=%u:%u:%u:%u;(0x%x)");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{rgba=%u:%u:%u:%u;(0x%x)}");

	CString cs_out;
	if (e_print::e_all == e_opt)
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
			TBase::R(), TBase::G(), TBase::B(), TBase::A(), TBase::ToRgbA()
		);
	if (e_print::e_no_ns == e_opt)
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__CLASS__,
			TBase::R(), TBase::G(), TBase::B(), TBase::A(), TBase::ToRgbA()
		);
	if (e_print::e_req == e_opt)
		cs_out.Format(pc_sz_pat_r, TBase::R(), TBase::G(), TBase::B(), TBase::A(), TBase::ToRgbA());

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);
		
	return cs_out;
}
#endif

/////////////////////////////////////////////////////////////////////////////

CClr_Float:: CClr_Float (void) : m_value{0.0f} {}
CClr_Float:: CClr_Float (const clr_type _clr) : CClr_Float() { *this << _clr; }
CClr_Float:: CClr_Float (const clr_value _r, const clr_value _g, const clr_value _b, const clr_value _a) : CClr_Float() {
	this->Set(_r_g_b_a(_r,_g,_b,_a));
}

/////////////////////////////////////////////////////////////////////////////

using e_ndx = CQuad::channel;

float CClr_Float::A (void) const { return this->m_value[e_ndx::a]; }
float CClr_Float::B (void) const { return this->m_value[e_ndx::b]; }
float CClr_Float::G (void) const { return this->m_value[e_ndx::g]; }
float CClr_Float::R (void) const { return this->m_value[e_ndx::r]; }

clr_float CClr_Float::Get (void) const {
	const clr_float v_result = {this->R(), this->G(), this->B(), this->A()};
	return v_result;
}

bool CClr_Float::A (const clr_value _u_value) {
	_u_value;
	const float f_value  = CConvert::ToFloat(_u_value);
	const bool b_changed = !Is_equal(this->A(), f_value); if (b_changed) this->m_value[e_ndx::a] = f_value;  return b_changed;
}

bool CClr_Float::B (const clr_value _u_value) {
	_u_value;
	const float f_value  = CConvert::ToFloat(_u_value);
	const bool b_changed = !Is_equal(this->B(), f_value); if (b_changed) this->m_value[e_ndx::b] = f_value;  return b_changed;
}

bool CClr_Float::G (const clr_value _u_value) {
	_u_value;
	const float f_value  = CConvert::ToFloat(_u_value);
	const bool b_changed = !Is_equal(this->G(), f_value); if (b_changed) this->m_value[e_ndx::g] = f_value;  return b_changed;
}

bool CClr_Float::R (const clr_value _u_value) {
	_u_value;
	const float f_value  = CConvert::ToFloat(_u_value);
	const bool b_changed = !Is_equal(this->R(), f_value); if (b_changed) this->m_value[e_ndx::r] = f_value;  return b_changed;
}

#if defined(_DEBUG)
CString  CClr_Float::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{r:%s;g:%s;b:%s;a:%s};");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{r:%s;g:%s;b:%s;a:%s};");
	static _pc_sz pc_sz_pat_r = _T("r:%s;g:%s;b:%s;a:%s");

	CString cs_a = TStringEx().Float(this->A());
	CString cs_b = TStringEx().Float(this->B());
	CString cs_g = TStringEx().Float(this->G());
	CString cs_r = TStringEx().Float(this->R());

	CString cs_out;
	if (e_print::e_all   == _e_opt)
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
			(_pc_sz)cs_r, (_pc_sz)cs_g, (_pc_sz)cs_b, (_pc_sz)cs_a
		);
	if (e_print::e_no_ns == _e_opt)
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__,
			(_pc_sz)cs_r, (_pc_sz)cs_g, (_pc_sz)cs_b, (_pc_sz)cs_a
		);
	if (e_print::e_req   == _e_opt)
		cs_out.Format(pc_sz_pat_r,
			(_pc_sz)cs_r, (_pc_sz)cs_g, (_pc_sz)cs_b, (_pc_sz)cs_a
		);

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
#endif

bool CClr_Float::Set (const clr_type _clr) {
	_clr;
	bool b_changed = false;
	if (this->A(get_a_value(_clr))) b_changed = true;
	if (this->B(get_b_value(_clr))) b_changed = true;
	if (this->G(get_g_value(_clr))) b_changed = true;
	if (this->R(get_r_value(_clr))) b_changed = true;
	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

CClr_Float&  CClr_Float::operator <<(const clr_type _clr) {
	this->Set(_clr);
	return *this;
}

/////////////////////////////////////////////////////////////////////////////

CHex:: CHex (clr_type _type) : m_color(_type) {}
CHex:: CHex (const CHex& _src) : CHex() { *this = _src; }
CHex::~CHex (void) {}

/////////////////////////////////////////////////////////////////////////////
const
CQuad& CHex::Color (void) const { return this->m_color; }
CQuad& CHex::Color (void)       { return this->m_color; }

/////////////////////////////////////////////////////////////////////////////

CHex& CHex::operator = (const CHex& _src) { *this << _src.Color(); return *this; }
CHex& CHex::operator <<(const clr_type _type) { this->Color() = _type; return *this; }
CHex& CHex::operator <<(const CQuad& _color) { this->Color() = _color; return *this; }

/////////////////////////////////////////////////////////////////////////////
#if defined (_DEBUG)
CString CHex::Print (const clr_type _clr) {
	_clr;
	static _pc_sz pc_sz_pat_v = _T("#%02x%02x%02x");

	CString cs_out; cs_out.Format(pc_sz_pat_v, ::get_r_value(_clr), ::get_g_value(_clr), ::get_b_value(_clr));
	return  cs_out;
}

CString CHex::Print (const CQuad& _quad, const e_print e_opt) {
	_quad; e_opt;

	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{value=%s; alpha=%03f}");
	static _pc_sz pc_sz_pat_r = _T("%s");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{value=%s; alpha=%03f}");

	CString cs_value = CHex::Print(_quad.ToRgbA());
	CString cs_out;

	if (e_print::e_all == e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)cs_value, _quad.A());
	}
	if (e_print::e_no_ns == e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz)cs_value, _quad.A());
	}
	if (e_print::e_req == e_opt) {
		cs_out.Format(pc_sz_pat_r, (_pc_sz)cs_value);
	}

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

	return  cs_out;
}
#endif