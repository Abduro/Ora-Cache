/*
	Created by Tech_dog (ebontrop@gmail.com) on 1-May-2012 at 11:31:40am, GMT+3, Rostov-on-Don, Tuesday;
	This is Pulsepay Server Application Runnable Object class implementation file.
	-----------------------------------------------------------------------------
	Adopted to Platinum Clocking project on 19-Mar-2014 at 11:25:35am, GMT+3, Taganrog, Wednesday;
	Adopted to E-Opinion project on 8-May-2014 at 7:31:17am, GMT+3, Saint-Petersburg, Thursday;
	Adopted to Fake GPS project on 23-Apr-2020 at 11:35:05p, UTC+7, Novosibirsk, Thursday;
*/
#include "runner.crt.h"

using namespace shared::runnable;

/////////////////////////////////////////////////////////////////////////////

namespace shared { namespace runnable { namespace details
{
	HRESULT Runner_ForceToTerminate(HANDLE event_, HANDLE thread_)
	{
		HRESULT hr_ = S_OK;
		const DWORD dwRet = ::WaitForSingleObject(event_, 10);
		if (WAIT_OBJECT_0!= dwRet)
		{
			if (thread_)
			{
				::TerminateThread(thread_, DWORD(-1));
			}
		}
		return  hr_;
	}

	DWORD   Runner_RunPriorityToDword(const TRunPriority ePriority)
	{
		switch (ePriority)
		{
		case CRunPriority::eHigh  :   return ABOVE_NORMAL_PRIORITY_CLASS;
		case CRunPriority::eNormal:   return NORMAL_PRIORITY_CLASS;
		}
		return BELOW_NORMAL_PRIORITY_CLASS;
	}
}}}
using namespace shared::runnable::details;
/////////////////////////////////////////////////////////////////////////////

CCrtRunner::CCrtRunner(TRunnableFunc func, IGenericEventNotify& sink_ref, const _variant_t& v_evt_id):
	m_async_evt(sink_ref, v_evt_id),
	m_hThread(NULL),
	m_hEvent(NULL),
	m_bStopped(true),
	m_function(func)
{
	m_hEvent = ::CreateEvent(0, TRUE, TRUE, 0);
	if (INVALID_HANDLE_VALUE == m_hEvent || NULL == m_hEvent)
	{
		ATLASSERT(FALSE); m_hEvent = NULL;
	}
}

CCrtRunner::~CCrtRunner(void)
{
	if (m_hEvent)
	{
		::CloseHandle(m_hEvent); 
		m_hEvent = NULL;
	}
}

/////////////////////////////////////////////////////////////////////////////

CMarshaller&
        CCrtRunner::Event(void)           { return m_async_evt; }
bool    CCrtRunner::IsRunning(void) const { return(m_hThread && !m_bStopped); }
bool    CCrtRunner::IsStopped(void) const { return m_bStopped;  }
void    CCrtRunner::MarkCompleted(void)   { if (m_hEvent) { ::SetEvent(m_hEvent); } }

HRESULT CCrtRunner::Start(const TRunPriority ePriority)
{
	if (NULL == m_hEvent) return OLE_E_BLANK;
	if (!IsStopped()) return S_OK;
	if (m_hThread)
	{
		::CloseHandle(m_hThread);
		m_hThread = NULL;
	}
	m_hThread  = (HANDLE)::_beginthreadex(NULL, NULL, m_function, this, CREATE_SUSPENDED, 0);
	if (INVALID_HANDLE_VALUE == m_hThread || NULL == m_hThread)
	{
		return E_OUTOFMEMORY;
	}
	m_bStopped = false;
	::ResetEvent(m_hEvent);
	::SetThreadPriority(m_hThread, details::Runner_RunPriorityToDword(ePriority));

	m_async_evt.Create();

	::ResumeThread(m_hThread);

	HRESULT hr__ = S_OK;
	return  hr__;
}

HRESULT CCrtRunner::Stop(const bool bForced)
{
	m_async_evt.Destroy();

	if (IsStopped())
		return S_OK;

	m_bStopped = true;

	if (NULL == m_hThread) return S_OK;
	if (bForced) {
		details::Runner_ForceToTerminate(m_hEvent, m_hThread);
	}
	else {
		INT cnt_ = 0;
		while (WAIT_OBJECT_0 != ::WaitForSingleObject(m_hEvent, 200))
		{
			::Sleep(100);
			cnt_ ++;
			if (cnt_ > 10) { // anti-blocker, actually should never happen
				return details::Runner_ForceToTerminate(m_hEvent, m_hThread);
			}
		}
	}
	if (m_hThread)
	{
		::CloseHandle(m_hThread);
		m_hThread = NULL;
	}
	HRESULT hr__ = S_OK;
	return  hr__;
}

HRESULT CCrtRunner::Wait(const DWORD dPeriod)
{
	const DWORD dResult = ::WaitForSingleObject(m_hEvent, (dPeriod < 1 ? INFINITE : dPeriod));
	return (WAIT_OBJECT_0 == dResult ? S_OK : S_FALSE);
}

/////////////////////////////////////////////////////////////////////////////

HANDLE  CCrtRunner::EventHandle(void)const { return m_hEvent; }