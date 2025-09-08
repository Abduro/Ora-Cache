/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Aug-2025 at 12:00:00.987, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL error handler adapter interface implementation file;
*/
#include "gl_error.h"
#include "gl_defs.h"

#pragma comment(lib, "shared.trim_v15.lib") // it is required for usage of the error base API;

using namespace ex_ui::draw::open_gl;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl_1 { void __warning_lnk_4221 (void) {}}}}}

// https://www.khronos.org/opengl/wiki/Debug_Output ; enumerates all constants related to debug output and/or error handling;
// https://registry.khronos.org/OpenGL/extensions/KHR/KHR_debug.txt ; looks like the origin of the error callback;

// this is useful for debug callbacks only ;
#define dbg_src_api             0x8246
#define dbg_src_window_system   0x8247
#define dbg_src_shader_compiler 0x8248
#define dbg_src_third_party     0x8249
#define dbg_src_application     0x824A
#define dbg_src_other           0x824B

// https://www.khronos.org/opengl/wiki/OpenGL_Error ;

#define err_none       GL_NO_ERROR          // 0x0     ;
#define err_inv_enum   GL_INVALID_ENUM      // 0x0500  ;
#define err_inv_value  GL_INVALID_VALUE     // 0x0501  ;
#define err_inv_oper   GL_INVALID_OPERATION // 0x0502  ;
#define err_stk_over   GL_STACK_OVERFLOW    // 0x0503  ;
#define err_stk_under  GL_STACK_UNDERFLOW   // 0x0504  ;
#define err_out_mem    GL_OUT_OF_MEMORY     // 0x0505  ;
#define err_inv_frame  0x0506               // GL_INVALID_FRAMEBUFFER_OPERATION ;   
#define err_ctx_lost   0x0507               // GL_CONTEXT_LOST ;  
#define err_tbl_large  0x8031               // GL_TABLE_TOO_LARGE ;  

CError_ex:: CError_ex (void) : TBase(), m_err_code(0) {}
CError_ex::~CError_ex (void) {}

#define err_dev_reset  DXGI_ERROR_DEVICE_RESET
#define err_acc_denied DXGI_ERROR_ACCESS_DENIED

uint32_t  CError_ex::Get_code (void) const { return this->m_err_code; }

#include <winnt.h>

err_code  CError_ex::Get_last (const bool _b_origin) const {
	_b_origin;
	// https://learn.microsoft.com/en-us/windows/win32/opengl/glgeterror?source=docs ;
	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/glGetError.xhtml ; the same error codes and the error description;
	// https://lmb.informatik.uni-freiburg.de/people/reisert/opengl/doc/glGetError.html ; it looks like the long story :-D

	bool b_origin_ = _b_origin; // actually this is the custom description of the error, that is assigned here, of course the description text was copied from the offcial websites;

	CString cs_desc;
	err_code n_result = __e_not_impl;

	this->m_err_code = ::glGetError();
	switch (this->m_err_code) { // in the most cases of the error occurs the DirectX error code is used; but error description is still kept original;
	case err_ctx_lost  : { n_result = err_dev_reset ; cs_desc = _T("The context has been lost, due to a graphics card reset."); } break;
	case err_inv_enum  : { n_result = __e_inv_arg   ; cs_desc = _T("An unacceptable value is specified for an enumerated argument."); } break;
	case err_inv_frame : { n_result = err_acc_denied; cs_desc = _T("Attempting to read from or write/render to a framebuffer failed."); } break;
	case err_inv_value : { n_result = __e_inv_arg   ; cs_desc = _T("A numeric argument is out of range."); } break;
	case err_inv_oper  : { n_result = (err_code) TErrCodes::eExecute::eFunction; cs_desc = _T("The specified operation is not allowed in the current state."); } break;
	case err_none      : { n_result = __s_ok; cs_desc = _T("No error has been recorded."); } break;
	case err_out_mem   : { n_result = __e_no_memory ; cs_desc = _T("There is not enough memory left to execute the command."); } break;
	// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-erref/596a1078-e883-4972-9bbc-49e60bebca55 ;
	case err_stk_over  : { n_result = __DwordToHresult(STATUS_STACK_OVERFLOW); cs_desc = _T("This command would cause a stack overflow."); } break;
	// https://learn.microsoft.com/en-us/cpp/sanitizers/error-stack-buffer-underflow ;
	case err_stk_under : { n_result = __e_index; cs_desc = _T("This command would cause a stack underflow."); } break; // not sure if the error code is correct for this kind of error;
	// https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glGetError.xml ;
	case err_tbl_large : { n_result = __e_no_memory; cs_desc = _T("The specified table exceeds the maximum supported table size."); } break; // not sure if the error code is correct for this kind of error;
	default:
		b_origin_ = true; // unrecognized error code description must be shown;
		n_result = (err_code) TErrCodes::eData::eInvalid; cs_desc = TString().Format(_T("#undef: 0x%04x"), this->m_err_code);
	}

	CError& base_ref = const_cast<CError&>((*this)());
	base_ref << n_result;
	if (b_origin_)
		base_ref = (_pc_sz) cs_desc;

	return (*this)();
}

const
CError&   CError_ex::operator ()(void) const { return (const TBase&)*this; }
CError&   CError_ex::operator ()(void)       { return (TBase&)*this; }

// useful for debug callback only; it is temporarily postponed;
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