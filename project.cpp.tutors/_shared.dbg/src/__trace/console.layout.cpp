/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Mar-2026 at 16:08:25.583, UTC+4, Batumi, Saturday;
	This is system console window and content layout wrapper interface implementation file;
*/
#include "console.layout.h"
#include "shared.preproc.h"

using namespace shared::console;
using namespace shared::console::layout;

#ifndef __H
#define __H(_rect) (_rect.bottom - _rect.top)
#endif

#ifndef __W
#define __W(_rect) (_rect.right - _rect.left)
#endif

#pragma region cls::CHScroll{}

CHScroll:: CHScroll (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("#__e_not_inited"); }

TError&  CHScroll::Error (void) const { return this->m_error; }

bool CHScroll::Get (void) const {

	CScreenBuffer buff;
	if (__failed( buff.Set()))
		return false;

	LONG_PTR lp_style = ::GetWindowLongPtr(::GetConsoleWindow(), GWL_STYLE);
	return   lp_style & WS_HSCROLL;
}

err_code CHScroll::Set (const bool _b_set) {
	_b_set;
	this->m_error <<__METHOD__<<__s_ok;

	const bool b_has = this->Get();

	if (_b_set == true && b_has == true) return this->Error();
	if (_b_set == false && b_has == false) return this->Error();

	CScreenBuffer buff_out;

	if (__failed(buff_out.Get()))
		return this->m_error = buff_out.Error();

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getclientrect ;
	t_rect rc_client = {0};
	if (0 == ::GetClientRect(::GetConsoleWindow(), &rc_client))
		return this->m_error.Last();

	const int n_req = __W(rc_client) / buff_out().dwSize.X;

	if (_b_set) {
		buff_out().dwSize.X = static_cast<int16_t>(buff_out().dwSize.X * 2);
	}
	else {
		buff_out().dwSize.X = static_cast<int16_t>(buff_out().dwSize.X / 2);
	}

	if (__failed(buff_out.Set()))
		this->m_error = buff_out.Error();

	return this->Error();
}

#pragma endregion
#pragma region cls::CLayout{}

CLayout::CLayout (void) {  this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("#__e_not_inited"); }

err_code CLayout::As_child (const HWND _h_parent, const t_rect& _rect_wnd_pos, const bool _b_visible) {
	_h_parent; _rect_wnd_pos; _b_visible;
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == _h_parent || false == !!::IsWindow(_h_parent))
		return this->m_error <<__e_inv_arg = _T("Handle of the parent window is not valid");

	if (::IsRectEmpty(&_rect_wnd_pos))
		return this->m_error << __e_rect = _T("The input rectangle is empty");

	const HWND h_con_wnd = ::GetConsoleWindow(); // https://learn.microsoft.com/en-us/windows/console/getconsolewindow ;
	if (nullptr == h_con_wnd)
		return this->m_error <<__e_hwnd = _T("There is no console attached to this process");
#if (0)
	// (1) hides the console window first;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-showwindow ; this function does *not* report an error!
	::ShowWindow(h_con_wnd, SW_HIDE);
#else
	static const uint32_t u_flags = SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowpos ;
	if (false == !!::SetWindowPos(h_con_wnd, 0, 0, 0, 0, 0,  u_flags | SWP_HIDEWINDOW))
		return this->m_error.Last();
#endif
	// (1) customizes the console for being a child window of the parent one, i.e. the main/app window;
	// (1.a) removes caption and borders of the window frame;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowlongptrw ;
	LONG_PTR lp_style = ::GetWindowLongPtr(h_con_wnd, GWL_STYLE);

	lp_style &= ~(WS_CAPTION|WS_THICKFRAME|WS_SYSMENU|WS_MINIMIZEBOX|WS_MAXIMIZEBOX);
//	lp_style |=   WS_CHILD; // it is not necessary because the console window can never be as a child window; (conhost.exe);
	lp_style |=   WS_HSCROLL;

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowlongptrw ;
	if (!::SetWindowLongPtr(h_con_wnd, GWL_STYLE, lp_style))
		return this->m_error.Last();

	// (1.b) applies new style to the console window; the flag 'SWP_FRAMECHANGED' is the most important;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowpos ;
	::SetWindowPos(
		h_con_wnd, 0, _rect_wnd_pos.left, _rect_wnd_pos.top, __W(_rect_wnd_pos), __H(_rect_wnd_pos), SWP_FRAMECHANGED|SWP_NOACTIVATE|SWP_NOZORDER
	);

	// (2) shows the console window at final step of the creating procedure;
	::ShowWindow(h_con_wnd, SW_SHOW);

	return this->Error();
}

TError&  CLayout::Error (void) const { return this->m_error; }

#pragma endregion