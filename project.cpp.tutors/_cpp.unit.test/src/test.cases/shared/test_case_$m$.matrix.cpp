/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Feb-2026 at 15:13:54.251, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL math lib matrix uint test interface implementation;
*/
#include "test_case_$m$.matrix.h"

using namespace ebo::boo::test::open_gl::math;

#pragma region cls::c_mtx_base

c_mtx_base::c_mtx_base (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& c_mtx_base::Error (void) const { return this->m_error; }

#pragma endregion
#pragma region cls::c_mtx_3x3

c_mtx_3x3::c_mtx_3x3 (void) : TBase() { TBase::m_error >>__CLASS__; }

_pc_sz  c_mtx_3x3::To_str (const t_mat3x3& _mat_3x3, const bool _b_out) {
         _mat_3x3; _b_out;
	static _pc_sz pc_sz_fmt_0 = _T("%9.7f");
	static CString  cs_out;

	for (uint32_t row_ = 0; row_ < t_mat3x3::u_rows; row_++) {
		CString cs_row;
		for (uint32_t col_ = 0; col_ < t_mat3x3::u_cols; col_++) {

			if (_mat_3x3(col_, row_) < 0.0f) {} // the '-' sign will be added by sprintf();
			else cs_row += _T(" ");

			cs_row += TString().Float(_mat_3x3(col_, row_), t_fmt_spec::e_decimal, pc_sz_fmt_0);

			if (col_ < t_mat3x3::u_cols - 1)
				cs_row += _T(" ");
		}
		cs_out += TString().Format(_T("%s%s%s"), predefs::_p_pfx, (_pc_sz) cs_row, predefs::_p_sfx);
	}
	if (_b_out) {
		_out() += TString().Format(_T("cls::[%s].%s() >> [%s%s%s]"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, predefs::_p_sfx, (_pc_sz) cs_out, predefs::_p_pfx);
	}

	return (_pc_sz) cs_out;
}

#pragma endregion
#pragma region cls::c_mtx_4x4{}

c_mtx_4x4::c_mtx_4x4 (void) : TBase() { TBase::m_error >>__CLASS__; }

_pc_sz  c_mtx_4x4::To_str (const t_mat4x4& _mat_4x4, const bool _b_out) {
         _mat_4x4; _b_out;
	static CString  cs_out;
	static _pc_sz pc_sz_fmt_0 = _T("%9.7f");

	for (uint32_t row_ = 0; row_ < t_mat4x4::u_rows; row_++) {
		CString cs_row;
		for (uint32_t col_ = 0; col_ < t_mat4x4::u_cols; col_++) {
			if (_mat_4x4(col_, row_) < 0.0f) {} // the '-' sign will be added by sprintf();
			else cs_row += _T(" ");

			cs_row += TString().Float(_mat_4x4(col_, row_), t_fmt_spec::e_decimal, pc_sz_fmt_0);

			if (col_ < t_mat4x4::u_cols - 1)
				cs_row += _T(" ");
		}
		cs_out += TString().Format(_T("%s%s%s"), predefs::_p_pfx, (_pc_sz) cs_row, predefs::_p_sfx);
	}
	if (_b_out) {
		_out() += TString().Format(_T("cls::[%s].%s() >> [%s%s%s]"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__,  predefs::_p_sfx, (_pc_sz) cs_out, predefs::_p_pfx);
	}
	return (_pc_sz) cs_out;
}

#pragma endregion