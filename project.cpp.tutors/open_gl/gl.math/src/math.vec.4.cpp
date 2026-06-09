/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Mar-2026 at 23:41:31.630, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' float data vector 4 interface implementation file;
*/
#include "math.vec.4.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl::math;

#pragma region s_vec_4{}

s_vec_4::s_vec_4 (void) : s_vec_3(), w(0.0f) {}
s_vec_4::s_vec_4 (const float _values[u_count]) : s_vec_4(_values[0], _values[1], _values[2], _values[3]) {}
s_vec_4::s_vec_4 (const float _x, const float _y, const float _z, const float _w) : s_vec_3(_x, _y, _z), w(_w) {}
s_vec_4::s_vec_4 (const s_vec_3& _src, const float _w) : s_vec_4() { this->Set(_src, _w); }

s_vec_4 s_vec_4::Get_cross (const s_vec_3& _v_3) { return s_vec_4((*this)().Get_cross(_v_3), this->w); }
s_vec_4 s_vec_4::Get_cross (const s_vec_4& _v_4) { return this->Get_cross(_v_4()); }

float s_vec_4::Get_dot (const s_vec_3& _v_3) const { return (*this)().Get_dot(_v_3); }
float s_vec_4::Get_dot (const s_vec_4& _v_4) const { return this->Get_dot(_v_4()); }

s_vec_4& s_vec_4::Invert (const float _f_scale)       { this->x /= _f_scale; this->y /= _f_scale; this->z /= _f_scale; this->w /= _f_scale; return *this; }      
s_vec_4  s_vec_4::Invert (const float _f_scale) const { return s_vec_4(this->x / _f_scale, this->y / _f_scale, this->z / _f_scale, this->w / _f_scale); }

bool  s_vec_4::Is_unit (void) const { return this->Length() <= 1.0f; }

float s_vec_4::Length (void) const {
	errno = 0;
	const float f_len = ::sqrtf(this->Sum(2));
	if (errno) {}
	return f_len;
}

s_vec_4& s_vec_4::Negate (void) {
	s_vec_3::Negate(); this->w = -this->w; return *this;
}
s_vec_4& s_vec_4::Normalize (const bool _b_fast) {
	_b_fast;
	if (defs::f_epsilon > this->Length())
		return *this;
	const float f_inv_len = (_b_fast ? ::_rsqrt(this->Sum(2)) : 1.0f/::sqrtf(this->Sum(2)));
	this->x *=  f_inv_len;
	this->y *=  f_inv_len;
	this->z *=  f_inv_len;
	this->w *=  f_inv_len; return *this;
}

s_vec_4& s_vec_4::Set (const float _values[u_count]) { return this->Set(_values[0], _values[1], _values[2], _values[4]); }
s_vec_4& s_vec_4::Set (const float _x, const float _y, const float _z, const float _w) {
	s_vec_3::Set(_x, _y, _z);
	this->w = _w; return *this;
}
s_vec_4& s_vec_4::Set (const s_vec_3& _src, const float _w/* = 0.0f*/) { return this->Set(_src.x, _src.y, _src.z, _w); }

float    s_vec_4::Sum (const uint32_t _u_exp/* = 1*/) const { return s_vec_3::Sum(_u_exp) + ::_pow_n(_u_exp, this->w); }

CString  s_vec_4::To_str (_pc_sz _p_format) const {
	static _pc_sz pc_sz_pat = _T("%s; w =%s");
	CString cs_out; cs_out.Format(pc_sz_pat, (_pc_sz) s_vec_3::To_str(_p_format), _format(this->w, _p_format));
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

s_vec_4 operator * (const s_vec_4& _left, const s_vec_4& _right) {
	return s_vec_4(_left.x * _right.x, _left.y * _right.y, _left.z * _right.z, _left.w * _right.w);
}

}}}}