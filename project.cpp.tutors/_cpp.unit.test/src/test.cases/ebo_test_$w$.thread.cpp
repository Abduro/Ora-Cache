/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Mar-2026 at 00:58:43.965, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' thread pool unit test adapter interface implementation file; 
*/
#include "ebo_test_$w$.thread.h"

using namespace ebo::boo::test::threads;

#pragma region cls::c_await{}

void c_await::Wait (void) {

	const uint32_t u_time_frame = 1000;
	const uint32_t u_time_slice = 100;

	CTstAwait await;
	await.Wait(u_time_frame, u_time_slice);

	_out()();
}

#pragma endregion
#pragma region cls::c_crt_runner{}

void c_crt_runner::Run (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	const uint32_t u_time_frame = 1000;
	const uint32_t u_time_slice = 100;

	// (1) crt runner object is already created in constructor of this class;
	CTstCrtRunner& crt_runner = (*this)();
	// (2) creating the await object in order to make main thread of test case waiting for the completness of worker thread procedure;
	CTstAwait await_obj;
	await_obj().Delay().Reset(u_time_slice, u_time_frame); // no check for the error, it is done in wait() operation;

	// (3) starting the work thread, the awaiting object delays its execution till the work thread gets its job done;
	if (__failed(crt_runner.Start())) { _out()(); return; } // the thread starting is failed, the tast case is not passed;

	// (4) connecting the event object of the crt runner with the event of the await object by duplicating;
	if (__failed(await_obj.Wait(crt_runner()().Event(), false))) {
		crt_runner()().Event() << true; // the worker thread must be stopped anyway;
	} else {
	// (5) at the end of the thread proc, the runner is notified about the job done and sets the event to signal state;
	}
	// (6) the awaiting object completes its work;
	_out() += _T("[impt] result: worker thread is completed its job;");
	_out()();
}

void c_crt_runner::Run_on_signal (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	const uint32_t u_timeout = 1000;
	// (1) crt runner object is already created in constructor of this class;
	CTstCrtRunner& crt_runner = (*this)();
	// (2) creating the await object in order to make main thread of test case waiting the completness of worker thread proc;
	CTstAwait await_obj;
	// (3) starting the work thread, the awaiting object delays its execution till the work thread gets its job done;
	if (__failed(crt_runner.Start())) { _out()(); return; } // the thread starting is failed, the tast case is not passed;
	// (4) makes the awaiting object to wait until the worker thread get its job done;
	if (__failed(await_obj.Wait_on_signal(crt_runner()().Event(), u_timeout, false))) {
		crt_runner()().Event() << true; // the worker thread must be stopped anyway;
	} else {
	// (5) at the end of the thread proc, the runner is notified about the job done and sets the event to signal state;
	}
	// (6) the awaiting object completes its work;
	_out() += _T("[impt] result: worker thread is completed its job;");

	_out()();
}

void c_crt_runner::Start (void) {

	const uint32_t u_time_frame = 1000;
	const uint32_t u_time_slice = 100;

	(*this)().Start();
	CTstAwait().Wait(u_time_frame, u_time_slice);
	(*this)().Stop(true); _out()();
}

void c_crt_runner::Stop (void) {
	(*this)().Stop(true); _out()(); // expected error: nothing is started - nothing is stopped;
}

const
CTstCrtRunner& c_crt_runner::operator ()(void) const { return this->m_crt_run; }
CTstCrtRunner& c_crt_runner::operator ()(void)       { return this->m_crt_run; }

#pragma endregion
#pragma region cls::c_event{}

void c_event::Create (void) { CTstEvent().Create(); _out()(); }

void c_event::Destroy (void) {

	CTstEvent event;

	event.Create();
	event.Destroy(); _out()();
}

void c_event::Signal (void) {

	CTstEvent event;
	event.Create();
	event.Signal (true);
	event.Signal (false);
	event.Destroy();
	_out()();
}

#pragma endregion
#pragma region cls::c_marshaller{}

void c_marshaller::Create (void) {

	CTstNotifier notifier;
	if (__succeeded(notifier.Create()))
		notifier.Destroy();

	_out()();
}

void c_marshaller::Destroy (void) {

	CTstNotifier notifier;
	notifier.Destroy();
	_out()();
}

void c_marshaller::Notify (void) {

	CTstEvent event;
	CTstNotifier notifier;

	const bool b_async = false; // the test case exits immediately with no waiting of receiving the notification asynchronously; 
#if (0)
	notifier.Notify(b_async);   // receiving the error is expected;
#endif
	event.Create();

	notifier.Create();
	notifier.Notify(b_async);

	event().Wait(100); // the waiting occurs in the same thread of this test case, thus nothing can be delivered to receiver/listener;

	notifier.Destroy();

	_out()();
}

#pragma endregion
#pragma region cls::c_tpl_runner

void c_tpl_runner::Run (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	const uint32_t u_time_frame = 1000;
	const uint32_t u_time_slice = 100;

	// (1) tpl runner local object;
	CTstTplRunner& tpl_runner = (*this)();
	// (2) creating the await object in order to make main thread of test case waiting for the completness of worker thread procedure;
	CTstAwait await_obj;
	await_obj().Delay().Reset(u_time_slice, u_time_frame); // no check for the error, it is done in wait() operation;

	// (3) starting the work thread, the awaiting object delays its execution till the work thread gets its job done;
	if (__failed(tpl_runner.Start())) { _out()(); return; } // the thread starting is failed, the tast case is not passed;

	// (4) connecting the event object of the crt runner with the event of the await object by duplicating;
	if (__failed(await_obj.Wait(tpl_runner()().Event(), false))) {
		tpl_runner()().Event() << true; // the worker thread must be stopped anyway;
	} else {
	// (5) at the end of the thread proc, the runner is notified about the job done and sets the event to signal state;
	}
	// (6) the awaiting object completes its work;
	_out() += _T("[impt] result: worker thread is completed its job;");
	_out()();
}

void c_tpl_runner::Start (void) {
	(*this)().Start(); _out()();
}

void c_tpl_runner::Stop (void) {
	(*this)().Stop();_out()();
}

const
CTstTplRunner& c_tpl_runner::operator ()(void) const { return this->m_tpl_run; }
CTstTplRunner& c_tpl_runner::operator ()(void)       { return this->m_tpl_run; }

#pragma endregion