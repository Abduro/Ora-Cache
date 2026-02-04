/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Sep-2025 at 18:26:16.505, UTC+4, Batumi, Thursday;
	This is Ebo_Pack tutorials' shared app/main window interace implementation file;
*/
#include "win.gui.wnd.h"

#include "shared.dbg.h"
#include "shared.theme.h"

#include "color._defs.h"
#include "sys.registry.h"

using namespace shared::gui;
using namespace shared::sys_core::storage;

using CPosition = CFrame::CPosition;

#pragma region cls::CAppWnd{}

CAppWnd:: CAppWnd (void) { TBase::m_error.Class(TString().Format(_T("%s::%s"), (_pc_sz)__CLASS__, TBase::Cls_name()), false); }
CAppWnd::~CAppWnd (void) { if (TBase::Is_valid()) this->Destroy(); }

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

	if (__succeeded(TBase::Create(_p_cls_name, _p_title, this->Frame().Position().Get(), _b_visible, HWND_DESKTOP))) {
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
	return TBase::Destroy(); // nonsense: the main window is already destroyed by the base class message handler;
}

const
CFrame&  CAppWnd::Frame (void) const { return this->m_frame; }
CFrame&  CAppWnd::Frame (void)       { return this->m_frame; }

err_code  CAppWnd::IMsg_OnMessage (const uint32_t _u_code, const w_param _w_param, const l_param _l_param) {
	_u_code; _w_param; _l_param;
	err_code n_result = __s_false; // not handled;
	if (WM_CLOSE == _u_code) {
		bool b_break = false; b_break = !b_break; // nothing to do here: the layout handles this message too;
	}
	if (WM_DESTROY == _u_code) {
		__trace_warn_3(_T("The window handle = %s is being destroyed;\n"), TString()._addr_of(this->Handle(), _T("0x%08x")));
	}
	if (WM_PAINT == _u_code) {
		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-fillrect ;
		// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createsolidbrush ;
		class CBrush {
		public:
			 CBrush (const rgb_color _clr) : m_brush(nullptr) { this->m_brush = ::CreateSolidBrush(_clr); }
			~CBrush (void) { if (this->m_brush){ ::DeleteObject(this->m_brush); this->m_brush = nullptr; }}
			HBRUSH  Get (void) const { return this->m_brush; }
		private:
			HBRUSH m_brush;
		};

		// https://learn.microsoft.com/en-us/windows/win32/gdi/wm-paint ; returned result: 0 - handled; otherwise not handled;
		PAINTSTRUCT ps = {0};
		const HDC h_dc = ::BeginPaint(TBase::Handle(), &ps);
		::FillRect(h_dc, &ps.rcPaint, CBrush(::Get_theme().Border()).Get());
		::EndPaint(TBase::Handle(), &ps);

		n_result = 0;
	}

	if (IMsg_Handler::_n_not_handled == this->Layout().IMsg_OnMessage(_u_code, _w_param, _l_param))
		n_result = TBase::IMsg_OnMessage(_u_code, _w_param, _l_param); // it is ***mandatory***, otherwise not handled messages will be lost;

	return n_result;
}
const
shared::gui::CLayout& CAppWnd::Layout(void) const { return this->m_layout; }
shared::gui::CLayout& CAppWnd::Layout(void)       { return this->m_layout; }

const
CAppWnd::TBase& CAppWnd::operator ()(void) const { return (const TBase&)*this; }
CAppWnd::TBase& CAppWnd::operator ()(void) { return (TBase&)*this; }

shared::gui::CAppWnd& ::Get_app_wnd (void) {
	static shared::gui::CAppWnd app_wnd;
	return app_wnd;
}

#pragma endregion
#pragma region cls::CFrame::CIcons{}

