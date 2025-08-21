/*
	Created by Tech_dog (ebontrop@gmail.com) 0n 18-Aug-2025 at 11:10:36.540, UTC+4, Batumi, Monday;
	This is OpenGL tutorial of the creating fake content interface implementation file;
*/
#include "open_gl_tutor.0.fake.h"

using namespace ex_ui::draw::open_gl::fake;

#ifndef _T
#ifndef  _UNICODE
#define _T(x)      x
#else
#define _T(x) L ## x
#endif
#endif

namespace ex_ui { namespace draw { namespace open_gl { namespace fake { namespace _impl {

	using namespace shared::defs;

}}}}}
using namespace ex_ui::draw::open_gl::fake::_impl;

CWnd:: CWnd (void) : TWindow(), m_h_dc(0), m_h_render(0) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited;

	TWindow::Create(HWND_MESSAGE);

	if (false == TWindow::IsWindow()) {
		this->m_error.Last();
		__trace_err_3(_T("%s"), (_pc_sz) this->Error().Print(TError::e_req)); return;
	}
	else {
		this->m_error << __s_ok;
		this->m_h_dc = TWindow::GetDC();
		__empty_ln();
		__trace_info_3(_T("context device: handle=%s\n"), (_pc_sz)__address_of(this->Get_ctx()));
	}

	PIXELFORMATDESCRIPTOR px_fmt_desc = {0}; // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-pixelformatdescriptor ;

	px_fmt_desc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	px_fmt_desc.nVersion = 1;
	px_fmt_desc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	px_fmt_desc.iPixelType = PFD_TYPE_RGBA;
	px_fmt_desc.cColorBits = 32;
	px_fmt_desc.cAlphaBits = 8;
	px_fmt_desc.cDepthBits = 24;
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-choosepixelformat ;
	int32_t n_px_format = ::ChoosePixelFormat(this->Get_ctx(), &px_fmt_desc);
	if (0== n_px_format) {
		this->m_error.Last(); return;
	}
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-setpixelformat ;
	if (false == !!::SetPixelFormat(this->Get_ctx(), n_px_format, &px_fmt_desc)) {
		this->m_error.Last(); return;
	}
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglcreatecontext ;
	this->m_h_render = ::wglCreateContext(this->Get_ctx());
	if ( 0 == this->m_h_render) {
		this->m_error.Last(); return;
	}
}
CWnd::~CWnd (void) {
	// (1) destroys the renderer handle first;

	this->m_error << __METHOD__ << __s_ok;

	if (nullptr != this->m_h_render) {
		// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wglmakecurrent ;
		if (0 == ::wglMakeCurrent(this->Get_ctx(), 0)) { this->m_error.Last(); ATLASSERT(FALSE); }
		// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-wgldeletecontext ;
		if (0 == ::wglDeleteContext(this->m_h_render)) { this->m_error.Last(); ATLASSERT(FALSE); }
		else this->m_h_render = nullptr;
	}
	// (2) destroys device context handle;
	if (nullptr != this->m_h_dc) {
		TWindow::ReleaseDC(this->m_h_dc); this->m_h_dc = nullptr; // error code is not analized here yet;
	}
	// (3) destroys the fake window itself;
	if (TWindow::IsWindow())
		TWindow::DestroyWindow(); // the error code is not important yet;
}

TError& CWnd::Error (void) const { return this->m_error; }
bool    CWnd::Is_valid (void) const { return false == this->Error(); }

const
HDC&    CWnd::Get_ctx  (void) const { return this->m_h_dc; }

CWnd::operator const HDC& (void) const { return this->Get_ctx(); }