/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-Mar-2026 at 12:07:00.084, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' generic data vector 2 interface implementation file;
*/
#include "math.vec.2x2.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl::math;

#pragma region s_vec_2{}

s_vec_2::s_vec_2 (void) : x(0.0f), y(0.0f) {}
s_vec_2::s_vec_2 (const float _values[u_count]) : s_vec_2(_values[0], _values[1]) {}
s_vec_2::s_vec_2 (const float _x, const float _y) : x(_x), y(_y) {}

float s_vec_2::Get_angle (const bool b_round, CError& _err) const {
	b_round;
	if (::abs(this->x) > 1.0f || ::abs(this->y) > 1.0f) {
		_err << (err_code) TErrCodes::eData::eInvalid = _T("The vector is not normalized;"); return 0.0f;
	}
	float f_angle = ::std::atan2f(this->y, this->x) * ::defs::rad_2_deg;
	if (b_round) {
		if (0.0f > f_angle) f_angle = ::std::floor(f_angle); else f_angle = ::std::ceil(f_angle);
	}
	return f_angle;
}

s_vec_2& s_vec_2::Invert (const float _f_scale)       { this->x /= _f_scale; this->y /= _f_scale; return *this; }      
s_vec_2  s_vec_2::Invert (const float _f_scale) const { return s_vec_2(this->x / _f_scale, this->y / _f_scale); }

bool  s_vec_2::Is_unit (void) const { return this->Length() <= 1.0f; }
float s_vec_2::Length (void) const { return ::sqrtf(this->Sum(2)); }

s_vec_2& s_vec_2::Negate (void) {
	this->x = -this->x; this->y = -this->y; return *this;
}
s_vec_2& s_vec_2::Normalize (void) {
	if (defs::f_epsilon > this->Length())
		return *this;
	const float f_inv_len = 1.0f/::sqrtf(this->Sum(2));
	this->x *=  f_inv_len;
	this->y *=  f_inv_len; return *this;
}

s_vec_2& s_vec_2::Round (void) {
	
	if (::abs(this->x) < defs::f_epsilon) this->x = 0.0f; else if (0.0f > this->x) this->x = ::std::floor(this->x); else this->x = ::std::ceil(this->x);
	if (::abs(this->y) < defs::f_epsilon) this->y = 0.0f; else if (0.0f > this->y) this->y = ::std::floor(this->y); else this->y = ::std::ceil(this->y);

	return *this;
}

s_vec_2& s_vec_2::Set (const float _values[u_count]) { return this->Set(_values[0], _values[1]); }
s_vec_2& s_vec_2::Set (const float _x, const float _y) { _x; _y; this->x = _x; this->y = _y;  return *this; }

float    s_vec_2::Sum (const uint32_t _u_exp/* = 1*/) const { return ::_pow_n(_u_exp, this->x) + ::_pow_n(_u_exp, this->y); }

CString  s_vec_2::To_str (_pc_sz _p_format) const {
	static _pc_sz pc_sz_pat = _T("x=%s;y=%s");
	CString cs_out; cs_out.Format(
		pc_sz_pat, TString().Float(this->x, _p_format), TString().Float(this->y, _p_format));
	return  cs_out;
}

s_vec_2  s_vec_2::operator  - (void) const { return s_vec_2(-this->x, -this->y); }
s_vec_2& s_vec_2::operator  - (void) { this->x *= -1.0f; this->y *= -1.0f; return *this; }

s_vec_2& s_vec_2::operator  = (const s_vec_2& _src) { this->x = _src.x; this->y = _src.y; return *this; }
s_vec_2& s_vec_2::operator *= (const s_vec_2& _multiplier) {
	_multiplier;
	this->x *= _multiplier.x;
	this->y *= _multiplier.y; return *this;
}

s_vec_2& s_vec_2::operator += (const s_vec_2& _v_2) {
	this->x += _v_2.x;
	this->y += _v_2.y; return *this;
}
s_vec_2& s_vec_2::operator -= (const s_vec_2& _v_2) {
	this->x -= _v_2.x;
	this->y -= _v_2.y; return *this;
}

s_vec_2& s_vec_2::operator += (const float _f_scalar) { this->x += _f_scalar; this->y += _f_scalar; return *this; }
s_vec_2& s_vec_2::operator -= (const float _f_scalar) { this->x -= _f_scalar; this->y -= _f_scalar; return *this; }

s_vec_2& s_vec_2::operator /= (const float _f_scale)       { return this->Invert(_f_scale); }     
s_vec_2  s_vec_2::operator /  (const float _f_scale) const { return this->Invert(_f_scale); } // double times of copying the result; not good :(

bool s_vec_2::operator == (const s_vec_2& _rhv) const { return (this->x == _rhv.x && this->y == _rhv.y); }

s_vec_2  s_vec_2::operator - (const s_vec_2& _v_what) const {
	return vec_2(this->x - _v_what.x, this->y - _v_what.y);
}

#pragma endregion

vec_2 operator - (const vec_2& _v_from, const vec_2& _v_what) {
	return vec_2(_v_from.x - _v_what.x, _v_from.y - _v_what.y);
}