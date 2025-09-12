/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Sep-2025 at 12:51:48.000, UTC+4, Batumi, Wednesday;
	This is OpenGL context creation tutorial module interface implementation file;
*/
#include "open_gl_tutor.1.module.h"
#include "open_gl_tutor.1.res.h"
#include "open_gl_tutor.1.wnd.h"

#include "shared.dbg.h"

#ifndef __H
#define __H(_rect) (_rect.bottom - _rect.top)
#endif
#ifndef __W
#define __W(_rect) (_rect.right - _rect.left)
#endif

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::context;

CContextModule _Module;

err_code CContextModule::PreMessageLoop (int nShowCmd) {
		nShowCmd;
		err_code n_result = __s_ok;

		n_result = TModule::PreMessageLoop(nShowCmd);
		if (__failed(n_result))
			return n_result;
		else
			return n_result = __s_ok; // forces to continue working with pumping windows' messages;
}

/////////////////////////////////////////////////////////////////////////////

INT __stdcall _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpstrCmdLine, INT nCmdShow) {
	hInstance; hPrevInstance; lpstrCmdLine; nCmdShow;

	/*
		Tech_dog commented on 09-Feb-2010 at 12:47:50pm, UTC+3, Rostov-on-Don, Monday:
		-----------------------------------------------------------------------------
		For linking ATL DLL statically an assignment LIBID manually is required,
		otherwise annoying fkn message "Did you forget to pass the LIBID to CComModule::Init?" is thrown;
	*/
	_Module.m_libid  = LIBID_ATLLib;
	int32_t n_result = __s_ok;

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used;
	::DefWindowProc(NULL, 0, 0, 0L);

	MSG msg = {0};

	static _pc_sz pc_sz_cls_name = _T("__open_gl_tutor_1_ctx");

	bool b_error = true; // this is for cases when an error occurs and after displaying the error message the message loop is interrupted;

	CAppWnd app_wnd;
	context::CWnd wnd_ctx; // the draw context window;

	do {

		// (0) creating the main window/application at the beginning of this 'journey';
		if (__failed(app_wnd.Create(pc_sz_cls_name, _T("OpenGL__tut_#1_ctx"), false))) {
			__trace_err_3(_T("%s\n"), (_pc_sz) app_wnd.Error().Print(TError::e_req));
			app_wnd.Error().Show(); break;
		}
		else {
			const bool b_is_top = app_wnd.Is_top();
			if (true == b_is_top) {
			}
		}

		t_rect rect_wnd = {0};
		::GetWindowRect(app_wnd.Handle(), &rect_wnd);

		shared::gui::CLayout& layout = app_wnd.Layout();

		// (0.a) sets up the app/main window layer first;
		layout.Main().Target(app_wnd);
		layout.Main().Size().Height().Set(__H(rect_wnd), docking::CValue::e_ctrl::e_fixed);
		layout.Main().Size().Width().Set(__W(rect_wnd), docking::CValue::e_ctrl::e_fixed);  // if both height and width is fixed, the size is locked;

		app_wnd.Frame().Icons().Set(IDR_TUTOR_0_ICO);
		app_wnd.Set_visible(true);

		// for this version of the implementation it is supposed to be the same rectangle that was used for the client area of the main window;
		t_rect rc_client  = {0, 0, CRatios().Get().at(0).cx, CRatios().Get().at(0).cy};
#if (1)
		const long n_part = __H(rc_client) / 3;
		t_rect rc_ctx = { rc_client.left, rc_client.top, rc_client.right, rc_client.bottom - n_part };
		t_rect rc_con = { rc_client.left, rc_ctx.bottom, rc_client.right, rc_client.bottom };

		::MapWindowPoints(app_wnd, 0, (LPPOINT)&rc_con, 2); // *important*: the console window uses the screen coordinates only;
#else	// not used anymore;
		// https://learn.microsoft.com/en-us/windows/win32/gdi/rectangle-functions ;
		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-inflaterect ;
		::InflateRect(&rc_client, -0x4, -0x4); // no check for error this time;
#endif
		// (0) creates the console output window;
		CConsole out_;
		if (__failed(out_.Open(app_wnd, rc_con, false))) { // the last arg of visibility mode is not used yet;
			__trace_err_3(_T("%s\n"), (_pc_sz) out_.Error().Print(TError::e_req));
			out_.Error().Show();
			break;
		}

		// *important*: all sizes of the target windows is fixed, because the main window size is fixed itself;
		layout.Bottom().Target(out_);
		layout.Bottom().Size().Height().Set(__H(rc_con), docking::CValue::e_ctrl::e_fixed);
		layout.Bottom().Size().Width().Set(__W(rc_con), docking::CValue::e_ctrl::e_fixed);

		layout.Update();

		// (1) creates the context target window;
		if (__failed(wnd_ctx.Create(app_wnd.Handle(), rc_ctx, true))) {
			__trace_err_3(_T("%s\n"), (_pc_sz) wnd_ctx.Error().Print(TError::e_req));
			wnd_ctx.Error().Show(); break;
		}
		
		layout.Top().Target(wnd_ctx);
		layout.Top().Size().Height().Set(__H(rc_ctx), docking::CValue::e_ctrl::e_fixed);
		layout.Top().Size().Width().Set(__W(rc_ctx), docking::CValue::e_ctrl::e_fixed);

		CContext ctx;
		// (1)(2) creates fake window and get OpenGL draw renderer context of the base version (OpenGL v1.1);
		// the error *always* occurs on RDP of MS Windows;
		if (__failed(ctx.Create(wnd_ctx.Handle(), 3, 3))) {
			__trace_err_3(_T("%s\n"), (_pc_sz) ctx.Error()().Print(TError::e_req));
			ctx.Error()().Show(); break;
		}
#if (0)
		else
		::MessageBox(
			HWND_DESKTOP, TString().Format(_T("Ctx is created: %s"), _T("successfully;")), _T("OpenGL Tutors::1"), MB_OK|MB_ICONASTERISK
		);
#endif
		// (3) getting *real* version information of openGL that is installed in MS Windows; *important*: OpenGL draw renderer context must be current;
		CVersion ver;
		if (ver.Error()) {
			ver.Error().Show();
			break;
		}

		CString cs_ver = ver.GetAtt(CVersion::e_atts::e_version).Print(e_print::e_req, false);
		::MessageBox(
			0, (_pc_sz) cs_ver, TString().Format(_T("%s::%s()"), (_pc_sz) __SP_NAME__, (_pc_sz) __METHOD__), MB_OK|MB_ICONINFORMATION
		);

		b_error = false;

	} while (true == false);

	if (b_error != false) // goes to message loop and waits the app window will be closed;
		msg.message = WM_QUIT;

	while( WM_QUIT != msg.message ) {
		if (::PeekMessage( &msg, NULL, 0, 0, PM_REMOVE )) {
			::TranslateMessage( &msg );
			::DispatchMessage ( &msg );
		}
		else {
			::Sleep(10);
		}
	}

	return n_result;
}