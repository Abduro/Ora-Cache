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
	const float  deg_2_rad = __pi / 180.0f /*0.017453300f*/;
	const float  rad_2_deg = 180.0f / __pi;
	const float  f_epsilon = 0.00001f;
}}}}}

#pragma region cls::c_mat2x2{}

c_mat2x2::c_mat2x2 (void) { this->m_data.resize(c_mat2x2::u_size, 0x0f); this->m_data.reserve(c_mat2x2::u_size); }
c_mat2x2::c_mat2x2 (const c_mat2x2& _src) : c_mat2x2() { *this = _src; }
c_mat2x2::c_mat2x2 (c_mat2x2&& _victim) : c_mat2x2() { *this = _victim; }

const
float& c_mat2x2::Cell (const uint32_t _u_col, const uint32_t _u_row) const {
	_u_col; _u_row;
	try { return this->m_data.at(_u_col * c_mat2x2::u_rows + _u_row); }
	catch (const ::std::out_of_range&) { __trace_err_2(_T("#__out_of_range: col=%u|row=%u;\n"), _u_col, _u_row); return ::_impl::$na; }
}
float& c_mat2x2::Cell (const uint32_t _u_col, const uint32_t _u_row) {
	_u_col; _u_row;
	try { return this->m_data.at(_u_col * c_mat2x2::u_rows + _u_row); }
	catch (const ::std::out_of_range&) { __trace_err_2(_T("#__out_of_range: col=%u|row=%u;\n"), _u_col, _u_row); return ::_impl::$na; }
}

float  c_mat2x2::Get  (const uint32_t _u_col, const uint32_t _u_row) const { return this->Cell (_u_col, _u_row); }

c_mat2x2&  c_mat2x2::operator = (const c_mat2x2& _src) { this->m_data = _src.m_data; return *this; }
c_mat2x2&  c_mat2x2::operator = (c_mat2x2&& _victim) { this->m_data.swap(_victim.m_data); return *this; }

#pragma endregion
#pragma region cls::c_mat3x3::c_cols{}

c_mat3x3::c_cols::c_cols (c_mat3x3& _mat_ref) : m_mat_ref(_mat_ref) {}

c_mat3x3& c_mat3x3::c_cols::Set (const float _col_0[u_count], const float _col_1[u_count], const float _col_2[u_count]) {
	this->Set(0, _col_0);
	this->Set(1, _col_1);
	this->Set(2, _col_2);
	return this->m_mat_ref; 
}
c_mat3x3& c_mat3x3::c_cols::Set (const uint32_t _u_col, const float _xyz[u_count]) { return this->Set(_u_col, _xyz[0], _xyz[1], _xyz[2]); }
c_mat3x3& c_mat3x3::c_cols::Set (const uint32_t _u_col, const float _x, const float _y, const float _z) {
	_u_col; _x; _y; _z;
	if (_u_col > c_cols::u_count - 1) { // just returns the reference to unchanged matrix;
		__trace_err_2(_T("#__e_inv_ndx: the col index (%u) is out of acceptable range;\n"), _u_col);
		return this->m_mat_ref;
	}
	(*this)()(_u_col, 0) = _x;
	(*this)()(_u_col, 1) = _y;
	(*this)()(_u_col, 2) = _z;

	return this->m_mat_ref;
}

c_mat3x3& c_mat3x3::c_cols::Set (const uint32_t _u_col, const vec_3& _xyz) { return this->Set(_u_col, _xyz.x, _xyz.y, _xyz.z); }
c_mat3x3& c_mat3x3::c_cols::Set (const vec_3&   _col_0, const vec_3& _col_1, const vec_3& _col_2) {
	this->Set(0, _col_0);
	this->Set(1, _col_1);
	this->Set(2, _col_2); return this->m_mat_ref;
}

const
c_mat3x3& c_mat3x3::c_cols::operator ()(void) const { return this->m_mat_ref; }
c_mat3x3& c_mat3x3::c_cols::operator ()(void)       { return this->m_mat_ref; }

#pragma endregion
#pragma region cls::c_mat3x3{}

