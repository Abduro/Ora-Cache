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

context::CTarget:: CTarget (void) : CBase(), m_dc_src(0), m_target(0) { CBase::m_error <<__CLASS__; }
context::CTarget:: CTarget (const HWND _h_wnd) : CTarget() { *this << _h_wnd; }
context::CTarget::~CTarget (void) {
	this->Free ();
}

err_code  context::CTarget::Free(void) {
	// https://stackoverflow.com/questions/3945721/win32-why-does-releasedc-say-my-dc-is-not-found ; good answer is >>
	// https://stackoverflow.com/a/3948202/4325555 ; the excerpt : ...Lots of OpenGl samples do rather (to my mind) weired things with device contexts... ;
	CBase::m_error << __METHOD__ << __s_ok;

	if (this->Is_valid() == false) {
		this->m_dc_src = nullptr; // for cases when handle of the device context has invalid state, i.e. is closed outside of this class instance;
		return CBase::Error();    // returns possibly the error state that is set by this::Is_valid();
	}

	if (0 == ::ReleaseDC(this->m_target, this->m_dc_src)) {
		CBase::m_error << (err_code) TErrCodes::eExecute::eState = _T("Releasing source device context failed");
		__trace_err_3(_T("%s"), (_pc_sz) CBase::Error().Print(TError::e_req));
	}

	return CBase::Error();
}

bool context::CTarget::Is_valid (void) const {

	CBase::m_error << __METHOD__ << __s_ok;

	if (nullptr == this->m_dc_src)
		return false;

	if (nullptr != this->m_dc_src)
		return false != (CBase::m_error << __e_not_inited).Is(); // the error onject set to error state (i.e. error == true);

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-getobjecttype ;
	const uint32_t u_dc_type = ::GetObjectType(this->m_dc_src);

	if (OBJ_DC != u_dc_type && OBJ_MEMDC != u_dc_type) // not sure that the source device context may be an in-memory one, but anyway it is okay;
		return false != (CBase::m_error << __e_inv_arg = _T("Source device context is not valid")).Is();

	return false == CBase::Error().Is(); // returns 'true' due to the error state is not set to err_code, i.e. everything is '__s_ok';
}

const HDC context::CTarget::Get (void) const { return this->m_dc_src; }
err_code  context::CTarget::Set (const HWND _h_wnd) {
	_h_wnd;
	CBase::m_error << __METHOD__ << __s_ok;

	if (this->Is_valid()) {
		CBase::m_error << (err_code) TErrCodes::eObject::eInited = _T("Source device context is already set");
		__trace_err_3(_T("%s"), (_pc_sz) CBase::Error().Print(TError::e_req)); return CBase::Error();
	}

	if (nullptr == _h_wnd || false == !!::IsWindow(_h_wnd)) {
		CBase::m_error << __e_hwnd = _T("Target window handle is invalid");
		__trace_err_3(_T("%s"), (_pc_sz) CBase::Error().Print(TError::e_req)); return CBase::Error();
	}

	this->m_target = _h_wnd;
	this->m_dc_src = ::GetDC(_h_wnd);
//	__empty_ln();
	__trace_info_3(_T("context device: handle=%s\n"), (_pc_sz)__address_of(this->m_dc_src));

	return CBase::Error();
}

CTarget&  context::CTarget::operator <<(const HWND _h_wnd) {
	_h_wnd;
	if (this->Is_valid())
		this->Free();
	if (this->Error()) // releasing the source device context handle is failed;
		return *this;
	this->Set(_h_wnd); return *this; // for getting the result of retreiving the device context the error state should be checked;
}

/////////////////////////////////////////////////////////////////////////////

context::CDevice:: CDevice (void) : CBase(), m_drw_ctx(0) { CBase::m_error <<__CLASS__; }

context::CDevice:: CDevice (const HWND _h_wnd) : CDevice() { *this << _h_wnd; }

context::CDevice::~CDevice (void) { this->Destroy(); }

