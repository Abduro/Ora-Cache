#ifndef _RUN_EVENT_H_INCLUDED
#define _RUN_EVENT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) 26-Dec-2010 at 7:00:02pm, GMT+3, Rostov-on-Don, Sunday;
	This is SFX project Asynchronous notifying/waiting object interface declartion file.
	-----------------------------------------------------------------------------
	Adopted to Pulspay Server project on 2-May-2012 at 1:09:18pm, GMT+3, Rostov-on-Don, Wednesday;
	Adopted to Platinum Clocking project on 19-Mar-2014 at 11:21:09am, GMT+3, Taganrog, Wednesday;
	Adopted to E-Opinion project on 8-May-2014 at 7:17:15am, GMT+3, Saint-Petersburg, Thursday;
	Adopted to Internext project on 20-Aug-2014 at 8:03:27pm, GMT+3, Taganrog, Wednesday;
	Adopted to Fake GPS project on 11-Dec-2019 at 7:59:09p, UTC+7, Novosibirsk, Wednesday;
*/
#include "run.base.h"

namespace shared { namespace runnable {

	interface IEventNotify // ToDo: the name of the interface looks like not so appropriate as should be;
	{
		virtual err_code  GenEvt_OnNotify (const _variant_t v_evt_id) { v_evt_id; return __e_not_impl; }
		virtual err_code  GenEvt_OnNotify (const _long n_evt_id) { n_evt_id; return __e_not_impl; }
		virtual err_code  GenEvt_OnNotify (const _long n_evt_id, const _variant_t v_data) { n_evt_id; v_data; return __e_not_impl; }
	};
	/* this class is for managing a thread procedure: to start or to stop it;
	*/
	class CEvent {
	public:
		 CEvent (void); CEvent (const CEvent&) = delete; CEvent (CEvent&&) = delete;
		~CEvent (void);

		err_code Create (void);
		err_code Destroy (void);
		// https://english.stackexchange.com/questions/239815/can-dupe-be-used-as-a-verb-instead-of-duplicate ;
		err_code Dup (const HANDLE _h_event, const HANDLE _process); // makes a duplicate of the input/given event handle;
		err_code Dup (const CEvent&); // duplicates input event handle for the current process;

		TError&  Error (void) const;
		bool  Is_valid (const bool _b_set_error = false) const; // sets error object if not valid for test cases if necessary;

		_pc_sz   Name (void) const;
		bool  Is_signaled (void) const;
		err_code Signaled (const bool _yes_or_no);   // sets this event state to signaled or to non-signaled;

		bool Wait (const uint32_t _u_timeout) const; // returns 'true' if the waiting operation succeeds (WAIT_OBJECT_0) after specified timeout (msec);

		CEvent& operator <<(const bool _yes_or_no);  // sets this event state to signaled or to non-signaled;
		CEvent& operator <<(const CEvent&);          // duplicates the event handle of input event object for *this* process;
		CEvent& operator <<(const HANDLE _h_event);  // duplicates the given event handle for *this* process;
		const
		HANDLE& operator ()(void) const;
		HANDLE& operator ()(void) ;
		// https://learn.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-compareobjecthandles ;
		bool operator == (const HANDLE _h_event) const; // makes a comparison of input handle with the handle of this object;

	private:
		CEvent& operator = (const CEvent&) = delete; CEvent& operator = (CEvent&&) = delete;
		mutable
		CError  m_error;
		HANDLE  m_event;
		CString m_name ;
	};
	/* this class creates message-only window: https://learn.microsoft.com/en-us/windows/win32/winmsg/window-features#message-only-windows ;
	   the instance of this class must be accessible in worker thread for sending messages to main thread through the window being hidden;
	*/
	class CMarshaller {
	public:
		 CMarshaller (IEventNotify&, const _variant_t& v_evt_id); CMarshaller (void) = delete; CMarshaller (CMarshaller&&) = delete;
		~CMarshaller (void);
		// the virtual functions/methods must be go first in declaraion of the class for better performance, but it is not important for now;
		virtual err_code  Create (void);
		virtual err_code  Destroy (void);

