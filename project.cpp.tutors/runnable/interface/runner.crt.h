#ifndef _RUNNER_CRT_H_INCLUDED
#define _RUNNER_CRT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 1-May-2012 at 11:18:24am, GMT+3, Rostov-on-Don, Tuesday;
	This is Pulsepay Server Application Runnable Object class delaration file.
	-----------------------------------------------------------------------------
	Adopted to Platinum Clocking project on 19-Mar-2014 at 11:21:09am, GMT+3, Taganrog, Wednesday;
	Adopted to E-Opinion project on 8-May-2014 at 7:28:02am, GMT+3, Saint-Petersburg, Thursday;
	Adopted to Ebo Pack on 9-Jul-2018 at 5:54:17p, UTC+7, Phuket, Rawai, Monday;
	Adopted to Fake GPS project on 23-Apr-2020 at 10:53:51p, UTC+7, Novosibirsk, Thursday;
*/
#include "run.event.h"

namespace shared { namespace runnable
{
	typedef unsigned int (__stdcall *TRunnableFunc)(void*); // __stdcall is required by _beginthreadex();

	class CRunPriority {
	public:
		enum e_level : uint32_t { // https://learn.microsoft.com/en-us/windows/win32/procthread/scheduling-priorities ;
		/* alias    | element value                     | brief description ;
		------------+-----------------------------------+-------------------*/
		    eLow    = 0, // BELOW_NORMAL_PRIORITY_CLASS | background threads, particularly those that are processor intensive;
		    eNormal = 1, // NORMAL_PRIORITY_CLASS       | (default) the thread priority is the same as the process priority class;
		    eHigh   = 2, // ABOVE_NORMAL_PRIORITY_CLASS | a thread runs at the highest priority level for extended periods;
		};
	};
	/* https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/beginthread-beginthreadex
	   this is a wrapper of _beginthreadex function that is reliable enough, at the same time it is dependable on vc-runtime;
	   it can be linked statically to an executable file, but all circumstances must be checked: it is possible some dynamic link(s) still remain;
	*/
	class CCrtRunner {
	public:
		CCrtRunner (TRunnableFunc, IEventNotify&, const _variant_t& v_evt_id);
		CCrtRunner (void) = delete; CCrtRunner (const CCrtRunner&) = delete; CCrtRunner (CCrtRunner&&) = delete;
		virtual ~CCrtRunner(void);

	public:
		TError& Error (void) const;
		const
		CEvent& Event (void) const; // gets the reference to the event object that is used for waiting in worker thread; (ro)
		CEvent& Event (void) ;      // gets the reference to the event object that is used for waiting in worker thread; (rw)
		
		virtual bool         IsRunning (void) const; // checks: (1) worker thread handle is created and (2) the thread is running;
		virtual bool         IsStopped (void) const; // manages the working thread: in case of set to 'true' the thread stops its work;
		virtual void         MarkCompleted (void);   // is set from working thread for reporting its job is done;
		virtual CMarshaller& Notifier (void);

		virtual err_code     Start (const CRunPriority::e_level = CRunPriority::eLow); // calls _beginthreadex();
		virtual err_code     Stop  (const bool bForced); // calls _endthreadex();

	private:
		CCrtRunner& operator = (const CCrtRunner&) = delete; CCrtRunner& operator = (CCrtRunner&&) = delete;
		mutable CError        m_error;
		CMarshaller           m_notifier ;  // for sending notifications from worker thread to main one;
		void*                 m_hThread  ;  // thread handle that runs a procedure;
	/*	volatile */ CEvent    m_event    ;  // synch primitive;
		volatile mutable bool m_bStopped ;  // this flag is set from worker thread owner and is read from worker thread procedure;
		TRunnableFunc         m_function ;  // worker thread procedure pointer that is applied to _beginthreadex();
	};
}}

typedef shared::runnable::CRunPriority::e_level TRunPriority;

#endif/*_RUNNER_CRT_H_INCLUDED*/