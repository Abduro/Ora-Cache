#ifndef _EBO_TEST_$D$_MENU_H_INCLUDED
#define _EBO_TEST_$D$_MENU_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Feb-2026 at 10:03:39.078, UTC+4, Batumi, Saturday;
	This is Ebo Pack window shortcut menu wrapper unit test adapter interface declaration file.
*/
#include "test_case_$d$.menu.h"

namespace ebo { namespace boo { namespace test { namespace win_api { namespace menu {
	using namespace ebo::boo::test;

	__class (c_ctx_menu) {
	public:
		c_ctx_menu (void); ~c_ctx_menu (void) = default;

		__method (Create);    // creates and destroys the popup menu;
		__method (Get_info);  // creates popup menu and gets information of the menu content from its handle;

	};

}}}}}

#endif/*_EBO_TEST_$D$_MENU_H_INCLUDED*/