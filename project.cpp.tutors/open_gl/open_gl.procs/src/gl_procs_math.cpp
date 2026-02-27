/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-Jan-2026 at 21:34:55.786, (UTC+4), Batumi, Monday;
	This is Ebo Pack OpenGL math functions' loader interface implementation file;
*/
#include "gl_procs_math.h"
#include "gl_procs.h"

#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::procs;
using namespace ex_ui::draw::open_gl::procs::math;

#pragma region cls::CMatrix

static _pc_sz mat_fun_names[] = {
	_T("glLoadIdentity"), _T("glLoadMatrixf")
};
enum class e_mat_fun_ndx : uint32_t {
	e_identity = 0x0, e_load, e_load_trans
};

CMatrix::CMatrix (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}

err_code CMatrix::Get (const e_mat_type _type, t_arr_4x4& _mat_4x4) {
	_type; _mat_4x4;
	CBase::m_error << __METHOD__ << __s_ok;

	if (__failed(::__get_param_procs().Get_ptr((uint32_t)_type, _mat_4x4.data())))
		CBase::m_error = ::__get_param_procs().Error();

	return CBase::Error();
}

err_code CMatrix::Get_all (void) {
	CBase::m_error << __METHOD__ << __s_ok;

	for (uint32_t i_ = 0; i_ < _countof(mat_fun_names); i_++) {
		if (nullptr == CBase::Get(mat_fun_names[i_]))
			break;
	}

	return CBase::Error();
}

err_code CMatrix::Identity (void) {
	/* Possible error codes:
	GL_INVALID_OPERATION : glMatrixMode() is executed between the execution of glBegin() and the corresponding execution of glEnd();
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Identity p_fun = reinterpret_cast<pfn_Identity>(CBase::Get(mat_fun_names[(uint32_t)e_mat_fun_ndx::e_identity]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun();
	const
	uint32_t u_err_code = CErr_ex().Get_code();
	switch ( u_err_code ){
	case GL_INVALID_OPERATION : CBase::m_error << __e_not_expect = _T("#__e_state: Invalid state for selecting an identity matrix"); break;
	default:
		if (!!u_err_code)
			CBase::m_error <<__e_fail = TString().Format(_T("#__e_undef: error code 0x%04x (%d)"), u_err_code, u_err_code);
	}
	return CBase::Error();
}

// https://docs.gl/gl3/glLoadTransposeMatrix ; https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glLoadTransposeMatrix.xml ;
err_code CMatrix::Load (const float* _p_mat4x4, const bool _b_transp) {
	_p_mat4x4; _b_transp;
	/* Possible error codes:
	GL_INVALID_OPERATION : glMatrixMode() is executed between the execution of glBegin() and the corresponding execution of glEnd();
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	if (nullptr == _p_mat4x4)
		return CBase::m_error <<__e_pointer = _T("#__e_ptr: the input pointer is invalid");

	pfn_Load p_fun = reinterpret_cast<pfn_Load>(CBase::Get(mat_fun_names[(uint32_t)(_b_transp ? e_mat_fun_ndx::e_load_trans : e_mat_fun_ndx::e_load)]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_p_mat4x4);
	const
	uint32_t u_err_code = CErr_ex().Get_code();
	switch ( u_err_code ){
	case GL_INVALID_OPERATION : CBase::m_error << __e_not_expect = _T("#__e_state: Invalid state for loading the matrix"); break;
	default:
		if (!!u_err_code)
			CBase::m_error <<__e_fail = TString().Format(_T("#__e_undef: error code 0x%04x (%d)"), u_err_code, u_err_code);
	}
	return CBase::Error();
}

#pragma endregion

TMatrixProcs& ::__get_matrix_procs (void) {
	static TMatrixProcs procs;
	static bool b_loaded = false;
	if (false == b_loaded) {
		if (__failed(procs.Get_all())) {
		    __trace_err_2(_T("%s;\n"), (_pc_sz) procs.Error().Print(TError::e_print::e_req)); }
		else
		    b_loaded = true;
	}
	return procs;
}