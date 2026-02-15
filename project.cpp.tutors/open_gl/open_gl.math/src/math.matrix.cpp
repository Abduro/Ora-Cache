/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Dec-2025 at 18:25:16.417, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' generic data matrix interface implementation file;
*/
#include "math.matrix.h"
#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl::math;

namespace ex_ui { namespace draw { namespace open_gl { namespace math { namespace _impl {
}}}}}

#pragma region cls::c_mat2x2::c_cols{}

c_mat2x2::c_cols::c_cols (c_mat2x2& _mat_ref) : m_mat_ref(_mat_ref) {}

vec_2 c_mat2x2::c_cols::Get (const uint32_t _u_col) const { return vec_2((*this)()(_u_col, 0), (*this)()(_u_col, 1)); }

c_mat2x2& c_mat2x2::c_cols::Set (const t_seq_2& _col_0, const t_seq_2& _col_1) {
	this->Set((uint32_t)0, _col_0); // error C2668: 'ex_ui::draw::open_gl::math::c_mat2x2::c_cols::Set': ambiguous call to overloaded function ;
	this->Set((uint32_t)1, _col_1);
	return this->m_mat_ref;
}
c_mat2x2& c_mat2x2::c_cols::Set (const uint32_t _u_col, const t_seq_2& _xy) { return this->Set(_u_col, _xy[0], _xy[1]); }
c_mat2x2& c_mat2x2::c_cols::Set (const uint32_t _u_col, const float _x, const float _y) {
	_u_col; _x; _y;
	if (_u_col > c_cols::u_count - 1) { // just returns the reference to unchanged matrix;
		__trace_err_2(_T("#__e_inv_ndx: the col index (%u) is out of acceptable range;\n"), _u_col);
		return this->m_mat_ref;
	}
	(*this)()(_u_col, 0) = _x;
	(*this)()(_u_col, 1) = _y;

	return this->m_mat_ref;
}

c_mat2x2& c_mat2x2::c_cols::Set (const uint32_t _u_col, const vec_2& _xy) { return this->Set(_u_col, _xy.x, _xy.y); }
c_mat2x2& c_mat2x2::c_cols::Set (const vec_2&   _col_0, const vec_2& _col_1) {
	this->Set(0, _col_0);
	this->Set(1, _col_1); return this->m_mat_ref;
}

const
c_mat2x2& c_mat2x2::c_cols::operator ()(void) const { return this->m_mat_ref; }
c_mat2x2& c_mat2x2::c_cols::operator ()(void)       { return this->m_mat_ref; }

c_mat2x2& c_mat2x2::c_cols::operator ()(const uint32_t _u_col, const t_seq_2& _xy) { return this->Set(_u_col, _xy);}
c_mat2x2& c_mat2x2::c_cols::operator ()(const uint32_t _u_col, const float _x, const float _y) { return this->Set(_u_col, _x, _y); }
c_mat2x2& c_mat2x2::c_cols::operator ()(const uint32_t _u_col, const vec_2& _xy) { return this->Set(_u_col, _xy); }

#pragma endregion
#pragma region cls::c_mat2x2::c_rows{}

c_mat2x2::c_rows::c_rows (c_mat2x2& _mat_ref) : m_mat_ref(_mat_ref) {}

vec_2 c_mat2x2::c_rows::Get (const uint32_t _n_row) const { return vec_2((*this)()(0, _n_row), (*this)()(1, _n_row)); }
void  c_mat2x2::c_rows::Set (const uint32_t _n_row, const float _f_val) {
	_n_row; _f_val;
	if (_n_row > c_mat2x2::u_rows - 1)
		return;
	for (uint32_t u_col = 0; u_col < c_mat2x2::u_cols; u_col++) {
		(*this)()(u_col, _n_row) = _f_val;
	}
}

const
c_mat2x2& c_mat2x2::c_rows::operator ()(void) const { return this->m_mat_ref; }
c_mat2x2& c_mat2x2::c_rows::operator ()(void)       { return this->m_mat_ref; }

#pragma endregion
#pragma region cls::c_mat2x2{}

