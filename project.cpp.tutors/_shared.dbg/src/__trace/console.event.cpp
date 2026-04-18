/*
	Created by Tech_dog (ebontrop@gmsil.com) on 22-Mar-2026 at 14:12:02.641, UTC+4, Batumi, Sunday;
	This is Ebo Pack console event handler interface implementation file;
*/
#include "console.event.h"
#include "console.font.h"

#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace shared::console;
using namespace shared::console::events;

#pragma region __aux_decls[]

using CSyncObject = shared::sys_core::CSyncObject;

CSyncObject& InputEvtGuardRef(void) { static CSyncObject crt_sect; return crt_sect; }
CSyncObject& OutputEvtGuardRef(void) { static CSyncObject crt_sect; return crt_sect; }

#define Input_Safe_Lock() Safe_Lock(InputEvtGuardRef());
#define Output_Safe_Lock() Safe_Lock(OutputEvtGuardRef());

typedef ::std::set<const ctrl::IEvtHandler*> TCtrlHandlers;
typedef ::std::set<const input::IEvtHandler*> TInputHandlers;

TCtrlHandlers& Get_ctrl_handlers (void) { static TCtrlHandlers handlers; return handlers; }
TInputHandlers& Get_input_handlers (void) { static TInputHandlers handlers; return handlers; }

static _pc_sz p_err_evt_handler_ptr = _T("$__e_ptr: input pointer to event handler is invalid");
static _pc_sz p_err_subscribed = _T("The handler = %s is already subscribed");
static _pc_sz p_err_not_found = _T("The handler = %s is not found");
static _pc_sz p_err_router_off = _T("Router is already turned off");
static _pc_sz p_err_router_on = _T("Router is already turned on");

#pragma endregion
#pragma region cls::CKey_Base{}

using CKey_Base = input::CKey_Base;

CKey_Base::CKey_Base (void) : m_code (0), m_changed(false) {}
CKey_Base::CKey_Base (const CKey_Base& _src) : CKey_Base() { *this = _src; }
CKey_Base::CKey_Base (CKey_Base&& _victim) : CKey_Base() { *this = _victim; }

uint16_t CKey_Base::Code (void) const { return this->m_code; }
bool     CKey_Base::Code (const uint16_t _n_value) {
	const bool b_changed = _n_value != this->Code();  if (b_changed) this->m_code = _n_value; return b_changed;
}
_pc_sz CKey_Base::Name (void) const { return (_pc_sz)this->m_name; }
bool   CKey_Base::Name (_pc_sz _p_name) {
	const bool b_changed = 0 != this->m_name.CompareNoCase(_p_name);  if (b_changed) this->m_name = _p_name; return b_changed;
}

bool   CKey_Base::Is_changed (void) const { return this->m_changed; }
bool&  CKey_Base::Is_changed (void)       { return this->m_changed; }

CKey_Base& CKey_Base::operator = (const CKey_Base& _src) { *this << _src.Code() << _src.Name() << _src.Is_changed(); return *this; }
CKey_Base& CKey_Base::operator = (CKey_Base&& _victim) { *this = (const CKey_Base&)_victim; return *this; }

CKey_Base& CKey_Base::operator <<(const bool  _b_changed) { this->Is_changed() = _b_changed; return *this; }
CKey_Base& CKey_Base::operator <<(const uint16_t _u_code) { this->Code(_u_code); return *this; }
CKey_Base& CKey_Base::operator <<(const _pc_sz   _p_name) { this->Name(_p_name); return *this; }
CKey_Base& CKey_Base::operator <<(const CString _cs_name) { this->Name((_pc_sz)_cs_name); return *this; }

#pragma endregion
#pragma region cls::CCtrl_Key{}

using CCtrl_Key = shared::console::events::input::CCtrl_Key;

CCtrl_Key::CCtrl_Key (void) : TBase(), m_state(e_state::e_none){}
CCtrl_Key::CCtrl_Key (const CCtrl_Key& _src) : CCtrl_Key() { *this = _src; }
CCtrl_Key::CCtrl_Key (CCtrl_Key&& _victim) : CCtrl_Key() { *this = _victim; }

CCtrl_Key::e_state CCtrl_Key::State (void) const { return this->m_state; }
bool  CCtrl_Key::State (const e_state _u_state) {
	TBase::Is_changed() = _u_state != this->State(); if (TBase::Is_changed()) this->m_state = _u_state; return TBase::Is_changed();
}

