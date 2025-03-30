#ifndef _HANDLER_CLIENT_H_INCLUDED
#define _HANDLER_CLIENT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Nov-2021 at 0:22:30.8506632 am, UTC+7, Novosibirsk, Friday;
	This is Ebo Pack UIX window client area message handler adapter base interface declaration file.
*/
#include "handler.base.h"

namespace ex_ui { namespace message { namespace handlers { namespace cl_area { // 'cl' is maybe not good abbreviation for 'client area';
	// https://forum.wordreference.com/threads/field-vs-area.415739/ ;
	// https://wikidiff.com/area/field ;

	// returns S_OK if message is handled, if not handled S_FALSE is returned, otherwise the error code;
	interface IEventSink {
		virtual err_code IEvt_OnCtxMenu (const w_param, const l_param) { // lparam a handle of a window; lparam is a cursor position;
			err_code n_result = __s_false; return n_result;
		}
		virtual err_code IEvt_OnHScroll (const w_param, const l_param) { // lparam a scroll bar info; wparam is scroll bar window handle;
			err_code n_result = __s_false; return n_result;
		}
		virtual err_code IEvt_OnVScroll (const w_param, const l_param) { // lparam a scroll bar info; wparam is scroll bar window handle;
			err_code n_result = __s_false; return n_result;
		}
	};

	typedef ::std::set<IEventSink*> TMsgListeners;

	class CHandler : public CBase { typedef CBase TBase; // this typedef looks like useless;
	protected:
		TMsgListeners m_sinks;

	public:
		 CHandler (void);
		 CHandler (const CHandler&);
		 CHandler (CHandler&&);
		~CHandler (void);

	public:
		BEGIN_MSG_MAP(CHandler)
			MESSAGE_HANDLER (WM_CONTEXTMENU , OnCtxMenu  ) // https://docs.microsoft.com/en-us/windows/win32/menurc/wm-contextmenu ;
			MESSAGE_HANDLER (WM_HSCROLL     , OnHScroll  ) // https://docs.microsoft.com/en-us/windows/win32/controls/wm-hscroll   ;
			MESSAGE_HANDLER (WM_VSCROLL     , OnVScroll  ) // https://docs.microsoft.com/en-us/windows/win32/controls/wm-vscroll   ;
		END_MSG_MAP()

	protected:
		virtual l_result OnCtxMenu (uint32_t, w_param, l_param, int32_t&);
		virtual l_result OnHScroll (uint32_t, w_param, l_param, int32_t&);
		virtual l_result OnVScroll (uint32_t, w_param, l_param, int32_t&);

	public:
		err_code   Arrogate(CHandler& _victim);
		err_code   Subscribe(IEventSink*);
		err_code   Unsubscribe(IEventSink*);

	public:
		CHandler& operator = (const CHandler&);
		CHandler& operator = (CHandler&&);
		CHandler& operator <<(IEventSink*);
		CHandler& operator >>(IEventSink*);
	};

}}}}

#endif/*_HANDLER_CLIENT_H_INCLUDED*/