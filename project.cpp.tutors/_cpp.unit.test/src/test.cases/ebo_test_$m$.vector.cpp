/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Dec-2025 at 16:53:10.131, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL math lib vector uint test interface implementation file; 
*/
#include "ebo_test_$m$.vector.h"
#include "shared.preproc.h"

using namespace ebo::boo::test::open_gl::math;

#pragma region cls::c_vec3{}

c_vec3::c_vec3(const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb && false) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

c_vec3::c_vec3 (const float _x, const float _y, const float _z, const bool _b_verb) : m_b_verb(_b_verb), m_vec_3(_x, _y, _z) {}

void c_vec3::_ctor (void) {
	
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	this->m_b_verb = true;
	this->To_str();
}

void c_vec3::Set (void) {
	
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	const float f_args[] = {1.101f, 2.202f, 3.303f };
	_out() += TString().Format(_T("the input args: x = %9.7f; y = %9.7f; z = %9.7f"), f_args[0], f_args[1], f_args[2]);

	this->ref().Set(f_args[0], f_args[1], f_args[2]);

	this->m_b_verb = true;
	this->To_str();
}

const
vec_3& c_vec3::ref (void) const { return this->m_vec_3; }
vec_3& c_vec3::ref (void)       { return this->m_vec_3; }

CString c_vec3::To_str (_pc_sz _p_prf, _pc_sz _p_sep, _pc_sz _p_sfx) const {
	_p_prf; _p_sep; _p_sfx;

	static _pc_sz pc_sz_fmt = _T("%9.7f");
	static _pc_sz pc_sz_pat = _T("[x = %s%sy = %s%sz = %s]");

	CString cs_out = TString().Format(pc_sz_pat,
		TString().Float(this->ref().x, t_fmt_spec::e_decimal, pc_sz_fmt), _p_sep,
		TString().Float(this->ref().y, t_fmt_spec::e_decimal, pc_sz_fmt), _p_sep,
		TString().Float(this->ref().z, t_fmt_spec::e_decimal, pc_sz_fmt)
	);

	if (this->m_b_verb) {
		_out() += TString().Format(_T("cls::[%s].%s() >> %s"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, (_pc_sz) cs_out);
		_out()();
	}
	return cs_out;
}

#pragma endregion
#pragma region cls::c_vec4{}

c_vec4::c_vec4(const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb && false) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

c_vec4::c_vec4 (const float _x, const float _y, const float _z, const float _w, const bool _b_verb) : m_b_verb(_b_verb), m_vec_4(_x, _y, _z, _w) {}

void c_vec4::_ctor (void) {
	
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	this->m_b_verb = true;
	this->To_str();
}

void c_vec4::Set (void) {
	
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	const float f_args[] = {1.101f, 2.202f, 3.303f, 0.101f };
	_out() += TString().Format(_T("the input args: x = %9.7f; y = %9.7f; z = %9.7f; w = %9.7f"), f_args[0], f_args[1], f_args[2], f_args[3]);

	this->ref().Set(f_args[0], f_args[1], f_args[2], f_args[3]);

	this->m_b_verb = true;
	this->To_str();
}

const
vec_4&  c_vec4::ref (void) const { return this->m_vec_4; }
vec_4&  c_vec4::ref (void)       { return this->m_vec_4; }

CString c_vec4::To_str (_pc_sz _p_prf, _pc_sz _p_sep, _pc_sz _p_sfx) const {
	_p_prf; _p_sep; _p_sfx;

	static _pc_sz pc_sz_fmt = _T("%9.7f");
	static _pc_sz pc_sz_pat = _T("[x = %s%sy = %s%sz = %s%sw = %s]");

	CString cs_out = TString().Format(pc_sz_pat,
		TString().Float(this->ref().x, t_fmt_spec::e_decimal, pc_sz_fmt), _p_sep,
		TString().Float(this->ref().y, t_fmt_spec::e_decimal, pc_sz_fmt), _p_sep,
		TString().Float(this->ref().z, t_fmt_spec::e_decimal, pc_sz_fmt), _p_sep,
		TString().Float(this->ref().w, t_fmt_spec::e_decimal, pc_sz_fmt)
	);

	if (this->m_b_verb) {
		_out() += TString().Format(_T("cls::[%s].%s() >> %s"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, (_pc_sz) cs_out);
		_out()();
	}
	return cs_out;
}

#pragma endregion