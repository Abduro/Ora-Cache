#ifndef _HANDLER_FRAME_H_INCLUDED
#define _HANDLER_FRAME_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-Nov-2021 at 0:24:48.7407929 am, UTC+7, Novosibirsk, Wednesday;
	This is Ebo Pack UIX window frame message handler adapter base interface declaration file.
*/
#include "handler.base.h"

namespace ex_ui { namespace message { namespace handlers { namespace frame {

	using shared::sys_core::CError;
	/**important*: all methods of this interface returns:
		__s_ok in case of handling the window message,
		__s_false in case of *not* handling the window message,
		otherwise, error code;
		taking into account window messages return TRUE or 0, message handlers which defined below take care of returning appropriate LRESULT value;
	*/
	interface IFrameEventSink {
		// https://learn.microsoft.com/en-us/windows/win32/inputdev/wm-activate ;
		virtual err_code  IEvtFrame_OnActivate (const w_param, const l_param) { // wparam is an activation data; lparam is target window handle;
			err_code n_result = __s_false; return n_result;
		}
		// https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-windowposchanged ;
		virtual err_code  IEvtFrame_OnChanged (const w_param, const l_param _l_param) { // wparam is not used; lparam is a pointer to position data;
			WINDOWPOS* p_pos_ = nullptr;
			if (_l_param) {
				p_pos_ = reinterpret_cast<WINDOWPOS*>(_l_param);
				if (p_pos_)
					return IEvtFrame_OnChanged(*p_pos_);
			}
			return __s_false;
		}
		virtual err_code  IEvtFrame_OnChanged(const WINDOWPOS& _pos) { _pos;
			err_code n_result = __s_false; return n_result;
		}

		// https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-windowposchanging ;
		virtual err_code  IEvtFrame_OnChanging(const w_param, const l_param _l_param) { // wparam is not used; lparam is a pointer to position data;
			WINDOWPOS* p_pos_ = nullptr;
			if (_l_param) {
				p_pos_ = reinterpret_cast<WINDOWPOS*>(_l_param);
				if (p_pos_)
					return IEvtFrame_OnChanging(*p_pos_);
			}
			return __s_false;
		}
		virtual err_code  IEvtFrame_OnChanging(const WINDOWPOS& _pos) { _pos;
			err_code n_result = __s_false; return n_result;
		}
		// https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-enable ;
		virtual err_code  IEvtFrame_OnEnable (const w_param, const l_param) { // wparam is enable/disable value; lparam is not used;
			err_code n_result = __s_false; return n_result;
		}
		// https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-move ;
		// wparam is not used; lparam coordinates of the left-top corner of the client area;
		virtual err_code  IEvtFrame_OnMove (const w_param, const l_param _l_param) {
			return IEvtFrame_OnMove (point_t{LOWORD(_l_param), HIWORD(_l_param)});
		}

		virtual err_code  IEvtFrame_OnMove (const point_t& _top_left_client_area) {
			_top_left_client_area;
			err_code n_result = __s_false; return n_result;
		}

		// https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-moving ;
		// wparam is not used; l_param is a pointer to a RECT structure with the current position of the window, in screen coordinates ;
		virtual err_code  IEvtFrame_OnMoving (const w_param, const l_param _l_param) {
			LPRECT p_rect = nullptr;
			if (_l_param) {
				p_rect = reinterpret_cast<LPRECT>(_l_param);
				if (p_rect)
					return IEvtFrame_OnMoving(*p_rect);
			}
			return __s_ok;
		}

		virtual err_code  IEvtFrame_OnMoving (const rect_t& _p_wnd_coords) {
			_p_wnd_coords; 
			err_code n_result = __s_ok; return n_result;
		}

		enum eState : uint32_t {
			eMaximized = SIZE_MAXIMIZED, // a window has been maximized ;
			eMinimized = SIZE_MINIMIZED, // a window has been minimized ;
			eRestored  = SIZE_RESTORED , // a window has been resized ; looks like as a default value;
		};
		// https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-size ;
		virtual err_code  IEvtFrame_OnSize (const w_param _w_param, const l_param _l_param) { // wparam is a size mode; lparam is a size of client area;
			return IEvtFrame_OnSize((const eState)_w_param, SIZE{LOWORD(_l_param), HIWORD(_l_param)});
		}
		virtual err_code  IEvtFrame_OnSize (const eState _state, const SIZE _client) { _state; _client;
			err_code n_result = __s_false; return n_result;
		}

		enum eEdges : uint32_t {
			eBottom      = WMSZ_BOTTOM     , // bottom edge ;
			eBottomLeft  = WMSZ_BOTTOMLEFT , // bottom-left corner ;
			eBottomRight = WMSZ_BOTTOMRIGHT, // bottom-right corner;
			eLeft        = WMSZ_LEFT       , // left edge ;
			eRight       = WMSZ_RIGHT      , // right edge;
			eTop         = WMSZ_TOP        , // top edge  ;
			eTopLeft     = WMSZ_TOPLEFT    , // top-left corner ;
			eTopRight    = WMSZ_TOPRIGHT   , // top-right corner;
			eUndefined   = 0,
		};

