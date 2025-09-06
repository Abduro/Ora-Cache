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
	context::CWnd w_target;

	do {

		// (0) creating the main window/application at the beginning of this 'journey';
		if (__failed(app_wnd.Create(pc_sz_cls_name, _T("OpenGL__tut_#1_ctx"), false))) {
			__trace_err_3(_T("%s\n"), (_pc_sz) app_wnd.Error().Print(TError::e_req));
			app_wnd.Error().Show(); break;
		}

		t_rect rect_wnd = {0};
		::GetWindowRect(app_wnd.Handle(), &rect_wnd);

		app_wnd.Layout().Size().Ref() = t_size{__W(rect_wnd), __H(rect_wnd)};
		app_wnd.Layout().Size().Is_locked(true);

		app_wnd.Frame().Icons().Set(IDR_TUTOR_0_ICO);
		app_wnd.Set_visible(true);

		// for this version of the implementation it is suppossed to be the same rectangle that was used for the client area of the main window;
		t_rect rc_client  = {0, 0, CRatios().Get().at(0).cx, CRatios().Get().at(0).cy};

		// https://learn.microsoft.com/en-us/windows/win32/gdi/rectangle-functions ;
		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-inflaterect ;
		::InflateRect(&rc_client, -0x4, -0x4); // no check for error this time;

		if (__failed(w_target.Create(app_wnd.Handle(), rc_client, true))) {
			__trace_err_3(_T("%s\n"), (_pc_sz) w_target.Error().Print(TError::e_req));
			w_target.Error().Show(); break;
		}

		CContext ctx;
		// (1)(2) creates fake window and get OpenGL draw renderer context of the base version (OpenGL v1.1);
		// the error *always* occurs on RDP of MS Windows;
		if (__failed(ctx.Create(w_target.Handle()))) {
			__trace_err_3(_T("%s\n"), (_pc_sz) ctx.Error()().Print(TError::e_req));
			ctx.Error()().Show(); break;
		}
#if (0)
		::MessageBox(
			HWND_DESKTOP, TString().Format(_T("Loaded functions:\n%s"), (_pc_sz)ctx.Cache().Print()), _T("OpenGL Tutors::1"), MB_OK|MB_ICONASTERISK
		);

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
#endif
		b_error = false;

	} while (true == false);

	if (b_error != false)
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