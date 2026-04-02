/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Mar-2026 at 12:34:01.536, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' thread pool event wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$w$.run.crt.h"
#include "shared.preproc.h"

using namespace ebo::boo::test::thread;

#pragma region cls::CTstRunner{}

CTstRunner:: CTstRunner (void) : m_runner(CTstRunner::Thread_Func, m_listener, _variant_t(1L)) {}
CTstRunner::~CTstRunner (void) {
	if ((*this)()().Is_running()) { // c-runtime worker thread does it automatically in its destructor, but for test case it is better to check it here;
		_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		this->Stop(/*_b_forced*/true, /*_cls_output*/false);
		_out()();
	}
}

err_code CTstRunner::Start (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Start())) { _out() += (*this)().Error(); return (*this)().Error(); }
	else _out() += _T("[impt] result: c-runtime thread is started;");

	return (*this)().Error();
}

err_code CTstRunner::Stop (const bool _b_forced/* = false*/, bool _cls_output/* = true*/) {
	_b_forced; _cls_output;
	if (_cls_output)
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(_T("Forced stop: '%s';"), TString().Bool(_b_forced));

	if (__failed((*this)().Stop(_b_forced))) { _out() += (*this)().Error(); return (*this)().Error(); }
	else _out() += _T("[impt] result: c-runtime thread is stopped;");

	return (*this)().Error();
}

const
CCrtRunner& CTstRunner::operator ()(void) const { return this->m_runner; }
CCrtRunner& CTstRunner::operator ()(void)       { return this->m_runner; }

unsigned int __stdcall CTstRunner::Thread_Func (void* pObject) {
	pObject;
	unsigned int u_result = 1; // sets to 'error' result;
	_out() += TString().Format(_T("[impt] cls::[%s].%s(): entered;"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

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

	const dword u_slice = 100;    // this is the counter/slice of time to increment the elapsed time;
	const dword u_frame = 2000;   // this is time frame to wait for; (msec);

	uint32_t cnt_ = 0; cnt_; // this is the counter of the iterations for log messages;

	CDelay delay_evt(u_slice, u_frame);
	/* to check p_runner->Is_stopped() does not have any reason, due to setting this flag can be only made outside of this thread procedure;
	   taking into account the fact that this procedure must get its job done,
	   there is a synchronization required between external delay object timeout and a period of time that is necessary for completing this procedure;
	   a one of the possible soliutions is to use event object:
	   the main thread waits the event to be signaled and then continue execution,
	   and this worker thread will set event to signaled state at the end of this procedure;
	   the setting 'is stopped' flag to 'true' is still possible for owner of this thread, but not for passing this test case;
	*/
	while (/*false == (*p_runner)().Is_stopped() &&*/ true == (*p_runner)().Is_running()) {
		
		delay_evt.Wait();        // waits for a particular time slice; (u_slice)
		_out() += TString().Format(_T("cls::[%s].%s(): iter_ = #%u;"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, ++cnt_);

		if (delay_evt.Elapsed()) { // the time frame being waited for is reached; (u_frame)
			delay_evt.Reset();
			break;
		}
		// sends a notification to the listener; in case of async == true, no notificatiom is delivered;
		// but writing to _out() works faster, that means sending a notification synchronously through neassage-only window is slow;
		p_runner->Notifier().Fire(true);
	}
	_out() += TString().Format(_T("cls::[%s].%s(): completed;"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	(*p_runner)().Event() << true; // all notifications and test case logger messages must appear before this command;

	return (u_result = 0);
}

#pragma endregion