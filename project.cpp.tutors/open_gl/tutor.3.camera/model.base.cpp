/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Apr-2026 at 08:41:40.435, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' model base interface implementation file;
*/
#include "model.base.h"

using namespace ex_ui::draw::open_gl::models;

#pragma region cls::CBase{}

CBase::CBase (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("#__e_state: base model is not created"); }

err_code CBase::Create (const HWND _h_surface) {
	_h_surface;
	this->m_error <<__METHOD__<<__s_ok;

	if (__failed(this->Grid().Create())) return this->m_error = this->Grid().Error();

	return this->Error();
}

err_code CBase::Destroy (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (__failed(this->Grid().Destroy())) return this->m_error = this->Grid().Error();

	return this->Error();
}

TError& CBase::Error (void) const { return this->m_error; }

err_code CBase::Init (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (false == ::Get_version().Is_base()) {
		static _pc_sz p_err_ver_unsupp = _T("#__e_vers: OpenGL ver %s is not supported");
		__trace_err_ex_2(
			this->m_error <<(err_code)TErrCodes::eExecute::eState = TString().Format(p_err_ver_unsupp, (_pc_sz) ::Get_version().Data().To_str() )
		);
		return this->Error();
	}
	// to-do: all functions being called must be moved to procedure loader project;

	::glShadeModel (GL_SMOOTH); // https://learn.microsoft.com/en-us/windows/win32/opengl/glshademodel ; err_code:{GL_INVALID_ENUM|GL_INVALID_OPERATION}

	::glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // https://learn.microsoft.com/en-us/windows/win32/opengl/glhint ; err_code:{GL_INVALID_ENUM|GL_INVALID_OPERATION}

	::glEnable(GL_DEPTH_TEST); // https://learn.microsoft.com/en-us/windows/win32/opengl/glenable ; err_code:{GL_INVALID_ENUM|GL_INVALID_OPERATION}
	::glEnable(GL_CULL_FACE);

	::glClearColor(0.152f, 0.152f, 0.152f, 1.0f); // must to go before glClear(); https://learn.microsoft.com/en-us/windows/win32/opengl/glclearcolor ; err_code:{GL_INVALID_OPERATION}
	::glClearStencil(0); // https://learn.microsoft.com/en-us/windows/win32/opengl/glclearstencil ; err_code:{GL_INVALID_OPERATION}
	::glClearDepth(1.0f); // https://learn.microsoft.com/en-us/windows/win32/opengl/glcleardepth ; err_code:{GL_INVALID_OPERATION}
	::glDepthFunc(GL_LEQUAL); // https://learn.microsoft.com/en-us/windows/win32/opengl/gldepthfunc ; err_code:{GL_INVALID_OPERATION}

	return this->Error();
}

const
CGrid&  CBase::Grid (void) const { return this->m_grid; }
CGrid&  CBase::Grid (void)       { return this->m_grid; }
const
CViewPort& CBase::ViewPort (void) const { return this->m_v_port; }
CViewPort& CBase::ViewPort (void)       { return this->m_v_port; }     

#pragma endregion