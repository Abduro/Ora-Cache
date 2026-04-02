/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Apr-2026 at 10:41:22.033, UTC+4, Batumi, Thursday;
	This is Ebo Pack runnable library thread wrapper shared interface implementation file;
*/
#include "runner.bas.h"

using namespace shared::runnable::threads;
using e_state = CState::e_state;

#pragma region cls::CState{}

CState:: CState (void) : m_state(e_state::eStopped) {
	this->m_error >>__CLASS__<<__METHOD__<<__s_ok; if (__failed(this->m_event.Create())) this->m_error = this->m_event.Error(); }
CState::~CState (void) { this->m_event.Destroy(); }

TError& CState::Error (void) const { return this->m_error; }
const
CEvent& CState::Event (void) const { return this->m_event; }
CEvent& CState::Event (void)       { return this->m_event; }

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

bool CState::Is_completed (void) { Safe_Lock(this->m_lock);
	const bool b_result = (*this)().Wait(0);

	if ((*this)().Error())
		this->m_error = (*this)().Error();
	else if (b_result)
		this->m_state = e_state::eCompleted;

	return b_result;
}

bool CState::Is_error (void) { return this->Error().Is() ? (this->m_state = e_state::eError) : this->Get(); }

bool CState::Is_running (void) const { return this->Get() == e_state::eWorking; }
#if (0)
bool CState::Is_stopped (void) { Safe_Lock(this->m_lock);
	const bool b_result = (*this)().Wait(INFINITE); // waiting for infinity looks not so good, perhaps a timeout must be defined or be set;

	if ((*this)().Error())
		this->m_error = (*this)().Error();
	else if (b_result)
		this->m_state = e_state::eStopped;

	return b_result;
}
#else
bool CState::Is_stopped (void) const { return this->Get() == e_state::eStopped; }
bool CState::Is_stopped (const bool) { return this->Set(e_state::eStopped); }
#endif
bool CState::Is_valid (void) const {
	
	if (this->Event().Error())
		this->m_error = this->Event().Error();

	return false == this->Error();

}

CLocker& CState::Locker (void) { return this->m_lock; }

CState::operator uint32_t (void) const { return this->Get(); }
const
CEvent&  CState::operator ()(void) const { return this->Event(); }
CEvent&  CState::operator ()(void)       { return this->Event(); }

CState&  CState::operator <<(const e_state _e_curr) { this->Set(_e_curr); return *this; }
TError&  CState::operator <<(TError& _error) { if (_error) { this->m_error = _error; (*this) << e_state::eError; } return _error; }
const
CState&  CState::operator >>(e_state& _out) const { _out = this->Get(); return *this; }

#pragma endregion
#pragma region cls::CThreadBase{}

CThreadBase:: CThreadBase (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CThreadBase::~CThreadBase (void) {}

TError& CThreadBase::Error (void) const { return this->m_error; }
bool CThreadBase::Is_valid (void) const {

	if ((*this)().Is_valid() == false)
		return true != (this->m_error = (*this)().Error()); // the error is set to error state that means it returns 'true' != 'true' >> false;
	else
		return false == this->Error(); // if this error is *not* set to error state, it returns 'false' == 'false' >> result 'true';
}

const
CState& CThreadBase::State (void) const { return this->m_state; }
CState& CThreadBase::State (void)       { return this->m_state; }

_pc_sz  CThreadBase::Cls_name (void) { static CString cs_class = __CLASS__; return (_pc_sz) cs_class; }

const
CState& CThreadBase::operator ()(void) const { return this->State(); }
CState& CThreadBase::operator ()(void)       { return this->State(); }

#pragma endregion