bool CCtrl_Key::Is_pressed (void) const { return this->State() == e_state::e_pressed; }
bool CCtrl_Key::Is_released (void) const { return this->State() == e_state::e_released; }

CCtrl_Key& CCtrl_Key::operator = (const CCtrl_Key& _src) { (TBase&)*this = (const TBase&)_src; *this << _src.State(); return *this; }
CCtrl_Key& CCtrl_Key::operator = (CCtrl_Key&& _victim) { *this = (const CCtrl_Key&)_victim; return *this; }
CCtrl_Key& CCtrl_Key::operator <<(const e_state _e_state) { this->State(_e_state); return *this; }

const
CKey_Base& CCtrl_Key::operator ()(void) const { return (TBase&)*this; }
CKey_Base& CCtrl_Key::operator ()(void)       { return (TBase&)*this; }

#pragma endregion
#pragma region cls::CLock_Key{}

using CLock_Key = shared::console::events::input::CLock_Key;

CLock_Key::CLock_Key (void) : m_turn(e_turn::e_off) {}
CLock_Key::CLock_Key (const CLock_Key& _src) : CLock_Key() { *this = _src; }
CLock_Key::CLock_Key (CLock_Key&& _victim) : CLock_Key() { *this =  _victim; }

bool  CLock_Key::Is_turned (void) const { return this->Turn() == e_turn::e_on; }
bool  CLock_Key::Is_turned (const e_turn _on_or_off) {
	TBase::Is_changed() = _on_or_off != this->Turn(); if (TBase::Is_changed()) this->m_turn = _on_or_off; return TBase::Is_changed();
}

CLock_Key::e_turn CLock_Key::Turn (void) const { return this->m_turn; }

CLock_Key& CLock_Key::operator = (const CLock_Key& _src) { (TBase&)*this = (const TBase&)_src; *this << _src.Turn(); return *this; }
CLock_Key& CLock_Key::operator = (CLock_Key&& _victim)   { *this = (const CLock_Key&)_victim; return *this; }

CLock_Key& CLock_Key::operator <<(const e_turn _e_turn)  { this->Is_turned(_e_turn); return *this; }

const
CKey_Base& CLock_Key::operator ()(void) const { return (TBase&)*this; }
CKey_Base& CLock_Key::operator ()(void)       { return (TBase&)*this; }

#pragma endregion
#pragma region cls::CKey_enum{}

input::CKey_enum::CKey_enum (void) : m_ctrl(v_psd_count, CCtrl_Key()), m_lock(v_lck_count, CLock_Key()) {
	this->m_ctrl.reserve(v_psd_count);
	this->m_lock.reserve(v_lck_count);

	for (uint32_t i_ = 0; i_ < v_psd_count; i_++) {
		CCtrl_Key& ctrl_key = this->m_ctrl.at(i_);

		 ctrl_key() << v_psd_codes[i_] << p_psd_names[i_];
	}

	for (uint32_t i_ = 0; i_ < v_lck_count; i_++) {
		CLock_Key& lock_key = this->m_lock.at(i_);

		 lock_key() << v_lck_codes[i_] << p_lck_names[i_];
	}
}

static CCtrl_Key inv_ctrl_key;
static CLock_Key inv_lock_key;

// yes, using the std::map class would be better;
CCtrl_Key& _get_ctrl_key (const dword _v_code, const input::ctrl_keys_t& _keys) {
	_v_code; _keys;
	input::ctrl_keys_t& keys_ = const_cast<input::ctrl_keys_t&>(_keys);
	if (_v_code == VK_LCONTROL || _v_code == LEFT_CTRL_PRESSED ) return keys_.at(0);
	if (_v_code == VK_RCONTROL || _v_code == RIGHT_CTRL_PRESSED) return keys_.at(1);

	if (_v_code == VK_LSHIFT || _v_code == SHIFT_PRESSED) return keys_.at(2);
	if (_v_code == VK_RSHIFT) return keys_.at(3);

	if (_v_code == VK_LMENU || _v_code == LEFT_ALT_PRESSED ) return keys_.at(4);
	if (_v_code == VK_RMENU || _v_code == RIGHT_ALT_PRESSED) return keys_.at(5);

	return inv_ctrl_key;
}

