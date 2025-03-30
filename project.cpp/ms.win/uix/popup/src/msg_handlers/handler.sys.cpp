/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-Nov-2021 at 9:35:30.7682246 am, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack UIX window system message handler adapter base interface implementation file.
*/
#include "handler.sys.h"

using namespace ex_ui::message::handlers;

/////////////////////////////////////////////////////////////////////////////

CMsgSystem:: CMsgSystem (void) : TBase(){ TBase::m_error >> __CLASS__ << __METHOD__; }
CMsgSystem:: CMsgSystem (const CMsgSystem& _ref) : CMsgSystem() { *this = _ref; }
CMsgSystem:: CMsgSystem (CMsgSystem&& _src) : CMsgSystem() { *this = _src; }
CMsgSystem::~CMsgSystem (void) {}

/////////////////////////////////////////////////////////////////////////////

l_result CMsgSystem::OnSetting(uint32_t, w_param _w_param, l_param _l_param, int32_t& _b_handled) {
	_b_handled = __s_ok;
	l_result l_result = 0;

	SAFE_LOCK(TBase::m_guard);

	for (TMsgSysListeners::iterator it_ = m_sinks.begin (); it_ != m_sinks.end (); ++it_) {
		IMsgSysEventSink* const pSink = *it_;
		if (0 == pSink)
			continue;

		err_code n_result = pSink->IEvtSys_OnSetting(_w_param, _l_param);
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

l_result CMsgSystem::OnSysCmd (uint32_t, w_param _w_param, l_param _l_param, int32_t& _b_handled) {
	_b_handled = __s_ok;
	l_result l_result = 0;

	SAFE_LOCK(TBase::m_guard);

	for (TMsgSysListeners::iterator it_ = m_sinks.begin (); it_ != m_sinks.end (); ++it_) {
		IMsgSysEventSink* const pSink = *it_;
		if (0 == pSink)
			continue;

		err_code n_result = pSink->IEvtSys_OnSysCmd(_w_param, _l_param);
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

l_result CMsgSystem::OnThemed (uint32_t, w_param _w_param, l_param _l_param, int32_t& _b_handled) {
	_b_handled = __s_ok;
	l_result l_result = 0;

	SAFE_LOCK(TBase::m_guard);

	for (TMsgSysListeners::iterator it_ = m_sinks.begin (); it_ != m_sinks.end (); ++it_) {
		IMsgSysEventSink* const pSink = *it_;
		if (0 == pSink)
			continue;

		err_code n_result = pSink->IEvtSys_OnThemed(_w_param, _l_param);
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

err_code CMsgSystem::Arrogate (CMsgSystem& _victim) {
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

err_code CMsgSystem::Subscribe (IMsgSysEventSink* _p_sink) {
	TBase::m_error << __METHOD__ << __s_ok;

	if (0 == _p_sink)
		return (TBase::m_error << __e_pointer);

	SAFE_LOCK(TBase::m_guard);

	TMsgSysListeners::iterator found_ = this->m_sinks.find(_p_sink);
	if (found_ != this->m_sinks.end())
		return (TBase::m_error << (err_code)TErrCodes::eObject::eExists);

	this->m_sinks.insert(_p_sink);

	return TBase::m_error;
}

err_code CMsgSystem::Unsubscribe (IMsgSysEventSink* _p_sink) {
	TBase::m_error << __METHOD__ << __s_ok;

	if (0 == _p_sink)
		return (TBase::m_error << __e_pointer);

	SAFE_LOCK(TBase::m_guard);
	
	TMsgSysListeners::iterator found_ = this->m_sinks.find(_p_sink);
	if (found_ == this->m_sinks.end())
		return (TBase::m_error << (err_code)TErrCodes::eObject::eNotFound);

	this->m_sinks.erase(found_);

	return TBase::m_error;
}

/////////////////////////////////////////////////////////////////////////////

CMsgSystem&  CMsgSystem::operator = (const CMsgSystem& _ref) {

	CMsgSystem& src_ = const_cast<CMsgSystem&>(_ref);

	this->Arrogate(src_);
	_ref; return *this;
}

CMsgSystem&  CMsgSystem::operator = (CMsgSystem&& _src) {

	this->Arrogate(_src);

	_src; return *this;
}

CMsgSystem&  CMsgSystem::operator << (IMsgSysEventSink* _p_sink) {
	this->Subscribe(_p_sink);
	return *this;
}

CMsgSystem&  CMsgSystem::operator >> (IMsgSysEventSink* _p_sink) {
	this->Unsubscribe(_p_sink);
	return *this;
}