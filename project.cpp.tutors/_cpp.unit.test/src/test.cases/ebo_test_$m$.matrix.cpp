/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Dec-2025 at 08:10:22.332, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL math lib matrix uint test interface implementation file; 
*/
#include "ebo_test_$m$.matrix.h"
#include "shared.preproc.h"

using namespace ebo::boo::test::open_gl::math;

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace _impl {}}}}}

#pragma region cls::c_mat3x3{}

c_mat3x3::c_mat3x3 (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb && false) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void c_mat3x3::_ctor (void) {
	
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	this->m_b_verb = true;
	this->To_str();
}

void c_mat3x3::Set (void) {

	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += _T("the matrix *initial* values:");

	this->To_str();

	c_tvec_3x3 col_0(0.0f, 1.0f, 2.0f), col_1(3.0f, 4.0f, 5.0f), col_2(6.0f, 7.0f, 8.0f);
	
	_out() += _T("*input* values:");
	_out() += TString().Format(_T("col_#0: %s"), (_pc_sz) col_0().To_str());
	_out() += TString().Format(_T("col_#1: %s"), (_pc_sz) col_1().To_str());
	_out() += TString().Format(_T("col_#2: %s"), (_pc_sz) col_2().To_str());

	this->ref().Cols().Set(0, col_0.ref());
	this->ref().Cols().Set(1, col_1.ref());
	this->ref().Cols().Set(2, col_2.ref());

	_out() += _T("the matrix *result* values:");
	this->To_str();
	_out()();
}

const
t_mat3x3& c_mat3x3::ref (void) const { return this->m_mat3x3; }
t_mat3x3& c_mat3x3::ref (void)       { return this->m_mat3x3; }

CString   c_mat3x3::To_str (_pc_sz _p_prf, _pc_sz _p_sep, _pc_sz _p_sfx) const {
	_p_prf; _p_sep; _p_sfx;
	return c_mtx_3x3().To_str((*this)(), this->m_b_verb);
}

const
t_mat3x3&  c_mat3x3::operator ()(void) const { return this->ref(); }
t_mat3x3&  c_mat3x3::operator ()(void)       { return this->ref(); }

#pragma endregion
#pragma region cls::c_mat4x4{}

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

	c_mtx_4x4().Identity(); _out()();
}

void c_mat4x4::Translate (void) {
	
	c_mtx_4x4().Translate(c_tvec_3x3(0.0f, 0.1f, 0.0f)()); _out()();
}

const
t_mat4x4& c_mat4x4::ref (void) const { return this->m_mat4x4; }
t_mat4x4& c_mat4x4::ref (void)       { return this->m_mat4x4; }

CString c_mat4x4::To_str (_pc_sz _p_prf, _pc_sz _p_sep, _pc_sz _p_sfx) const {
	_p_prf; _p_sep; _p_sfx;
	return c_mtx_4x4().To_str(this->ref(), this->m_b_verb);
}

#pragma endregion
#pragma region cls::c_rot_3x3{}

c_rot_3x3::c_rot_3x3 (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb && false) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void c_rot_3x3::_ctor (void) {
	
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	this->To_str();
}

const
t_rot3x3& c_rot_3x3::ref (void) const { return this->m_rot3x3; }
t_rot3x3& c_rot_3x3::ref (void)       { return this->m_rot3x3; }

void      c_rot_3x3::Rotate_x (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += _T("the matrix *before* rotate:");

	c_mtx_3x3().To_str(this->ref(), true);

	c_tvec_3x3 x_axis(1.0f, 0.0f, 0.0f);

	static _pc_sz pc_sz_fmt = _T("input values: rotate angle = %.1f; %s-axis = %s;");

	const float f_angels[] = {0.0f, +90.0f, -90.0f, +180.0f, -180.0f, +270.0f, -270.0f, +360.0f, -360.0f};

	for (uint32_t i_ = 0; i_ < _countof(f_angels); i_++) {
		_out() += TString().Format(pc_sz_fmt, f_angels[i_], _T("x"), (_pc_sz) x_axis().To_str());

		this->ref().Do(f_angels[i_], x_axis.ref());

		_out() += _T("the matrix *after* rotate:");
		_out() +=  c_mtx_3x3().To_str(this->ref(), true);
	}
	_out()();
}

