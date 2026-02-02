/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Sep-2025 at 01:20:31.586, UTC+4, Batumi, Friday;
	This is Ebo Pack shared window message handler interface definition file;
*/
#include "shared.wnd.msg.h"
#include "shared.preproc.h"

using namespace ex_ui::popup;
using namespace ex_ui::popup::messages;

#include "sys.sync_obj.h"

using CSyncObject = shared::sys_core::CSyncObject;

namespace ex_ui { namespace popup { namespace messages { namespace _impl {

CSyncObject& MsgGuardRef(void) { static CSyncObject crt_sect; return crt_sect; }
CSyncObject& MsgMouseRef(void) { static CSyncObject crt_sect; return crt_sect; }
CSyncObject& MsgKbrdRef(void) { static CSyncObject crt_sect; return crt_sect; }

#define Mouse_Safe_Lock() Safe_Lock(MsgMouseRef());
#define Kbrd_Safe_Lock() Safe_Lock(MsgKbrdRef());
#define Router_Safe_Lock() Safe_Lock(MsgGuardRef());

typedef ::std::map<const HWND, IMsg_Handler*> THandlers; // the reference to handle interface cannot be used here;
typedef ::std::set<const IMouse_Handler*> TMouseHandlers;
typedef ::std::set<const IKbrd_Handler*> TKbrdHandlers;

THandlers& Get_handlers (void) { static THandlers handlers; return handlers; }
TMouseHandlers& Get_mouse_handlers (void) { static TMouseHandlers handlers; return handlers; }
TKbrdHandlers& Get_kbrd_handlers (void) { static TKbrdHandlers handlers; return handlers; }

static _pc_sz pc_sz_pat_subscribed = _T("The handler = %s is already subscribed");
static _pc_sz pc_sz_pat_not_found = _T("The handler = %s is not found");

	class CPrint {
	using e_action = IMouse_Handler::e_action;
	using e_button = IMouse_Handler::e_button;
	using e_v_key  = IMouse_Handler::e_v_key;
	using CCoords  = IMouse_Handler::CCoords;
	using CEvent   = IMouse_Handler::CEvent ;
	using CVirtKeys = IMouse_Handler::CVirtKeys;
	public:
		CPrint (void) = default; CPrint (const CPrint&) = delete; CPrint (CPrint&&) = delete; ~CPrint (void) = default;

		CString Out (const e_action _action) const {
			_action;
			CString cs_out;
			switch (_action) {
			case e_action::e_double: cs_out = _T("dbl clicked"); break;
			case e_action::e_pressed: cs_out = _T("pressed"); break;
			case e_action::e_released: cs_out = _T("released"); break;
			default:
				 cs_out = _T("#undef"); break;
			}
			return  cs_out;
		}

		CString Out (const e_button _button) const {
			_button;
			CString cs_out;
			switch (_button) {
			case e_button::e_left  : cs_out = TString().Format(_T("e_left (%04x)"), _button); break;
			case e_button::e_middle: cs_out = TString().Format(_T("e_middle (%04x)"), _button); break;
			case e_button::e_right : cs_out = TString().Format(_T("e_right (%04x)"), _button); break;
			case e_button::e_x_1   : cs_out = TString().Format(_T("e_x_1 (%04x)"), _button); break;
			case e_button::e_x_2   : cs_out = TString().Format(_T("e_x_2 (%04x)"), _button); break;
			default:
				cs_out = TString().Format(_T("#undef (%04x)"), _button); break;
			}
			return  cs_out;
		}

		CString Out (const CCoords& _coords) const {
			_coords;
			CString cs_out; cs_out = TString().Format(_T("{x:%04x;y:%04x}"), _coords.Get().x, _coords.Get().y);
			return  cs_out;
		}

		CString Out (const CEvent& _evt) const {
			_evt;
			static _pc_sz pc_sz_pat = _T("virt keys: %s; button: %s %s at point: %s;");

			CString cs_out;
			cs_out.Format (pc_sz_pat,
				(_pc_sz) this->Out(_evt.Keys()), (_pc_sz) this->Out(_evt.Button()), (_pc_sz) this->Out(_evt.Action()), (_pc_sz) this->Out(_evt.Coords())
			);
			return  cs_out;
		}

