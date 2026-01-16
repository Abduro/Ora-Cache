/*
	Created by Tech_dog (eb0ntrop@gmail.com) on 09-Jan-2026 at 22:02:46.843, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL tutorials' program wrapper unit test interface implementation file.
*/
#include "ebo_test_$d$.prog.h"

using namespace ebo::boo::test::open_gl::draw;

#pragma region cls::c_prog{}

c_prog::c_prog (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb && false) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void c_prog::Grid (void) {

	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CDevCtx dev_ctx;
	CGraphCtx graph_ctx;

	if (__failed(dev_ctx.Create())) return;
	if (__failed(graph_ctx.Create(dev_ctx.Window()))) return;

	CProg prog(e_object::e_grid); prog.Opts() << CProg::COpts::e_opts::e_link << CProg::COpts::e_opts::e_use_$;

	prog.Target(e_object::e_grid); // by default, it is already set as the target of the grid, but for better readability;
	prog.Opts().Use_$(true);       // turn on the option of using the program shaders;
	prog.Opts().Link(true);        // turn on the option of linking the program;

	prog.Create();
	prog.Delete();

	graph_ctx.Delete();
	dev_ctx.Delete();

	_out()();
}

#pragma endregion