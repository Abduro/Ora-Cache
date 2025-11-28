/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Sep-2025 at 01:20:31.586, UTC+4, Batumi, Friday;
	This is Ebo Pack shared window message handler interface definition file;
*/
#include "shared.wnd.msg.h"
#include "shared.preproc.h"

using namespace ex_ui::popup;

#include "sys.sync_obj.h"

using CSyncObject = shared::sys_core::CSyncObject;

CSyncObject& MsgGuardRef(void) { static CSyncObject crt_sect; return crt_sect; }
CSyncObject& MsgKbrdRef(void) { static CSyncObject crt_sect; return crt_sect; }

#define Kbrd_Safe_Lock() Safe_Lock(MsgKbrdRef());
#define Router_Safe_Lock() Safe_Lock(MsgGuardRef());

typedef ::std::map<const HWND, IMsg_Handler*> THandlers; // the reference to handle interface cannot be used here;
typedef ::std::set<const IKbrd_Handler*> TKbrdHandlers;

THandlers& Get_handlers (void) { static THandlers handlers; return handlers; }
TKbrdHandlers& Get_kbrds (void) { static TKbrdHandlers handlers; return handlers; }

static l_result __stdcall __msg_handler (HWND _h_wnd, uint32_t _msg_id, w_param _w_param, l_param _l_param)  {
	_h_wnd; _msg_id; _w_param; _l_param;
	Router_Safe_Lock();
	THandlers::iterator it_ = Get_handlers().find(_h_wnd);
	/*important:
	  some messages comes from system procedure CreateWindow(), thus the input window handle is not registered yet in handlers,
	  because the system function does not complete its work yet and not return the control to window class method;
	  thus, such messages as WM_CREATE, WM_SIZE are not handled by class that creates a window;
	  it looks like what one of the reasons of existing an ATL::thunk intermediate adapter layer;
	  solution:
	  the window creation procedure should call its message handler with the WM_CREATE message identifier immediately after subscribing to this message handler;
	  final decision:
	  the procedure that creates a window makes necessary things by direct call the required function(s) without sending a message;
	*/
	if (Get_handlers().end() == it_ || nullptr == it_->second)
		return ::DefWindowProc(_h_wnd, _msg_id, _w_param, _l_param);
	l_result n_result = 0;
	// each message defines the value of the result code: i.e. the message is handled or not;
	switch (_msg_id) {
	case WM_ACTIVATE:
	case WM_CREATE  : 
	case WM_CLOSE   :
	case WM_DESTROY : {
		n_result = it_->second->IMsg_OnMessage(_msg_id, _w_param, _l_param);
	} break;
//	case WM_CHAR    :
	case WM_KEYDOWN : {
		n_result = ::Get_kbrd().IMsg_OnMessage(_msg_id, _w_param, _l_param); // implicit conversion of h_result to l_result is not good;
	} break;
	case WM_MOVING  :
	case WM_SIZE    :
	case WM_SIZING  :
	case WM_WINDOWPOSCHANGING: {
		n_result = it_->second->IMsg_OnMessage(_msg_id, _w_param, _l_param);
	} break;
	case WM_PAINT   : { // https://learn.microsoft.com/en-us/windows/win32/gdi/wm-paint ; l_param and w_param are not used;
		n_result = it_->second->IMsg_OnMessage(_msg_id, 0, 0);
	} break;
#if (0)
	case WM_SYSCOMMAND : { // https://learn.microsoft.com/en-us/windows/win32/menurc/wm-syscommand ;
		n_result = it_->second->IMsg_OnMessage(_msg_id, _w_param, _l_param);
	} break;
#endif
	default:
		n_result = ::DefWindowProc(_h_wnd, _msg_id, _w_param, _l_param);
	}

		return n_result;
	}

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

	THandlers::const_iterator it_ = Get_handlers().find(_h_wnd);
	if (it_ != Get_handlers().end())
		return this->m_error << (err_code) TErrCodes::eObject::eExists;

	try {
		Get_handlers().insert(::std::make_pair(_h_wnd, &_handler));
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

	THandlers& handlers = Get_handlers();

	THandlers::iterator it_ = handlers.find(_h_wnd);
	if (it_ == Get_handlers().end())
		return this->m_error << (err_code) TErrCodes::eData::eNotFound;

	Get_handlers().erase(it_);

	return this->Error();
}

TMsgRouter& Get_router (void) {
	static TMsgRouter router;
	return router;
}

/////////////////////////////////////////////////////////////////////////////

CKbrdRouter::CKbrdRouter (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

err_code CKbrdRouter::IMsg_OnMessage (const uint32_t _u_code, const w_param _w_param, const l_param _l_param) {
	_u_code; _w_param; _l_param;

	Kbrd_Safe_Lock();

	err_code n_result = __s_false; // the message is not handled;

	// https://learn.microsoft.com/en-us/windows/win32/inputdev/about-keyboard-input ;

	const uint32_t v_key = static_cast<uint32_t>(_u_code);
	const uint16_t u_flags = static_cast<uint16_t>(HIWORD(_l_param));
	const bool b_repeat = !!LOWORD(_l_param);
	const bool b_extend = !!(u_flags & KF_EXTENDED);

	TKbrdHandlers& handlers = Get_kbrds();

	for (TKbrdHandlers::iterator it_ = handlers.begin(); it_ != handlers.end(); ++it_) {
		if (nullptr == *it_)
			continue;
		const IKbrd_Handler* p_handler = *it_;
		n_result = const_cast<IKbrd_Handler*>(p_handler)->IKbrd_OnKeyDown(v_key, b_repeat, b_extend);
		if (__s_ok == n_result)
			break;
		else if (__s_false == n_result)
			continue;
		else {
			this->m_error = p_handler->IKbrd_Error(); break;
		}
	}

	return n_result;
}

TError&  CKbrdRouter::Error (void) const { return this->m_error; }

err_code CKbrdRouter::Subscribe (const IKbrd_Handler* _p_handler) {
	_p_handler;

	Kbrd_Safe_Lock();

	this->m_error <<__METHOD__<<__s_ok;

	if (nullptr == _p_handler)
		return this->m_error <<__e_pointer;

	TKbrdHandlers::const_iterator it_ = Get_kbrds().find(_p_handler);
	if (it_ != Get_kbrds().end())
		return this->m_error << (err_code) TErrCodes::eObject::eExists = TString().Format(_T("The handler = %s is already subscribed"), TString()._addr_of(_p_handler, _T("0x%08x")));

	try {
		Get_kbrds().insert(_p_handler);
	}
	catch (const ::std::bad_alloc&) {
		this->m_error << __e_no_memory;
	}

	return this->Error();
}

err_code CKbrdRouter::Unsubscribe (const IKbrd_Handler* _p_handler) {
	_p_handler;

	Kbrd_Safe_Lock();

	this->m_error <<__METHOD__<<__s_ok;

	TKbrdHandlers& handlers = Get_kbrds();

	TKbrdHandlers::iterator it_ = handlers.find(_p_handler);
	if (it_ == handlers.end())
		return this->m_error << (err_code) TErrCodes::eData::eNotFound = TString().Format(_T("The handler = %s is not found"), TString()._addr_of(_p_handler, _T("0x%08x")));;

	handlers.erase(it_);

	return this->Error();
}

TKbrdRouter& ::Get_kbrd (void) {
	static TKbrdRouter kbrd_router;
	return kbrd_router;
}