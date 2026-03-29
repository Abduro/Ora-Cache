#ifndef _EBO_TEST_$W$_THREAD_INCLUDED
#define _EBO_TEST_$W$_THREAD_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Mar-2026 at 00:55:27.998, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' thread pool unit test adapter interface declaration file; 
*/
#include "test_case_$w$.event.h"

namespace ebo { namespace boo { namespace test { namespace thread {

	__class (c_event) {
	public:
		 c_event (void) = default; c_event (const c_event&) = delete; c_event (c_event&&) = delete;
		~c_event (void) = default;

		__method (Create);
		__method (Destroy);

	private:
		c_event& operator = (const c_event&) = delete; c_event& operator = (c_event&&) = delete;
	};

}}}}

#endif/*_EBO_TEST_$W$_THREAD_INCLUDED*/