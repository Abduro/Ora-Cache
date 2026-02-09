/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-Feb-2026 at 11:03:10.677, UTC+4, Batumi, Sunday;
	This is Ebo Pack shared window popup menu item state interface implemtation file;
*/
#include "shared.menu.state.h"
#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace shared::gui::menus;

namespace shared { namespace gui { namespace menus { namespace _impl {
#if (0)
	enum class e_state : uint32_t {
		e_checked  = MF_CHECKED  , // check mark is placed next to the item; (for drop-down menus, submenus, and shortcut menus only);
		e_break    = MF_MENUBREAK, // menu item is placed in a new column (for drop-down menus, submenus, and shortcut menus) without separating columns;
		e_custom   = MF_OWNERDRAW, // menu item is owner-drawn;
		e_disabled = MF_DISABLED , // menu item is disabled;
		e_grayed   = MF_GRAYED   , // menu item is disabled and grayed;
		e_hilite   = MF_HILITE   , // menu item is highlighted;
		e_popup    = MF_POPUP    , // menu item is a submenu;
		e_separator= MF_SEPARATOR, // it is a horizontal dividing line (for drop-down menus, submenus, and shortcut menus only);
		e_undef = 0x0,
	};
#endif
}}}}
using namespace _impl;

#pragma region cls::CState{}

CState::CState (void) : m_state{true, false} { CBase::m_error >>__CLASS__;}
CState::CState (const CState& _src) : CState() { *this = _src; }
CState::CState (CState&& _victim) : CState() { *this = _victim; }

bool CState::Get (const e_state _state) const {
	_state;
	return e_state::e_enabled == _state ? this->Is_enabled() : this->Is_checked();
}
err_code CState::Set (const TItemInfo& _info) {
	_info;
	err_code n_result = __s_ok;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-menuiteminfow ;
	this->m_state[e_state::e_checked] =  (_info.fState & MFS_CHECKED);
	this->m_state[e_state::e_enabled] = !(_info.fState & MFS_DISABLED | MF_GRAYED);
	this->m_state[e_state::e_popup] = (_info.fState & MF_POPUP);

	return n_result;
}
err_code CState::Set (const HMENU _h_menu, const uint32_t _u_cmd_id, CState& _out, CError& _err) {
	_h_menu; _u_cmd_id; _out; _err;
	if (nullptr == _h_menu || false == !!::IsMenu(_h_menu))
		return _err <<__e_inv_arg;
	if (0 == _u_cmd_id)
		return _err <<__e_inv_arg;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmenustate ;
	if (0 > ::GetMenuState(_h_menu, _u_cmd_id, MF_BYCOMMAND))
		return _err.Last();

	return _err;
}

bool CState::Is_checked (void) const { return this->m_state[e_state::e_checked]; }
bool CState::Is_enabled (void) const { return this->m_state[e_state::e_enabled]; }
bool CState::Is_popup (void) const {  return this->m_state[e_state::e_popup];  }

_pc_sz CState::To_str (void) const {
	static _pc_sz pc_sz_pat = _T("checked: %s; enabled: %s; sub-menu: %s");
	static CString cs_out;  cs_out.Format(pc_sz_pat, TString().Bool(this->Is_checked()), TString().Bool(this->Is_enabled()), TString().Bool(this->Is_popup()));
	return (_pc_sz) cs_out;
}

CState& CState::operator = (const CState& _src) {
	(*this)[e_state::e_checked] = _src.Is_checked();
	(*this)[e_state::e_enabled] = _src.Is_enabled();
	(*this)[e_state::e_popup] = _src.Is_popup(); return *this;
}

CState& CState::operator = (CState&& _victim) { *this = (const CState&)_victim;  return *this; }

bool& CState::operator [] (const e_state _state) { return this->m_state[_state]; }

#pragma endregion