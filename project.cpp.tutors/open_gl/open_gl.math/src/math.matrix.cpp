/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Dec-2025 at 18:25:16.417, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' generic data matrix interface implementation file;
*/
#include "math.matrix.h"
#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl::math;

namespace ex_ui { namespace draw { namespace open_gl { namespace math { namespace _impl {
	float $na = 0.0f;
	#define __pi 3.141593f
	const float  deg_2_rad = __pi / 180.0f;
	const float  rad_2_deg = 180.0f / __pi;
	const float  f_epsilon = 0.00001f;
}}}}}

#pragma region cls::c_mat2x2{}

c_mat2x2::c_mat2x2 (void) { this->m_data.resize(c_mat2x2::u_size, 0x0f); this->m_data.reserve(c_mat2x2::u_size); }
c_mat2x2::c_mat2x2 (const c_mat2x2& _src) : c_mat2x2() { *this = _src; }

float& c_mat2x2::Cell (const uint32_t _u_col, const uint32_t _u_row) {
	_u_col; _u_row;
	try { return this->m_data.at(_u_col * c_mat2x2::u_rows + _u_row); }
	catch (const ::std::out_of_range&) { __trace_err_2(_T("#__out_of_range: col=%u|row=%u;\n"), _u_col, _u_row); return ::_impl::$na; }
}

c_mat2x2&  c_mat2x2::operator = (const c_mat2x2& _src) { _src; return *this; }

#pragma endregion
#pragma region cls::c_mat3x3{}

c_mat3x3::c_mat3x3 (void) { this->m_data.resize(c_mat3x3::u_size, 0x0f); this->m_data.reserve(c_mat3x3::u_size); }
c_mat3x3::c_mat3x3 (const c_mat3x3& _src) : c_mat3x3() { *this = _src; }

float& c_mat3x3::Cell (const uint32_t _u_col, const uint32_t _u_row) {
	_u_col; _u_row;
	try { return this->m_data.at(_u_col * c_mat3x3::u_rows + _u_row); }
	catch (const ::std::out_of_range&) { __trace_err_2(_T("#__out_of_range: col=%u|row=%u;\n"), _u_col, _u_row); return ::_impl::$na; }
}

c_mat3x3&  c_mat3x3::operator = (const c_mat3x3& _src) { _src; return *this; }

#pragma endregion
#pragma region cls::c_mat4x4{}

c_mat4x4::c_mat4x4 (void) : m_rows(*this), m_rotator(*this) { this->m_data.resize(c_mat4x4::u_size, 0.0f); this->m_data.reserve(c_mat4x4::u_size); }
c_mat4x4::c_mat4x4 (const c_mat4x4& _src) : c_mat4x4() { *this = _src; }

const
float& c_mat4x4::Cell (const uint32_t _u_col, const uint32_t _u_row) const {
	_u_col; _u_row;
	try { return this->m_data.at(_u_col * c_mat4x4::u_rows + _u_row); }
	catch (const ::std::out_of_range&) { __trace_err_2(_T("#__out_of_range: col=%u|row=%u;\n"), _u_col, _u_row); return ::_impl::$na; }
}

float& c_mat4x4::Cell (const uint32_t _u_col, const uint32_t _u_row) {
	_u_col; _u_row;
	try { return this->m_data.at(_u_col * c_mat4x4::u_rows + _u_row); }
	catch (const ::std::out_of_range&) { __trace_err_2(_T("#__out_of_range: col=%u|row=%u;\n"), _u_col, _u_row); return ::_impl::$na; }
}

c_mat4x4& c_mat4x4::Identity (void) {

	this->m_data.resize(c_mat4x4::u_size, 0.0f); this->m_data.reserve(c_mat4x4::u_size);

	uint32_t i_ = 0;
	try {
		for (; i_ < c_mat4x4::u_size; i_+= (c_mat4x4::u_rows + 1)) {
			this->m_data.at(i_) = 1.0f;
		}
	}
	catch ( const ::std::out_of_range&) {
		__trace_err_2(_T("#__out_of_range: _ndx=%u|size=%u;\n"), i_, c_mat4x4::u_size);
	}
	return *this;
}

using c_rotator = c_mat4x4::c_rotator;
using c_rows = c_mat4x4::c_rows;

const
c_rotator& c_mat4x4::Rotator (void) const { return this->m_rotator; }
c_rotator& c_mat4x4::Rotator (void)       { return this->m_rotator; }

const
c_rows& c_mat4x4::Rows (void) const { return this->m_rows; }
c_rows& c_mat4x4::Rows (void)       { return this->m_rows; }

