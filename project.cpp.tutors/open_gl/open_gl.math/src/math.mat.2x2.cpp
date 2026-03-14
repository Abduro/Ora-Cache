/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Mar-2026 at 21:45:05.074, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' generic data matrix 2x2 implementation declaration file;
*/
#include "math.mat.2x2.h"
#include "math.mat.invert.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl::math;

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
/* important: vector::resize() only fills new elements if the new size is *larger* than the current size; */
c_mat2x2::c_mat2x2 (void) : m_cols(*this), m_rows(*this), m_data{0.0f} { /*this->m_data.resize(c_mat2x2::u_size, 0x0f); this->m_data.reserve(c_mat2x2::u_size);*/ }
c_mat2x2::c_mat2x2 (const c_mat2x2& _src) : c_mat2x2() { *this = _src; }
c_mat2x2::c_mat2x2 (const t_seq_2x2& _arr_values) : c_mat2x2() { *this << _arr_values; }
c_mat2x2::c_mat2x2 (c_mat2x2&& _victim) : c_mat2x2() { *this = _victim; }

static _pc_sz p_sz_err_out_of_range = _T("#__out_of_range: col=%u|row=%u;\n");

const
float& c_mat2x2::Cell (const uint32_t _u_col, const uint32_t _u_row) const {
	_u_col; _u_row;
	try { return this->m_data.at(_u_col * c_mat2x2::u_rows + _u_row); }
	catch (const ::std::out_of_range&) { __trace_err_2(p_sz_err_out_of_range, _u_col, _u_row); return ::defs::$na; }
}
float& c_mat2x2::Cell (const uint32_t _u_col, const uint32_t _u_row) {
	_u_col; _u_row;
	try { return this->m_data.at(_u_col * c_mat2x2::u_rows + _u_row); }
	catch (const ::std::out_of_range&) { __trace_err_2(p_sz_err_out_of_range, _u_col, _u_row); return ::defs::$na; }
}

c_mat2x2& c_mat2x2::Clear (void) { /*this->Raw().fill(0.0f);*/ ::std::fill(this->m_data.begin(), this->m_data.end(), 0.0f); return *this; }

const
c_mat2x2::c_cols& c_mat2x2::Cols (void) const { return this->m_cols; }
c_mat2x2::c_cols& c_mat2x2::Cols (void)       { return this->m_cols; }
const
t_seq_2x2& c_mat2x2::Data (void) const { return this->m_data; }
t_seq_2x2& c_mat2x2::Data (void)       { return this->m_data; }

float  c_mat2x2::Get (const uint32_t _u_col, const uint32_t _u_row) const { return this->Cell (_u_col, _u_row); }
vec_2& c_mat2x2::Mltply (vec_2& _vec2, const bool _b_round/* = false*/, const float _threshold/* = defs::f_epsilon*/) const {
	_vec2; _b_round; _threshold;
	/*cols:    0#   #1      #0                                #0  #1 (i stads for an index)
	rows: #0  (0,0) (1,0) * [x] = [(0,0) * x + (1,0) * y]  == i_0 i_2 * [x] = [ i_0 * x + i_2 * y]
	      #1  (0,1) (1,1)   [y]   [(0,1) * x + (1,1) * y];    i_1 i_3   [y]   [ i_1 * x + i_3 * y];
	*/
	_vec2.Set(
		(*this)()[0] * _vec2.x + (*this)()[2] * _vec2.y,
		(*this)()[1] * _vec2.x + (*this)()[3] * _vec2.y
	);
#if (0)
	if (_b_epsilon) {
		if (::abs(_vec2.x) < defs::f_epsilon) _vec2.x = 0.0f;
		if (::abs(_vec2.y) < defs::f_epsilon) _vec2.y = 0.0f;
	}
#else
	if (_b_round) _vec2.Round(_threshold);
#endif
	return _vec2;
}
#if (0)
const
t_seq_2x2& c_mat2x2::Raw (void) const { return this->m_data; }
t_seq_2x2& c_mat2x2::Raw (void)       { return this->m_data; }
#endif
c_mat2x2&  c_mat2x2::Seed (const float _f_by/* = 0.0f*/) {
	_f_by;
#if (0)
	this->Raw().fill(_f_by);
#else
	::std::fill(this->m_data.begin(), this->m_data.end(), _f_by);
#endif
	return *this;
}
c_mat2x2&  c_mat2x2::Transpose (void) {
	/*
		[ 0, 2 ] >> [ 0, 1 ] :: entries being swapped are symmetrically located on opposite sides of the matrix diagonal;
		[ 1, 3 ]    [ 2, 3 ]    pair(s) of indices being swapped {1, 2};
	*/
	try { ::std::swap (this->Cell(0, 0), this->Cell(1, 0)); } catch (const ::std::bad_alloc&) {} // try-catch block is not required here;
#if (0)
	*this = c_trans::Get(*this); // this function makes a copy of data, looks like not so efficient;
#endif
	return *this;
}

