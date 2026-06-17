/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Jun-2026 at 10:01:06.662, UTC+4, Batumi, Wednesday;
	This is OpenGL ver.1.1 buffers' swap wrapper interface implementation file;
*/
#include "gl_procs_vsync.h"

using namespace ::open_gl::procs::utils::ver_1_1;

#pragma region cls::CVSync{}

static _pc_sz p_vsync_func_name_get = _T("wglGetSwapIntervalEXT");
static _pc_sz p_vsync_func_name_set = _T("wglSwapIntervalEXT");

static _pc_sz p_err_no_dc_found = _T("The driver cannot obtain a Device Context (DC) to query the interval");
static _pc_sz p_err_no_rc_bound = _T("Rendering Context (RC) is not currently bound or made current to the calling thread");

CVSync::CVSync (void) { TBase::m_error >>__CLASS__; }

int32_t  CVSync::Get (void) {
	/* possible error codes:
	ERROR_DC_NOT_FOUND:  An OpenGL Rendering Context (RC) is not currently bound or made current to the calling thread. The driver cannot obtain a Device Context (DC) to query the interval.
	ERROR_INVALID_DATA:  The 'interval' parameter is negative.
	*/
	TBase::m_error <<__METHOD__<<__s_ok;

	int32_t n_intervals = 0;

	pfn_GetSwapInterval p_fun = reinterpret_cast<pfn_GetSwapInterval>(TBase::Get(p_vsync_func_name_get));
	if (nullptr == p_fun)
		return n_intervals;

	n_intervals = p_fun();
	const
	dword  u_err_code = CErr_ex().Get_code();
	switch(u_err_code){
	case ERROR_DC_NOT_FOUND: (TBase::m_error = u_err_code) = p_err_no_dc_found; break;
	case GL_INVALID_OPERATION : (TBase::m_error = u_err_code) = p_err_inv_oper; break;
	default:
		if (!!u_err_code)
			TBase::m_error <<__e_fail = TString().Format(p_err_unk_code,  u_err_code,  u_err_code);
	}

	return n_intervals;
}

err_code CVSync::Set (const uint32_t _intervals) {
	_intervals;
	/* possible error codes:
	ERROR_DC_NOT_FOUND:  An OpenGL Rendering Context (RC) is not currently bound or made current to the calling thread. The driver cannot obtain a Device Context (DC) to query the interval.
	ERROR_INVALID_DATA:  The 'interval' parameter is negative.
	*/
	TBase::m_error <<__METHOD__<<__s_ok;

	pfn_SetSwapInterval p_fun = reinterpret_cast<pfn_SetSwapInterval>(TBase::Get(p_vsync_func_name_set));
	if (nullptr == p_fun)
		return TBase::Error();

	p_fun(_intervals);
	const
	dword  u_err_code = CErr_ex().Get_code();
	switch(u_err_code){
	case ERROR_DC_NOT_FOUND: (TBase::m_error = u_err_code) = p_err_no_dc_found; break;
	case ERROR_INVALID_DATA: (TBase::m_error = u_err_code) = TString().Format(_T("#__e_inv_arg: 'interval' (%d) is not valid"), _intervals); break; // cannot occur because input arg is unsigned;
	case GL_INVALID_OPERATION : (TBase::m_error = u_err_code) = p_err_inv_oper; break;
	default:
		if (!!u_err_code)
			TBase::m_error <<__e_fail = TString().Format(p_err_unk_code,  u_err_code,  u_err_code);
	}

	return TBase::Error();
}

#pragma endregion