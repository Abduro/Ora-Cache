#ifndef _SHARED_TIMER_H_INCLUDED
#define _SHARED_TIMER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 3-Jan-2019 at 11:49:24p, UTC+7, Novosibirsk, Thursday;
	This is Ebo Pack shared lite library waitable timer interface declaration file.
	-----------------------------------------------------------------------------
	Original file is created for SfxSOA common timer object on 8-Dec-2010 at 1:49:00am, GMT+3, Rostov-on-Don, Wednesday;
*/
#include "shared.types.h"

namespace shared { namespace common {

	using namespace shared::types;

	interface IWaitable_Events {
		virtual void  IWaitable_OnComplete(void) = 0;
	};

	class CTimer_Base {
	protected:
	    CTimer_Base (IWaitable_Events&);
		CTimer_Base (void) = delete; CTimer_Base (const CTimer_Base&) = delete; CTimer_Base (CTimer_Base&&) = delete;
	   ~CTimer_Base (void);

	public:
		virtual bool  IsValid(void) const = 0; // ToDo: the pure virtuality is not necessary; the kid classes may simply override it;

	protected:
		CTimer_Base&  operator = (const CTimer_Base&) = delete; CTimer_Base& operator = (CTimer_Base&&) = delete;

	protected:
		IWaitable_Events& m_sink;
	};
	// https://learn.microsoft.com/en-us/windows/win32/sync/using-waitable-timer-objects ;
	// waitable timer creates a delay in the same thread as a caller runs in;
	// windows messages are kept for processing, i.e. message loop is created;
	//
	class CWaitableTimer : public CTimer_Base {
	                      typedef CTimer_Base TTimer;
	public:
	    CWaitableTimer (IWaitable_Events&);
		CWaitableTimer (void) = delete; CWaitableTimer (const CWaitableTimer&) = delete; CWaitableTimer (CWaitableTimer&&) = delete;
	   ~CWaitableTimer (void);

	public:
		virtual bool  IsValid(void) const override; // valid for cases when timer handle is not null;

	public:
		err_code Delay  (const UINT _u_ms);         // sets timer delay in miliseconds;
		err_code Destroy(void);                     // closes a timer handle;
	protected:
		HANDLE m_timer;
	private:
		CWaitableTimer& operator = (const CWaitableTimer&) = delete; CWaitableTimer& operator = (CWaitableTimer&&) = delete;
	};
	// https://learn.microsoft.com/en-us/windows/win32/winmsg/using-timers ;
	// standard timer is a timer that uses static timer procedure instead of handling WM_TIMER message by a window;
	// the procedure keeps timer identifier and callback pairs for multiple use of this class object;
	//
	class CStdTimer : public CTimer_Base {
	                 typedef CTimer_Base TTimer;
	public:
	    CStdTimer (IWaitable_Events&); CStdTimer (void) = delete; CStdTimer (const CStdTimer&) = delete; CStdTimer (CStdTimer&&) = delete;
	   ~CStdTimer (void);

	public:
		virtual bool IsValid(void) const override;

	public:
		err_code   Create (const UINT _u_ms); // time-out in milliseconds;
		err_code   Destroy(void);

	protected:
		UINT_PTR   m_tm_id; // timer identifier;

	private:
		CStdTimer& operator = (const CStdTimer&) = delete; CStdTimer& operator = (CStdTimer&&) = delete;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setcoalescabletimer ; just for info;

}}

#endif/*_SHARED_TIMER_H_INCLUDED*/