c_mat2x2::c_mat2x2 (void) : m_cols(*this), m_rows(*this) { this->m_data.resize(c_mat2x2::u_size, 0x0f); this->m_data.reserve(c_mat2x2::u_size); }
c_mat2x2::c_mat2x2 (const c_mat2x2& _src) : c_mat2x2() { *this = _src; }
c_mat2x2::c_mat2x2 (const t_seq_2x2& _arr_values) : c_mat2x2() { *this << _arr_values; }
c_mat2x2::c_mat2x2 (c_mat2x2&& _victim) : c_mat2x2() { *this = _victim; }

const
float& c_mat2x2::Cell (const uint32_t _u_col, const uint32_t _u_row) const {
	_u_col; _u_row;
	try { return this->m_data.at(_u_col * c_mat2x2::u_rows + _u_row); }
	catch (const ::std::out_of_range&) { __trace_err_2(_T("#__out_of_range: col=%u|row=%u;\n"), _u_col, _u_row); return ::defs::$na; }
}
float& c_mat2x2::Cell (const uint32_t _u_col, const uint32_t _u_row) {
	_u_col; _u_row;
	try { return this->m_data.at(_u_col * c_mat2x2::u_rows + _u_row); }
	catch (const ::std::out_of_range&) { __trace_err_2(_T("#__out_of_range: col=%u|row=%u;\n"), _u_col, _u_row); return ::defs::$na; }
}

const
c_mat2x2::c_cols& c_mat2x2::Cols (void) const { return this->m_cols; }
c_mat2x2::c_cols& c_mat2x2::Cols (void)       { return this->m_cols; }

float  c_mat2x2::Get (const uint32_t _u_col, const uint32_t _u_row) const { return this->Cell (_u_col, _u_row); }

c_mat2x2&  c_mat2x2::operator = (const c_mat2x2& _src) { this->m_data = _src.m_data; return *this; }
c_mat2x2&  c_mat2x2::operator = (c_mat2x2&& _victim) { this->m_data.swap(_victim.m_data); return *this; }

const
float& c_mat2x2::operator ()(const uint32_t _u_col, const uint32_t _u_row) const { return this->Cell(_u_col, _u_row); }
float& c_mat2x2::operator ()(const uint32_t _u_col, const uint32_t _u_row)       { return this->Cell(_u_col, _u_row); }

c_mat2x2& c_mat2x2::operator <<(const t_seq_2x2& _arr_values) {
	_arr_values;
	this->Cols().Set(0, _arr_values.at(0), _arr_values.at(1));
	this->Cols().Set(1, _arr_values.at(3), _arr_values.at(4));
	return *this;
}

c_mat2x2& c_mat2x2::operator *=(const float _f_scale) {
	_f_scale;
	for (uint32_t u_col = 0; u_col < c_mat2x2::u_cols; u_col++)
		for (uint32_t u_row = 0; u_row < c_mat2x2::u_rows; u_row++)
			(*this)(u_col, u_row) *= _f_scale;
	return *this;
}

c_mat2x2  operator * (const c_mat2x2& _left, const c_mat2x2& _right) {
	_left; _right;
	return c_mat2x2({
		_left(0,0) * _right(0,0) + _left(1,0) * _right(0,1),  _left(0,1) * _right(0,0) + _left(1,1) * _right(0,1),
		_left(0,0) * _right(1,0) + _left(1,0) * _right(1,1),  _left(0,1) * _right(1,0) + _left(1,1) * _right(1,1)
	});
}

c_mat2x2  operator + (const c_mat2x2& _left, const c_mat2x2& _right) {
	_left; _right;
	return c_mat2x2({
		_left(0,0) + _right(0,0), _left(0,1) + _right(0,1),  _left(1,0) + _right(1,0), _left(1,1) + _right(1,1)
	});
}

c_mat2x2  operator - (const c_mat2x2& _left, const c_mat2x2& _right) {
	_left; _right;
	return c_mat2x2({
		_left(0,0) - _right(0,0), _left(0,1) - _right(0,1),  _left(1,0) - _right(1,0), _left(1,1) - _right(1,1)
	});
}

c_mat2x2  operator - (const c_mat2x2& _mat) {
	return c_mat2x2({-1.0f * _mat(0,0), -1.0f * _mat(0,1), -1.0f * _mat(1,0), -1.0f * _mat(1,1)});
}