c_mat3x3::c_mat3x3 (void) : m_cols(*this) { this->m_data.resize(c_mat3x3::u_size, 0.0f); this->m_data.reserve(c_mat3x3::u_size); }
c_mat3x3::c_mat3x3 (const c_mat3x3& _src) : c_mat3x3() { *this = _src; }
c_mat3x3::c_mat3x3 (c_mat3x3&& _victim) : c_mat3x3() { *this = _victim; }

const
float& c_mat3x3::Cell (const uint32_t _u_col, const uint32_t _u_row) const {
	_u_col; _u_row;
	try { return this->m_data.at(_u_col * c_mat3x3::u_rows + _u_row); }
	catch (const ::std::out_of_range&) { __trace_err_2(_T("#__out_of_range: col=%u|row=%u;\n"), _u_col, _u_row); return ::_impl::$na; }
}
float& c_mat3x3::Cell (const uint32_t _u_col, const uint32_t _u_row) {
	_u_col; _u_row;
	try { return this->m_data.at(_u_col * c_mat3x3::u_rows + _u_row); }
	catch (const ::std::out_of_range&) { __trace_err_2(_T("#__out_of_range: col=%u|row=%u;\n"), _u_col, _u_row); return ::_impl::$na; }
}
const
c_mat3x3::c_cols& c_mat3x3::Cols (void) const { return this->m_cols; }
c_mat3x3::c_cols& c_mat3x3::Cols (void)       { return this->m_cols; }

float c_mat3x3::Get  (const uint32_t _u_col, const uint32_t _u_row) const { return (*this)(_u_col, _u_row); }

c_mat3x3& c_mat3x3::operator = (const c_mat3x3& _src) { this->m_data = _src.m_data; return *this; }
c_mat3x3& c_mat3x3::operator = (c_mat3x3&& _victim) { this->m_data.swap(_victim.m_data); return *this; }

const
float&  c_mat3x3::operator ()(const uint32_t _u_col, const uint32_t _u_row) const { return this->Cell(_u_col, _u_row); }
float&  c_mat3x3::operator ()(const uint32_t _u_col, const uint32_t _u_row)       { return this->Cell(_u_col, _u_row); }

#pragma endregion
#pragma region cls::c_mat4x4::c_cols{}

c_mat4x4::c_cols::c_cols (c_mat4x4& _mat_ref) : m_mat_ref(_mat_ref) {}

vec_4 c_mat4x4::c_cols::Get (const uint32_t _u_col) const { return vec_4((*this)()(_u_col, 0), (*this)()(_u_col, 1), (*this)()(_u_col, 2), (*this)()(_u_col, 3)); }

c_mat4x4& c_mat4x4::c_cols::Set (const float _col_0[u_count], const float _col_1[u_count], const float _col_2[u_count], const float _col_3[u_count]) {
	this->Set(0, _col_0);
	this->Set(1, _col_1);
	this->Set(2, _col_2);
	this->Set(3, _col_3);
	return this->m_mat_ref;
}
c_mat4x4& c_mat4x4::c_cols::Set (const uint32_t _u_col, const float _xyzw[u_count]) { return this->Set(_u_col, _xyzw[0], _xyzw[1], _xyzw[2], _xyzw[3]); }
c_mat4x4& c_mat4x4::c_cols::Set (const uint32_t _u_col, const float _x, const float _y, const float _z, const float _w) {
	_u_col; _x; _y; _z; _w;
	if (_u_col > c_cols::u_count - 1) { // just returns the reference to unchanged matrix;
		__trace_err_2(_T("#__e_inv_ndx: the col index (%u) is out of acceptable range;\n"), _u_col);
		return this->m_mat_ref;
	}
	(*this)()(_u_col, 0) = _x;
	(*this)()(_u_col, 1) = _y;
	(*this)()(_u_col, 2) = _z;
	(*this)()(_u_col, 3) = _w;

	return this->m_mat_ref;
}

c_mat4x4& c_mat4x4::c_cols::Set (const uint32_t _u_col, const vec_4& _xyzw) { return this->Set(_u_col, _xyzw.x, _xyzw.y, _xyzw.z, _xyzw.w); }
c_mat4x4& c_mat4x4::c_cols::Set (const vec_4&   _col_0, const vec_4& _col_1, const vec_4& _col_2, const vec_4& _col_3) {
	this->Set(0, _col_0);
	this->Set(1, _col_1);
	this->Set(2, _col_2);
	this->Set(3, _col_3); return this->m_mat_ref;
}

