/*
	Created by Tech_dog (ebontrop@gmail.com) 0n 18-Aug-2025 at 22:33:32.728, UTC+4, Batumi, Monday;
	This is OpenGL fake content creation tutorial module interface implementation file;
*/
#include "open_gl_tutor.0.module.h"
#include "open_gl_tutor.0.fake.h"

using namespace ebo::pack::draw::open_gl::fake;

CFakeModule _Module;

err_code CFakeModule::PreMessageLoop (int nShowCmd) {
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
	{
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox ;
		CWnd wnd;
		if (wnd.Is_valid()) {
#if defined(_DEBUG)
			::MessageBox(0, _T("The content is created successfullly;"), _T("OpenGL Tutors"), MB_OK|MB_ICONINFORMATION);
#endif
		}
		else {
#if defined(_DEBUG)
#endif
		}
	}

	MSG msg = {0, WM_QUIT, 0, 0, 0, {0, 0}};

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