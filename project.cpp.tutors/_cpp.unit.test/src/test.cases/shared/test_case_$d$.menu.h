#ifndef _TEST_CASE_$D$_MENU_H_INCLUDED
#define _TEST_CASE_$D$_MENU_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Feb-2026 at 09:38:55.937, UTC+4, Batumi, Saturday;
	This is Ebo Pack window shortcut menu wrapper interface declaration file for using in test cases adapters;
*/
#include "ebo_test_$d$.defs.h"
#include "shared.ctx.menu.h"

namespace ebo { namespace boo { namespace test { namespace win_api { namespace menu {

	using namespace shared::gui;
	using namespace shared::gui::menus;

	using CMenu = shared::gui::menus::CMenu;
	using CMenu_Enum = shared::gui::menus::CMenu_Enum;
	using CState = shared::gui::menus::CState;
	/* these use cases do not require OpenGL API; it looks like such a kind of use cases must be placed in separate test case project;
	*/
	class CTMenu {
	public:
		CTMenu (void); CTMenu (const CTMenu&) = delete; CTMenu (CTMenu&&) = delete; ~CTMenu (void) = default;
		TError& Error (void) const;

		err_code Create (_pc_sz _p_caption = nullptr);
		err_code Delete (void); // this method is for test of deleting menu handle, but actually 'CCtxMenu' class makes it in its destructor;
		err_code Check  (const uint32_t _u_cmd_id, const bool);
		err_code Enable (const uint32_t _u_cmd_id, const bool);

		uint32_t Get_last_cmd (void) const;

		const
		CMenu& operator ()(void) const;
		CMenu& operator ()(void) ;

	public:
		CTMenu& operator = (const CTMenu&) = delete; CTMenu& operator = (CTMenu&&) = delete;
		CError m_error;
		CMenu  m_menu;   // shortcut/context popup menu;
	};

	class CTMenus {
	public:
		CTMenus (void); CTMenus (const CTMenus&) = delete; CTMenus (CTMenus&&) = delete; ~CTMenus (void) = default;
		TError& Error (void) const;

		err_code Find (const uint32_t _cmd_id, HMENU& _h_result); // finds the menu item by given command identifier, returns menu handle if found, otherwise, nullptr;
		err_code Find (const HMENU _h_where, const uint32_t _cmd_id, HMENU& _h_result);

		err_code Get_info (void); // creates a popup menu and gets information of all menu items from the menu handle;

	public:
		CTMenus& operator = (const CTMenus&) = delete; CTMenus& operator = (CTMenus&&) = delete;
		CError m_error;
	};

}}}}}

#endif/*_TEST_CASE_$D$_MENU_H_INCLUDED*/