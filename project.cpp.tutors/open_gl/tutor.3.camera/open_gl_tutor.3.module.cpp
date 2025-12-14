/*
	Created by Tech_dog (ebontrop@gmail.com) 0n 26-Aug-2025 at 02:41:05.044, UTC+4, Batumi, Tuesday;
	This is OpenGL shader creation tutorial module interface implementation file;
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack OpenDL tutorial project at 01:40:28.285, UTC+4, Batumi, Thursday;
*/
#pragma region __includes
#include "open_gl_tutor.3.module.h"                                                   
#include "open_gl_tutor.3.res.h"

#include "shared.dbg.h"
#include "shared.theme.h"
#include "gl_renderer.h"
#include "gl_version.h"

#include "console.h"
#include "console.font.h"

#include "win.gui.wnd.h"

#include "shapes\gl_shape.2d.h"
#pragma endregion
using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::camera;
using namespace shared::console;
using namespace shared::gui;

CCameraModule _Module;

err_code CCameraModule::PreMessageLoop (int nShowCmd) {
	nShowCmd;
	err_code n_result = __s_ok;

	n_result = TModule::PreMessageLoop(nShowCmd);
	if (__failed(n_result))
		return n_result;
	else
		return n_result = __s_ok; // forces to continue working with pumping windows' messages;
}

/////////////////////////////////////////////////////////////////////////////
/*
	api-ms-win-core-synch-l1-2-0 cannot be loaded >> access violation error may occur in case when this solution must be re-built;
*/
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
	::DefWindowProc(nullptr, 0, 0, 0L);

	MSG msg = {0};

	static _pc_sz pc_sz_cls_name = _T("__open_gl_tutor_3_camera");

	bool b_error = true;

	CAppWnd& app_wnd = ::Get_app_wnd();
	camera::CWnd cam_wnd; // the draw context window;

	using
	CTriangle = ex_ui::draw::open_gl::shapes::CTriangle;
	CTriangle triangle;

	TRenderer& renderer = ::Get_renderer();

	do {
		__trace::Use_con(true); // the console window is not created yet; VS debug output is used anyway;
#pragma region __step_0
		// (0) creating the main window/application at the beginning of this 'journey';
		if (__failed(app_wnd.Create(pc_sz_cls_name, _T("OpenGL__tut_#3_camera"), true))) {
			__trace_err_3(_T("%s\n"), (_pc_sz) app_wnd.Error().Print(TError::e_req));
			app_wnd.Error().Show(); break;
		}

		app_wnd.Frame().Icons().Set(IDR_TUTOR_0_ICO);

		/*const */shared::gui::CLayout& layout = app_wnd.Layout();
#pragma endregion
#pragma region __step_1
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

		shared::console::CFormat::CBkgnd con_bkg;
		con_bkg.Color(::Get_theme().Bkgnd_rgb());
		// *important*: all sizes of the target windows is fixed, because the main window size is fixed itself;
		layout.Update();
		shared::console::CLayout().Output().HScroll().Set(true);

		__trace_warn_3(_T("%s\n"), (_pc_sz) CVersion().Print_2());
#pragma endregion
#pragma region __step_2
		// (2) creates the context target window; the required GDI and draw contexts are also created;
		if (__failed(cam_wnd.Create(app_wnd.Handle(), layout.Top().Rect(), true))) {
			__trace_err_3(_T("%s\n"), (_pc_sz) cam_wnd.Error().Print(TError::e_req)); // debug output console window is already created;
		}
		else
			layout.Top().Target(cam_wnd);
		// (2.a) tries to set shaders source code from this executable resources;
		//  *important*: no scene preparation is called before setting the shape;
		if (__failed(cam_wnd.PostCreate())) {
			__trace_err_3(_T("%s\n"), (_pc_sz) cam_wnd.Error().Print(TError::e_req));
			break;
		}
#pragma endregion
#pragma region __step_3
		// (3) creates a rectangle shape and initializes it with colors and coordinates of its vertices;
		triangle.A().Attrs().Clr().Set(1.0f, 0.0f, 0.0f, 1.0f);
		triangle.B().Attrs().Clr().Set(0.0f, 1.0f, 0.0f, 1.0f);
		triangle.C().Attrs().Clr().Set(0.0f, 0.0f, 1.0f, 1.0f);

		// for this tutorial direct assigning coordinates to the rectangle vertices is acceptable;
		triangle.A().Attrs().Pos().Set(+0.0f, +0.5f);
		triangle.B().Attrs().Pos().Set(-0.5f, -0.5f);
		triangle.C().Attrs().Pos().Set(+0.5f, -0.5f);

		if (__failed(triangle.Update())) { // if an error occurs, the method prints it itself;
			break;
		}
#pragma endregion
#pragma region __step_4
		// (4) sets vertex attributes array to vertex array object;
		using CBuffer = vertex::CBuffer;

		if (__failed(renderer.Scene().Prepare())) break;
#if (0)
		CBuffer& buffer = renderer.Scene().ArrObjs().Get(e_arr_ndx::e_tria).VertArray().Buffer();

		// (4.a) sets buffer cfg values;
		buffer.Cfg().Count(triangle.Vertices().Count());
		buffer.Cfg().Primitive(triangle.Primitive());
		buffer.Cfg().StartAt(0);

		if (__failed(buffer.SetData(triangle.Vertices().Data_ref()))) {
			break;
		}
#endif
#pragma endregion
#pragma region __step_5
		// (5) sets renderer cfg values;
		renderer.Cfg().Count(triangle.Vertices().Count());
		renderer.Cfg().Primitive(triangle.Primitive());
		renderer.Cfg().StartAt(0);
#pragma endregion
	} while (true == false);

	if (b_error != false) // goes to message loop and waits the app window will be closed;
		msg.message = WM_QUIT;

	while( WM_QUIT != msg.message ) {
		if (::PeekMessage( &msg, NULL, 0, 0, PM_REMOVE )) {
			::TranslateMessage( &msg );
			::DispatchMessage ( &msg );
		}
		if (false == b_error /*&& cam_wnd.Renderer().Is_allowed()*/) {
			if (__failed(renderer.Draw()))   // perhaps this function must check for changing the draw data before draw it;
				b_error = true;
			else
				renderer.Is_allowed(false);  // the window is not sized and there is no action on changing draw mode;
			::Sleep(100);
		}
	}

	::Get_app_wnd().Destroy();
	__trace::OnTime();
	return n_result;
}