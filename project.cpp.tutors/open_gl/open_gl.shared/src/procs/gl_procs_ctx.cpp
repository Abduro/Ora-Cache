/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Oct-2025 at 17:42:56.321, (UTC+4), Batumi, Saturday;
	This is Ebo Pack OpenGL context functions' loader interface implementation file;
*/
#include "gl_procs_ctx.h"
#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::procs;

static _pc_sz ctx_fun_names[] = { _T("wglChoosePixelFormatARB"), _T("wglCreateContextAttribsARB"), _T("wglSwapIntervalEXT") };

CContext:: CContext (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}

// https://www.khronos.org/opengl/wiki/Creating_an_OpenGL_Context_(WGL) ;
int32_t  CContext::ChoosePxFormatArb (HDC _h_dc, const int* _p_atts_i, const float* _p_atts_f, uint32_t _u_max_fmts, int* _p_fmts, uint32_t* _p_fmt_count) {
	_h_dc; _p_atts_i; _p_atts_f; _u_max_fmts; _p_fmts; _p_fmt_count;
	// it returns: 0 - this is the failure, otherwise the result value > 0, that means success;
	CBase::m_error << __METHOD__ << __s_ok;

	int32_t n_result = 0; // this is the failure result; in case of unsuccessful loading the function it will be returned to the caller;
	
	// this is the function for creating draw renderer context;
	pfn_ChoosePxFormatArb p_fun = reinterpret_cast<pfn_ChoosePxFormatArb>(CBase::Get(ctx_fun_names[0]));
	if (nullptr == p_fun)
		return n_result; // needs to be figured out of what result should be returned in case of failure; (done)

	n_result = p_fun(_h_dc, _p_atts_i, _p_atts_f, _u_max_fmts, _p_fmts, _p_fmt_count);

	return n_result;
}

#pragma region _defs
// from win32_platform.h
#define ERROR_INVALID_VERSION_ARB 0x2095
#define ERROR_INVALID_PROFILE_ARB 0x2096

#define __err_inv_ctx     ERROR_DC_NOT_FOUND        
#define __err_inv_pxl_fmt ERROR_INVALID_PIXEL_FORMAT
#define __err_inv_oper    ERROR_INVALID_OPERATION   
#define __err_no_sys_res  ERROR_NO_SYSTEM_RESOURCES 
#define __err_inv_param   ERROR_INVALID_PARAMETER   
#define __err_inv_ver_arb ERROR_INVALID_VERSION_ARB 
#define __err_inv_profile ERROR_INVALID_PROFILE_ARB 
#pragma endregion
// https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_create_context.txt ;
HGLRC    CContext::CreateCtxAttsArb (HDC _h_dc, HGLRC _h_shared_ctx, const int* p_att_lst) {
	_h_dc; _h_shared_ctx; p_att_lst;
	// on failure returns nullptr; extended error information can be obtained with GetLastError() ;
	/* Possible error codes:
		ERROR_DC_NOT_FOUND        : _h_dc is not a valid device context handle ;
		ERROR_INVALID_PIXEL_FORMAT: the pixel format associated with _h_dc does not support OpenGL contexts providing the requested API major and minor version, forward-compatible flag ;
		ERROR_INVALID_OPERATION   : _h_shared_ctx is neither zero nor a valid context handle ;
		ERROR_INVALID_OPERATION   : _h_shared_ctx was created on a different device context than the one referenced by _h_dc ; or if the contexts are otherwise incompatible ;
		ERROR_NO_SYSTEM_RESOURCES : the OpenGL server does not have enough resources to allocate the new context ;
		ERROR_INVALID_PARAMETER   : an unrecognized attribute is present in attribute list p_att_lst ;
		ERROR_INVALID_VERSION_ARB : the major and minor attributes of the version with compatible bit specify non-exist version ;
		ERROR_INVALID_PROFILE_ARB : WGL_CONTEXT_PROFILE_MASK_ARB has no bits set;
			it has any bits set other than WGL_CONTEXT_CORE_PROFILE_BIT_ARB and WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB ;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	HGLRC h_render = nullptr;

	pfn_CreateCtxAttsArb p_fun = reinterpret_cast<pfn_CreateCtxAttsArb>(CBase::Get(ctx_fun_names[1]));
	if (nullptr == p_fun)
		return h_render;

	h_render = p_fun(_h_dc, _h_shared_ctx, p_att_lst);

	switch (CErr_ex().Get_last(false)) {
	case __err_inv_ctx : CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_dc_n_found: device context invalid")); break;
	case __err_inv_pxl_fmt : CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_pxl_fmt: pixel format invalid")); break;
	case __err_inv_oper : {
	//		if (0 != _h_shared_ctx) // there is no need to check the general context for its validity or anything like that;
				CBase::m_error <<(err_code)TErrCodes::eExecute::eOperate = TString().Format(_T("#__e_inv_oper: shared context invalid"));
		} break;
	case __err_no_sys_res : CBase::m_error <<(err_code)TErrCodes::eExecute::eEnviron = TString().Format(_T("#__e_no_sys_res: no system resources")); break;
	case __err_inv_param : CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_param: one of the attribute params is invalid")); break;
	case __err_inv_ver_arb : CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_vers: arb version is not valid")); break;
	case __err_inv_profile : CBase::m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_prof: arb profile is not valid")); break;
	default:;
	}

	return h_render;
}
// https://www.khronos.org/opengl/wiki/Swap_Interval ;
bool  CContext::SwapIntervalExt (const int _n_interval) {
	_n_interval;
	/* Possible error reasons:
		- PFD_DOUBLEBUFFER must be set, but it is not;
		- the required OpenGL is not installed;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	int32_t n_result = 0;

	pfn_SwapIntervalExt p_fun = reinterpret_cast<pfn_SwapIntervalExt>(CBase::Get(ctx_fun_names[2]));
	if (nullptr == p_fun)
		return n_result; // needs to be figured out of what result should be returned in case of failure;

	n_result = p_fun(_n_interval);
	return !!n_result;
}

err_code CContext::Get_all (void) {
	CBase::m_error << __METHOD__ << __s_ok;

	for (uint32_t i_ = 0; i_ < _countof(ctx_fun_names); i_++) {
		if (nullptr == CBase::Get(ctx_fun_names[i_]))
			break;
	}

	return CBase::Error();
}

TCtxProcs&  ::__get_ctx_procs (void) {
	static TCtxProcs procs;
	static bool b_loaded = false;

	if (false == b_loaded) {
		if (__failed(procs.Get_all())) {
			__trace_err_2(_T("%s;\n"), (_pc_sz) procs.Error().Print(TError::e_print::e_req)); }
		else
			b_loaded = true;
	}
	return procs;
}