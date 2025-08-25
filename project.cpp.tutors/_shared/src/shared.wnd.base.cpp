/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Aug-2025 at 12:41:07.778, UTC+4, Batumi, Sunday;
	This is Ebo Pack tutorials' shared window base interface implementation file;
*/
#include <map>
#include "shared.wnd.base.h"
#include "sys.sync_obj.h"

#ifndef __H
#define __H(_rect) (_rect.bottom - _rect.top)
#endif
#ifndef __W
#define __W(_rect) (_rect.right - _rect.left)
#endif

using namespace ex_ui::popup;

CAtom:: CAtom (void) : m_atom(0) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CAtom::~CAtom (void) {}

TError&  CAtom::Error (void) const { return this->m_error; }

bool  CAtom::Is_valid (void) const { return this->m_atom != 0; }

bool  CAtom::Is_exist (_pc_sz _cls_name) const {
	_cls_name;
	this->m_error << __METHOD__ <<  __s_ok;

	CString cls_name(_cls_name); cls_name.Trim();

	if (cls_name.IsEmpty())
		return this->m_error << __e_inv_arg = _T("Input class name is invalid;");

	HINSTANCE h_instance = reinterpret_cast<HINSTANCE>(::GetModuleHandle(nullptr));
	WNDCLASSEX wnd_cls = { 0 };
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getclassinfoexa ;
	if (false == !!::GetClassInfoEx(h_instance, (_pc_sz) cls_name, &wnd_cls))
		this->m_error.Last();

	return false == this->Error();
}

err_code CAtom::Register (_pc_sz _cls_name) {
	_cls_name;
	this->m_error << __METHOD__ <<  __s_ok;

	if (this->Is_valid()) // the atom has been already created; doesn't matter with such name it was created, but must be unregistered first;
		return this->m_error << (err_code) TErrCodes::eObject::eExists;

	if (this->Is_exist(_cls_name))
		return this->Error(); // no indication of the error this time, but just returns __s_ok;

	CString cls_name(_cls_name); cls_name.Trim();

	HINSTANCE h_instance = reinterpret_cast<HINSTANCE>(::GetModuleHandle(nullptr));

	WNDCLASSEX wnd_cls = { 0 }; // https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassexw ;

	wnd_cls.cbSize        = sizeof(WNDCLASSEX);
	wnd_cls.style         = CS_OWNDC|CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS;
	wnd_cls.lpfnWndProc   = ::DefWindowProc;
	wnd_cls.hInstance     = h_instance;
#if (0)
	/* excerpt from above URL:
		When this member is NULL, an application must paint its own background whenever it is requested to paint in its client area...
	*/
	wnd_cls.hbrBackground = (HBRUSH)::GetStockObject(BLACK_BRUSH); // https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-getstockobject ;
#endif
	wnd_cls.hbrBackground = nullptr;
	wnd_cls.lpszClassName = (_pc_sz)cls_name;

	::Get_router().ApplyTo(wnd_cls); // it is *required* for receiving windows messages through the router procedure;

	this->m_atom = ::RegisterClassEx(&wnd_cls);
	if (0 == this->m_atom)
		this->m_error.Last();

	this->m_cls_name = cls_name;

	return this->Error();
}

err_code CAtom::Unregister (void) {

	this->m_error << __METHOD__ <<  __s_ok;

	if (false == this->Is_valid())
		return this->Error();  // nothing is to unregister, that's okay;

	if (this->m_cls_name.IsEmpty())
		return this->m_error << __e_not_expect;

	const
	HINSTANCE h_instance = reinterpret_cast<HINSTANCE>(::GetModuleHandle(nullptr));

	if (false == ::UnregisterClass((_pc_sz)this->m_cls_name, h_instance))
		return this->m_error.Last();

	this->m_atom = 0;
	this->m_cls_name.Empty();

	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////
const
CAtom& CAtom::operator >>(CString& _cls_name) const { _cls_name = this->m_cls_name; return *this; }

CAtom::operator ATOM (void) const { return this->m_atom; }

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace popup { namespace _impl {

	using CSyncObject = shared::sys_core::CSyncObject;

	CSyncObject& SafeGuardRef(void)
	{
		static CSyncObject crt_sect;
		return crt_sect;
	}

	#define Router_Safe_Lock() Safe_Lock(SafeGuardRef());

	typedef ::std::map<const HWND, IMsg_Handler*> THandlers; // the reference to handle interface cannot be used here;

	THandlers handlers;

	static l_result __stdcall __msg_handler (HWND _h_wnd, uint32_t _msg_id, w_param _w_param, l_param _l_param)  {
		_h_wnd; _msg_id; _w_param; _l_param;
		Router_Safe_Lock();
		THandlers::iterator it_ = handlers.find(_h_wnd);
		if (handlers.end() == it_ || nullptr == it_->second)
			return ::DefWindowProc(_h_wnd, _msg_id, _w_param, _l_param);
		l_result n_result = 0;
		// each message defines the value of the result code: i.e. the message is handled or not;
		switch (_msg_id) {
		case WM_CREATE : break;
		case WM_CLOSE  : break;
		case WM_DESTROY: break;
		case WM_KEYDOWN: break;
		case WM_SIZE   : break;
		default:
			n_result = ::DefWindowProc(_h_wnd, _msg_id, _w_param, _l_param);
		}

		return n_result;
	}

}}}

