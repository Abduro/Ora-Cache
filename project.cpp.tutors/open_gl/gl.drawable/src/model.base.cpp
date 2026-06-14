/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Apr-2026 at 08:41:40.435, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' model base interface implementation file;
*/
#include "model.base.h"

using namespace ::open_gl::models;

namespace open_gl { namespace models { namespace _impl {

}}} using namespace ::open_gl::models::_impl;

#pragma region cls::CBase{}

CBase::CBase (void) : m_model(true) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("#__e_state: base model is not created"); }

err_code CBase::Create (const HWND _h_surface) {
	_h_surface;
	this->m_error <<__METHOD__<<__s_ok;
	
	return this->Error();
}

err_code CBase::Destroy (void) {
	this->m_error <<__METHOD__<<__s_ok;

	return this->Error();
}

TError&  CBase::Error (void) const { return this->m_error; }

//	::glShadeModel(GL_SMOOTH); // https://learn.microsoft.com/en-us/windows/win32/opengl/glshademodel ; err_code:{GL_INVALID_ENUM|GL_INVALID_OPERATION}
//	::glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // https://learn.microsoft.com/en-us/windows/win32/opengl/glhint ; err_code:{GL_INVALID_ENUM|GL_INVALID_OPERATION}
//	::glEnable(GL_CULL_FACE);

const
c_mat4x4&  CBase::Mat_model (void) const { return this->m_model; }
c_mat4x4&  CBase::Mat_model (void)       { return this->m_model; }

#pragma endregion