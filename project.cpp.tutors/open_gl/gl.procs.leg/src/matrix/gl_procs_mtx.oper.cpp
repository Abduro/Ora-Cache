/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Feb-2026 at 18:27:49.788, (UTC+4), Batumi, Thursday;
	This is Ebo Pack OpenGL math matrix mode functions' loader interface implementation file;
*/
#include "gl_procs_mtx.oper.h"

namespace open_gl { namespace procs { namespace matrix {
namespace ver_1_1 {

#pragma region cls::COpers

COpers::COpers (void) : TBase() { TBase::m_error >>__CLASS__; }

// https://learn.microsoft.com/en-us/windows/win32/opengl/glmultmatrixf ;
err_code COpers::Multiply (const f_mat_4x4& _by) {
	_by;
	/* possible error codes:
	GL_INVALID_OPERATION : The function was called between a call to glBegin and the corresponding call to glEnd.
	*/
	TBase::m_error <<__METHOD__<<__s_ok;

	::glMultMatrixf(_by.data());
	const
	dword  u_err_code = CErr_ex().Get_code();
	switch(u_err_code) {
	case GL_INVALID_OPERATION : (TBase::m_error = u_err_code) = p_err_inv_oper; break;
	default:
		if (!!u_err_code)
			TBase::m_error <<__e_fail = TString().Format(p_err_unk_code,  u_err_code,  u_err_code);
	}
	return TBase::Error();
}

// https://learn.microsoft.com/en-us/windows/win32/opengl/glscalef ;
err_code COpers::Scale (const f_set_3& _to) {
	_to;
	/* possible error codes:
	GL_INVALID_OPERATION : The function was called between a call to glBegin and the corresponding call to glEnd.
	*/
	TBase::m_error <<__METHOD__<<__s_ok;

	::glScalef(_to.at(0), _to.at(1), _to.at(2));
	const
	dword  u_err_code = CErr_ex().Get_code();
	switch(u_err_code) {
	case GL_INVALID_OPERATION : (TBase::m_error = u_err_code) = p_err_inv_oper; break;
	default:
		if (!!u_err_code)
			TBase::m_error <<__e_fail = TString().Format(p_err_unk_code,  u_err_code,  u_err_code);
	}
	return TBase::Error();
}

// https://learn.microsoft.com/en-us/windows/win32/opengl/glrotatef ;
err_code COpers::Rotate (float _f_angle, const float _x, const float _y, const float _z) {
	_f_angle; _x; _y; _z;
	/* possible error codes:
	GL_INVALID_OPERATION : The function was called between a call to glBegin and the corresponding call to glEnd.
	*/
	TBase::m_error <<__METHOD__<<__s_ok;
	::glRotatef (_f_angle, _x, _y, _z);
	const
	dword  u_err_code = CErr_ex().Get_code();
	switch(u_err_code) {
	case GL_INVALID_OPERATION : (TBase::m_error = u_err_code) = p_err_inv_oper; break;
	default:
		if (!!u_err_code)
			TBase::m_error <<__e_fail = TString().Format(p_err_unk_code,  u_err_code,  u_err_code);
	}
	return TBase::Error();
}

err_code COpers::Rotate (float _f_angle, const f_set_3& _where) {
	return this->Rotate (_f_angle, _where.at(0), _where.at(1), _where.at(2));
}

// https://learn.microsoft.com/en-us/windows/win32/opengl/gltranslatef ;
err_code COpers::Translate (const float _x, const float _y, const float _z) {
	_x; _y; _z;
	/* possible error codes:
	GL_INVALID_OPERATION : The function was called between a call to glBegin and the corresponding call to glEnd.
	*/
	TBase::m_error <<__METHOD__<<__s_ok;
	::glTranslatef (_x, _y, _z);
	const
	dword  u_err_code = CErr_ex().Get_code();
	switch(u_err_code) {
	case GL_INVALID_OPERATION : (TBase::m_error = u_err_code) = p_err_inv_oper; break;
	default:
		if (!!u_err_code)
			TBase::m_error <<__e_fail = TString().Format(p_err_unk_code,  u_err_code,  u_err_code);
	}
	return TBase::Error();
}

err_code COpers::Translate (const f_set_3& _what) {
	return this->Translate (_what.at(0), _what.at(1), _what.at(2));
}

#pragma endregion
}
namespace arb {}

}}}
#if (0)
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
#endif