const
c_mat4x4& c_mat4x4::c_cols::operator ()(void) const { return this->m_mat_ref; }
c_mat4x4& c_mat4x4::c_cols::operator ()(void)       { return this->m_mat_ref; }

#pragma endregion
#pragma region cls::c_mat4x4{}

c_mat4x4::c_mat4x4 (void) : m_cols(*this), m_rows(*this) { this->m_data.resize(c_mat4x4::u_size, 0.0f); this->m_data.reserve(c_mat4x4::u_size); }
c_mat4x4::c_mat4x4 (const c_mat4x4& _src) : c_mat4x4() { *this = _src; }
c_mat4x4::c_mat4x4 (c_mat4x4&& _victim) : c_mat4x4() { *this = _victim; }

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

const
c_mat4x4::c_cols& c_mat4x4::Cols (void) const { return this->m_cols; }
c_mat4x4::c_cols& c_mat4x4::Cols (void)       { return this->m_cols; }

float c_mat4x4::Get (const uint32_t _u_col, const uint32_t _u_row) const { return (*this)(_u_col, _u_row); }

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

const
c_mat4x4::c_rows& c_mat4x4::Rows (void) const { return this->m_rows; }
c_mat4x4::c_rows& c_mat4x4::Rows (void)       { return this->m_rows; }

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
			f_val += this->Get (u_col, c_mat4x4::u_rows - 1) * *w_coords[u_row];
		}
	}

	return *this;
}

c_mat4x4& c_mat4x4::Translate (const vec_3& _v_3) { return this->Translate(_v_3.x, _v_3.y, _v_3.z); }

c_mat4x4& c_mat4x4::operator = (const c_mat4x4& _src) { this->m_data = _src.m_data; return *this; }
c_mat4x4& c_mat4x4::operator = (c_mat4x4&& _victim) { this->m_data.swap(_victim.m_data);  return *this;}

const
float& c_mat4x4::operator ()(const uint32_t _u_col, const uint32_t _u_row) const { return this->Cell(_u_col, _u_row); }
float& c_mat4x4::operator ()(const uint32_t _u_col, const uint32_t _u_row)       { return this->Cell(_u_col, _u_row); }

#pragma endregion
#pragma region cls::c_mat4x4::c_rows{}

c_mat4x4::c_rows::c_rows (c_mat4x4& _mat_ref) : m_mat_ref(_mat_ref) {}

vec_4 c_mat4x4::c_rows::Get (const uint32_t _n_row) const { return vec_4((*this)()(0, _n_row), (*this)()(1, _n_row), (*this)()(2, _n_row), (*this)()(3, _n_row)); }

void  c_mat4x4::c_rows::Set (const uint32_t _n_row, const float _f_val) {
	_n_row; _f_val;
	if (_n_row > c_mat4x4::u_rows - 1)
		return;
	for (uint32_t u_col = 0; u_col < c_mat4x4::u_cols; u_col++) {
		this->m_mat_ref.Cell(u_col, _n_row) = _f_val;
	}
}

const
c_mat4x4& c_mat4x4::c_rows::operator ()(void) const { return this->m_mat_ref; }
c_mat4x4& c_mat4x4::c_rows::operator ()(void)       { return this->m_mat_ref; }

#pragma endregion
#pragma region cls::c_rotate_3x3{}

c_rotate_3x3::c_rotate_3x3 (void) : c_mat3x3() {}
c_rotate_3x3::c_rotate_3x3 (const float _f_angle, const float _x, const float _y, const float _z) { (*this)(_f_angle, _x, _y, _z); }

