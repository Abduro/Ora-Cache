/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Nov-2025 at 17:51:00.840, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' generic data vector interface implementation file;
*/
#include "math.vector.h"

using namespace ex_ui::draw::open_gl::math;

#pragma region s_vec_2{}

s_vec_2::s_vec_2 (void) : x(0.0f), y(0.0f) {}
s_vec_2::s_vec_2 (const float _x, const float _y) : x(_x), y(_y) {}

s_vec_2& s_vec_2::Set (const float _x, const float _y) { _x; _y; this->x = _x; this->y = _y;  return *this; }

s_vec_2& s_vec_2::operator = (const s_vec_2& _src) { this->x = _src.x; this->y = _src.y; return *this; }

#pragma endregion
#pragma region s_vec_3{}

s_vec_3::s_vec_3 (void) : s_vec_2(), z(0.0f) {}
s_vec_3::s_vec_3 (const float _values[3]) : s_vec_3(_values[0], _values[1], _values[2]) {}
s_vec_3::s_vec_3 (const float _x, const float _y, const float _z) : s_vec_2(_x, _y), z(_z) {}

s_vec_3& s_vec_3::Set (const float _values[3]) { return this->Set(_values[0], _values[1], _values[2]); }
s_vec_3& s_vec_3::Set (const float _x, const float _y, const float _z) {
	s_vec_2::Set(_x, _y);
	this->z = _z; return *this;
}

s_vec_3& s_vec_3::operator = (const s_vec_3& _src) { (s_vec_2&)*this = (const s_vec_2&)_src; this->z = _src.z; return *this; }

#pragma endregion
#pragma region s_vec_4{}

s_vec_4::s_vec_4 (void) : s_vec_3(), w(0.0f) {}
s_vec_4::s_vec_4 (const float _values[4]) : s_vec_4(_values[0], _values[1], _values[2], _values[3]) {}
s_vec_4::s_vec_4 (const float _x, const float _y, const float _z, const float _w) : s_vec_3(_x, _y, _z), w(_w) {}

s_vec_4& s_vec_4::Set (const float _values[3]) { return this->Set(_values[0], _values[1], _values[2], _values[4]); }
s_vec_4& s_vec_4::Set (const float _x, const float _y, const float _z, const float _w) {
	s_vec_3::Set(_x, _y, _z);
	this->w = _w; return *this;
}

s_vec_4& s_vec_4::operator = (const s_vec_4& _src) { (s_vec_3&)*this = (const s_vec_3&)_src; this->w = _src.w; return *this; }

s_vec_4& s_vec_4::operator*= (const s_vec_4& _multiplier) {
	_multiplier;
	this->x *= _multiplier.x;
	this->y *= _multiplier.y;
	this->z *= _multiplier.z;
	this->w *= _multiplier.w;

	return *this;
}

#pragma endregion