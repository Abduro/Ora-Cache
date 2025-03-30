#ifndef _HANDLER_DRAW_H_INCLUDED
#define _HANDLER_DRAW_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 5-Nov-2021 at 11:44:41.7510067 pm, UTC+7, Novosibirsk, Friday;
	This is Ebo Pack UIX window draw client area message handler base interface declaration file.
*/
#include "handler.base.h"

namespace ex_ui { namespace message { namespace handlers { namespace draw {

	using shared::sys_core::CError;
	using shared::sys_core::CSyncObject;

	interface IDrawEventSink {
		virtual err_code IEvtDraw_OnErase (const w_param _w_param, const l_param) { // S_FALSE is handled, S_OK is not handled, otherwise is error code;
			return   IEvtDraw_OnErase ((HDC)_w_param);
		}
		// https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-erasebkgnd ;
		virtual err_code IEvtDraw_OnErase (const HDC _dev_ctx) { _dev_ctx;
			err_code n_result = __s_ok; return n_result;
		}
		// https://learn.microsoft.com/en-us/windows/win32/gdi/wm-paint
		virtual err_code IEvtDraw_OnPaint (const w_param, const l_param) { // S_OK is handled, S_FALSE is not handled, otherwise is error code;
			err_code n_result = __s_ok; return n_result;
		}
	};

	typedef ::std::set<IDrawEventSink*> TDrawEvtListeners;

	class CHandler : public CBase { typedef CBase TBase;
	protected:
		TDrawEvtListeners m_sinks;

	public:
		 CHandler (void);
		 CHandler (const CHandler&);
		 CHandler (CHandler&&);
		~CHandler (void);

	public:
		BEGIN_MSG_MAP(CHandler)
			MESSAGE_HANDLER(WM_ERASEBKGND, OnErase) // https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-erasebkgnd ;
			MESSAGE_HANDLER(WM_PAINT     , OnPaint) // https://docs.microsoft.com/en-us/windows/win32/gdi/wm-paint ;
		END_MSG_MAP()

	protected:
		virtual l_result OnErase (uint32_t, w_param, l_param, int32_t&);
		virtual l_result OnPaint (uint32_t, w_param, l_param, int32_t&);

	public:
		err_code  Arrogate (CHandler& _victim);
		err_code  Subscribe (IDrawEventSink*);
		err_code  Unsubscribe (IDrawEventSink*);

	public:
		CHandler& operator = (const CHandler&);
		CHandler& operator = (CHandler&&);
		CHandler& operator <<(IDrawEventSink*);
		CHandler& operator >>(IDrawEventSink*);
	};

}}}}

#endif/*_HANDLER_DRAW_H_INCLUDED*/