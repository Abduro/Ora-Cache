/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-Jun-2026 at 12:11:49.451, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' view background interface implementation file;
*/
#include "view.bkgnd.h"
#include "gl_procs_surface.h"
#include "gl_procs_clear.h"

using namespace open_gl::views;

using ::open_gl::procs::ver_1_1::CClear;
using ::open_gl::procs::ver_1_1::s_clear_args;

#pragma region cls::CBkgnd{}

using e_clear_ops = ex_ui::draw::open_gl::procs::CEraser::e_clear_ops;

CBkgnd::CBkgnd (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

err_code CBkgnd::Draw (void) {
	this->m_error <<__METHOD__<<__s_ok;

	using shared::gui::theme::s_flt_clr;
	const s_flt_clr& bkg_clr = ::Get_theme().Bkgnd().Float();

	// (1) sets background color;
	CClear clear;
	if (__failed(clear.All(s_clear_args(bkg_clr, 0, 1.0f))))
		this->m_error = clear.Error();

	return this->Error();
}

err_code CBkgnd::Draw_Arb (void) {
	this->m_error <<__METHOD__<<__s_ok;

	using shared::gui::theme::s_flt_clr;
	// (1) gets the background color from the registry; the background is drawn in anyway, regardless of renderer drawable object settings;
	const s_flt_clr& clr_bkgnd = ::Get_theme().Bkgnd().Float();
	
	// (1.a) sets the color for using by background eraser;
	if (__failed(::__get_eraser_procs().Clr(clr_bkgnd._red, clr_bkgnd._green, clr_bkgnd._blue, clr_bkgnd._alpha))) {
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
	// (1.b) applies the background color; the same color is also applied to the console of the debug output;
	if (__failed(::__get_eraser_procs().All(e_clear_ops::e_color|e_clear_ops::e_depth))) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) ::__get_eraser_procs().Error().Print(TError::e_print::e_req));
		return this->m_error = ::__get_eraser_procs().Error();
	}

	return this->Error();
}

TError&  CBkgnd::Error (void) const { return this->m_error; }

#pragma endregion