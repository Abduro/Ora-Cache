/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Oct-2025 at 23:43:04.685, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' draw renderer interface implementation file;
*/
#include "gl_renderer.h"
#include "shared.preproc.h"

#include "procs\gl_procs_surface.h"

using namespace ex_ui::draw::open_gl;

using e_clear_ops = procs::CEraser::e_clear_ops;

CRenderer:: CRenderer (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CRenderer::~CRenderer (void) {}

err_code    CRenderer::Draw (void) const {
	this->m_error <<__METHOD__<<__s_ok;

	if (__failed(::__get_eraser_procs().All(e_clear_ops::e_color|e_clear_ops::e_depth))) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) ::__get_eraser_procs().Error().Print(TError::e_print::e_req));
		return this->m_error = ::__get_eraser_procs().Error();
	}

	return this->Error();
}

TError&     CRenderer::Error (void) const { return this->m_error; }
const
CScene&     CRenderer::Scene (void) const { return this->m_scene; }
CScene&     CRenderer::Scene (void)       { return this->m_scene; }
const
CViewPort&  CRenderer::View (void) const  { return this->m_view; }
CViewPort&  CRenderer::View (void)        { return this->m_view; }