		CString Out (const e_v_key _key) const {
			_key;
			CString cs_out;
			switch (_key) {
			case e_v_key::e_alt : cs_out = TString().Format(_T("[alt] (%04x)"), _key); break;			
			case e_v_key::e_ctrl: cs_out = TString().Format(_T("[ctrl] (%04x)"), _key); break;
			case e_v_key::e_shft: cs_out = TString().Format(_T("[shft] (%04x)"), _key); break;
			default:
				cs_out = TString().Format(_T("#undef (%04x)"), _key); break;
			}
			return  cs_out;
		}

		CString Out (const CVirtKeys& _keys) const {
			_keys;
			CString cs_out;
			if (_keys.Get(e_v_key::e_alt )) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("[alt]" ); }
			if (_keys.Get(e_v_key::e_ctrl)) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("[ctrl]"); }
			if (_keys.Get(e_v_key::e_shft)) { if (cs_out.IsEmpty() == false) cs_out += _T("|"); cs_out += _T("[shft]"); }
			if (cs_out.IsEmpty())
				cs_out = _T("(none)");
			return  cs_out;
		}

	private:
		CPrint& operator = (const CPrint&) = delete; CPrint& operator = (CPrint&&) = delete;
	};

}}}}
using namespace _impl;

#pragma region cls::CBaseHandler{}

