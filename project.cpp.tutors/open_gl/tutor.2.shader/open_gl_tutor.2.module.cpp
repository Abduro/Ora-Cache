/*
	Created by Tech_dog (ebontrop@gmail.com) 0n 26-Aug-2025 at 02:41:05.044, UTC+4, Batumi, Tuesday;
	This is OpenGL shader creation tutorial module interface implementation file;
*/
#include "open_gl_tutor.2.module.h"
#include "open_gl_tutor.2.res.h"

#include "shared.dbg.h"
#include "gl_version.h"

#include "console.h"
#include "console.font.h"

#include "win.gui.wnd.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::shader;
using namespace shared::console;
using namespace shared::gui;

CShaderModule _Module;

err_code CShaderModule::PreMessageLoop (int nShowCmd) {
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

	static _pc_sz pc_sz_cls_name = _T("__open_gl_tutor_2_shader");

	bool b_error = true;

	CAppWnd& app_wnd = ::Get_app_wnd();
	shader::CWnd wnd_shader; // the draw context window;

	do {
		__trace::Use_con(true); // the console window is not created yet; VS debug output is used anyway;

		// (0) creating the main window/application at the beginning of this 'journey';
		if (__failed(app_wnd.Create(pc_sz_cls_name, _T("OpenGL__tut_#2_shader"), true))) {
			__trace_err_3(_T("%s\n"), (_pc_sz) app_wnd.Error().Print(TError::e_req));
			app_wnd.Error().Show(); break;
		}

		app_wnd.Frame().Icons().Set(IDR_TUTOR_0_ICO);

		/*const */shared::gui::CLayout& layout = app_wnd.Layout();
		
		// (1) creates the console output window;
		if (__failed(_out.Open(app_wnd, layout.Bottom().Rect(), false))) { // the last arg of visibility mode is not used yet;
			__trace_err_3(_T("%s\n"), (_pc_sz) _out.Error().Print(TError::e_req));
			_out.Error().Show();
			break;
		}
		__trace::Use_con(true);
		layout.Bottom().Target(_out.Handle());
		layout.Update();
		b_error = false;

		shared::console::CFont font_; font_.Set(_T("consolas"), 15);

		// *important*: all sizes of the target windows is fixed, because the main window size is fixed itself;
		layout.Update();
		shared::console::CLayout().Output().HScroll().Set(true);

		__trace_warn_3(_T("%s\n"), (_pc_sz) CVersion().Print_2());

		// (2) creates the context target window;
		if (__failed(wnd_shader.Create(app_wnd.Handle(), layout.Top().Rect(), true))) {
			__trace_err_3(_T("%s\n"), (_pc_sz) wnd_shader.Error().Print(TError::e_req)); // debug output console window is already created;
		}
		else
			layout.Top().Target(wnd_shader);

		if (__failed(wnd_shader.PostCreate())) {
			__trace_err_3(_T("%s\n"), (_pc_sz) wnd_shader.Error().Print(TError::e_req));
			break;
		}

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

	::Get_app_wnd().Destroy();

	return n_result;
}