c_mat4x4& c_mat4x4::Translate (const float _x, const float _y, const float _z) {
	_x; _y; _z;
	/* cols:  1st         2nd         3rd         4th
	rows: 1st 0 += 3 * x  4 += 7 * x  8 += b * x  c += f * x
	      2nd 1 += 3 * y  5 += 7 * y  9 += b * y  d += f * y
	      3rd 2 += 3 * z  6 += 7 * z  a += b * z  e += f * z
	      4th 3 == 3      7 == 7      b == b      f == f
	*/
	const float* w_coords[] = {&_x, &_y, &_z}; // input world coordinates;

	for (uint32_t u_col = 0; u_col < c_mat4x4::u_cols; u_col++) {
		for (uint32_t u_row = 0; u_row < c_mat4x4::u_rows - 1; u_row++) { // the last cell of the column 'w' remains the same (u_rows - 1);

			float& f_val = this->Cell (u_col, u_row);
			f_val += this->Cell (u_col, c_mat4x4::u_rows - 1) * *w_coords[u_row];
		}
	}

	return *this;
}

c_mat4x4& c_mat4x4::Translate (const vec_3& _v_3) { return this->Translate(_v_3.x, _v_3.y, _v_3.z); }

c_mat4x4& c_mat4x4::operator = (const c_mat4x4& _src) { _src; return *this; }

#pragma endregion
#pragma region cls::c_mat4x4::c_rotator{}

c_mat4x4::c_rotator::c_rotator (c_mat4x4& _mat_ref) : m_mat_ref(_mat_ref) {}

c_mat4x4& c_mat4x4::c_rotator::Do (const float _f_angle, const float _x, const float _y, const float _z) {
	_f_angle; _x; _y; _z;
	const float cos_ = ::cosf(_f_angle * ::_impl::deg_2_rad);
	const float sin_ = ::sinf(_f_angle * ::_impl::deg_2_rad); const float cos_1 = 1.0f - cos_;
	
	// copies original data before making the calculations;
	struct {
		float _x; // indices: 0|4|8|c;
		float _y; // indices: 1|5|9|d;
		float _z; // indices: 2|6|a|e;
	}
	col_0 {this->m_mat_ref.Cell(0, 0), this->m_mat_ref.Cell(0, 1), this->m_mat_ref.Cell(0, 2)}, // col_#_1: x, y, z; w:3 excluded;
	col_1 {this->m_mat_ref.Cell(1, 0), this->m_mat_ref.Cell(1, 1), this->m_mat_ref.Cell(1, 2)}, // col_#_2: x, y, z; w:7 excluded;
	col_2 {this->m_mat_ref.Cell(2, 0), this->m_mat_ref.Cell(2, 1), this->m_mat_ref.Cell(2, 2)}, // col_#_3: x, y, z; w:b excluded;
	col_3 {this->m_mat_ref.Cell(3, 0), this->m_mat_ref.Cell(3, 1), this->m_mat_ref.Cell(3, 2)}; // col_#_4: x, y, z; w:f excluded;

	// build rotation matrix [3x3];
	/* cols:     1st                           2nd                           3rd                      
	rows: x 1st  0 = x * x * cos_1 + 0 + cos_  4 = x * y * cos_1 + z *-sin_  8 = x * z * cos_1 + y * sin_
	      y 2nd  1 = y * x * cos_1 + z * sin_  5 = y * y * cos_1 + 0 + cos_  9 = y * z * cos_1 + x *-sin_
	      z 3rd  2 = z * x * cos_1 + y *-sin_  6 = z * y * cos_1 + x * sin_  a = z * z * cos_1 + 0 + cos_
	*/
	// col_#_1
    col_0._x = _x * _x * cos_1 + 0 + cos_; // 0 x
    col_0._y = _y * _x * cos_1 +_z * sin_; // 1 y
    col_0._z = _z * _x * cos_1 -_y * sin_; // 2 z would be: z * x * cos_1 + y *-sin_
	// col_#_2
    col_1._x = _x * _y * cos_1 -_z * sin_; // 4 x would be: x * y * cos_1 + z *-sin_
    col_1._y = _y * _y * cos_1 + 0 + cos_; // 5 y
    col_1._z = _z * _y * cos_1 +_x * sin_; // 6 z
	// col_#_3
    col_2._x = _x * _z * cos_1 +_y * sin_; // 8 x
    col_2._y = _y * _z * cos_1 -_x * sin_; // 9 y would be: y * z * cos_1 + x *-sin_
    col_2._z = _z * _z * cos_1 + 0 + cos_; // a z

	return this->m_mat_ref;
}

