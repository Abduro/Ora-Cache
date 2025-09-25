/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Sep-2025 at 13:37:58.720, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' context window interface implementation file;
*/
#include "open_gl_tutor.1.wnd.h"
#include "open_gl_tutor.1.res.h"
#include "shared.preproc.h"
#include "shared.dbg.h"
#include "gl_version.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::context;

context::CWnd:: CWnd (void) : TBase() { TBase::m_error >>__CLASS__; }
context::CWnd::~CWnd (void) { } // parent class object will destroy window created automatically on its (parent) destruction;

err_code context::CWnd::Create (const HWND _h_parent, const t_rect& _rc_wnd_pos, const bool _b_visible) {
	_h_parent; _rc_wnd_pos; _b_visible;
	TBase::m_error << __METHOD__ << __s_ok;

	if (TBase::Is_valid())
		return TBase::m_error << (err_code) TErrCodes::eObject::eExists;

	static _pc_sz p_cls_name = _T("__open_gl_ctx_wnd");

	CWndCls wnd_cls;

	if (__failed(wnd_cls.Register(p_cls_name))) {
		__trace_err_3(_T("%s\n"), (_pc_sz) wnd_cls.Error().Print(TError::e_req));
		return TBase::m_error = wnd_cls.Error();
	}

	TBase::Styles().Default_for_kid();

	if (__failed(TBase::Create(
		p_cls_name, TString().Format(_T("cls::[%s:%s]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__), _rc_wnd_pos, _b_visible, _h_parent
	))) {
		return TBase::Error();
	}	
	return TBase::Error();
}

const
CContext& context::CWnd::Ctx (void) const { return this->m_ctx; }
CContext& context::CWnd::Ctx (void)       { return this->m_ctx; }

err_code  context::CWnd::PostCreate (void) {

	TBase::m_error << __METHOD__ << __s_ok;

	// it is very dependable on the sequence of calling OpenGL functions, especially creating the context and make it current; :(
	int32_t ver_major = CVersion().Major(); if (false == !!ver_major) ver_major = 4;
	int32_t ver_minor = CVersion().Minor(); if (false == !!ver_minor) ver_minor = 6;
	// from the other hand the above statement may be incorrect, due to glGetIntegerv() does not work in expected way in comparison with glGetString();

	if (__failed(this->Ctx().Create(*this, ver_major, ver_minor))) {
		return this->Ctx().Error();
	}

	return TBase::Error();
}

const
ex_ui::popup::CWndBase& context::CWnd::operator ()(void) const { return (TBase&)*this; }
ex_ui::popup::CWndBase& context::CWnd::operator ()(void)       { return (TBase&)*this; }