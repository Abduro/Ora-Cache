#ifndef _SHARED_MENU_ENUM_H_INCLUDED
#define _SHARED_MENU_ENUM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Feb-2026 at 01:04:36.009, UTC+4, Batumi, Monday;
	This is Ebo Pack shared window popup menu content enumerator interface declaration file;
*/
#include "shared.menu.popup.h"

namespace shared { namespace gui { namespace menus {
	
	typedef ::std::map<HMENU, menus::TItems> TMenuMap;
	typedef ::std::vector<HMENU> TSubmenus;

	class CMenu_Enum { // gets complete info of menu comntent: items and sub-menu(s) from given menu handle;
	public:
		CMenu_Enum (void); CMenu_Enum (const CMenu_Enum&) = delete; CMenu_Enum (CMenu_Enum&&) = delete; ~CMenu_Enum (void) = default;

		static err_code Do (const HMENU _h_top, TMenuMap&, CError&); // enumerates all submenus from the given menu handle;
		static err_code Get (const HMENU _h_top, TSubmenus&, CError&); // gets all submenus from given menu handle;

		static const HMENU Find (const HMENU _h_top, const uint32_t _cmd_id, CError&); // finds menu handle that contains the requested menu item, returns nullptr if not found;
		static const CItem& Find (const CMenu&, const uint32_t _cmd_id, CError&); // finds menu item by given identifier, if not found the refernce to fake menu item is returned;

	private:
		CMenu_Enum& operator = (const CMenu_Enum&) = delete; CMenu_Enum& operator = (CMenu_Enum&&) = delete;
	};

}}}

#endif/*_SHARED_MENU_ENUM_H_INCLUDED*/