c_mat4x4& c_mat4x4::c_rotator::On_x (const float _f_angle) {
	_f_angle;
	const float cos_ = ::cosf(_f_angle * ::_impl::deg_2_rad);
	const float sin_ = ::sinf(_f_angle * ::_impl::deg_2_rad);
	// copies original data before making the calculations;
	struct {
		float _y; // indices: 1|5|9|d;
		float _z; // indices: 2|6|a|e;
	}
	col_0 {this->m_mat_ref.Cell(0, 1), this->m_mat_ref.Cell(0, 2)}, // col_#_1: y, z; x:0 & w:3 excluded;
	col_1 {this->m_mat_ref.Cell(1, 1), this->m_mat_ref.Cell(1, 2)}, // col_#_2: y, z; x:4 & w:7 excluded;
	col_2 {this->m_mat_ref.Cell(2, 1), this->m_mat_ref.Cell(2, 2)}, // col_#_3: y, z; x:8 & w:b excluded;
	col_3 {this->m_mat_ref.Cell(3, 1), this->m_mat_ref.Cell(3, 2)}; // col_#_4: y, z; x:c & w:f excluded;

	/* cols:     1st                        2nd                        3rd                        4th
	x-axis: 1st  0                          4                          8                          c :excluded;
	rows  : 2nd  1 = 1' * cos_ + 2' *-sin_  5 = 5' * cos_ + 6' *-sin_  9 = 9' * cos_ + a' *-sin_  d = d' * cos_ + e' *-sin_
	        3rd  2 = 1' * sin_ + 2' * cos_  6 = 5' * sin_ + 6' * cos_  a = 9' * sin_ + a' * cos_  e = d' * sin_ + e' * cos_
	w-dir : 4th  3                          7                          b                          f :excluded;
	*/
	// calculus: formula (applied to indices of this matrix data vector);
	// col_#_1
	this->m_mat_ref.Cell(0, 1) = col_0._y * cos_ + col_0._z *-sin_; // #this = #this * cos + #next *-sin ; where: cos is the math.cos(rotate angle in degrees);
	this->m_mat_ref.Cell(0, 2) = col_0._y * sin_ + col_0._z * cos_; // #this = #prev * sin + #this * cos ;        sin is the math.sin(rotate angle in degrees);
	// col_#_2
	this->m_mat_ref.Cell(1, 1) = col_1._y * cos_ + col_1._z *-sin_;
	this->m_mat_ref.Cell(1, 2) = col_1._y * sin_ + col_1._z * cos_;
	// col_#_3
	this->m_mat_ref.Cell(2, 1) = col_2._y * cos_ + col_2._z *-sin_;
	this->m_mat_ref.Cell(2, 2) = col_2._y * sin_ + col_2._z * cos_;
	// col_#_4
	this->m_mat_ref.Cell(3, 1) = col_3._y * cos_ + col_3._z *-sin_;
	this->m_mat_ref.Cell(3, 2) = col_3._y * sin_ + col_3._z * cos_;

	return this->m_mat_ref;
}

c_mat4x4& c_mat4x4::c_rotator::On_y (const float _f_angle) {
	_f_angle;
	const float cos_ = ::cosf(_f_angle * ::_impl::deg_2_rad);
	const float sin_ = ::sinf(_f_angle * ::_impl::deg_2_rad);
	// copies original data before making the calculations;
	struct {
		float _x; // indices: 0|4|8|c;
		float _z; // indices: 2|6|a|e;
	}
	col_0 {this->m_mat_ref.Cell(0, 0), this->m_mat_ref.Cell(0, 2)}, // col_#_1: x, z; y:1 & w:3 excluded;
	col_1 {this->m_mat_ref.Cell(1, 0), this->m_mat_ref.Cell(1, 2)}, // col_#_2: x, z; y:5 & w:7 excluded;
	col_2 {this->m_mat_ref.Cell(2, 0), this->m_mat_ref.Cell(2, 2)}, // col_#_3: x, z; y:9 & w:b excluded;
	col_3 {this->m_mat_ref.Cell(3, 0), this->m_mat_ref.Cell(3, 2)}; // col_#_4: x, z; y:d & w:f excluded;

	/* cols:     1st                        2nd                        3rd                        4th
	rows  : 1st  0 = 0' * cos + 2' * sin_  4 = 4' * cos_ + 6' * sin_  8 = 8' * cos_ + a' * sin_  c = c' * cos_ + e' * sin_
	y-axis: 2rd  1                          5                          9                          d :excluded;
	        3nd  2 = 0' *-sin_ + 2' * cos_  6 = 4' *-sin_ + 6' * cos_  a = 8' *-sin_ + a' * cos_  e = c' *-sin_ + e' * cos_
	w-dir : 4th  3                          7                          b                          f :excluded;
	*/
	// calculus: formula (applied to indices of this matrix data vector);
	// col_#_1
	this->m_mat_ref.Cell(0, 0) = col_0._x * cos_ + col_0._z * sin_; // #this = #this * cos  + #after_next * sin ; where: cos is the math.cos(rotate angle in degrees);
	this->m_mat_ref.Cell(0, 2) = col_0._x *-sin_ + col_0._z * cos_; // #this = #before_prev *-sin + #this * cos ;        sin is the math.sin(rotate angle in degrees);
	// col_#_2
	this->m_mat_ref.Cell(1, 0) = col_1._x * cos_ + col_1._z * sin_;
	this->m_mat_ref.Cell(1, 2) = col_1._x *-sin_ + col_1._z * cos_;
	// col_#_3
	this->m_mat_ref.Cell(2, 0) = col_2._x * cos_ + col_2._z * sin_;
	this->m_mat_ref.Cell(2, 2) = col_2._x *-sin_ + col_2._z * cos_;
	// col_#_4
	this->m_mat_ref.Cell(3, 0) = col_3._x * cos_ + col_3._z * sin_;
	this->m_mat_ref.Cell(3, 2) = col_3._x *-sin_ + col_3._z * cos_;

	return this->m_mat_ref;
}

