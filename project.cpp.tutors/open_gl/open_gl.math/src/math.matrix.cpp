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

c_mat2x2::c_mat2x2 (void) { this->m_data.resize(c_mat2x2::u_cols * c_mat2x2::u_rows, 0x0f); this->m_data.reserve(this->m_data.size()); }
c_mat2x2::c_mat2x2 (const c_mat2x2& _src) : c_mat2x2() { *this = _src; }

float& c_mat2x2::cell (const uint32_t _u_col, const uint32_t _u_row) {
	_u_col; _u_row;
	try { return this->m_data.at(_u_col * c_mat2x2::u_rows + _u_row); }
	catch (const ::std::out_of_range&) { __trace_err_2(_T("#__out_of_range: col=%u|row=%u;\n"), _u_col, _u_row); return ::_impl::$na; }
}

c_mat2x2&  c_mat2x2::operator = (const c_mat2x2& _src) { _src; return *this; }
