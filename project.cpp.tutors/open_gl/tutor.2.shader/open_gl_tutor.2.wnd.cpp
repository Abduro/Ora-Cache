/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Aug-2025 at 03:01:10.215, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' shader window interface implementation file;
*/
#include "open_gl_tutor.2.wnd.h"
#include "open_gl_tutor.2.res.h"
#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::shader;

namespace ex_ui { namespace draw { namespace open_gl { namespace shader {

typedef ex_ui::popup::CWndBase TBase;

shader::CWnd:: CWnd (void) : TParent() { TBase::m_error >>__CLASS__; }
shader::CWnd::~CWnd (void) { } // parent class object will destroy window created automatically on its (parent) destruction;

err_code shader::CWnd::Create (const HWND _h_parent, const t_rect& _rc_wnd_pos, const bool _b_visible) {
	_h_parent; _rc_wnd_pos; _b_visible;
	TParent::m_error << __METHOD__ << __s_ok;

	if (TParent::Is_valid())
		return TParent::m_error << (err_code) TErrCodes::eObject::eExists;

	static _pc_sz p_cls_name = _T("__open_gl_shader_wnd");

	CWndCls wnd_cls;

	if (__failed(wnd_cls.Register(p_cls_name))) {
		__trace_err_3(_T("%s\n"), (_pc_sz) wnd_cls.Error().Print(TError::e_req));
		return TParent::m_error = wnd_cls.Error();
	}

	TParent::Styles().Default_for_kid();

	if (__failed(TBase::Create(
		p_cls_name, TString().Format(_T("cls::[%s:%s]"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__), _rc_wnd_pos, _b_visible, _h_parent
	))) {
	} else if (__failed(TParent::Ctx().Create(*this, 4, 6))) {
		__trace_err_3(_T("%s\n"), (_pc_sz) TParent::Ctx().Error()().Print(TError::e_req));
	}

	return TParent::Error();
}

}}}}