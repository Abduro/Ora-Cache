/*
	Created by Tech_dog (ebontrop@gmail.com) on 17-Jun-2026 at 01:08:23.116, UTC+4, Batumi, Wednesday;
	This is OpenGL ver.1.1 draw object property wrapper interface implementation file;
*/
#include "gl_procs_params.h"

using namespace ::open_gl::procs::ver_1_1;

#pragma region cls::CParam{}

CParam::CParam (const uint32_t _param_id) : m_param_id (_param_id) { TBase::m_error >>__CLASS__; }

// https://learn.microsoft.com/en-us/windows/win32/opengl/glgetbooleanv ;
bool    CParam::GetBool (const uint32_t _u_param_id) {
	_u_param_id;
	/* Possible error codes:
	GL_INVALID_ENUM : '_u_param_id' has not an accepted value;
	GL_INVALID_OPERATION : glGetBoolean was called between a call to glBegin and the corresponding call to glEnd;
	*/
	TBase::m_error << __METHOD__ << __s_ok;

	unsigned char u_result = 0;

	::glGetBooleanv(_u_param_id, &u_result);
	const
	uint32_t u_err_code = CErr_ex().Get_code();
	switch ( u_err_code ){
	case GL_INVALID_ENUM : TBase::m_error <<__e_inv_arg = TString().Format(p_err_unk_param, _u_param_id, _u_param_id); break;
	case GL_INVALID_OPERATION : { TBase::m_error << (err_code) TErrCodes::eExecute::eOperate = p_err_inv_oper; } break;
	default:
		if (!!u_err_code)
			TBase::m_error <<__e_fail = TString().Format(p_err_unk_code, u_err_code, u_err_code);
	}

	return !!u_result;
}

// https://learn.microsoft.com/en-us/windows/win32/opengl/glgetdoublev ;
double  CParam::GetDouble(const uint32_t _u_param_id) {
	_u_param_id;
	double d_value = 0.0;
	this->Get_ptr(_u_param_id, &d_value);

	return d_value;
}

// https://learn.microsoft.com/en-us/windows/win32/opengl/glgetfloatv   ;
float   CParam::GetFloat (const uint32_t _u_param_id) {
	_u_param_id;
	float  f_result = 0.0f;
	this->Get_ptr(_u_param_id, &f_result);

	return f_result;
}

// https://learn.microsoft.com/en-us/windows/win32/opengl/glgetintegerv ;
int32_t CParam::GetInt (const uint32_t _u_param_id) {
	_u_param_id;
	_u_param_id;
	int32_t n_result = 0;
	this->Get_ptr(_u_param_id, &n_result);

	return n_result;
}

// https://learn.microsoft.com/en-us/windows/win32/opengl/glgetdoublev  ;
err_code CParam::Get_ptr (const uint32_t _u_param_id, double* _p_ptr) {
	_u_param_id; _p_ptr;
	/* Possible error codes:
	GL_INVALID_ENUM      : '_u_param_id' is not an accepted value;
	GL_INVALID_OPERATION : glGet() is executed between the execution of glBegin() and the corresponding execution of glEnd();
	*/
	TBase::m_error << __METHOD__ << __s_ok;

	if (nullptr == _p_ptr)
		return TBase::m_error <<__e_pointer = _T("#__e_ptr: input pointer is invalid");
	::glGetDoublev(_u_param_id, _p_ptr);
	const
	dword  u_err_code = CErr_ex().Get_code();
	switch(u_err_code){
	case GL_INVALID_ENUM: (TBase::m_error = u_err_code) = TString().Format(p_err_unk_param, _u_param_id, _u_param_id); break;
	case GL_INVALID_OPERATION : { (TBase::m_error = u_err_code) = p_err_inv_oper; } break;
	default:
		if (!!u_err_code)
			TBase::m_error <<__e_fail = TString().Format(p_err_unk_code, u_err_code, u_err_code);
	}

	return TBase::Error();
}

// https://learn.microsoft.com/en-us/windows/win32/opengl/glgetfloatv   ;
err_code CParam::Get_ptr (const uint32_t _u_param_id, float* _p_ptr) {
	_u_param_id; _p_ptr;
	/* Possible error codes:
	GL_INVALID_ENUM      : '_u_param_id' is not an accepted value;
	GL_INVALID_OPERATION : glGet() is executed between the execution of glBegin() and the corresponding execution of glEnd();
	*/
	TBase::m_error << __METHOD__ << __s_ok;

	if (nullptr == _p_ptr)
		return TBase::m_error <<__e_pointer = _T("#__e_ptr: input pointer is invalid");
	::glGetFloatv(_u_param_id, _p_ptr);
	const
	dword  u_err_code = CErr_ex().Get_code();
	switch(u_err_code){
	case GL_INVALID_ENUM: (TBase::m_error = u_err_code) = TString().Format(p_err_unk_param, _u_param_id, _u_param_id); break;
	case GL_INVALID_OPERATION : { (TBase::m_error = u_err_code) = p_err_inv_oper; } break;
	default:
		if (!!u_err_code)
			TBase::m_error <<__e_fail = TString().Format(p_err_unk_code, u_err_code, u_err_code);
	}

	return TBase::Error();
}

// https://learn.microsoft.com/en-us/windows/win32/opengl/glgetintegerv ;
err_code CParam::Get_ptr (const uint32_t _u_param_id, int32_t* _p_ptr) {
	_u_param_id; _p_ptr;
	/* Possible error codes:
	GL_INVALID_ENUM      : '_u_param_id' is not an accepted value;
	GL_INVALID_OPERATION : glGet() is executed between the execution of glBegin() and the corresponding execution of glEnd();
	*/
	TBase::m_error << __METHOD__ << __s_ok;

	if (nullptr == _p_ptr)
		return TBase::m_error <<__e_pointer = _T("#__e_ptr: input pointer is invalid");
	::glGetIntegerv(_u_param_id, _p_ptr);
	const
	dword  u_err_code = CErr_ex().Get_code();
	switch(u_err_code){
	case GL_INVALID_ENUM: (TBase::m_error = u_err_code) = TString().Format(p_err_unk_param, _u_param_id, _u_param_id); break;
	case GL_INVALID_OPERATION : { (TBase::m_error = u_err_code) = p_err_inv_oper; } break;
	default:
		if (!!u_err_code)
			TBase::m_error <<__e_fail = TString().Format(p_err_unk_code, u_err_code, u_err_code);
	}

	return TBase::Error();
}

#pragma endregion