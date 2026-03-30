/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Dec-2010 at 7:21:12pm, GMT+3, Rostov-on-Don, Sunday;
	This is SFX project Asynchronous notifying/Wait Object interface implementation file.
	-----------------------------------------------------------------------------
	Adopted to Pulsepay Server project on 2-May-2012 at 1:20:12pm, GMT+3, Rostov-on-Don, Wednesday;
	Adopted to Platinum Clocking project on 19-Mar-2014 at 11:21:09am, GMT+3, Taganrog, Wednesday;
	Adopted to E-Opinion project on 8-May-2014 at 7:20:22am, GMT+3, Saint-Petersburg, Thursday;
	Adopted to Internext project on 20-Aug-2014 at 8:0*:**pm, GMT+3, Taganrog, Wednesday;
	Adopted to Fake GPS project on 11-Dec-2019 at 8:02:19p, UTC+7, Novosibirsk, Wednesday;
*/
#include "run.event.h"
#include "shared.preproc.h"

using namespace shared::runnable;
using namespace shared::sys_core;

#pragma region cls::CEvent{}

static uint32_t u_evt_count = 0;

CEvent:: CEvent (void) : m_event(0) {
	this->m_name.Format(_T("cls::[%s]_#%u"), (_pc_sz)__CLASS__, ++u_evt_count); this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("#__e_not_inited: the event object is not created"); }
CEvent::~CEvent (void) { if (this->Is_valid()) this->Destroy(); u_evt_count--; }

err_code CEvent::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Is_valid())
		return this->m_error << (err_code) TErrCodes::eObject::eInited = _T("#__e_inv_state: event object is already created");

	// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createeventw ;
	// https://learn.microsoft.com/en-us/windows/win32/sync/using-event-objects ;
	
	if (0 == (m_event = ::CreateEvent(nullptr, true, false, this->Name()))) // it is expected the name of the event is unique, no check for ERROR_ALREADY_EXISTS;
		this->m_error.Last();

	return this->Error();
}

err_code CEvent::Destroy (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (false == this->Is_valid())
		return this->m_error << (err_code) TErrCodes::eExecute::eState = _T("#__e_inv_state: the event object is not created yet");
	{
		// https://learn.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-closehandle ;
		if (0 == ::CloseHandle(m_event))
			this->m_error.Last();
		else
			m_event = 0;
	}
	return this->Error();
}

TError&  CEvent::Error (void) const {return this->m_error; }
bool  CEvent::Is_valid (void) const {
	return 0 != this->m_event && __e_handle != this->m_event;
}

_pc_sz CEvent::Name (void) const { return this->m_name.GetString(); }

bool  CEvent::Is_signaled (void) const { return this->Wait(0); }

err_code CEvent::Signaled (const bool _yes_or_no) {
	_yes_or_no;
	this->m_error <<__METHOD__<<__s_ok;

	if (false == this->Is_valid())
		return this->m_error <<__e_not_inited = _T("#__e_not_inited: event object is not created yet");

	const bool b_signaled = this->Is_signaled();
	if (this->Error())
		return this->Error();

	if (true == b_signaled && true == _yes_or_no)
		return this->m_error <<(err_code) TErrCodes::eExecute::eState = _T("#__e_inv_state: the event is already set to signaled state");
	if (false == b_signaled && false == _yes_or_no)
		return this->m_error <<(err_code) TErrCodes::eExecute::eState = _T("#__e_inv_state: the event is already set to nonsignaled state");

	if (_yes_or_no) {
		// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-setevent ;
		if (0 == ::SetEvent(this->m_event))
			this->m_error.Last();
	}
	else {
		// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-resetevent ;
		if (0 == ::ResetEvent(this->m_event))
			this->m_error.Last();
	}
	return this->Error();
}

