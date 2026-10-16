#ifndef _COMMON_MENU_H_INCLUDED
#define _COMMON_MENU_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Oct-2026 at 19:30:32.926, UTC+4, Batumi, Thursday;
	This is virtual camera test cases' shortcut menu wrapper interface declaration file;
*/
#include <common.defs.h>

namespace test { namespace gui { namespace menus { using namespace ::test::draw::defs;

	class CShortcut {
	public:
		 CShortcut (void); CShortcut (const CShortcut&) = delete; CShortcut (CShortcut&&) = delete;
		~CShortcut (void);

		err_code Destroy (void);          // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-destroymenu ;
		TError&  Error (void) const;

		bool Is_valid (void) const;       // checks the validity of the menu handle;
		err_code Load (uint16_t _res_id); // loads a menu from resource of the executable by given resource identifier;

		uint32_t Track (const HWND _h_owner); // tracks popup menu at current position of the cursor;
		uint32_t Track (const HWND _h_owner, const point_t& _pt_screen); // tracks popup menu; returns selected menu item command ID or 0;

		CShortcut& operator << (uint16_t _res_id);

	private:
		CShortcut& operator = (const CShortcut&) = delete; CShortcut& operator = (CShortcut&&) = delete;
		CError   m_error;
		HMENU    m_h_menu;
		uint16_t m_res_id;  // this is resource identifier by which this menu is loaded;
	};

}}}

#endif/*_COMMON_MENU_H_INCLUDED*/