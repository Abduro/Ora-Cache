/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Jan-2016 at 2:00:32am, GMT+7, Phuket, Rawai, Friday;
	This is File Guardian (thefileguardian.com) app entry point implementation file.
	-----------------------------------------------------------------------------
	Adopted to vs15 on 1-Jul-2018 at 6:11:43p, UTC+7, Phuket, Rawai, Sunday;
	Adopted to Ebo Pack draw renderer test app 30-Mar-2025 at 16:28:15.839, UTC+4, Batumi, Sunday;
*/
#include "win.gui_module.h"

using namespace shared::sys_core;
using namespace ebo::boo::gui;

CWinGuiModule _Module;

/////////////////////////////////////////////////////////////////////////////

err_code CWinGuiModule::PreMessageLoop (int nShowCmd) {
		nShowCmd;
		err_code n_result = __s_ok;

		n_result = TBase::PreMessageLoop(nShowCmd);
		if (__failed(n_result))
			return n_result;
		else
			return n_result = __s_ok; // forces to continue working with pumping windows' messages;
} 

/////////////////////////////////////////////////////////////////////////////

INT __stdcall _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpstrCmdLine, INT nCmdShow)
{
	hInstance; hPrevInstance; lpstrCmdLine; nCmdShow;

	using CError = shared::sys_core::CError;

	CError error;
	error >> __CLASS__ << __METHOD__ << __e_not_inited;

	/*
		Tech_dog commented on 09-Feb-2010 at 12:47:50pm, UTC+3, Rostov-on-Don, Monday:
		-----------------------------------------------------------------------------
		For linking ATL DLL statically an assignment LIBID manually is required,
		otherwise annoying fkn message "Did you forget to pass the LIBID to CComModule::Init?" is thrown;
	*/
	_Module.m_libid  = LIBID_ATLLib;
	int32_t n_result = __s_ok;
	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	ex_ui::theme::Get_current().Load();  // no returned error code is concerned here yet;

	ebo::boo::gui::CFrame frame;

	n_result = frame.Create();
	if (__succeeded(n_result)) {
#if (0)
		_Module.WinMain(nCmdShow);
#else
		MSG msg = {0};
		while( WM_QUIT != msg.message ) { // PeekMessage is used for getting an ability of drawing render surface when no message is in the queue;
			if (::PeekMessage( &msg, NULL, 0, 0, PM_REMOVE )) {
				::TranslateMessage( &msg );
				::DispatchMessage ( &msg );
			}
			else {
			#if (0)
				const bool b_is_dark = TTheme::IsDark();
				if (b_is_dark) {}
			#else
				static uint32_t n_counter = 0;
				if (0 == n_counter) {
					using CUI_Parts = ebo::sha::theme::direct_x::CUI_Parts;
					_render().Target().OnDraw(CUI_Parts().Bkg()); // ToDo: eats a lot of CPU time, and needs to be reviewed;
					n_counter += 1;
				}
				else {
					n_counter += 1;
					::Sleep(10);         // works unexpectedly great!;
					if (n_counter == 60)
						n_counter = 0;
				}
				// if no size of the direct_x surface is changed, it should not be called from here;
				// maybe an animation can be produced, but at least on separate time event;
			#endif
			}
		}
#endif
		frame.Destroy();       // a handling of possible error is not done yet; because it is not necessary for now;
	}
	else
		error = frame.Error(); // for debug purpose;

	return n_result;
}