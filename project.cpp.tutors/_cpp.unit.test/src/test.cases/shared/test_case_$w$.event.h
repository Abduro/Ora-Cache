#ifndef _TEST_CASE_$W$_EVENT_H_INCLUDED
#define _TEST_CASE_$W$_EVENT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Mar-2026 at 00:45:13.516, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' thread event wrapper interface declaration file for using in test cases adapters;
*/
#include "ebo_test_$w$.defs.h"
#include "run.event.h"

namespace ebo { namespace boo { namespace test { namespace thread {

	using CEvent = shared::runnable::CEvent;
	using CMarshaller = shared::runnable::CMarshaller;
	using IEvtNotify = shared::runnable::IGenericEventNotify;

	class CTstEvent {
	public:
		 CTstEvent (void) = default; CTstEvent (const CTstEvent&) = delete; CTstEvent (CTstEvent&&) = delete;
		~CTstEvent (void) = default;

		err_code Create (void);
		err_code Destroy (void);
		err_code Signaled (const bool _b_on_off);

		const
		CEvent& operator ()(void) const;
		CEvent& operator ()(void) ;

	private:
		CTstEvent& operator = (const CTstEvent&) = delete; CTstEvent& operator = (CTstEvent&&) = delete;
		CEvent m_event; 
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