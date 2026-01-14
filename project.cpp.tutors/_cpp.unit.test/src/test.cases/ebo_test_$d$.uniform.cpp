/*
	Created by Tech_dog (eb0ntrop@gmail.com) on 14-Jan-2026 at 18:01:14.975, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' uniform data type wrapper unit test adapter interface implementation file.
*/
#include "ebo_test_$d$.uniform.h"

using namespace ebo::boo::test::open_gl::draw;

#pragma region cls::c_uni_enum{}

c_uni_enum::c_uni_enum (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb && false) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void c_uni_enum::Count (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CCtx_auto ctx_auto;
	if (ctx_auto.Error()) { _out()(); return; }

	CProg prog;

	// to-do this set of function calls must be moved to one method for simple call;
	prog.Target(e_object::e_grid);
	prog.Opts().UseShaders(true);
	prog.Opts().Link(true);

	prog.Create();

	CUni_enum uni_enum;
	const uint32_t u_vars = uni_enum.Count(prog.GetId());

	_out() += TString().Format(_T("Uniform vars count: %u;"), u_vars);
	_out()();
}

#pragma endregion