void      c_rot_3x3::Rotate_y (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += _T("the matrix *before* rotate:");

	c_mtx_3x3().To_str(this->ref(), true);
	c_tvec_3x3 y_axis(0.0f, 1.0f, 0.0f);

	static _pc_sz pc_sz_fmt = _T("input values: rotate angle = %.1f; %s-axis = %s;");

	const float f_angels[] = {0.0f, +90.0f, -90.0f, +180.0f, -180.0f, +270.0f, -270.0f, +360.0f, -360.0f};

	for (uint32_t i_ = 0; i_ < _countof(f_angels); i_++) {
		_out() += TString().Format(pc_sz_fmt, f_angels[i_], _T("y"), (_pc_sz) y_axis().To_str());

		this->ref().Do(f_angels[i_], y_axis.ref());

		_out() += _T("the matrix *after* rotate:");
		c_mtx_3x3().To_str(this->ref(), true);
	}
	_out()();
}

void      c_rot_3x3::Rotate_z (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += _T("the matrix *before* rotate:");

	c_mtx_3x3().To_str(this->ref(), true);
	c_tvec_3x3 z_axis(0.0f, 0.0f, 1.0f);

	static _pc_sz pc_sz_fmt = _T("input values: rotate angle = %.1f; %s-axis = %s;");

	const float f_angels[] = {0.0f, +90.0f, -90.0f, +180.0f, -180.0f, +270.0f, -270.0f, +360.0f, -360.0f};

	for (uint32_t i_ = 0; i_ < _countof(f_angels); i_++) {
		_out() += TString().Format(pc_sz_fmt, f_angels[i_], _T("z"), (_pc_sz) z_axis().To_str());

		this->ref().Do(f_angels[i_], z_axis.ref());

		_out() += _T("the matrix *after* rotate:");
		c_mtx_3x3().To_str(this->ref(), true);
	}
	_out()();
}

CString   c_rot_3x3::To_str (void) const {
	CString cs_out = c_mtx_3x3().To_str(this->ref(), this->m_b_verb); if (this->m_b_verb) _out()();
	return  cs_out;
}

#pragma endregion
#pragma region cls::c_rot_4x4{}

c_rot_4x4::c_rot_4x4 (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb && false) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void c_rot_4x4::_ctor (void) {
	
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	this->To_str();
}

const
t_rot4x4& c_rot_4x4::ref (void) const { return this->m_rot4x4; }
t_rot4x4& c_rot_4x4::ref (void)       { return this->m_rot4x4; }

void c_rot_4x4::Rotate_free (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += _T("the matrix *before* rotate:");

	c_mtx_4x4().To_str(this->ref(), true);

	this->m_b_verb = false; // disables trace output to test console temporarily;
	this->Set();

	c_tvec_3x3 axis(0.5f, 0.5f, 0.5f);

	static _pc_sz pc_sz_fmt = _T("input values: rotate angle = %.1f; axis = %s");

	const float f_angels[] = {0.0f, +90.0f, -90.0f, +180.0f, -180.0f, +270.0f, -270.0f, +360.0f, -360.0f};

	for (uint32_t i_ = 0; i_ < _countof(f_angels); i_++) {
		_out() += TString().Format(pc_sz_fmt, f_angels[i_], (_pc_sz) axis().To_str() );

		this->ref().Do(f_angels[i_], axis.ref());

		_out() += _T("the matrix *after* rotate:");
		c_mtx_4x4().To_str(this->ref(), true);
	}
	_out()();
}

