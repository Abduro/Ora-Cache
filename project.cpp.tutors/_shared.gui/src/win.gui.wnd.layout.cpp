/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Sep-2025 at 05:29:19.252, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' shared GUI window layout interface implementation file;
*/
#include "win.gui.wnd.layout.h"
#include "shared.wnd.base.h"
#include "shared.wnd.msg.h"

using namespace shared::gui;
using namespace shared::gui::docking;

using namespace ex_ui::popup;

#ifndef __H
#define __H(_rect) (_rect.bottom - _rect.top)
#endif
#ifndef __W
#define __W(_rect) (_rect.right - _rect.left)
#endif

/////////////////////////////////////////////////////////////////////////////

CPane:: CPane (void) : m_wnd(0) {}

bool    CPane::Is_valid (void) const { return (0 != this->m_wnd && ::IsWindow(this->m_wnd)); }

const
CSide&  CPane::Side (void) const { return this->m_side; }
CSide&  CPane::Side (void)       { return this->m_side; }
const
CSize&  CPane::Size (void) const { return this->m_size; }
CSize&  CPane::Size (void)       { return this->m_size; }

const
HWND     CPane::Target (void) const { return this->m_wnd; }
err_code CPane::Target (const HWND _h_target) {
	_h_target;
	if (0 == _h_target || false == !!::IsWindow(_h_target))
		return __e_hwnd;

	this->m_wnd = _h_target;

	return __s_ok;
}

/////////////////////////////////////////////////////////////////////////////

CSide:: CSide (void) : m_area(e_areas::e_left) {}
CSide:: CSide (const e_areas _area) : CSide() { *this << _area; }

CSide::e_areas CSide::Value (void) const { return this->m_area; }

bool CSide::Value (const e_areas _area) {
	_area;
	const bool b_changed = this->Value() != _area;
	if (b_changed)
		this->m_area = _area;
	return b_changed;
}

CSide&  CSide::operator <<(const e_areas _area) { this->Value(_area); return *this; }

/////////////////////////////////////////////////////////////////////////////

CSize:: CSize (const long _l_cx, const long _l_cy) { *this << CValue(_l_cx) >> CValue(_l_cy); }
CSize:: CSize (const CValue& _cx, const CValue& _cy) { *this << _cx >> _cy; }

const
CValue& CSize::Height (void) const { return this->m_height; }
CValue& CSize::Height (void)       { return this->m_height; }
bool    CSize::Height (const long _l_value, const CValue::e_ctrl _e_type) {
	_l_value; _e_type;
	return this->Height().Set(_l_value, _e_type);
}

bool CSize::Is_locked (void) const { return (this->Height().Is_fixed() && this->Height().Is_fixed()); }

const
CValue& CSize::Width (void) const { return this->m_width; }
CValue& CSize::Width (void)       { return this->m_width; }
bool    CSize::Width (const long _l_value, const CValue::e_ctrl _e_type) {
	_l_value; _e_type;
	return this->Width().Set(_l_value, _e_type);
}

CSize&  CSize::operator >>(const CValue& _v_height) { this->Height().Set(_v_height.Get(), _v_height.Ctrl()); return *this; }
CSize&  CSize::operator <<(const CValue& _v_width) { this->Width().Set(_v_width.Get(), _v_width.Ctrl()); return *this; }

/////////////////////////////////////////////////////////////////////////////

CValue:: CValue (const long _l_value, const e_ctrl _e_ctrl_type) : m_ctrl(_e_ctrl_type), m_value(_l_value) {}

CValue::e_ctrl CValue::Ctrl (void) const { return this->m_ctrl; }
bool CValue::Ctrl (const e_ctrl _e_type) {
	_e_type;
	const bool b_changed = this->Ctrl() != _e_type;
	if (b_changed)
		this->m_ctrl = _e_type;
	return b_changed;
}

bool CValue::Is_auto (void) const { return this->Ctrl() == e_ctrl::e_auto; }
bool CValue::Is_auto (const bool b_state) {
	return this->Ctrl(b_state ? e_ctrl::e_auto : e_ctrl::e_fixed);
}

bool CValue::Is_fixed (void) const { return this->Ctrl() == e_ctrl::e_fixed; }
bool CValue::Is_fixed (const bool b_state) {
	return this->Ctrl(b_state ? e_ctrl::e_fixed : e_ctrl::e_auto);
}
long CValue::Get (void) const { return this->m_value; }
bool CValue::Set (const long _l_value) {
	_l_value;
	const bool b_changed = this->Get() != _l_value;
	if (b_changed)
		this->m_value = _l_value;
	return b_changed;
}

bool    CValue::Set (const long _l_value, const e_ctrl _ctrl) {
	_l_value; _ctrl;
	bool b_changed = false;

	if (this->Set(_l_value)) b_changed = true;
	if (this->Ctrl(_ctrl)) b_changed = true;

	return b_changed;
}

CValue& CValue::operator <<(const e_ctrl _e_type) { this->Ctrl(_e_type); return *this; }
CValue& CValue::operator <<(const long _l_value) { this->Set(_l_value); return *this; }

CValue::operator long (void) const { return this->Get(); }

/////////////////////////////////////////////////////////////////////////////

