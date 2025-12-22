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
}}}}}

#pragma region cls::c_mat2x2{}

c_mat2x2::c_mat2x2 (void) { this->m_data.resize(c_mat2x2::u_cols * c_mat2x2::u_rows, 0x0f); this->m_data.reserve(this->m_data.size()); }
c_mat2x2::c_mat2x2 (const c_mat2x2& _src) : c_mat2x2() { *this = _src; }

float& c_mat2x2::cell (const uint32_t _u_col, const uint32_t _u_row) {
	_u_col; _u_row;
	try { return this->m_data.at(_u_col * c_mat2x2::u_rows + _u_row); }
	catch (const ::std::out_of_range&) { __trace_err_2(_T("#__out_of_range: col=%u|row=%u;\n"), _u_col, _u_row); return ::_impl::$na; }
}

c_mat2x2&  c_mat2x2::operator = (const c_mat2x2& _src) { _src; return *this; }

#pragma endregion
#pragma region cls::c_mat4x4{}

c_mat4x4::c_mat4x4 (void) : m_rows(*this) { this->m_data.resize(c_mat4x4::u_size, 0.0f); this->m_data.reserve(c_mat4x4::u_size); }
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

using c_rows = c_mat4x4::c_rows;

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