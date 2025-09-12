/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Sep-2025 at 01:20:31.586, UTC+4, Batumi, Friday;
	This is Ebo Pack shared window message handler interface definition file;
*/
#include "shared.wnd.msg.h"
#include "shared.preproc.h"

using namespace ex_ui::popup;

#include "sys.sync_obj.h"

using CSyncObject = shared::sys_core::CSyncObject;

CSyncObject& SafeGuardRef(void)
{
	static CSyncObject crt_sect;
	return crt_sect;
}

#define Router_Safe_Lock() Safe_Lock(SafeGuardRef());

typedef ::std::map<const HWND, IMsg_Handler*> THandlers; // the reference to handle interface cannot be used here;

THandlers& Get_handlers (void) {
	static THandlers handlers;
	return handlers;
}

static l_result __stdcall __msg_handler (HWND _h_wnd, uint32_t _msg_id, w_param _w_param, l_param _l_param)  {
	_h_wnd; _msg_id; _w_param; _l_param;
	Router_Safe_Lock();
	THandlers::iterator it_ = Get_handlers().find(_h_wnd);
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
#if (0)
		#define btns_info (MB_OK|MB_ICONINFORMATION)

		CString cs_cap = TString().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		CString cs_msg ;

		switch (_msg_id) {
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
	} break;
	case WM_MOVING :
	case WM_WINDOWPOSCHANGING: {
		n_result = it_->second->IMsg_OnMessage(_msg_id, _w_param, _l_param);
	} break;
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

	THandlers::iterator it_ = Get_handlers().find(_h_wnd);
	if (it_ == Get_handlers().end())
		return this->m_error << (err_code) TErrCodes::eData::eNotFound;

	Get_handlers().erase(it_);

	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////

TRouter&  Get_router (void) {
	static TRouter router;
	return router;
}