/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Aug-2026 at 08:34:19.031, UTC+4, Batumi, Thursday;
	This is virtual camera test cases' desktop GUI main window interface implementation file;
*/
#include "test.gui.window.h"

using namespace ::test::app;

namespace test { namespace app { namespace _impl {

	class CIcon_Att {
	public:
		 CIcon_Att (void) {} CIcon_Att (const CIcon_Att&) = delete; CIcon_Att (CIcon_Att&&) = delete;
		~CIcon_Att (void) {}
	public:
		SIZE  Size (const bool bTreatAsLargeIcon) const
		{
			const SIZE szIcon = {
				::GetSystemMetrics(bTreatAsLargeIcon ? SM_CXICON : SM_CXSMICON), 
				::GetSystemMetrics(bTreatAsLargeIcon ? SM_CYICON : SM_CYSMICON)
			};
			return szIcon;
		}

	private:
		CIcon_Att& operator = (const CIcon_Att&) = delete;
		CIcon_Att& operator = (CIcon_Att&&) = delete;
	};

	class CIcon_Loader { // no error handling for this version yet;
	public:
		 CIcon_Loader (void) {} CIcon_Loader (const CIcon_Loader&) = delete; CIcon_Loader (CIcon_Loader&&) = delete;
		~CIcon_Loader (void) {}

		HICON   Get (const uint16_t nIconResId, const bool bTreatAsLargeIcon) const
		{	// https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulehandlew ;
			// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-loadimagew ;
			const SIZE szIcon = CIcon_Att().Size(bTreatAsLargeIcon);
			const HINSTANCE hInstance = static_cast<HINSTANCE>(::GetModuleHandle(nullptr));
			const HICON hIcon = (HICON)::LoadImage(
				hInstance, MAKEINTRESOURCE(nIconResId), IMAGE_ICON, szIcon.cx, szIcon.cy, LR_DEFAULTCOLOR
			);
			return hIcon;
		}

	private:
		CIcon_Loader& operator = (const CIcon_Loader&) = delete;
		CIcon_Loader& operator = (CIcon_Loader&&) = delete;
	};

}}} using namespace ::test::app::_impl;

#pragma region cls::CAppWnd{}

CAppWnd:: CAppWnd (void) {}
CAppWnd::~CAppWnd (void) { this->Destroy(); }

err_code CAppWnd::Create (void) {
	err_code n_result = __s_ok;
	// https://learn.microsoft.com/en-us/windows/win32/winmsg/extended-window-styles ;
	// https://learn.microsoft.com/en-us/windows/win32/winmsg/window-styles ;
	static const dword_t dw_ext_style = WS_EX_OVERLAPPEDWINDOW | WS_EX_COMPOSITED;
	static const dword_t dw_std_style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	const // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexw ;
	HWND h_wnd = TWindow::Create(HWND_DESKTOP, 0, 0, dw_std_style, dw_ext_style);
	if ( h_wnd == 0 )
		return (n_result = __LastErrToHresult());

	return n_result;
}

err_code CAppWnd::Destroy (void) {
	err_code n_result = __s_ok;
	if (this->Is_valid()) {
		if (0 == TWindow::DestroyWindow()) // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-destroywindow ;
			return (n_result = __LastErrToHresult());
	}
	return n_result;
}

const
CFrame&  CAppWnd::Frame (void) const { return this->m_frame; }
CFrame&  CAppWnd::Frame (void)       { return this->m_frame; }

bool CAppWnd::Is_valid (void) const { return !!TWindow::IsWindow(); } 

l_result CAppWnd::OnClose (const uint32_t, const l_param, const w_param, bool_t& _b_handled) {
	_b_handled = true;
	this->Destroy(); // no prompt for this time, just destroying this window;
	return __s_ok;
}

l_result CAppWnd::OnCreate (const uint32_t, const l_param _l_param, const w_param _w_param, bool_t& _b_handled) {
	_l_param; _w_param; _b_handled = true;
	l_result n_result = __s_ok; // this message is handled, otherwise, it should equals to -1;
	const CREATESTRUCT* p_struct = reinterpret_cast<CREATESTRUCT*>(_w_param);
	if (nullptr != p_struct) {}

	return n_result;
}

l_result CAppWnd::OnDestroy (const uint32_t, const l_param _l_param, const w_param _w_param, bool_t& _b_handled) {
	_l_param; _w_param; _b_handled = false;

	l_result n_result = __s_false; // this message is not handled, otherwise, it should be __s_ok;
	::PostQuitMessage(0); // it is required to exit the message received loop;
	return n_result;
}

#pragma endregion
#pragma region cls::CFrame{}

const
CFrame::CIcons& CFrame::Icons (void) const { return this->m_icons; }
CFrame::CIcons& CFrame::Icons (void)       { return this->m_icons; }

#pragma endregion
#pragma region cls::CFrame::CIcons{}

CFrame::CIcons::CIcons (void) : m_res_id(0), m_wnd(0) {}

err_code CFrame::CIcons::Set (const uint16_t _u_res_id) {
	return CFrame::CIcons::Set(_u_res_id, this->m_wnd);
}
err_code  CFrame::CIcons::Set (const uint16_t _u_res_id, const HWND _h_wnd) {
	_u_res_id; _h_wnd;
	if (0 == _h_wnd || false == !!::IsWindow(_h_wnd))
		return __e_hwnd;

	if (false == !!_u_res_id)
		return __e_inv_arg;

	/* https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-seticon ;
	   there is no error handling: sending this message does not set the last error in case of failure;
	   the following reqs must be met:
	   the icon being referenced must have predefined icon size: 16x16 px for small icon and 32x32 px for the large one;
	*/
	::SendMessage(_h_wnd, WM_SETICON, 0, (l_param) CIcon_Loader().Get(_u_res_id, 0));
	::SendMessage(_h_wnd, WM_SETICON, 1, (l_param) CIcon_Loader().Get(_u_res_id, 1));

	return __s_ok;
}

CFrame::CIcons& CFrame::CIcons::operator <<(const HWND _h_wnd) { this->m_wnd = _h_wnd; return *this; }
CFrame::CIcons& CFrame::CIcons::operator <<(const uint16_t _res_id) { this->m_res_id = _res_id; this->Set(_res_id); return *this; }

#pragma endregion