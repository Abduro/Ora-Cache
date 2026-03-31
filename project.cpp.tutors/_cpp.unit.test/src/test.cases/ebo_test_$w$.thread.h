#ifndef _EBO_TEST_$W$_THREAD_INCLUDED
#define _EBO_TEST_$W$_THREAD_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Mar-2026 at 00:55:27.998, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' thread pool unit test adapter interface declaration file; 
*/
#include "test_case_$w$.run.crt.h"

namespace ebo { namespace boo { namespace test { namespace thread {

	__class (c_await) {
	public:
		 c_await (void) = default; c_await (const c_await&) = delete; c_await (c_await&&) = delete;
		~c_await (void) = default;

		__method (Wait);

	private:
		c_await& operator = (const c_await&) = delete; c_await& operator = (c_await&&) = delete;
	};

	__class (c_crt_runner) {
	public:
		 c_crt_runner (void) = default; c_crt_runner (const c_crt_runner&) = delete; c_crt_runner (c_crt_runner&&) = delete;
		~c_crt_runner (void) = default;

		__method (Start);
		__method (Stop);

		const
		CTstRunner& operator ()(void) const;
		CTstRunner& operator ()(void) ;

	private:
		c_crt_runner& operator = (const c_crt_runner&) = delete; c_crt_runner& operator = (c_crt_runner&&) = delete;
		CTstRunner m_crt_run;
	};

	__class (c_event) {
	public:
		 c_event (void) = default; c_event (const c_event&) = delete; c_event (c_event&&) = delete;
		~c_event (void) = default;

		__method (Create);
		__method (Destroy);
		__method (Signaled);

	private:
		c_event& operator = (const c_event&) = delete; c_event& operator = (c_event&&) = delete;
	};

	__class (c_marshaller) {
	public:
		 c_marshaller (void) = default; c_marshaller (const c_marshaller&) = delete; c_marshaller (c_marshaller&&) = delete;
		~c_marshaller (void) = default;

		__method (Create);
		__method (Destroy);
		__method (Notify);

	private:
		c_marshaller& operator = (const c_marshaller&) = delete; c_marshaller& operator = (c_marshaller&&) = delete;
	};

}}}}

#endif/*_EBO_TEST_$W$_THREAD_INCLUDED*/