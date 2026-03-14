/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Feb-2026 at 15:13:54.251, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL math lib matrix 3x3 uint test interface implementation;
*/
#include "test_case_$m$.mat3x3.h"

using namespace ebo::boo::test::open_gl::math;

#pragma region cls::c_mtx_3x3

_pc_sz  c_mtx_3x3::To_str (const t_mat3x3& _mat_3x3, const bool _b_cls) {
         _mat_3x3; _b_cls;
	static _pc_sz pc_sz_fmt_0 = _T("%9.7f");
	static CString  cs_out;

	if (cs_out.IsEmpty() == false)
		cs_out.Empty();

	CString cs_value;

	for (uint32_t row_ = 0; row_ < t_mat3x3::u_rows; row_++) {
		CString cs_row;
		for (uint32_t col_ = 0; col_ < t_mat3x3::u_cols; col_++) {

			cs_value = TString().Float(_mat_3x3(col_, row_), t_fmt_spec::e_decimal, pc_sz_fmt_0);
			if (_T('-') == cs_value.Left(1)) {}
			else cs_row += _T(" ");

			cs_row += cs_value;

			if (col_ < t_mat3x3::u_cols - 1)
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
#pragma region cls::c_rot_3x3

static _pc_sz pc_sz_fmt_args = _T("Rotate args: angle = %.2f; around %s");

_pc_sz __axis_to_str (const axes_t::e_axes _e_axis) {
	_e_axis;
	static CString  cs_out;
	switch (_e_axis) {
	case axes_t::e_axes::e_x_axis: cs_out = _T("x-axis"); break;
	case axes_t::e_axes::e_y_axis: cs_out = _T("y-axis"); break;
	case axes_t::e_axes::e_z_axis: cs_out = _T("z-axis"); break;
	default: cs_out = _T("#undef");
	}

	return (_pc_sz) cs_out;
}

t_rot3x3& c_rot_3x3::Prepare (const s_rot_cri_t& _cri) {
	_cri;
	if (_cri.m_b_print_cls)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(pc_sz_fmt_args, _cri.m_f_angle, __axis_to_str(_cri.m_e_axis));

	(*this)().Prepare(_cri.m_f_angle, _cri.m_e_axis);

	_out() += _T("[impt] c_mtx_3x3 is prepared for rotation:");
	c_mtx_3x3::To_str((*this)()(), false);

	return (*this)();
}

vec_2& c_rot_3x3::Rotate (const s_rot_cri_ex& _cri, vec_2& _to_rot) {
	_cri; _to_rot;

	this->Prepare(_cri());

	_out() += TString().Format(pc_sz_fmt_args, _cri.m_f_angle, __axis_to_str(_cri.m_e_axis));
	_out() += TString().Format(_T("Input vec_2: %s;"), (_pc_sz) _to_rot.To_str());
	_out() += TString().Format(_T("Pivot point: %s;"), (_pc_sz) _cri.m_v_pivot.To_str());

//	_to_rot = (*this)().Do(_cri.m_f_angle, _to_rot, _cri.m_b_use_eps); // assigning to the reference to itself is not necessary, but for better readability;
	_to_rot = (*this)().Do(_cri.m_f_angle, _cri.m_v_pivot, _to_rot, _cri.m_b_use_eps);

	_out() += TString().Format(_T("[impt] rotation result: %s;"), (_pc_sz) _to_rot.To_str());

	return _to_rot;
}
const
t_rot3x3& c_rot_3x3::operator ()(void) const { return this->m_rot3x3; }
t_rot3x3& c_rot_3x3::operator ()(void)       { return this->m_rot3x3; }

#pragma endregion