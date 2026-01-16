/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Jan-2026 at 22:19:29.729, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL draw renderer wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$d$.render.h"
#include "gl_drawable.h"

using namespace ebo::boo::test::open_gl::draw;

#pragma region cls::CFake_renderer{}

CFake_renderer::CFake_renderer (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

const
CCtx_auto& CFake_renderer::Ctx (void) const { return this->m_ctx_auto; }
CCtx_auto& CFake_renderer::Ctx (void)       { return this->m_ctx_auto; }

err_code CFake_renderer::Draw (void) {
	this->m_error <<__METHOD__<<__s_ok; return CFake_renderer::Draw(this->m_error);
}

err_code CFake_renderer::Draw (CError& _err) {
	_err;
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CCtx_auto ctx_auto;
	if (ctx_auto.Error())
		return _err = ctx_auto.Error();

	CProg prog(e_object::e_grid); prog << CProg::e_opts::e_use_$ << CProg::e_opts::e_link;

	// on possible error case the exiting from this function is reasonable, but what is about deleting the prog object?

	if (__failed(prog.Create())) { return _err = prog.Error(); }
	if (__failed(prog.Use())) { prog.Delete(); return _err = prog.Error(); }

#if (0)
	if (__failed(renderer.Draw())) { _err = renderer.Error()};
#else
	CBkgnd bkgnd;
	if (__failed(bkgnd.Draw())) { _err = bkgnd.Error(); }

	CGraphCtx graph;
	if (__failed(graph.Swap())) { _err = graph.Error(); }
#endif

	prog.Delete(); // a possible error is held by the program object itself and is not important at the end of this procedure;
	return _err;
}

TError&  CFake_renderer::Error (void) const { return this->m_error; }

err_code CFake_renderer::On_draw_begin (void) {

	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (this->Ctx().Error()) return this->m_error = this->Ctx().Error();

	CProg prog(e_object::e_grid); prog << CProg::e_opts::e_use_$ << CProg::e_opts::e_link;

	if (__failed(prog.Create())) { return this->m_error = prog.Error(); }
	if (__failed(prog.Use())) { return this->m_error = prog.Error(); }

	CBkgnd bkgnd;
	if (__failed(bkgnd.Draw())) { this->m_error = bkgnd.Error(); }

	return this->Error();
}

err_code CFake_renderer::On_draw_end (void) {
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed(this->Ctx().Graph().Swap())) { this->m_error = this->Ctx().Graph().Error(); } // just keeping going ahead; the swap is the final point of draw operation;

	CProg prog(e_object::e_grid);

	if (__failed(prog.Delete())) this->m_error = prog.Error();

	return this->Error();
}

#pragma endregion