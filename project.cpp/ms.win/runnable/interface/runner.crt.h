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
	typedef unsigned int (__stdcall *TRunnableFunc)(void*);

	class CRunPriority {
	public:
		enum _e {
			eLow    = 0, // default;
			eNormal = 1,
			eHigh   = 2
		};
	};
	//
	// https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/beginthread-beginthreadex
	// this is a wrapper of _beginthreadex function that is reliable enough, at the same time it is dependable on vc-runtime;
	// it can be linked statically to an executable file, but all circumstances must be checked: it is possible some dynamic link(s) still remain;
	//
	class CCrtRunner
	{
	private:
		CMarshaller              m_async_evt;
		HANDLE                   m_hThread  ;             // thread handle that runs a procedure;
		volatile HANDLE          m_hEvent   ;             // synch primitive;
		volatile mutable bool    m_bStopped ;
		TRunnableFunc            m_function ;
	protected:
		CCrtRunner (TRunnableFunc, IGenericEventNotify&, const _variant_t& v_evt_id);
		virtual ~CCrtRunner(void);
	public:
		virtual CMarshaller&     Event    (void)      ;
		virtual bool             IsRunning(void) const;
		virtual bool             IsStopped(void) const;
		virtual void             MarkCompleted  (void);
		virtual HRESULT          Start(const CRunPriority::_e = CRunPriority::eLow);
		virtual HRESULT          Stop (const bool bForced);
		virtual HRESULT          Wait (const DWORD = 0);
	public:
		HANDLE                   EventHandle(void)const;
	private:
		CCrtRunner(const CCrtRunner&);
		CCrtRunner& operator= (const CCrtRunner&);
	};
}}

typedef shared::runnable::CRunPriority::_e  TRunPriority;

#endif/*_RUNNER_CRT_H_INCLUDED*/