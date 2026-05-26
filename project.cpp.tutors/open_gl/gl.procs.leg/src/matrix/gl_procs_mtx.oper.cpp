/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Feb-2026 at 18:27:49.788, (UTC+4), Batumi, Thursday;
	This is Ebo Pack OpenGL math matrix mode functions' loader interface implementation file;
*/
#include "gl_procs_mtx.oper.h"
#include "gl_procs.h"

#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::procs;
using namespace ex_ui::draw::open_gl::procs::matrix;

#pragma region cls::COpers

static _pc_sz oper_fun_names[] = {
	_T("glMultMatrixf"), _T("glMultTransposeMatrixf"), _T("glTranslatef")
};
enum class e_oper_fun_ndx : uint32_t {
	e_multiply = 0x0, e_mult_trans, e_translate
};

COpers::COpers (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}

err_code COpers::Get_all (void) {
	CBase::m_error << __METHOD__ << __s_ok;

	for (uint32_t i_ = 0; i_ < _countof(oper_fun_names); i_++) {
		if (nullptr == CBase::Get(oper_fun_names[i_]))
			break;
	}

	return CBase::Error();
}

// https://docs.gl/gl3/glMultMatrix ; https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glMultMatrix.xml ;
err_code COpers::Multiply (const float* _p_mat4x4, const bool _b_transp) {
	_p_mat4x4; _b_transp;
	/* Possible error codes:
	GL_INVALID_OPERATION : glMatrixMode() is executed between the execution of glBegin() and the corresponding execution of glEnd();
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	if (nullptr == _p_mat4x4)
		return CBase::m_error <<__e_pointer = _T("#__e_ptr: the input pointer is invalid");

	pfn_Multiply p_fun = reinterpret_cast<pfn_Multiply>(CBase::Get(oper_fun_names[(uint32_t)(_b_transp ? e_oper_fun_ndx::e_mult_trans : e_oper_fun_ndx::e_multiply)]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_p_mat4x4);
	const
	uint32_t u_err_code = CErr_ex().Get_code();
	switch ( u_err_code ){
	case GL_INVALID_OPERATION : CBase::m_error << __e_not_expect = _T("#__e_state: Invalid state for matrix multiplication"); break;
	default:
		if (!!u_err_code)
			CBase::m_error <<__e_fail = TString().Format(_T("#__e_undef: error code 0x%04x (%d)"), u_err_code, u_err_code);
	}
	return CBase::Error();
}

err_code COpers::Translate (const float _x, const float _y, const float _z) {
	_x; _y; _z;
	/* Possible error codes:
	GL_INVALID_OPERATION : glTranslatef() is called between the executions of glBegin() and corresponding glEnd();
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Translate p_fun = reinterpret_cast<pfn_Translate>(CBase::Get(oper_fun_names[(uint32_t)e_oper_fun_ndx::e_translate]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun(_x, _y, _z);
	const
	uint32_t u_err_code = CErr_ex().Get_code();
	switch ( u_err_code ){
	case GL_INVALID_OPERATION : CBase::m_error << __e_not_expect = _T("#__e_state: Invalid state to translate the vector"); break;
	default:
		if (!!u_err_code)
			CBase::m_error <<__e_fail = TString().Format(_T("#__e_undef: error code 0x%04x (%d)"), u_err_code, u_err_code);
	}

	return CBase::Error();
}

#pragma endregion