/*
	Created by Tech_dog (ebontrop@gmail.com) on 5-Nov-2021 at 11:51:16.8950509 pm, UTC+7, Novosibirsk, Friday;
	This is Ebo Pack UIX window draw client area message handler base interface implementation file.
*/
#include "handler.draw.h"

using namespace ex_ui::message::handlers;
using namespace ex_ui::message::handlers::draw;

/////////////////////////////////////////////////////////////////////////////

CHandler:: CHandler (void) : TBase() { TBase::m_error >> __CLASS__ << __METHOD__; }
CHandler:: CHandler (const CHandler& _ref) : CHandler() { *this = _ref; }
CHandler:: CHandler (CHandler&& _src) : CHandler() { *this= _src; }
CHandler::~CHandler (void) {}

/////////////////////////////////////////////////////////////////////////////

l_result   CHandler::OnErase  (uint32_t, w_param _w_param, l_param _l_param, int32_t& _b_handled) {
	_b_handled = 0;
	l_result l_result = 0;

	SAFE_LOCK(TBase::m_guard);

	for (TDrawEvtListeners::iterator it_ = m_sinks.begin (); it_ != m_sinks.end (); ++it_) {
		IDrawEventSink* const pSink = *it_;
		if (0 == pSink)
			continue;

		err_code n_result = pSink->IEvtDraw_OnErase(_w_param, _l_param);
		if (__s_ok == n_result) {
			_b_handled = true; l_result = _b_handled;
			break;
		}
		if (__failed (n_result)) {
			m_error << __METHOD__ << n_result;
			break;
		}
	}

	return  l_result;
}

l_result   CHandler::OnPaint  (uint32_t, w_param _w_param, l_param _l_param, int32_t& _b_handled) {
	_b_handled = 0;
	l_result l_result = 0;

	SAFE_LOCK(TBase::m_guard);

	for (TDrawEvtListeners::iterator it_ = m_sinks.begin (); it_ != m_sinks.end (); ++it_) {
		IDrawEventSink* const pSink = *it_;
		if (0 == pSink)
			continue;

		err_code n_result = pSink->IEvtDraw_OnPaint(_w_param, _l_param);
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

err_code   CHandler::Arrogate (CHandler& _victim) {
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

err_code   CHandler::Subscribe (IDrawEventSink* _p_sink) {
	TBase::m_error << __METHOD__ << __s_ok;

	if (0 == _p_sink)
		return (TBase::m_error << __e_pointer);

	SAFE_LOCK(TBase::m_guard);

	TDrawEvtListeners::iterator found_ = this->m_sinks.find(_p_sink);
	if (found_ != this->m_sinks.end())
		return (TBase::m_error << (err_code)TErrCodes::eObject::eExists);

	this->m_sinks.insert(_p_sink);

	return TBase::m_error;
}

err_code   CHandler::Unsubscribe (IDrawEventSink* _p_sink) {
	TBase::m_error << __METHOD__ << __s_ok;

	if (0 == _p_sink)
		return (TBase::m_error << __e_pointer);

	SAFE_LOCK(TBase::m_guard);
	
	TDrawEvtListeners::iterator found_ = this->m_sinks.find(_p_sink);
	if (found_ == this->m_sinks.end())
		return (TBase::m_error << (err_code)TErrCodes::eObject::eNotFound);

	this->m_sinks.erase(found_);

	return TBase::m_error;
}

/////////////////////////////////////////////////////////////////////////////

CHandler&  CHandler::operator = (const CHandler& _ref) {
	CHandler& src_ = const_cast<CHandler&>(_ref);
	this->Arrogate( src_ );
	return *this;
}

CHandler&  CHandler::operator = (CHandler&& _src) {

	this->Arrogate(_src);
	return *this;
}

CHandler&  CHandler::operator << (IDrawEventSink* _p_sink) {

	this->Subscribe(_p_sink);
	return *this;
}
CHandler&  CHandler::operator >> (IDrawEventSink* _p_sink) {

	this->Unsubscribe(_p_sink);
	return *this;
}