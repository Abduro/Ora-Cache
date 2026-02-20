/*
	Created by Tech_dog (ebontrop@gmail.com) on 4-Jan-2019 at 0:15:35a, UTC+7, Novosibirsk, Thursday;
	This is Ebo Pack shared lite library waitable timer interface implementation file.
	-----------------------------------------------------------------------------
	Original file is created for SfxSOA common timer object on 8-Dec-2010 at 2:01:24am, GMT+3, Rostov-on-Don, Wednesday;
*/
#include "shared.timer.h"
#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace shared::common;
using namespace shared::sys_core;

namespace shared { namespace common { namespace details {

	typedef ::std::map<UINT_PTR, IWaitable_Events*>  TStdTimers;

	//
	// TODO: a map must be thread-safe;
	//
	TStdTimers& CWaitable_StdRef(void) {
		static TStdTimers tm_;
		return tm_;
	}

	class CWaitable_Helper {
	private:
		enum _rs : int32_t {
			e_err  = -1,
			e_none =  0,   // no error;
		};
	public:
		VOID _process_message(void) {
			MSG  msg_ = {0};
			BOOL b_rs = ::GetMessage(&msg_, NULL, 0, 0);

			if ( b_rs == _rs::e_err ) {
				_ASSERTE(FALSE);
				return;
			}
			else if ( b_rs == FALSE ) {
				::PostQuitMessage (0);
			}
			::TranslateMessage(&msg_);
			::DispatchMessage (&msg_);
		}
	public:
		static
		void __stdcall _timer_proc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
			hWnd; uMsg; idEvent; dwTime;
			TStdTimers& tms_ = CWaitable_StdRef();
			if (tms_.empty())
				return;
			TStdTimers::const_iterator it_ = tms_.find(idEvent);
			if (it_ != tms_.end() &&
			    it_->second != nullptr)
				it_->second->IWaitable_OnComplete();
		}
	};

}}}
using namespace shared::common::details;

#pragma region cls::CTimer_Base{}

CTimer_Base:: CTimer_Base(IWaitable_Events& _snk) : m_sink(_snk) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CTimer_Base::~CTimer_Base(void) {}

TError&  CTimer_Base::Error (void) const { return this->m_error; }

#pragma endregion
#pragma region cls::CWaitableTimer{}

CWaitableTimer:: CWaitableTimer(IWaitable_Events& _snk) : TBase(_snk), m_timer(nullptr) { TBase::m_error >>__CLASS__<<__e_not_inited; }
CWaitableTimer::~CWaitableTimer(void) {
	if (nullptr != m_timer) {
		::CloseHandle(m_timer); m_timer = nullptr;
	}
}

bool  CWaitableTimer::IsValid(void) const { return (nullptr != m_timer); }

err_code CWaitableTimer::Delay (const uint32_t _u_ms) {
	_u_ms;
	TBase::m_error <<__METHOD__<<__s_ok;
	//
	// https://en.wikipedia.org/wiki/Nanosecond ;
	//
	// 1,000,000 nanoseconds – one millisecond (ms);
	// 100 ns                - one period;
	// 10, 000 periods       - one millisecond (ms);
	//
	if (_u_ms < 1)
		return (TBase::m_error <<__e_inv_arg);

	if (this->IsValid() == true)
		return TBase::m_error << (err_code) TErrCodes::eObject::eInited;

	// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createwaitabletimerw ;

	m_timer = ::CreateWaitableTimer(nullptr, false, nullptr);
	if (nullptr == m_timer)
		return (TBase::m_error.Last());

	LARGE_INTEGER delay_ = {0};
	delay_.QuadPart = -(_u_ms * 10000LL);

	// https://docs.microsoft.com/en-us/windows/desktop/api/synchapi/nf-synchapi-setwaitabletimer ;

	if (::SetWaitableTimer(m_timer, &delay_, 0, NULL, NULL, FALSE)) {
		bool b_exit = false;
		while ( b_exit == false ) {
			switch ( ::MsgWaitForMultipleObjects(1, &m_timer, FALSE, INFINITE, QS_ALLEVENTS) ) {
			case WAIT_OBJECT_0 + 0: {
					this->Destroy();
					b_exit = true;
				} break;
			case WAIT_OBJECT_0 + 1: {
					CWaitable_Helper()._process_message();
				} break;
			default:
				_ASSERTE(FALSE);
				TBase::m_error << __e_not_expect;
			}
		}
	}
	return TBase::Error();
}

err_code CWaitableTimer::Destroy(void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	if (this->IsValid() == false)
		return (TBase::m_error << __e_not_inited);
	// https://learn.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-closehandle ;
	if (false == !!::CloseHandle(m_timer))
		TBase::m_error.Last();
	else
		m_timer  = nullptr;

	return TBase::Error();
}

#pragma endregion
#pragma region cls::CStdTimer{}

CStdTimer:: CStdTimer (IWaitable_Events& _snk) : TBase(_snk),  m_tm_id(0) { this->m_error >>__CLASS__<<__e_not_inited; }
CStdTimer::~CStdTimer (void) {
	if (this->IsValid())
		this->Destroy();
}

bool CStdTimer::IsValid (void) const { return (0 != m_tm_id); }

err_code CStdTimer::Create (const uint32_t _u_ms) {
	_u_ms;
	TBase::m_error <<__METHOD__<<__s_ok;

	if (0 == _u_ms)
		return (TBase::m_error <<__e_inv_arg);

	if (this->IsValid() == true)
		return (TBase::m_error <<(err_code) TErrCodes::eObject::eExists);

	// learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-settimer ;

	m_tm_id = ::SetTimer(0, 0, _u_ms, CWaitable_Helper::_timer_proc);
	if (0 == m_tm_id)
		return TBase::m_error.Last();
	
	try {
		CWaitable_StdRef()[m_tm_id] = &this->m_sink;
	}
	catch (::std::bad_alloc&) {
		TBase::m_error <<__e_no_memory;
	}

	return TBase::Error();
}

err_code CStdTimer::Destroy(void) {
	TBase::m_error <<__METHOD__<<__s_ok;

	if (this->IsValid() == false)
		return (TBase::m_error <<__e_not_inited);

	if (false == !!::KillTimer(nullptr, m_tm_id))
		TBase::m_error.Last();
	else {
		TStdTimers& tms_ = CWaitable_StdRef();
		if (tms_.empty() == false) { // it is required for safe exit from the app that creates this timer, otherwise access violation error occurs;
			TStdTimers::const_iterator it_ = tms_.find(m_tm_id);
			if (it_ != tms_.end())
				tms_.erase(it_);
		}
		m_tm_id  = 0;
	}
	return TBase::Error();
}

#pragma endregion
#pragma region cls::CChromo{}

using namespace ::std::chrono;

CChrono::CChrono (void) : m_stopped(true) { this->m_pt_start = high_resolution_clock::now(); this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& CChrono::Error (void) const { return this->m_error; }

err_code CChrono::Start (void) {
	this->m_error <<__METHOD__<<__s_ok;

	return this->Error();
}

err_code CChrono::Stop (void) {
	this->m_error <<__METHOD__<<__s_ok;

	return this->Error();
}

#pragma endregion