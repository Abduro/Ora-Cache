/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Jan-2026 at 14:40:29.234, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL uniform data type wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$d$.uniform.h"

using namespace ebo::boo::test::open_gl::draw;

#pragma region cls::CTU_enum{}

CTU_enum::CTU_enum (const e_object _target) : TPipe(_target) {
	this->m_error >>__CLASS__<<__METHOD__<< (e_object::e_none == _target ? __e_not_inited : __s_ok);

	static _pc_sz pc_sz_pat_tgt = _T("%s cls::[%s::%s] >> the draw target is set to: '%s';");

	if (e_object::e_none == _target) {
	      _out() += TString().Format(pc_sz_pat_tgt, _T("[error]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TPipe::To_str(_target)); }
	else {_out() += TString().Format(pc_sz_pat_tgt, _T("[warn]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TPipe::To_str(_target)); }
}

uint32_t CTU_enum::Count (void) const {
	this->m_error <<__METHOD__<<__s_ok; return CTU_enum::Count(TPipe::Target(), this->m_error);
}
uint32_t CTU_enum::Count (const e_object _target, CError& _err) {
	_target; _err;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s() <static>:"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out()(false); // turns the logger output off;

	CCtx_auto ctx_auto(true);

	if (ctx_auto.Error()) {
		_err = ctx_auto.Error(); return 0;
	}

	CProg prog(_target); prog << CProg::e_opts::e_use_$ << CProg::e_opts::e_link;
	prog.Create();

	const uint32_t u_count = CU_vars_enum::Count(_target, _err); // this method traces its error(s) and pront out the count property result;

	_out()(true);  // turns the logger output on;
	_out() += TString().Format(_T("[impt] Uniform vars count: %u;"), u_count);
	_out()(false); // no output from destructors;
	return u_count;
}

TError&  CTU_enum::Error (void) const { return this->m_error; }
#if (0)
err_code CTU_enum::Get (void) {
	this->m_error <<__METHOD__<<__s_ok; return CTU_enum::Get(TPipe::Target(), this->m_vars, this->m_error);
}
err_code CTU_enum::Get (const e_object _target, TUniVars& _vars, CError& _err) {
	_target; _vars; _err;
	return CUniEnum::Get(_target, _vars, _err);
}

err_code  CTU_enum::OnDraw (void) {
	this->m_error <<__METHOD__<<__s_ok;
	return CTU_enum::OnDraw(TPipe::Target(), this->m_vars, this->m_error);
}

err_code  CTU_enum::OnDraw (const e_object _target, TUniVars& _vars, CError& _err) {
	_vars; _err;
	CFake_renderer renderer(_target);

	if (__failed(renderer.On_draw_begin())) _err = renderer.Error(); // just keeps going, no exit;

	CUniEnum::Get(_target, _vars, _err); // this is the main point of uniform variable test;

	if (__failed(renderer.On_draw_end()))  _err = renderer.Error();

	return _err;
}

const
TUniVars& CTU_enum::Vars (void) const { return this->m_vars; }
#endif
#pragma endregion
#pragma region cls::CUni_form{}
#if (0)
CUni_form::CUni_form (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& CUni_form::Error (void) const { return this->m_error; }

CString CUni_form::To_str (const CUniform& _u_form) {
	_u_form;
	static _pc_sz pc_sz_pat_u_form = _T("cls::[%s::%s] >> {name = %s; type = %s (0x%04x)};");

	CString cs_out;
	        cs_out.Format(pc_sz_pat_u_form, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, _u_form.Name(), (_pc_sz) _u_form.Value().Type().To_str(), _u_form.Value().Type().Get());
	return  cs_out;
}
#endif
#pragma endregion
#pragma region cls::CTU_val_v4{}

CTU_val_v4::CTU_val_v4 (const e_object _target) : TPipe(_target), m_val_v4(_target) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& CTU_val_v4::Error (void) const { return this->m_error; }

err_code CTU_val_v4::Get (const e_object _target, const uint32_t _locate, t_uniform_4f& _value, CError& _err) {
	_target; _locate; _value; _err;
	_out()(true); // it may be turned off before, but the info from this test function is useful;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s() <static>:"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CU_val_v4 vec4(_target); vec4.Locate(_locate);

	if (__failed(vec4.Get())) {
		_err = vec4.Error();
		_out() += _err.Print(TError::e_print::e_req); return _err; // no value retrieved - no sense to go ahead;
	}

	const t_uniform_4f& v4_dat = vec4.Data();

	_out() += TString().Format(_T("the value is: {%.06f;%.06f;%.06f;%.06f}"), v4_dat.at(0), v4_dat.at(1), v4_dat.at(2), v4_dat.at(3) );
	_out()(false);

	return _err;
}

err_code CTU_val_v4::Get (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	this->m_error <<__METHOD__<<__s_ok;

	C3angle tria;
	
	if (false) {}
	else if (__failed(tria.Draw())) { this->m_error = tria.Error(); }
	else if ((*this)().Is_valid() == false) { this->m_error = (*this)().Error(); _out() += this->Error().Print(TError::e_print::e_req); }
	else if (__failed((*this)().Get())) { this->m_error = (*this)().Error(); _out() += this->Error().Print(TError::e_print::e_req); }
	else {
		_out() += _T("Getting the value of uniform variable succeeded:");

		const t_uniform_4f& v4_dat = (*this)().Data();

		_out() += TString().Format(_T("the value is: {%.06f;%.06f;%.06f;%.06f}"), v4_dat.at(0), v4_dat.at(1), v4_dat.at(2), v4_dat.at(3) );
	}

	if (tria.Error() == false)
		tria.Delete();

	_out()(false); // prevents the output from triangle destructor;

	return this->Error();
}

const
CU_val_v4& CTU_val_v4::operator ()(void) const { return this->m_val_v4; }
CU_val_v4& CTU_val_v4::operator ()(void)       { return this->m_val_v4; }

#pragma endregion