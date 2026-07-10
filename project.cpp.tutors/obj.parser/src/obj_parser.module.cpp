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
#if (0)
	// https://stackoverflow.com/questions/21257544/c-wait-for-user-input ;
	out_t << _T("\n\tPress [Enter] key or click [x] button to exit;");
	in_t.get();
#else
	::_tprintf(_T("\n\n\tPress any key or click [x] button to exit;")); // https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/printf-printf-l-wprintf-wprintf-l ;
	::_gettch();                                                        // https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/getch-getwch ;
#endif
	return 0;
}
#else

using namespace shared::console::events;
using CSyncObject = shared::sys_core::CSyncObject;

CSyncObject& MsgQuitRef(void) { static CSyncObject crt_sect; return crt_sect; }

#define Quit_Safe_Lock() Safe_Lock(MsgQuitRef());
static bool b_quit = false;

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

	using CCmd_Handler = shared::console::CCmd_Handler;
	using CBtn_enum  = shared::console::events::input::CBtn_enum;
	using e_cmd_ids = shared::console::e_cmd_ids;

	err_code On_button(const input::evt_mouse_data_t& _data) override final {
		_data;
		this->m_btns.Set(_data.dwButtonState);

		if (this->m_btns.Get(VK_RBUTTON).Is_released()) {
			if ((::Get_Shortcut() << IDR_OBJ_PARSER_CTX_MENU_0).Error()) {::__trace_err_ex_2(::Get_Shortcut().Error()); }
			else {
				TFakeWnd  m_fk_wnd(false);
				const uint32_t u_cmd_id = ::Get_Shortcut().Track(/*TConAccess()*/m_fk_wnd); // doesn't work for direct call to console window;
				switch (u_cmd_id) {
				case IDR_OBJ_PARSER_CON_CLEAR: {
					CCmd_Handler handler;
					if (__failed(handler.On_command(e_cmd_ids::e_clear))) {
						::__trace_err_ex_2(handler.Error());
					} else {
						__trace_info_2(_T("command 'Clear console' (%04u) is completed;\n"), u_cmd_id);
					}
				
				} break;
				case IDR_OBJ_PARSER_CON_CLOSE: {
					::Get_ConPers().Save();
					{
						Quit_Safe_Lock();
						b_quit = true; // signals to main message loop to exit;
					}
					__trace_warn_2(_T("command 'Close console' (%04u) is completed;\n"), u_cmd_id);
				} break;
				default:;
				}
			}
		}
		return __s_ok;
	}
	/* https://stackoverflow.com/questions/45691954/native-exiting-with-with-code-1073741510-0xc000013a-while-using-prime-checke ;
	   https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-erref/596a1078-e883-4972-9bbc-49e60bebca55 ;
	   0xC000013A >> STATUS_CONTROL_C_EXIT >> {Application Exit by CTRL+C} The application terminated as a result of a CTRL+C.
	*/
	err_code On_close (const ctrl::CEvent::evt_source _dw_reason) override final {
		_dw_reason; // does not matter;
		::Get_ConPers().Save();
		{
		Quit_Safe_Lock();
		b_quit = true;
		}
		return __s_ok;
	}

	err_code On_move (const input::evt_mouse_data_t& _data) override final {
		_data; return __s_ok;
	}

	err_code On_size  (const input::evt_buff_size_t _data) override final {
		_data; return __s_ok;
	}
private:
	CBtn_enum m_btns;
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
	
	// before creating the console, the root registry key must be set so as not to interfere with the 'debugging trace' settings;
	::Get_ConPers().Pos() << CLocator::Root();
	_con.Frame().Use_close(false);

	if (__failed(_con.Create())) { ::__trace_err_ex_2(error = _con.Error()); }
	else {
		shared::console::CBkgnd con_bkg;
		con_bkg.Color(::Get_theme().Bkgnd().Rgba());

		_con.Frame().Icon() << IDR_OBJ_PARSER_CON_0_ICO;
		_con.Frame().Caption() << IDS_OBJ_PARSER_CON_CAP;
	}
	CHandler_auto handler_auto;

	do {
		if (error.Is()) break;
#if (0)
		CLocator locator;
		if (__failed(locator.Locate())) {
			::__trace_err_ex_2(error = locator.Error()); 
			break;
		}
#endif
		CReader reader;
		if (__failed(reader.Read())) {
			::__trace_err_ex_2(error = reader.Error());
		}

	} while (true == false);
#if (0) // if an error occurred in one the previous steps, there is no ability to see that error in the console trace, so it is disabled;
	if (error != false) { // goes to message loop and waits the app window will be closed;
		Quit_Safe_Lock();
		b_quit = true;
	}
#endif
	do {
		Quit_Safe_Lock();
		if (b_quit)
			break;

		if (::PeekMessage( &msg, 0, 0, 0, PM_REMOVE )) {
		    ::TranslateMessage( &msg );
		    ::DispatchMessage ( &msg );
		}
		::Sleep(10); // it looks like useless;
	} while( true != false );

	__trace::OnTime();
	return n_result;
}

#endif