c_mat3x3& c_rotate_3x3::Do (const float _f_angle, const float _x, const float _y, const float _z) {
	_f_angle; _x; _y; _z;
	const float cos_ = ::cosf(_f_angle * ::_impl::deg_2_rad);
	const float sin_ = ::sinf(_f_angle * ::_impl::deg_2_rad); const float cos_1 = 1.0f - cos_;

	// build rotation matrix [3x3];
	/* cols:     1st                           2nd                           3rd                      
	rows: x 1st  0 = x * x * cos_1 + 0 + cos_  4 = x * y * cos_1 + z *-sin_  8 = x * z * cos_1 + y * sin_
	      y 2nd  1 = y * x * cos_1 + z * sin_  5 = y * y * cos_1 + 0 + cos_  9 = y * z * cos_1 + x *-sin_
	      z 3rd  2 = z * x * cos_1 + y *-sin_  6 = z * y * cos_1 + x * sin_  a = z * z * cos_1 + 0 + cos_
	*/
	// col_#_1
    (*this)()(0, 0) = _x * _x * cos_1 + 0 + cos_; // 0 x
    (*this)()(0, 1) = _y * _x * cos_1 +_z * sin_; // 1 y
    (*this)()(0, 2) = _z * _x * cos_1 -_y * sin_; // 2 z would be: z * x * cos_1 + y *-sin_
	// col_#_2
    (*this)()(1, 0) = _x * _y * cos_1 -_z * sin_; // 4 x would be: x * y * cos_1 + z *-sin_
    (*this)()(1, 1) = _y * _y * cos_1 + 0 + cos_; // 5 y
    (*this)()(1, 2) = _z * _y * cos_1 +_x * sin_; // 6 z
	// col_#_3
    (*this)()(2, 0) = _x * _z * cos_1 +_y * sin_; // 8 x
    (*this)()(2, 1) = _y * _z * cos_1 -_x * sin_; // 9 y would be: y * z * cos_1 + x *-sin_
    (*this)()(2, 2) = _z * _z * cos_1 + 0 + cos_; // a z

	return (c_mat3x3&)*this;
}

c_mat3x3& c_rotate_3x3::Do (const float _f_angle, const vec_3& _axis) { return this->Do(_f_angle, _axis.x, _axis.y, _axis.z); }

c_mat3x3& c_rotate_3x3::operator ()(const float _f_angle, const float _x, const float _y, const float _z) { return this->Do(_f_angle, _x, _y, _z); }
const
c_mat3x3& c_rotate_3x3::operator ()(void) const { return (c_mat3x3&)*this; }
c_mat3x3& c_rotate_3x3::operator ()(void)       { return (c_mat3x3&)*this; }

#pragma endregion
#pragma region cls::c_rotate_4x4{}

c_rotate_4x4::c_rotate_4x4 (void) : c_mat4x4() {}

