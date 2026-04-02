#ifndef _TEST_CASE_$W$_EVENT_H_INCLUDED
#define _TEST_CASE_$W$_EVENT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Mar-2026 at 00:45:13.516, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' thread event wrapper interface declaration file for using in test cases adapters;
*/
#include "ebo_test_$w$.defs.h"
#include "run.event.h"

namespace ebo { namespace boo { namespace test { namespace thread {

	using CAwait = shared::runnable::CAwait;
	using CDelay = shared::runnable::CDelay;
	using CEvent = shared::runnable::CEvent;
	using CMarshaller = shared::runnable::CMarshaller;
	using IEvtNotify = shared::runnable::IEventNotify;

	class CTstEvent {
	public:
		 CTstEvent (void) = default; CTstEvent (const CTstEvent&) = delete; CTstEvent (CTstEvent&&) = delete;
		~CTstEvent (void); // the destructor is necessary for output that the encapsulated object(s) is destroyed too;

		err_code Create (void);
		err_code Destroy (void);
		err_code Signal (const bool _b_on_off);

		const
		CEvent& operator ()(void) const;
		CEvent& operator ()(void) ;

	private:
		CTstEvent& operator = (const CTstEvent&) = delete; CTstEvent& operator = (CTstEvent&&) = delete;
		CEvent m_event; 
	};

	class CTstAwait {
	public:
		 CTstAwait (void) = default; CTstAwait (const CTstAwait&) = delete; CTstAwait (CTstAwait&&) = delete;
		~CTstAwait (void); // the destructor is necessary for output that the encapsulated object(s) is destroyed too;

		err_code Wait (const uint32_t _u_frame, const uint32_t _u_slice);  // works with internal event object and uses input params to set delay object;
		err_code Wait (const CEvent& _evt_extern, const bool _cls_output = false); // is intended for working with c-runtime thead event object;
		/*
		this test case *cannot* be used because it block the main thread for waiting the thread execution completeness,
		but thread function tries to send notifications to listener:  *deadlock*;
		*/
		err_code Wait_on_signal (const CEvent& _signal_from, const uint32_t _e_timeout, const bool _cls_output);

		const
		CAwait& operator ()(void) const;
		CAwait& operator ()(void) ;

	private:
		CTstAwait& operator = (const CTstAwait&) = delete; CTstAwait& operator = (CTstAwait&&) = delete;
		CAwait    m_await;
		CTstEvent m_event; // this event is used as external event object for emulating a thread's event that used for indicating the thread work is done;
	};

	using namespace shared::types;

	class CTstListener : public IEvtNotify {
	public:
		 CTstListener (void) = default; CTstListener (const CTstListener&) = delete; CTstListener (CTstListener&&) = delete;
		~CTstListener (void) = default;

		err_code  GenEvt_OnNotify (const _long n_evt_id) override final;

	private:
		CTstListener& operator = (const CTstListener&) = delete; CTstListener& operator = (CTstListener&&) = delete;
	};

	class CTstNotifier {
	public:
		 CTstNotifier (void); CTstNotifier (const CTstNotifier&) = delete; CTstNotifier (CTstNotifier&&) = delete;
		~CTstNotifier (void) = default;

		err_code Create (void);
		err_code Destroy (void);
		err_code Notify (const bool _b_async); // generates the sending a notification to the listener; it looks like the asynchronous sending is not suitable for test case;

		const
		CMarshaller& operator ()(void) const;
		CMarshaller& operator ()(void) ;

	private:
		CTstNotifier& operator = (const CTstNotifier&) = delete; CTstNotifier& operator = (CTstNotifier&&) = delete;
		CMarshaller   m_notifier;
		CTstListener  m_listener;
	};

}}}}

#endif/*_TEST_CASE_$W$_EVENT_H_INCLUDED*/