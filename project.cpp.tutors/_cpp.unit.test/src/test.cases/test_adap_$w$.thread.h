#ifndef _TEST_ADAP_$W$_THREAD_INCLUDED
#define _TEST_ADAP_$W$_THREAD_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Mar-2026 at 00:55:27.998, UTC+4, Batumi, Monday;
	This is Ebo Pack c-runtime and system thread pool unit test adapter interface declaration file; 
*/
#include "test_case_$w$.run.crt.h"
#include "test_case_$w$.run.tpl.h"

namespace test { namespace win_api { namespace threads {

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
		/* the following steps compose this test case:
		   (1) creating crt runner object that will manage the worker thread;
		   (2) creating the await object in order to make main thread of test case waiting the completness of worker thread procedure;
		   (3) starting the work thread, the awaiting object will delay its execution till the work thread gets its job done;
		   (4) connecting the event object of the crt runner with the event of the await object by duplicating;
		   (5) at the end of the thread proc, the runner is notified about the job done and sets the event to signal state;
		   (6) the awaiting object completes its work;
		   the result: and the test case is successfully completed;
		*/
		__method (Run);
		__method (Run_on_signal); // uses other function that connect two events together for waiting on change the state of one of them;
		// starts the crt thread by connecting delay object with fake event, after delay finishes,
		// the worker thread is forced to stop, regardless the thread procedure completeness;
		__method (Start);
		__method (Stop);   // this test case tries to stop crt thread that is not started yet; the expected error is handled;

		const
		CTstCrtRunner& operator ()(void) const;
		CTstCrtRunner& operator ()(void) ;

	private:
		c_crt_runner& operator = (const c_crt_runner&) = delete; c_crt_runner& operator = (c_crt_runner&&) = delete;
		CTstCrtRunner m_crt_run;
	};

	__class (c_event) {
	public:
		 c_event (void) = default; c_event (const c_event&) = delete; c_event (c_event&&) = delete;
		~c_event (void) = default;

		__method (Create);
		__method (Destroy);
		__method (Signal);

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

	__class (c_tpl_runner) {
	public:
		 c_tpl_runner (void) = default; c_tpl_runner (const c_tpl_runner&) = delete; c_tpl_runner (c_tpl_runner&&) = delete;
		~c_tpl_runner (void) = default;

		__method (Run);
		__method (Start);
		__method (Stop);

		const
		CTstTplRunner& operator ()(void) const;
		CTstTplRunner& operator ()(void) ;

	private:
		c_tpl_runner& operator = (const c_tpl_runner&) = delete; c_tpl_runner& operator = (c_tpl_runner&&) = delete;
		CTstTplRunner m_tpl_run;
	};
}}}

#endif/*_TEST_ADAP_$W$_THREAD_INCLUDED*/