CLayout:: CLayout (void) : m_wait(*this) { this->Bottom().Side().Value(CSide::e_btm); this->Top().Side().Value(CSide::e_top); }
CLayout::~CLayout (void) {
	if (false == this->m_wait.IsValid())
		this->m_wait.Destroy();
}

const
CPane&  CLayout::Bottom (void) const { return this->m_low; }
CPane&  CLayout::Bottom (void)       { return this->m_low; }

err_code CLayout::IMsg_OnMessage (const uint32_t _u_code, const w_param _w_param, const l_param _l_param) {
	_u_code; _w_param; _l_param;
	err_code n_result = IMsg_Handler::_n_not_handled;
	switch (_u_code) {
	case WM_ACTIVATE:{
		const bool b_activated = (WA_INACTIVE != _w_param); // https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-activate ;
		const HWND h_after = b_activated ?  HWND_TOPMOST : HWND_NOTOPMOST;

		if (false == b_activated) {
			if (false == this->m_wait.IsValid())
				this->m_wait.Create(555);
		}
		else
			this->m_wait.Destroy();

		::SetWindowPos(this->Bottom().Target(), h_after, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE|SWP_NOACTIVATE);
		n_result = __s_ok; // this message is handled;
	} break;
	case WM_MOVING: { // https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-moving ;
#if (1)
		t_rect* p_rect_pos = reinterpret_cast<t_rect*>(_l_param); // the input rectangle is in screen coordinates;
		if (p_rect_pos) {
			this->Update(p_rect_pos);
		}
		else n_result = __s_ok; // does not bother; that means the message is not handled;
#else
		n_result = __s_ok;
#endif
	} break;
	case WM_WINDOWPOSCHANGING:
		{
			// https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-windowposchanging ;
			_w_param;  // not used;
			WINDOWPOS* p_wnd_pos = reinterpret_cast<WINDOWPOS*>(_l_param);
			if (nullptr != p_wnd_pos) {
#if (0)
				__trace_info(_T("x=%d;y=%d;cx=%d;cy=%d"), p_wnd_pos->x, p_wnd_pos->y, p_wnd_pos->cx, p_wnd_pos->cy);
#endif
				// locks the size change;
				if (this->Main().Size().Is_locked()) {
					p_wnd_pos->cx = this->Main().Size().Width();
					p_wnd_pos->cy = this->Main().Size().Height();
				}
				// https://stackoverflow.com/questions/812686/can-a-window-be-always-on-top-of-just-one-other-window ;
				// this answer: https://stackoverflow.com/a/821061/4325555 really works; thanks Matthew Xavier ;
				::DefWindowProc(this->Main().Target(), _u_code, _w_param, _l_param);

				p_wnd_pos->hwnd = this->Bottom().Target();
				p_wnd_pos->hwndInsertAfter = this->Main().Target();
				p_wnd_pos->flags &= ~SWP_NOZORDER;

				n_result = __s_ok; // this message is handled;
			}
			// https://stackoverflow.com/questions/1825868/how-to-prevent-window-resizing-temporarily ; Tech_dog's answer is there;
		} break;
	case WM_SYSCOMMAND : { // https://learn.microsoft.com/en-us/windows/win32/menurc/wm-syscommand ;
		const bool b_max = (SC_MAXIMIZE == _w_param); b_max;
		const bool b_min = (SC_MINIMIZE == _w_param); b_min;

		if (b_max)
			n_result = __s_ok; // this message is handled;
		else
			n_result = __s_false;

		} break;
	}
	return n_result;
}

bool    CLayout::Is_valid (void) const { return this->Bottom().Is_valid() && this->Main().Is_valid() && this->Top().Is_valid(); }

const
CPane&  CLayout::Main (void) const { return this->m_target; }
CPane&  CLayout::Main (void)       { return this->m_target; }
const
CPane&  CLayout::Top (void) const { return this->m_top; }
CPane&  CLayout::Top (void)       { return this->m_top; }

err_code CLayout::Update (t_rect* const _p_rect) {

	err_code n_result = __s_ok; // the message 'wm_moving' is not handled;

	t_rect rc_wnd_pos = {0};

	if (0 == _p_rect) {
		::GetWindowRect(this->Main().Target(), &rc_wnd_pos);
	}
	else
		::CopyRect(&rc_wnd_pos, _p_rect);

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getsystemmetrics ;
	// removing WS_THICKFRAME style from the console window is useful, but it has the side effect: the console window size increases;
	const int n_border = ::GetSystemMetrics(SM_CXBORDER);
	if (0 == n_border) {
		// looks like the system error occurs, but the last error does not contain any useful info;
	}
	const int n_gap = n_border * 8; // empirical way is used;

	// it is assumed that the height and width of the input rectangle remain unchanged because the size of the main window is fixed;
	const t_rect rect_con = {
		rc_wnd_pos.left + n_gap, rc_wnd_pos.bottom - this->Bottom().Size().Height(), rc_wnd_pos.right - n_gap, rc_wnd_pos.bottom - n_gap
	};
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-movewindow ;
	if (0 == ::MoveWindow(this->Bottom().Target(), rect_con.left, rect_con.top, __W(rect_con), __H(rect_con), true)) {
		const err_code n_code = __LastErrToHresult(); n_code; // for debug purposes only, this time;
	}
	n_result = __s_false; // this message is handled;

	return n_result;
}

void  CLayout::IWaitable_OnComplete (void) {
	this->Update();
}