/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Mar-2026 at 00:58:43.965, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' thread pool unit test adapter interface implementation file; 
*/
#include "ebo_test_$w$.thread.h"

using namespace ebo::boo::test::thread;

#pragma region cls::c_await{}

void c_await::Wait (void) {

	CTstAwait await;
	await.Wait();

	_out()();
}

#pragma endregion
#pragma region cls::c_crt_runner{}

void c_crt_runner::Start (void) {

	(*this)().Start();
	(*this)().Stop(true); _out()();
}

void c_crt_runner::Stop (void) {
	(*this)().Stop(true); _out()();
}

const
CTstRunner& c_crt_runner::operator ()(void) const { return this->m_crt_run; }
CTstRunner& c_crt_runner::operator ()(void)       { return this->m_crt_run; }

#pragma endregion
#pragma region cls::c_event{}

void c_event::Create (void) { CTstEvent().Create(); _out()(); }

void c_event::Destroy (void) {

	CTstEvent event;

	event.Create();
	event.Destroy(); _out()();
}

void c_event::Signaled (void) {

	CTstEvent event;
	event.Create();
	event.Signaled (true);
	event.Signaled (false);
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

	const bool b_async = false; // the test case exits immediately with no waiting the receiving the notification asynchronously; 
#if (0)
	notifier.Notify(b_async);   // receiving the error is expected;
#endif
	event.Create();

	notifier.Create();
	notifier.Notify(b_async);

	event().Wait(100); // the waiting occurs in the one thread of this test case, thus nothing can be delivered to receiver/listener;

	notifier.Destroy();

	_out()();
}

#pragma endregion