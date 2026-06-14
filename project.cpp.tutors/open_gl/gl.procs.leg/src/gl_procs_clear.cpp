/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-May-2026 at 20:14:16.267, UTC+4, Batumi, Monday;
	This is OpenGL ver.1.1  glClear* function set wrapper interface implementation file;
*/
#include "gl_procs_clear.h"

using namespace open_gl::procs::ver_1_1;

#pragma region cls::CClear{}

static _pc_sz p_err_inv_mask = _T("#__inv_arg: input mask (%u) has undefined bit");

CClear::CClear (void) { TBase::m_error >>__CLASS__; }

// https://learn.microsoft.com/en-us/windows/win32/opengl/glclear ;
err_code CClear::All (void) {
	/* the possible error codes:
	GL_INVALID_OPERATION : The function was called between a call to glBegin and the corresponding call to glEnd.
	GL_INVALID_VALUE     : Any bit other than the four defined bits was set in mask;
	*/
	TBase::m_error <<__METHOD__<<__s_ok;

	static const uint32_t u_mask = GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_ACCUM_BUFFER_BIT|GL_STENCIL_BUFFER_BIT;

	::glClear(u_mask);
	const
	dword  u_err_code = CErr_ex().Get_code();
	switch(u_err_code){
	case GL_INVALID_OPERATION : (TBase::m_error = u_err_code) = p_err_inv_oper; break;
	case GL_INVALID_VALUE : (TBase::m_error = u_err_code) = TString().Format(p_err_inv_mask, u_mask); break; // should never occur;
	default:
		if (!!u_err_code)
			TBase::m_error <<__e_fail = TString().Format(p_err_unk_code,  u_err_code,  u_err_code);
	}

	return TBase::Error();
}

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
	dword  u_err_code = CErr_ex().Get_code();
	switch(u_err_code){
	case GL_INVALID_OPERATION : (TBase::m_error = u_err_code) = p_err_inv_oper; break;
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
	dword  u_err_code = CErr_ex().Get_code();
	switch(u_err_code){
	case GL_INVALID_OPERATION : (TBase::m_error = u_err_code) = p_err_inv_oper; break;
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
	dword  u_err_code = CErr_ex().Get_code();
	switch(u_err_code){
	case GL_INVALID_OPERATION : (TBase::m_error = u_err_code) = p_err_inv_oper; break;
	default:
		if (!!u_err_code)
			TBase::m_error <<__e_fail = TString().Format(p_err_unk_code,  u_err_code,  u_err_code);
	}
	return TBase::Error();
}

#pragma endregion