/*
	Created by Tech_dog (eb0ntrop@gmail.com) on 14-Jan-2026 at 18:01:14.975, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' uniform data type wrapper unit test adapter interface implementation file.
*/
#include "ebo_test_$d$.uniform.h"

using namespace ebo::boo::test::open_gl::draw;

#pragma region cls::c_uni_enum{}

c_uni_enum::c_uni_enum (const e_object _target, const bool _b_verb) : m_b_verb(_b_verb), m_pipe(_target) {
	if (this->m_b_verb && false) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
	static _pc_sz pc_sz_pat_tgt = _T("%s cls::[%s::%s] >> the draw target is set to: '%s';");

	if (e_object::e_none == _target) {
	      _out() += TString().Format(pc_sz_pat_tgt, _T("[error]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TPipe::To_str(_target)); }
	else {_out() += TString().Format(pc_sz_pat_tgt, _T("[warn]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TPipe::To_str(_target)); }
}

void c_uni_enum::Count (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CCtx_auto ctx_auto;
	if (ctx_auto.Error()) { _out()(); return; }

	CProg prog((*this)()); prog << CProg::e_opts::e_use_$ << CProg::e_opts::e_link;

	prog.Create();

	CUni_enum uni_enum((*this)());
	const uint32_t u_vars = uni_enum.Count();

	prog.Delete();

	_out() += TString().Format(_T("Uniform vars count: %u;"), u_vars);
	_out()();
}

void c_uni_enum::Get (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CCtx_auto ctx_auto;
	if (ctx_auto.Error()) { _out()(); return; }

	CProg prog((*this)()); prog << CProg::e_opts::e_use_$ << CProg::e_opts::e_link;

	prog.Create();

	CUni_enum uni_enum((*this)()); uni_enum.Get();

	prog.Delete();

	_out() += TString().Format(_T("Uniform vars count: %u;"), uni_enum.Vars().size());
	for (uint32_t i_ = 0; i_ < uni_enum.Vars().size(); i_++)
	_out() += CUni_form::To_str(uni_enum.Vars().at(i_));
	_out()();
}

void c_uni_enum::OnDraw (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CUni_enum uni_enum((*this)()); uni_enum.OnDraw();

	_out() += TString().Format(_T("Uniform vars count: %u;"), uni_enum.Vars().size());
	for (uint32_t i_ = 0; i_ < uni_enum.Vars().size(); i_++)
	_out() += CUni_form::To_str(uni_enum.Vars().at(i_));
	_out()();
}

const
TPipe&  c_uni_enum::Pipe (void) const { return this->m_pipe; }
TPipe&  c_uni_enum::Pipe (void)       { return this->m_pipe; }

const
TPipe&  c_uni_enum::operator ()(void) const { return this->Pipe(); }
TPipe&  c_uni_enum::operator ()(void)       { return this->Pipe(); }

#pragma endregion