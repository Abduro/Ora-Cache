/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-Apr-2026 at 18:32:44.373, (UTC+4), Batumi, Monday;
	This is Ebo Pack console mouse buttons' interface implementation file;
*/
#include "console.evt.btn.h"

using namespace shared::console::events::input;
using e_state = CButton::e_state;

#pragma region cls::CButton{}

CButton::CButton (const uint32_t _v_code, _pc_sz _p_name) : m_code(_v_code), m_name(_p_name), m_state(e_state::e_none) {}
CButton::CButton (const CButton& _src) : CButton() { *this = _src; }
CButton::CButton (CButton&& _victim) : CButton() { *this = _victim; }

uint32_t CButton::Code (void) const { return this->m_code; }
bool     CButton::Code (const uint32_t _v_code) {
	const bool b_changed = _v_code != this->Code(); if (b_changed) this->m_code = _v_code; return b_changed;
}

bool CButton::Is_pressed  (void) const { return e_state::e_pressed  == this->State(); }
bool CButton::Is_released (void) const { return e_state::e_released == this->State(); }
bool CButton::Is_valid (void) const { return !!this->Code(); } // name is not checked;

_pc_sz CButton::Name (void) const { return (_pc_sz)this->m_name; }
bool   CButton::Name (_pc_sz _p_name) {
	const bool b_changed = 0 == this->m_name.CompareNoCase(_p_name); if (b_changed) this->m_name = _p_name; return b_changed;
}

e_state  CButton::State (void) const { return this->m_state; }
bool     CButton::State (const e_state _e_value) {
	const bool b_changed = _e_value != this->State(); if (b_changed) this->m_state = _e_value; return b_changed;
}

CButton& CButton::operator = (const CButton& _src) { *this << _src.Code() << _src.Name() << _src.State(); return *this; }
CButton& CButton::operator = (CButton&& _victim) { *this = (const CButton&)_victim; return *this; }

CButton& CButton::operator <<(const uint32_t _v_code) { this->Code(_v_code); return *this; }
CButton& CButton::operator <<(_pc_sz _p_name) { this->Name(_p_name); return *this; }
CButton& CButton::operator <<(const CString& _cs_name) { this->Name((_pc_sz) _cs_name); return *this; }
CButton& CButton::operator <<(const e_state _e_value) { this->State(_e_value); return *this; }

#pragma endregion
#pragma region cls::CBtn_enum{}

static ctrl_btns_t g_btns = {
	CButton(v_btn_codes[0], p_btn_names[0]), CButton(v_btn_codes[1], p_btn_names[1]), CButton(v_btn_codes[2], p_btn_names[2]),
	CButton(v_btn_codes[3], p_btn_names[3]), CButton(v_btn_codes[4], p_btn_names[4])
};

CButton&  _find_btn (const uint32_t _u_code) {
	_u_code;
	for (uint32_t i_ = 0; i_ < g_btns.size(); i_++) {
		if (_u_code == g_btns.at(i_).Code())
			return g_btns.at(i_);
	}
	static CButton inv_btn; return inv_btn;
}
uint32_t  _state_to_code (const uint32_t _u_state) {
	switch (_u_state) {
	case FROM_LEFT_1ST_BUTTON_PRESSED : return VK_LBUTTON;
	case FROM_LEFT_2ND_BUTTON_PRESSED : return VK_MBUTTON;
	case FROM_LEFT_3RD_BUTTON_PRESSED : return VK_XBUTTON1;
	case FROM_LEFT_4TH_BUTTON_PRESSED : return VK_XBUTTON2;
	case RIGHTMOST_BUTTON_PRESSED     : return VK_RBUTTON;
	default: return 0;
	}
}

CBtn_enum::CBtn_enum (void) {}

const
CButton& CBtn_enum::Get (const dword _v_code) const { return ::_find_btn(_v_code); }
CButton& CBtn_enum::Get (const dword _v_code)       { return ::_find_btn(_v_code); }

const ctrl_btns_t& CBtn_enum::Set (const dword _btn_state) {
	_btn_state;
	for (uint32_t i_ = 0; i_ < g_btns.size(); i_++) {
		CButton& btn = g_btns.at(i_);
		if (::_state_to_code(_btn_state) == btn.Code()) btn.State(e_state::e_pressed); // the button is pressed; set current state;
		else if (btn.State() == e_state::e_pressed) btn.State(e_state::e_released);    // the button was pressed before, the curren state is 'released';
		else {/*the button with state 'e_none' remains in the previous/unchanged state*/}
	}
	return g_btns;
}

const
CButton& CBtn_enum::operator ()(const uint32_t _u_code) const { return this->Get(_u_code); }
CButton& CBtn_enum::operator ()(const uint32_t _u_code)       { return this->Get(_u_code); }

#pragma endregion