/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Nov-2025 at 17:51:00.840, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' generic data vector interface implementation file;
*/
#include "math.vector.h"

using namespace ex_ui::draw::open_gl::math;

#pragma region s_vec_2{}

s_vec_2::s_vec_2 (void) : x(0.0f), y(0.0f) {}
s_vec_2::s_vec_2 (const float _values[u_count]) : s_vec_2(_values[0], _values[1]) {}
s_vec_2::s_vec_2 (const float _x, const float _y) : x(_x), y(_y) {}

s_vec_2& s_vec_2::Invert (const float _f_scale)       { this->x /= _f_scale; this->y /= _f_scale; return *this; }      
s_vec_2  s_vec_2::Invert (const float _f_scale) const { return s_vec_2(this->x / _f_scale, this->y / _f_scale); }

float s_vec_2::Length (void) const { return ::sqrtf(this->Sum(2)); }

s_vec_2& s_vec_2::Negate (void) {
	this->x = -this->x; this->y = -this->y; return *this;
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
	this->y *= _multiplier.y;
	
	return *this;
}

s_vec_2& s_vec_2::operator += (const float _f_scalar) { this->x += _f_scalar; this->y += _f_scalar; return *this; }
s_vec_2& s_vec_2::operator -= (const float _f_scalar) { this->x -= _f_scalar; this->y -= _f_scalar; return *this; }

s_vec_2& s_vec_2::operator /= (const float _f_scale)       { return this->Invert(_f_scale); }     
s_vec_2  s_vec_2::operator /  (const float _f_scale) const { return this->Invert(_f_scale); } // double times of copying the result; not good :(

#pragma endregion
#pragma region s_vec_3{}

s_vec_3::s_vec_3 (void) : s_vec_2(), z(0.0f) {}
s_vec_3::s_vec_3 (const float _values[u_count]) : s_vec_3(_values[0], _values[1], _values[2]) {}
s_vec_3::s_vec_3 (const float _x, const float _y, const float _z) : s_vec_2(_x, _y), z(_z) {}
s_vec_3::s_vec_3 (const s_vec_2& _src, const float _z/* = 0.0f*/) : s_vec_3() { this->Set(_src, _z); }

s_vec_3 s_vec_3::Get_cross (const s_vec_3& _v_3) {
	return s_vec_3(this->y * _v_3.z - this->z *_v_3.y, this->z * _v_3.x - this->x *_v_3.z, this->x * _v_3.y - this->y *_v_3.x);
}

float s_vec_3::Get_dot (const s_vec_3& _v_3) {
	return this->x * _v_3.x + this->y * _v_3.y + this->z * _v_3.z;
}

s_vec_3& s_vec_3::Invert (const float _f_scale)       { this->x /= _f_scale; this->y /= _f_scale; this->z /= _f_scale; return *this; }      
s_vec_3  s_vec_3::Invert (const float _f_scale) const { return s_vec_3(this->x / _f_scale, this->y / _f_scale, this->z / _f_scale); }

float s_vec_3::Length (void) const { return ::sqrtf(this->x * this->x + this->y * this->y + this->z * this->z); }

s_vec_3& s_vec_3::Negate (void) {
	s_vec_2::Negate(); this->z = -this->z; return *this;
}
s_vec_3& s_vec_3::Normalize (void) {
	const float f_sum = this->x * this->x + this->y * this->y + this->z * this->z;
	const float f_inv_len = 1.0f/::sqrtf(f_sum);
	this->x *=  f_inv_len;
	this->y *=  f_inv_len;
	this->z *=  f_inv_len; return *this;
}

s_vec_3& s_vec_3::Set (const float _values[u_count]) { return this->Set(_values[0], _values[1], _values[2]); }
s_vec_3& s_vec_3::Set (const float _x, const float _y, const float _z) {
	s_vec_2::Set(_x, _y);
	this->z = _z; return *this;
}
s_vec_3& s_vec_3::Set (const s_vec_2& _src, const float _z/* = 0.0f*/) { return this->Set(_src.x, _src.y, _z); }
float    s_vec_3::Sum (const uint32_t _u_exp/* = 1*/) const { return s_vec_2::Sum(_u_exp) + ::_pow_n(_u_exp, this->z); }

CString  s_vec_3::To_str (_pc_sz _p_format) const {
	static _pc_sz pc_sz_pat = _T("%s;z=%s");
	CString cs_out; cs_out.Format(
		pc_sz_pat, (_pc_sz) s_vec_2::To_str(_p_format), TString().Float(this->z, _p_format));
	return  cs_out;
}

