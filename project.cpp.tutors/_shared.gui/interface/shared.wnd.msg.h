#ifndef _SHARED_WND_MSG_H_INCLUDED
#define _SHARED_WND_MSG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Sep-2025 at 01:12:31.835, UTC+4, Batumi, Friday;
	This is Ebo Pack shared window message handler interface declaration file;
*/
#include "shared.defs.h"

namespace ex_ui { namespace popup { namespace messages {

	using namespace shared::defs;

	class CBaseHandler {
	public:
		CBaseHandler (void); ~CBaseHandler (void) = default; CBaseHandler (const CBaseHandler&) = delete; CBaseHandler (CBaseHandler&&) = delete;

		TError& Error (void) const;

	protected:
		CError m_error;
	private:
		CBaseHandler& operator = (const CBaseHandler&) = delete; CBaseHandler& operator = (CBaseHandler&&) = delete;
	};

	interface IMsg_Handler {
		static const err_code _n_not_handled = -1;
		virtual err_code IMsg_OnMessage (const uint32_t _u_code, const w_param, const l_param) { // possibly, 'const' to w_param/l_param must be removed;
			_u_code;                // message code, e.g. WM_CREATE;
			return _n_not_handled;  // __s_ok|__s_false - depending on the message code, otherwise the error code; 
		}
	};

	// https://learn.microsoft.com/en-us/windows/win32/learnwin32/writing-the-window-procedure#avoiding-bottlenecks-in-your-window-procedure ;
	class CMsgRouter : public CBaseHandler { typedef CBaseHandler TBase;
	public:
		CMsgRouter (void); ~CMsgRouter (void) = default;

		bool ApplyTo (WNDCLASSEX&); // sets the pointer to address of the internal message handler/window procedure; returns 'true' in case of data changed;

		err_code Subscribe (const HWND, IMsg_Handler&);
		err_code Unsubscribe (const HWND);
	};

	interface IMouse_Handler {

		enum class e_action : uint32_t {
			e_none = 0x0, e_double = 0x1, e_pressed = 0x2, e_released = 0x3,
		};

		enum class e_button : uint32_t { // mouse buttons' enumeration;
			e_undef = 0x0, e_left = MK_LBUTTON , e_middle = MK_MBUTTON , e_right = MK_RBUTTON , e_x_1 = MK_XBUTTON1, e_x_2 = MK_XBUTTON2,
		};

		enum class e_v_key : uint32_t { // virtual keys enumeration;
			e_none = 0x0,
			e_alt  = FALT    ,  // alt-key is not defined in mouse message virtual keys, but the definition for keyboard accelerators is fine;        
			e_ctrl = FCONTROL,  // the 'ctrl' key is down; the same as MK_CONTROL [0x0008] ;
			e_shft = FSHIFT  ,  // the 'shift' key is down; the same as MK_SHIF [0x0004] ;
		};

		class CCoords {
		public:
			CCoords (void); CCoords (const CCoords&) = delete; CCoords (CCoords&&) = delete; ~CCoords (void) = default;

			const
			t_point& Get (void) const;    // returns the reference to currently set cursor position;
			bool     Set (const l_param); // sets the cursor position in client area coordinate system; returns 'true' if the cursor position is changed;
			bool Use_screen (void) const;
			void Use_screen (const bool); // to-do: this option is not accessible from event consumer side, set to 'true' by default;

		private:
			CCoords& operator = (const CCoords&) = delete; CCoords& operator = (CCoords&&) = delete;
			bool     m_screen;  // this flag is for using point in different coordinate systems: 'true' - screen, 'false' - window client area;
			t_point  m_point;
		};
		
		class CVirtKeys {
		public:
			CVirtKeys (void); CVirtKeys (const CVirtKeys&) = delete; CVirtKeys (CVirtKeys&&) = delete; ~CVirtKeys (void) = default;

			bool Get (const e_v_key) const;  // returns 'true' if the given key is pressed;
			bool Set (const w_param) ;       // sets the flags from given w_param value; returns 'true' if at least one virtual key state is changed;