c_mat4x4& c_rotate_4x4::Do (const float _f_angle, const float _x, const float _y, const float _z) {
	_f_angle; _x; _y; _z;
	const float cos_ = ::cosf(_f_angle * ::_impl::deg_2_rad);
	const float sin_ = ::sinf(_f_angle * ::_impl::deg_2_rad); const float cos_1 = 1.0f - cos_;

	// copies original data before making the calculations;
	struct {
		float _x; // indices: 0|4|8|c;
		float _y; // indices: 1|5|9|d;
		float _z; // indices: 2|6|a|e;
	}
	col_0 {(*this)()(0, 0), (*this)()(0, 1), (*this)()(0, 2)}, // col_#_1: x, y, z; w:3 excluded;
	col_1 {(*this)()(1, 0), (*this)()(1, 1), (*this)()(1, 2)}, // col_#_2: x, y, z; w:7 excluded;
	col_2 {(*this)()(2, 0), (*this)()(2, 1), (*this)()(2, 2)}, // col_#_3: x, y, z; w:b excluded;
	col_3 {(*this)()(3, 0), (*this)()(3, 1), (*this)()(3, 2)}; // col_#_4: x, y, z; w:f excluded;

	c_rotate_3x3 rot(_f_angle, _x, _y, _z);

	// multiplies view matrix by rotation matrix;
	/* cols:     1st                              2nd                              3rd                              4th
	rows: x 1st  0 = r0 * 0' + r4 * 1' + r8 * 2'  4 = r0 * 4' + r4 * 5' + r8 * 6'  8 = r0 * 8' + r4 * 9' + r8 * a'  c = r0 * c' + r4 * d' + r8 * e'
	      y 2nd  1 = r1 * 0' + r5 * 1' + r9 * 2'  5 = r1 * 4' + r5 * 5' + r9 * 6'  9 = r1 * 8' + r5 * 9' + r9 * a'  d = r1 * c' + r5 * d' + r9 * e'
	      z 3rd  2 = r2 * 0' + r6 * 1' + ra * 2'  6 = r2 * 4' + r6 * 5' + ra * 6'  a = r2 * 8' + r6 * 9' + ra * a'  e = r2 * c' + r6 * d' + ra * e'
	      w : excluded;
	*/
	// col_#_1
    (*this)()(0, 0) = rot()(0, 0) * col_0._x + rot()(1, 0) * col_0._y + rot()(2, 0) * col_0._z;  // 0 = 1st row of rotate matrix [0|4|8] * 1st col of the view matrix [0|1|2];
    (*this)()(0, 1) = rot()(0, 1) * col_0._x + rot()(1, 1) * col_0._y + rot()(2, 1) * col_0._z;  // 1 = 2nd row of rotate matrix [1|5|9] * 1st col of the view matrix [0|1|2];
    (*this)()(0, 2) = rot()(0, 2) * col_0._x + rot()(1, 2) * col_0._y + rot()(2, 2) * col_0._z;  // 2 = 3rd row of rotate matrix [2|6|a] * 1st col of the view matrix [0|1|2];
	// col_#_2
    (*this)()(1, 0) = rot()(0, 0) * col_1._x + rot()(1, 0) * col_1._y + rot()(2, 0) * col_1._z;  // 4 = 1st row of rotate matrix [0|4|8] * 2nd col of the view matrix [4|5|6];
    (*this)()(1, 1) = rot()(0, 1) * col_1._x + rot()(1, 1) * col_1._y + rot()(2, 1) * col_1._z;  // 5 = 2nd row of rotate matrix [1|5|9] * 2nd col of the view matrix [4|5|6];
    (*this)()(1, 2) = rot()(0, 2) * col_1._x + rot()(1, 2) * col_1._y + rot()(2, 2) * col_1._z;  // 6 = 3rd row of rotate matrix [2|6|a] * 2nd col of the view matrix [4|5|6];
	// col_#_3
    (*this)()(2, 0) = rot()(0, 0) * col_2._x + rot()(1, 0) * col_2._y + rot()(2, 0) * col_2._z;  // 8 = 1st row of rotate matrix [0|4|8] * 3rd col of the view matrix [8|9|a];
    (*this)()(2, 1) = rot()(0, 1) * col_2._x + rot()(1, 1) * col_2._y + rot()(2, 1) * col_2._z;  // 9 = 2nd row of rotate matrix [1|5|9] * 3rd col of the view matrix [8|9|a];
    (*this)()(2, 2) = rot()(0, 2) * col_2._x + rot()(1, 2) * col_2._y + rot()(2, 2) * col_2._z;  // a = 3rd row of rotate matrix [2|6|a] * 3rd col of the view matrix [8|9|a];
	// col_#_4
    (*this)()(3, 0) = rot()(0, 0) * col_3._x + rot()(1, 0) * col_3._y + rot()(2, 0) * col_3._z;  // c = 1st row of rotate matrix [0|4|8] * 3rd col of the view matrix [c|d|e];
    (*this)()(3, 1) = rot()(0, 1) * col_3._x + rot()(1, 1) * col_3._y + rot()(2, 1) * col_3._z;  // d = 2nd row of rotate matrix [1|5|9] * 3rd col of the view matrix [c|d|e];
    (*this)()(3, 2) = rot()(0, 2) * col_3._x + rot()(1, 2) * col_3._y + rot()(2, 2) * col_3._z;  // e = 3rd row of rotate matrix [2|6|a] * 3rd col of the view matrix [c|d|e];

	return (*this)();
}

c_mat4x4& c_rotate_4x4::Do (const float _f_angle, const vec_3& _coords) { return this->Do(_f_angle, _coords.x, _coords.y, _coords.z); }

