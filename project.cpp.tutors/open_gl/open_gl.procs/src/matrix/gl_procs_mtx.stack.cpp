/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Feb-2026 at 19:23:24.391, (UTC+4), Batumi, Thursday;
	This is Ebo Pack OpenGL math matrix mode functions' loader interface implementation file;
*/
#include "gl_procs_mtx.stack.h"
#include "gl_procs.h"

#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::procs;
using namespace ex_ui::draw::open_gl::procs::matrix;

#pragma region cls::CStack{}

static _pc_sz stk_fun_names[] = {
	_T("glPopMatrix")   , _T("glPushMatrix")
};
enum class e_stk_fun_ndx : uint32_t {
	e_pop = 0x0, e_push
};

CStack::CStack (void) : CBase() { CString cs_cls = TString().Format(_T("%s::%s"), CBase::m_error.Class(), (_pc_sz)__CLASS__);
	CBase::m_error.Class(cs_cls, false);
}

err_code CStack::Get_all (void) {
	CBase::m_error << __METHOD__ << __s_ok;

	for (uint32_t i_ = 0; i_ < _countof(stk_fun_names); i_++) {
		if (nullptr == CBase::Get(stk_fun_names[i_]))
			break;
	}

	return CBase::Error();
}

err_code CStack::Pop (void) {
	/* Possible error codes:
	GL_INVALID_OPERATION : glPopMatrix() is executed between the execution of glBegin() and the corresponding execution of glEnd();
	GL_STACK_OVERFLOW    : glPushMatrix() is called while the current matrix stack is full;
	GL_STACK_UNDERFLOW   : glPopMatrix() is called while the current matrix stack contains only a single matrix;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Pop p_fun = reinterpret_cast<pfn_Pop>(CBase::Get(stk_fun_names[(uint32_t)e_stk_fun_ndx::e_pop]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun();
	const
	uint32_t u_err_code = CErr_ex().Get_code();
	switch ( u_err_code ){
	case GL_INVALID_OPERATION : CBase::m_error << __e_not_expect = _T("#__e_state: Invalid state to pop the matrix from stack"); break;
	case GL_STACK_UNDERFLOW : CBase::m_error << __e_not_expect = _T("#__e_underflow: the matrix stack is empty"); break;
	default:
		if (!!u_err_code)
			CBase::m_error <<__e_fail = TString().Format(_T("#__e_undef: error code 0x%04x (%d)"), u_err_code, u_err_code);
	}

	return CBase::Error();
}

err_code CStack::Push (void) {
	/* Possible error codes:
	GL_INVALID_OPERATION : glPushMatrix() is executed between the execution of glBegin() and the corresponding execution of glEnd();
	GL_STACK_OVERFLOW    : glPushMatrix() is called while the current matrix stack is full;
	*/
	CBase::m_error << __METHOD__ << __s_ok;

	pfn_Push p_fun = reinterpret_cast<pfn_Push>(CBase::Get(stk_fun_names[(uint32_t)e_stk_fun_ndx::e_push]));
	if (nullptr == p_fun)
		return CBase::Error();

	p_fun();
	const
	uint32_t u_err_code = CErr_ex().Get_code();
	switch ( u_err_code ){
	case GL_INVALID_OPERATION : CBase::m_error << __e_not_expect = _T("#__e_state: Invalid state to push the matrix to stack"); break;
	case GL_STACK_OVERFLOW : CBase::m_error << __e_not_expect = _T("#__e_overflow: the matrix stack is full"); break;
	default:
		if (!!u_err_code)
			CBase::m_error <<__e_fail = TString().Format(_T("#__e_undef: error code 0x%04x (%d)"), u_err_code, u_err_code);
	}

	return CBase::Error();
}

#pragma endregion

TStackProcs& ::__get_stack_procs (void) {
	static TStackProcs procs;
	static bool b_loaded = false;
	if (false == b_loaded) {
		if (__failed(procs.Get_all())) {
		    __trace_err_2(_T("%s;\n"), (_pc_sz) procs.Error().Print(TError::e_print::e_req)); }
		else
		    b_loaded = true;
	}
	return procs;
}