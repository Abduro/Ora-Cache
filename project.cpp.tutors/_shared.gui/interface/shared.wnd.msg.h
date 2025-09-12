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

}}

typedef ex_ui::popup::CMsgRouter TRouter;

TRouter& Get_router (void);

#endif/*_SHARED_WND_MSG_H_INCLUDED*/