/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Sep-2025 at 05:29:19.252, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' shared GUI window layout interface implementation file;
*/
#include "win.gui.wnd.layout.h"

using namespace shared::out;
using namespace shared::out::docking;

CPane:: CPane (void) {}

const
CSide&  CPane::Side (void) const { return this->m_side; }
CSide&  CPane::Side (void)       { return this->m_side; }
const
CSize&  CPane::Size (void) const { return this->m_size; }
CSize&  CPane::Size (void)       { return this->m_size; }

/////////////////////////////////////////////////////////////////////////////

CSide:: CSide (void) : m_side(e_sides::e_left) {}

CSide::e_sides CSide::Side (void) const { return this->m_side; }

bool CSide::Side (const e_sides _e_side) {
	_e_side;
	const bool b_changed = this->Side() != _e_side;
	if (b_changed)
		this->m_side = _e_side;
	return b_changed;
}

CSide&  CSide::operator <<(const e_sides _e_side) { this->Side(_e_side); return *this; }

/////////////////////////////////////////////////////////////////////////////

CSize:: CSize (const long _l_cx, const long _l_cy) { *this << CValue(_l_cx) >> CValue(_l_cy); }
CSize:: CSize (const CValue& _cx, const CValue& _cy) { *this << _cx >> _cy; }

const
CValue& CSize::Height (void) const { return this->m_height; }
CValue& CSize::Height (void)       { return this->m_height; }
bool    CSize::Height (const long _l_value, const CValue::e_ctrl _e_type) {
	_l_value; _e_type;
	return this->Height().Set(_l_value, _e_type);
}

const
CValue& CSize::Width (void) const { return this->m_width; }
CValue& CSize::Width (void)       { return this->m_width; }
bool    CSize::Width (const long _l_value, const CValue::e_ctrl _e_type) {
	_l_value; _e_type;
	return this->Width().Set(_l_value, _e_type);
}

CSize&  CSize::operator >>(const CValue& _v_height) { this->Height().Set(_v_height.Get(), _v_height.Ctrl()); return *this; }
CSize&  CSize::operator <<(const CValue& _v_width) { this->Width().Set(_v_width.Get(), _v_width.Ctrl()); return *this; }

/////////////////////////////////////////////////////////////////////////////

CValue:: CValue (const long _l_value, const e_ctrl _e_ctrl_type) : m_ctrl(_e_ctrl_type), m_value(_l_value) {}

CValue::e_ctrl CValue::Ctrl (void) const { return this->m_ctrl; }
bool CValue::Ctrl (const e_ctrl _e_type) {
	_e_type;
	const bool b_changed = this->Ctrl() != _e_type;
	if (b_changed)
		this->m_ctrl = _e_type;
	return b_changed;
}

bool CValue::Is_auto (void) const { return this->Ctrl() == e_ctrl::e_auto; }
bool CValue::Is_auto (const bool b_state) {
	return this->Ctrl(b_state ? e_ctrl::e_auto : e_ctrl::e_fixed);
}

bool CValue::Is_fixed (void) const { return this->Ctrl() == e_ctrl::e_fixed; }
bool CValue::Is_fixed (const bool b_state) {
	return this->Ctrl(b_state ? e_ctrl::e_fixed : e_ctrl::e_auto);
}
long CValue::Get (void) const { return this->m_value; }
bool CValue::Set (const long _l_value) {
	_l_value;
	const bool b_changed = this->Get() != _l_value;
	if (b_changed)
		this->m_value = _l_value;
	return b_changed;
}

bool    CValue::Set (const long _l_value, const e_ctrl _ctrl) {
	_l_value; _ctrl;
	bool b_changed = false;

	if (this->Set(_l_value)) b_changed = true;
	if (this->Ctrl(_ctrl)) b_changed = true;

	return b_changed;
}

CValue& CValue::operator <<(const e_ctrl _e_type) { this->Ctrl(_e_type); return *this; }
CValue& CValue::operator <<(const long _l_value) { this->Set(_l_value); return *this; }  

/////////////////////////////////////////////////////////////////////////////

CLayout:: CLayout (void) {}

const
CWindow&  CLayout::Main (void) const { return this->m_target; }
CWindow&  CLayout::Main (void)       { return this->m_target; }