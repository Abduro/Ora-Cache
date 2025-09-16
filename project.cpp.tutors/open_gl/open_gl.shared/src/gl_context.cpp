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

context::CBase:: CBase (void) : m_drw_ctx(0) { this->m_error()>>__CLASS__<<__METHOD__<<__e_not_inited; }
context::CBase::~CBase (void) { this->Destroy(); }

err_code context::CBase::Destroy(void) {
	this->m_error() <<__METHOD__<<__s_ok;

	// (1) destroys the renderer handle first;
	if (nullptr != this->m_drw_ctx) {
		// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglmakecurrent ;
		if (0 == ::wglMakeCurrent(this->Target().Get(), 0)) {
			__trace_err_3(_T("%s"), (_pc_sz) (this->m_error()(CError::e_cmds::e_get_last)).Print(TError::e_req));
		}
		// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wgldeletecontext ;
		if (0 == ::wglDeleteContext(this->m_drw_ctx)) {
			__trace_err_3(_T("%s"), (_pc_sz) (this->m_error()(CError::e_cmds::e_get_last)).Print(TError::e_req));
		}
		else
			this->m_drw_ctx = nullptr;
	}
	// (2) destroys device context handle; https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-releasedc ;
	if (this->Target().Is_valid())
		if (__failed(this->Target().Free()))
			this->m_error() = this->Target().Error();

	return this->Error()();
}

TErr_ex& context::CBase::Error (void) const { return this->m_error; }

bool   context::CBase::Is_valid (void) const {
	return !!this->m_drw_ctx;
}

HGLRC  context::CBase::Renderer (void) const {
	return this->m_drw_ctx;
}

err_code context::CBase::Set (const HWND _h_target) {
	_h_target;

	if (this->Is_valid()) {
		this->m_error() << (err_code) TErrCodes::eObject::eInited = _T("Draw renderer exists");
		__trace_err_3(_T("%s"), (_pc_sz) this->Error()().Print(TError::e_req)); return this->Error()();
	}

	this->m_error()<<__METHOD__<<__s_ok;

	if (__failed(this->Target().Set(_h_target))) {
		return this->m_error() = this->Target().Error();
	}

	return this->Error()();
}

const
CTarget& context::CBase::Target (void) const { return this->m_target; }
CTarget& context::CBase::Target (void)       { return this->m_target; }    

CBase& context::CBase::operator <<(const HWND _h_wnd) {
	_h_wnd;
	if (this->Is_valid())
		this->Destroy();
	if (this->Error()) // the destruction is failed;
		return *this;
	this->Set(_h_wnd); return *this;
}

/////////////////////////////////////////////////////////////////////////////

context::CTarget:: CTarget (void) :  m_dc_src(0), m_target(0) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
context::CTarget:: CTarget (const HWND _h_wnd) : CTarget() { *this << _h_wnd; }
context::CTarget::~CTarget (void) {
	this->Free ();
}

err_code context::CTarget::Free (void) {
	// https://stackoverflow.com/questions/3945721/win32-why-does-releasedc-say-my-dc-is-not-found ; good answer is >>
	// https://stackoverflow.com/a/3948202/4325555 ; the excerpt : ...Lots of OpenGl samples do rather (to my mind) weired things with device contexts... ;
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Is_valid() == false) {
		this->m_dc_src = nullptr; // for cases when handle of the device context has invalid state, i.e. is closed outside of this class instance;
		return this->Error();    // returns possibly the error state that is set by this::Is_valid();
	}

	if (0 == ::ReleaseDC(this->m_target, this->m_dc_src)) {
		this->m_error << (err_code) TErrCodes::eExecute::eState = _T("Releasing source device context failed");
		__trace_err_3(_T("%s"), (_pc_sz) this->Error().Print(TError::e_req));
	}

	return this->Error();
}

TError& context::CTarget::Error (void) const { return this->m_error; }

bool context::CTarget::Is_valid (void) const {

	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == this->m_dc_src) {
		this->m_error << __e_not_inited;  // the error object set to error state (i.e. error == true);
		return false;
	}

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-getobjecttype ;
	const uint32_t u_dc_type = ::GetObjectType(this->m_dc_src);

	if (OBJ_DC != u_dc_type && OBJ_MEMDC != u_dc_type) // not sure that the source device context may be an in-memory one, but anyway it is okay;
		return false != (this->m_error << __e_inv_arg = _T("Source device context is not valid")).Is();

	return false == this->Error().Is(); // returns 'true' due to the error state is not set to err_code, i.e. everything is '__s_ok';
}

