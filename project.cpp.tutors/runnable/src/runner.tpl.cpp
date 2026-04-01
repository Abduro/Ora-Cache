/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Jan-2016 at 3:37:45pm, GMT+7, Phuket, Rawai, Monday;
	This is Shared Lite library system thread pool related class(s) implementation file.
*/
#include "runner.tpl.h"
#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace shared::runnable::threads;
using e_state = CState::e_state;

#pragma region cls::CBase{}

CBase:: CBase (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CBase::~CBase (void) { if ((*this)().Is_running()) this->Stop(); }

err_code CBase::Start (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (true == (*this)().Is_running()) {
		return this->m_error <<(err_code) TErrCodes::eExecute::eState = _T("#__e_inv_state: worker thread is already running");
	}

	(*this)().Event() << false; // sets the event to nonsignal state before running a worker thread;

	if (false == !!CThreadPool::QueueUserWorkItem(&CBase::ThreadFunction, this)) {
		this->m_error.Last(); (*this)() << this->Error(); // updates the current state value;
	}
	else {
		(*this)() << e_state::eWorking;
	}
	return this->Error();
}

err_code CBase::Stop (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (false == (*this)().Is_running()) { // Is_stopped() is not used here because it queries event object, thus evaluating current state is enough;
		return this->m_error <<(err_code) TErrCodes::eExecute::eState = _T("#__e_inv_state: worker thread is not running");
	}

	const bool b_result = (*this)().Is_stopped();
	if ((*this)().Error())
		this->m_error = (*this)().Error();
	
	else if (b_result) { /*does nothing*/ }
	else { // what is about the case when b_result == false and no error? it needs more clarification, in such case there is nether eError nor eStopped;
		CError unk_err; unk_err >>__CLASS__<<__METHOD__<<__e_not_expect  = _T("#__e_unexpect: thread stop error is unknown");
		__trace_err_3(unk_err); // just trace, no error assigning to this method;
	}

	return this->Error();
}

bool CBase::Is_valid (void) const {

	if ((*this)().Is_valid() == false)
		return true != (this->m_error = (*this)().Error()); // the error is set to error state that means it returns 'true' != 'true' >> false;
	else
		return false == this->Error(); // if this error is *not* set to error state, it returns 'false' == 'false' >> result 'true';
}

const
CState&  CBase::State (void) const { return this->m_state; }
CState&  CBase::State (void)       { return this->m_state; }

#pragma endregion
#pragma region cls::CState{}

CState::CState (void) : m_state(e_state::eStopped) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& CState::Error (void) const { return this->m_error; }

e_state CState::Get (void) const {

	Safe_Lock (this->m_lock);
	const
	e_state e_loc = this->m_state; // makes a local copy;
	return  e_loc;
}
bool CState::Set (const e_state _e_current) {
	Safe_Lock(this->m_lock);
	const bool b_changed = _e_current != this->Get(); if (b_changed) this->m_state = _e_current; return b_changed;
}

bool CState::Is_completed (void) const { Safe_Lock(this->m_lock);
	const bool b_result = (*this)().Wait(0);

	if ((*this)().Error())
		this->m_error = (*this)().Error();
	else if (b_result)
		this->m_state = e_state::eCompleted;

	return b_result;
}

bool CState::Is_error (void) const { return this->Error().Is() ? (this->m_state = e_state::eError) : this->Get(); }

bool CState::Is_running   (void) const { return this->Get() == e_state::eWorking; }
bool CState::Is_stopped   (void) const { Safe_Lock(this->m_lock);
	const bool b_result = (*this)().Wait(INFINITE); // waiting for infinity looks not so good, perhaps a timeout must be defined or be set;

	if ((*this)().Error())
		this->m_error = (*this)().Error();
	else if (b_result)
		this->m_state = e_state::eStopped;

	return b_result;
}

CState::operator uint32_t (void) const { return this->Get(); }

#pragma endregion