			static bool Has (const e_v_key e_key, const w_param _values);

		private:
			CVirtKeys& operator = (const CVirtKeys&) = delete; CVirtKeys& operator = (CVirtKeys&&) = delete;
			bool m_keys[3]; // 0: alt; 1: ctrl; 2: shift;
		};

		class CEvent {
		public:
			CEvent (void); CEvent (const CEvent&) = delete; CEvent (CEvent&&) = delete; ~CEvent (void) = default;

			e_action Action (void) const;
			bool     Action (const e_action);
			e_button Button (void) const;
			bool     Button (const e_button);
			const
			CCoords& Coords (void) const;
			CCoords& Coords (void) ;
			const
			CVirtKeys& Keys (void) const;
			CVirtKeys& Keys (void) ;

			CString  To_str (void) const;

		private:
			CEvent& operator = (const CEvent&) = delete; CEvent& operator = (CEvent&&) = delete;
			e_action  m_action;
			e_button  m_button;
			CCoords   m_coords;
			CVirtKeys m_v_keys;
		};

		virtual TError&  IMouse_Error (void) const = 0;
		virtual err_code IMouse_OnEvent (const CEvent&) {
			// __s_ok: handled; __s_false = not handled; otherwise the error code;
			return __s_false;
		}
	};

	class CMouseRouter : public IMsg_Handler, public CBaseHandler { typedef CBaseHandler TBase;
	public:
		CMouseRouter (void); ~CMouseRouter (void) = default;

		err_code IMsg_OnMessage (const uint32_t _u_code, const w_param, const l_param) override final;

		err_code Subscribe (const IMouse_Handler*);
		err_code Unsubscribe (const IMouse_Handler*);

		err_code operator <<(const IMouse_Handler*); // subscribes the given interface handler pointer;
		err_code operator >>(const IMouse_Handler*); // unsubscribes the given interface handler pointer;
	};

	interface IKbrd_Handler {

		virtual TError& IKbrd_Error (void) const = 0;
		// https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes ;
		enum class e_pref_keys : uint32_t {
			e_down  = VK_DOWN  , // arrow key : 'down' ;
			e_left  = VK_LEFT  , // arrow key : 'left' ;
			e_right = VK_RIGHT , // arrow key : 'right';
			e_up    = VK_UP    , // arrow key : 'up';
		};
		/* https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-keydown :
		   _v_key    : the virtual key code;
		   _b_repeat : indicates the long pressing the particular key;
		   _b_extend : the key being pressed is on the extended part of the keyboard;
		*/
		virtual err_code IKbrd_OnKeyDown (const uint32_t _v_key, const bool _b_repeat, const bool _b_extend) {
			_v_key; _b_repeat; _b_extend;
			// __s_ok: handled; __s_false = not handled; otherwise the error code;
			return __s_false;
		}

		static CString To_str (const uint32_t _v_key);
	};

	class CKbrdRouter : public IMsg_Handler, public CBaseHandler { typedef CBaseHandler TBase;
	public:
		CKbrdRouter (void); ~CKbrdRouter (void) = default;

		err_code IMsg_OnMessage (const uint32_t _u_code, const w_param, const l_param) override final;

		err_code Subscribe (const IKbrd_Handler*);
		err_code Unsubscribe (const IKbrd_Handler*);

		err_code operator <<(const IKbrd_Handler*); // subscribes the given interface handler pointer;
		err_code operator >>(const IKbrd_Handler*); // unsubscribes the given interface handler pointer;
	};
}}}

typedef ex_ui::popup::messages::CKbrdRouter TKbrdRouter; TKbrdRouter& Get_kbrd (void);
typedef ex_ui::popup::messages::CMsgRouter TMsgRouter; TMsgRouter& Get_router (void);
typedef ex_ui::popup::messages::CMouseRouter TMseRouter; TMseRouter& Get_mouse (void); 

#endif/*_SHARED_WND_MSG_H_INCLUDED*/