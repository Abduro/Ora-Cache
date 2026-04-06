#ifndef _CONSOLE_EVENT_H_INCLUDED
#define _CONSOLE_EVENT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmsil.com) on 22-Mar-2026 at 14:10:38.110, UTC+4, Batumi, Sunday;
	This is Ebo Pack console event handler interface declaration file;
*/
#include "console.defs.h"
#include "console.mode.h"

namespace shared { namespace console { namespace events {

	class CRouterBase {
	protected:
		 CRouterBase (void); CRouterBase (const CRouterBase&) = delete; CRouterBase (CRouterBase&&) = delete;
		~CRouterBase (void) = default;
	public:
		TError&  Error (void) const;
		bool     Is_on (void) const;

	protected:
		CRouterBase& operator = (const CRouterBase&) = delete; CRouterBase& operator = (CRouterBase&&) = delete;
		CError m_error;
		volatile bool  m_turned;
	};
namespace ctrl   { using namespace shared::console;
#define ctrl_c_key    CTRL_C_EVENT
#define ctsl_break    CTRL_BREAK_EVENT
#define ctrl_close    CTRL_CLOSE_EVENT
#define ctrl_logoff   CTRL_LOGOFF_EVENT
#define ctrl_shutdown CTRL_SHUTDOWN_EVENT
	// https://learn.microsoft.com/en-us/windows/console/setconsolectrlhandler ;
	class CEvent {
	public:
		enum evt_source : uint32_t { // https://learn.microsoft.com/en-us/windows/console/handlerroutine ;
		e__undef   = 0xf,
		e_abort    = ctrl_c_key   , // https://www.lifewire.com/what-is-ctrl-c-used-for-2625834 ;
		e_break    = ctsl_break   , // https://learn.microsoft.com/en-us/windows/console/ctrl-c-and-ctrl-break-signals ;
		e_close    = ctrl_close   , // the console is being closed by command from system menu or by ending console process in task manager;
		e_logoff   = ctrl_logoff  , // is sent at the end of user session;
		e_shutdown = ctrl_shutdown, // operating system is shutting down, that means computer power is turned off;
		};
		 CEvent (void) = default; CEvent (const CEvent&) = delete; CEvent (CEvent&&) = delete;
		~CEvent (void) = default;

		static evt_source DwordToEnum (const dword);
		static CString To_str (const evt_source);

	private:
		CEvent& operator = (const CEvent&) = delete; CEvent& operator = (CEvent&&) = delete;
	};

	interface IEvtHandler {
		// returned code: __s_ok - event handled, __s_false - not handled, otherwise error code;
		virtual err_code On_close (const CEvent::evt_source _dw_reason) { _dw_reason; return __s_false; }
	};

	class CRouter : public CRouterBase { typedef CRouterBase TBase;
	public:
		 CRouter (void); CRouter (const CRouter&) = delete; CRouter (CRouter&&) = delete;
		~CRouter (void); // auto-turn-off is required;

		err_code Turn (const bool _b_on_off); // it makes this router started to do its work or stopped to route events;

		err_code Subscribe (const IEvtHandler*);
		err_code Unsubscribe (const IEvtHandler*);

		err_code operator <<(const IEvtHandler*); // subscribes the given interface handler pointer;
		err_code operator >>(const IEvtHandler*); // unsubscribes the given interface handler pointer;

	private:
		CRouter& operator = (const CRouter&) = delete; CRouter& operator = (CRouter&&) = delete;
		// https://learn.microsoft.com/en-us/windows/console/handlerroutine ;
		static int __stdcall Receive_evt (const dword dwCtrlType); // returns 'true' if the signal is handled, otherwise 'false';
	};
}
namespace input  { using namespace shared::console;

	// https://learn.microsoft.com/en-us/windows/console/reading-input-buffer-events << the example of using ReadConsoleInput();
	// https://learn.microsoft.com/en-us/windows/console/readconsoleinput ;

	typedef MENU_EVENT_RECORD   evt_menu_data_t;
	typedef MOUSE_EVENT_RECORD  evt_mouse_data_t;
	typedef KEY_EVENT_RECORD    evt_kbrd_data_t;
	typedef WINDOW_BUFFER_SIZE_RECORD evt_buffer_size_t;

	class CEvent {
	public:
		enum evt_source : uint32_t { // https://learn.microsoft.com/en-us/windows/console/input-record-str ;
		e__undef = 0x0,
		e_buffer = 0x1, // https://learn.microsoft.com/en-us/windows/console/window-buffer-size-record-str ;
		e_focus  = 0x2, // https://learn.microsoft.com/en-us/windows/console/focus-event-record-str ; no info is provided yet; 
		e_kbrd   = 0x3, // https://learn.microsoft.com/en-us/windows/console/key-event-record-str ;
		e_menu   = 0x4, // https://learn.microsoft.com/en-us/windows/console/menu-event-record-str ;
		e_mouse  = 0x5, // https://learn.microsoft.com/en-us/windows/console/mouse-event-record-str ;
		};
		 CEvent (void) = default; CEvent (const CEvent&) = delete; CEvent (CEvent&&) = delete;
		~CEvent (void) = default;

		static CString  To_str (const evt_menu_data_t&);
		static CString  To_str (const evt_mouse_data_t&);
		static CString  To_str (const evt_kbrd_data_t&);
		static CString  To_str (const evt_buffer_size_t&);

	private:
		CEvent& operator = (const CEvent&) = delete; CEvent& operator = (CEvent&&) = delete;
	};

	interface IEvtHandler {
		// returned code: __s_ok - event handled, __s_false - not handled, otherwise error code;

		virtual err_code On_menu  (const evt_menu_data_t&) { return __s_false; } // selected command identifier would be enough;
		virtual err_code On_mouse (const evt_mouse_data_t&) { return __s_false; }
		virtual err_code On_kbrd  (const evt_kbrd_data_t&) { return __s_false; }
		virtual err_code On_size  (const evt_buffer_size_t) { return __s_false; }
	};

	class CRouter : public CRouterBase { typedef CRouterBase TBase;
	public:
		 CRouter (void); CRouter (const CRouter&) = delete; CRouter (CRouter&&) = delete;
		~CRouter (void); // auto-turn-off is required;

		err_code Turn  (const bool _b_on_off); // it makes this router started to do its work or stopped to route events;

		err_code Subscribe (const IEvtHandler*);
		err_code Unsubscribe (const IEvtHandler*);

		err_code operator <<(const IEvtHandler*); // subscribes the given interface handler pointer;
		err_code operator >>(const IEvtHandler*); // unsubscribes the given interface handler pointer;

	private:
		CRouter& operator = (const CRouter&) = delete; CRouter& operator = (CRouter&&) = delete;
		void Receive_evt (void); // thread function for receiving input events;
		::std::thread  m_thread; // the thread for receiving input buffer events;
	};
}
}}}

typedef shared::console::events::ctrl::CRouter  TCtrlRouter;  TCtrlRouter& Get_ctrl (void);
typedef shared::console::events::input::CRouter TInputRouter; TInputRouter& Get_input (void);

#endif/*_CONSOLE_EVENT_H_INCLUDED*/