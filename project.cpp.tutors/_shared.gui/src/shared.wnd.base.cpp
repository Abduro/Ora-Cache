/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Aug-2025 at 12:41:07.778, UTC+4, Batumi, Sunday;
	This is Ebo Pack tutorials' shared window base interface implementation file;
*/
#include "shared.wnd.base.h"
#include "shared.preproc.h"
#include "shared.wnd.res.h"

#include "shared.dbg.h"

#ifndef __H
#define __H(_rect) (_rect.bottom - _rect.top)
#endif
#ifndef __W
#define __W(_rect) (_rect.right - _rect.left)
#endif

using namespace ex_ui::popup;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace popup { namespace _impl {

}}}

using namespace ex_ui::popup::_impl;

/////////////////////////////////////////////////////////////////////////////

CWndBase::CLayout::CSize:: CSize (const uint32_t _u_cx, const uint32_t _u_cy) : m_size{static_cast<long>(_u_cx), static_cast<long>(_u_cy)}, m_lock(false) {}

bool  CWndBase::CLayout::CSize::Is_locked (void) const { return this->m_lock; }
bool  CWndBase::CLayout::CSize::Is_locked (const bool _b_state) {
	_b_state;
	const bool b_changed = this->Is_locked() != _b_state;
	if (b_changed)
		this->m_lock = _b_state;

	return b_changed;
}

const
t_size& CWndBase::CLayout::CSize::Ref (void) const { return this->m_size; }
t_size& CWndBase::CLayout::CSize::Ref (void)       { return this->m_size; }

/////////////////////////////////////////////////////////////////////////////

CWndBase::CLayout:: CLayout (void) {}

const
CWndBase::CLayout::CSize&  CWndBase::CLayout::Size (void) const { return this->m_size; }
CWndBase::CLayout::CSize&  CWndBase::CLayout::Size (void)       { return this->m_size; }

/////////////////////////////////////////////////////////////////////////////

CWndBase:: CWndBase (void) : m_h_wnd (0) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; this->m_cls_name = __CLASS__; }
CWndBase::~CWndBase (void) {
	if (this->Is_valid())
		this->Destroy(); // it is *required* for removing message handler interface pointer from router notification queue;
}

err_code CWndBase::IMsg_OnMessage (const uint32_t _u_code, const w_param _w_param, const l_param _l_param) {
	_u_code; _w_param; _l_param;
	err_code n_result = __s_false; // not handled;
	switch (_u_code) {
	case WM_CREATE : {} break; // does nothing; this->Create() function subscribes to message router in case of success;
	case WM_CLOSE  : {
			// the [x] 'Close' window title button is pressed or system menu 'Close' command is selected;
			// in order to avoid any intermediate steps Destroy() procedure is called directly;
			// unsubscribes and destroys itself; this base window implementation does not show any prompt;
			if (__succeeded(this->Destroy()))
				n_result = __s_ok; // this message is handled;
		} break;
	case WM_DESTROY: {
		__trace_warn_3(_T("The window handle = %s is being destroyed;\n"), TString()._addr_of(this->Handle(), _T("0x%08x")));
		} break;
	}

#if (0)
	#define btns_info (MB_OK|MB_ICONINFORMATION)

	CString cs_cap = TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	CString cs_msg ;

	switch (_u_code) {
	case WM_CREATE : cs_msg = _T("wm_create"); break;
	case WM_CLOSE  : cs_msg = _T("wm_close"); break;
	case WM_DESTROY: cs_msg = _T("wm_destroy"); break;
	default:
		cs_msg = _T("#undef");
	}

	cs_msg.Format (_T("On message=%s"), (_pc_sz)cs_msg);

	::MessageBox(
			0, (_pc_sz) cs_msg,
			   (_pc_sz) cs_cap , btns_info
		);
#endif

	return n_result;
}

err_code CWndBase::Create (_pc_sz _p_cls_name, _pc_sz _p_title, const t_rect& _rect, const bool _b_vidible/* = true*/, const HWND _h_parent/* = 0*/) {
	_p_cls_name; _p_title; _rect; _b_vidible; _h_parent;
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Is_valid())
		return this->m_error << (err_code) TErrCodes::eObject::eExists;

	if (false == CWndCls().Is_exist(_p_cls_name))
		return this->m_error << __e_inv_arg = TString().Format(_T("The class '%s' is not registered"), _p_cls_name);
	// just checks the window visibility flag for accordance with input arg value;
	this->Styles().Std(_b_vidible ? this->Styles().Std() | WS_VISIBLE : this->Styles().Std() & ~WS_VISIBLE);

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa ;
	this->m_h_wnd = ::CreateWindowEx(
		this->Styles().Ext(), _p_cls_name, _p_title,
		this->Styles().Std(), _rect.left, _rect.top, __W(_rect), __H(_rect), _h_parent, 0, 0, 0
	);
	if (nullptr == this->m_h_wnd)
		this->m_error.Last();
	else
		::Get_router().Subscribe(this->Handle(), *this);

	return this->Error();
}