s_vec_3  s_vec_3::operator - (void) const { return s_vec_3(-(s_vec_2&)*this, -this->z); }
s_vec_3& s_vec_3::operator - (void) { -(s_vec_2&)*this; this->z *= -1.0f; return *this; }

s_vec_3& s_vec_3::operator = (const s_vec_3& _src) { (s_vec_2&)*this = (const s_vec_2&)_src; this->z = _src.z; return *this; }
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

#pragma endregion
#pragma region s_vec_4{}

s_vec_4::s_vec_4 (void) : s_vec_3(), w(0.0f) {}
s_vec_4::s_vec_4 (const float _values[u_count]) : s_vec_4(_values[0], _values[1], _values[2], _values[3]) {}
s_vec_4::s_vec_4 (const float _x, const float _y, const float _z, const float _w) : s_vec_3(_x, _y, _z), w(_w) {}
s_vec_4::s_vec_4 (const s_vec_3& _src, const float _w) : s_vec_4() { this->Set(_src, _w); }

s_vec_4& s_vec_4::Invert (const float _f_scale)       { this->x /= _f_scale; this->y /= _f_scale; this->z /= _f_scale; this->w /= _f_scale; return *this; }      
s_vec_4  s_vec_4::Invert (const float _f_scale) const { return s_vec_4(this->x / _f_scale, this->y / _f_scale, this->z / _f_scale, this->w / _f_scale); }

s_vec_4& s_vec_4::Set (const float _values[u_count]) { return this->Set(_values[0], _values[1], _values[2], _values[4]); }
s_vec_4& s_vec_4::Set (const float _x, const float _y, const float _z, const float _w) {
	s_vec_3::Set(_x, _y, _z);
	this->w = _w; return *this;
}
s_vec_4& s_vec_4::Set (const s_vec_3& _src, const float _w/* = 0.0f*/) { return this->Set(_src.x, _src.y, _src.z, _w); }

float    s_vec_4::Sum (const uint32_t _u_exp/* = 1*/) const { return s_vec_3::Sum(_u_exp) + ::_pow_n(_u_exp, this->w); }

CString  s_vec_4::To_str (_pc_sz _p_format) const {
	static _pc_sz pc_sz_pat = _T("%s;w=%s");
	CString cs_out; cs_out.Format(
		pc_sz_pat, (_pc_sz) s_vec_3::To_str(_p_format), TString().Float(this->w, _p_format));
	return  cs_out;
}

s_vec_4  s_vec_4::operator - (void) const { return s_vec_4(-(s_vec_3&)*this, -this->w); }
s_vec_4& s_vec_4::operator - (void) { -(s_vec_3&)*this; this->w *= -1.0f; return *this; }

s_vec_4& s_vec_4::operator  = (const s_vec_4& _src) { (s_vec_3&)*this = (const s_vec_3&)_src; this->w = _src.w; return *this; }
s_vec_4& s_vec_4::operator *= (const s_vec_4& _multiplier) { (*this)() *= (_multiplier)(); this->w *= _multiplier.w; return *this; }

s_vec_4& s_vec_4::operator += (const float _f_scalar) { (s_vec_3&)*this += _f_scalar; this->w += _f_scalar; return *this; }
s_vec_4& s_vec_4::operator -= (const float _f_scalar) { (s_vec_3&)*this -= _f_scalar; this->w -= _f_scalar; return *this; }

s_vec_4& s_vec_4::operator /= (const float _f_scale)       { return this->Invert(_f_scale); }     
s_vec_4  s_vec_4::operator /  (const float _f_scale) const { return this->Invert(_f_scale); } // double times of copying the result; not good :(

const
s_vec_3& s_vec_4::operator ()(void) const { return (s_vec_3&)*this; }
s_vec_3& s_vec_4::operator ()(void)       { return (s_vec_3&)*this; }     

#pragma endregion

namespace ex_ui { namespace draw { namespace open_gl { namespace math { // otherwise: fatal error LNK1120: 1 unresolved externals ;

bool operator == (const s_vec_3& _left, const s_vec_3& _right) {
	return (_left.x == _right.x && _left.y == _right.y && _left.z == _right.z);
}
s_vec_3 operator * (const float _lft, const s_vec_3& _v_3) {
	return s_vec_3(_lft * _v_3.x, _lft * _v_3.y, _lft * _v_3.z);
}
s_vec_4 operator * (const s_vec_4& _left, const s_vec_4& _right) {
	return s_vec_4(_left.x * _right.x, _left.y * _right.y, _left.z * _right.z, _left.w * _right.w);
}

}}}}