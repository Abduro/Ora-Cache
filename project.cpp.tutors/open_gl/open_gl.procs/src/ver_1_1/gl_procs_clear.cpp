/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-May-2026 at 20:14:16.267, UTC+4, Batumi, Monday;
	This is OpenGL ver.1.1  glClear* function set wrapper interface implementation file;
*/
#include "gl_procs_clear.h"

using namespace open_gl::procs::ver_1_1;

#pragma region cls::CClear{}

static _pc_sz p_err_inv_oper = _T("#__e_inv_oper: called between glBegin() and glEnd()");
static _pc_sz p_err_unk_code = _T("#__e_undef: error code 0x%04x (%d)");

CClear::CClear (void) { TBase::m_error >>__CLASS__; }

err_code CClear::All (const s_clear_args& _args) {
	_args;
	if (__failed(this->Color(_args._f_color))) __trace_err_ex_2(TBase::Error());
	if (__failed(this->Depth(_args._f_value))) __trace_err_ex_2(TBase::Error());
	if (__failed(this->Stencil(_args._n_index))) __trace_err_ex_2(TBase::Error());

	if (false == TBase::Error())
		TBase::m_error <<__METHOD__<<__s_ok;

	return TBase::Error(); // only the last error is returned, but trace makes his work;
}

err_code CClear::Color (const f_clr_t _clr_value) {
	_clr_value;
	TBase::m_error <<__METHOD__<<__s_ok;
	//  https://learn.microsoft.com/en-us/windows/win32/opengl/glclearcolor ; err_code:{GL_INVALID_OPERATION}
	::glClearColor(_clr_value.at(0), _clr_value.at(1), _clr_value.at(2), _clr_value.at(3));
	const
	uint32_t u_err_code = CErr_ex().Get_code();
	switch ( u_err_code ) {
	case GL_INVALID_OPERATION : {
			TBase::m_error << (err_code) TErrCodes::eExecute::eOperate = p_err_inv_oper; } break;
	default:
		if (!!u_err_code)
			TBase::m_error <<__e_fail = TString().Format(p_err_unk_code,  u_err_code,  u_err_code);
	}
	return TBase::Error();
}

err_code CClear::Depth (const float _f_value) {
	_f_value;
	TBase::m_error <<__METHOD__<<__s_ok;
	// https://learn.microsoft.com/en-us/windows/win32/opengl/glcleardepth ; err_code:{GL_INVALID_OPERATION}
	::glClearDepth(_f_value);
	const
	uint32_t u_err_code = CErr_ex().Get_code();
	switch ( u_err_code ) {
	case GL_INVALID_OPERATION : {
			TBase::m_error << (err_code) TErrCodes::eExecute::eOperate = p_err_inv_oper; } break;
	default:
		if (!!u_err_code)
			TBase::m_error <<__e_fail = TString().Format(p_err_unk_code,  u_err_code,  u_err_code);
	}
	return TBase::Error();
}

err_code CClear::Stencil (const int32_t _n_index) {
	_n_index;
	TBase::m_error <<__METHOD__<<__s_ok;
	// https://learn.microsoft.com/en-us/windows/win32/opengl/glclearstencil ; err_code:{GL_INVALID_OPERATION}
	::glClearStencil (_n_index);
	const
	uint32_t u_err_code = CErr_ex().Get_code();
	switch ( u_err_code ) {
	case GL_INVALID_OPERATION : {
			TBase::m_error << (err_code) TErrCodes::eExecute::eOperate = p_err_inv_oper; } break;
	default:
		if (!!u_err_code)
			TBase::m_error <<__e_fail = TString().Format(p_err_unk_code,  u_err_code,  u_err_code);
	}
	return TBase::Error();
}

#pragma endregion