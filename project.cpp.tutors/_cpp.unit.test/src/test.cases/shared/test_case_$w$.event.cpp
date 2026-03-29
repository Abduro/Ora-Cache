/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Mar-2026 at 00:49:46.026, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' thread pool event wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$w$.event.h"

using namespace ebo::boo::test::thread;

#pragma region cls::CTstEvent{}

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

const
CEvent& CTstEvent::operator ()(void) const { return this->m_event; }
CEvent& CTstEvent::operator ()(void)       { return this->m_event; }

#pragma endregion