c_mat2x2&  c_mat2x2::operator = (const c_mat2x2& _src) { this->m_data = _src.m_data; return *this; }
c_mat2x2&  c_mat2x2::operator = (c_mat2x2&& _victim) { this->m_data.swap(_victim.m_data); return *this; }

const
float& c_mat2x2::operator ()(const uint32_t _u_col, const uint32_t _u_row) const { return this->Cell(_u_col, _u_row); }
float& c_mat2x2::operator ()(const uint32_t _u_col, const uint32_t _u_row)       { return this->Cell(_u_col, _u_row); }

c_mat2x2& c_mat2x2::operator <<(const t_seq_2x2& _arr_values) {
	_arr_values;
	this->Cols().Set(0, _arr_values.at(0), _arr_values.at(1));
	this->Cols().Set(1, _arr_values.at(2), _arr_values.at(3));
	return *this;
}

c_mat2x2& c_mat2x2::operator *=(const float _f_scale) {
	_f_scale;
	for (uint32_t u_col = 0; u_col < c_mat2x2::u_cols; u_col++)
		for (uint32_t u_row = 0; u_row < c_mat2x2::u_rows; u_row++)
			(*this)(u_col, u_row) *= _f_scale;
	return *this;
}

c_mat2x2& c_mat2x2::operator *=(const c_mat2x2& _mat2x2) {
	_mat2x2;
	/*
	matrices:  this    rhs      result
	cols:    #0  #1   #0  #1    #0                     #1                       #0 (col, row)                 #1 (col, row)
	rows: #0 t0  t2 * r0  r2  = t[0]*r[0] + t[2]*r[1]  t[0]*r[2] + t[2]*r[3] >> t(0,0)*r(0,0) + t(1,0)*r(0,1) t(0,0)*r(1,0) + t(1,0)*r(1,1)
	      #1 t1  t3   r1  r3    m[1]*r[0] + m[3]*r[1]  t[1]*r[2] + t[3]*r[3]    t(0,1)*r(0,0) + t(1,1)*r(0,1) t(0,1)*r(1,0) + t(1,1)*r(1,1)
	*/
	this->m_data = {
		(*this)(0, 0) * _mat2x2(0, 0) + (*this)(1, 0) * _mat2x2(0, 1), // col:0;row:0;
		(*this)(0, 1) * _mat2x2(0, 0) + (*this)(1, 1) * _mat2x2(0, 1), // col:0;row:1;
		(*this)(0, 0) * _mat2x2(1, 0) + (*this)(1, 0) * _mat2x2(1, 1), // col:1;row:0;
		(*this)(0, 1) * _mat2x2(1, 0) + (*this)(1, 1) * _mat2x2(1, 1), // col:1;row:1;
	};
	return *this;
}

vec_2& c_mat2x2::operator *= (vec_2& _v_2) const {
	_v_2;
	/* cols:  #0   #1
	rows: #0  i_0 i_2 * [x] = [ i_0 * x + i_2 * y]
	      #1  i_1 i_3   [2]   [ i_1 * x + i_3 * y];
	*/
	return _v_2.Set(
		(*this)()[0] * _v_2.x + (*this)()[2] * _v_2.y,
		(*this)()[1] * _v_2.x + (*this)()[3] * _v_2.y
	);
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
const
float* c_mat2x2::operator ()(void) const { return this->m_data.data(); }
float* c_mat2x2::operator ()(void)       { return this->m_data.data(); }

bool c_mat2x2::operator ==(const c_mat2x2& _mat2x2) const {
	return (this->m_data == _mat2x2.m_data);
}

c_mat2x2::operator const t_seq_2x2& (void) const { return this->Data(); }
c_mat2x2::operator       t_seq_2x2& (void)       { return this->Data(); }

#pragma endregion

vec_2& operator * (const cmat2x2_t& _mat2x2, vec_2& _vec2) {
	_mat2x2; _vec2;
	return _mat2x2.Mltply(_vec2, false);
}