		virtual err_code  Fire (const bool _b_async = true);
		static  err_code  Fire (const HWND hHandler, CError&, const bool _b_async = true); // hwnd is the window for receiving messages, it is expected to be message-only window;
		virtual err_code  Post (void);   // posts a message directly to thread by using PostThreadMessage();

		TError& Error (void) const;
		virtual HWND  GetHandle_Safe (void) const; // returns message-only-window handle, otherwise nullptr;
		const bool    Is_valid (void) const;       // checks message-only-window handle;

	protected:
		void*   m_handler;  // the pointer to class which creates message-only window; to-do: such hidden of the implementatiom must be reviewed;
		CError  m_error;

	private:
		CMarshaller& operator = (const CMarshaller&) = delete;
		CMarshaller& operator = (CMarshaller&&) = delete;
	};
	/* this class is intended to be used in worker thread procedure in order to create so delay in time, especially,
	   in iterative loops of the processing data;
	   also, this class may be used in the main thread for waiting when worker thead ends its job, for example, in test cases;
	*/
	class CDelay {
	public:
		enum e_frame : d_word {
			e_na      = 0,
			eInfinite = (d_word)-1
		};

	public:
		 CDelay (const dword nTimeSlice = e_frame::e_na, const dword nTimeFrame = e_frame::e_na);
		 CDelay (const CDelay&); CDelay (CDelay&&) = delete;
		~CDelay (void) = default;

		dword    Frame (void) const ; // gets time frame value in msec;
		err_code Frame (const dword); // sets time frame value in msec; if input value equals to 0, error code is returne;
		dword    Slice (void) const ; // gets time slice or step value that increments the elapsed time till the total or frame period of time;
		err_code Slice (const dword); // sets time slice in msec; error code is returned in cases: input equals to '0' or grater than time frame;

		TError&  Error (void) const;

		bool  Elapsed  (void) const;  // returns 'true' in case when elapsed time equals to or greater than time frame and 'reset' is required;
		bool  IsReset  (void) const;  // returns 'true' in case the elapsed time, i.e. current time value, equals to '0' that means a start point for delaying;
		bool  Is_valid (void) const;  // checks values of the elapced/current time and time frame; it it returns 'false' the error object contains the description;

		err_code Reset (void);        // resets the current/elapsed time to 0 (zero) for starting new iteration of delaying process;
		err_code Reset (const d_word nTimeSlice, const d_word nTimeFrame); // sets new time slice and frame values; 
		err_code Wait  (void);        // starts to delay for specified time frame; there is no check for error because ::Sleep(0) works also;

		CString  To_str (void) const; // converts this class object fields to string representation for test cases' output;

		CDelay& operator = (const CDelay&); CDelay& operator = (CDelay&&) = delete;
		CDelay& operator <<(const d_word); // sets time frame value of waiting for;
		CDelay& operator >>(const d_word); // sets time slice value for incresing the elapsed time;

	protected:
		volatile d_word m_nTimeSlice; // time slice in milliseconds; 'volatile' specificator is required because values can be changed from different threads;
		volatile d_word m_nTimeFrame; // total time to wait for;
		mutable
		CError m_error;
		d_word m_nCurrent; // current time;
	};
	/* this class is for waiting till a worker thread ends its job, or similar asynchronous work;
	*/
	class CAwait {
	public:
		 CAwait (void); CAwait (const CAwait&) = delete; CAwait (CAwait&&) = delete;
		~CAwait (void) = default;
		 CAwait (const CDelay&, const CEvent&);
		const
		CDelay&  Delay (void) const;
		CDelay&  Delay (void) ;
		const
		CEvent&  Event (void) const; // gets reference to the event object that must be duplicated from event that is used by worker thread; (ro)
		CEvent&  Event (void) ;      // gets reference to the event object that must be duplicated from event that is used by worker thread; (rw)

		TError&  Error (void) const;
		bool  Is_valid (void) const;

		err_code Wait  (void) ;

		CAwait&  operator <<(const CDelay&);
		CAwait&  operator <<(const CEvent&);

	private:
		CAwait&  operator = (const CAwait&) = delete; CAwait& operator = (CAwait&&) = delete;
		mutable
		CError   m_error;
		CDelay   m_delay;
		CEvent   m_event;
	};

}}

#endif/*_RUN_EVENT_H_INCLUDED*/