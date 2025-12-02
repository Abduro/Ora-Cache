/*
	Created by Tech_dog (ebontrop@gmail.com) on 01-Dec-2025 at 18:25:16.417, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' generic data matrix interface implementation file;
*/
#include "math.matrix.h"

using namespace ex_ui::draw::open_gl::math;

CMat2x2:: CMat2x2 (void) : m_data{0.0f} {}
CMat2x2:: CMat2x2 (const CMat2x2& _src) : CMat2x2() { *this = _src; }
CMat2x2:: CMat2x2 (CMat2x2&& _victim) : CMat2x2() { *this = _victim; }
CMat2x2::~CMat2x2 (void) {}

float& CMat2x2::cell (const uint32_t _n_col, const uint32_t _n_row) {
	_n_col; _n_row;
	if (1 < _n_col || 1 < _n_row) {
		static float na_cell = 0.0f;
		return na_cell;
	}
	else
		return this->m_data[_n_col][_n_row];
}


CMat2x2&  CMat2x2::operator = (const CMat2x2& _src) { _src; return *this; }
CMat2x2&  CMat2x2::operator = (CMat2x2&& _victim) { _victim; return *this; }