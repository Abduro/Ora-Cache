/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-Nov-2021 at 1:20:56.2382245 am, UTC+7, Novosibirsk, Wednesday;
	This is Ebo Pack UIX window frame message handler adapter base interface implementation file.
*/
#include "handler.frame.h"

using namespace ex_ui::message::handlers;
using namespace ex_ui::message::handlers::frame;

/////////////////////////////////////////////////////////////////////////////

CHandler:: CHandler (void) : TBase(){ TBase::m_error >> __CLASS__ << __METHOD__; }
CHandler:: CHandler (const CHandler& _ref) : CHandler() { *this = _ref; }
CHandler:: CHandler (CHandler&& _src) : CHandler() { *this = _src; }
CHandler::~CHandler (void) {}

/////////////////////////////////////////////////////////////////////////////

l_result   CHandler::OnActivate (uint32_t, w_param _w_param, l_param _l_param, int32_t& _b_handled) {
	_b_handled = __s_ok;
	l_result l_result = 0;

	SAFE_LOCK(TBase::m_guard);

	for (TFrameEvtListeners::iterator it_ = m_sinks.begin (); it_ != m_sinks.end (); ++it_) {
		IFrameEventSink* const pSink = *it_;
		if (0 == pSink)
			continue;

		err_code n_result = pSink->IEvtFrame_OnActivate(_w_param, _l_param);
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

l_result   CHandler::OnChanged (uint32_t, w_param _w_param, l_param _l_param, int32_t& _b_handled) {
	_b_handled = __s_ok;
	l_result l_result = 0;

	SAFE_LOCK(TBase::m_guard);

	for (TFrameEvtListeners::iterator it_ = m_sinks.begin (); it_ != m_sinks.end (); ++it_) {
		IFrameEventSink* const pSink = *it_;
		if (0 == pSink)
			continue;

		err_code n_result = pSink->IEvtFrame_OnChanged(_w_param, _l_param);
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

l_result   CHandler::OnChanging (uint32_t, w_param _w_param, l_param _l_param, int32_t& _b_handled) {
	_b_handled = __s_ok;
	l_result l_result = 0;

	SAFE_LOCK(TBase::m_guard);

	for (TFrameEvtListeners::iterator it_ = m_sinks.begin (); it_ != m_sinks.end (); ++it_) {
		IFrameEventSink* const pSink = *it_;
		if (0 == pSink)
			continue;

		err_code n_result = pSink->IEvtFrame_OnChanging(_w_param, _l_param);
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

l_result   CHandler::OnEnable (uint32_t, w_param _w_param, l_param _l_param, int32_t& _b_handled) {
	_b_handled = __s_ok;
	l_result l_result = 0;

	SAFE_LOCK(TBase::m_guard);

	for (TFrameEvtListeners::iterator it_ = m_sinks.begin (); it_ != m_sinks.end (); ++it_) {
		IFrameEventSink* const pSink = *it_;
		if (0 == pSink)
			continue;

		err_code n_result = pSink->IEvtFrame_OnEnable(_w_param, _l_param);
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

l_result   CHandler::OnMove (uint32_t, w_param _w_param, l_param _l_param, int32_t& _b_handled) {
	_b_handled = __s_ok;
	l_result l_result = 0;

	SAFE_LOCK(TBase::m_guard);

	for (TFrameEvtListeners::iterator it_ = m_sinks.begin (); it_ != m_sinks.end (); ++it_) {
		IFrameEventSink* const pSink = *it_;
		if (0 == pSink)
			continue;

		err_code n_result = pSink->IEvtFrame_OnMove(_w_param, _l_param);
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

l_result   CHandler::OnMoving (uint32_t, w_param _w_param, l_param _l_param, int32_t& _b_handled) {
	_b_handled = __s_ok;
	l_result l_result = 0;

	SAFE_LOCK(TBase::m_guard);

	for (TFrameEvtListeners::iterator it_ = m_sinks.begin (); it_ != m_sinks.end (); ++it_) {
		IFrameEventSink* const pSink = *it_;
		if (0 == pSink)
			continue;

		err_code n_result = pSink->IEvtFrame_OnMoving(_w_param, _l_param);
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

l_result   CHandler::OnSize (uint32_t, w_param _w_param, l_param _l_param, int32_t& _b_handled) {
	_b_handled = __s_ok;
	l_result l_result = 0;

	SAFE_LOCK(TBase::m_guard);

	for (TFrameEvtListeners::iterator it_ = m_sinks.begin (); it_ != m_sinks.end (); ++it_) {
		IFrameEventSink* const pSink = *it_;
		if (0 == pSink)
			continue;

		err_code n_result = pSink->IEvtFrame_OnSize(_w_param, _l_param);
		if (__s_ok == n_result) {
			l_result = true;
			break;
		}
		if (__failed (n_result)) {
			m_error << __METHOD__ << n_result;
			break;
		}
	}

	return  l_result;
}

l_result   CHandler::OnSizing (uint32_t,  w_param _w_param, l_param _l_param, int32_t& _b_handled) {
	_w_param; _l_param; _b_handled = __s_ok;
	l_result l_result = 0;

	SAFE_LOCK(TBase::m_guard);

	for (TFrameEvtListeners::iterator it_ = m_sinks.begin (); it_ != m_sinks.end (); ++it_) {
		IFrameEventSink* const pSink = *it_;
		if (0 == pSink)
			continue;

		err_code n_result = pSink->IEvtFrame_OnSizing(_w_param, _l_param);
		if (__s_ok == n_result) {
			l_result = true;
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

err_code   CHandler::Arrogate (CHandler& _victim) {
	TBase::m_error << __METHOD__ << __s_ok;

	if (SUCCEEDED (_victim.Lock ()) && SUCCEEDED(TBase::Lock()))
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
			TBase::m_error << E_OUTOFMEMORY;
		}
		_victim.Unlock();
		TBase::Unlock();
	}

	return TBase::m_error;
}

err_code   CHandler::Subscribe (IFrameEventSink* _p_sink) {
	TBase::m_error << __METHOD__ << __s_ok;

	if (0 == _p_sink)
		return (TBase::m_error << E_POINTER);

	SAFE_LOCK(TBase::m_guard);

	TFrameEvtListeners::iterator found_ = this->m_sinks.find(_p_sink);
	if (found_ != this->m_sinks.end())
		return (TBase::m_error << __DwordToHresult(ERROR_ALREADY_EXISTS));

	this->m_sinks.insert(_p_sink);

	return TBase::m_error;
}

err_code   CHandler::Unsubscribe (IFrameEventSink* _p_sink) {
	TBase::m_error << __METHOD__ << __s_ok;

	if (0 == _p_sink)
		return (TBase::m_error << E_POINTER);

	SAFE_LOCK(TBase::m_guard);
	
	TFrameEvtListeners::iterator found_ = this->m_sinks.find(_p_sink);
	if (found_ == this->m_sinks.end())
		return (TBase::m_error << __DwordToHresult(ERROR_NOT_FOUND));

	this->m_sinks.erase(found_);

	return TBase::m_error;
}

/////////////////////////////////////////////////////////////////////////////

CHandler&  CHandler::operator = (const CHandler& _ref) {

	CHandler& src_ = const_cast<CHandler&>(_ref);

	this->Arrogate(src_);
	_ref; return *this;
}

CHandler&  CHandler::operator = (CHandler&& _src) {

	this->Arrogate(_src);

	_src; return *this;
}

CHandler&  CHandler::operator << (IFrameEventSink* _p_sink) {
	this->Subscribe(_p_sink);
	return *this;
}

CHandler&  CHandler::operator >> (IFrameEventSink* _p_sink) {
	this->Unsubscribe(_p_sink);
	return *this;
}