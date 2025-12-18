/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Dec-2025 at 10:50:26.070, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL drawable components' interface implementation file;
*/
#include "gl_drawable.h"

#include "shared.dbg.h"
#include "shared.preproc.h"
#include "shared.theme.h"
#include "sys.registry.h"

#include "procs\gl_procs_surface.h"

#include "color._defs.h"

using namespace ex_ui::draw::open_gl;

#pragma region cls::CBkgnd{}

using e_clear_ops = procs::CEraser::e_clear_ops;

CBkgnd:: CBkgnd (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CBkgnd::~CBkgnd (void) {}

err_code CBkgnd::Draw (void) {
	this->m_error <<__METHOD__<<__s_ok;

	// (1) gets the background color from the registry; the background is drawn in anyway, regardless of renderer drawable object settings;
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
	// (1.b) applies the background color; the same color is also applied to the console of the debug output;
	if (__failed(::__get_eraser_procs().All(e_clear_ops::e_color|e_clear_ops::e_depth))) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) ::__get_eraser_procs().Error().Print(TError::e_print::e_req));
		return this->m_error = ::__get_eraser_procs().Error();
	}

	return this->Error();
}

TError&  CBkgnd::Error (void) const { return this->m_error; }

#pragma endregion