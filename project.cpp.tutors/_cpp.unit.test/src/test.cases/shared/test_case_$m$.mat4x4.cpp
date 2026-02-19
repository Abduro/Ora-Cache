/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Feb-2026 at 14:01:04.258, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL math lib matrix 4x4 uint test interface implementation;
*/
#include "test_case_$m$.mat4x4.h"

using namespace ebo::boo::test::open_gl::math;

#pragma region cls::c_mtx_4x4{}

c_mtx_4x4::c_mtx_4x4 (void) : TBase() { TBase::m_error >>__CLASS__; }


err_code c_mtx_4x4::Identity (void) {
	TBase::m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	this->To_str((*this)().Identity(), true);
	return TBase::Error();
}

err_code c_mtx_4x4::Translate(vec_3& v_pos) {
	v_pos;
	TBase::m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(_T("Input vector *before* translate: {%s}"), (_pc_sz) v_pos.To_str());

	_out() += _T("Test case #0: *no* transformation");
	_out() += _T("Translate matrix:");
	this->To_str((*this)().Identity(), true); // sets the last matrix cell to 1.0f value, otherwise there's no translation for direction;

	return TBase::Error();
}

_pc_sz  c_mtx_4x4::To_str (const t_mat4x4& _mat_4x4, const bool _b_cls) {
         _mat_4x4; _b_cls;
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
	if (_b_cls) {
		_out() += TString().Format(_T("cls::[%s].%s() >> [%s%s%s]"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__,  predefs::_p_sfx, (_pc_sz) cs_out, predefs::_p_pfx);
	}
	return (_pc_sz) cs_out;
}
const
t_mat4x4&  c_mtx_4x4::operator ()(void) const { return this->m_mat4x4; }
t_mat4x4&  c_mtx_4x4::operator ()(void)       { return this->m_mat4x4; }

#pragma endregion