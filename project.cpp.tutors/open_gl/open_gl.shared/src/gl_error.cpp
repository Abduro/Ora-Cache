/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Aug-2025 at 12:00:00.987, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL error handler adapter interface implementation file;
*/
#include "gl_error.h"

#pragma comment(lib, "shared.trim_v15.lib") // it is required for usage of the error base API;

using namespace ex_ui::draw::open_gl;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl_1 { void __warning_lnk_4221 (void) {}}}}}

// https://www.khronos.org/opengl/wiki/Debug_Output ; enumerates all constants related to debug output and/or error handling;
// https://registry.khronos.org/OpenGL/extensions/KHR/KHR_debug.txt ; looks like the origin of the error callback;

#define dbg_src_api             0x8246
#define dbg_src_window_system   0x8247
#define dbg_src_shader_compiler 0x8248
#define dbg_src_third_party     0x8249
#define dbg_src_application     0x824A
#define dbg_src_other           0x824B

CError_ex:: CError_ex (void) : TBase() {}
CError_ex::~CError_ex (void) {}

const
CError&   CError_ex::operator ()(void) const { return (const TBase&)*this; }
CError&   CError_ex::operator ()(void)       { return (TBase&)*this; }

CString   CErr_src::Src_to_str(const uint32_t _u_cat) {
	_u_cat;
	CString cs_src;
	switch (_u_cat) {
	case dbg_src_api             : cs_src = _T("$src_api") ; break;
	case dbg_src_window_system   : cs_src = _T("$wnd_sys") ; break;
	case dbg_src_shader_compiler : cs_src = _T("$sh_comp") ; break;
	case dbg_src_third_party     : cs_src = _T("$3d_party"); break;
	case dbg_src_application     : cs_src = _T("$this_app"); break;
	case dbg_src_other           : cs_src = _T("$unknown") ; break;
	default:
		cs_src = _T("#undef");
	}

	return  cs_src;
}