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

vec_2& c_rot_3x3::Do (const s_rot_cri_v2& _cri, vec_2& _to_rot) {
	_cri; _to_rot;
	this->Prepare(_cri()); // actually calling this function is not necessary, but just for detailed info output;

	_out() += TString().Format(pc_sz_fmt_args, _cri.m_f_angle, axes_t::To_str(_cri.m_e_axis));
	_out() += TString().Format(_T("Input vec_2: %s;"), (_pc_sz) _to_rot.To_str());
	_out() += TString().Format(_T("Pivot point: %s;"), (_pc_sz) _cri.m_v_pivot.To_str());

//	_to_rot = (*this)().Do(_cri.m_f_angle, _to_rot, _cri.m_b_use_eps); // assigning to the reference to itself is not necessary, but for better readability;
	_to_rot = (*this)().Do(_cri.m_f_angle, _cri.m_v_pivot, _to_rot, _cri.m_b_use_eps);

	_out() += TString().Format(_T("[impt] rotation result: %s;"), (_pc_sz) _to_rot.To_str());

	return _to_rot;
}

vec_3& c_rot_3x3::Do (const s_rot_cri_v3& _cri, vec_3& _to_rot) {
	_cri; _to_rot;
	_out() += TString().Format(pc_sz_fmt_args, _cri.m_f_angle, axes_t::To_str(_cri.m_e_axis));

	vec_3 v3_cpy = _to_rot; // makes the copy of input vector for making comparison after rotation;

	_to_rot = (*this)().Do(_cri.m_f_angle, _to_rot, _cri.m_e_axis, _cri.m_b_use_eps);

	_out() += _T("[impt] c_mtx_3x3 is prepared for rotation:");
	c_mtx_3x3::To_str((*this)()(), false);

	_out() += TString().Format(_T("Input math::vec_3 *before*: %s;"), (_pc_sz) v3_cpy.To_str());
	_out() += TString().Format(_T("Input math::vec_3 *after* : %s;"), (_pc_sz) _to_rot.To_str());

	return _to_rot;
}

t_rot3x3& c_rot_3x3::Prepare (const s_rot_cri_t& _cri) {
	_cri;
	if (_cri.m_b_print_cls)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(pc_sz_fmt_args, _cri.m_f_angle, axes_t::To_str(_cri.m_e_axis));

	(*this)().Prepare(_cri.m_f_angle, _cri.m_e_axis);

	_out() += _T("[impt] c_mtx_3x3 is prepared for rotation:");
	c_mtx_3x3::To_str((*this)()(), false);

	return (*this)();
}

const
t_rot3x3& c_rot_3x3::operator ()(void) const { return this->m_rot3x3; }
t_rot3x3& c_rot_3x3::operator ()(void)       { return this->m_rot3x3; }

#pragma endregion