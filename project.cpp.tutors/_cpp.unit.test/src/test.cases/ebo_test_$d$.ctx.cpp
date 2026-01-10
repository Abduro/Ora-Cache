/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Jan-2026 at 01:26:39.207, UTC+4, Batumi, Wednesday;
	Ebo Pack OpenGL drawing context of regular device and of renderer uint test interface implementation file;
*/
#include "ebo_test_$d$.ctx.h"
#include "shared.preproc.h"

#include <crtdbg.h>

using namespace ebo::boo::test::open_gl::draw;

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw { namespace _impl {
}}}}}}


#pragma region cls::c_ctx{}

c_ctx::c_ctx (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb && false) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

c_ctx::~c_ctx (void) {
//	__debugbreak(); it very looks like running *each* test case method creates its own *new* copy of this class;
//	_out()();       thus other event handlers' macros should be used those are executed *before* and *after* running the test case;
}

void c_ctx::OnClean (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out()();
}

void c_ctx::OnInit (void) {
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out()();
}

void c_ctx::_ctor (void) {
	if (false == this->m_b_verb)
		return;
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out()();
}

void c_ctx::Device (void) {

	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	
	CBuilder builder;

	builder.Device().Create(); // the error and result are output by builder itself;
	builder.Device().Delete();

	_out()();
}

void c_ctx::Graphics (void) {

	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CBuilder builder;

	const bool b_error = false; // if is set to 'true' the error part of this test case throws the error;
	if (b_error) {
		builder.Graph().Create(nullptr);
		builder.Graph().Delete();
	}
	else if (__failed(builder.Device().Create())) { /*nothing to test;*/ }
	else if (__failed(builder.Graph().Create(builder.Device().Window().m_hWnd)))  { /*nothing to test;*/ }
	else {
		builder.Graph().Delete();
		builder.Device().Delete();
	}
	_out()();
}

#pragma endregion