#ifndef _SHARED_MENU_STATE_H_INCLUDED
#define _SHARED_MENU_STATE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-Feb-2026 at 11:00:31.277, UTC+4, Batumi, Sunday;
	This is Ebo Pack shared window popup menu item state interface declaration file;
*/
#include "shared.menu.base.h"

namespace shared { namespace gui { namespace menus {

	class CState : public CBase { // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmenustate << should be used;
	public:
		// the using 'class' specifier leads to: C2677: binary '[': no global operator found which takes type 'shared::gui::menus::CState::e_state' ;
		enum /*class*/ e_state : uint32_t { e_checked = 0x0, e_enabled, e_popup }; // this is the named indices of the state value array;
		CState (void); CState (const CState&); CState (CState&&); ~CState (void) = default;

		bool Get (const e_state) const;   // gets menu item state by given enumeration value;

		bool Is_checked (void) const;
		bool Is_enabled (void) const;
		bool Is_popup (void) const;       // the menu item is the popup submenu;

		static
		err_code Set (const HMENU, const uint32_t _u_cmd_id, CState&, CError&); // sets menu item state from menu handle by command identifier;
		err_code Set (const TItemInfo&);  // sets menu item state fields' values from given menu info structure;

		_pc_sz To_str (void) const;

	public:
		CState& operator = (const CState&); CState& operator = (CState&&);
		bool& operator [](const e_state);

	private:
		bool m_state[(uint32_t)e_state::e_popup + 1u];
	};

}}}

#endif/*_SHARED_MENU_STATE_H_INCLUDED*/