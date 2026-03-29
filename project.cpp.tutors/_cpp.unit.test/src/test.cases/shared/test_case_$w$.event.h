#ifndef _TEST_CASE_$W$_EVENT_H_INCLUDED
#define _TEST_CASE_$W$_EVENT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Mar-2026 at 00:45:13.516, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' thread pool event wrapper interface declaration file for using in test cases adapters;
*/
#include "ebo_test_$w$.defs.h"
#include "run.event.h"

namespace ebo { namespace boo { namespace test { namespace thread {

	using CEvent = shared::runnable::CEvent;

	class CTstEvent {
	public:
		 CTstEvent (void) = default; CTstEvent (const CTstEvent&) = delete; CTstEvent (CTstEvent&&) = delete;
		~CTstEvent (void) = default;

		err_code Create (void);
		err_code Destroy (void);

		const
		CEvent& operator ()(void) const;
		CEvent& operator ()(void) ;

	private:
		CTstEvent& operator = (const CTstEvent&) = delete; CTstEvent& operator = (CTstEvent&&) = delete;
		CEvent m_event; 
	};

}}}}

#endif/*_TEST_CASE_$W$_EVENT_H_INCLUDED*/