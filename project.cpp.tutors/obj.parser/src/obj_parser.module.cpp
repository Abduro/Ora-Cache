/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Jun-2026 at 11:48:34.557, UTC+4, Batumi, Sunday;
	This is 3D module object parser module interface implementation file;
*/
#include "obj_parser.module.h"
#include "obj_parser.res.h"

using namespace ::shared::parsers::obj;

#if defined(_USE_CONSOLE)
uint32_t _tmain (int argc, _TCHAR* argv[]) {
	argc; argv;
	using namespace shared::console;

	CInvader invader; invader.Deprive();

	CPers pers; if (__failed(pers.Load())) __trace_err_ex_2(pers.Error());
	CLoader().Do_it();
	
#if (0)
	// https://stackoverflow.com/questions/21257544/c-wait-for-user-input ;
	out_t << _T("\n\tPress [Enter] key or click [x] button to exit;");
	in_t.get();
#else
	::_tprintf(_T("\n\n\tPress any key or click [x] button to exit;")); // https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/printf-printf-l-wprintf-wprintf-l ;
	::_gettch();                                                        // https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/getch-getwch ;
#endif
	invader.BringBack();
	return 0;
}
#else

using namespace shared::console::events;

CTraceConsole _Module;

err_code CTraceConsole::PreMessageLoop (int nShowCmd) {
	nShowCmd;
	err_code n_result = __s_ok;

	n_result = TModule::PreMessageLoop(nShowCmd);
	if (__failed(n_result))
		return n_result;
	else
		return n_result = __s_ok; // forces to continue working with pumping windows' messages;
}

class CHandler : public CHandler_Dflt {
public:
	CHandler (void) {}

	err_code On_close (const ctrl::CEvent::evt_source _dw_reason) override final {
		_dw_reason; // does not matter;
		::Get_ConPers().Save();
		return __s_ok;
	}

	err_code On_move (const input::evt_mouse_data_t& _data) override final {
		_data; return __s_ok;
	}

	err_code On_size  (const input::evt_buff_size_t _data) override final {
		_data; return __s_ok;
	}
};

class CHandler_auto {
public:
	CHandler_auto (void) {
		TInputRouter& in_router = ::Get_input(); if (in_router.Turn(true) == __s_ok) in_router.Subscribe(&this->m_handler);
		TCtrlRouter& ctrl_router = ::Get_ctrl(); if (ctrl_router.Turn(true) == __s_ok) ctrl_router.Subscribe(&this->m_handler);
	}
	~CHandler_auto (void) {
		TInputRouter& in_router = ::Get_input(); in_router.Unsubscribe(&this->m_handler); in_router.Turn(false);
		TCtrlRouter& ctrl_router = ::Get_ctrl(); ctrl_router.Unsubscribe(&this->m_handler); ctrl_router.Turn(false);
	}
private:
	CHandler m_handler;
};

/* api-ms-win-core-synch-l1-2-0 cannot be loaded >> access violation error may occur in case when this solution must be re-built;
*/
INT __stdcall _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpstrCmdLine, INT nCmdShow) {
	hInstance; hPrevInstance; lpstrCmdLine; nCmdShow;
	CError error(__CLASS__,__METHOD__,__s_ok);
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
	bool b_error = true;
	
	// before creating the console, the root registry key must be set so as not to interfere with the 'debugging trace' settings;
	CString cs_root = TString().Format(_T("%s\\Utils\\ObjParser"), ::Get_reg_router().Root().Path());

	::Get_ConPers().Pos() << (_pc_sz) cs_root;
	_con.Frame().Use_close(true);

	if (__failed(_con.Create())) { __trace_err_ex_2(_con.Error()); }
	else {
		shared::console::CFont font_; font_.Set(_T("consolas"), 15);
		shared::console::CBkgnd con_bkg;
		con_bkg.Color(::Get_theme().Bkgnd().Rgba());

		_con.Frame().Icon() << IDR_OBJ_PARSER_CON_0_ICO;
		_con.Frame().Caption() << IDS_OBJ_PARSER_CON_CAP;

		b_error = false;
	}
	CHandler_auto handler_auto;

	do {} while (true == false);

	if (b_error != false) // goes to message loop and waits the app window will be closed;
		msg.message = WM_QUIT;

	while( WM_QUIT != msg.message ) {
		if (::PeekMessage( &msg, 0, 0, 0, PM_REMOVE )) {
		    ::TranslateMessage( &msg );
		    ::DispatchMessage ( &msg );
		}
		::Sleep(100); // it looks like useless;
	}

	__trace::OnTime();
	return n_result;
}

#endif