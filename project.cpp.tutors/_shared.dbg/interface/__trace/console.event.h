#ifndef _CONSOLE_EVENT_H_INCLUDED
#define _CONSOLE_EVENT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmsil.com) on 22-Mar-2026 at 14:10:38.110, UTC+4, Batumi, Sunday;
	This is Ebo Pack console event handler interface declaration file;
*/
#include "console.defs.h"
#include "console.mode.h"

namespace shared { namespace console { namespace events {
namespace ctrl   { using namespace shared::console;

	// https://learn.microsoft.com/en-us/windows/console/setconsolectrlhandler ;
	class CEvent {
	public:
		enum evt_source : uint32_t  { // https://learn.microsoft.com/en-us/windows/console/handlerroutine ;
		e__undef = 0xf,
		e_abort  = CTRL_C_EVENT     , // https://www.lifewire.com/what-is-ctrl-c-used-for-2625834 ;
		e_break  = CTRL_BREAK_EVENT , // https://learn.microsoft.com/en-us/windows/console/ctrl-c-and-ctrl-break-signals ;
		e_close  = CTRL_CLOSE_EVENT , // the console is being closed by command from system menu or by ending console process in task manager;
		e_logoff = CTRL_LOGOFF_EVENT, // is sent at the end of user session;
		e_shut_down = CTRL_SHUTDOWN_EVENT, // operating system is shutting down, that means computer power is turned off;
		};
		 CEvent (void) = default; CEvent (const CEvent&) = delete; CEvent (CEvent&&) = delete;
		~CEvent (void) = default;

	private:
		CEvent& operator = (const CEvent&) = delete; CEvent& operator = (CEvent&&) = delete;
	};

	class CHandler {
	public:
		CHandler (void); CHandler (const CHandler&) = delete; CHandler (CHandler&&) = delete;

		TError&  Error (void) const;

	private:
		CHandler& operator = (const CHandler&) = delete; CHandler& operator = (CHandler&&) = delete;
		CError m_error;
	};

}
namespace input  { using namespace shared::console;

	// https://learn.microsoft.com/en-us/windows/console/reading-input-buffer-events << the example of using ReadConsoleInput();
	// https://learn.microsoft.com/en-us/windows/console/readconsoleinput ;

	class CEvent {
	public:
		enum evt_source : uint32_t { // https://learn.microsoft.com/en-us/windows/console/input-record-str ;
		e__undef = 0x0,
		e_buffer = 0x1, // https://learn.microsoft.com/en-us/windows/console/window-buffer-size-record-str ;
		e_focus  = 0x2, // https://learn.microsoft.com/en-us/windows/console/focus-event-record-str ; no info provided yet; 
		e_kbrd   = 0x3, // https://learn.microsoft.com/en-us/windows/console/key-event-record-str ;
		e_menu   = 0x4, // https://learn.microsoft.com/en-us/windows/console/menu-event-record-str ;
		e_mouse  = 0x5, // https://learn.microsoft.com/en-us/windows/console/mouse-event-record-str ;
		};
		 CEvent (void) = default; CEvent (const CEvent&) = delete; CEvent (CEvent&&) = delete;
		~CEvent (void) = default;

	private:
		CEvent& operator = (const CEvent&) = delete; CEvent& operator = (CEvent&&) = delete;
	};

	interface IEvtHandler {
		// returned code: __s_ok - event handled, __s_false - not handled, otherwise error code;
		virtual err_code On_menu  (const MENU_EVENT_RECORD&) { return __s_false; } // selected command identifier would be enough;
		virtual err_code On_mouse (const MOUSE_EVENT_RECORD&) { return __s_false; }
		virtual err_code On_kbrd  (const KEY_EVENT_RECORD&) { return __s_false; }
	};

	class CRouter {
	public:
		CRouter (void); CRouter (const CRouter&) = delete; CRouter (CRouter&&) = delete;

		TError&  Error (void) const;
		bool     Is_on (void) const;
		err_code Turn  (const bool _b_on_off); // it makes this router started to do its work or stopped to route events;

	private:
		CRouter& operator = (const CRouter&) = delete; CRouter& operator = (CRouter&&) = delete;
		void Receive_evt (void); // thread function for receiving input events;

		CError m_error;
		::std::thread  m_thread; // the thread for receiving input buffer events;
		volatile bool  m_turned;
	};
}
}}}

typedef shared::console::events::input::CRouter TInputRouter; TInputRouter& Get_input (void);

#endif/*_CONSOLE_EVENT_H_INCLUDED*/