c_mat4x4& c_mat4x4::c_rotator::On_z (const float _f_angle) {
	_f_angle;
	const float cos_ = ::cosf(_f_angle * ::_impl::deg_2_rad);
	const float sin_ = ::sinf(_f_angle * ::_impl::deg_2_rad);
	// copies original data before making the calculations;
	struct {
		float _x; // indices: 0|4|8|c;
		float _y; // indices: 1|5|9|d;
	}
	col_0 {this->m_mat_ref.Cell(0, 0), this->m_mat_ref.Cell(0, 1)}, // col_#_1: x, y; z:2 & w:3 excluded;
	col_1 {this->m_mat_ref.Cell(1, 0), this->m_mat_ref.Cell(1, 1)}, // col_#_2: x, y; z:6 & w:7 excluded;
	col_2 {this->m_mat_ref.Cell(2, 0), this->m_mat_ref.Cell(2, 1)}, // col_#_3: x, y; z:a & w:b excluded;
	col_3 {this->m_mat_ref.Cell(3, 0), this->m_mat_ref.Cell(3, 1)}; // col_#_4: x, y; z:e & w:f excluded;

	/* cols:     1st                         2nd                         3rd                         4th
	rows:   1st  0 = 0' * cos_ + 1' * -sin_  4 = 4' * cos_ + 5' * -sin_  8 = 8' * cos_ + 9' * -sin_  c = c' * cos_ + d' * -sin_
	        2nd  1 = 0' * sin_ + 1' *  cos_  5 = 4' * sin_ + 5' *  cos_  9 = 8' * sin_ + 9' *  cos_  d = c' * sin_ + d' *  cos_
	z-axis: 3rd  2                           6                           a                           e :excluded;
	w-dir : 4th  3                           7                           b                           f :excluded;
	*/
	// calculus: formula (applied to indices of this matrix data vector);
	// col_#_1
	this->m_mat_ref.Cell(0, 0) = col_0._x * cos_ + col_0._y *-sin_; // #this = #this * cos + #next * -sin ; where: cos is the math.cos(rotate angle in degrees);
	this->m_mat_ref.Cell(0, 1) = col_0._x * sin_ + col_0._y * cos_; // #this = #prev * sin + #this *  cos ;        sin is the math.sin(rotate angle in degrees);
	// col_#_2
	this->m_mat_ref.Cell(1, 0) = col_1._x * cos_ + col_1._y *-sin_;
	this->m_mat_ref.Cell(1, 1) = col_1._x * sin_ + col_1._y * cos_;
	// col_#_3
	this->m_mat_ref.Cell(2, 0) = col_2._x * cos_ + col_2._y *-sin_;
	this->m_mat_ref.Cell(2, 1) = col_2._x * sin_ + col_2._y * cos_;
	// col_#_4
	this->m_mat_ref.Cell(3, 0) = col_3._x * cos_ + col_3._y *-sin_;
	this->m_mat_ref.Cell(3, 1) = col_3._x * sin_ + col_3._y * cos_;
	return this->m_mat_ref;
}

#pragma endregion
#pragma region cls::c_mat4x4::c_rows{}

c_mat4x4::c_rows::c_rows (c_mat4x4& _mat_ref) : m_mat_ref(_mat_ref) {}

void c_mat4x4::c_rows::Set (const uint32_t _n_row, const float _f_val) {
	_n_row; _f_val;
	if (_n_row > c_mat4x4::u_rows - 1)
		return;
	for (uint32_t u_col = 0; u_col < c_mat4x4::u_cols; u_col++) {
		this->m_mat_ref.Cell(u_col, _n_row) = _f_val;
	}
}

#pragma endregion