CLock_Key& _get_lock_key (const dword _v_code, const input::lock_keys_t& _keys) {
	_v_code; _keys;
	input::lock_keys_t& keys_ = const_cast<input::lock_keys_t&>(_keys);
	if (_v_code == VK_CAPITAL || _v_code == CAPSLOCK_ON )  return keys_.at(0);
	if (_v_code == VK_NUMLOCK || _v_code == NUMLOCK_ON )   return keys_.at(1);
	if (_v_code == VK_SCROLL  || _v_code == SCROLLLOCK_ON) return keys_.at(2);
	
	return inv_lock_key;
}

const
input::CCtrl_Key& input::CKey_enum::Get_Ctrl (const dword _v_code) const { return _get_ctrl_key(_v_code, this->m_ctrl); }
input::CCtrl_Key& input::CKey_enum::Get_Ctrl (const dword _v_code)       { return _get_ctrl_key(_v_code, this->m_ctrl); }
const
input::CLock_Key& input::CKey_enum::Get_Lock (const dword _v_code) const { return _get_lock_key(_v_code, this->m_lock); }
input::CLock_Key& input::CKey_enum::Get_Lock (const dword _v_code)       { return _get_lock_key(_v_code, this->m_lock); }

const input::ctrl_keys_t& input::CKey_enum::Set_Ctrl (void) {
	
	for (uint32_t i_ = 0; i_ < m_ctrl.size(); i_++) {

		input::CCtrl_Key& ctrl_key = this->m_ctrl.at(i_);
		ctrl_key() << false; // marks the object state as unchanged;

		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getasynckeystate ;
		const bool b_pressed = ::GetAsyncKeyState(ctrl_key.Code()) < 0;

		if (false == b_pressed && ctrl_key.Is_pressed() == true ) ctrl_key << input::CCtrl_Key::e_released;
		if (true  == b_pressed && ctrl_key.Is_pressed() == false) ctrl_key << input::CCtrl_Key::e_pressed;
	}
	return this->m_ctrl;
}

const input::ctrl_keys_t& input::CKey_enum::Set_Ctrl (const dword _ctrl_state) {
	_ctrl_state;
	this->Get_Ctrl(VK_LMENU) << ((_ctrl_state & LEFT_ALT_PRESSED ) ? input::CCtrl_Key::e_pressed : input::CCtrl_Key::e_released);
	this->Get_Ctrl(VK_RMENU) << ((_ctrl_state & RIGHT_ALT_PRESSED) ? input::CCtrl_Key::e_pressed : input::CCtrl_Key::e_released);

	this->Get_Ctrl(VK_LCONTROL) << ((_ctrl_state & LEFT_CTRL_PRESSED )? input::CCtrl_Key::e_pressed : input::CCtrl_Key::e_released);
	this->Get_Ctrl(VK_RCONTROL) << ((_ctrl_state & RIGHT_CTRL_PRESSED)? input::CCtrl_Key::e_pressed : input::CCtrl_Key::e_released);

	this->Get_Ctrl(VK_LSHIFT) << ((_ctrl_state & SHIFT_PRESSED) ? input::CCtrl_Key::e_pressed : input::CCtrl_Key::e_released);
	this->Get_Ctrl(VK_RSHIFT) << (input::CCtrl_Key::e_released);  // the console input does not distinguish left and right shift buttons;

	return this->m_ctrl;
}

const input::lock_keys_t& input::CKey_enum::Set_Lock (void) {
	
	for (uint32_t i_ = 0; i_ < m_lock.size(); i_++) {

		input::CLock_Key& lock_key = this->m_lock.at(i_);
		lock_key() << false; // marks the object state as unchanged;

		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getasynckeystate ;
		const bool b_pressed = ::GetAsyncKeyState(lock_key.Code()) < 0;

		if (false == b_pressed && lock_key.Is_turned() == true ) lock_key << input::CLock_Key::e_off;
		if (true  == b_pressed && lock_key.Is_turned() == false) lock_key << input::CLock_Key::e_on ;
	}
	return this->m_lock;
}

