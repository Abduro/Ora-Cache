/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Jan-2026 at 01:26:39.207, UTC+4, Batumi, Wednesday;
	Ebo Pack OpenGL drawing context of regular device and of renderer uint test interface implementation file;
*/
#include "ebo_test_$d$.ctx.h"
#include "shared.preproc.h"

#include <crtdbg.h>

using namespace ebo::boo::test::open_gl::draw;

#pragma region cls::c_ctx{}

c_ctx::c_ctx (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb && false) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

c_ctx::~c_ctx (void) {
//	__debugbreak();
//	_out()();
}

void c_ctx::_ctor (void) {
	if (false == this->m_b_verb)
		return;
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += this->Fake_wnd().To_str();
	_out()();
}

void c_ctx::Device (void) {

	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += this->Fake_wnd().To_str();

	if (this->Fake_wnd().Error()) {
		_out()();
		return;
	}

	TRenderer& renderer = ::Get_renderer();

	// the code block below is copied from camera::CWnd ctor;
	CDevice& dev_ref = renderer.Scene().Ctx().Device();
	dev_ref.Target().Source(TString().Format(_T("%s::%s"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__));

	if (__failed(dev_ref.Create(this->Fake_wnd().m_hWnd))) {
		_out() += this->Fake_wnd().Error().Print(TError::e_print::e_req);
	}

	// at the end of this test case the context and renderer objects must be destroyed;
	// otherwise on process exit and calling objects' destructors a lot of errors is thrown;
	renderer.Scene().Ctx().Clear();
	if (renderer.Scene().Ctx().Device().Is_valid())
	    renderer.Scene().Ctx().Device().Destroy();

	_out()();
}

const
CFakeWnd& c_ctx::Fake_wnd (void) const { return this->m_fk_wnd; }
CFakeWnd& c_ctx::Fake_wnd (void)       { return this->m_fk_wnd; }

#pragma endregion