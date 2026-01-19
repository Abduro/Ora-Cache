/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Jan-2026 at 14:40:29.234, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL uniform data type wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$d$.uniform.h"

using namespace ebo::boo::test::open_gl::draw;

#pragma region cls::CUni_enum{}

CUni_enum::CUni_enum (const e_object _target) : TPipe(_target) {
	this->m_error >>__CLASS__<<__METHOD__<< (e_object::e_none == _target ? __e_not_inited : __s_ok);

	static _pc_sz pc_sz_pat_tgt = _T("%s cls::[%s::%s] >> the draw target is set to: '%s';");

	if (e_object::e_none == _target) {
	      _out() += TString().Format(pc_sz_pat_tgt, _T("[error]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TPipe::To_str(_target)); }
	else {_out() += TString().Format(pc_sz_pat_tgt, _T("[warn]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TPipe::To_str(_target)); }
}

uint32_t CUni_enum::Count (void) const {
	this->m_error <<__METHOD__<<__s_ok; return CUni_enum::Count(TPipe::Target(), this->m_error);
}
uint32_t CUni_enum::Count (const e_object _target, CError& _err) {
	return CUniEnum::Count(_target, _err);
}

TError&  CUni_enum::Error (void) const { return this->m_error; }

err_code CUni_enum::Get (void) {
	this->m_error <<__METHOD__<<__s_ok; return CUni_enum::Get(TPipe::Target(), this->m_vars, this->m_error);
}
err_code CUni_enum::Get (const e_object _target, TUniVars& _vars, CError& _err) {
	_target; _vars; _err;
	return CUniEnum::Get(_target, _vars, _err);
}

err_code  CUni_enum::OnDraw (void) {
	this->m_error <<__METHOD__<<__s_ok;
	return CUni_enum::OnDraw(TPipe::Target(), this->m_vars, this->m_error);
}

err_code  CUni_enum::OnDraw (const e_object _target, TUniVars& _vars, CError& _err) {
	_vars; _err;
	CFake_renderer renderer(_target);

	if (__failed(renderer.On_draw_begin())) _err = renderer.Error(); // just keeps going, no exit;

	CUniEnum::Get(_target, _vars, _err); // this is the main point of uniform variable test;

	if (__failed(renderer.On_draw_end()))  _err = renderer.Error();

	return _err;
}

const
TUniVars& CUni_enum::Vars (void) const { return this->m_vars; }

#pragma endregion
#pragma region cls::CUni_form{}

CUni_form::CUni_form (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& CUni_form::Error (void) const { return this->m_error; }

CString CUni_form::To_str (const CUniform& _u_form) {
	_u_form;
	static _pc_sz pc_sz_pat_u_form = _T("cls::[%s::%s] >> {name = %s; type = %s (0x%04x)};");

	CString cs_out;
	        cs_out.Format(pc_sz_pat_u_form, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, _u_form.Name(), (_pc_sz) _u_form.Value().Type().To_str(), _u_form.Value().Type().Get());
	return  cs_out;
}

#pragma endregion
#pragma region cls::CUni_value{}

CUni_value::CUni_value (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& CUni_value::Error (void) const { return this->m_error; }

#pragma endregion