		// https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-sizing ;
		virtual err_code  IEvtFrame_OnSizing (const w_param _w_param, const l_param _l_param) { // wparam is a size mode; lparam is window rectangle in screen coords;
			LPRECT p_rect = nullptr;
			if (_l_param) {
				p_rect = reinterpret_cast<LPRECT>(_l_param);
				if (p_rect)
					return IEvtFrame_OnSizing((const eEdges)_w_param, p_rect);
			}
			return __s_false;
		}
		virtual err_code  IEvtFrame_OnSizing (const eEdges, LPRECT _p_rect) { _p_rect;
			err_code n_result = __s_false; return n_result;
		}
		// https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-getminmaxinfo ;
		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-minmaxinfo ;
		virtual err_code  IEvtFrame_OnSizeInfo (const w_param, const l_param _l_param) {
			MINMAXINFO* p_info = nullptr;
			if (_l_param) {
				p_info = reinterpret_cast<MINMAXINFO*>(_l_param);
				if (p_info)
					return IEvtFrame_OnSizeInfo(*p_info);
			}
			return __s_false;
		}
		virtual err_code  IEvtFrame_OnSizeInfo (MINMAXINFO& _info) { _info;
			return __s_false;
		}
	};

	typedef ::std::set<IFrameEventSink*> TFrameEvtListeners;

	// https://wikidiff.com/frame/form
	class CHandler : public CBase { typedef CBase TBase;
	protected:
		TFrameEvtListeners m_sinks;

	public:
		 CHandler (void);
		 CHandler (const CHandler&);
		 CHandler (CHandler&&);
		~CHandler (void);

		#define WM_SIZEINFO WM_GETMINMAXINFO
		#define WM_CHANGED  WM_WINDOWPOSCHANGED
		#define WM_CHANGING WM_WINDOWPOSCHANGING

	public:
		BEGIN_MSG_MAP(CHandler)
			MESSAGE_HANDLER (WM_ACTIVATE , OnActivate ) // https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-activate       ;
			MESSAGE_HANDLER (WM_CHANGED  , OnChanged  ) // https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-windowposchanged ;
			MESSAGE_HANDLER (WM_CHANGING , OnChanging ) // https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-windowposchanging;
			MESSAGE_HANDLER (WM_ENABLE   , OnEnable   ) // https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-enable           ;
			MESSAGE_HANDLER (WM_MOVE     , OnMove     ) // https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-move             ;
			MESSAGE_HANDLER (WM_MOVING   , OnMoving   ) // https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-moving          ;
			MESSAGE_HANDLER (WM_SIZE     , OnSize     ) // https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-size             ;
			MESSAGE_HANDLER (WM_SIZEINFO , OnSizeInfo ) // https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-getminmaxinfo   ;
			MESSAGE_HANDLER (WM_SIZING   , OnSizing   ) // https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-sizing          ;
		END_MSG_MAP()

	protected:                                                              // the excerpts from documentation which URLs are pointed out above:
		virtual l_result OnActivate (uint32_t, w_param, l_param, int32_t&); // If an application processes this message, it should return zero.
		virtual l_result OnChanged  (uint32_t, w_param, l_param, int32_t&); // If an application processes this message, it should return zero.
		virtual l_result OnChanging (uint32_t, w_param, l_param, int32_t&); // If an application processes this message, it should return zero.
		virtual l_result OnEnable   (uint32_t, w_param, l_param, int32_t&); // If an application processes this message, it should return zero.
		virtual l_result OnMove     (uint32_t, w_param, l_param, int32_t&); // If an application processes this message, it should return zero.
		virtual l_result OnMoving   (uint32_t, w_param, l_param, int32_t&); // An application should return TRUE if it processes this message.
		virtual l_result OnSize     (uint32_t, w_param, l_param, int32_t&); // If an application processes this message, it should return zero.
		virtual l_result OnSizeInfo (uint32_t, w_param, l_param, int32_t&); // If an application processes this message, it should return zero.
		virtual l_result OnSizing   (uint32_t, w_param, l_param, int32_t&); // An application should return TRUE if it processes this message.

	public:
		err_code   Arrogate(CHandler& _victim);
		err_code   Subscribe(IFrameEventSink*);
		err_code   Unsubscribe(IFrameEventSink*);

	public:
		CHandler& operator = (const CHandler&);
		CHandler& operator = (CHandler&&);
		CHandler& operator <<(IFrameEventSink*);
		CHandler& operator >>(IFrameEventSink*);
	};
}}}}

#endif/*_HANDLER_FRAME_H_INCLUDED*/