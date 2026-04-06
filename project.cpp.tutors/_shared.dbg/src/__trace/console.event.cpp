/*
	Created by Tech_dog (ebontrop@gmsil.com) on 22-Mar-2026 at 14:12:02.641, UTC+4, Batumi, Sunday;
	This is Ebo Pack console event handler interface implementation file;
*/
#include "console.event.h"
#include "shared.preproc.h"

using namespace shared::console;
using namespace shared::console::events;

using CSyncObject = shared::sys_core::CSyncObject;
CSyncObject& EvtGuardRef(void) { static CSyncObject crt_sect; return crt_sect; }

#define Input_Safe_Lock() Safe_Lock(EvtGuardRef());

typedef ::std::set<const input::IEvtHandler*> TInputHandlers;

TInputHandlers& Get_input_handlers (void) { static TInputHandlers handlers; return handlers; }

static _pc_sz p_err_evt_handler_ptr = _T("$__e_ptr: input pointer to event handler is invalid");
static _pc_sz pc_sz_pat_subscribed = _T("The handler = %s is already subscribed");
static _pc_sz pc_sz_pat_not_found = _T("The handler = %s is not found");

#pragma region cls::ctrl::CRouter{}

ctrl::CRouter::CRouter (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& ctrl::CRouter::Error (void) const { return this->m_error; }

#pragma endregion

namespace shared { namespace console { namespace _impl {

	CString ctrl_key_to_str (const uint32_t _u_key_state) {
		_u_key_state;
		static _pc_sz p_sz_ctrl_keys  = _T("ctrl key: %s");
		CString cs_keys;
		if (CAPSLOCK_ON        == _u_key_state) { if (cs_keys.IsEmpty() == false) cs_keys += _T("|"); cs_keys += _T("caps lock"); }
		if (ENHANCED_KEY       == _u_key_state) { if (cs_keys.IsEmpty() == false) cs_keys += _T("|"); cs_keys += _T("enhanced"); }
		if (LEFT_ALT_PRESSED   == _u_key_state) { if (cs_keys.IsEmpty() == false) cs_keys += _T("|"); cs_keys += _T("left alt"); }
		if (LEFT_CTRL_PRESSED  == _u_key_state) { if (cs_keys.IsEmpty() == false) cs_keys += _T("|"); cs_keys += _T("left ctrl"); }
		if (NUMLOCK_ON         == _u_key_state) { if (cs_keys.IsEmpty() == false) cs_keys += _T("|"); cs_keys += _T("num lock"); }
		if (RIGHT_ALT_PRESSED  == _u_key_state) { if (cs_keys.IsEmpty() == false) cs_keys += _T("|"); cs_keys += _T("right alt"); }
		if (RIGHT_CTRL_PRESSED == _u_key_state) { if (cs_keys.IsEmpty() == false) cs_keys += _T("|"); cs_keys += _T("right ctrl"); }
		if (SCROLLLOCK_ON      == _u_key_state) { if (cs_keys.IsEmpty() == false) cs_keys += _T("|"); cs_keys += _T("scroll lock"); }
		if (SHIFT_PRESSED      == _u_key_state) { if (cs_keys.IsEmpty() == false) cs_keys += _T("|"); cs_keys += _T("shift"); }
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

CString  input::CEvent::To_str (const evt_mouse_data_t& _data) {
	_data;
	CString cs_pos; cs_pos.Format(_T("cell = {x:%u|y:%u}"), _data.dwMousePosition.X, _data.dwMousePosition.Y);

	static _pc_sz p_sz_action = _T("action: %s");
	static _pc_sz p_sz_ctrl_keys  = _T("ctrl keys: %s");
	static _pc_sz p_sz_button = _T("button pressed: %s");

	CString cs_action;
	if (DOUBLE_CLICK   == _data.dwEventFlags) cs_action.Format(p_sz_action, _T("double click"));
	if (MOUSE_HWHEELED == _data.dwEventFlags) cs_action.Format(p_sz_action, _T("horz wheel"));
	if (MOUSE_MOVED    == _data.dwEventFlags) cs_action.Format(p_sz_action, _T("moving"));
	if (MOUSE_WHEELED  == _data.dwEventFlags) cs_action.Format(p_sz_action, _T("vert wheel"));

	CString cs_button;
	if (FROM_LEFT_1ST_BUTTON_PRESSED == _data.dwButtonState) cs_button.Format(p_sz_button, _T("left"));
	if (FROM_LEFT_2ND_BUTTON_PRESSED == _data.dwButtonState) cs_button.Format(p_sz_button, _T("left + 1"));
	if (FROM_LEFT_3RD_BUTTON_PRESSED == _data.dwButtonState) cs_button.Format(p_sz_button, _T("left + 2"));
	if (FROM_LEFT_4TH_BUTTON_PRESSED == _data.dwButtonState) cs_button.Format(p_sz_button, _T("left + 3"));
	if (RIGHTMOST_BUTTON_PRESSED     == _data.dwButtonState) cs_button.Format(p_sz_button, _T("right"));

	CString cs_out;
	/* https://learn.microsoft.com/en-us/windows/console/mouse-event-record-str ;
	   the excerpt from the above article:
	   (dwEventFlags) If this value is zero, it indicates a mouse button being pressed or released.
	   ...
	   but the mouse can be moved with a button being pressed, for example, making selection of the part of window content;
	*/
	const bool b_no_action = cs_action.IsEmpty();

	cs_out.Format(_T("mouse event >> %s at %s; %s"),
		b_no_action ? (_pc_sz) cs_button : (_pc_sz) cs_action, (_pc_sz) cs_pos, (_pc_sz) ctrl_key_to_str(_data.dwControlKeyState)
	);
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

CString  input::CEvent::To_str (const evt_buffer_size_t& _data) {
	_data;
	CString cs_out; cs_out.Format(_T("size = {x:%u|y:%u}"), _data.dwSize.X, _data.dwSize.Y);
	return  cs_out;
}

#pragma endregion
#pragma region cls::input::CRouter{}

input::CRouter:: CRouter (void) : m_turned(false) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
input::CRouter::~CRouter (void) { if (this->Is_on()) this->Turn(false); }

TError&  input::CRouter::Error (void) const { return this->m_error; }
bool     input::CRouter::Is_on (void) const { return this->m_turned; }
err_code input::CRouter::Turn  (const bool _b_on_off) {
	_b_on_off;
	this->m_error <<__METHOD__<<__s_ok;

	if (_b_on_off) {
		if (this->Is_on())
			return this->m_error << (err_code) TErrCodes::eExecute::eState = _T("Router is already turned on");

		this->m_thread = ::std::thread(&input::CRouter::Receive_evt, this);
		this->m_turned = true;
	}
	else {
		if (this->Is_on() == false)
			return this->m_error << (err_code) TErrCodes::eExecute::eState = _T("Router is already turned off");

		this->m_turned = false;
		this->m_thread.join();
	}

	return this->Error();
}

err_code input::CRouter::Subscribe (const input::IEvtHandler* _p_handler) {
	_p_handler;
	this->m_error <<__METHOD__<<__s_ok;
	if (nullptr == _p_handler)
		return this->m_error <<__e_pointer = p_err_evt_handler_ptr;

	TInputHandlers& handlers = ::Get_input_handlers();
	TInputHandlers::const_iterator it_ = handlers.find(_p_handler);

	if (it_ != handlers.end())
		return this->m_error << (err_code) TErrCodes::eObject::eExists = TString().Format(pc_sz_pat_subscribed, TString()._addr_of(_p_handler, _T("0x%08x")));

	try {
		handlers.insert(_p_handler);
	}
	catch (const ::std::bad_alloc&) { this->m_error << __e_no_memory; }

	return this->Error();
}

err_code input::CRouter::Unsubscribe (const input::IEvtHandler* _p_handler) {
	_p_handler;
	this->m_error <<__METHOD__<<__s_ok;
	if (nullptr == _p_handler)
		return this->m_error <<__e_pointer = p_err_evt_handler_ptr;

	TInputHandlers& handlers = ::Get_input_handlers();
	TInputHandlers::const_iterator it_ = handlers.find(_p_handler);

	if (it_ != handlers.end())
		return this->m_error << (err_code) TErrCodes::eObject::eExists = TString().Format(pc_sz_pat_subscribed, TString()._addr_of(_p_handler, _T("0x%08x")));

	handlers.erase(it_);

	return this->Error();
}

err_code input::CRouter::operator <<(const input::IEvtHandler* _p_handler) { return this->Subscribe(_p_handler); }
err_code input::CRouter::operator >>(const input::IEvtHandler* _p_handler) { return this->Unsubscribe(_p_handler); }

#define SIZE_EVENT WINDOW_BUFFER_SIZE_EVENT

void input::CRouter::Receive_evt (void) {
	this->m_error <<__METHOD__<<__s_ok; // error object can work in multi threaded environment;
	
	// disables quick edit mode because it interfers with receiving mouse inputs;
	static const ulong u_req_flags = (ENABLE_WINDOW_INPUT|ENABLE_MOUSE_INPUT|ENABLE_EXTENDED_FLAGS) & ~ENABLE_QUICK_EDIT_MODE;
	static const ulong u_rec_size  =  128;

	modes::CInput input;
	if (__failed( input.Get() )) { this->m_error = input.Error(); this->m_turned = false; return; }
	if (__failed( input << (input.Flags() | u_req_flags))) { this->m_error = input.Error(); this->m_turned = false; return; }

	ulong u_recs = 0;
	ulong u_read = 0;
//	INPUT_RECORD in_recs[u_rec_size] = {0};
//	https://learn.microsoft.com/en-us/windows/console/reading-input-buffer-events ;
	while (this->m_turned) {

		::std::this_thread::sleep_for(::std::chrono::milliseconds(50));

		// https://learn.microsoft.com/en-us/windows/console/getnumberofconsoleinputevents ;
		if (false == !!::GetNumberOfConsoleInputEvents(__in_handle, &u_recs)) {
			this->m_error.Last(); break;
		}
		if (0 == u_recs)
			continue;
		// https://learn.microsoft.com/en-us/windows/console/input-record-str ;
		::std::vector<INPUT_RECORD> v_recs(u_recs, {0});

		if (false == ::ReadConsoleInput(__in_handle, v_recs.data(), u_recs, &u_read)) {
			this->m_error.Last(); break;
		}

		TInputHandlers& handlers = Get_input_handlers();
		TInputHandlers::iterator it_;

		for (it_ = handlers.begin(); it_ != handlers.end(); ++it_) {
			if (nullptr == *it_)
				continue;

			input::IEvtHandler* p_handler = const_cast<input::IEvtHandler*>(*it_);

			for (ulong i_ = 0; i_ < v_recs.size(); i_++) {
				if (false){}
				else if (KEY_EVENT   == v_recs.at(i_).EventType) { p_handler->On_kbrd (v_recs.at(i_).Event.KeyEvent); }
				else if (MENU_EVENT  == v_recs.at(i_).EventType) { p_handler->On_menu (v_recs.at(i_).Event.MenuEvent); }
				else if (MOUSE_EVENT == v_recs.at(i_).EventType) { p_handler->On_mouse(v_recs.at(i_).Event.MouseEvent); }
				else if (SIZE_EVENT  == v_recs.at(i_).EventType) { p_handler->On_size (v_recs.at(i_).Event.WindowBufferSizeEvent ); }
			}
		}
	}
	this->m_turned = false;

	return;
}

#pragma endregion

TInputRouter& ::Get_input (void) {
	static TInputRouter input_router;
	return input_router;
}