using namespace ex_ui::popup::_impl;

CMsgRouter:: CMsgRouter (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

bool CMsgRouter::ApplyTo (WNDCLASSEX& _wnd_cls) {
	_wnd_cls;
	const bool b_changed = _wnd_cls.lpfnWndProc != __msg_handler;
	if (b_changed)
		_wnd_cls.lpfnWndProc = __msg_handler;
	return b_changed;
}

TError&  CMsgRouter::Error (void) const { return this->m_error; }

err_code CMsgRouter::Subscribe (const HWND _h_wnd, IMsg_Handler& _handler) {
	_h_wnd; _handler;

	Router_Safe_Lock();

	this->m_error <<__METHOD__<<__s_ok;

	THandlers::const_iterator it_ = handlers.find(_h_wnd);
	if (it_ != handlers.end())
		return this->m_error << (err_code) TErrCodes::eObject::eExists;

	try {
		handlers.insert(::std::make_pair(_h_wnd, &_handler));
	}
	catch (const ::std::bad_alloc&) {
		this->m_error << __e_no_memory;
	}

	return this->Error();
}

err_code CMsgRouter::Unsubscribe (const HWND _h_wnd) {
	_h_wnd;

	Router_Safe_Lock();

	this->m_error <<__METHOD__<<__s_ok;

	THandlers::iterator it_ = handlers.find(_h_wnd);
	if (it_ == handlers.end())
		return this->m_error << (err_code) TErrCodes::eData::eNotFound;

	handlers.erase(it_);

	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////

CWnd:: CWnd (void) : m_h_wnd (0) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CWnd::~CWnd (void) {
	if (this->Is_valid())
		this->Destroy(); // it is *required* for removing message handler interface pointer from router notification queue;
}

err_code CWnd::Create (_pc_sz _p_cls_name, _pc_sz _p_title, const t_rect& _rect, const bool _b_vidible/* = true*/, const HWND _h_parent/* = 0*/) {
	_p_cls_name; _p_title; _rect; _b_vidible; _h_parent;
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Is_valid())
		return this->m_error << (err_code) TErrCodes::eObject::eExists;

	if (false == CAtom().Is_exist(_p_cls_name))
		return this->m_error << __e_inv_arg = TString().Format(_T("The class '%s' is not registered"), _p_cls_name);

	const uint32_t u_ex_style = WS_EX_NOPARENTNOTIFY; // extended style flags' set;
	const uint32_t u_st_style = WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN|WS_CLIPSIBLINGS; // standard style flags' set;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-createwindowexa ;
	this->m_h_wnd = ::CreateWindowEx(u_ex_style, _p_cls_name, _p_title, u_st_style, _rect.left, _rect.top, __W(_rect), __H(_rect), _h_parent, 0, 0, 0);
	if (nullptr == this->m_h_wnd)
		this->m_error.Last();

	return this->Error();
}

err_code CWnd::Destroy (void) {

	this->m_error <<__METHOD__<<__s_ok;

	if (this->Is_valid() == false)
		return this->Error();   // no error, just returns 'success';
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-destroywindow ;
	if (false == !!::DestroyWindow(this->m_h_wnd))
		return this->m_error.Last();
	else {
		this->m_error << __e_not_inited;
		this->m_h_wnd = 0;
	}

	return __s_ok;
}

TError&  CWnd::Error (void) const { return this->m_error; }

HWND CWnd::Handle (void) const { return this->m_h_wnd; }

bool  CWnd::Is_valid (void) const {
	return nullptr != this->m_h_wnd && true == !!::IsWindow(this->Handle());
}

bool CWnd::operator == (const CWnd& _rsh) const { return this->Handle() == _rsh.Handle(); }
bool CWnd::operator == (const HWND _what) const { return this->Handle() == _what; }

CWnd::operator const HWND (void) const { return this->Handle(); }

/////////////////////////////////////////////////////////////////////////////

TRouter&  Get_router (void) {
	static TRouter router;
	return router;
}