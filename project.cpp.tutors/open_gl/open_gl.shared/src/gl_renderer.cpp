/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Oct-2025 at 23:43:04.685, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' draw renderer interface implementation file;
*/
#include "gl_renderer.h"
#include "shapes\gl_shape.bs.h"

#include "shared.preproc.h"
#include "sys.registry.h"
#include "color.rgb.h"

#include "procs\gl_procs_surface.h"

using namespace ex_ui::draw::open_gl;
using namespace shared::sys_core::storage;
using namespace ex_ui::color::rgb;

using e_clear_ops = procs::CEraser::e_clear_ops;
using CConvert    = ex_ui::color::rgb::CConvert; // this class has static method for converting color channel to float value;
using CHex = ex_ui::color::rgb::CHex;

/////////////////////////////////////////////////////////////////////////////
#pragma region cls::render::CCfg{}
render::CCfg:: CCfg (void) : m_opts{0}, m_flags{false} { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; this->Load();
	m_opts[1] = (uint32_t)procs::CPrimitives::e_others::e_points;
}

uint32_t render::CCfg::Count (void) const { return this->m_opts[0]; }
bool     render::CCfg::Count (const uint32_t _n_count) {
	_n_count;
	const bool b_changed = (this->Count() != _n_count);
	if (b_changed)
		this->m_opts[0] = _n_count;
	return b_changed;
}

TError&  render::CCfg::Error (void) const { return this->m_error; }

bool render::CCfg::Is_drawable (const CPipeline::e_object _target) const {
	_target;
	if (e_object::e_grid == _target) return this->m_flags[0];
	if (e_object::e_tria == _target) return this->m_flags[1];
	return false;
}

err_code  render::CCfg::Load  (void) {
	this->m_error <<__METHOD__<<__s_ok;

	using CRegDraw = shared::sys_core::storage::CReg_router::CDraw;
	using e_draw   = CRegDraw::e_targets;
	const CRegDraw& draw = ::Get_reg_router().Draw();

	TRegKeyEx reg_key;
	this->m_flags[0] = reg_key.Value().GetDword(draw.Root(), (_pc_sz) draw.Name(e_draw::e_grid)); if (reg_key.Error()) __trace_err_2(_T("%s;\n"), (_pc_sz) reg_key.Error().Print(TError::e_print::e_req));
	this->m_flags[1] = reg_key.Value().GetDword(draw.Root(), (_pc_sz) draw.Name(e_draw::e_tria)); if (reg_key.Error()) __trace_err_2(_T("%s;\n"), (_pc_sz) reg_key.Error().Print(TError::e_print::e_req));

	if (reg_key.Error()) {
		this->m_error = reg_key.Error();
	}

	return this->Error();
}

uint32_t render::CCfg::Primitive (void) const { return this->m_opts[1]; }
bool     render::CCfg::Primitive (const uint32_t _u_mode) {
	_u_mode;
	const bool b_changed = (this->Primitive() != _u_mode);
	if (b_changed)
		this->m_opts[1] = _u_mode;
	return b_changed;
}

uint32_t render::CCfg::StartAt (void) const { return this->m_opts[2]; }
bool     render::CCfg::StartAt (const uint32_t _u_ndx) {
	_u_ndx;
	const bool b_changed = (this->StartAt() != _u_ndx);
	if (b_changed)
		this->m_opts[2] = _u_ndx;
	return b_changed;
}

#pragma endregion
/////////////////////////////////////////////////////////////////////////////

CRenderer:: CRenderer (void) : m_b_allowed (false) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; ::Get_kbrd().Subscribe(this); }
CRenderer::~CRenderer (void) { ::Get_kbrd().Unsubscribe(this); }

TError&  CRenderer::IKbrd_Error (void) const { return this->Error(); }

err_code CRenderer::IKbrd_OnKeyDown (const uint32_t _v_key, const bool _b_repeat, const bool _b_extend) {
	_v_key; _b_repeat; _b_extend;
	__trace_info_2(_T("%s;\n"), (_pc_sz) IKbrd_Handler::To_str(_v_key));
	return __s_false;
}

const
render::CCfg&  CRenderer::Cfg (void) const { return this->m_cfg; }
render::CCfg&  CRenderer::Cfg (void)       { return this->m_cfg; }

err_code    CRenderer::Draw (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (false == this->Is_allowed())
		return this->Error();
	// (1) gets the background color from the registry;
	const v_color& clr_bkgnd = ::Get_theme().Bkgnd_flt();
	if (4 > clr_bkgnd.size()) {
		return this->m_error << __e_inv_arg = TString().Format(_T("#__e_inv_arg: the float color vector size = %u"), clr_bkgnd.size());
	}
	// (1.a) sets the color for using by background eraser;
	if (__failed(::__get_eraser_procs().Clr(clr_bkgnd.at(0), clr_bkgnd.at(1), clr_bkgnd.at(2), clr_bkgnd.at(3)))) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) ::__get_eraser_procs().Error().Print(TError::e_print::e_req));
		return this->m_error = ::__get_eraser_procs().Error();
	}
	/* setting e_clear_ops::e_depth for clean operation requires:
	...ensure depth testing is enabled (glEnable(GL_DEPTH_TEST)) and clear the depth buffer, at the beginning of each frame to correctly handle overlapping geometry...
	*/
#if (0)
	using e_caps = TCapsProcs::e_caps;
	if (__failed(::__get_caps_procs().Enable(true, e_caps::e_depth_tst))) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) ::__get_caps_procs().Error().Print(TError::e_print::e_req));
		return this->m_error = ::__get_caps_procs().Error();
	}
#endif
	// (1.b) applies the background color that is saved in the registry; the same color is also applied to the console of the debug output;
	if (__failed(::__get_eraser_procs().All(e_clear_ops::e_color|e_clear_ops::e_depth))) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) ::__get_eraser_procs().Error().Print(TError::e_print::e_req));
		return this->m_error = ::__get_eraser_procs().Error();
	}
	// (2) draws the viewport grid;
	this->View().Grid().Draw();

	// (3) draws the triangle;
//	::Get_shapes().Get(e_object::e_tria).Draw();

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-swapbuffers ;
	if (false == !!::SwapBuffers(this->Scene().Ctx().Draw().Target().Get())) {
		this->m_error.Last();
		__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}

//	this->Scene().Array().Unbind();
	
	return this->Error();
}

TError&     CRenderer::Error (void) const { return this->m_error; }

bool  CRenderer::Is_allowed (void) const  { return this->m_b_allowed; }
bool  CRenderer::Is_allowed (const bool _b_state) {
	_b_state;
	const bool b_changed = this->Is_allowed() != _b_state; if (b_changed) this->m_b_allowed = _b_state; return b_changed;
}
const
CScene&     CRenderer::Scene (void) const { return this->m_scene; }
CScene&     CRenderer::Scene (void)       { return this->m_scene; }
const
CViewPort&  CRenderer::View (void) const  { return this->m_view; }
CViewPort&  CRenderer::View (void)        { return this->m_view; }

TRenderer&  ::Get_renderer (void) {
	static TRenderer renderer; return renderer;
}