CFrame::CIcons:: CIcons (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError&   CFrame::CIcons::Error (void) const { return this->m_error; }
err_code  CFrame::CIcons::Set (const uint16_t _u_res_id) {
	_u_res_id;
	this->m_error <<__METHOD__<<__s_ok;
	
	if (false == !!_u_res_id)
		return this->m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_arg: res_id (%u) is not valid"), _u_res_id);

	CAppWnd& app_wnd = ::Get_app_wnd();

	if (app_wnd.Is_valid() == false)
		return this->m_error << __e_hwnd = _T("#__e_hwnd: the window handle is invalid");
	/* https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-seticon ;
	   there is no error handling: sending this message does not set the last error in case of failure;
	   the following reqs must be met:
	   the icon being referenced must have predefined icon size: 16x16 px for small icon and 32x32 px for the large one;
	*/
	::SendMessage(app_wnd()(), WM_SETICON, 0, (l_param) ex_ui::resource::CIcon().Load(_u_res_id, 0));
	::SendMessage(app_wnd()(), WM_SETICON, 1, (l_param) ex_ui::resource::CIcon().Load(_u_res_id, 1));

	return this->Error();
}

#pragma endregion
#pragma region cls::CFrame{}

CFrame:: CFrame (void) {}
CFrame::~CFrame (void) {}

const
CFrame::CIcons& CFrame::Icons (void) const { return this->m_icons; }
CFrame::CIcons& CFrame::Icons (void)       { return this->m_icons; }

const
CPosition& CFrame::Position (void) const { return this->m_pos; }
CPosition& CFrame::Position (void)       { return this->m_pos; }
const
CFrame::CSize& CFrame::Size (void) const { return this->m_size; }
CFrame::CSize& CFrame::Size (void)       { return this->m_size; }

#pragma endregion
#pragma region cls::CPosition{}

CPosition:: CPosition (void) : m_rect{0} { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CPosition::~CPosition (void) {}

TError&  CPosition::Error (void) const { return this->m_error; }

const
t_rect&  CPosition::Get (void) const { return this->m_rect; }
bool     CPosition::Set (const t_rect& _rect) {
	_rect;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-equalrect ;
	const bool b_changed = !::EqualRect(&_rect, &this->Get()); if (b_changed) this->m_rect = _rect; return b_changed;
}

err_code CPosition::Load (void) {
	this->m_error <<__METHOD__<<__s_ok;

	using CRegWnd = route::CApp::CWindow;
	using e_pos = CRegWnd::e_pos;
	const CRegWnd& wnd = ::Get_reg_router().App().Window();

	TRegKeyEx reg_key;
	this->m_rect.left   = reg_key.Value().GetDword(wnd.Position(), wnd.Side(e_pos::e_left));   if (reg_key.Error()) { this->m_error = reg_key.Error(); }
	this->m_rect.right  = reg_key.Value().GetDword(wnd.Position(), wnd.Side(e_pos::e_right));  if (reg_key.Error()) { this->m_error = reg_key.Error(); }
	this->m_rect.top    = reg_key.Value().GetDword(wnd.Position(), wnd.Side(e_pos::e_top));    if (reg_key.Error()) { this->m_error = reg_key.Error(); }
	this->m_rect.bottom = reg_key.Value().GetDword(wnd.Position(), wnd.Side(e_pos::e_bottom)); if (reg_key.Error()) { this->m_error = reg_key.Error(); }

	if (::IsRectEmpty(&this->m_rect)) {
	}

	return this->Error();
}

err_code CPosition::Save (void) {
	this->m_error <<__METHOD__<<__s_ok;

	using CRegWnd = route::CApp::CWindow;
	using e_pos = CRegWnd::e_pos;
	const CRegWnd& wnd = ::Get_reg_router().App().Window();
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowrect ;
	t_rect rect = {0};
	if (false == !!::GetWindowRect(::Get_app_wnd().Handle(), &rect)) {
		return this->m_error.Last();
	}

	TRegKeyEx reg_key;
	
	reg_key.Value()() << wnd.Position();
	reg_key.Value()() >> wnd.Side(e_pos::e_left); if (__failed(reg_key.Value().Set(rect.left))) this->m_error = reg_key.Error();
	reg_key.Value()() >> wnd.Side(e_pos::e_right); if (__failed(reg_key.Value().Set(rect.right))) this->m_error = reg_key.Error();
	reg_key.Value()() >> wnd.Side(e_pos::e_top); if (__failed(reg_key.Value().Set(rect.top))) this->m_error = reg_key.Error();
	reg_key.Value()() >> wnd.Side(e_pos::e_bottom); if (__failed(reg_key.Value().Set(rect.bottom))) this->m_error = reg_key.Error();

	return this->Error();
}

const
t_rect&  CPosition::operator ()(void) const { return this->m_rect; }
t_rect&  CPosition::operator ()(void)       { return this->m_rect; }

CPosition& CPosition::operator <<(const t_rect& _rect) { this->Set(_rect); return *this; }

#pragma endregion
#pragma region cls::CSize{}

CFrame::CSize::CSize (void) : m_locked(true) {}

bool CFrame::CSize::Is_locked(void) const { return this->m_locked; }
bool CFrame::CSize::Is_locked(const bool _b_state) {
	_b_state;
	const bool b_changed = this->Is_locked() != _b_state;
	if (b_changed)
		this->m_locked = _b_state;
	return b_changed;
}

#pragma endregion