/*
	Created by Tech_dog (ebontrop@gmail.com) on 31-Aug-2025 at 12:33:39.591, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL tutorials' context base interface implementation file;
*/
#include "gl_context.h"
#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::context;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl {

}}}}

using namespace ex_ui::draw::open_gl::_impl;

context::CBase:: CBase (void) { this->m_error() >> __CLASS__ << __METHOD__ << __e_not_inited; }
context::CBase::~CBase (void) {}

TErr_ex& context::CBase::Error (void) const { return this->m_error; }

/////////////////////////////////////////////////////////////////////////////

context::CDevice:: CDevice (void) : CBase(), m_drw_ctx(0), m_dc_src(0), m_target(0) { CBase::m_error <<__CLASS__; }
context::CDevice::~CDevice (void) {}

err_code context::CDevice::Create (const HWND _h_wnd) {
	_h_wnd;
	CBase::m_error <<__METHOD__<<__s_ok;

	if (this->m_drw_ctx) {
		CBase::m_error << (err_code) TErrCodes::eObject::eInited = _T("Draw renderer exists");
		__trace_err_3(_T("%s"), (_pc_sz) CBase::Error().Print(TError::e_req)); return CBase::Error();
	}

	if (nullptr == _h_wnd || false == !!::IsWindow(_h_wnd)) {
		CBase::m_error << __e_hwnd = _T("Target window handle is invalid");
		__trace_err_3(_T("%s"), (_pc_sz) CBase::Error().Print(TError::e_req)); return CBase::Error();
	}
	this->m_target = _h_wnd;
	this->m_dc_src = ::GetDC(_h_wnd);
	__empty_ln();
	__trace_info_3(_T("context device: handle=%s\n"), (_pc_sz)__address_of(this->m_dc_src));

	PIXELFORMATDESCRIPTOR px_fmt_desc = {0}; // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-pixelformatdescriptor ;
	// https://www.khronos.org/opengl/wiki/Creating_an_OpenGL_Context_(WGL) << there is the example of how to do that;
	px_fmt_desc.nSize      = sizeof(PIXELFORMATDESCRIPTOR);
	px_fmt_desc.nVersion   = 1;
	px_fmt_desc.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	px_fmt_desc.iPixelType = PFD_TYPE_RGBA;
	px_fmt_desc.cColorBits = 32; // colordepth of the framebuffer;
	px_fmt_desc.cAlphaBits = 8;  // the number of bits for the stencilbuffer;
	px_fmt_desc.cDepthBits = 24; // the number of bits for the depthbuffer;

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-choosepixelformat ;
	int32_t n_px_format = ::ChoosePixelFormat(this->m_dc_src, &px_fmt_desc);
	if (0== n_px_format) {
		__trace_err_3(_T("%s"), (_pc_sz) (CBase::m_error()(CError::e_cmds::e_get_last)).Print(TError::e_req));
		return CBase::Error();
	}

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-setpixelformat ;
	if (false == !!::SetPixelFormat(this->m_dc_src, n_px_format, &px_fmt_desc)) {
		__trace_err_3(_T("%s"), (_pc_sz) (CBase::m_error()(CError::e_cmds::e_get_last)).Print(TError::e_req));
		return CBase::Error();
	}

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglcreatecontext ;
	this->m_drw_ctx = ::wglCreateContext(this->m_dc_src);
	if ( 0 == this->m_drw_ctx) {
		__trace_err_3(_T("%s"), (_pc_sz) (CBase::m_error()(CError::e_cmds::e_get_last)).Print(TError::e_req));
		return CBase::Error();
	}

	if (0 == ::wglMakeCurrent(this->m_dc_src, this->m_drw_ctx)) { // it is required, otherwise nothing will work;
		__trace_err_3(_T("%s"), (_pc_sz) (CBase::m_error()(CError::e_cmds::e_get_last)).Print(TError::e_req));
	}
	return CBase::Error();
}

err_code context::CDevice::Destroy(void) {
	this->m_error << __METHOD__ << __s_ok;

	// (1) destroys the renderer handle first;
	if (nullptr != this->m_drw_ctx) {
		// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglmakecurrent ;
		if (0 == ::wglMakeCurrent(m_dc_src, 0)) {
			__trace_err_3(_T("%s"), (_pc_sz) (CBase::m_error()(CError::e_cmds::e_get_last)).Print(TError::e_req));
		}
		// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wgldeletecontext ;
		if (0 == ::wglDeleteContext(this->m_drw_ctx)) {
			__trace_err_3(_T("%s"), (_pc_sz) (CBase::m_error()(CError::e_cmds::e_get_last)).Print(TError::e_req));
		}
		else
			this->m_drw_ctx = nullptr;
	}
	// (2) destroys device context handle; https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-releasedc ;
	if (nullptr != this->m_dc_src) {
		if (0 == ::ReleaseDC(this->m_target, this->m_dc_src)) {
			CBase::m_error << (err_code) TErrCodes::eExecute::eState = _T("Releasing source device context failed");
			__trace_err_3(_T("%s"), (_pc_sz) CBase::Error().Print(TError::e_req));
		}
			
		this->m_dc_src = nullptr; // sets nullptr regardless the error of releasing device context;
	}
	return CBase::Error();
}