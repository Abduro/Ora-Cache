/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Jan-2026 at 01:26:39.207, UTC+4, Batumi, Wednesday;
	Ebo Pack OpenGL drawing context of regular device and of renderer uint test interface implementation file;
*/
#include "ebo_test_$d$.ctx.h"
#include "shared.preproc.h"

using namespace ebo::boo::test::open_gl::draw;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl_2 { void __warning_lnk_4006 (void) {}}}}}

#pragma region cls::c_ctx{}

c_ctx::c_ctx (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb && false) {
		_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void c_ctx::_ctor (void) {
	if (false == this->m_b_verb)
		return;
	_out() += TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += this->Ref().To_str();

	_out()();
}

void c_ctx::Device (void) {
	this->_ctor();
}

const
CFakeWnd& c_ctx::Ref (void) const { return this->m_fk_wnd; }
CFakeWnd& c_ctx::Ref (void)       { return this->m_fk_wnd; }

#pragma endregion