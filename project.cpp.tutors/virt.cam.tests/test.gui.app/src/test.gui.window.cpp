/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Aug-2026 at 08:34:19.031, UTC+4, Batumi, Thursday;
	This is virtual camera test cases' desktop GUI main window interface implementation file;
*/
#include "test.gui.window.h"

using namespace ::test::app;

#pragma region cls::CMainWnd{}

CMainWnd:: CMainWnd (void) {}
CMainWnd::~CMainWnd (void) {}

err_code CMainWnd::Create (void) {
	err_code n_result = __s_ok;
	const
	HWND h_wnd = TWindow::Create(HWND_DESKTOP); // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexw ;
	if ( h_wnd == 0 )
		return (n_result = __LastErrToHresult());

	return n_result;
}

err_code CMainWnd::Destroy (void) {
	err_code n_result = __s_ok;
	return n_result;
}

l_result CMainWnd::OnCreate (const uint32_t, const l_param _l_param, const w_param _w_param, bool_t& _b_handled) {
	_l_param; _w_param; _b_handled = true;
	l_result n_result = __s_ok; // this message is handled, otherwise, it should equals to -1;
	const CREATESTRUCT* p_struct = reinterpret_cast<CREATESTRUCT*>(_w_param);
	if (nullptr != p_struct) {}

	return n_result;
}

l_result CMainWnd::OnDestroy (const uint32_t, const l_param _l_param, const w_param _w_param, bool_t& _b_handled) {
	_l_param; _w_param; _b_handled = false;

	l_result n_result = __s_false; // this message is not handled, otherwise, it should be __s_ok;
	return n_result;
}

#pragma endregion