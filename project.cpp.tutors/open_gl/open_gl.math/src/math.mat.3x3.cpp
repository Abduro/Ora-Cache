/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-Mar-2026 at 21:51:34.262, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' generic data matrix 3x3 interface implementation file;
*/
#include "math.mat.3x3.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl::math;

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

c_mat3x3::c_mat3x3 (void) : m_cols(*this), m_rows(*this) { /*this->m_data.resize(c_mat3x3::u_size, 0.0f); this->m_data.reserve(c_mat3x3::u_size);*/ }
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

c_mat3x3& c_mat3x3::Clear (void) { this->m_data.fill(0.0f); return *this; }

const
c_mat3x3::c_cols& c_mat3x3::Cols (void) const { return this->m_cols; }
c_mat3x3::c_cols& c_mat3x3::Cols (void)       { return this->m_cols; }

float c_mat3x3::Get  (const uint32_t _u_col, const uint32_t _u_row) const { return (*this)(_u_col, _u_row); }

c_mat3x3& c_mat3x3::Identity (void) {
//	this->m_data.resize(c_mat3x3::u_size, 0.0f); this->m_data.reserve(c_mat3x3::u_size);
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

c_mat3x3& c_mat3x3::Set (const c_mat2x2& _mat_2) {
	_mat_2;
	(*this)(0,0) = _mat_2(0,0); (*this)(1,0) = _mat_2(1,0);
	(*this)(0,1) = _mat_2(0,1); (*this)(1,1) = _mat_2(1,1);

	return *this;
}

c_mat3x3& c_mat3x3::Transpose (void) {
	/*cols:    0  1  2        0  1  2
	 rows: 0 [ 0, 3, 6 ]    [ 0, 1, 2 ]    indexes that are symmetrically located on opposite sides of the matrix diagonal;
	       1 [ 1, 4, 7 ] >> [ 3, 4, 5 ] :: the pears of indices being swapped: {1,3}{2,6}{5,7} 
	       2 [ 2, 5, 8 ]    [ 6, 7, 8 ]
	*/
	::std::swap(this->Cell(0, 1), this->Cell(1, 0));
	::std::swap(this->Cell(0, 2), this->Cell(2, 0));
	::std::swap(this->Cell(1, 2), this->Cell(2, 1));
#if (0)
	*this = c_trans::Get (*this); // is not used due to it makes the input matrix copy;
#endif
	return *this;
}

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

c_mat3x3::operator c_mat2x2 (void) const {
	return c_mat2x2(
		{(*this)(0,0), (*this)(0,1), (*this)(1,0), (*this)(1,1)}
	);
}

#pragma endregion