/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Mar-2026 at 12:34:01.536, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' thread pool event wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$w$.run.crt.h"
#include "shared.preproc.h"

using namespace ebo::boo::test::thread;

#pragma region cls::CTstRunner{}

CTstRunner::CTstRunner (void) : m_runner(CTstRunner::Thread_Func, m_listener, _variant_t(1L)) {}

unsigned int __stdcall CTstRunner::Thread_Func (void* pObject) {
	pObject;
	unsigned int u_result = 1; // sets to 'error' result;

	if (nullptr == pObject) {
		return u_result;
	}

	CCrtRunner* p_runner = 0;
	// try...catch block looks like not necessary because the input parameter data type is guaranteed by this class implementation;
	try {
		p_runner = reinterpret_cast<CCrtRunner*>(pObject);
		if (nullptr == p_runner) {
			return u_result;
		}
	}
	catch(::std::bad_cast&) { return u_result; }

	const dword u_slice = 10;    // this is the counter/slice of time to increment the elapsed time;
	const dword u_frame = 100;   // this is time frame to wait for; (msec);

	CDelay delay_evt(u_slice, u_frame);

	while (false == p_runner->IsStopped()) {
		
		delay_evt.Wait();        // waits for a particular time slice; (u_slice)
		if (delay_evt.Elapsed()) // the time frame being waited for is reached; (u_frame)
			delay_evt.Reset();

		p_runner->Notifier().Fire(false); // sends a notification to the listener;
	}

	p_runner->MarkCompleted();

	return (u_result = 0);
}

#pragma endregion