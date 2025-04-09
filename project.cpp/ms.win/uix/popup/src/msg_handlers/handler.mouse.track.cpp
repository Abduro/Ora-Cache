/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Oct-2024 at 15:14:06.972, UTC+4, Batumi, Monday;
	This is Ebo Pack shared mouse movement track interface implementation file;
*/
#include "handler.mouse.track.h"

using namespace ex_ui::message::handlers;
using namespace ex_ui::message::handlers::mouse;

/////////////////////////////////////////////////////////////////////////////

CTrackHandler:: CTrackHandler (void) : TBase(), m_bTracked(false), m_bTurnedOn(false), m_track_data{0} {}
CTrackHandler:: CTrackHandler (const CTrackHandler& _ref) : CTrackHandler() { *this = _ref; }
CTrackHandler:: CTrackHandler (CTrackHandler&& _src) : CTrackHandler() { *this = _src; }
CTrackHandler::~CTrackHandler (void) {}

/////////////////////////////////////////////////////////////////////////////

l_result CTrackHandler::OnMouseHover(uint32_t, w_param _w_param, l_param _l_param, int32_t& _b_handled) {
	_b_handled = __s_ok;
	l_result l_result = 0;

	Safe_Lock(TBase::m_guard);

	for (TTrackEvtListeners::iterator it_ = m_sinks.begin (); it_ != m_sinks.end (); ++it_) {
		ITrackEventSink* const pSink = *it_;
		if (0 == pSink)
			continue;

		err_code n_result = pSink->IEvtMouse_OnHover(_w_param, _l_param);
		if (__s_ok == n_result) {
			_b_handled = true;
			break;
		}
		if (__failed (n_result)) {
			m_error << __METHOD__ << n_result;
			break;
		}
	}

	return  l_result;
}

l_result CTrackHandler::OnMouseMove (uint32_t, w_param _w_param, l_param _l_param, int32_t& _b_handled) {
	_b_handled = __s_ok;
	l_result l_result = 0;

	const bool b_mouse_enter = !this->IsTurned();

	Safe_Lock(TBase::m_guard);

	for (TTrackEvtListeners::iterator it_ = m_sinks.begin (); it_ != m_sinks.end (); ++it_) {
		ITrackEventSink* const pSink = *it_;
		if (0 == pSink)
			continue;

		err_code n_result = pSink->IEvtMouse_OnMove(_w_param, _l_param);
		if (__s_ok == n_result) {
			_b_handled = true;
			break;
		}
		if (__failed (n_result)) {
			m_error << __METHOD__ << n_result;
			break;
		}

		if (this->IsTurned () && b_mouse_enter) {
			n_result = pSink->IEvtMouse_OnEnter(_w_param, _l_param); // does not matter about returned result yet;
		}
	}

	return  l_result;
}
l_result CTrackHandler::OnMouseOut  (uint32_t, w_param _w_param, l_param _l_param, int32_t& _b_handled) {
	_b_handled = __s_ok;
	l_result l_result = 0;

	Safe_Lock(TBase::m_guard);

	const bool b_mouse_leave = m_bTracked;
	if (b_mouse_leave) {

		m_bTracked = false;

		for (TTrackEvtListeners::iterator it_ = m_sinks.begin (); it_ != m_sinks.end (); ++it_) {
			ITrackEventSink* const pSink = *it_;
			if (0 == pSink)
				continue;

			err_code n_result = pSink->IEvtMouse_OnLeave(_w_param, _l_param);
			if (__s_ok == n_result) {
				_b_handled = true;
				break;
			}
			if (__failed (n_result)) {
				m_error << __METHOD__ << n_result;
				break;
			}
		}
	}

	return  l_result;
}

l_result CTrackHandler::OnMouseWheel(uint32_t, w_param _w_param, l_param _l_param, int32_t& _b_handled) {
	_b_handled = __s_ok;
	l_result l_result = 0;

	Safe_Lock(TBase::m_guard);

	for (TTrackEvtListeners::iterator it_ = m_sinks.begin (); it_ != m_sinks.end (); ++it_) {
		ITrackEventSink* const pSink = *it_;
		if (0 == pSink)
			continue;

		err_code n_result = pSink->IEvtMouse_OnWheel(_w_param, _l_param);
		if (__s_ok == n_result) {
			_b_handled = true;
			break;
		}
		if (__failed (n_result)) {
			m_error << __METHOD__ << n_result;
			break;
		}
	}

	return  l_result;
}

/////////////////////////////////////////////////////////////////////////////