err_code context::CDevice::Create (const HWND _h_wnd) {
	_h_wnd;
	CBase::m_error <<__METHOD__<<__s_ok;

	if (this->Is_valid()) {
		CBase::m_error << (err_code) TErrCodes::eObject::eInited = _T("Draw renderer exists");
		__trace_err_3(_T("%s"), (_pc_sz) CBase::Error().Print(TError::e_req)); return CBase::Error();
	}

	if (__failed(this->Target().Set(_h_wnd))) {
		return CBase::m_error = this->Target().Error();
	}

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
	int32_t n_px_format = ::ChoosePixelFormat(this->Target().Get(), &px_fmt_desc);
	if (0== n_px_format) {
		__trace_err_3(_T("%s"), (_pc_sz) (CBase::m_error()(CError::e_cmds::e_get_last)).Print(TError::e_req));
		return CBase::Error();
	}

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-setpixelformat ;
	if (false == !!::SetPixelFormat(this->Target().Get(), n_px_format, &px_fmt_desc)) {
		__trace_err_3(_T("%s"), (_pc_sz) (CBase::m_error()(CError::e_cmds::e_get_last)).Print(TError::e_req));
		return CBase::Error();
	}

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglcreatecontext ;
	this->m_drw_ctx = ::wglCreateContext(this->Target().Get());
	if ( 0 == this->m_drw_ctx) {
		__trace_err_3(_T("%s"), (_pc_sz) (CBase::m_error()(CError::e_cmds::e_get_last)).Print(TError::e_req));
		return CBase::Error();
	}

	if (0 == ::wglMakeCurrent(this->Target().Get(), this->m_drw_ctx)) { // it is required, otherwise nothing will work;
		__trace_err_3(_T("%s"), (_pc_sz) (CBase::m_error()(CError::e_cmds::e_get_last)).Print(TError::e_req));
	}
	return CBase::Error();
}

err_code context::CDevice::Destroy(void) {
	this->m_error << __METHOD__ << __s_ok;

	// (1) destroys the renderer handle first;
	if (nullptr != this->m_drw_ctx) {
		// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglmakecurrent ;
		if (0 == ::wglMakeCurrent(this->Target().Get(), 0)) {
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
	if (this->Target().Is_valid())
		if (__failed(this->Target().Free()))
			CBase::m_error = this->Target().Error();

	return CBase::Error();
}

bool   context::CDevice::Is_valid (void) const {
	return !!this->m_drw_ctx;
}

HGLRC  context::CDevice::Renderer (void) const {
	return this->m_drw_ctx;
}

const
context::CTarget& context::CDevice::Target (void) const { return this->m_target; }
context::CTarget& context::CDevice::Target (void)       { return this->m_target; }

CDevice& context::CDevice::operator <<(const HWND _h_wnd) {
	_h_wnd;
	if (this->Is_valid())
		this->Destroy();
	if (this->Error()) // the destruction is failed;
		return *this;
	this->Create(_h_wnd); return *this; // for getting the result of creation the error state should be checked;
}

/////////////////////////////////////////////////////////////////////////////

#include "open_gl_tutor.0.fake.h"
#pragma comment(lib, "gl.tutor.0.fake.lib") // this is required due to the fake window is used in the first step;

CContext:: CContext (void) { TBase::m_error >>__CLASS__<<__METHOD__<< __e_not_inited; }
CContext::~CContext (void) {}

err_code   CContext::Create (const HWND h_target) {
	h_target;
	TBase::m_error <<__METHOD__<< __s_ok;
	// (1) Creates the fake window;
	TFakeWnd fk_wnd;
	if (fk_wnd.Is_valid() == false)
		return TBase::m_error() = fk_wnd.Error();
	// (2) creating the drawing renderer context;
	context::CDevice dev_ctx;
	if (__failed(dev_ctx.Create(fk_wnd.m_hWnd)))
		return TBase::m_error() = dev_ctx.Error();
	// (3) creates OpenGL context functions' cache;

	this->Cache().Get_all();

	if (this->Cache().Error())
		return TBase::m_error() = this->Cache().Error();

	// (4) gets context;

	return TBase::Error();
}

const
procs::CContext& CContext::Cache (void) const { return this->m_fn_cache; }
procs::CContext& CContext::Cache (void)       { return this->m_fn_cache; }