#pragma endregion
#pragma region cls::c_mat3x3::c_cols{}

c_mat3x3::c_cols::c_cols (c_mat3x3& _mat_ref) : m_mat_ref(_mat_ref) {}

vec_3 c_mat3x3::c_cols::Get (const uint32_t _u_col) const { return vec_3((*this)()(_u_col, 0), (*this)()(_u_col, 1), (*this)()(_u_col, 2)); }

c_mat3x3& c_mat3x3::c_cols::Set (const t_seq_3& _col_0, const t_seq_3& _col_1, const t_seq_3& _col_2) {
	this->Set(0, _col_0);
	this->Set(1, _col_1);
	this->Set(2, _col_2);
	return this->m_mat_ref; 
}
c_mat3x3& c_mat3x3::c_cols::Set (const uint32_t _u_col, const t_seq_3& _xyz) { return this->Set(_u_col, _xyz[0], _xyz[1], _xyz[2]); }
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

c_mat3x3& c_mat3x3::c_cols::operator ()(const uint32_t _u_col, const t_seq_3& _xyz) { return this->Set(_u_col, _xyz); }
c_mat3x3& c_mat3x3::c_cols::operator ()(const uint32_t _u_col, const float _x, const float _y, const float _z) { return this->Set(_u_col, _x, _y, _z); }
c_mat3x3& c_mat3x3::c_cols::operator ()(const uint32_t _u_col, const vec_3& _xyz) { return this->Set(_u_col, _xyz); }

#pragma endregion
#pragma region cls::c_mat3x3::c_rows{}

c_mat3x3::c_rows::c_rows (c_mat3x3& _mat_ref) : m_mat_ref(_mat_ref) {}

vec_3 c_mat3x3::c_rows::Get (const uint32_t _n_row) const { return vec_3((*this)()(0, _n_row), (*this)()(1, _n_row), (*this)()(2, _n_row)); }
void  c_mat3x3::c_rows::Set (const uint32_t _n_row, const float _f_val) {
	_n_row; _f_val;
	if (_n_row > c_mat3x3::u_rows - 1)
		return;
	for (uint32_t u_col = 0; u_col < c_mat3x3::u_cols; u_col++) {
		(*this)()(u_col, _n_row) = _f_val;
	}
}

const
c_mat3x3& c_mat3x3::c_rows::operator ()(void) const { return this->m_mat_ref; }
c_mat3x3& c_mat3x3::c_rows::operator ()(void)       { return this->m_mat_ref; }

#pragma endregion
#pragma region cls::c_mat3x3{}

c_mat3x3::c_mat3x3 (void) : m_cols(*this), m_rows(*this) { this->m_data.resize(c_mat3x3::u_size, 0.0f); this->m_data.reserve(c_mat3x3::u_size); }
c_mat3x3::c_mat3x3 (const c_mat3x3& _src) : c_mat3x3() { *this = _src; }
c_mat3x3::c_mat3x3 (const t_seq_3x3& _arr_values) : c_mat3x3() { *this << _arr_values; }
c_mat3x3::c_mat3x3 (const t_seq_3& _col_0, const t_seq_3& _col_1, const t_seq_3& _col_2) : c_mat3x3() {
	this->Cols().Set(0, _col_0);
	this->Cols().Set(1, _col_1);
	this->Cols().Set(2, _col_2);
}
c_mat3x3::c_mat3x3 (c_mat3x3&& _victim) : c_mat3x3() { *this = _victim; }

const
float& c_mat3x3::Cell (const uint32_t _u_col, const uint32_t _u_row) const {
	_u_col; _u_row;
	try { return this->m_data.at(_u_col * c_mat3x3::u_rows + _u_row); }
	catch (const ::std::out_of_range&) { __trace_err_2(_T("#__out_of_range: col=%u|row=%u;\n"), _u_col, _u_row); return ::defs::$na; }
}
float& c_mat3x3::Cell (const uint32_t _u_col, const uint32_t _u_row) {
	_u_col; _u_row;
	try { return this->m_data.at(_u_col * c_mat3x3::u_rows + _u_row); }
	catch (const ::std::out_of_range&) { __trace_err_2(_T("#__out_of_range: col=%u|row=%u;\n"), _u_col, _u_row); return ::defs::$na; }
}
const
c_mat3x3::c_cols& c_mat3x3::Cols (void) const { return this->m_cols; }
c_mat3x3::c_cols& c_mat3x3::Cols (void)       { return this->m_cols; }