const input::lock_keys_t& input::CKey_enum::Set_Lock (const dword _lock_state) {
	_lock_state;
	this->Get_Lock(VK_CAPITAL) << ((_lock_state & CAPSLOCK_ON)   ? input::CLock_Key::e_on : input::CLock_Key::e_off);
	this->Get_Lock(VK_NUMLOCK) << ((_lock_state & NUMLOCK_ON )   ? input::CLock_Key::e_on : input::CLock_Key::e_off);
	this->Get_Lock(VK_SCROLL ) << ((_lock_state & SCROLLLOCK_ON) ? input::CLock_Key::e_on : input::CLock_Key::e_off);

	return this->m_lock;
}

#pragma endregion
#pragma region cls::CRouterBase{}

CRouterBase::CRouterBase (void) : m_turned(false) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError&  CRouterBase::Error (void) const { return this->m_error; }
bool     CRouterBase::Is_on (void) const { return this->m_turned; }

#pragma endregion
#pragma region cls::ctrl::CEvent{}

using evt_source = ctrl::CEvent::evt_source;

evt_source ctrl::CEvent::DwordToEnum (const dword _u_value) {
	_u_value;
	evt_source e_evt_src = evt_source::e__undef;
	switch (_u_value) {
	case evt_source::e_abort:
	case evt_source::e_break:
	case evt_source::e_close: case evt_source::e_logoff: case evt_source::e_shutdown : e_evt_src = (evt_source)_u_value; break;
	}
	return e_evt_src;
}

CString ctrl::CEvent::To_str (const evt_source _e_src) {
	_e_src;
	CString cs_out;
	switch (_e_src) {
	case evt_source::e_abort   : cs_out = _T("[ctrl] + [c]"); break;
	case evt_source::e_break   : cs_out = _T("[ctrl] + [break]"); break;
	case evt_source::e_close   : cs_out = _T("[x] or cmd:end task"); break;
	case evt_source::e_logoff  : cs_out = _T("user logoff"); break;
	case evt_source::e_shutdown: cs_out = _T("shut down"); break;
	default: cs_out = _T("#undef");
	}
	return cs_out;
}

#pragma endregion
#pragma region cls::ctrl::CRouter{}

ctrl::CRouter:: CRouter (void) : TBase() { TBase::m_error >>__CLASS__; }
ctrl::CRouter::~CRouter (void) { if (TBase::Is_on()) this->Turn(false); }

err_code ctrl::CRouter::Subscribe (const ctrl::IEvtHandler* _p_handler) {
	_p_handler;
	TBase::m_error <<__METHOD__<<__s_ok;
	if (nullptr == _p_handler)
		return TBase::m_error <<__e_pointer = p_err_evt_handler_ptr;

	TCtrlHandlers& handlers = ::Get_ctrl_handlers();
	TCtrlHandlers::const_iterator it_ = handlers.find(_p_handler);

	if (it_ != handlers.end())
		return TBase::m_error << (err_code) TErrCodes::eObject::eExists = TString().Format(p_err_subscribed, TString()._addr_of(_p_handler, _T("0x%08x")));

	try {
		handlers.insert(_p_handler);
	}
	catch (const ::std::bad_alloc&) { TBase::m_error << __e_no_memory; }

	return TBase::Error();
}

err_code ctrl::CRouter::Unsubscribe (const ctrl::IEvtHandler* _p_handler) {
	_p_handler;
	TBase::m_error <<__METHOD__<<__s_ok;
	if (nullptr == _p_handler)
		return TBase::m_error <<__e_pointer = p_err_evt_handler_ptr;

	TCtrlHandlers& handlers = ::Get_ctrl_handlers();
	TCtrlHandlers::const_iterator it_ = handlers.find(_p_handler);

	if (it_ != handlers.end())
		return TBase::m_error << (err_code) TErrCodes::eObject::eExists = TString().Format(p_err_not_found, TString()._addr_of(_p_handler, _T("0x%08x")));

	handlers.erase(it_);

	return this->Error();
}

err_code ctrl::CRouter::Turn (const bool _b_on_off) {
	_b_on_off;
	TBase::m_error <<__METHOD__<<__s_ok;
	// https://learn.microsoft.com/en-us/windows/console/setconsolectrlhandler ;
	if (_b_on_off) {
		if (this->Is_on())
			return TBase::m_error << (err_code) TErrCodes::eExecute::eState = p_err_router_on;
		if (false == !!::SetConsoleCtrlHandler(ctrl::CRouter::Receive_evt, true))
		     TBase::m_error.Last();
		else TBase::m_turned = true;
	}
	else {
		if (this->Is_on() == false)
			return TBase::m_error << (err_code) TErrCodes::eExecute::eState = p_err_router_off;

		if (false == !!::SetConsoleCtrlHandler(ctrl::CRouter::Receive_evt, false))
		     TBase::m_error.Last();
		else TBase::m_turned = false;
	}

	return TBase::Error();
}