c_mat4x4& c_rotate_4x4::On_x (const float _f_angle) {
	_f_angle;
	const float cos_ = ::cosf(_f_angle * ::_impl::deg_2_rad);
	const float sin_ = ::sinf(_f_angle * ::_impl::deg_2_rad);
	// copies original data before making the calculations;
	struct {
		float _y; // indices: 1|5|9|d;
		float _z; // indices: 2|6|a|e;
	}
	col_0 {(*this)()(0, 1), (*this)()(0, 2)}, // col_#_1: y, z; x:0 & w:3 excluded;
	col_1 {(*this)()(1, 1), (*this)()(1, 2)}, // col_#_2: y, z; x:4 & w:7 excluded;
	col_2 {(*this)()(2, 1), (*this)()(2, 2)}, // col_#_3: y, z; x:8 & w:b excluded;
	col_3 {(*this)()(3, 1), (*this)()(3, 2)}; // col_#_4: y, z; x:c & w:f excluded;

	/* cols:     1st                        2nd                        3rd                        4th
	x-axis: 1st  0                          4                          8                          c :excluded;
	rows  : 2nd  1 = 1' * cos_ + 2' *-sin_  5 = 5' * cos_ + 6' *-sin_  9 = 9' * cos_ + a' *-sin_  d = d' * cos_ + e' *-sin_
	        3rd  2 = 1' * sin_ + 2' * cos_  6 = 5' * sin_ + 6' * cos_  a = 9' * sin_ + a' * cos_  e = d' * sin_ + e' * cos_
	w-dir : 4th  3                          7                          b                          f :excluded;
	*/
	// calculus: formula (applied to indices of this matrix data vector);
	// col_#_1
	(*this)()(0, 1) = col_0._y * cos_ + col_0._z *-sin_; // #this = #this * cos + #next *-sin ; where: cos is the math.cos(rotate angle in degrees);
	(*this)()(0, 2) = col_0._y * sin_ + col_0._z * cos_; // #this = #prev * sin + #this * cos ;        sin is the math.sin(rotate angle in degrees);
	// col_#_2
	(*this)()(1, 1) = col_1._y * cos_ + col_1._z *-sin_;
	(*this)()(1, 2) = col_1._y * sin_ + col_1._z * cos_;
	// col_#_3
	(*this)()(2, 1) = col_2._y * cos_ + col_2._z *-sin_;
	(*this)()(2, 2) = col_2._y * sin_ + col_2._z * cos_;
	// col_#_4
	(*this)()(3, 1) = col_3._y * cos_ + col_3._z *-sin_;
	(*this)()(3, 2) = col_3._y * sin_ + col_3._z * cos_;

	return (*this)();
}

c_mat4x4& c_rotate_4x4::On_y (const float _f_angle) {
	_f_angle;
	const float cos_ = ::cosf(_f_angle * ::_impl::deg_2_rad);
	const float sin_ = ::sinf(_f_angle * ::_impl::deg_2_rad);
	// copies original data before making the calculations;
	struct {
		float _x; // indices: 0|4|8|c;
		float _z; // indices: 2|6|a|e;
	}
	col_0 {(*this)()(0, 0), (*this)()(0, 2)}, // col_#_1: x, z; y:1 & w:3 excluded;
	col_1 {(*this)()(1, 0), (*this)()(1, 2)}, // col_#_2: x, z; y:5 & w:7 excluded;
	col_2 {(*this)()(2, 0), (*this)()(2, 2)}, // col_#_3: x, z; y:9 & w:b excluded;
	col_3 {(*this)()(3, 0), (*this)()(3, 2)}; // col_#_4: x, z; y:d & w:f excluded;

	/* cols:     1st                        2nd                        3rd                        4th
	rows  : 1st  0 = 0' * cos + 2' * sin_  4 = 4' * cos_ + 6' * sin_  8 = 8' * cos_ + a' * sin_  c = c' * cos_ + e' * sin_
	y-axis: 2rd  1                          5                          9                          d :excluded;
	        3nd  2 = 0' *-sin_ + 2' * cos_  6 = 4' *-sin_ + 6' * cos_  a = 8' *-sin_ + a' * cos_  e = c' *-sin_ + e' * cos_
	w-dir : 4th  3                          7                          b                          f :excluded;
	*/
	// calculus: formula (applied to indices of this matrix data vector);
	// col_#_1
	(*this)()(0, 0) = col_0._x * cos_ + col_0._z * sin_; // #this = #this * cos  + #after_next * sin ; where: cos is the math.cos(rotate angle in degrees);
	(*this)()(0, 2) = col_0._x *-sin_ + col_0._z * cos_; // #this = #before_prev *-sin + #this * cos ;        sin is the math.sin(rotate angle in degrees);
	// col_#_2
	(*this)()(1, 0) = col_1._x * cos_ + col_1._z * sin_;
	(*this)()(1, 2) = col_1._x *-sin_ + col_1._z * cos_;
	// col_#_3
	(*this)()(2, 0) = col_2._x * cos_ + col_2._z * sin_;
	(*this)()(2, 2) = col_2._x *-sin_ + col_2._z * cos_;
	// col_#_4
	(*this)()(3, 0) = col_3._x * cos_ + col_3._z * sin_;
	(*this)()(3, 2) = col_3._x *-sin_ + col_3._z * cos_;

	return (*this)();
}

