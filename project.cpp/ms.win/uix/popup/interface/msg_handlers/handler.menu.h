#ifndef _HANDLER_MENU_H_INCLUDED
#define _HANDLER_MENU_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Oct-2024 at 23:56:48.387, UTC+4, Batumi, Sunday;
	This is Ebo Pack shared menu message handler interface declaration file;
*/
#include "handler.base.h"

namespace ex_ui { namespace message { namespace handlers { namespace menu { // window manu bar and menu itself is controlled by the system, thus frame is used;

	// returns __s_ok if message is handled, if not handled __s_false is returned, otherwise the error code;
	interface IMenuEventSink {

		// https://learn.microsoft.com/en-us/windows/win32/menurc/wm-initmenu ;
		virtual err_code  IEvtMenu_OnInit(const w_param _w_menu, const l_param) { // w_param is a menu handle being initialized; l_param is not used;
			err_code n_result = __s_false;
			if (_w_menu) {
				return IEvtMenu_OnInit(reinterpret_cast<HMENU>(_w_menu));
			}
			return n_result;
		}

		virtual err_code  IEvtMenu_OnInit(const HMENU _h_menu) {
			_h_menu;
			err_code n_result = __s_false;
			return n_result;
		}

		// https://learn.microsoft.com/en-us/windows/win32/menurc/wm-initmenupopup ;
		virtual err_code  IEvtMenu_OnPopup(const w_param _w_menu, const l_param _n_data) { // wparam is menu handle, lparam is menu position and is window menu or not;
			err_code n_result = __s_false;
			if (_w_menu) {
				HMENU h_menu = reinterpret_cast<HMENU>(_w_menu);
				return IEvtMenu_OnPopup(h_menu, LOWORD(_n_data), !!HIWORD(_n_data));
			}
			else
				return n_result;
		}

		virtual err_code  IEvtMenu_OnPopup(const HMENU _h_menu, const uint32_t _n_index, const bool _b_wnd_menu) {
			_h_menu; _n_index; _b_wnd_menu;
			err_code n_result = __s_false; return n_result;
		}
	};

	typedef ::std::set<IMenuEventSink*> TMenuEvtListeners;

#define WM_MENUPOPUP WM_INITMENUPOPUP

	class CHandler : public CBase { typedef CBase TBase;
	protected:
		TMenuEvtListeners  m_sinks;

	public:
		 CHandler (void);
		 CHandler (const CHandler&);
		 CHandler (CHandler&&);
		~CHandler (void);

	public:
		BEGIN_MSG_MAP(CHandler)
			MESSAGE_HANDLER (WM_INITMENU  , OnInit  ) // https://learn.microsoft.com/en-us/windows/win32/menurc/wm-initmenu ;
			MESSAGE_HANDLER (WM_MENUPOPUP , OnPopup ) // https://learn.microsoft.com/en-us/windows/win32/menurc/wm-initmenupopup ;
		END_MSG_MAP()

	protected:
		virtual l_result OnInit  (uint32_t, w_param, l_param, int32_t&);
		virtual l_result OnPopup (uint32_t, w_param, l_param, int32_t&);

	public:
		err_code   Arrogate (CHandler& _victim);
		err_code   Subscribe (IMenuEventSink*);
		err_code   Unsubscribe (IMenuEventSink*);

	public:
		 CHandler& operator = (const CHandler&);
		 CHandler& operator = (CHandler&&);
		 CHandler& operator <<(IMenuEventSink*);
		 CHandler& operator >>(IMenuEventSink*);
	};

}}}}

#endif/*_HANDLER_MENU_H_INCLUDED*/