/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-May-2026 at 16:19:21.618, UTC+4, Batumi, Wednesday;
	This is OpenGL v.1.1 matrix related function set wrapper interface implementation file;
*/
#include "gl_procs_matrix.h"

using namespace ::open_gl::procs::ver_1_1;
using namespace ::open_gl::procs::ver_1_1::matrix;

#pragma region cls::CMode{}

CMode::CMode (void) : TBase(), m_current(e_modes::e_modelview) { TBase::m_error >>__CLASS__; }

e_modes  CMode::Get (void) const { return this->m_current; }

// https://learn.microsoft.com/en-us/windows/win32/opengl/glgetintegerv ;
err_code CMode::Get (void) {
	/* possible error codes:
	GL_INVALID_ENUM      : input argument has not acceptable value;
	GL_INVALID_OPERATION : the call is made between a call to glBegin() and the corresponding call to glEnd();
	*/
	TBase::m_error <<__s_ok;
	this->m_current = e_modes::e_modelview; // sets default value;

	int32_t n_current = this->m_current;
	::glGetIntegerv(GL_MATRIX_MODE, &n_current);
	const
	uint32_t u_err_code = CErr_ex().Get_code();
	switch ( u_err_code ){
	case GL_INVALID_VALUE : (TBase::m_error = (dword)u_err_code) = TString().Format(p_err_inv_enum, GL_MATRIX_MODE, GL_MATRIX_MODE); break;
	case GL_INVALID_OPERATION : (TBase::m_error = (dword)u_err_code) = p_err_inv_oper; break;
	default:
		if (!!u_err_code)
			TBase::m_error <<__e_fail = TString().Format(p_err_unk_code, u_err_code, u_err_code);
	}
	if (false == TBase::Error())
		this->m_current = (e_modes)n_current; // updates the current mode value;
	return TBase::Error();
}

//https://learn.microsoft.com/en-us/windows/win32/opengl/glmatrixmode ;
err_code CMode::Set (const e_modes _e_mode) {
	_e_mode;
	/* Possible error codes:
	GL_INVALID_ENUM      : '_e_mode' is not an accepted value;
	GL_INVALID_OPERATION : glMatrixMode() is executed between the execution of glBegin() and the corresponding execution of glEnd();
	*/
	TBase::m_error <<__s_ok;

	::glMatrixMode((uint32_t)_e_mode);
	const
	uint32_t u_err_code = CErr_ex().Get_code();
	switch ( u_err_code ){
	case GL_INVALID_VALUE : (TBase::m_error = (dword)u_err_code) = TString().Format(p_err_inv_enum, _e_mode, _e_mode); break;
	case GL_INVALID_OPERATION : (TBase::m_error = (dword)u_err_code) = p_err_inv_oper; break;
	default:
		if (!!u_err_code)
			TBase::m_error <<__e_fail = TString().Format(p_err_unk_code, u_err_code, u_err_code);
	}
	if (false == TBase::Error())
		this->m_current = _e_mode; // updates the current mode value;

	return TBase::Error();
}

const
CMode& CMode::operator >>(e_modes& _e_mode) const { _e_mode = this->Get(); return *this; }
CMode& CMode::operator <<(const e_modes _e_mode) { this->Set(_e_mode); return *this; }

bool   CMode::Is_model   (void) const { return e_modes::e_modelview == this->Get(); }
bool   CMode::Is_project (void) const { return e_modes::e_project   == this->Get(); }
bool   CMode::Is_textrue (void) const { return e_modes::e_texture   == this->Get(); }

_pc_sz CMode::To_str (const e_modes _e_mode) {
	_e_mode;
	static CString cs_out;
	switch (_e_mode) {
	case e_modes::e_project  : cs_out = _T("e_projection"); break;
	case e_modes::e_texture  : cs_out = _T("e_texture"); break;
	default: cs_out = _T("e_modelview");
	}
	return (_pc_sz) cs_out;
}

#pragma endregion
#pragma region cls::CMatrix{}

CMatrix::CMatrix (void) : TBase() { TBase::m_error >>__CLASS__; }

// https://learn.microsoft.com/en-us/windows/win32/opengl/glgetfloatv ;
err_code CMatrix::Get (const e_mat_type _e_type, c_mat4x4& _result) {
	_e_type; _result;

	TBase::m_error <<__METHOD__<<__s_ok;
	_result.Identity();

	::glGetFloatv(_e_type, _result());
	const
	uint32_t u_err_code = CErr_ex().Get_code();
	switch ( u_err_code ) {
	case GL_INVALID_ENUM : TBase::m_error <<__e_inv_arg = TString().Format(p_err_inv_enum, _e_type); break;
	case GL_INVALID_OPERATION : { TBase::m_error << (err_code) TErrCodes::eExecute::eOperate = p_err_inv_oper; } break;
	default:
		if (!!u_err_code)
			TBase::m_error <<__e_fail = TString().Format(p_err_unk_code,  u_err_code,  u_err_code);
	}
	return TBase::Error();
}

// https://learn.microsoft.com/en-us/windows/win32/opengl/glloadidentity ;
err_code CMatrix::To_self (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	::glLoadIdentity();
	const
	uint32_t u_err_code = CErr_ex().Get_code();
	switch ( u_err_code ) {
	case GL_INVALID_OPERATION : { TBase::m_error << (err_code) TErrCodes::eExecute::eOperate = p_err_inv_oper; } break;
	default:
		if (!!u_err_code)
			TBase::m_error <<__e_fail = TString().Format(p_err_unk_code,  u_err_code,  u_err_code);
	}
	return TBase::Error();
}

#pragma endregion