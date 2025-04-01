/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Jan-2016 at 2:00:32am, GMT+7, Phuket, Rawai, Friday;
	This is File Guardian (thefileguardian.com) app entry point implementation file.
	-----------------------------------------------------------------------------
	Adopted to vs15 on 1-Jul-2018 at 6:11:43p, UTC+7, Phuket, Rawai, Sunday;
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

	ebo::boo::gui::CFrame frame;

	n_result = frame.Create();
	if (__succeeded(n_result)) {

		_Module.WinMain(nCmdShow);
		frame.Destroy();       // a handling of possible error is not done yet; because it is not necessary for now;
	}
	else
		error = frame.Error(); // for debug purpose;

	return n_result;
}