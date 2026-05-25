/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Jan-2026 at 22:19:29.729, UTC+4, Batumi, Thursday;
	This is OpenGL draw renderer wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$d$.render.h"
#include "gl_drawable.h"

using namespace test::open_gl::draw;
using namespace test::open_gl::prog;

#pragma region cls::CTstRenderer{}

CTstRenderer::CTstRenderer (const e_object _target) : TPipe(_target) {

	static _pc_sz pc_sz_pat_tgt = _T("%s cls::[%s::%s] >> the draw target is set to: '%s';");

	if (e_object::e_none == _target) {
	      _out() += TString().Format(pc_sz_pat_tgt, _T("[error]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TPipe::To_str(_target)); }
	else {_out() += TString().Format(pc_sz_pat_tgt, _T("[warn]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, TPipe::To_str(_target)); }
}

err_code CTstRenderer::Draw (void) {	
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed(this->m_graph.Create()))
		return this->m_graph().Error();

	CProg prog(this->Target()); prog << CProg::e_opts::e_use_$ << CProg::e_opts::e_link;

	// on possible error case the exiting from this function is reasonable, but what is about deleting the prog object?

	if (__failed(prog.Create())) { _out() += prog.Error(); return prog.Error(); }
	if (__failed(prog.Use())) { _out() += prog.Error();
		if (__failed(prog.Delete())) _out() += prog.Error(); return prog.Error();
	}

#if (0)
	if (__failed(renderer.Draw())) { _err = renderer.Error()};
#else
	::open_gl::views::CBkgnd bkgnd;
	if (__failed(bkgnd.Draw())) { _out() += bkgnd.Error(); return bkgnd.Error(); }
#endif
	if (__failed(this->m_graph.Swap())) {
		_out() += this->m_graph().Error(); return this->m_graph().Error();
	}

	prog.Delete(); // a possible error is held by the program object itself and is not important at the end of this procedure;
	return __s_ok;
}

err_code CTstRenderer::On_draw_begin (void) {

	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (this->m_graph().Error()) {
		_out() += this->m_graph().Error(); return this->m_graph().Error();
	}

	CProg prog((*this)()); prog << CProg::e_opts::e_use_$ << CProg::e_opts::e_link;

	if (__failed(prog.Create())) { _out() += prog.Error(); return prog.Error(); }
	if (__failed(prog.Use())) { _out() += prog.Error();
		if (__failed(prog.Delete())) _out() += prog.Error(); return prog.Error();
	}
#if (0) // drawing the background does not use shaders; so it is useless;
	CBkgnd bkgnd;
	if (__failed(bkgnd.Draw())) { this->m_error = bkgnd.Error(); }
#endif;
	if (__failed(::Get_shapes().Defaults().SetTo(e_object::e_tria))) {
		_out() += ::Get_shapes().Defaults().Error(); // just traces the error, no return from this proc yet;
	}

	shapes::CShape& tria = ::Get_shapes().Get(e_object::e_tria);
	if (__failed(tria.Draw())) {
		_out() += tria.Error(); return tria.Error();
	}

	return __s_ok;
}

err_code CTstRenderer::On_draw_end (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed(this->m_graph.Swap())) {
		_out() += this->m_graph().Error(); // just keeping going ahead; the swap is the final point of draw operation, but the program must be deleted;
	}

	CProg prog((*this)());

	if (__failed(prog.Delete())) { _out() += prog.Error(); return prog.Error(); }

	return __s_ok;
}

const
TPipe& CTstRenderer::operator ()(void) const { return (TPipe&)*this; }
TPipe& CTstRenderer::operator ()(void)       { return (TPipe&)*this; }

#pragma endregion