/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Sep-2025 at 12:51:48.000, UTC+4, Batumi, Wednesday;
	This is OpenGL context creation tutorial module interface implementation file;
*/
#include "open_gl_tutor.1.module.h"
#include "open_gl_tutor.1.wnd.h"

#include "shared.dbg.h"

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
#if (0)
	::MessageBox(HWND_DESKTOP, _T("Context module;"), _T("OpenGL Tutors::1"), MB_OK|MB_ICONASTERISK);
#else
	do {
		CContext ctx;

		if (__failed(ctx.Create(0))) {
			__trace_err_3(_T("%s\n"), (_pc_sz) ctx.Error()().Print(TError::e_req));
			ctx.Error()().Show(); break;
		}
	} while (true == false);
#endif
	msg.message = WM_QUIT;

	while( WM_QUIT != msg.message ) {
		if (::PeekMessage( &msg, NULL, 0, 0, PM_REMOVE )) {
			::TranslateMessage( &msg );
			::DispatchMessage ( &msg );
		}
		else {
		}
	}

	return n_result;
}