err_code ctrl::CRouter::operator <<(const ctrl::IEvtHandler* _p_handler) { return this->Subscribe(_p_handler); }
err_code ctrl::CRouter::operator >>(const ctrl::IEvtHandler* _p_handler) { return this->Unsubscribe(_p_handler); }

int ctrl::CRouter::Receive_evt (const dword dwCtrlType) {
	dwCtrlType;
	TCtrlHandlers& handlers = ::Get_ctrl_handlers();
	TCtrlHandlers::iterator it_;

	bool b_result = false; // not handled;

	__trace_warn_2(_T("close control event source: '%s';\n"), (_pc_sz) ctrl::CEvent::To_str(ctrl::CEvent::DwordToEnum(dwCtrlType)));

	for (it_ = handlers.begin(); it_ != handlers.end(); ++it_) {
		if (nullptr == *it_)
			continue;

		ctrl::IEvtHandler* p_handler = const_cast<ctrl::IEvtHandler*>(*it_);

		// https://learn.microsoft.com/en-us/windows/console/handlerroutine ;
		b_result = __s_ok == p_handler->On_close(ctrl::CEvent::DwordToEnum(dwCtrlType));
		if (b_result)
			break;
	}
	return b_result;
}

#pragma endregion

namespace shared { namespace console { namespace _impl {

	CString ctrl_key_to_str (const uint32_t _u_key_state) {
		_u_key_state;
		static _pc_sz p_sz_ctrl_keys  = _T("ctrl key: %s");
		CString cs_keys;
		if (CAPSLOCK_ON        & _u_key_state) { if (cs_keys.IsEmpty() == false) cs_keys += _T("|"); cs_keys += _T("caps lock"); }
		if (ENHANCED_KEY       & _u_key_state) { if (cs_keys.IsEmpty() == false) cs_keys += _T("|"); cs_keys += _T("enhanced"); }
		if (LEFT_ALT_PRESSED   & _u_key_state) { if (cs_keys.IsEmpty() == false) cs_keys += _T("|"); cs_keys += _T("left alt"); }
		if (LEFT_CTRL_PRESSED  & _u_key_state) { if (cs_keys.IsEmpty() == false) cs_keys += _T("|"); cs_keys += _T("left ctrl"); }
		if (NUMLOCK_ON         & _u_key_state) { if (cs_keys.IsEmpty() == false) cs_keys += _T("|"); cs_keys += _T("num lock"); }
		if (RIGHT_ALT_PRESSED  & _u_key_state) { if (cs_keys.IsEmpty() == false) cs_keys += _T("|"); cs_keys += _T("right alt"); }
		if (RIGHT_CTRL_PRESSED & _u_key_state) { if (cs_keys.IsEmpty() == false) cs_keys += _T("|"); cs_keys += _T("right ctrl"); }
		if (SCROLLLOCK_ON      & _u_key_state) { if (cs_keys.IsEmpty() == false) cs_keys += _T("|"); cs_keys += _T("scroll lock"); }
		if (SHIFT_PRESSED      & _u_key_state) { if (cs_keys.IsEmpty() == false) cs_keys += _T("|"); cs_keys += _T("shift"); }

		cs_keys = TString().Format(p_sz_ctrl_keys, cs_keys.IsEmpty() ? _T("none") : (_pc_sz) cs_keys );
		return cs_keys;
	}

}}} using namespace _impl;

#pragma region cls::input::CEvent{}

CString  input::CEvent::To_str (const evt_menu_data_t& _data) {
	_data;
	CString cs_out; cs_out.Format(_T("menu event >> {cmd_id = %u}"), _data.dwCommandId);
	return  cs_out;
}

