/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Aug-2026 at 08:40:26.442, UTC+4, Batumi, Wednesday;
	This is virtual camera test cases' desktop GUI app module interface implementation file;
*/
#include "test.gui.module.h"

using namespace ::test::draw;

CModule _Module;

err_code CModule::PreMessageLoop (int nShowCmd) {
	nShowCmd;
	err_code n_result = __s_ok;

	n_result = TModule::PreMessageLoop(nShowCmd);
	if (__failed(n_result))
		return n_result;
	else
		return n_result = __s_ok; // forces to continue working with pumping windows' messages;
}

/* api-ms-win-core-synch-l1-2-0 cannot be loaded >> access violation error may occur in case when this solution must be re-built;
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
	do {

		if (::PeekMessage( &msg, 0, 0, 0, PM_REMOVE )) {
		    ::TranslateMessage( &msg );
		    ::DispatchMessage ( &msg );
			if (msg.message == WM_QUIT)
				break;
		}
	} while( true != false );

	return n_result;
}