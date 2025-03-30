#ifndef _HANDLER_MOUSE_TRACK_H_INCLUDED
#define _HANDLER_MOUSE_TRACK_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Oct-2024 at 15:09:34.268, UTC+4, Batumi, Monday;
	This is Ebo Pack shared mouse movement track interface declaration file;
*/
#include "handler.base.h"

namespace ex_ui { namespace message { namespace handlers { namespace mouse {

	using CError = shared::sys_core::CError;
	using TError = const CError;

	interface ITrackEventSink {
		
		// this message handler is called in cases when mouse tracking is turned on, otherwise, mouse move message handler proceeds its work;
		virtual err_code  IEvtMouse_OnEnter(const w_param _w_param, const l_param _l_param) { // wparam is for virtual key; lparam is for mouse point in client area;
			return IEvtMouse_OnEnter (static_cast<uint32_t>(_w_param), POINT{GET_X_LPARAM(_l_param), GET_Y_LPARAM(_l_param)});
		}
		virtual err_code  IEvtMouse_OnEnter(const uint32_t _buttons_n_keys , const POINT _pt_cursor) {
			_buttons_n_keys; _pt_cursor;
			err_code n_result = __s_false; return n_result;
		}

		// https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-mousehover#parameters ;
		virtual err_code  IEvtMouse_OnHover(const w_param _w_param , const l_param _l_param) { // wparam is for virtual key; lparam is for mouse point in client area;
			return IEvtMouse_OnHover(static_cast<uint32_t>(_w_param), POINT{GET_X_LPARAM(_l_param), GET_Y_LPARAM(_l_param)});
		}
		virtual err_code  IEvtMouse_OnHover(const uint32_t _buttons_n_keys , const POINT _pt_cursor) {
			_buttons_n_keys; _pt_cursor;
			err_code n_result = __s_false; return n_result;
		}
		// https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-mousemove ;
		virtual err_code  IEvtMouse_OnMove (const w_param _w_param , const l_param _l_param) { // wparam is for virtual key; lparam is for mouse point in client area;
			return IEvtMouse_OnMove (static_cast<uint32_t>(_w_param), POINT{GET_X_LPARAM(_l_param), GET_Y_LPARAM(_l_param)});
		}
		virtual err_code  IEvtMouse_OnMove (const uint32_t _buttons_n_keys , const POINT _pt_cursor) {
			_buttons_n_keys; _pt_cursor;
			err_code n_result = __s_false; return n_result;
		}
		// https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-mouseleave ;
		virtual err_code  IEvtMouse_OnLeave(const w_param, const l_param) { // wparam is not used; lparam is not used either;
			return IEvtMouse_OnLeave();
		}
		virtual err_code  IEvtMouse_OnLeave(void) {
			err_code n_result = __s_false; return n_result;
		}
		// https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-mousehwheel ;
		// wparam is for virtual key and wheel delta; lparam is for mouse point in client area;
		virtual err_code  IEvtMouse_OnWheel(const w_param _w_param, const l_param _l_param) {
			const uint32_t dw_keys = GET_KEYSTATE_WPARAM(_w_param);
			const SHORT s_delta = GET_WHEEL_DELTA_WPARAM(_w_param); // if less than 0, then it is equivalent to VK_UP, otherwise to VK_DOWN;
			return IEvtMouse_OnWheel(dw_keys, s_delta, POINT{GET_X_LPARAM(_l_param), GET_Y_LPARAM(_l_param)});
		}
		virtual err_code  IEvtMouse_OnWheel(const uint32_t _keys, const SHORT _delta, const POINT _pt_cursor) {
			_keys; _delta; _pt_cursor;
			err_code n_result = __s_false; return n_result;
		}
	};

	typedef ::std::set<ITrackEventSink*> TTrackEvtListeners;

	class CTrackHandler : public CBase { typedef CBase TBase;
	private:
		TTrackEvtListeners  m_sinks;
		TRACKMOUSEEVENT     m_track_data;
		bool m_bTracked ;
		bool m_bTurnedOn;

	public:
		 CTrackHandler (void);
		 CTrackHandler (const CTrackHandler&);
		 CTrackHandler (CTrackHandler&&);
		~CTrackHandler (void);

	public:
		BEGIN_MSG_MAP(CTrackHandler)
			MESSAGE_HANDLER (WM_MOUSEHOVER   , OnMouseHover) // https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-mousehover ;
			MESSAGE_HANDLER (WM_MOUSEMOVE    , OnMouseMove ) // https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-mousemove  ;
			MESSAGE_HANDLER (WM_MOUSELEAVE   , OnMouseOut  ) // https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-mouseleave ;
			MESSAGE_HANDLER (WM_MOUSEHWHEEL  , OnMouseWheel) // https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-mousehwheel;
		END_MSG_MAP()

	protected:
		virtual l_result OnMouseHover(uint32_t, w_param, l_param, int32_t&);
		virtual l_result OnMouseMove (uint32_t, w_param, l_param, int32_t&);
		virtual l_result OnMouseOut  (uint32_t, w_param, l_param, int32_t&);
		virtual l_result OnMouseWheel(uint32_t, w_param, l_param, int32_t&);

	public:
		HWND      Target   (void) const;                     // returns a handle of window for which track mouse operation is turned on/off;
		err_code  Target   (CONST HWND);                     // sets a target window handle, if track operation is turned on, it will be stopped;
		bool      IsTurned (void) const;
		err_code  IsTurned (const bool _b_on_off );

	public:
		err_code  Arrogate (CTrackHandler& _victim);
		err_code  Subscribe (ITrackEventSink*);
		err_code  Unsubscribe (ITrackEventSink*);

	public:
		 CTrackHandler& operator = (const CTrackHandler&);
		 CTrackHandler& operator = (CTrackHandler&&);
		 CTrackHandler& operator <<(ITrackEventSink*);
		 CTrackHandler& operator >>(ITrackEventSink*);
	};

}}}}

#endif/*_HANDLER_MOUSE_TRACK_H_INCLUDED*/