err_code CWndBase::Destroy (void) {

	this->m_error <<__METHOD__<<__s_ok;

	if (this->Is_valid() == false)
		return this->Error();   // no error, just returns 'success';

	const bool b_is_top = this->Is_top();

	::Get_router().Unsubscribe(this->Handle());

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-destroywindow ;
	if (false == !!::DestroyWindow(this->m_h_wnd))
		return this->m_error.Last();
	else {
		this->m_error << __e_not_inited;
		this->m_h_wnd = 0;

		if (b_is_top) {
#if (0)
		#define btns_info (MB_OK|MB_ICONINFORMATION)
		CString cs_cap = TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		CString cs_msg = TString().Format(_T("is_top: %s;"), _T("true"));

		::MessageBox(
			0, (_pc_sz) cs_msg,
			   (_pc_sz) cs_cap , btns_info
		);
#endif
		::PostQuitMessage(0); // special case and it requires to exit; it is assumed the app main window handles this message;
		}
	}

	return __s_ok;
}

TError&  CWndBase::Error (void) const { return this->m_error; }

HWND  CWndBase::Handle (void) const { return this->m_h_wnd; }

bool  CWndBase::Is_valid (void) const {
	return nullptr != this->m_h_wnd && true == !!::IsWindow(this->Handle());
}

bool  CWndBase::Is_top (void) const {
	return 0 == (this->Styles().Std() & WS_CHILD); // it is assumed that all child windows has this style flag, the main window doesn't;
}

void  CWndBase::Set_visible (const bool _b_state) const {
	_b_state;
	if (this->Is_valid()) {
		::ShowWindow(this->Handle(), _b_state ? SW_SHOW : SW_HIDE);
	}
}

const
CWndBase::CLayout& CWndBase::Layout (void) const { return this->m_layout; }
CWndBase::CLayout& CWndBase::Layout (void)       { return this->m_layout; }

const
CWndBase::CStyles& CWndBase::Styles (void) const { return this->m_styles; }
CWndBase::CStyles& CWndBase::Styles (void)       { return this->m_styles; }

_pc_sz CWndBase::Cls_name (void) const { return (_pc_sz) this->m_cls_name; }

bool CWndBase::operator == (const CWndBase& _rsh) const { return this->Handle() == _rsh.Handle(); }
bool CWndBase::operator == (const HWND _what) const { return this->Handle() == _what; }

CWndBase::operator const HWND (void) const { return this->Handle(); }

/////////////////////////////////////////////////////////////////////////////

CWndBase::CStyles:: CStyles (void) : m_ext(0), m_std(0) {}
CWndBase::CStyles::~CStyles (void) {}

bool CWndBase::CStyles::Default_for_app (void) { bool b_changed = /*this->Ext(WS_EX_NOPARENTNOTIFY)*/false; if (this->Std(WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN|WS_CLIPSIBLINGS)) b_changed = true; return b_changed; }
bool CWndBase::CStyles::Default_for_kid (void) { bool b_changed = /*this->Ext(WS_EX_NOPARENTNOTIFY)*/false; if (this->Std(WS_CHILD|WS_CLIPCHILDREN|WS_CLIPSIBLINGS)) b_changed = true; return b_changed; }

uint32_t CWndBase::CStyles::Ext (void) const { return this->m_ext; }
bool     CWndBase::CStyles::Ext (const uint32_t _u_styles) {
	_u_styles;
	const bool b_changed = (/*!!_u_styles &&*/ this->Ext() != _u_styles);
	if (b_changed)
		this->m_ext = _u_styles;

	return b_changed;
}

uint32_t CWndBase::CStyles::Extended (void) const { return this->Ext(); }
bool     CWndBase::CStyles::Extended (const uint32_t _u_styles) { return this->Ext(_u_styles); }

uint32_t CWndBase::CStyles::Standard (void) const { return this->Std(); }    
bool     CWndBase::CStyles::Standard (const uint32_t _u_styles) { return this->Std(_u_styles); }

uint32_t CWndBase::CStyles::Std (void) const { return this->m_std; }
bool     CWndBase::CStyles::Std (const uint32_t _u_styles) {
	_u_styles;
	const bool b_changed = (/*!!_u_styles &&*/ this->Std() != _u_styles);
	if (b_changed)
		this->m_std = _u_styles;

	return b_changed;
}