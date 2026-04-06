/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Mar-2026 at 13:21:33.292, UTC+4, Batumi, Tuesday;
	This is Ebo Pack tutorials' shared debug trace console entry point implementation file;
*/
#include "trace_con.module.h"
#include "trace_con.loader.h"

/*Enable Automatic Closing (Recommended):
  (1) Navigate to Settings: Go to Tools > Options from the top menu;
  (2) Debugging Section: Expand the Debugging category on the left and select General;
  (3) Toggle the Checkbox: Find the option 'Automatically close the console when debugging stops' and ensure it is checked;
*/
#pragma region cls::CInvader{}

using namespace shared::console;
using namespace shared::console::_impl;

static _pc_sz p_err_no_con_wnd = _T("#__e_hwnd: console window is not attached");

__int3264 CInvader::m_proc_origin = 0;

CInvader:: CInvader (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("#__e_not_inited: no subclassing yet"); }
CInvader::~CInvader (void) {}

err_code CInvader::BringBack (void) {
	this->m_error <<__METHOD__<<__s_ok;

	const HWND h_con_wnd = ::GetConsoleWindow();
	if (nullptr == h_con_wnd)
		return this->m_error <<__e_hwnd = p_err_no_con_wnd;

	if (0 == CInvader::m_proc_origin)
		return this->m_error <<(err_code)TErrCodes::eExecute::eState = _T("#__e_state: console window is not subclassed");

	if (0 == ::SetWindowLongPtr(h_con_wnd, GWLP_WNDPROC, CInvader::m_proc_origin)) {
		this->m_error.Last();
		__trace_err_ex_2(this->m_error);
	}
	else
		CInvader::m_proc_origin = 0;

	return this->Error();
}

err_code CInvader::Deprive (void) {
	this->m_error <<__METHOD__<<__s_ok;

	const HWND h_con_wnd = ::GetConsoleWindow();
	if (nullptr == h_con_wnd)
		return this->m_error <<__e_hwnd = p_err_no_con_wnd;

	if (0 != CInvader::m_proc_origin)
		return this->m_error <<(err_code)TErrCodes::eExecute::eState = _T("#__e_state: console window is already subclassed");

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowlongptrw ;
	CInvader::m_proc_origin = ::SetWindowLongPtr(h_con_wnd, GWLP_WNDPROC, (LONG_PTR)CInvader::WndProc);
	if (0 == CInvader::m_proc_origin) {
		this->m_error.Last();
		__trace_err_ex_2(this->m_error);
	}

	return this->Error();
}

TError   CInvader::Error (void) const { return this->m_error; }

l_result CInvader::WndProc (HWND _h_wnd, _uint _u_msg, w_param _w_value, l_param _l_value) {
	_h_wnd; _u_msg; _w_value; _l_value;
	/*
	::SetWindowPos(
		h_con_wnd, 0, _rect_wnd_pos.left, _rect_wnd_pos.top, __W(_rect_wnd_pos), __H(_rect_wnd_pos), SWP_FRAMECHANGED|SWP_NOACTIVATE|SWP_NOZORDER
	);
	*/
	switch (_u_msg) {
	case WM_CREATE: {
	/* https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-create ;
	   important excerpts from the above atricle:
	   (1) this message is sent before the function returns (CreateWindow|CreateWindowEx);
	   (2) window procedure of the new window receives this message after the window is created, but *before* the window becomes *visible*;
	*/
		CError error(__CLASS__,__METHOD__,__s_ok);

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-createstructw ;
		CREATESTRUCT* p_create = reinterpret_cast<CREATESTRUCT*>(_l_value);
		if (0 == p_create)
			break; // let's default win proc takes care;
		if (WS_VISIBLE & p_create->style) {}
	/*
	   (3) it should return zero to continue creation of the window. If the application returns –1, the window is destroyed and the 
	       (CreateWindow|CreateWindowEx) returns nullptr (0);
	*/
		return 0;
	} break;
	case WM_WINDOWPOSCHANGING: { // == {#_u_msg}
	/* https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-windowposchanged ;
	   important excerpts from the article above:
	   (1) The WM_SIZE and WM_MOVE messages are not sent if an application handles the {#_u_msg} >> no call to def_win_proc;
	   (2) It is more *efficient* to perform any move or size change processing during {#_u_msg} >> no call to def_win_proc;
	*/
		CError error(__CLASS__,__METHOD__,__s_ok);

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-windowpos ;
		WINDOWPOS* p_wnd_pos = reinterpret_cast<WINDOWPOS*>(_l_value);
		if (0 == p_wnd_pos)
			break; // let's default win proc takes care;
		
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowpos ;
		if (0 == ::SetWindowPos(_h_wnd, p_wnd_pos->hwndInsertAfter, p_wnd_pos->x, p_wnd_pos->y, p_wnd_pos->cx, p_wnd_pos->cy, p_wnd_pos->flags)) {
			error.Last();
			__trace_err_ex_2(error);
		}
		return false == error ? __s_ok : __s_false; // __s_ok: message is handled, otherwise __s_false;
	} break;
	default: ;
	}
	if (0 == CInvader::m_proc_origin)
	return ::DefWindowProc(_h_wnd, _u_msg, _w_value, _w_value); else
	return ::CallWindowProc((pfn_WndProc) CInvader::m_proc_origin, _h_wnd, _u_msg, _w_value, _w_value);
}

#pragma endregion
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

class COutput : public input::IEvtHandler {
public:
	COutput (void) = default; ~COutput (void) = default;

	err_code On_menu (const input::evt_menu_data_t& _data) override final {
		__trace_info(_T("%s\n"), (_pc_sz) input::CEvent().To_str(_data)); return __s_ok;
	}

	err_code On_mouse (const input::evt_mouse_data_t& _data) override final {
		__trace_info(_T("%s\n"), (_pc_sz) input::CEvent().To_str(_data)); return __s_ok;
	}

	err_code On_size (const input::evt_buffer_size_t _data) override final {
		__trace_info(_T("%s\n"), (_pc_sz) input::CEvent().To_str(_data)); return __s_ok;
	}
};

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

	using CCon_cls = ex_ui::popup::CCon_cls;

	MSG msg = {0};
	bool b_error = true;

	COutput out_;

	do {
		CCon_cls con_cls;
#if (0) // it dosn't work: there's no atom of the console class in global atom table;
		if (__failed(con_cls.Get())) {
			__trace_err_ex_2(con_cls.Error());
		}
#elsif (false == true)
		if (__failed(con_cls.Register())) {
			__trace_err_ex_2(con_cls.Error()); break;
		}

		con_cls << CInvader::WndProc;
		if (::AllocConsole()) b_error = false;

		if (__failed(con_cls.Unregister())) {
			__trace_err_ex_2(con_cls.Error()); break;
		}
#endif
		if (false == !!::AllocConsole()) break;

		TInputRouter& in_route = ::Get_input();
		if (__failed( in_route.Turn(true))) {
			__trace_err_ex_2(in_route.Error()); break;
		}

		in_route.Subscribe(&out_);

		CPers pers; if (__failed(pers.Load())) __trace_err_ex_2(pers.Error());
		CLoader().Do_it();

		b_error = false;

	} while (true == false);

	if (b_error != false) // goes to message loop and waits the app window will be closed;
		msg.message = WM_QUIT;

	while( WM_QUIT != msg.message ) {
		if (::PeekMessage( &msg, 0, 0, 0, PM_REMOVE )) {
		    ::TranslateMessage( &msg );
		    ::DispatchMessage ( &msg );
		}
		::Sleep(100);
	}

	__trace::OnTime();
	return n_result;
}
#endif