/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-Apr-2026 at 17:55:07.872, (UTC+4), Batumi, Monday;
	This is Ebo Pack console control key interface implementation file;
*/
#include "console.evt.key.h"

using namespace shared::console::events::input;

#pragma region cls::CKey_Base{}

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
#pragma region cls::CLock_Key{}

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
#pragma region cls::CCtrl_Key{}

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
#pragma region cls::CKey_enum{}

CKey_enum::CKey_enum (void) : m_ctrl(v_psd_count, CCtrl_Key()), m_lock(v_lck_count, CLock_Key()) {
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
CCtrl_Key& _get_ctrl_key (const dword _v_code, const ctrl_keys_t& _keys) {
	_v_code; _keys;
	ctrl_keys_t& keys_ = const_cast<ctrl_keys_t&>(_keys);
	if (_v_code == VK_LCONTROL || _v_code == LEFT_CTRL_PRESSED ) return keys_.at(0);
	if (_v_code == VK_RCONTROL || _v_code == RIGHT_CTRL_PRESSED) return keys_.at(1);

	if (_v_code == VK_LSHIFT || _v_code == SHIFT_PRESSED) return keys_.at(2);
	if (_v_code == VK_RSHIFT) return keys_.at(3);

	if (_v_code == VK_LMENU || _v_code == LEFT_ALT_PRESSED ) return keys_.at(4);
	if (_v_code == VK_RMENU || _v_code == RIGHT_ALT_PRESSED) return keys_.at(5);

	return inv_ctrl_key;
}

CLock_Key& _get_lock_key (const dword _v_code, const lock_keys_t& _keys) {
	_v_code; _keys;
	lock_keys_t& keys_ = const_cast<lock_keys_t&>(_keys);
	if (_v_code == VK_CAPITAL || _v_code == CAPSLOCK_ON )  return keys_.at(0);
	if (_v_code == VK_NUMLOCK || _v_code == NUMLOCK_ON )   return keys_.at(1);
	if (_v_code == VK_SCROLL  || _v_code == SCROLLLOCK_ON) return keys_.at(2);
	
	return inv_lock_key;
}

const
CCtrl_Key& CKey_enum::Get_Ctrl (const dword _v_code) const { return _get_ctrl_key(_v_code, this->m_ctrl); }
CCtrl_Key& CKey_enum::Get_Ctrl (const dword _v_code)       { return _get_ctrl_key(_v_code, this->m_ctrl); }
const
CLock_Key& CKey_enum::Get_Lock (const dword _v_code) const { return _get_lock_key(_v_code, this->m_lock); }
CLock_Key& CKey_enum::Get_Lock (const dword _v_code)       { return _get_lock_key(_v_code, this->m_lock); }

const ctrl_keys_t& CKey_enum::Set_Ctrl (void) {
	
	for (uint32_t i_ = 0; i_ < m_ctrl.size(); i_++) {

		CCtrl_Key& ctrl_key = this->m_ctrl.at(i_);
		ctrl_key() << false; // marks the object state as unchanged;

		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getasynckeystate ;
		const bool b_pressed = ::GetAsyncKeyState(ctrl_key.Code()) < 0;

		if (false == b_pressed && ctrl_key.Is_pressed() == true ) ctrl_key << CCtrl_Key::e_released;
		if (true  == b_pressed && ctrl_key.Is_pressed() == false) ctrl_key << CCtrl_Key::e_pressed;
	}
	return this->m_ctrl;
}

const ctrl_keys_t& CKey_enum::Set_Ctrl (const dword _ctrl_state) {
	_ctrl_state;
	this->Get_Ctrl(VK_LMENU) << ((_ctrl_state & LEFT_ALT_PRESSED ) ? CCtrl_Key::e_pressed : CCtrl_Key::e_released);
	this->Get_Ctrl(VK_RMENU) << ((_ctrl_state & RIGHT_ALT_PRESSED) ? CCtrl_Key::e_pressed : CCtrl_Key::e_released);

	this->Get_Ctrl(VK_LCONTROL) << ((_ctrl_state & LEFT_CTRL_PRESSED )? CCtrl_Key::e_pressed : CCtrl_Key::e_released);
	this->Get_Ctrl(VK_RCONTROL) << ((_ctrl_state & RIGHT_CTRL_PRESSED)? CCtrl_Key::e_pressed : CCtrl_Key::e_released);

	this->Get_Ctrl(VK_LSHIFT) << ((_ctrl_state & SHIFT_PRESSED) ? CCtrl_Key::e_pressed : CCtrl_Key::e_released);
	this->Get_Ctrl(VK_RSHIFT) << (CCtrl_Key::e_released);  // the console input does not distinguish left and right shift buttons;

	return this->m_ctrl;
}

const lock_keys_t& CKey_enum::Set_Lock (void) {
	
	for (uint32_t i_ = 0; i_ < m_lock.size(); i_++) {

		CLock_Key& lock_key = this->m_lock.at(i_);
		lock_key() << false; // marks the object state as unchanged;

		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getasynckeystate ;
		const bool b_pressed = ::GetAsyncKeyState(lock_key.Code()) < 0;

		if (false == b_pressed && lock_key.Is_turned() == true ) lock_key << CLock_Key::e_off;
		if (true  == b_pressed && lock_key.Is_turned() == false) lock_key << CLock_Key::e_on ;
	}
	return this->m_lock;
}

const lock_keys_t& CKey_enum::Set_Lock (const dword _lock_state) {
	_lock_state;
	this->Get_Lock(VK_CAPITAL) << ((_lock_state & CAPSLOCK_ON)   ? CLock_Key::e_on : CLock_Key::e_off);
	this->Get_Lock(VK_NUMLOCK) << ((_lock_state & NUMLOCK_ON )   ? CLock_Key::e_on : CLock_Key::e_off);
	this->Get_Lock(VK_SCROLL ) << ((_lock_state & SCROLLLOCK_ON) ? CLock_Key::e_on : CLock_Key::e_off);

	return this->m_lock;
}

#pragma endregion