const HDC context::CTarget::Get (void) const { return this->m_dc_src; }
err_code  context::CTarget::Set (const HWND _h_wnd) {
	_h_wnd;

	if (this->Is_valid()) {
		this->m_error << (err_code) TErrCodes::eObject::eInited = _T("Source device context is already set");
		__trace_err_3(_T("%s"), (_pc_sz) this->Error().Print(TError::e_req)); return this->Error();
	}

	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == _h_wnd || false == !!::IsWindow(_h_wnd)) {
		this->m_error << __e_hwnd = _T("Target window handle is invalid");
		__trace_err_3(_T("%s"), (_pc_sz) this->Error().Print(TError::e_req)); return this->Error();
	}

	this->m_target = _h_wnd;
	this->m_dc_src = ::GetDC(_h_wnd);
//	__empty_ln();
	__trace_info_3(_T("context device: handle=%s\n"), (_pc_sz)__address_of(this->m_dc_src));

	return this->Error();
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

context::CDevice:: CDevice (void) : CBase() { CBase::m_error <<__CLASS__; }

context::CDevice:: CDevice (const HWND _h_target) : CDevice() { *this << _h_target; }

context::CDevice::~CDevice (void) { this->Destroy(); }

err_code context::CDevice::Create (const HWND _h_target) {
	_h_target;
	CBase::m_error() <<__METHOD__<<__s_ok;

	if (__failed(CBase::Set(_h_target))) {
		return CBase::Error()();
	}

	PIXELFORMATDESCRIPTOR px_fmt_desc = {0}; // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-pixelformatdescriptor ;
	// https://www.khronos.org/opengl/wiki/Creating_an_OpenGL_Context_(WGL) << there is the example of how to do that;
	px_fmt_desc.nSize      = sizeof(PIXELFORMATDESCRIPTOR);
	px_fmt_desc.nVersion   = 1;
	px_fmt_desc.dwFlags    = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL/* | PFD_DOUBLEBUFFER*/;
	px_fmt_desc.iPixelType = PFD_TYPE_RGBA;
	px_fmt_desc.cColorBits = 32; // colordepth of the framebuffer;
	px_fmt_desc.cAlphaBits = 8;  // the number of bits for the stencilbuffer;
	px_fmt_desc.cDepthBits = 24; // the number of bits for the depthbuffer;

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-choosepixelformat ;
	int32_t n_px_format = ::ChoosePixelFormat(CBase::Target().Get(), &px_fmt_desc);
	if (0== n_px_format) {
		__trace_err_3(_T("%s"), (_pc_sz) (CBase::m_error()(CError::e_cmds::e_get_last)).Print(TError::e_req));
		return CBase::Error()();
	}

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-setpixelformat ;
	if (false == !!::SetPixelFormat(CBase::Target().Get(), n_px_format, &px_fmt_desc)) {
		__trace_err_3(_T("%s"), (_pc_sz) (CBase::m_error()(CError::e_cmds::e_get_last)).Print(TError::e_req));
		return CBase::Error()();
	}

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglcreatecontext ;
	this->m_drw_ctx = ::wglCreateContext(CBase::Target().Get());
	if ( 0 == this->m_drw_ctx) {
		__trace_err_3(_T("%s"), (_pc_sz) (CBase::m_error()(CError::e_cmds::e_get_last)).Print(TError::e_req));
		return CBase::Error()();
	}

	if (0 == ::wglMakeCurrent(CBase::Target().Get(), this->m_drw_ctx)) { // it is required, otherwise nothing will work;
		__trace_err_3(_T("%s"), (_pc_sz) (CBase::m_error()(CError::e_cmds::e_get_last)).Print(TError::e_req));
	}
	return CBase::Error()();
}

CDevice& context::CDevice::operator <<(const HWND _h_target) {
	_h_target;
	(CBase&)*this << _h_target;
	this->Create(_h_target); return *this; // for getting the result of creation the error state should be checked;
}

/////////////////////////////////////////////////////////////////////////////

#include "open_gl_tutor.0.fake.h"
#pragma comment(lib, "gl.tutor.0.fake.lib") // this is required due to the fake window is used in the first step;

#include "gl_format.h"

using namespace ex_ui::draw::open_gl::format;

CContext:: CContext (void) : TBase() { TBase::m_error()>>__CLASS__<<__METHOD__<<__e_not_inited; }
CContext::~CContext (void) {}

