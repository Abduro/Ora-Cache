/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Mar-2026 at 16:49:27.708, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' generic data vector 3 interface implementation file;
*/
#include "math.vec.3.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl::math;

#pragma region s_vec_3{}

s_vec_3::s_vec_3 (void) : s_vec_2(), z(0.0f) {}
s_vec_3::s_vec_3 (const t_set_3& _arr_values) : s_vec_3(_arr_values.at(0), _arr_values.at(1), _arr_values.at(2)) {}
s_vec_3::s_vec_3 (const float _values[u_count]) : s_vec_3(_values[0], _values[1], _values[2]) {}
s_vec_3::s_vec_3 (const float _x, const float _y, const float _z) : s_vec_2(_x, _y), z(_z) {}
s_vec_3::s_vec_3 (const s_vec_2& _src, const float _z/* = 0.0f*/) : s_vec_3() { this->Set(_src, _z); }

s_vec_3 s_vec_3::Get_cross (const s_vec_3& _v_3) {
	return s_vec_3(this->y * _v_3.z - this->z *_v_3.y, this->z * _v_3.x - this->x *_v_3.z, this->x * _v_3.y - this->y *_v_3.x);
}

float s_vec_3::Get_dot (const s_vec_3& _v_3) const {
	return this->x * _v_3.x + this->y * _v_3.y + this->z * _v_3.z;
}

s_vec_3& s_vec_3::Invert (const float _f_scale)       { this->x /= _f_scale; this->y /= _f_scale; this->z /= _f_scale; return *this; }
s_vec_3  s_vec_3::Invert (const float _f_scale) const { return s_vec_3(this->x / _f_scale, this->y / _f_scale, this->z / _f_scale); }

bool s_vec_3::Is_unit (void) const { return this->Length() <= 1.0f; }
/* https://en.cppreference.com/w/c/numeric/math/sqrt.html ; */
#include <errno.h>
float s_vec_3::Length (void) const {
	errno = 0;
	const float f_len = ::sqrtf(this->Sum(2));
	if (errno) {}
	return f_len;
}

s_vec_3& s_vec_3::Negate (void) {
	s_vec_2::Negate(); this->z = -this->z; return *this;
}
s_vec_3& s_vec_3::Normalize (const bool _b_bits) { // https://registry.khronos.org/OpenGL-Refpages/gl4/html/normalize.xhtml ;
	_b_bits;
	if (defs::f_epsilon > this->Length())
		return *this;
	const float f_inv_len = (_b_bits ? ::_rsqrt(this->Sum(2)) : 1.0f/::sqrtf(this->Sum(2)));
	this->x *=  f_inv_len;
	this->y *=  f_inv_len;
	this->z *=  f_inv_len; return *this;
}

s_vec_3& s_vec_3::Round (const float _threshold/* = defs::f_epsilon*/) {
	_threshold;
	const float f_delta = ::abs(_threshold);
	if (::abs(this->x) < f_delta) this->x = 0.0f; else if (0.0f > this->x) this->x = ::std::floor(this->x); else this->x = ::std::ceil(this->x);
	if (::abs(this->y) < f_delta) this->y = 0.0f; else if (0.0f > this->y) this->y = ::std::floor(this->y); else this->y = ::std::ceil(this->y);
	if (::abs(this->z) < f_delta) this->z = 0.0f; else if (0.0f > this->z) this->z = ::std::floor(this->z); else this->z = ::std::ceil(this->z);

	return *this;
}

s_vec_3& s_vec_3::Set (const float _values[u_count]) {
	if (nullptr == _values) {
		return *this;
	}
	try {
		this->Set(_values[0], _values[1], _values[2]);
	} catch (...) { __trace_err_ex_2(CError(__CLASS__, __METHOD__, __e_fail)); }

	return *this;
}
s_vec_3& s_vec_3::Set (const float _x, const float _y, const float _z) {
	s_vec_2::Set(_x, _y);
	this->z = _z; return *this;
}
s_vec_3& s_vec_3::Set (const s_vec_2& _src, const float _z/* = 0.0f*/) { return this->Set(_src.x, _src.y, _z); }

float    s_vec_3::Sum (const uint32_t _u_exp/* = 1*/) const { return s_vec_2::Sum(_u_exp) + ::_pow_n(_u_exp, this->z); }

CString  s_vec_3::To_str (_pc_sz _p_format) const {
	static _pc_sz pc_sz_pat = _T("%s; z =%s");
	CString cs_out; cs_out.Format(pc_sz_pat, (_pc_sz) s_vec_2::To_str(_p_format), _format(this->z, _p_format));
	return  cs_out;
}

s_vec_3  s_vec_3::operator - (void) const { return s_vec_3(-(s_vec_2&)*this, -this->z); }
s_vec_3& s_vec_3::operator - (void) { -(s_vec_2&)*this; this->z *= -1.0f; return *this; }

s_vec_3& s_vec_3::operator = (const s_vec_3& _src) { (s_vec_2&)*this = (const s_vec_2&)_src; this->z = _src.z; return *this; }
s_vec_3& s_vec_3::operator +=(const s_vec_3& _v_3) {
	(s_vec_2&)*this += (const s_vec_2&)_v_3; this->z += _v_3.z; return *this;
}
s_vec_3& s_vec_3::operator*= (const s_vec_3& _multiplier) {
	_multiplier;
	(*this)() *= (_multiplier)(); this->z *= _multiplier.z; return *this;
}

s_vec_3& s_vec_3::operator /=(const float _f_scale)       { return this->Invert(_f_scale); }     
s_vec_3  s_vec_3::operator / (const float _f_scale) const { return this->Invert(_f_scale); } // double times of copying the result; not good :(

s_vec_3  s_vec_3::operator + (const s_vec_3& _v_3 ) const {
	return s_vec_3(this->x + _v_3.x, this->y + _v_3.y, this->z + _v_3.z);
}

s_vec_3& s_vec_3::operator +=(const float _f_scalar) { (s_vec_2&)*this += _f_scalar; this->z += _f_scalar; return *this; }
s_vec_3& s_vec_3::operator -=(const float _f_scalar) { (s_vec_2&)*this -= _f_scalar; this->z -= _f_scalar; return *this; }

const
s_vec_2& s_vec_3::operator ()(void) const { return (s_vec_2&)*this; }
s_vec_2& s_vec_3::operator ()(void)       { return (s_vec_2&)*this; }

bool s_vec_3::operator == (const s_vec_3& _rhv) const { return (*this)() == _rhv() && this->z == _rhv.z; }

#pragma endregion