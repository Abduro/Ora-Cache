/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Mar-2026 at 15:05:53.503, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL math lib matrix 2x2 uint test interface implementation file for using in test cases' adapters;
*/
#include "test_case_$m$.mat2x2.h"

using namespace ebo::boo::test::open_gl::math;

#pragma region cls::c_mtx_2x2

_pc_sz  c_mtx_2x2::To_str (const t_mat2x2& _mat_2x2, const bool _b_cls) {
         _mat_2x2; _b_cls;
	static _pc_sz pc_sz_fmt_0 = _T("%9.7f");
	static CString cs_out;

	if (cs_out.IsEmpty() == false)
		cs_out.Empty();

	CString cs_value;

	for (uint32_t row_ = 0; row_ < t_mat2x2::u_rows; row_++) {
		CString cs_row;
		for (uint32_t col_ = 0; col_ < t_mat2x2::u_cols; col_++) {

			cs_value = TString().Float(_mat_2x2(col_, row_), t_fmt_spec::e_decimal, pc_sz_fmt_0);
			if (_T('-') == cs_value.Left(1)) {}
			else cs_row += _T(" ");

			cs_row += cs_value;

			if (col_ < t_mat2x2::u_cols - 1)
				cs_row += _T(" ");
		}
		cs_out += TString().Format(_T("%s%s%s"), predefs::_p_pfx, (_pc_sz) cs_row, predefs::_p_sfx);
	}
	if (_b_cls) {
		_out() += TString().Format(_T("cls::[%s].%s() >> [%s%s%s]"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__,  predefs::_p_sfx, (_pc_sz) cs_out, predefs::_p_pfx);
	}
	else {
		_out() += TString().Format(_T("%s[%s%s%s]"), predefs::_p_pfx_hf, predefs::_p_sfx, (_pc_sz) cs_out, predefs::_p_pfx);
	}

	return (_pc_sz) cs_out;
}

#pragma endregion
#pragma region cls::c_mtx_2x2

static _pc_sz pc_sz_fmt_angle = _T("Input values: rotate angle = %.2f;");

t_rot2x2& c_rot_2x2::Prepare (const float _f_angle) {
	_f_angle;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(pc_sz_fmt_angle, _f_angle);

	(*this)().Prepare(_f_angle);

	_out() += _T("[warn] c_mtx_2x2 is prepared for rotation:");
	c_mtx_2x2::To_str((*this)(), false);

	return (*this)();
}

t_mat2x2& c_rot_2x2::Rotate (const float _f_angle, t_mat2x2& _mat_to_rot) {
	_f_angle;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(pc_sz_fmt_angle, _f_angle);

	_out() += _T("[warn] c_mtx_2x2 is prepared for rotation:"); (*this)().Prepare(_f_angle); c_mtx_2x2::To_str((*this)(), false);
	_out() += _T("input c_mtx_2x2 *before* rotation:"); (*this)().Prepare(_f_angle); c_mtx_2x2::To_str(_mat_to_rot, false);

	(*this)() ^ _mat_to_rot;

	_out() += _T("[inpt] input c_mtx_2x2 *after* rotation:"); (*this)().Prepare(_f_angle); c_mtx_2x2::To_str(_mat_to_rot, false);

	return _mat_to_rot;
}

const
t_rot2x2& c_rot_2x2::operator ()(void) const { return this->m_rot2x2; }
t_rot2x2& c_rot_2x2::operator ()(void)       { return this->m_rot2x2; }

#pragma endregion