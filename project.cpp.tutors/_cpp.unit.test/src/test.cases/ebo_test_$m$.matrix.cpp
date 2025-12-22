/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Dec-2025 at 08:10:22.332, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL math lib matrix uint test interface implementation file; 
*/
#include "ebo_test_$m$.matrix.h"
#include "shared.preproc.h"

using namespace ebo::boo::test::open_gl::math;

c_mat4x4::c_mat4x4 (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void c_mat4x4::_ctor (void) {
	
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	this->m_b_verb = true;
	this->To_str();
}

void c_mat4x4::Identity (void) {

	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	this->ref().Identity();

	this->m_b_verb = true;
	this->To_str();
}

void c_mat4x4::Translate (void) {

	c_vec3 vec3;
	vec3.Set();

	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += _T("the matrix *before* translate:");

	this->ref().Rows().Set(t_mat4x4::u_rows - 1, 1.0f); // sets the last row of the matrix to some value that is not zero, otherwise there's no translation;

	this->m_b_verb = true;
	this->To_str();

	this->ref().Translate(vec3.ref());

	_out() += _T("the matrix *after* translate:");
	this->To_str();
}

const
t_mat4x4& c_mat4x4::ref (void) const { return this->m_mat4x4; }
t_mat4x4& c_mat4x4::ref (void)       { return this->m_mat4x4; }

CString c_mat4x4::To_str (_pc_sz _p_prf, _pc_sz _p_sep, _pc_sz _p_sfx) const {
	_p_prf; _p_sep; _p_sfx;

	static _pc_sz pc_sz_fmt = _T("%9.7f");

	CString cs_out;

	for (uint32_t row_ = 0; row_ < t_mat4x4::u_rows; row_++) {
		CString cs_row;
		for (uint32_t col_ = 0; col_ < t_mat4x4::u_cols; col_++) {
			cs_row += TString().Float(this->ref().Cell(col_, row_), t_fmt_spec::e_decimal, pc_sz_fmt);
			if (col_ < t_mat4x4::u_cols - 1)
				cs_row += _p_sep;
		}
		cs_out += TString().Format(_T("%s%s%s"), _p_prf, (_pc_sz) cs_row, _p_sfx);
	}
	if (this->m_b_verb) {
		_out() += TString().Format(_T("cls::[%s].%s() >> [%s%s%s]"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _p_sfx, (_pc_sz) cs_out, _p_prf);
		_out()();
	}
	return cs_out;
}