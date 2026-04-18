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

	#define WND_BUF_SIZE_REC WINDOW_BUFFER_SIZE_RECORD

	typedef MENU_EVENT_RECORD  evt_menu_data_t;
	typedef MOUSE_EVENT_RECORD evt_mouse_data_t;
	typedef KEY_EVENT_RECORD   evt_kbrd_data_t;
	typedef WND_BUF_SIZE_REC   evt_buff_size_t;

	/* this key base class could contain 'generic' state of particular key true/false: pressed/released for control key and turned on/off for lock keys;
	   but for this version of the implementation, the control and lock key classes do this separately;
	*/
	class CKey_Base {
	protected:
		CKey_Base (void); CKey_Base (const CKey_Base&); CKey_Base (CKey_Base&&); ~CKey_Base (void) = default;

	public:
		uint16_t  Code (void) const;      // gets key virtual code;
		bool      Code (const uint16_t);  // sets key virtual code; returns 'true' in case of code change;
		_pc_sz Name (void) const;         // gets the key name;
		bool   Name (_pc_sz);             // sets the key name; returns 'true' in case of name change;

		bool   Is_changed (void) const;   // indicates the key state is changed;
		bool&  Is_changed (void) ;        // sets the key change flag value;
	
		CKey_Base& operator <<(const bool  _b_changed);
		CKey_Base& operator <<(const uint16_t _u_code);
		CKey_Base& operator <<(const _pc_sz   _p_name);
		CKey_Base& operator <<(const CString _cs_name);

		CKey_Base& operator = (const CKey_Base&); CKey_Base& operator = (CKey_Base&&);
	protected:
		uint16_t m_code;
		CString  m_name;
		bool     m_changed;
	};

	class CCtrl_Key : public CKey_Base { typedef CKey_Base TBase;
	public:
		enum e_state : uint32_t {
		e_none     = 0x0,  // normal state, neither pressed nor released;
		e_pressed  = 0x1,  // the key is pressed and still be held;
		e_released = 0x2,  // the key is released;
		};
		
		 CCtrl_Key (void); CCtrl_Key (const CCtrl_Key&); CCtrl_Key (CCtrl_Key&&);
		~CCtrl_Key (void) = default;

		e_state  State (void) const;      // gets current key state;
		bool     State (const e_state);   // sets current key state' returns 'true' in case of state change;

		bool  Is_pressed (void) const;    // returns 'true' if the key is pressed;
		bool  Is_released (void) const;   // returns 'true' if the key is released;
	
		CCtrl_Key& operator = (const CCtrl_Key&);
		CCtrl_Key& operator = (CCtrl_Key&&);

		CCtrl_Key& operator <<(const e_state);
		const
		CKey_Base& operator ()(void) const;
		CKey_Base& operator ()(void) ;

	private:
		e_state  m_state;  // pressed/released;
	};

	class CLock_Key : public CKey_Base { typedef CKey_Base TBase;
	public:
		enum e_turn : uint32_t {
			e_off = 0x0,
			e_on
		};
		CLock_Key (void); CLock_Key (const CLock_Key&); CLock_Key (CLock_Key&&); ~CLock_Key (void) = default;

		bool  Is_turned (void) const;     // returns 'true' in case when the key state is turned on, e.g. caps loc is turned on;
		bool  Is_turned (const e_turn);   // turns 'on' or 'off' the key turn state;

		e_turn Turn (void) const;         // returns an element of turn state enumeration which is currently set;

		CLock_Key& operator = (const CLock_Key&);
		CLock_Key& operator = (CLock_Key&&);

		CLock_Key& operator <<(const e_turn);
		const
		CKey_Base& operator ()(void) const;
		CKey_Base& operator ()(void) ;

	private:
		e_turn m_turn; // turned on/off;
	};
	// these codes are for using in GetAsyncKeyState(), they have different codes in console type definition;
	static const uint16_t v_psd_codes[] = {VK_LCONTROL, VK_RCONTROL, VK_LSHIFT, VK_RSHIFT, VK_LMENU, VK_RMENU}; // 6 elements;
	static const uint32_t v_psd_count = _countof(v_psd_codes);
	static _pc_sz p_psd_names[] = {_T("L-Ctrl"), _T("R-Ctrl"), _T("L-Shift"), _T("R-Shift"), _T("L-Alt"), _T("R-Alt")}; // 6 elements;

	// these codes are from console type definition (wincontypes.h), otherwise it would be >> VK_CAPITAL, VK_NUMLOCK and VK_SCROLL;
	static const uint16_t v_lck_codes[] = /*{CAPSLOCK_ON, NUMLOCK_ON, SCROLLLOCK_ON}*/{VK_CAPITAL, VK_NUMLOCK, VK_SCROLL};
	static const uint32_t v_lck_count = _countof(v_lck_codes);
	static _pc_sz p_lck_names[] = {_T("Caps Lock"), _T("Num Lock"), _T("ScrLk")}; // https://en.wikipedia.org/wiki/Scroll_Lock ;

	// perhaps using std::map would be better;
	typedef ::std::vector<CCtrl_Key> ctrl_keys_t;
	typedef ::std::vector<CLock_Key> lock_keys_t;

	/* from https://learn.microsoft.com/en-us/windows/console/key-event-record-str#remarks ;
	ENHANCED_KEY could possibly be one of the keys from keypad:
	(Num Lock is off)
	VK_NUMPAD0 >> [Ins] ; VK_DECIMAL >> [Del] ;
	VK_NUMPAD1 >> [End] ; VK_NUMPAD2 >> [Down]; VK_NUMPAD3 >> [Pg Dn]; VK_NUMPAD4 >> [Left]; VK_NUMPAD6 >> [Right];
	VK_NUMPAD7 >> [Home]; VK_NUMPAD8 >> [Up]  ; VK_NUMPAD9 >> [Pg Up];
	(Num Lock does not affect)
	VK_RETURN  >> [Enter],VK_DIVIDE  >> [/];
	*/

	class CKey_enum {
	public:
		CKey_enum (void); CKey_enum (const CKey_enum&) = delete; CKey_enum (CKey_enum&&) = delete; ~CKey_enum (void) = default;

		const
		CCtrl_Key& Get_Ctrl (const dword _v_code) const; // gets the reference to key by virtual code (either generic or console code), if not found, fake reference is returned;
		CCtrl_Key& Get_Ctrl (const dword _v_code) ;
		const
		CLock_Key& Get_Lock (const dword _v_code) const;
		CLock_Key& Get_Lock (const dword _v_code) ;

		const ctrl_keys_t& Set_Ctrl (void); // it uses GetAsyncKeyState() for setting appropriate state of the control keys; 
		const lock_keys_t& Set_Lock (void); // it uses GetAsyncKeyState() for setting appropriate state of the lock keys;

		const ctrl_keys_t& Set_Ctrl (const dword _ctrl_state); // sets ctrl key state by using MOUSE_EVENT_RECORD.dwControlKeyState;
		const lock_keys_t& Set_Lock (const dword _lock_state); // sets lock key state by using MOUSE_EVENT_RECORD.dwControlKeyState;

	private:
		CKey_enum& operator = (const CKey_enum&) = delete; CKey_enum& operator = (CKey_enum&&) = delete;
		ctrl_keys_t m_ctrl;
		lock_keys_t m_lock;
	};

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
		enum evt_mouse : uint32_t {
			e_button = evt_source::e_mouse + 1,
			e_move   = e_button + 1,
		};
		 CEvent (void) = default; CEvent (const CEvent&) = delete; CEvent (CEvent&&) = delete;
		~CEvent (void) = default;

		static CString  To_str (const evt_buff_size_t&);
		static CString  To_str (const evt_menu_data_t&);
		static CString  To_str (const evt_mouse_data_t&, const evt_mouse);
		static CString  To_str (const evt_kbrd_data_t&);

	private:
		CEvent& operator = (const CEvent&) = delete; CEvent& operator = (CEvent&&) = delete;
	};

	interface IEvtMouse {
		// returned code: __s_ok - event handled, __s_false - not handled, otherwise error code;
		virtual err_code On_button (const evt_mouse_data_t&) { return __s_false; }  // on mouse button press/release;
		virtual err_code On_move   (const evt_mouse_data_t&) { return __s_false; }  // on mouse move/double click;
	};

	interface IEvtHandler : public IEvtMouse {
		// returned code: __s_ok - event handled, __s_false - not handled, otherwise error code;

		virtual err_code On_menu  (const evt_menu_data_t&)  { return __s_false; } // selected command identifier would be enough;
		virtual err_code On_mouse (const evt_mouse_data_t&) { return __s_false; } // for mouse related events: button press/release and mouse move;
		virtual err_code On_kbrd  (const evt_kbrd_data_t&)  { return __s_false; } // keyboard input events; 
		virtual err_code On_size  (const evt_buff_size_t) { return __s_false; } // console window size change;
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
	class CHandler_Dflt : public input::IEvtHandler, public ctrl::IEvtHandler {
	public:
		 CHandler_Dflt (void) = default; CHandler_Dflt (const CHandler_Dflt&) = delete; CHandler_Dflt (CHandler_Dflt&&) = delete;
		~CHandler_Dflt (void) = default;

		err_code On_close (const ctrl::CEvent::evt_source _dw_reason) override; // this event can be traced to log file or/and VS debug output;
		err_code On_menu  (const input::evt_menu_data_t&  _data) override;
		err_code On_mouse (const input::evt_mouse_data_t& _data) override;
		err_code On_kbrd  (const input::evt_kbrd_data_t&  _data) override;
		err_code On_size  (const input::evt_buff_size_t _data) override;

		err_code On_button(const input::evt_mouse_data_t& _data) override;  // on mouse button press/release;
		err_code On_move  (const input::evt_mouse_data_t& _data) override;  // on mouse move/double click;

	private:
		CHandler_Dflt& operator = (const CHandler_Dflt&) = delete; CHandler_Dflt& operator = (CHandler_Dflt&&) = delete;
	};
}}}

bool operator != (const COORD& _left, const COORD& _right);
bool operator == (const COORD& _left, const COORD& _right);

typedef shared::console::events::ctrl::CRouter  TCtrlRouter;  TCtrlRouter& Get_ctrl (void);
typedef shared::console::events::input::CRouter TInputRouter; TInputRouter& Get_input (void);

#endif/*_CONSOLE_EVENT_H_INCLUDED*/