c_mat4x4& c_rotate_4x4::On_z (const float _f_angle) {
	_f_angle;
	const float cos_ = ::cosf(_f_angle * ::_impl::deg_2_rad);
	const float sin_ = ::sinf(_f_angle * ::_impl::deg_2_rad);
	// copies original data before making the calculations;
	struct {
		float _x; // indices: 0|4|8|c;
		float _y; // indices: 1|5|9|d;
	}
	col_0 {(*this)()(0, 0), (*this)()(0, 1)}, // col_#_1: x, y; z:2 & w:3 excluded;
	col_1 {(*this)()(1, 0), (*this)()(1, 1)}, // col_#_2: x, y; z:6 & w:7 excluded;
	col_2 {(*this)()(2, 0), (*this)()(2, 1)}, // col_#_3: x, y; z:a & w:b excluded;
	col_3 {(*this)()(3, 0), (*this)()(3, 1)}; // col_#_4: x, y; z:e & w:f excluded;

	/* cols:     1st                         2nd                         3rd                         4th
	rows:   1st  0 = 0' * cos_ + 1' * -sin_  4 = 4' * cos_ + 5' * -sin_  8 = 8' * cos_ + 9' * -sin_  c = c' * cos_ + d' * -sin_
	        2nd  1 = 0' * sin_ + 1' *  cos_  5 = 4' * sin_ + 5' *  cos_  9 = 8' * sin_ + 9' *  cos_  d = c' * sin_ + d' *  cos_
	z-axis: 3rd  2                           6                           a                           e :excluded;
	w-dir : 4th  3                           7                           b                           f :excluded;
	*/
	// calculus: formula (applied to indices of this matrix data vector);
	// col_#_1
	(*this)()(0, 0) = col_0._x * cos_ + col_0._y *-sin_; // #this = #this * cos + #next * -sin ; where: cos is the math.cos(rotate angle in degrees);
	(*this)()(0, 1) = col_0._x * sin_ + col_0._y * cos_; // #this = #prev * sin + #this *  cos ;        sin is the math.sin(rotate angle in degrees);
	// col_#_2
	(*this)()(1, 0) = col_1._x * cos_ + col_1._y *-sin_;
	(*this)()(1, 1) = col_1._x * sin_ + col_1._y * cos_;
	// col_#_3
	(*this)()(2, 0) = col_2._x * cos_ + col_2._y *-sin_;
	(*this)()(2, 1) = col_2._x * sin_ + col_2._y * cos_;
	// col_#_4
	(*this)()(3, 0) = col_3._x * cos_ + col_3._y *-sin_;
	(*this)()(3, 1) = col_3._x * sin_ + col_3._y * cos_;

	return (*this)();
}

const
c_mat4x4& c_rotate_4x4::operator ()(void) const { return (c_rotate_4x4&)*this; }
c_mat4x4& c_rotate_4x4::operator ()(void)       { return (c_rotate_4x4&)*this; }

#pragma endregion

c_mat4x4 operator * (const c_mat4x4& _left, const c_mat4x4& _right) {
	_left; _right;
	// no check for number of rows of the left matrix for coincident or be the same with the number of columns of the right matrix: arguments are the same type; 
	c_mat4x4 m_result;
#if (0)
	for (uint32_t u_col = 0; u_col < c_mat4x4::c_cols::u_count; u_col++) {
		for (uint32_t u_row = 0; u_row < c_mat4x4::c_rows::u_count; u_row++) {
			for (uint32_t u_ndx = 0; c_mat4x4::c_rows::u_count > u_ndx && c_mat4x4::c_cols::u_count > u_ndx; u_ndx++) {
				m_result(u_col, u_row) += (_left(u_ndx, u_row));
			}
		}
	}
#endif
	return m_result;
}