CString  input::CEvent::To_str (const evt_mouse_data_t& _data, const evt_mouse _e_mouse) {
	_data; _e_mouse;
	CString cs_pos; cs_pos.Format(_T("cell = {x:%u|y:%u}"), _data.dwMousePosition.X, _data.dwMousePosition.Y);

	static _pc_sz p_sz_action = _T("action: %s");
	static _pc_sz p_sz_btn_press = _T("button pressed: [%s]");
	static _pc_sz p_sz_btn_released = _T("button released: [%s]");

	CString cs_out;

	/* https://learn.microsoft.com/en-us/windows/console/mouse-event-record-str ;
	   the excerpt from the above article:
	   (dwEventFlags) If this value is zero, it indicates a mouse button being pressed or released.
	   ...
	   but the mouse can be moved with a button being pressed, for example, making selection of the part of window content;
	*/

	if (evt_mouse::e_move == _e_mouse) {
		CString cs_action;
		if (DOUBLE_CLICK   == _data.dwEventFlags) cs_action.Format(p_sz_action, _T("double click"));
		if (MOUSE_HWHEELED == _data.dwEventFlags) cs_action.Format(p_sz_action, _T("horz wheel"));
		if (MOUSE_MOVED    == _data.dwEventFlags) cs_action.Format(p_sz_action, _T("moving"));
		if (MOUSE_WHEELED  == _data.dwEventFlags) cs_action.Format(p_sz_action, _T("vert wheel"));
		if (0 != _data.dwEventFlags)/* cs_action.Format(p_sz_action, _T("no action"));*/
			cs_out.Format(_T("mouse event >> %s; %s"), (_pc_sz) cs_action, (_pc_sz) ctrl_key_to_str(_data.dwControlKeyState));
	}

	if (evt_mouse::e_button == _e_mouse) {
		static CString cs_last;
		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getasynckeystate ;

		CString cs_button;
		if (0 != _data.dwButtonState) { // one of the mouse button is pressed;
			if (FROM_LEFT_1ST_BUTTON_PRESSED == _data.dwButtonState) cs_button.Format(p_sz_btn_press, (_pc_sz)(cs_last = _T("left")));
			if (FROM_LEFT_2ND_BUTTON_PRESSED == _data.dwButtonState) cs_button.Format(p_sz_btn_press, (_pc_sz)(cs_last = _T("left + 1")));
			if (FROM_LEFT_3RD_BUTTON_PRESSED == _data.dwButtonState) cs_button.Format(p_sz_btn_press, (_pc_sz)(cs_last = _T("left + 2")));
			if (FROM_LEFT_4TH_BUTTON_PRESSED == _data.dwButtonState) cs_button.Format(p_sz_btn_press, (_pc_sz)(cs_last = _T("left + 3")));
			if (RIGHTMOST_BUTTON_PRESSED     == _data.dwButtonState) cs_button.Format(p_sz_btn_press, (_pc_sz)(cs_last = _T("right")));
		}
		else if (false == cs_last.IsEmpty()) cs_button.Format(p_sz_btn_released, (_pc_sz) cs_last);
		else cs_button.Format(p_sz_btn_press, _T("none")); // mouse movement or double click occurs;

		cs_out.Format(_T("mouse event >> %s; %s"), (_pc_sz) cs_button, (_pc_sz) ctrl_key_to_str(_data.dwControlKeyState));
	}
	return  cs_out;
}

CString  input::CEvent::To_str (const evt_kbrd_data_t& _data) {
	_data;
	static _pc_sz p_kbrd_evt = _T("key code: %u; state: '%s'; repeated: '%s'; %s");

	// https://learn.microsoft.com/en-us/windows/console/key-event-record-str#remarks ;
	CString cs_state;  cs_state = _data.bKeyDown ? _T("pressed") : _T("released");
	CString cs_out; cs_out.Format(
		p_kbrd_evt, _data.wVirtualKeyCode, (_pc_sz) cs_state,  TString().Bool(_data.wRepeatCount), (_pc_sz) ctrl_key_to_str(_data.dwControlKeyState));
	return  cs_out;
}

CString  input::CEvent::To_str (const evt_buff_size_t& _data) {
	_data;
	CString cs_out; cs_out.Format(_T("size = {x:%u|y:%u}"), _data.dwSize.X, _data.dwSize.Y);
	return  cs_out;
}

#pragma endregion
#pragma region cls::input::CRouter{}

input::CRouter:: CRouter (void) : TBase() { TBase::m_error >>__CLASS__; }
input::CRouter::~CRouter (void) { if (TBase::Is_on()) this->Turn(false); }

