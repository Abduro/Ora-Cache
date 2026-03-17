/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Feb-2026 at 14:01:04.258, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL math lib matrix 4x4 uint test interface implementation;
*/
#include "test_case_$m$.mat4x4.h"

using namespace ebo::boo::test::open_gl::math;

#pragma region cls::c_mtx_4x4{}

c_mtx_4x4::c_mtx_4x4 (void) : m_mat4x4(false) {} // no identity matrix by default construction;
c_mtx_4x4::c_mtx_4x4 (const ::glm::mat4x4& _mat4x4) : c_mtx_4x4() {
#if (0)
	t_mat4x4::Set((*this)(), static_cast<const float*>(::glm::value_ptr(_mat4x4)), this->m_error);
#else
	(*this)() = c_adapter() << _mat4x4;
#endif
}

t_mat4x4  c_mtx_4x4::Generate (const float _f_min, const float _f_max) {
	_f_min; _f_max;
	t_mat4x4 mat_result;

	for (uint32_t i_ = 0; i_ < t_mat4x4::u_size; i_++)
		mat_result.Data().at(i_) = TRandom_2::Float(_f_min, _f_max); // actually it is not expected the 'out_of_range' exception;

	return mat_result;
}

t_mat4x4& c_mtx_4x4::Identity (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	this->To_str((*this)().Identity(), true);
	return (*this)();
}

t_mat4x4& c_mtx_4x4::Translate(vec_3& v_pos) {
	v_pos;
	/* translate matrix:
	cols:    #0 #1 #2 #3
	rows: #0  1  0  0  X
	      #1  0  1  0  Y
	      #2  0  0  1  Z
	      #3  0  0  0  1, where X,Y,Z the coordinates to move/change vertex position;
	*/
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(_T("Input vector *before* translate: {%s}"), (_pc_sz) v_pos.To_str());
	_out() += _T("Translate matrix:");
	this->To_str((*this)().Translate(v_pos), true); // the matrix is the identity in its initial stage;

	return (*this)();
}

t_mat4x4& c_mtx_4x4::Transpose (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	this->To_str((*this)().Transpose(), true);
	return (*this)();
}

_pc_sz    c_mtx_4x4::To_str (const t_mat4x4& _mat_4x4, const bool _b_cls) {
	_mat_4x4; _b_cls;
	static CString  cs_out;
	static _pc_sz pc_sz_fmt_0 = _T("%9.7f");

	if (cs_out.IsEmpty() == false)
		cs_out.Empty();

	CString cs_value;

	for (uint32_t row_ = 0; row_ < t_mat4x4::u_rows; row_++) {
		CString cs_row;
		for (uint32_t col_ = 0; col_ < t_mat4x4::u_cols; col_++) {
#if (0) // -0.00f is not recognizable as a digit that is less than 0.0f and the format being applied is not correct;
			if (_mat_4x4(col_, row_) < 0.0f) {} // the '-' sign will be added by sprintf();
			else cs_row += _T(" ");

			cs_row += TString().Float(_mat_4x4(col_, row_), t_fmt_spec::e_decimal, pc_sz_fmt_0);
#else
			cs_value = TString().Float(_mat_4x4(col_, row_), t_fmt_spec::e_decimal, pc_sz_fmt_0);
			if (_T('-') == cs_value.Left(1)) {}
			else cs_row += _T(" ");

			cs_row += cs_value;
#endif
			if (col_ < t_mat4x4::u_cols - 1)
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
const
t_mat4x4& c_mtx_4x4::operator ()(void) const { return this->m_mat4x4; }
t_mat4x4& c_mtx_4x4::operator ()(void)       { return this->m_mat4x4; }

t_mat4x4& c_mtx_4x4::operator <<(const ::glm::mat4x4& _mat4x4) {
	return (*this)() = c_adapter() << _mat4x4;
}

::glm::mat4x4& c_mtx_4x4::operator >> (::glm::mat4x4& _mat4x4) const {
	_mat4x4;
	CError error(__CLASS__, __METHOD__, __s_ok);

	(*this)().Set(static_cast<float*>(::glm::value_ptr(_mat4x4)), error);
	return _mat4x4;
}

#pragma endregion
#pragma region cls::c_rot_4x4{}

vec_4& c_rot_4x4::Do (const s_rot_cri_v4& _cri, vec_4& _to_rot) {
	_cri; _to_rot;
	_out() += TString().Format(pc_sz_fmt_args, _cri.m_f_angle, axes_t::To_str(_cri.m_e_axis));

	vec_4 v4_cpy = _to_rot; // makes the copy of input vector for making comparison after rotation;

	_to_rot = (*this)().Do(_cri.m_f_angle, _to_rot, _cri.m_e_axis, _cri.m_b_use_eps);

	_out() += _T("[impt] c_mtx_4x4 is prepared for rotation:");
	c_mtx_4x4::To_str((*this)()(), false);

	_out() += TString().Format(_T("Input math::vec_4 *before*: %s;"), (_pc_sz) v4_cpy.To_str());
	_out() += TString().Format(_T("Input math::vec_4 *after* : %s;"), (_pc_sz) _to_rot.To_str());

	return _to_rot;
}

t_rot4x4& c_rot_4x4::Prepare (const s_rot_cri_t& _cri) {
	_cri;
	if (_cri.m_b_print_cls)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(pc_sz_fmt_args, _cri.m_f_angle, axes_t::To_str(_cri.m_e_axis));

	(*this)().Prepare(_cri.m_f_angle, _cri.m_e_axis);

	_out() += _T("[impt] c_mtx_4x4 is prepared for rotation:");
	c_mtx_4x4::To_str((*this)()(), false);

	return (*this)();
}

const
t_rot4x4&  c_rot_4x4::operator ()(void) const { return this->m_rot4x4; }
t_rot4x4&  c_rot_4x4::operator ()(void)       { return this->m_rot4x4; }

#pragma endregion