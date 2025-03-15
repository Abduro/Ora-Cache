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

using namespace shared::runnable;
using namespace shared::sys_core;

/////////////////////////////////////////////////////////////////////////////

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
/////////////////////////////////////////////////////////////////////////////

CMarshaller::CMarshaller(IGenericEventNotify& sink_ref, const _variant_t& v_evt_id) : m_handler(nullptr) {
	try
	{
		m_handler = new _impl::CMessageHandler(sink_ref, v_evt_id);
	}
	catch(::std::bad_alloc&){}
}

CMarshaller::~CMarshaller(void) {
	Destroy();
}

/////////////////////////////////////////////////////////////////////////////

err_code  CMarshaller::Create(void)
{
	if (!m_handler)
		return __e_not_inited;

	if (__handler_ptr()->IsWindow())
		return __s_ok;

	__handler_ptr()->Create(HWND_MESSAGE);
	return (__handler_ptr()->IsWindow() ? __s_ok : HRESULT_FROM_WIN32(::GetLastError()));
}

err_code  CMarshaller::Destroy(void)
{
	if (!m_handler)
		return __e_not_inited;

	if (!__handler_ptr()->IsWindow())
		return __s_ok;

	if (__handler_ptr()->DestroyWindow())
		__handler_ptr()->m_hWnd = nullptr;
	else
	{
		CError err_obj; err_obj.Last();
		ATLASSERT(0);
	}
	try
	{
		delete m_handler; m_handler = nullptr;
	}
	catch(...){return E_OUTOFMEMORY;}
	return __s_ok;
}

HWND     CMarshaller::GetHandle_Safe(void) const
{
	if (!m_handler)
		return nullptr;
	return (__handler_ptr()->IsWindow() ? __handler_ptr()->m_hWnd : nullptr);
}

/////////////////////////////////////////////////////////////////////////////

err_code  CMarshaller::Fire(const bool bAsynch)
{
	const HWND hHandler = this->GetHandle_Safe();
	return CMarshaller::Fire(hHandler, bAsynch);
}

/////////////////////////////////////////////////////////////////////////////

err_code  CMarshaller::Fire2(void)
{
	const HWND  hHandler = this->GetHandle_Safe();
	if (nullptr == hHandler)
		return OLE_E_INVALIDHWND;
	if (!::PostThreadMessage(
			__handler_ptr()->_OwnerThreadId(),
			_impl::CMessageHandler::eInternalMsgId,
			0,
			0
		))
		return __HRESULT_FROM_WIN32(::GetLastError());
	err_code hr_ = __s_ok;
	return  hr_;
}

/////////////////////////////////////////////////////////////////////////////

err_code  CMarshaller::Fire(const HWND hHandler, const bool bAsynch)
{
	if (!::IsWindow(hHandler))
		return __e_hwnd;

	if (bAsynch)
		::PostMessage(hHandler, _impl::CMessageHandler::eInternalMsgId, (WPARAM)0, (LPARAM)0);
	else
		::SendMessage(hHandler, _impl::CMessageHandler::eInternalMsgId, (WPARAM)0, (LPARAM)0);
	return __s_ok;
}

/////////////////////////////////////////////////////////////////////////////

CDelayEvent:: CDelayEvent(const d_word nTimeSlice, const d_word nTimeFrame):
	m_nTimeSlice(nTimeSlice), m_nTimeFrame(nTimeFrame), m_nCurrent(0) {
	ATLASSERT(m_nTimeSlice);
	ATLASSERT(m_nTimeFrame);
}

CDelayEvent::~CDelayEvent(void) {}

/////////////////////////////////////////////////////////////////////////////

bool CDelayEvent::Elapsed(void) const { return (m_nCurrent >= m_nTimeFrame); }
bool CDelayEvent::IsReset(void) const { return (m_nCurrent == 0); }

VOID CDelayEvent::Reset  (const d_word nTimeSlice, const d_word nTimeFrame)
{
	if (0 < nTimeSlice) m_nTimeSlice = nTimeSlice; ATLASSERT(m_nTimeSlice);
	if (0 < nTimeFrame) m_nTimeFrame = nTimeFrame; ATLASSERT(m_nTimeFrame);

	m_nCurrent = 0;
}

void CDelayEvent::Wait(void) {
	::Sleep(m_nTimeSlice);
	m_nCurrent += m_nTimeSlice;
}

/////////////////////////////////////////////////////////////////////////////

CDelayEvent& CDelayEvent::operator= (const d_word _v) { if (_v) { m_nTimeFrame = _v; }  return *this; }