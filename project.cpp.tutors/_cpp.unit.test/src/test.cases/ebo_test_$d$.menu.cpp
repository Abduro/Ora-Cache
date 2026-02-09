/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Feb-2026 at 10:03:39.078, UTC+4, Batumi, Saturday;
	This is Ebo Pack window shortcut menu wrapper unit test adapter interface implementation file.
*/
#include "ebo_test_$d$.menu.h"

using namespace ebo::boo::test::win_api::menu;

#pragma region cls::c_ctx_menu{}

c_ctx_menu::c_ctx_menu (void) {}

void c_ctx_menu::Create (void) { CTMenu menu; menu.Create(_T("Popup menu")); _out()(); }
void c_ctx_menu::Get_info (void) {
	CTMenus menu_enum;
	if (__failed(menu_enum.Get_info())) { _out()(); return; }

	_out()();
}

#pragma endregion