float c_mat3x3::Get  (const uint32_t _u_col, const uint32_t _u_row) const { return (*this)(_u_col, _u_row); }

c_mat3x3& c_mat3x3::Identity (void) {

	this->m_data.resize(c_mat3x3::u_size, 0.0f); this->m_data.reserve(c_mat3x3::u_size);

	uint32_t i_ = 0;
	try {
		for (; i_ < c_mat3x3::u_size; i_+= (c_mat3x3::u_rows + 1)) {
			this->m_data.at(i_) = 1.0f;
		}
	}
	catch ( const ::std::out_of_range&) {
		__trace_err_2(_T("#__out_of_range: _ndx=%u|size=%u;\n"), i_, c_mat3x3::u_size);
	}
	return *this;
}

const
c_mat3x3::c_rows& c_mat3x3::Rows (void) const { return this->m_rows; }
c_mat3x3::c_rows& c_mat3x3::Rows (void)       { return this->m_rows; }

c_mat3x3& c_mat3x3::operator = (const c_mat3x3& _src) { this->m_data = _src.m_data; return *this; }
c_mat3x3& c_mat3x3::operator = (c_mat3x3&& _victim) { this->m_data.swap(_victim.m_data); return *this; }

const
float&  c_mat3x3::operator ()(const uint32_t _u_col, const uint32_t _u_row) const { return this->Cell(_u_col, _u_row); }
float&  c_mat3x3::operator ()(const uint32_t _u_col, const uint32_t _u_row)       { return this->Cell(_u_col, _u_row); }

c_mat3x3& c_mat3x3::operator <<(const t_seq_3x3& _arr_values) {
	_arr_values;
	this->Cols().Set(0, _arr_values.at(0), _arr_values.at(1), _arr_values.at(2));
	this->Cols().Set(1, _arr_values.at(3), _arr_values.at(4), _arr_values.at(5));
	this->Cols().Set(2, _arr_values.at(6), _arr_values.at(7), _arr_values.at(8));
	return *this;
}

c_mat3x3& c_mat3x3::operator *=(const float _f_scale) {
	_f_scale;
	for (uint32_t u_col = 0; u_col < c_mat3x3::u_cols; u_col++)
		for (uint32_t u_row = 0; u_row < c_mat3x3::u_rows; u_row++)
			(*this)(u_col, u_row) *= _f_scale;
	return *this;
}

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
c_mat4x4& c_mat4x4::c_cols::Set (const uint32_t _u_col, const vec_3& _xyz ) {
	_u_col; _xyz;
	if (_u_col > c_cols::u_count - 1) { // just returns the reference to unchanged matrix;
		__trace_err_2(_T("#__e_inv_ndx: the col index (%u) is out of acceptable range;\n"), _u_col);
		return this->m_mat_ref;
	}
	(*this)()(_u_col, 0) = _xyz.x;
	(*this)()(_u_col, 1) = _xyz.y;
	(*this)()(_u_col, 2) = _xyz.z; return this->m_mat_ref;
}

const
c_mat4x4& c_mat4x4::c_cols::operator ()(void) const { return this->m_mat_ref; }
c_mat4x4& c_mat4x4::c_cols::operator ()(void)       { return this->m_mat_ref; }

#pragma endregion
#pragma region cls::c_mat4x4{}

c_mat4x4::c_mat4x4 (const bool _b_identity) : m_cols(*this), m_rows(*this) {
	this->m_data.resize(c_mat4x4::u_size, 0.0f); this->m_data.reserve(c_mat4x4::u_size); if (_b_identity) this->Identity();
}
c_mat4x4::c_mat4x4 (const c_mat4x4& _src) : c_mat4x4(false) { *this = _src; }
c_mat4x4::c_mat4x4 (const t_seq_4x4& _arr_values) : c_mat4x4() { *this << _arr_values; }
c_mat4x4::c_mat4x4 (c_mat4x4&& _victim) : c_mat4x4() { *this = _victim; }