bool CEvent::Wait (const uint32_t _u_timeout) const {
	_u_timeout;
	// https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-waitforsingleobject ;
	const dword n_result = ::WaitForSingleObject(this->m_event, _u_timeout);

	switch (n_result) {
	case WAIT_FAILED   : this->m_error.Last(); break;
	case WAIT_ABANDONED:
	case WAIT_TIMEOUT  :
	case WAIT_OBJECT_0 :
	default:; // error object is not set, because everything goes by expected way;
	}
	return (WAIT_OBJECT_0 == n_result);
}

CEvent& CEvent::operator <<(const bool _yes_or_no) { this->Signaled(_yes_or_no); return *this; }

const
HANDLE& CEvent::operator ()(void) const { return this->m_event; }
HANDLE& CEvent::operator ()(void)       { return this->m_event; }

#pragma endregion

namespace shared { namespace runnable { namespace _impl
{
	class CMessageHandler:
		public ::ATL::CWindowImpl<CMessageHandler>
	{
	public:
		enum {
			eInternalMsgId = WM_USER + 1,
		};
	private:
		IGenericEventNotify& m_sink_ref;
		const _variant_t     m_event_id;
		d_word               m_threadId;
	public:
		BEGIN_MSG_MAP(CMessageHandler)
			MESSAGE_HANDLER(CMessageHandler::eInternalMsgId, OnGenericEventNotify)
		END_MSG_MAP()
	private:
		virtual LRESULT  OnGenericEventNotify(_uint, w_param, l_param, _bool&)
		{
			err_code hr_ = (TErrCodes::eExecute::eState);
			if (__failed(hr_)) hr_ = m_sink_ref.GenEvt_OnNotify(m_event_id);
			if (__failed(hr_)) hr_ = m_sink_ref.GenEvt_OnNotify((LONG)m_event_id);
			return 0;
		}
	public:
		CMessageHandler(IGenericEventNotify& sink_ref, const _variant_t& v_evt_id):
			m_sink_ref(sink_ref),
			m_event_id(v_evt_id),
			m_threadId(::GetCurrentThreadId())
		{
		}
		virtual ~CMessageHandler(void)
		{
		}
	public:
		d_word  _OwnerThreadId(void)const
		{
			return m_threadId;
		}
	};
}}}

#define __handler_ptr()  reinterpret_cast<_impl::CMessageHandler*>(this->m_handler)

#pragma region cls::CMarshaller{}

static _pc_sz p_err_inv_handler = _T("#__e_handler: the message handler is invalid");
static _pc_sz p_err_wnd_not_inited = _T("#__e_not_inited: message window is not created");

CMarshaller:: CMarshaller (IGenericEventNotify& sink_ref, const _variant_t& v_evt_id) : m_handler(nullptr) {
	this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = p_err_wnd_not_inited;
	try {
		m_handler = new _impl::CMessageHandler(sink_ref, v_evt_id);
	}
	catch(::std::bad_alloc&){ this->m_error <<__e_no_memory = _T("#__e_fail: message handler creation is failed"); }
}

CMarshaller::~CMarshaller (void) {
	Destroy();
}

err_code  CMarshaller::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == m_handler)
		return this->m_error << __e_not_inited = p_err_inv_handler;

	if (true == this->Is_valid())
		return this->m_error << __e_not_inited = _T("#__e_not_inited: the marshaller is already created");

	__handler_ptr()->Create(HWND_MESSAGE);
	if (false == this->Is_valid())
		this->m_error.Last();

	return this->Error();
}

err_code  CMarshaller::Destroy (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == m_handler)
		return this->m_error << __e_not_inited = p_err_inv_handler;
	// in case of getting an error while destroying message-only window there is no way to return from this function,
	// otherwise the pointer of handler object will be not deleted: memory leak is guaranteed;
	if (false == this->Is_valid())
		this->m_error << __e_not_inited = _T("#__e_not_inited: the marshaller is not created"); // this error can be overwritten too;

	if (__handler_ptr()->DestroyWindow())
		__handler_ptr()->m_hWnd = nullptr;
	else this->m_error.Last(); // this error may be overwritten in case of getting the error while deleting the handler object;

	try {
		delete m_handler; m_handler = nullptr;
	}
	catch(...){ this->m_error <<__e_no_memory = _T("#__e_fail: handler object deleting is failed"); }
	return this->Error();
}

