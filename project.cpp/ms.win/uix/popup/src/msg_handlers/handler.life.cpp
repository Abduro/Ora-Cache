/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Oct-2021 at 2:19:53.5668134 pm, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack UIX window life cycle message handler base interface implementation file.
*/
#include "handler.life.h"

using namespace ex_ui::message::handlers;
using namespace ex_ui::message::handlers::life;

/////////////////////////////////////////////////////////////////////////////

CHandler:: CHandler (void) : TBase(){ TBase::m_error >> __CLASS__ << __METHOD__; }
CHandler:: CHandler (const CHandler& _ref) : CHandler() { *this = _ref; }
CHandler:: CHandler (CHandler&& _src) : CHandler() { *this = _src; }
CHandler::~CHandler (void) {}

/////////////////////////////////////////////////////////////////////////////

l_result   CHandler::OnClose  (uint32_t, w_param _w_param, l_param _l_param, int32_t& _b_handled) {
	_b_handled = __s_ok;
	l_result l_result = 0;

	Safe_Lock(TBase::m_guard);

	for (TLifeEvtListeners::iterator it_ = m_sinks.begin (); it_ != m_sinks.end (); ++it_) {
		ILifeEvtSink* const pSink = *it_;
		if (0 == pSink)
			continue;

		err_code n_result = pSink->IEvtLife_OnClose(_w_param, _l_param);
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

l_result   CHandler::OnCreate (uint32_t, w_param _w_param, l_param _l_param, int32_t& _b_handled) {
	_b_handled = __s_ok;
	l_result l_result = 0;

	Safe_Lock(TBase::m_guard);

	for (TLifeEvtListeners::iterator it_ = m_sinks.begin (); it_ != m_sinks.end (); ++it_) {
		ILifeEvtSink* const pSink = *it_;
		if (0 == pSink)
			continue;

		err_code n_result = pSink->IEvtLife_OnCreate(_w_param, _l_param);
		if (__s_ok == n_result || _block_creation == n_result) {
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

l_result   CHandler::OnDestroy(uint32_t, w_param _w_param, l_param _l_param, int32_t& _b_handled) {
	_b_handled = __s_ok;
	l_result l_result = 0;

	Safe_Lock(TBase::m_guard);

	for (TLifeEvtListeners::iterator it_ = m_sinks.begin (); it_ != m_sinks.end (); ++it_) {
		ILifeEvtSink* const pSink = *it_;
		if (0 == pSink)
			continue;

		err_code n_result = pSink->IEvtLife_OnDestroy(_w_param, _l_param);
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

err_code   CHandler::Subscribe (ILifeEvtSink* _p_sink) {
	TBase::m_error << __METHOD__ << __s_ok;

	if (0 == _p_sink)
		return (TBase::m_error << __e_pointer);

	Safe_Lock(TBase::m_guard);

	TLifeEvtListeners::iterator found_ = this->m_sinks.find(_p_sink);
	if (found_ != this->m_sinks.end())
		return (TBase::m_error << (err_code)TErrCodes::eObject::eExists);

	this->m_sinks.insert(_p_sink);

	return TBase::m_error;
}

err_code   CHandler::Unsubscribe (ILifeEvtSink* _p_sink) {
	TBase::m_error << __METHOD__ << __s_ok;

	if (0 == _p_sink)
		return (TBase::m_error << __e_pointer);

	Safe_Lock(TBase::m_guard);
	
	TLifeEvtListeners::iterator found_ = this->m_sinks.find(_p_sink);
	if (found_ == this->m_sinks.end())
		return (TBase::m_error << (err_code)TErrCodes::eObject::eNotFound);

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

CHandler&  CHandler::operator << (ILifeEvtSink* _p_sink) {
	this->Subscribe(_p_sink);
	return *this;
}

CHandler&  CHandler::operator >> (ILifeEvtSink* _p_sink) {
	this->Unsubscribe(_p_sink);
	return *this;
}