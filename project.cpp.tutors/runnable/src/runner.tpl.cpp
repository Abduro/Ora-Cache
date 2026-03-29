/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Jan-2016 at 3:37:45pm, GMT+7, Phuket, Rawai, Monday;
	This is Shared Lite library system thread pool related class(s) implementation file.
*/
#include "runner.tpl.h"
#include "shared.preproc.h"

using namespace shared::runnable;

#pragma region cls::CThreadCrtData {}

CThreadCrtData:: CThreadCrtData(void) : m_bStopped(false) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CThreadCrtData::~CThreadCrtData(void) {}

TError&  CThreadCrtData::Error (void) const { return this->m_error; }

const
CEvent&  CThreadCrtData::Event (void)const { return this->m_event; }
CEvent&  CThreadCrtData::Event (void)      { return this->m_event; }

bool     CThreadCrtData::IsStopped (void)const { return m_bStopped; }
void     CThreadCrtData::IsStopped (const bool _stop) { m_bStopped = _stop; }

#pragma endregion
#pragma region cls::CThreadBase{}

CThreadBase:: CThreadBase(void) : m_state(CThreadState::eStopped) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CThreadBase::~CThreadBase(void) { if (this->IsRunning()) this->Stop(); }

bool CThreadBase::IsComplete(void) const {
	// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-waitforsingleobject ;
	const dword dwResult = ::WaitForSingleObject(m_crt.EvtObject(), 0);
	switch (dwResult) {
	case WAIT_FAILED   : this->m_error.Last(); break;
	case WAIT_ABANDONED: break;
	case WAIT_TIMEOUT  : break;
	default:; // error object is not set, because everything goes by expected way;
	}
	return (dwResult == WAIT_OBJECT_0);
}

err_code CThreadBase::MarkToStop(void) {
	m_crt.IsStopped(true);
	err_code hr_ = __s_ok;
	return  hr_;
}

err_code CThreadBase::Start(void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (this->IsRunning()) {
		return this->m_error <<(err_code) TErrCodes::eExecute::eState = _T("#__e_inv_state: worker thread is already running");
	}

	m_crt.IsStopped(false);
	::ResetEvent(m_crt.EvtObject());

	if (!CThreadPool::QueueUserWorkItem(&CThreadBase::ThreadFunction, this))
		hr_ = __LastErrToHresult();
	
	if (SUCCEEDED(hr_))
		m_state = CThreadState::eWorking;
	else
		m_state = CThreadState::eError;

	return hr_;
}

err_code    CThreadBase::Stop (void) {
	err_code hr_ = __s_ok;

	if (this->IsRunning() == false) {
		hr_ = __DwordToHresult(ERROR_INVALID_STATE);
		return hr_;
	}
	m_crt.IsStopped(true);

	const DWORD dwResult = ::WaitForSingleObject(m_crt.EvtObject(), INFINITE);

	if (dwResult != WAIT_OBJECT_0)
		hr_ = __LastErrToHresult();
	
	if (SUCCEEDED(hr_))
		m_state = CThreadState::eStopped;
	else
		m_state = CThreadState::eError;

	return hr_;
}

/////////////////////////////////////////////////////////////////////////////

const bool  CThreadBase::IsRunning(void) const 
{
	bool bRunning = false;
	{
		Safe_Lock(m_lock);
		bRunning = !!(CThreadState::eWorking & m_state);
	}
	return bRunning;
}

const bool  CThreadBase::IsValid(void) const
{
	return (m_crt.IsValid());
}

const DWORD CThreadBase::State(void) const
{
	DWORD state_ = 0;
	{
		Safe_Lock(m_lock);
		state_ =  m_state;
	}
	return state_;
}