err_code input::CRouter::Turn (const bool _b_on_off) {
	_b_on_off;
	TBase::m_error <<__METHOD__<<__s_ok;

	if (_b_on_off) {
		if (this->Is_on())
			return TBase::m_error << (err_code) TErrCodes::eExecute::eState = p_err_router_on;

		this->m_thread = ::std::thread(&input::CRouter::Receive_evt, this);
		TBase::m_turned = true;
	}
	else {
		if (this->Is_on() == false)
			return TBase::m_error << (err_code) TErrCodes::eExecute::eState = p_err_router_off;

		TBase::m_turned = false;
		this->m_thread.join();
	}

	return TBase::Error();
}

err_code input::CRouter::Subscribe (const input::IEvtHandler* _p_handler) {
	_p_handler;
	TBase::m_error <<__METHOD__<<__s_ok;
	if (nullptr == _p_handler)
		return TBase::m_error <<__e_pointer = p_err_evt_handler_ptr;

	TInputHandlers& handlers = ::Get_input_handlers();
	TInputHandlers::const_iterator it_ = handlers.find(_p_handler);

	if (it_ != handlers.end())
		return TBase::m_error << (err_code) TErrCodes::eObject::eExists = TString().Format(p_err_subscribed, TString()._addr_of(_p_handler, _T("0x%08x")));

	try {
		handlers.insert(_p_handler);
	}
	catch (const ::std::bad_alloc&) { TBase::m_error << __e_no_memory; }

	return TBase::Error();
}

err_code input::CRouter::Unsubscribe (const input::IEvtHandler* _p_handler) {
	_p_handler;
	TBase::m_error <<__METHOD__<<__s_ok;
	if (nullptr == _p_handler)
		return TBase::m_error <<__e_pointer = p_err_evt_handler_ptr;

	TInputHandlers& handlers = ::Get_input_handlers();
	TInputHandlers::const_iterator it_ = handlers.find(_p_handler);

	if (it_ != handlers.end())
		return TBase::m_error << (err_code) TErrCodes::eObject::eExists = TString().Format(p_err_not_found, TString()._addr_of(_p_handler, _T("0x%08x")));

	handlers.erase(it_);

	return this->Error();
}

err_code input::CRouter::operator <<(const input::IEvtHandler* _p_handler) { return this->Subscribe(_p_handler); }
err_code input::CRouter::operator >>(const input::IEvtHandler* _p_handler) { return this->Unsubscribe(_p_handler); }

#define SIZE_EVENT WINDOW_BUFFER_SIZE_EVENT

void input::CRouter::Receive_evt (void) {
	TBase::m_error <<__METHOD__<<__s_ok; // error object can work in multi threaded environment;
	
	// disables quick edit mode because it interfers with receiving mouse inputs;
	static const ulong u_req_flags = (ENABLE_WINDOW_INPUT|ENABLE_MOUSE_INPUT|ENABLE_EXTENDED_FLAGS) & ~ENABLE_QUICK_EDIT_MODE;
	static const ulong u_rec_size  =  128;

	modes::CInput input;
	if (__failed( input.Get() )) { TBase::m_error = input.Error(); TBase::m_turned = false; return; }
	if (__failed( input << (input.Flags() | u_req_flags))) { TBase::m_error = input.Error(); TBase::m_turned = false; return; }

	ulong u_recs = 0;
	ulong u_read = 0;
//	INPUT_RECORD in_recs[u_rec_size] = {0};
//	https://learn.microsoft.com/en-us/windows/console/reading-input-buffer-events ;
	while (this->m_turned) {

		::std::this_thread::sleep_for(::std::chrono::milliseconds(50));

		// https://learn.microsoft.com/en-us/windows/console/getnumberofconsoleinputevents ;
		if (false == !!::GetNumberOfConsoleInputEvents(__in_handle, &u_recs)) {
			TBase::m_error.Last(); break;
		}
		if (0 == u_recs)
			continue;
		// https://learn.microsoft.com/en-us/windows/console/input-record-str ;
		::std::vector<INPUT_RECORD> v_recs(u_recs, {0});

		if (false == ::ReadConsoleInput(__in_handle, v_recs.data(), u_recs, &u_read)) {
			TBase::m_error.Last(); break;
		}

		TInputHandlers& handlers = ::Get_input_handlers();
		TInputHandlers::iterator it_;

		for (it_ = handlers.begin(); it_ != handlers.end(); ++it_) {
			if (nullptr == *it_)
				continue;

			input::IEvtHandler* p_handler = const_cast<input::IEvtHandler*>(*it_);

			for (ulong i_ = 0; i_ < v_recs.size(); i_++) {
				if (false){}
				else if (KEY_EVENT   == v_recs.at(i_).EventType) { p_handler->On_kbrd (v_recs.at(i_).Event.KeyEvent); }
				else if (MENU_EVENT  == v_recs.at(i_).EventType) { p_handler->On_menu (v_recs.at(i_).Event.MenuEvent); }
				else if (SIZE_EVENT  == v_recs.at(i_).EventType) { p_handler->On_size (v_recs.at(i_).Event.WindowBufferSizeEvent ); }
				else if (MOUSE_EVENT == v_recs.at(i_).EventType) { p_handler->On_mouse(v_recs.at(i_).Event.MouseEvent); }
			}
		}
	}
	TBase::m_turned = false;

	return;
}