CBaseHandler::CBaseHandler (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& CBaseHandler::Error(void) const { return this->m_error; }

#pragma endregion
#pragma region cls::CMsgRouter{}

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
	case WM_ACTIVATE: case WM_CREATE : case WM_CLOSE :
	case WM_DESTROY : {
		n_result = __s_ok == it_->second->IMsg_OnMessage(_msg_id, _w_param, _l_param) ? __s_ok : __s_false;
	} break;
	case WM_LBUTTONDBLCLK : case WM_LBUTTONDOWN : case WM_LBUTTONUP :
	case WM_RBUTTONDBLCLK : case WM_RBUTTONDOWN : case WM_RBUTTONUP : {
		n_result = __s_ok == ::Get_mouse().IMsg_OnMessage(_msg_id, _w_param, _l_param) ? __s_ok : __s_false; // the possible error code is not of interest here;
		if (__s_false == n_result) // in order to guarantee the message is handled it is sent to generic handler;
			n_result = __s_ok == it_->second->IMsg_OnMessage(_msg_id, _w_param, _l_param) ? __s_ok : __s_false;
	} break;
	case WM_KEYDOWN : {
		n_result = __s_ok == ::Get_kbrd().IMsg_OnMessage(_msg_id, _w_param, _l_param)  ? __s_ok : __s_false;
	} break;
	case WM_MOVING  : case WM_SIZE : case WM_SIZING :
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

CMsgRouter:: CMsgRouter (void) : TBase() { TBase::m_error >>__CLASS__; }

bool CMsgRouter::ApplyTo (WNDCLASSEX& _wnd_cls) {
	_wnd_cls;
	const bool b_changed = _wnd_cls.lpfnWndProc != __msg_handler;
	if (b_changed)
		_wnd_cls.lpfnWndProc = __msg_handler;
	return b_changed;
}

err_code CMsgRouter::Subscribe (const HWND _h_wnd, IMsg_Handler& _handler) {
	_h_wnd; _handler;
	Router_Safe_Lock();

	TBase::m_error <<__METHOD__<<__s_ok;

	THandlers::const_iterator it_ = Get_handlers().find(_h_wnd);
	if (it_ != Get_handlers().end())
		return this->m_error << (err_code) TErrCodes::eObject::eExists;

	try {
		Get_handlers().insert(::std::make_pair(_h_wnd, &_handler));
	}
	catch (const ::std::bad_alloc&) { TBase::m_error << __e_no_memory; }

	return TBase::Error();
}

err_code CMsgRouter::Unsubscribe (const HWND _h_wnd) {
	_h_wnd;
	Router_Safe_Lock();

	TBase::m_error <<__METHOD__<<__s_ok;

	THandlers& handlers = Get_handlers();

	THandlers::iterator it_ = handlers.find(_h_wnd);
	if (it_ == Get_handlers().end())
		return TBase::m_error << (err_code) TErrCodes::eData::eNotFound;

	Get_handlers().erase(it_);

	return TBase::Error();
}

TMsgRouter& Get_router (void) {
	static TMsgRouter router;
	return router;
}

#pragma endregion

using e_action  = IMouse_Handler::e_action;
using e_button  = IMouse_Handler::e_button;
using e_v_key   = IMouse_Handler::e_v_key;
using CCoords   = IMouse_Handler::CCoords;
using CEvent    = IMouse_Handler::CEvent;
using CVirtKeys = IMouse_Handler::CVirtKeys;

#pragma region cls::CCoords{}

CCoords::CCoords (void) : m_point{0}, m_screen(true) {}
const
t_point& CCoords::Get (void) const { return this->m_point; }
bool     CCoords::Set (const l_param _l_pos) {
	_l_pos;
	if (false == this->Use_screen()) {
	const t_point pt_loc = { GET_X_LPARAM(_l_pos), GET_Y_LPARAM(_l_pos) };
	const bool b_changed = this->Get().x != pt_loc.x || this->Get().y != pt_loc.y; if (b_changed) this->m_point = pt_loc; return b_changed; } else {

		t_point pt_screen = {0};
		if (0 == ::GetCursorPos(&pt_screen)) { // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getcursorpos ;
			return false;
		} else if (this->Get().x != pt_screen.x || this->Get().y != pt_screen.y) {
			this->m_point = pt_screen; return true;
		} else return false;
	}
}

bool CCoords::Use_screen (void) const { return this->m_screen; }
void CCoords::Use_screen (const bool _b_use) { this->m_screen = _b_use; }

#pragma endregion
#pragma region cls::IMouse_Handler::CEvent{}

CEvent::CEvent (void) : m_action(e_action::e_none), m_button(e_button::e_undef) {}

e_action CEvent::Action (void) const { return this->m_action; }
bool CEvent::Action (const e_action _e_action) {
	_e_action;
	const bool b_changed = this->Action() != _e_action; if (b_changed) this->m_action = _e_action; return b_changed;
}

e_button CEvent::Button (void) const { return this->m_button; }
bool CEvent::Button (const e_button _e_button) {
	_e_button;
	const bool b_changed = this->Button() != _e_button; if (b_changed) this->m_button = _e_button; return b_changed;
}
const
CCoords& CEvent::Coords (void) const { return this->m_coords; }
CCoords& CEvent::Coords (void)       { return this->m_coords; }
const
CVirtKeys& CEvent::Keys (void) const { return this->m_v_keys; }
CVirtKeys& CEvent::Keys (void)       { return this->m_v_keys; }

CString CEvent::To_str  (void) const {
	return CString(TString().Format(_T("cls::[%s::%s] >> {%s};"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) CPrint().Out(*this)));
}

#pragma endregion
#pragma region cls::IMouse_Handler::CVirtKey{}

CVirtKeys::CVirtKeys (void) : m_keys{false} {}

bool CVirtKeys::Get (const e_v_key _key) const { return e_v_key::e_alt == _key ? this->m_keys[0] : e_v_key::e_ctrl == _key ? this->m_keys[1] : this->m_keys[2]; }
bool CVirtKeys::Set (const w_param _values) {
	_values;
	bool b_changed = false;
	if (CVirtKeys::Has (e_v_key::e_alt , _values) != this->Get(e_v_key::e_alt )) { this->m_keys[0] = !this->m_keys[0]; b_changed = true; }
	if (CVirtKeys::Has (e_v_key::e_ctrl, _values) != this->Get(e_v_key::e_ctrl)) { this->m_keys[1] = !this->m_keys[1]; b_changed = true; }
	if (CVirtKeys::Has (e_v_key::e_shft, _values) != this->Get(e_v_key::e_shft)) { this->m_keys[2] = !this->m_keys[2]; b_changed = true; }
	return b_changed;
}

bool CVirtKeys::Has (const e_v_key e_key, const w_param _values) {
	e_key; _values;
	// https://stackoverflow.com/questions/1811206/on-win32-how-to-detect-whether-a-left-shift-or-right-alt-is-pressed-using-perl ;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getkeystate ;
	if (e_v_key::e_alt  == e_key) { return ::GetKeyState(VK_MENU) < 0; }
	if (e_v_key::e_ctrl == e_key) { return !!(static_cast<uint32_t>(_values) & (uint32_t)e_key); }
	if (e_v_key::e_shft == e_key) { return !!(static_cast<uint32_t>(_values) & (uint32_t)e_key); }

	return false;
}

#pragma endregion
#pragma region cls::CMouseRouter{}

CMouseRouter::CMouseRouter (void) : TBase() { TBase::m_error >>__CLASS__; }

err_code CMouseRouter::IMsg_OnMessage (const uint32_t _u_code, const w_param _w_param, const l_param _l_param) {
	_u_code; _w_param; _l_param;
	Mouse_Safe_Lock();

	TBase::m_error <<__METHOD__<<__s_false; // the message is not handled;
	// https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-lbuttondblclk ;
	// https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-lbuttondown   ;
	// https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-lbuttonup     ;
	// https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-rbuttondblclk ;
	// https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-rbuttondown   ;
	// https://docs.microsoft.com/en-us/windows/win32/inputdev/wm-rbuttonup     ;

	using e_action = IMouse_Handler::e_action;
	using e_button = IMouse_Handler::e_button;
	using e_v_key  = IMouse_Handler::e_v_key ;

	IMouse_Handler::CEvent event_; event_.Keys().Set(_w_param); event_.Coords().Set(_l_param);

	switch (_u_code) {
	case WM_LBUTTONDBLCLK : { event_.Action(e_action::e_double); event_.Button(e_button::e_left) ; } break;
	case WM_RBUTTONDBLCLK : { event_.Action(e_action::e_double); event_.Button(e_button::e_right); } break;
	case WM_LBUTTONDOWN : { event_.Action(e_action::e_pressed); event_.Button(e_button::e_left) ; } break;
	case WM_RBUTTONDOWN : { event_.Action(e_action::e_pressed); event_.Button(e_button::e_right); } break;
	case WM_LBUTTONUP : { event_.Action(e_action::e_released); event_.Button(e_button::e_left) ; } break;
	case WM_RBUTTONUP : { event_.Action(e_action::e_released); event_.Button(e_button::e_right); } break;
	default:
		return TBase::Error(); // still not handled;
	}

	TMouseHandlers& handlers = ::Get_mouse_handlers();

	for (TMouseHandlers::iterator it_ = handlers.begin(); it_ != handlers.end(); ++it_) {
		if (nullptr == *it_)
			continue;
		const IMouse_Handler* p_handler = *it_;
		err_code n_result = const_cast<IMouse_Handler*>(p_handler)->IMouse_OnEvent(event_);
		if (__s_ok == n_result) {
			TBase::m_error << n_result; break;
		}
		else if (__s_false == n_result)
			continue;
		else {
			TBase::m_error = p_handler->IMouse_Error(); break;
		}
	}

	return TBase::Error();
}

err_code CMouseRouter::Subscribe (const IMouse_Handler* _p_handler) {
	_p_handler;
	Mouse_Safe_Lock();

	TBase::m_error <<__METHOD__<<__s_ok;

	if (nullptr == _p_handler)
		return TBase::m_error <<__e_pointer;

	TMouseHandlers& handlers = ::Get_mouse_handlers();
	TMouseHandlers::const_iterator it_ = handlers.find(_p_handler);
	if (it_ != handlers.end())
		return TBase::m_error << (err_code) TErrCodes::eObject::eExists = TString().Format(pc_sz_pat_subscribed, TString()._addr_of(_p_handler, _T("0x%08x")));

	try {
		handlers.insert(_p_handler);
	}
	catch (const ::std::bad_alloc&) { TBase::m_error << __e_no_memory; }

	return TBase::Error();
}

err_code CMouseRouter::Unsubscribe (const IMouse_Handler* _p_handler) {
	_p_handler;
	Mouse_Safe_Lock();
	this->m_error <<__METHOD__<<__s_ok;

	TMouseHandlers& handlers = ::Get_mouse_handlers();
	TMouseHandlers::iterator it_ = handlers.find(_p_handler);
	if (it_ == handlers.end())
		return TBase::m_error << (err_code) TErrCodes::eData::eNotFound = TString().Format(pc_sz_pat_not_found, TString()._addr_of(_p_handler, _T("0x%08x")));

	handlers.erase(it_);

	return TBase::Error();
}

err_code CMouseRouter::operator <<(const IMouse_Handler* _p_handler) { return this->Subscribe(_p_handler); }
err_code CMouseRouter::operator >>(const IMouse_Handler* _p_handler) { return this->Unsubscribe(_p_handler); }

TMseRouter& ::Get_mouse (void) {
	static TMseRouter mouse_router;
	return mouse_router;
}

#pragma endregion
#pragma region cls::CKbrdRouter{}

CString  IKbrd_Handler::To_str(const uint32_t _v_key) {
	_v_key;
	CString cs_out;

	switch (_v_key) {
	case (uint32_t) e_pref_keys::e_down  : cs_out = TString().Format(_T("$arr_down (0x%02x)") , _v_key); break;
	case (uint32_t) e_pref_keys::e_left  : cs_out = TString().Format(_T("$arr_left (0x%02x)") , _v_key); break;
	case (uint32_t) e_pref_keys::e_right : cs_out = TString().Format(_T("$arr_right (0x%02x)"), _v_key); break;
	case (uint32_t) e_pref_keys::e_up    : cs_out = TString().Format(_T("$arr_up (0x%02x)"), _v_key); break;
	default:
		cs_out.Format(_T("v_key (0x%02x)"), _v_key);
	}

	return  cs_out;
}

CKbrdRouter::CKbrdRouter (void) : TBase() { TBase::m_error >>__CLASS__; }

err_code CKbrdRouter::IMsg_OnMessage (const uint32_t _u_code, const w_param _w_param, const l_param _l_param) {
	_u_code; _w_param; _l_param;
	Kbrd_Safe_Lock();

	TBase::m_error <<__METHOD__<<__s_false; // the message is not handled;

	// https://learn.microsoft.com/en-us/windows/win32/inputdev/about-keyboard-input ;

	const uint32_t v_key = static_cast<uint32_t>(_w_param);
	const uint16_t u_flags = static_cast<uint16_t>(HIWORD(_l_param));
	const bool b_repeat = !!LOWORD(_l_param);
	const bool b_extend = !!(u_flags & KF_EXTENDED);

	TKbrdHandlers& handlers = Get_kbrd_handlers();

	for (TKbrdHandlers::iterator it_ = handlers.begin(); it_ != handlers.end(); ++it_) {
		if (nullptr == *it_)
			continue;
		const IKbrd_Handler* p_handler = *it_;
		err_code n_result = const_cast<IKbrd_Handler*>(p_handler)->IKbrd_OnKeyDown(v_key, b_repeat, b_extend);
		if (__s_ok == n_result) {
			TBase::m_error << n_result; break;
		}
		else if (__s_false == n_result)
			continue;
		else {
			TBase::m_error = p_handler->IKbrd_Error(); break;
		}
	}

	return TBase::Error();
}

err_code CKbrdRouter::Subscribe (const IKbrd_Handler* _p_handler) {
	_p_handler;
	Kbrd_Safe_Lock();

	TBase::m_error <<__METHOD__<<__s_ok;

	if (nullptr == _p_handler)
		return TBase::m_error <<__e_pointer;

	TKbrdHandlers& handlers = ::Get_kbrd_handlers();
	TKbrdHandlers::const_iterator it_ = handlers.find(_p_handler);
	if (it_ != handlers.end())
		return TBase::m_error << (err_code) TErrCodes::eObject::eExists = TString().Format(pc_sz_pat_subscribed, TString()._addr_of(_p_handler, _T("0x%08x")));

	try {
		handlers.insert(_p_handler);
	}
	catch (const ::std::bad_alloc&) { TBase::m_error << __e_no_memory; }

	return TBase::Error();
}

err_code CKbrdRouter::Unsubscribe (const IKbrd_Handler* _p_handler) { _p_handler;

	Kbrd_Safe_Lock();
	this->m_error <<__METHOD__<<__s_ok;

	TKbrdHandlers& handlers = ::Get_kbrd_handlers();
	TKbrdHandlers::iterator it_ = handlers.find(_p_handler);
	if (it_ == handlers.end())
		return TBase::m_error << (err_code) TErrCodes::eData::eNotFound = TString().Format(pc_sz_pat_not_found, TString()._addr_of(_p_handler, _T("0x%08x")));

	handlers.erase(it_);

	return TBase::Error();
}

TKbrdRouter& ::Get_kbrd (void) {
	static TKbrdRouter kbrd_router;
	return kbrd_router;
}

err_code CKbrdRouter::operator <<(const IKbrd_Handler* _p_handler) { return this->Subscribe(_p_handler); }
err_code CKbrdRouter::operator >>(const IKbrd_Handler* _p_handler) { return this->Unsubscribe(_p_handler); }

#pragma endregion