void c_rot_4x4::Rotate_x (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += _T("the matrix *before* rotate:");

	c_mtx_4x4().To_str(this->ref(), true);

	this->m_b_verb = false; // disables trace output to test console temporarily;
	this->Set();

	static _pc_sz pc_sz_fmt = _T("input values: rotate angle = %.1f;");

	const float f_angels[] = {0.0f, +90.0f, -90.0f, +180.0f, -180.0f, +270.0f, -270.0f, +360.0f, -360.0f};

	for (uint32_t i_ = 0; i_ < _countof(f_angels); i_++) {
		_out() += TString().Format(pc_sz_fmt, f_angels[i_]);

		this->ref().On_x(f_angels[i_]);

		_out() += _T("the matrix *after* rotate:");
		c_mtx_4x4().To_str(this->ref(), true);
	}
	_out()();
}

void c_rot_4x4::Rotate_y (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += _T("the matrix *before* rotate:");

	c_mtx_4x4().To_str(this->ref(), true);

	this->m_b_verb = false; // disables trace output to test console temporarily;
	this->Set();

	static _pc_sz pc_sz_fmt = _T("input values: rotate angle = %.1f;");

	const float f_angels[] = {0.0f, +90.0f, -90.0f, +180.0f, -180.0f, +270.0f, -270.0f, +360.0f, -360.0f};

	for (uint32_t i_ = 0; i_ < _countof(f_angels); i_++) {
		_out() += TString().Format(pc_sz_fmt, f_angels[i_]);

		this->ref().On_y(f_angels[i_]);

		_out() += _T("the matrix *after* rotate:");
		c_mtx_4x4().To_str(this->ref(), true);
	}
	_out()();
}

void c_rot_4x4::Rotate_z (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += _T("the matrix *before* rotate:");

	c_mtx_4x4().To_str(this->ref(), true);

	this->m_b_verb = false; // disables trace output to test console temporarily;
	this->Set();

	static _pc_sz pc_sz_fmt = _T("input values: rotate angle = %.1f;");

	const float f_angels[] = {0.0f, +90.0f, -90.0f, +180.0f, -180.0f, +270.0f, -270.0f, +360.0f, -360.0f};

	for (uint32_t i_ = 0; i_ < _countof(f_angels); i_++) {
		_out() += TString().Format(pc_sz_fmt, f_angels[i_]);

		this->ref().On_z(f_angels[i_]);

		_out() += _T("the matrix *after* rotate:");
		c_mtx_4x4().To_str(this->ref(), true);
	}
	_out()();
}

void c_rot_4x4::Set (void) {

	if (this->m_b_verb) { // if this method is called indirectly, this data output is not required;
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += _T("the matrix *initial* state entries:");

	c_mtx_4x4().To_str(this->ref(), true);
	}
	c_vec4
	col_0(0.0f, 0.1f, 0.2f, 1.0f, false),
	col_1(0.4f, 0.5f, 0.6f, 1.0f, false),
	col_2(0.7f, 0.8f, 0.9f, 1.0f, false),
	col_3(0.5f, 0.5f, 0.5f, 1.0f, false);

	_out() += TString().Format(_T("col_#_0: %s"), (_pc_sz) col_0.To_str());
	_out() += TString().Format(_T("col_#_1: %s"), (_pc_sz) col_1.To_str());
	_out() += TString().Format(_T("col_#_2: %s"), (_pc_sz) col_2.To_str());
	_out() += TString().Format(_T("col_#_3: %s"), (_pc_sz) col_3.To_str());

	this->ref().Cols().Set(col_0.ref(), col_1.ref(), col_2.ref(), col_3.ref());

	_out() += _T("the matrix *after* setting data:");
	c_mtx_4x4().To_str(this->ref(), true);

	if (this->m_b_verb) // if this method is called indirectly, the trace output may not be required yet;
	_out()();
}

CString   c_rot_4x4::To_str (void) const {
	CString cs_out = c_mtx_4x4().To_str(this->ref(), this->m_b_verb); if (this->m_b_verb) _out()();
	return  cs_out;
}

#pragma endregion