err_code   CContext::Create (const HWND h_target, const uint32_t _u_gl_major_ver, const uint32_t _u_gl_miner_ver) {
	h_target; _u_gl_major_ver; _u_gl_miner_ver;
	TBase::m_error() <<__METHOD__<< __s_ok;
	// (1) Creates the fake window;
	TFakeWnd fk_wnd;
	if (fk_wnd.Is_valid() == false)
		return TBase::m_error() = fk_wnd.Error();
	// (2) creating the drawing renderer context;
	context::CDevice dev_ctx;
	if (__failed(dev_ctx.Create(fk_wnd.m_hWnd)))
		return TBase::m_error() = dev_ctx.Error()();
	// (3) creates OpenGL context functions' cache;

	this->Cache().Get_all();

	if (this->Cache().Error())
		return TBase::m_error() = this->Cache().Error();

	// (4) gets context;
	// (4.a) get target window context device first;

	if (__failed(TBase::Set(h_target)) || false == TBase::Target().Is_valid())
		return TBase::Error()();

	// (4.b) chooses the pixel format;
	CAtt_set_pixels pxl_atts; // no error check for this time yet;

	uint32_t n_count = 0;
	int32_t p_formats = 0;

	// https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_pixel_format.txt ; this file contains the function description;
	// https://www.khronos.org/opengl/wiki/Creating_an_OpenGL_Context_(WGL) ; << there is the example of how to use the function;

	const int32_t n_result = this->Cache().ChoosePxFormatArb(
		TBase::Target().Get(), pxl_atts.IAtt_Get_Int_Ptr(), nullptr, 1, &p_formats, &n_count
	);

#define btns_info (MB_OK|MB_ICONINFORMATION)
#define btns_warn (MB_OK|MB_ICONEXCLAMATION)

//	CString cs_cap = TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
//	CString cs_fmts = TString().Format(_T("formats: %u; count: %u;"), p_formats, n_count);
#if (0) // wrong way;
	CString cs_fmt_pairs;
	int32_t n_fmt_num = 0;
	int32_t* p_data = &p_formats;

	while (n_count > 0 && !!p_formats) {
		cs_fmt_pairs += TString().Format(_T("att #%u: id=%u;val=%u;"), n_fmt_num, &p_data[n_fmt_num + 0], &p_data[n_fmt_num + 1]);
		n_fmt_num += 1;
		n_count -= 2;
	}
#endif
	bool b_can_go_ahead = false;

	if (0 == n_result) { // the failure has occurred: the format cannot be chosen for creating the context;
		if (this->Cache().Error()) { // checks for failure of loading the function pointer;
			this->Cache().Error().Show();
			TBase::m_error() = this->Cache().Error();
		}
		else { // otherwise checks the OpenGL error that has been thrown;
			TBase::m_error.Get_last();
			TBase::m_error().Show();
		}
	}
	else if (nullptr != &p_formats && true == !!n_count) { b_can_go_ahead = true; }
	else { b_can_go_ahead = true; }
#if (0)
	::MessageBox(
			0, (_pc_sz) cs_fmts,
			   (_pc_sz) cs_cap , btns_info
		);
	::MessageBox(
			0, (_pc_sz) pxl_atts.Print(),
			   (_pc_sz) cs_cap , btns_info
		);
#else
//	__trace_info_3(_T("%s\n"), (_pc_sz) cs_fmts);
//	__trace_info_3(_T("%s\n"), (_pc_sz) cs_cap);
#endif
	if (false == b_can_go_ahead)
		return TBase::Error()();

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-describepixelformat ;
	PIXELFORMATDESCRIPTOR pfd = {0};
	if (0 == ::DescribePixelFormat(TBase::Target().Get(), p_formats, sizeof(PIXELFORMATDESCRIPTOR), &pfd))
		return TBase::m_error().Last();
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-setpixelformat ;
	if (false ==!!::SetPixelFormat(TBase::Target().Get(), p_formats, &pfd))
		return TBase::m_error().Last();

	CAtt_set_ctx ctx_atts(_u_gl_major_ver, _u_gl_miner_ver);
	// https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_create_context.txt ;
	this->m_drw_ctx = this->Cache().CreateCtxAttsArb(TBase::Target().Get(), 0, ctx_atts.IAtt_Get_Int_Ptr());
	if (nullptr == this->m_drw_ctx) {
		return TBase::m_error().Last(); // the excerpt: Extended error information can be obtained with GetLastError().
	}

	if (0 == ::wglMakeCurrent(CBase::Target().Get(), this->m_drw_ctx)) { // it is required, otherwise nothing will work;
		__trace_err_3(_T("%s"), (_pc_sz) (CBase::m_error()(CError::e_cmds::e_get_last)).Print(TError::e_req));
#if (0)
		::MessageBox(
			0, (_pc_sz) _T("wglMakeCurrent is failed") ,
			   (_pc_sz) cs_cap , btns_warn
		);
#endif
	}

	return TBase::Error()();
}

const
procs::CContext& CContext::Cache (void) const { return this->m_fn_cache; }
procs::CContext& CContext::Cache (void)       { return this->m_fn_cache; }