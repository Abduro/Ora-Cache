#ifndef _RUNNER_BAS_H_INCLUDED
#define _RUNNER_BAS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Apr-2026 at 10:40:24.405, UTC+4, Batumi, Thursday;
	This is Ebo Pack runnable library thread wrapper shared interface declaration file;
*/
#include "run.event.h"

namespace shared { namespace runnable { namespace threads { using namespace shared::runnable;

	// https://learn.microsoft.com/en-us/previous-versions/windows/desktop/legacy/ms686736(v=vs.85) << definition of thread callback (legacy but still valid);
	typedef unsigned long (__stdcall *pfn_Run_with_data)(void*);   // functiom with ptr to input data;
	typedef unsigned long (__stdcall *pfn_Runnable_void)(void );   // function with no parameter;

	/*important: the error of thread state can be set only the following cases:
	(1) the system function that starts a thread throws an error; e.g. _beginthreadex();
	(2) the system functiom that stops a thread throws an error; e.g. _endthreadex();
	all other errors must be held by thread wrapper class itself;
	*/
	class CState {
	public:
		 enum e_state : uint32_t {
		 /* element of enum    | functions responsible for status change 
		 ----------------------+---------------------------------------*/
			 eStopped   = 0x0, // *runner::Stop();
			 eError     = 0x2, // *runner::Stop()/Start();
			 eWorking   = 0x4, // *runner::Start();
		 };
		 CState (void); CState (const CState&); CState (CState&&) = delete;
		~CState (void);

		TError&  Error (void) const;
		const
		CEvent&  Event (void) const;    // gets the reference to the event object that is used for waiting in worker thread; (ro)
		CEvent&  Event (void);		    // gets the reference to the event object that is used for waiting in worker thread; (rw)

		e_state  Get (void) const;      // returns currently set state value;
		bool     Set (const e_state);   // returns 'true' in case of state value change; this is direct set of the value;

		bool Is_error     (void) ;      // returns result in accordance with current state of the error object;
		bool Is_running   (void) const;
#if (0) // *important*: getting a query must "not" change the value of the current state;
		bool Is_stopped   (void) ;      // queries the event object for its signal state and changing the current state value appropriately;
#else   // changing value of the status to 'stopped' is the care of thread function 'stop';
		bool Is_stopped   (void) const; // checks only the current state, there is no query to event object;
		bool Is_stopped   (const bool); // sets current state to stopped; there is no query to event object; returns 'true' if state is changed;
#endif
		bool Is_valid (void) const;     // checks internal event object and own error state;

		CLocker& Locker (void);

		operator uint32_t (void) const;
		const
		CEvent&  operator ()(void) const;
		CEvent&  operator ()(void) ;

		CState&  operator <<(const e_state);
		TError&  operator <<(TError&); // sets current state value to e_state::eError, the error object is updated too;
		const
		CState&  operator >>(e_state& _out) const; // assigns current state value to input variable reference;

	private:
		CState& operator = (const CState&) = delete; CState& operator = (CState&&) = delete;
		// https://stackoverflow.com/questions/2484980/why-is-volatile-not-considered-useful-in-multithreaded-c-or-c-programming ;
		mutable CError  m_error;
		mutable CLocker m_lock ;  // this field is copied neither copy constructor nor copy assignment operator;
		CEvent  m_event;
		e_state m_state;
		
	};

	class CThreadBase {
	public:
		 CThreadBase (void); CThreadBase (const CThreadBase&); CThreadBase (CThreadBase&&) = delete;
		~CThreadBase (void);

		TError& Error (void) const;
		bool Is_valid (void) const; // checks error objects: its own and state object;
		/* query: QueueUserWorkItem how to get thread id winapi :
		The most direct way to get the ID of the thread currently executing work item is to call GetCurrentThreadId() within the callback thread proc;
		*/
		dword Id (void) const;  // just for removing unnecessary cast from 'unsigned long' to 'unsigned int': DWORD >> uint32_t;
		bool  Id (const dword); // it should be called within thread callback function/proc; returns 'true' on ID value change; not good idea :(

		const
		CState& State (void) const;
		CState& State (void) ;

		const
		CState& operator ()(void) const;
		CState& operator ()(void) ;

		static _pc_sz Cls_name (void);

	protected:
		CThreadBase& operator = (const CThreadBase&); CThreadBase& operator = (CThreadBase&&) = delete;
		mutable
		CError  m_error;
		CState  m_state;
		dword   m_id;
	};
}}}

typedef shared::runnable::threads::CState       TThreadState;
typedef shared::runnable::threads::CThreadBase  TThreadBase ;

#endif/*_RUNNER_BAS_H_INCLUDED*/