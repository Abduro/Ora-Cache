/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Jan-2026 at 22:19:29.729, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL draw renderer wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$d$.render.h"
#include "gl_drawable.h"

using namespace ebo::boo::test::open_gl::draw;

#pragma region cls::CFake_renderer{}

CFake_renderer::CFake_renderer (const e_object _target) : TPipe(_target) {
	this->m_error >>__CLASS__<<__METHOD__<< (e_object::e_none == _target ? __e_not_inited : __s_ok);

	static _pc_sz pc_sz_pat_tgt = _T("%s cls::[%s::%s] >> the draw target is set to: '%s';");

	if (e_object::e_none == _target) {
	      _out() += TString().Format(pc_sz_pat_tgt, _T("[error]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TPipe::To_str(_target)); }
	else {_out() += TString().Format(pc_sz_pat_tgt, _T("[warn]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TPipe::To_str(_target)); }
}

const
CCtx_auto& CFake_renderer::Ctx (void) const { return this->m_ctx_auto; }
CCtx_auto& CFake_renderer::Ctx (void)       { return this->m_ctx_auto; }

err_code CFake_renderer::Draw (void) {
	this->m_error <<__METHOD__<<__s_ok; return CFake_renderer::Draw((*this)(), this->m_error);
}

err_code CFake_renderer::Draw (const e_object _target, CError& _err) {
	_target; _err;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s() <static>:"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CCtx_auto ctx_auto;
	if (ctx_auto.Error())
		return _err = ctx_auto.Error();

	CProg prog(_target); prog << CProg::e_opts::e_use_$ << CProg::e_opts::e_link;

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

	CProg prog((*this)()); prog << CProg::e_opts::e_use_$ << CProg::e_opts::e_link;

	if (__failed(prog.Create())) { return this->m_error = prog.Error(); }
	if (__failed(prog.Use())) { return this->m_error = prog.Error(); }
#if (0) // drawing the background does not use shaders; so it is useless;
	CBkgnd bkgnd;
	if (__failed(bkgnd.Draw())) { this->m_error = bkgnd.Error(); }
#endif;
	if (__failed(::Get_shapes().Defaults().SetTo(e_object::e_tria))) {
		this->m_error = ::Get_shapes().Defaults().Error();
		_out()(this->Error()); // just traces the error, no return from this proc yet;
	}

	shapes::CShape& tria = ::Get_shapes().Get(e_object::e_tria);
	if (__failed(tria.Draw())) {
		this->m_error = tria.Error();
		_out()(this->Error()); // just traces the error, no return from this proc yet;
	}

	return this->Error();
}

err_code CFake_renderer::On_draw_end (void) {
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed(this->Ctx().Graph().Swap())) { this->m_error = this->Ctx().Graph().Error(); } // just keeping going ahead; the swap is the final point of draw operation;

	CProg prog((*this)());

	if (__failed(prog.Delete())) this->m_error = prog.Error();

	return this->Error();
}

const
TPipe& CFake_renderer::operator ()(void) const { return (TPipe&)*this; }
TPipe& CFake_renderer::operator ()(void)       { return (TPipe&)*this; }

#pragma endregion