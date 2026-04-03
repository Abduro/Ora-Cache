/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Jan-2016 at 3:37:45pm, GMT+7, Phuket, Rawai, Monday;
	This is Shared Lite library system thread pool related class(s) implementation file.
*/
#include "runner.tpl.h"

using namespace shared::runnable::threads::pool;
using e_state = TThreadState::e_state;

#pragma region cls::CThreadPool{}

template <typename T>
int CThreadPool::QueueUserWorkItem (void (T::*pfn)(void),  T* pObject, ULONG flags/* = CThreadType::eLongOper*/) {
	pObject; flags;
	typedef std::pair<void (T::*)(), T*> CallbackType;
	::std::unique_ptr<CallbackType> ptr_(new CallbackType(pfn, pObject));
	if (::QueueUserWorkItem(ThreadProc<T>, ptr_.get(), flags)) {
		ptr_.release(); // the ownership of the encapsulated pointer is assigned to system procedure;
		return true;
	} else
		return false;
}

template <typename T>
int CThreadPool::QueueUserWorkItemEx (void (T::*pfn)(T*), T* pObject, ULONG flags/* = CThreadType::eLongOper*/) {
	pObject; flags;
	typedef std::pair<void (T::*)(T*), T*> CallbackType;
	::std::unique_ptr<CallbackType> ptr_(new CallbackType(pfn, pObject));

	if (::QueueUserWorkItem(ThreadProcEx<T>, ptr_.get(), flags)) {
		ptr_.release(); // the ownership of the encapsulated pointer is assigned to system procedure;
		return true;
	}
	else
		return false;
}

template <typename T>
dword CThreadPool::ThreadProc(void* _p_context) {
	_p_context;
	typedef std::pair<void (T::*)(), T*> CallbackType;

	::std::unique_ptr<CallbackType> ptr_(static_cast<CallbackType*>(_p_context));

	(ptr_->second->*ptr_->first)();
	return 0;
}

template <typename T>
dword CThreadPool::ThreadProcEx(void* _p_context) {
	_p_context;
	typedef std::pair<void (T::*)(T*), T*> CallbackType;

	::std::unique_ptr<CallbackType> ptr_(static_cast<CallbackType*>(_p_context));

	(ptr_->second->*ptr_->first)(ptr_->second);
	return 0;
}

#pragma endregion
#pragma region cls::CTplRunner{}

CTplRunner:: CTplRunner (void) : TBase() { TBase::m_error >> TString().Format(_T("%s::%s"), TBase::Cls_name(), (_pc_sz)__CLASS__); }
CTplRunner::~CTplRunner (void) { if ((*this)().Is_running()) this->Stop(); }

err_code CTplRunner::Start (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	if (true == (*this)().Is_running()) {
		return TBase::m_error <<(err_code) TErrCodes::eExecute::eState = _T("#__e_inv_state: worker thread is already running");
	}

	(*this)().Event() << false; // sets the event to nonsignal state before running a worker thread;

	if (false == !!CThreadPool::QueueUserWorkItem(&CTplRunner::Run_Func, this)) {
		TBase::m_error.Last(); (*this)() << TBase::Error(); // updates the current state value;
	}
	else {
		(*this)() << e_state::eWorking;
	}
	return TBase::Error();
}

err_code CTplRunner::Stop (void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	if (false == (*this)().Is_running()) { // Is_stopped() is not used here because it queries event object, thus evaluating current state is enough;
		return TBase::m_error <<(err_code) TErrCodes::eExecute::eState = _T("#__e_inv_state: worker thread is not running");
	}
	(*this)().Is_stopped(true);        // lets to 'know' to thread procedure to complete its work;
	(*this)().Event().Wait(dword(-1)); // waits the event state to be signaled by thread procedure;

	return TBase::Error();
}

void CTplRunner::Run_Func (void) {

	CDelay delay(10, 100);

	while (false == (*this)().Is_stopped()) {
		delay.Wait();
		if (delay.Elapsed())
			break;
	}
	(*this)().Event() << true; // sets the event to signal state, i.e. the job is done;
}

#pragma endregion