#pragma endregion
#pragma region cls::CHandler_Dflt{}

err_code CHandler_Dflt::On_close(const ctrl::CEvent::evt_source _dw_reason) {
	__trace_warn_2(_T("%s\n"), (_pc_sz) ctrl::CEvent().To_str(_dw_reason)); return __s_ok;
}

err_code CHandler_Dflt::On_menu (const input::evt_menu_data_t& _data) {
	__trace_impt_2(_T("%s\n"), (_pc_sz) input::CEvent().To_str(_data)); return __s_ok;
}

err_code CHandler_Dflt::On_mouse (const input::evt_mouse_data_t& _data) {
	_data;
	if (0 == _data.dwEventFlags)
		return this->On_button(_data);
	else
		return this->On_move(_data);
}

err_code CHandler_Dflt::On_kbrd (const input::evt_kbrd_data_t& _data) {
	static input::evt_kbrd_data_t data_ = {0};
	const
	bool b_changed = data_.bKeyDown != _data.bKeyDown || data_.wVirtualKeyCode != _data.wVirtualKeyCode || data_.dwControlKeyState != _data.dwControlKeyState;

	if (b_changed) {
		data_ = _data;
		__trace_info(_T("%s\n"), (_pc_sz) input::CEvent().To_str(_data)); return __s_ok;
	}
	else return __s_false;
}

err_code CHandler_Dflt::On_size (const input::evt_buff_size_t _data) {
	__trace_info(_T("%s\n"), (_pc_sz) input::CEvent().To_str(_data)); return __s_ok;
}

err_code CHandler_Dflt::On_button (const input::evt_mouse_data_t& _data) {

	static input::evt_mouse_data_t data_ = {0};
	bool b_changed = false;
	
	if (false == b_changed) b_changed = 0 == data_.dwEventFlags && data_.dwButtonState != _data.dwButtonState; // data_.dwEventFlags must be equal to 0;
	
	if (b_changed) {
		data_ = _data;
		__trace_info(_T("%s\n"), (_pc_sz) input::CEvent().To_str(_data, input::CEvent::e_button)); return __s_ok;
	}
	else return __s_false;
}

err_code CHandler_Dflt::On_move (const input::evt_mouse_data_t& _data) {

	static const uint32_t u_threshould = 3;
	static input::evt_mouse_data_t data_ = {0};
	bool b_changed = false;
	
	if (false == b_changed) b_changed = 0 != _data.dwEventFlags  // data_.dwEventFlags must be not equal to 0;
		 && abs(data_.dwMousePosition.X - _data.dwMousePosition.X) > u_threshould;
	
	if (b_changed) {
		data_ = _data;
		__trace_info(_T("%s\n"), (_pc_sz) input::CEvent().To_str(_data, input::CEvent::e_move)); return __s_ok;
	}
	else return __s_false;
}

#pragma endregion

bool operator != (const COORD& _left, const COORD& _right) {
	return _left.X != _right.X || _left.Y != _right.Y;
}

bool operator == (const COORD& _left, const COORD& _right) {
	return false == (_left != _right);
}

TCtrlRouter&  ::Get_ctrl (void) {
	static TCtrlRouter ctrl_router;
	return ctrl_router;
}

TInputRouter& ::Get_input (void) {
	static TInputRouter input_router;
	return input_router;
}