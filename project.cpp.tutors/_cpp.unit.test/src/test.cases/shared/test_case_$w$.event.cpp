/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Mar-2026 at 00:49:46.026, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' thread event wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$w$.event.h"

using namespace ebo::boo::test::thread;

#pragma region cls::CTstAwait{}

CTstAwait::~CTstAwait (void) {
	if ((*this)().Event().Is_valid()) {
		_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

		if (__failed((*this)().Event().Destroy())) _out() += (*this)().Event().Error();
		else _out() += TString().Format(_T("[impt] The event object (name = '%s') is destroyed;"), (_pc_sz) (*this)().Event().Name());

		_out()();
	}
}

err_code CTstAwait::Wait (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() +=_T("Creating external event object:");

	if (__failed(this->m_event.Create())) return this->m_event().Error(); // the error is added to output by test case itself;
	if (__failed((*this)().Event().Dup(this->m_event()))) { _out() += (*this)().Event().Error(); return (*this)().Event().Error(); } // this is direct call;
	else _out() += TString().Format(_T("The external event '%s' is duplicated by '%s';"), this->m_event().Name(), (*this)().Event().Name());

	if (__failed((*this)().Delay().Reset(100, 1000))) { _out() += (*this)().Delay().Error(); return (*this)().Delay().Error(); } // this is direct call;
	else _out() += TString().Format(_T("%s;"), (_pc_sz) (*this)().Delay().To_str());

	if (false == (*this)().Is_valid()) { _out() += (*this)().Error(); return (*this)().Error(); } // this is direct call;
	else _out() += TString().Format(_T("[impt] The await object is ready;"));

	uint32_t u_count = 0;

	while (false == (*this)().Event().Is_signaled()) {
		(*this)().Delay().Wait();
		if (false == (*this)().Delay().Elapsed())
			_out() += TString().Format(_T("wait notify #%u;"), ++u_count);
		else {
			_out() += _T("[warn] the time frame is elapsed;");
			(*this)().Event() << true; // this is the signal to stop this iteration;
			(*this)().Delay().Reset();
		}
	}
	_out() += _T("[impt] result: the delaying is ended;");

	return (*this)().Error();
}

const
CAwait& CTstAwait::operator ()(void) const { return this->m_await; }
CAwait& CTstAwait::operator ()(void)       { return this->m_await; }

#pragma endregion
#pragma region cls::CTstEvent{}

CTstEvent::~CTstEvent (void) {
	if ((*this)().Is_valid()) {
		_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

		if (__failed((*this)().Destroy())) _out() += (*this)().Error();
		else _out() += TString().Format(_T("[impt] The event object (name = '%s') is destroyed;"), (_pc_sz) (*this)().Name());

		_out()();
	}
}

err_code CTstEvent::Create (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Create())) { _out() += (*this)().Error(); }
	else { _out() += TString().Format(_T("[impt] result: the event object '%s' is created;"), (*this)().Name()); }

	return (*this)().Error();
}

err_code CTstEvent::Destroy (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Destroy())) { _out() += (*this)().Error(); }
	else { _out() += TString().Format(_T("[impt] result: the event object '%s' is destroyed;"), (*this)().Name()); }

	return (*this)().Error();
}

err_code CTstEvent::Signaled (const bool _b_on_off) {
	_b_on_off;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(_T("Set signaled: '%s';"), TString().Bool(_b_on_off));

	if (__failed((*this)().Signaled(_b_on_off))) { _out() += (*this)().Error(); }
	else { _out() += TString().Format(_T("[impt] result: the event object '%s' state is '%s';"), (*this)().Name(), TString().Bool((*this)().Is_signaled())); }

	return (*this)().Error();
}

const
CEvent& CTstEvent::operator ()(void) const { return this->m_event; }
CEvent& CTstEvent::operator ()(void)       { return this->m_event; }

#pragma endregion
#pragma region cls::CTstListener{}

err_code CTstListener::GenEvt_OnNotify (const _long n_evt_id) {
	n_evt_id;
	_out() += TString().Format(_T("[warn] cls::[%s].%s():#n_evt_id = %u"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, n_evt_id);

	return __s_ok;
}

#pragma endregion
#pragma region cls::CTstNotifier{}

CTstNotifier::CTstNotifier (void) : m_notifier(m_listener, _variant_t((long)1)) {}

err_code CTstNotifier::Create (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Create())) { _out() += (*this)().Error(); }
	else { _out() += _T("[impt] result: the notifier is created;"); }

	return (*this)().Error();
}

err_code CTstNotifier::Destroy (void) {
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed((*this)().Destroy())) { _out() += (*this)().Error(); }
	else { _out() += _T("[impt] result: the notifier is destroyed;"); }

	return (*this)().Error();
}

err_code CTstNotifier::Notify (const bool _b_async) {
	_b_async;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(_T("Async notify: '%s';"), TString().Bool(_b_async));

	const
	err_code n_result = (*this)().Fire(_b_async);

	if (__failed(n_result)) { _out() += (*this)().Error(); }
	else { _out() += TString().Format(_T("[impt] result code: 0x%x; (%d)"), n_result, n_result); }

	return n_result;
}

const
CMarshaller& CTstNotifier::operator ()(void) const { return this->m_notifier; }
CMarshaller& CTstNotifier::operator ()(void)       { return this->m_notifier; }

#pragma endregion