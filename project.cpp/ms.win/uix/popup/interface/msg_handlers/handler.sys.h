#ifndef _HANDLER_SYS_H_INCLUDED
#define _HANDLER_SYS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-Nov-2021 at 8:57:59.4498537 am, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack UIX window system message handler adapter base interface declaration file.
*/
#include "handler.base.h"

namespace ex_ui { namespace message { namespace handlers {

	using shared::sys_core::CError;

	// returns S_OK if message is handled, if not handled __s_false is returned, otherwise the error code;
	interface IMsgSysEventSink {

		enum eSysCmd : uint32_t {    // https://learn.microsoft.com/en-us/windows/win32/menurc/wm-syscommand ;
			eClose    = SC_CLOSE   , // closes a window ;
			eMaximize = SC_MAXIMIZE, // maximizes a window ;
			eMinimize = SC_MINIMIZE, // minimizes a window ;
		};

		virtual err_code  IEvtSys_OnSetting(const w_param, const l_param) { // wparam is an action, lparam is a pointer to structure of data being set/get;
			err_code n_result = __s_false; return n_result;
		}
		virtual err_code  IEvtSys_OnSysCmd (const w_param, const l_param) { // wparam is a command, lparam is cursor position;
			err_code n_result = __s_false; return n_result;
		}
		virtual err_code  IEvtSys_OnThemed (const w_param, const l_param) { // wparam is resered, lparam is reserved too;
			err_code n_result = __s_false; return n_result;
		}
	};

	typedef ::std::set<IMsgSysEventSink*> TMsgSysListeners;

	class CMsgSystem : public CBase { typedef CBase TBase;
	protected:
		TMsgSysListeners m_sinks;

	public:
		 CMsgSystem (void);
		 CMsgSystem (const CMsgSystem&);
		 CMsgSystem (CMsgSystem&&);
		~CMsgSystem (void);

	public:
		BEGIN_MSG_MAP(CMsgSystem)
			MESSAGE_HANDLER(WM_SETTINGCHANGE,  OnSetting) // https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-settingchange ;
			MESSAGE_HANDLER(WM_SYSCOMMAND   ,  OnSysCmd ) // https://docs.microsoft.com/en-us/windows/win32/menurc/wm-syscommand    ;
			MESSAGE_HANDLER(WM_THEMECHANGED ,  OnThemed ) // https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-themechanged  ;
		END_MSG_MAP()

	protected:
		virtual l_result OnSetting(uint32_t, w_param, l_param, int32_t&);
		virtual l_result OnSysCmd (uint32_t, w_param, l_param, int32_t&);
		virtual l_result OnThemed (uint32_t, w_param, l_param, int32_t&);

	public:
		err_code   Arrogate (CMsgSystem& _victim);
		err_code   Subscribe (IMsgSysEventSink*);
		err_code   Unsubscribe (IMsgSysEventSink*);

	public:
		CMsgSystem& operator = (const CMsgSystem&);
		CMsgSystem& operator = (CMsgSystem&&);
		CMsgSystem& operator <<(IMsgSysEventSink*);
		CMsgSystem& operator >>(IMsgSysEventSink*);
	};

}}}
#endif/*_HANDLER_SYS_H_INCLUDED*/