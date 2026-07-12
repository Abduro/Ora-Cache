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

CSyncObject& MsgExtRef(void) { static CSyncObject crt_sect; return crt_sect; }

#define Msg_Safe_Lock() Safe_Lock(MsgExtRef());

static uint32_t g_the_last_cmd = 0;

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

#pragma region cls::CCmdHandler{}

CCmdHandler::CCmdHandler (void) : m_fk_wnd(false) { if ((::Get_Shortcut() << IDR_OBJ_PARSER_CTX_MENU_0).Error()) {::__trace_err_ex_2(::Get_Shortcut().Error()); }}

uint32_t CCmdHandler::TrackMenu (void) {

	using CCmd_Handler = shared::console::CCmd_Handler;
	using e_cmd_ids = shared::console::e_cmd_ids;

	const uint32_t u_cmd_id = ::Get_Shortcut().Track(m_fk_wnd);
	switch (u_cmd_id) {
	case CMD_OBJ_PARSER_CON_CLEAR: {
		CCmd_Handler handler;
		if (__failed(handler.On_command(e_cmd_ids::e_clear))) {
			::__trace_err_ex_2(handler.Error());
		} else {
			__trace_info_2(_T("command 'Clear console' (%04u) is completed;\n"), u_cmd_id);
		}
	} break;
	case CMD_OBJ_PARSER_CON_CLOSE: {
		::Get_ConPers().Save();
		{
			Msg_Safe_Lock();
			g_the_last_cmd = u_cmd_id; // signals to main message loop to exit;
		}
		__trace_warn_2(_T("command 'Close Console' (%04u) is handled;\n"), u_cmd_id);
	} break;
	case CMD_OBJ_FILE_SELECT: {
		{
			Msg_Safe_Lock();
			g_the_last_cmd = u_cmd_id; // indicates that 'Open File' command must be handled;
		}
		__trace_warn_2(_T("command 'Open File' (%04u) is handled;\n"), u_cmd_id);
	} break;
	default:;
	}
	return u_cmd_id;
}

#pragma endregion

class CHandler : public CHandler_Dflt {
public:
	CHandler (void) {}

	using CCmd_Handler = shared::console::CCmd_Handler;
	using CBtn_enum  = shared::console::events::input::CBtn_enum;
	using e_cmd_ids = shared::console::e_cmd_ids;
	// to-do: this handler works in worker thread, not in the main one; it is required to redirect commands to the main thread; 
	err_code On_button(const input::evt_mouse_data_t& _data) override final {
		_data;
		this->m_btns.Set(_data.dwButtonState);

		if (this->m_btns.Get(VK_RBUTTON).Is_released()) {
			if (true)
			{
				Msg_Safe_Lock();
				g_the_last_cmd = CMD_OBJ_PARSER_SHOW_CTX;
				return __s_ok;
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
			Msg_Safe_Lock();
			g_the_last_cmd = CMD_OBJ_PARSER_CON_CLOSE;
		}
		return __s_ok;
	}

	err_code On_move (const input::evt_mouse_data_t& _data) override final {
		_data; return __s_ok;
	}

	err_code On_size (const input::evt_buff_size_t _data) override final {
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

	::shared::sys_core::CCoIniter_auto co_initer;
	
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
	CReader reader;
	CCmdHandler cmd_handler;
	do {
		if (error.Is()) break;

		if (__failed(reader.Read())) {
			::__trace_err_ex_2(error = reader.Error());
		}

	} while (true == false);
#if (0) // if an error occurred in one the previous steps, there is no ability to see that error in the console trace, so it is disabled;
	if (error != false) { // goes to message loop and waits the app window will be closed;
		Msg_Safe_Lock();
		b_quit = true;
	}
#endif
	MSG msg = {0};
	uint32_t u_msg_loc = 0;
	do {{
			Msg_Safe_Lock();
			u_msg_loc = g_the_last_cmd; // makes a quick-copy of the last command global value;
		}
		if (u_msg_loc == CMD_OBJ_PARSER_CON_CLOSE)
			break;
		if (u_msg_loc == CMD_OBJ_PARSER_SHOW_CTX) {
			static bool b_track = false;
			if (b_track)
				continue;
			else b_track = true;

			const uint32_t u_cmd_id = cmd_handler.TrackMenu();
			if (false) {}
			else if (CMD_OBJ_PARSER_CON_CLOSE == u_cmd_id) break;
			else if (CMD_OBJ_FILE_SELECT == u_cmd_id) {
				if (__s_ok == (reader.Loc().Open()))
				reader.Read();
			}
			b_track = false;
			Msg_Safe_Lock(); g_the_last_cmd = 0;
		}

		if (::PeekMessage( &msg, 0, 0, 0, PM_REMOVE )) {
		    ::TranslateMessage( &msg );
		    ::DispatchMessage ( &msg );
			if (msg.message == WM_QUIT)
				break;
		}
		
		::Sleep(10); // it looks like useless;
	} while( true != false );

	__trace::OnTime();
	return n_result;
}

#endif