err_code  CMarshaller::Fire (const bool _b_async) {
	_b_async;
	this->m_error <<__METHOD__<<__s_ok;
	return CMarshaller::Fire(this->GetHandle_Safe(), this->m_error, _b_async);
}

err_code  CMarshaller::Fire2 (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == m_handler) return this->m_error << __e_not_inited = p_err_inv_handler;
	if (false == this->Is_valid()) return this->m_error << __e_not_inited = p_err_wnd_not_inited;

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-postthreadmessagew ;
	if (0 == ::PostThreadMessage( __handler_ptr()->_OwnerThreadId(), _impl::CMessageHandler::eInternalMsgId, 0, 0 ))
		this->m_error.Last();

	return this->Error();
}

err_code  CMarshaller::Fire (const HWND _h_handler, CError& _err, const bool _b_async) {
	_h_handler; _err; _b_async;

	if (0 == _h_handler || false == !!::IsWindow(_h_handler))
		return _err <<__e_hwnd = _T("#__e_hwnd: window handle is invalid");

	static const uint32_t u_msg_code = _impl::CMessageHandler::eInternalMsgId;

	if (_b_async) {
		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-postmessagew ;
		if (0 == ::PostMessage(_h_handler, u_msg_code, (w_param)0, (l_param)0))
			_err.Last();
	} else {
#if (1)
		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-sendmessagetimeoutw ;
		static const uint32_t u_req_flags = SMTO_NORMAL|SMTO_ERRORONEXIT;
		static const uint32_t u_timeout = 100;

		unsigned __int64 u_result = 0; // the result can contain an error code; it is not handled yet;

		if (0 == ::SendMessageTimeout(_h_handler, u_msg_code, (w_param)0, (l_param)0, u_req_flags, u_timeout, &u_result)) {
			_err.Last();
			if (ERROR_SUCCESS == _err.Code())
				_err <<__e_fail = _T("#__e_fail: generic error occurs");
		}
#else
		::SendMessage(_h_handler, _impl::CMessageHandler::eInternalMsgId, (WPARAM)0, (LPARAM)0);
#endif
	}
	return __s_ok;
}

TError&   CMarshaller::Error (void) const {return this->m_error; }

HWND CMarshaller::GetHandle_Safe (void) const
{
	if (nullptr == m_handler)
		return nullptr;
	return (__handler_ptr()->IsWindow() ? __handler_ptr()->m_hWnd : nullptr);
}

const bool CMarshaller::Is_valid (void) const {
	return nullptr != this->GetHandle_Safe();
}

#pragma endregion
#pragma region cls::CDelayEvent{}

CDelayEvent:: CDelayEvent(const d_word nTimeSlice, const d_word nTimeFrame) : m_nTimeSlice(e_frame::e_na), m_nTimeFrame(e_frame::e_na), m_nCurrent(0) {
	this->Reset(nTimeSlice, nTimeFrame);
}
bool CDelayEvent::Elapsed (void) const { return (m_nCurrent >= m_nTimeFrame); }
bool CDelayEvent::IsReset (void) const { return (m_nCurrent == 0); }

void CDelayEvent::Reset  (const d_word nTimeSlice, const d_word nTimeFrame)
{
	if (0 < nTimeSlice) m_nTimeSlice = nTimeSlice; ATLASSERT(m_nTimeSlice);
	if (0 < nTimeFrame) m_nTimeFrame = nTimeFrame; ATLASSERT(m_nTimeFrame);

	m_nCurrent = 0;
}

void CDelayEvent::Wait(void) {
	::Sleep(m_nTimeSlice);
	m_nCurrent += m_nTimeSlice;
}

CDelayEvent& CDelayEvent::operator <<(const d_word _v) { if (_v) { this->m_nTimeFrame = _v; }  return *this; }

#pragma endregion