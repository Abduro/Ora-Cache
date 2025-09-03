/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Sep-2025 at 13:37:58.720, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' context window interface implementation file;
*/
#include "open_gl_tutor.1.wnd.h"
#include "open_gl_tutor.1.res.h"
#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::context;

context::CWnd:: CWnd (void) : TBase() { TBase::m_error >>__CLASS__; }
context::CWnd::~CWnd (void) { } // parent class object will destroy window created automatically on its (parent) destruction;


err_code context::CWnd::Create (void) {

	TBase::m_error << __METHOD__ << __s_ok;

	if (TWindow::Is_valid())
		return TBase::m_error << (err_code) TErrCodes::eObject::eExists;

	static _pc_sz p_cls_name = _T("__open_gl_ctx_wnd");

	CWndCls wnd_cls;

	if (__failed(wnd_cls.Register(p_cls_name))) {
		__trace_err_3(_T("%s"), (_pc_sz) wnd_cls.Error().Print(TError::e_req));
		return TBase::m_error = wnd_cls.Error();
	}
	// ToDo: it looks like casting signed to unsigned data type is not good approach and must be reviewed;
#if (0)
	const
	t_size cl_size = CRatios().Get().at(0);
	t_rect cl_rect = CPrimary().Centered(t_size_u{(uint32_t)cl_size.cx, (uint32_t)cl_size.cy});
#else
	t_rect rc_pos  = CPrimary().Centered(t_size_u{uint32_t(CRatios().Get().at(0).cx), uint32_t(CRatios().Get().at(0).cy)});
#endif
	TBase::Styles().Default_for_app();
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-adjustwindowrect ;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-adjustwindowrectex ;
	if (false == !!::AdjustWindowRect(&rc_pos, TBase::Styles().Std(), false)) {
		__trace_err_3(_T("%s"), (_pc_sz) TBase::Error().Print(TError::e_req)); // just for indicating the error state and continue;
	}

	if (__failed(TBase::Create(
		p_cls_name, TString().Format(_T("cls::[%s:%s]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__), rc_pos
	))) {
	}
	else {
		TBase::m_error << TBase::Icons().Set(IDR_TUTOR_0_ICO, TBase::Handle());
		if (TBase::Error()) {
			__trace_err_3(_T("%s"), (_pc_sz) TBase::Error().Print(TError::e_req));
		}
	}

	return TBase::Error(); // it is very important to set error state properly, otherwise the module will exit immediately;
}