/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-May-2026 at 01:26:41.331, UTC+4, Batumi, Tuesday;
	This is OpenGL ver.1.1 depth wrapper interface implementation file;
*/
#include "gl_procs_depth.h"

using namespace open_gl::procs::ver_1_1;

#pragma region cls::CComparator{}

using CComp = CDepth::CComparator;

CComp::CComparator (void) : TBase() { TBase::m_error >>__CLASS__; }

err_code CComp::Condition (const e_criteria _e_condition) {
	_e_condition;
	TBase::m_error <<__METHOD__<<__s_ok;
	// https://learn.microsoft.com/en-us/windows/win32/opengl/gldepthfunc ;
	::glDepthFunc (_e_condition);
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

bool     CComp::Is_enabled (void) const {
	return CProperty::Is_enabled(GL_DEPTH_TEST, TBase::m_error);
}
err_code CComp::Is_enabled (const bool _yes_or_no) {
	return CProperty::Is_enabled(GL_DEPTH_TEST, _yes_or_no, TBase::m_error);	
}

CComp& CComp::operator <<(const e_criteria _criterion) { this->Condition(_criterion); return *this; }
CComp& CComp::operator <<(const bool _yes_or_no) { this->Is_enabled(_yes_or_no); return *this; }

#pragma endregion
#pragma region cls::CDepth{}

CDepth::CDepth (void) : TBase() { TBase::m_error >>__CLASS__; }

err_code CDepth::Clear (const float _f_value) {
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

const
CComp&   CDepth::Comp (void) const { return this->m_comp; }
CComp&   CDepth::Comp (void)       { return this->m_comp; }

err_code CDepth::Range (const float _f_near, const float _f_far) {
	_f_near; _f_far;
	TBase::m_error <<__METHOD__<<__s_ok;
	// https://learn.microsoft.com/en-us/windows/win32/opengl/gldepthrange ; err_code:{GL_INVALID_OPERATION}
	::glDepthRange(_f_near, _f_far);
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