const
float& c_mat4x4::Cell (const uint32_t _u_col, const uint32_t _u_row) const {
	_u_col; _u_row;
	try { return this->m_data.at(_u_col * c_mat4x4::u_rows + _u_row); }
	catch (const ::std::out_of_range&) { __trace_err_2(_T("#__out_of_range: col=%u|row=%u;\n"), _u_col, _u_row); return ::defs::$na; }
}
float& c_mat4x4::Cell (const uint32_t _u_col, const uint32_t _u_row) {
	_u_col; _u_row;
	try { return this->m_data.at(_u_col * c_mat4x4::u_rows + _u_row); }
	catch (const ::std::out_of_range&) { __trace_err_2(_T("#__out_of_range: col=%u|row=%u;\n"), _u_col, _u_row); return ::defs::$na; }
}

const
c_mat4x4::c_cols& c_mat4x4::Cols (void) const { return this->m_cols; }
c_mat4x4::c_cols& c_mat4x4::Cols (void)       { return this->m_cols; }

c_mat3x3 c_mat4x4::Exclude (const uint32_t _u_col, const uint32_t _u_row) const {
	_u_col; _u_row;
	if (_u_col > c_mat4x4::u_cols - 1) { __trace_err_2(_T("#e__inv_arg: col index = %u;\n"), _u_col); return c_mat3x3(); }
	if (_u_row > c_mat4x4::u_rows - 1) { __trace_err_2(_T("#e__inv_arg: row index = %u;\n"), _u_row); return c_mat3x3(); }

	c_mat3x3 mat_;

	for (uint32_t u_col = 0; u_col < c_mat4x4::u_cols; u_col++)
		if (_u_col != u_col)
			for (uint32_t u_row = 0; u_row < c_mat4x4::u_rows; u_row++)
				if (_u_row != u_row)
					mat_(u_col, u_row) = (*this)(u_col, u_row);

	return mat_;
}

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
c_mat4x4& c_mat4x4::operator*= (const float _f_scale) {
	_f_scale;
	for (uint32_t u_col = 0; u_col < c_mat4x4::u_cols; u_col++)
		for (uint32_t u_row = 0; u_row < c_mat4x4::u_rows; u_row++)
			(*this)(u_col, u_row) *= _f_scale;
	return *this;
}
c_mat4x4& c_mat4x4::operator <<(const t_seq_4x4& _arr_values) {
	_arr_values;
	this->Cols().Set(0, _arr_values.at(0x0), _arr_values.at(0x1), _arr_values.at(0x2), _arr_values.at(0x3));
	this->Cols().Set(1, _arr_values.at(0x4), _arr_values.at(0x5), _arr_values.at(0x6), _arr_values.at(0x7));
	this->Cols().Set(2, _arr_values.at(0x8), _arr_values.at(0x9), _arr_values.at(0xa), _arr_values.at(0xb));
	this->Cols().Set(3, _arr_values.at(0xc), _arr_values.at(0xd), _arr_values.at(0xe), _arr_values.at(0xf));
	return *this;
}

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
		(*this)()(u_col, _n_row) = _f_val;
	}
}

const
c_mat4x4& c_mat4x4::c_rows::operator ()(void) const { return this->m_mat_ref; }
c_mat4x4& c_mat4x4::c_rows::operator ()(void)       { return this->m_mat_ref; }

#pragma endregion

c_mat4x4 operator * (const c_mat4x4& _left, const c_mat4x4& _right) {
	_left; _right;
	c_mat4x4 result;
	// no check for number of rows of the left matrix for coincident or be the same with the number of columns of the right matrix: arguments are the same type;
	for (uint32_t u_col = 0; u_col < c_mat4x4::c_cols::u_count; u_col++) {

		vec_4 col = _right.Cols().Get(u_col);

		for (uint32_t u_row = 0; u_row < c_mat4x4::c_rows::u_count; u_row++) {
			vec_4 row = _left.Rows().Get(u_row);
			vec_4 res = col * row;
			result(u_col, u_row) = res.Sum(); // result.Cell(u_col, u_row) = (_left.Rows(u_row) * _right.Cols(u_col)).Sum();
		}
	}
	
	return result;
}