/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Oct-2025 at 23:43:04.685, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' draw renderer interface implementation file;
*/
#include "gl_renderer.h"
#include "shared.preproc.h"

#include "procs\gl_procs_surface.h"

using namespace ex_ui::draw::open_gl;

using e_clear_ops = procs::CEraser::e_clear_ops;

/////////////////////////////////////////////////////////////////////////////

CRender_Cfg:: CRender_Cfg (void) : m_count_ndx(0), m_prim_mode((uint32_t)procs::CPrimitives::e_others::e_points), m_start_ndx(0) {}

uint32_t CRender_Cfg::Count (void) const { return this->m_count_ndx; }
bool     CRender_Cfg::Count (const uint32_t _n_count) {
	_n_count;
	const bool b_changed = (this->Count() != _n_count);
	if (b_changed)
		this->m_count_ndx = _n_count;
	return b_changed;
}

uint32_t CRender_Cfg::Primitive (void) const { return this->m_prim_mode; }
bool     CRender_Cfg::Primitive (const uint32_t _u_mode) {
	_u_mode;
	const bool b_changed = (this->Primitive() != _u_mode);
	if (b_changed)
		this->m_prim_mode = _u_mode;
	return b_changed;
}

uint32_t CRender_Cfg::StartAt (void) const { return this->m_start_ndx; }
bool     CRender_Cfg::StartAt (const uint32_t _u_ndx) {
	_u_ndx;
	const bool b_changed = (this->StartAt() != _u_ndx);
	if (b_changed)
		this->m_start_ndx = _u_ndx;
	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

CRenderer:: CRenderer (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CRenderer::~CRenderer (void) {}

const
CRender_Cfg&  CRenderer::Cfg (void) const { return this->m_cfg; }
CRender_Cfg&  CRenderer::Cfg (void)       { return this->m_cfg; }

err_code    CRenderer::Draw (void) const {
	this->m_error <<__METHOD__<<__s_ok;

	if (__failed(::__get_eraser_procs().All(e_clear_ops::e_color|e_clear_ops::e_depth))) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) ::__get_eraser_procs().Error().Print(TError::e_print::e_req));
		return this->m_error = ::__get_eraser_procs().Error();
	}

	if (__failed(__get_render_procs().DrawArrays(this->Scene().Prog().Id().Get(), this->Cfg().Primitive(), this->Cfg().StartAt(), this->Cfg().Count()))) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) ::__get_render_procs().Error().Print(TError::e_print::e_req));
		return this->m_error = ::__get_render_procs().Error();
	}
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-swapbuffers ;
	if (false == !!::SwapBuffers(this->Scene().Ctx().Device().Target().Get())) {
		this->m_error.Last();
		__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
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