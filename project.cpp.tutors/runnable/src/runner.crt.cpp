/*
	Created by Tech_dog (ebontrop@gmail.com) on 1-May-2012 at 11:31:40am, GMT+3, Rostov-on-Don, Tuesday;
	This is Pulsepay Server Application Runnable Object class implementation file.
	-----------------------------------------------------------------------------
	Adopted to Platinum Clocking project on 19-Mar-2014 at 11:25:35am, GMT+3, Taganrog, Wednesday;
	Adopted to E-Opinion project on 8-May-2014 at 7:31:17am, GMT+3, Saint-Petersburg, Thursday;
	Adopted to Fake GPS project on 23-Apr-2020 at 11:35:05p, UTC+7, Novosibirsk, Thursday;
*/
#include "runner.crt.h"
#include "shared.preproc.h"

using namespace shared::runnable;

namespace shared { namespace runnable { namespace _impl
{
	err_code Runner_ForceToTerminate(const CEvent& _event, const HANDLE _thread, CError& _err) {
		_event; _thread; _err;
		if (__e_handle == _thread || 0 == _thread)
			return _err <<__e_inv_arg = _T("#__e_inv_arg: thread handle is invalid");

		if (false == _event.Wait(10)) {
			if (_event.Error())
				return _err = _event.Error();
			// https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-getexitcodethread ;
			// https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-terminatethread ;
#if (1)
			// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/endthread-endthreadex << is recommended for use;
			::_endthreadex(STILL_ACTIVE);
#else
			if (0 == ::TerminateThread(_thread, /*dword(-1)*/STILL_ACTIVE))
				_err.Last();
#endif
		}
		return _err;
	}

	dword Runner_RunPriorityToDword(const TRunPriority ePriority)
	{
		switch (ePriority) // https://learn.microsoft.com/en-us/windows/win32/procthread/scheduling-priorities ;
		{
		case CRunPriority::eHigh  :   return ABOVE_NORMAL_PRIORITY_CLASS;
		case CRunPriority::eNormal:   return NORMAL_PRIORITY_CLASS;
		}
		return BELOW_NORMAL_PRIORITY_CLASS;
	}
}}}
using namespace shared::runnable::_impl;

#pragma region cls::CCrtRunner{}

CCrtRunner::CCrtRunner (TRunnableFunc func, IEventNotify& sink_ref, const _variant_t& v_evt_id):
	m_notifier(sink_ref, v_evt_id), m_hThread(0), m_bStopped(true), m_function(func) {

	this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("#__e_not_inited: c-runtime thread is not created");

	if (__succeeded(this->m_event.Create()))
		this->m_event.Signaled(true); // means the work thread is not started yet;
}

CCrtRunner::~CCrtRunner(void) { this->m_event.Destroy(); }

TError& CCrtRunner::Error (void) const { return this->m_error; }
CMarshaller&
     CCrtRunner::Notifier (void)        { return m_notifier; }
bool CCrtRunner::IsRunning (void) const { return m_hThread && false == m_bStopped; }
bool CCrtRunner::IsStopped (void) const { return m_bStopped;  }
void CCrtRunner::MarkCompleted (void)   { this->m_event.Signaled(true); }

err_code CCrtRunner::Start (const TRunPriority ePriority) {
	ePriority;
	this->m_error <<__METHOD__<<__s_ok;

	if (false == this->m_event.Is_valid())
		return this->m_error = this->m_event.Error();

	if (false == IsStopped())
		return this->m_error << (err_code) TErrCodes::eExecute::eState = _T("#__e_inv_state: thread is already started");

	// if the worker thread was previously started, but somehow the thread handle is not cleared; to-do: it must be checked;
	if (this->m_hThread) {
		if (false == !!::CloseHandle(this->m_hThread))
			return this->m_error.Last();
		else
			this->m_hThread = nullptr;
	}
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/beginthread-beginthreadex << contains the example of symbol output to console;
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/standard-types << data type of returned value is 'uintptr_t';
	this->m_hThread = reinterpret_cast<void*>(::_beginthreadex(0, 0, m_function, this, CREATE_SUSPENDED, 0));
	if (0 == m_hThread || __e_handle == m_hThread)
		return this->m_error << __e_no_memory = _T("#__e_fail: cannot create c-runtime thread");

	this->m_bStopped = false;
	this->m_event << false;    // sets the event to nonsignal state, i.e. work thread is started its job;

	// https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-setthreadpriority ;
	// https://learn.microsoft.com/en-us/windows/win32/procthread/scheduling-priorities ;
	if (0 == ::SetThreadPriority(m_hThread, _impl::Runner_RunPriorityToDword(ePriority)))
		return this->m_error.Last();

	// prepares marshaller object for sending notification(s);
	if (__failed(this->m_notifier.Create()))
		return this->m_error = this->m_notifier.Error();
	// https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-resumethread ;
	if ((dword)-1 == ::ResumeThread(this->m_hThread))
		this->m_error.Last();

	return this->Error();
}

err_code CCrtRunner::Stop (const bool bForced) {
	bForced;
	this->m_error <<__METHOD__<<__s_ok;

	if (true == this->IsStopped())
		return this->m_error << (err_code) TErrCodes::eExecute::eState = _T("#__e_inv_state: thread is already stopped");

	this->m_bStopped = true;

	if (__failed(this->m_notifier.Destroy()))
		return this->m_error = this->m_notifier.Error();
	// if the input flag 'bForced' is set to 'true' that means the event object is not set to signaled state by the worker thread yet;
	// otherwise, it is expected the thread has already made its job and has set the event to signal state;
	if (bForced) {
		if (__failed(_impl::Runner_ForceToTerminate(this->m_event, m_hThread, this->m_error)))
			return this->Error();
	}
	else {
		uint32_t cnt_ = 0;
		while (false == this->m_event.Wait(200)) { // the hardcoded value of the wait timeout possibly must be reviewed;
			cnt_ ++;
			if (cnt_ > 10) { // anti-blocker, actually should never happen;
				return _impl::Runner_ForceToTerminate(this->m_event, m_hThread, this->m_error);
			}
		}
	}
	/* https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/endthread-endthreadex
	   the excerpt from the above article:
	   therefore, when you use _beginthreadex and _endthreadex, you must close the thread handle by calling the Win32 CloseHandle...;
	*/
	if (this->m_hThread) { // the thread handle must be still valid otherwise calling this function should never occur;
		if (0 == ::CloseHandle(m_hThread))
			this->m_error.Last();
		else
			this->m_hThread = 0;
	}
	return this->Error();
}

#pragma endregion