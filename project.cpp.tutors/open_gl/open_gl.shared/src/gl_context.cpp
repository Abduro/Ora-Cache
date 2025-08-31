/*
	Created by Tech_dog (ebontrop@gmail.com) on 31-Aug-2025 at 12:33:39.591, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL tutorials' context base interface implementation file;
*/
#include "gl_context.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::context;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl {

}}}}

using namespace ex_ui::draw::open_gl::_impl;

context::CBase:: CBase (void) { this->m_error() >> __CLASS__ << __METHOD__ << __e_not_inited; }
context::CBase::~CBase (void) {}

err_code context::CBase::CreateAttsArb (HDC _h_dc, HGLRC _h_shared_ctx, const int* p_att_lst) {
	_h_dc; _h_shared_ctx; p_att_lst;
	return __e_not_impl;
}

TErr_ex& context::CBase::Error (void) const { return this->m_error; }