/*
	Created by Tech_dog (eb0ntrop@gmail.com) on 09-Jan-2026 at 22:02:46.843, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL tutorials' program wrapper unit test interface implementation file.
*/
#include "ebo_test_$d$.prog.h"

using namespace ebo::boo::test::open_gl::draw;

#pragma region cls::c_prog{}

c_prog::c_prog (const e_object _target, const bool _b_verb) : m_pipe(_target), m_b_verb(_b_verb) {
	if (this->m_b_verb && false) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void c_prog::Grid (void) {

	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CCtx_auto ctx_auto;
	if (ctx_auto.Error()) return; // the error is already traced by one of the context objects;

	CProg prog(e_object::e_grid); prog.Opts() << CProg::COpts::e_opts::e_link << CProg::COpts::e_opts::e_use_$;

	prog.Create();
	prog.Delete();

	_out()();
}

void c_prog::Tria (void) {

	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CCtx_auto ctx_auto;
	if (ctx_auto.Error()) return; // the error is already traced by one of the context objects;

	CProg prog(e_object::e_tria); prog.Opts() << CProg::COpts::e_opts::e_link << CProg::COpts::e_opts::e_use_$;

	prog.Create();
	prog.Delete();

	_out()();
}
#pragma endregion