err_code CTrackHandler::Arrogate (CTrackHandler& _victim) {
	TBase::m_error << __METHOD__ << __s_ok;

	if (__succeeded (_victim.Lock ()) && __succeeded(TBase::Lock()))
	{
		if (this->m_sinks.empty() == false)
			this->m_sinks.clear();

		try {
			if (_victim.m_sinks.empty() == false) {
				::std::copy(_victim.m_sinks.begin(), _victim.m_sinks.end(), ::std::inserter(this->m_sinks, this->m_sinks.begin()));
			}
			_victim.m_sinks.clear();
		}
		catch (const ::std::bad_alloc&)
		{
			TBase::m_error << __e_no_memory;
		}
		_victim.Unlock();
		TBase::Unlock();
	}

	return TBase::m_error;
}

err_code CTrackHandler::Subscribe (ITrackEventSink* _p_sink) {
	TBase::m_error << __METHOD__ << __s_ok;

	if (0 == _p_sink)
		return (TBase::m_error << __e_pointer);

	Safe_Lock(TBase::m_guard);

	TTrackEvtListeners::iterator found_ = this->m_sinks.find(_p_sink);
	if (found_ != this->m_sinks.end())
		return (TBase::m_error << (err_code)TErrCodes::eObject::eExists);

	this->m_sinks.insert(_p_sink);

	return TBase::m_error;
}

err_code CTrackHandler::Unsubscribe (ITrackEventSink* _p_sink) {
	TBase::m_error << __METHOD__ << __s_ok;

	if (0 == _p_sink)
		return (TBase::m_error << __e_pointer);

	Safe_Lock(TBase::m_guard);
	
	TTrackEvtListeners::iterator found_ = this->m_sinks.find(_p_sink);
	if (found_ == this->m_sinks.end())
		return (TBase::m_error << (err_code)TErrCodes::eObject::eNotFound);

	this->m_sinks.erase(found_);

	return TBase::m_error;
}

/////////////////////////////////////////////////////////////////////////////

HWND     CTrackHandler::Target   (void) const { return this->m_track_data.hwndTrack; }
err_code CTrackHandler::Target   (CONST HWND _target) {
	m_error << __METHOD__ << __s_ok;

	if (0 == _target || false == !!::IsWindow(_target))
		return (m_error << __e_hwnd);

	if (this->IsTurned())
		this->IsTurned(false);

	this->m_track_data.hwndTrack = _target;

	return m_error;
}

bool     CTrackHandler::IsTurned (void) const { return m_bTurnedOn; }
err_code CTrackHandler::IsTurned (const bool _b_on_off) {
	m_error << __METHOD__ << __s_ok;

	if (0 == m_track_data.hwndTrack || false == !!::IsWindow(m_track_data.hwndTrack))
		return (m_error << __e_not_inited);

	if (_b_on_off == this->IsTurned())
		return (m_error << (err_code)TErrCodes::eExecute::eState);

	// https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-trackmouseevent ;
	if (false == _b_on_off) {

		m_track_data.dwFlags |= TME_CANCEL;
		if (!::TrackMouseEvent (&m_track_data)) {
			m_error.Last();
		}
		else
			this->m_bTurnedOn = _b_on_off;
	}
	else
	{
		// it is assumed a target window handle is already set;
		m_track_data.cbSize      = sizeof(TRACKMOUSEEVENT);
		m_track_data.dwFlags     = TME_HOVER | TME_LEAVE /*| TME_NONCLIENT*/;
		m_track_data.dwHoverTime = HOVER_DEFAULT;

		if (!::TrackMouseEvent (&m_track_data)) {
			m_error.Last();
		}
		else
			this->m_bTurnedOn = _b_on_off;
	}

	return m_error;
}

/////////////////////////////////////////////////////////////////////////////

CTrackHandler& CTrackHandler::operator = (const CTrackHandler& _ref) {
	
	CTrackHandler& src_ = const_cast<CTrackHandler&>(_ref);

	this->Arrogate(src_);
	
	return *this;
}

CTrackHandler& CTrackHandler::operator = (CTrackHandler&& _src) {

	this->Arrogate(_src);

	return *this;
}

CTrackHandler& CTrackHandler::operator <<(ITrackEventSink* _p_sink) {
	this->Subscribe(_p_sink);
	return *this;
}

CTrackHandler& CTrackHandler::operator >>(ITrackEventSink* _p_sink) {
	this->Unsubscribe(_p_sink);
	return *this;
}