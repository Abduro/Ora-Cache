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

	interface IGenericEventNotify // ToDo: the name of the interface looks like not so appropriate as should be;
	{
		virtual err_code  GenEvt_OnNotify (const _variant_t v_evt_id) { v_evt_id; return __e_not_impl; }
		virtual err_code  GenEvt_OnNotify (const _long n_evt_id) { n_evt_id; return __e_not_impl; }
		virtual err_code  GenEvt_OnNotify (const _long n_evt_id, const _variant_t v_data) { n_evt_id; v_data; return __e_not_impl; }
	};

	class CEvent {
	public:
		 CEvent (void); CEvent (const CEvent&) = delete; CEvent (CEvent&&) = delete;
		~CEvent (void);

		err_code Create (void);
		err_code Destroy (void);

		TError&  Error (void) const;
		bool  Is_valid (void) const;

		_pc_sz   Name (void) const;
		bool  Is_signaled (void) const;
		err_code Signaled (const bool _yes_or_no);   // sets signaled state to signaled or to non-signaled one;

		bool Wait (const uint32_t _u_timeout) const; // returns 'true' if the waiting operation succeeds (WAIT_OBJECT_0) after specified timeout (msec);

		CEvent& operator <<(const bool _yes_or_no);
		const
		HANDLE& operator ()(void) const;
		HANDLE& operator ()(void) ;

	private:
		CEvent& operator = (const CEvent&) = delete; CEvent& operator = (CEvent&&) = delete;
		mutable
		CError  m_error;
		HANDLE  m_event;
		CString m_name ;
	};
	/* the class below creates message-only window:
	   https://learn.microsoft.com/en-us/windows/win32/winmsg/window-features#message-only-windows ;
	   the instance of this class must be accessible in worker thread for sending messages to main thread through the window being hidden;
	*/
	class CMarshaller {
	public:
		 CMarshaller (IGenericEventNotify&, const _variant_t& v_evt_id); CMarshaller (void) = delete; CMarshaller (CMarshaller&&) = delete;
		~CMarshaller (void);

		virtual err_code  Create (void);
		virtual err_code  Destroy (void);

		virtual err_code  Fire (const bool _b_async = true);
		virtual err_code  Fire2(void);   // posts a message directly to thread by using PostThreadMessage();
		static  err_code  Fire (const HWND hHandler, CError&, const bool _b_async = true);

		TError& Error (void) const;
		virtual HWND  GetHandle_Safe (void) const; // returns message-only-window handle, otherwise nullptr;
		const bool    Is_valid (void) const;       // checks message-only-window handle;

	protected:
		void*   m_handler;  // the pointer to class which creates message-only window;
		CError  m_error;

	private:
		CMarshaller& operator = (const CMarshaller&) = delete;
		CMarshaller& operator = (CMarshaller&&) = delete;
	};
	/* this class is intended to be used in worker thread procedure in order to create so delay in time, especially,
	   in iterative loops of the processing data;
	*/
	class CDelayEvent {
	public:
		enum e_frame : d_word {
			e_na      = 0,
			eInfinite = (d_word)-1
		};

	public:
		 CDelayEvent (const d_word nTimeSlice = e_frame::e_na, const d_word nTimeFrame = e_frame::e_na);
		 CDelayEvent (const CDelayEvent&) = delete; CDelayEvent (CDelayEvent&&) = delete;
		~CDelayEvent (void) = default;

		virtual bool Elapsed (void) const;
		virtual bool IsReset (void) const;

		virtual void Reset (const d_word nTimeSlice = e_frame::e_na, const d_word nTimeFrame = e_frame::e_na);
		virtual void Wait  (void);

		CDelayEvent& operator = (const CDelayEvent&) = delete; CDelayEvent& operator = (CDelayEvent&&) = delete;
		CDelayEvent& operator <<(const d_word) ; // sets time frame value of waiting for;

	protected:
		volatile d_word m_nTimeSlice; // time slice in milliseconds;
		volatile d_word m_nTimeFrame; // total time to wait for;
	
		d_word m_nCurrent; // current time;
	};

}}

#endif/*_RUN_EVENT_H_INCLUDED*/