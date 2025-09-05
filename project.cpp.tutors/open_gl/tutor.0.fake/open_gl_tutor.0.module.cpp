/*
	Created by Tech_dog (ebontrop@gmail.com) 0n 18-Aug-2025 at 22:33:32.728, UTC+4, Batumi, Monday;
	This is OpenGL fake context creation tutorial module interface implementation file;
*/
#include "open_gl_tutor.0.module.h"

using namespace ex_ui::draw::open_gl::fake;

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

	do {
	// (1) the message-only window must be created first aka fake window, it is necessary for creating OpenGL draw renderer compatible with regular GDI context;
		TFakeWnd fk_wnd; // this class creates the fake window in its constructor;
		if (fk_wnd.Is_valid() == false) {
			// the error of the creating the window is already traced; just break the test case;
			fk_wnd.Error().Show();
			break;
		}
	// (2) creating the drawing renderer context;
		context::CDevice dev_ctx;
		if (__failed(dev_ctx.Create(fk_wnd.m_hWnd))) {
			dev_ctx.Error()().Show();
			break;
		}
	// (3) getting version information of openGL that is default in MS Windows; *important*: the fake/false context is still be current; (fake window is valid);
		CVersion ver;
		if (ver.Error()) {
			ver.Error().Show();
			break;
		}

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox ;
		CString cs_ver = ver.GetAtt(CVersion::e_atts::e_version).Print(e_print::e_req, false);
		::MessageBox(
			0, (_pc_sz) cs_ver, TString().Format(_T("%s::%s()"), (_pc_sz) __SP_NAME__, (_pc_sz) __METHOD__), MB_OK|MB_ICONINFORMATION
		);
		break;
	} while (true == false);

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