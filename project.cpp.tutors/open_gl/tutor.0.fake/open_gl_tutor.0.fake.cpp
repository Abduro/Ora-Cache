/*
	Created by Tech_dog (ebontrop@gmail.com) 0n 18-Aug-2025 at 11:10:36.540, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL fake (message-only) window interface implementation file;
*/
#include "open_gl_tutor.0.fake.h"
#include "shared.dbg.h"
#include "shared.preproc.h"

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

CWnd:: CWnd (void) : TWindow(), m_h_dc(0) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited;

	TWindow::Create(HWND_MESSAGE);

	if (false == TWindow::IsWindow()) {
		this->m_error.Last();
		__trace_err_3(_T("%s\n"), (_pc_sz) this->Error().Print(TError::e_req)); return;
	}
	else {
		this->m_error << __s_ok;
		this->m_h_dc = TWindow::GetDC();
	//	__empty_ln();
		__trace_info_3(_T("context device: handle=%s\n"), (_pc_sz)__address_of(this->Get_ctx()));
	}
}

CWnd::~CWnd (void) {
	this->m_error << __METHOD__ << __s_ok;

	// (1) destroys device context handle;
	if (nullptr != this->m_h_dc) {
		TWindow::ReleaseDC(this->m_h_dc); this->m_h_dc = nullptr; // error code is not analized here yet;
	}
	// (2) destroys the fake window itself;
	if (TWindow::IsWindow())
		TWindow::DestroyWindow(); // the error code is not important yet;
}

TError& CWnd::Error (void) const { return this->m_error; }
bool    CWnd::Is_valid (void) const { return false == this->Error(); }

const
HDC&    CWnd::Get_ctx  (void) const { return this->m_h_dc; }

CWnd::operator const HDC& (void) const { return this->Get_ctx(); }