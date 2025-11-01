/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Sep-2025 at 18:26:16.505, UTC+4, Batumi, Thursday;
	This is Ebo_Pack tutorials' shared app/main window interace implementation file;
*/
#include "win.gui.wnd.h"
#include "shared.dbg.h"

using namespace shared::gui;

CFrame::CIcons:: CIcons (CFrame* const _p_frm) : m_p_frm(_p_frm) {}

err_code  CFrame::CIcons::Set (const uint16_t _u_res_id) {
	_u_res_id;
	err_code n_result = __s_ok;
	if (nullptr == this->m_p_frm)
		return n_result = __e_pointer;

	if (false == !!_u_res_id)
		return n_result = __e_invalid_arg;

	if (false == !!this->m_p_frm->Window().m_hWnd || false == !!this->m_p_frm->Window().IsWindow())
		return n_result = __e_hwnd;

	// no error handling of icon assignment through sending the message; 
	this->m_p_frm->Window().SendMessage(WM_SETICON, 0, (l_param) ex_ui::resource::CIcon().Load(_u_res_id, 0));
	this->m_p_frm->Window().SendMessage(WM_SETICON, 1, (l_param) ex_ui::resource::CIcon().Load(_u_res_id, 1));

	return n_result;
}

/////////////////////////////////////////////////////////////////////////////

CFrame:: CFrame (void) : m_icons(this) {}
CFrame::~CFrame (void) {}

const
CFrame::CIcons& CFrame::Icons (void) const { return this->m_icons; }
CFrame::CIcons& CFrame::Icons (void)       { return this->m_icons; }

const
CWindow&  CFrame::Window (void) const { return this->m_owner; }
CWindow&  CFrame::Window (void)       { return this->m_owner; }

/////////////////////////////////////////////////////////////////////////////

CAppWnd:: CAppWnd (void) { TBase::m_error.Class(TString().Format(_T("%s::%s"), (_pc_sz)__CLASS__, TBase::Cls_name()), false); }
CAppWnd::~CAppWnd (void) { if (TBase::Is_valid()) this->Destroy(); }

err_code  CAppWnd::IMsg_OnMessage (const uint32_t _u_code, const w_param _w_param, const l_param _l_param) {
	_u_code; _w_param; _l_param;
	err_code n_result = __s_false; // not handled;

	if (IMsg_Handler::_n_not_handled == this->Layout().IMsg_OnMessage(_u_code, _w_param, _l_param))
		n_result = TBase::IMsg_OnMessage(_u_code, _w_param, _l_param); // it is ***mandatory***, otherwise not handled messages will be lost;

	return n_result;
}

#if (1)
err_code CAppWnd::Create (_pc_sz _p_cls_name, _pc_sz _p_title, const bool _b_visible) {
	_p_cls_name; _p_title; _b_visible;
	TBase::m_error <<__METHOD__<<__s_ok;

	__trace::Use_con(false); // outputs to VS debug window; 

	// the main window class must be registered first if it is not yet;
	CWndCls wnd_cls;

	if (__failed(wnd_cls.Register(_p_cls_name))) {
		__trace_err_3(_T("%s\n"), (_pc_sz) wnd_cls.Error().Print(TError::e_req));
		return TBase::m_error = wnd_cls.Error();
	}

	TBase::Styles().Default_for_app();

	if (__failed(TBase::m_error << this->Layout().Recalc())) {
		__trace_err_3(_T("%s\n"), (_pc_sz) TBase::m_error.Print(TError::e_req));
	}

	if (__succeeded(TBase::Create(_p_cls_name, _p_title, this->Layout().Main().Position(), _b_visible, HWND_DESKTOP))) {
		this->Frame().Window() = TBase::Handle();
		this->Layout().Main().Target(*this);
#if (0) // the stupid approach is commented out;
		// the parent class of this one has successfully created a window and can call the message handler itself,
		// overriding of the virtual function should work properly, but for better clarity, the handler is called from here;
		const t_rect& rect = this->Layout().Main().Position();
		// https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-create ;
		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-createstructw ;
		CREATESTRUCT crt_data = {
			0, 0, 0, ::GetParent((*this)()), __H(rect), __W(rect), rect.top, rect.left, 0, 0, 0, 0
		};
		this->IMsg_OnMessage(WM_CREATE, 0, (l_param)&crt_data);
#endif
	}
	else
		this->Frame().Window() = HWND_DESKTOP; // the same as (HWND)nullptr;

	return TBase::Error();
}
#else
err_code CAppWnd::Create (_pc_sz _p_cls_name, _pc_sz _p_title, const bool _b_visible) {
	_p_cls_name; _p_title; _b_visible;
	// the main window class must be registered first if it is not yet;
	CWndCls wnd_cls;

	if (__failed(wnd_cls.Register(_p_cls_name))) {
		__trace_err_3(_T("%s\n"), (_pc_sz) wnd_cls.Error().Print(TError::e_req));
		return TBase::m_error = wnd_cls.Error();
	}

	// ToDo: it looks like casting signed to unsigned data type is not good approach and must be reviewed;
#if (0)
	const
	t_size cl_size = CRatios().Get().at(0);
	t_rect cl_rect = CPrimary().Centered(t_size_u{(uint32_t)cl_size.cx, (uint32_t)cl_size.cy});
#else
	t_rect rc_pos  = layout::CPrimary().Centered(layout::t_size_u{uint32_t(layout::CRatios().Get().at(0).cx), uint32_t(layout::CRatios().Get().at(0).cy)});
#endif
	TBase::Styles().Default_for_app();

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-adjustwindowrect ;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-adjustwindowrectex ;

	if (false == !!::AdjustWindowRect(&rc_pos, TBase::Styles().Std(), false)) {
		__trace_err_3(_T("%s\n"), (_pc_sz) TBase::Error().Print(TError::e_req)); // just for indicating the error state and continue;
	}

	if (__succeeded(TBase::Create(_p_cls_name, _p_title, rc_pos, _b_visible, HWND_DESKTOP)))
		this->Frame().Window() = TBase::Handle();
	else
		this->Frame().Window() = HWND_DESKTOP; // the same as (HWND)nullptr;

	return TBase::Error(); // it is very important to set error state properly, otherwise the module will exit immediately;
}
#endif

err_code CAppWnd::Destroy (void) {
	/* https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-destroy ;
	   https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-destroywindow :
	   the excerpt from the above article:
	   ...function first destroys child or owned windows, and then it destroys the parent or owner window...
	*/
	this->Frame().Window() = (HWND)nullptr;
	return TBase::Destroy(); // nonsense: the main window is already destroyed by the base class message handler;
}

const
CFrame&  CAppWnd::Frame (void) const { return this->m_frame; }
CFrame&  CAppWnd::Frame (void)       { return this->m_frame; }

const
shared::gui::CLayout& CAppWnd::Layout(void) const { return this->m_layout; }
shared::gui::CLayout& CAppWnd::Layout(void)       { return this->m_layout; }

const
CAppWnd::TBase& CAppWnd::operator ()(void) const { return (const TBase&)*this; }
CAppWnd::TBase& CAppWnd::operator ()(void) { return (TBase&)*this; }

shared::gui::CAppWnd&  ::Get_app_wnd (void) {
	static shared::gui::CAppWnd app_wnd;
	return app_wnd;
}