#ifndef _SHARED_WND_MSG_H_INCLUDED
#define _SHARED_WND_MSG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Sep-2025 at 01:12:31.835, UTC+4, Batumi, Friday;
	This is Ebo Pack shared window message handler interface declaration file;
*/
#include "shared.defs.h"

namespace ex_ui { namespace popup {

	using namespace shared::defs;

	// yes, that's right, it is possibly not the place for window message handler, but it is acceptable for the time being;

	interface IMsg_Handler {
		static const err_code _n_not_handled = -1;
		virtual err_code IMsg_OnMessage (const uint32_t _u_code, const w_param, const l_param) { // possibly, 'const' to w_param/l_param must be removed;
			_u_code;                // message code, e.g. WM_CREATE;
			return _n_not_handled;  // __s_ok|__s_false - depending on the message code, otherwise the error code; 
		}
	};

	// https://learn.microsoft.com/en-us/windows/win32/learnwin32/writing-the-window-procedure#avoiding-bottlenecks-in-your-window-procedure ;
	class CMsgRouter {
	public:
		CMsgRouter (void); ~CMsgRouter (void) = default;

	public:
		bool ApplyTo (WNDCLASSEX&); // sets the pointer to address of the internal message handler/window procedure; returns 'true' in case of data changed;
		TError& Error (void) const;

		err_code Subscribe (const HWND, IMsg_Handler&);
		err_code Unsubscribe (const HWND);

	private:
		CError m_error;

		CMsgRouter (const CMsgRouter&) = delete; CMsgRouter (CMsgRouter&&) = delete;
		CMsgRouter& operator = (const CMsgRouter&) = delete; CMsgRouter& operator = (CMsgRouter&&) = delete;

		friend CMsgRouter& Get_router(void); // it is not necessary for the current implementation of this class;
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

	class CKbrdRouter : public IMsg_Handler {
	public:
		CKbrdRouter (void); ~CKbrdRouter (void) = default;

		err_code IMsg_OnMessage (const uint32_t _u_code, const w_param, const l_param) override final;

		TError& Error (void) const;

		err_code Subscribe (const IKbrd_Handler*);
		err_code Unsubscribe (const IKbrd_Handler*);

	private:
		CError m_error;

		CKbrdRouter (const CKbrdRouter&) = delete; CKbrdRouter (CKbrdRouter&&) = delete;
		CKbrdRouter& operator = (const CKbrdRouter&) = delete;  CKbrdRouter& operator = (CKbrdRouter&&) = delete;
	};
}}

typedef ex_ui::popup::CKbrdRouter TKbrdRouter; TKbrdRouter& Get_kbrd (void);
typedef ex_ui::popup::CMsgRouter TMsgRouter; TMsgRouter& Get_router (void);

#endif/*_SHARED_WND_MSG_H_INCLUDED*/