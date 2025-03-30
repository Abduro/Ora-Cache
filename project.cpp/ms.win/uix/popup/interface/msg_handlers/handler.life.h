#ifndef _HANDLER_LIFE_H_INCLUDED
#define _HANDLER_LIFE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Oct-2021 at 1:59:45.0122097 pm, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack UIX window life cycle message handler base interface declaration file.
*/
#include "handler.base.h"

namespace ex_ui { namespace message { namespace handlers { namespace life { // no additional namespace here intentionally; perhaps 'life_cycle' or 'window';

	using shared::sys_core::CError;

	// returns S_OK if message is handled, if not handled __s_false is returned, otherwise the error code;
	interface ILifeEvtSink {
		virtual err_code  IEvtLife_OnClose   (const w_param, const l_param) { // wparam is not used; lparam is not used either;
			err_code n_result = __s_false; return n_result;
		}
#define _block_creation (-1)
		virtual err_code  IEvtLife_OnCreate  (const w_param, const l_param) { // wparam is not used; lparam is a pointer to create window data;
			err_code n_result = __s_false; return n_result;                   // S_OK is handled; -1 is for not creation, otherwise the error code;
		}
		virtual err_code  IEvtLife_OnDestroy (const w_param, const l_param) { // wparam is not used; lparam is not used either;
			err_code n_result = __s_false; return n_result;
		}
	};

	typedef ::std::set<ILifeEvtSink*> TLifeEvtListeners;

	class CHandler : public CBase { typedef CBase TBase;
	protected:
		TLifeEvtListeners m_sinks;

	public:
		 CHandler (void);
		 CHandler (const CHandler&);
		 CHandler (CHandler&&);
		~CHandler (void);

	public:
		BEGIN_MSG_MAP(CHandler)
			MESSAGE_HANDLER (WM_CLOSE  , OnClose  ) // https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-close
			MESSAGE_HANDLER (WM_CREATE , OnCreate ) // https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-create
			MESSAGE_HANDLER (WM_DESTROY, OnDestroy) // https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-destroy
		END_MSG_MAP()

	protected:
		virtual l_result OnClose  (uint32_t, w_param, l_param, int32_t&);
		virtual l_result OnCreate (uint32_t, w_param, l_param, int32_t&);
		virtual l_result OnDestroy(uint32_t, w_param, l_param, int32_t&);

	public:
		err_code Arrogate (CHandler& _victim);
		err_code Subscribe (ILifeEvtSink*);
		err_code Unsubscribe (ILifeEvtSink*);

	public:
		CHandler& operator = (const CHandler&);
		CHandler& operator = (CHandler&&);
		CHandler& operator <<(ILifeEvtSink*);
		CHandler& operator >>(ILifeEvtSink*);
	};
}}}}


#endif/*_HANDLER_LIFE_H_INCLUDED*/