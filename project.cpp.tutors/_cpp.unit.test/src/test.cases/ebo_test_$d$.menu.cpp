/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Feb-2026 at 10:03:39.078, UTC+4, Batumi, Saturday;
	This is Ebo Pack window shortcut menu wrapper unit test adapter interface implementation file.
*/
#include "ebo_test_$d$.menu.h"

using namespace ebo::boo::test::win_api::menu;

#pragma region cls::c_ctx_menu{}

c_ctx_menu::c_ctx_menu (void) {}

void c_ctx_menu::Checked (void) {

	CTMenu menu;
	_out() += _T("Failure test case:"); CTMenu().Check(0xff, true); // wrong command identifier;
	_out() += _T("Success test case:"); CTMenu().Check(menu.Get_last_cmd() + 1, true); // the appending new menu items is not started yet, the first id value is the last + 1;

	_out()();	
}

void c_ctx_menu::Create (void) { CTMenu menu; menu.Create(); _out()(); }
void c_ctx_menu::Find (void) {
	CTMenu  menu;
	CTMenus menu_enum;
	HMENU h_menu = nullptr;
	const uint32_t u_cmd_id = 1;

	if (__failed(menu.Create())) { _out()(); return; }
	if (__failed(menu_enum.Find(menu()(), u_cmd_id, h_menu))) { _out()(); return; }
}

void c_ctx_menu::Enabled (void) {

	CTMenu menu;
	_out() += _T("Failure test case:"); CTMenu().Enable(0xff, true); // wrong command identifier;
	_out() += _T("Success test case:"); CTMenu().Enable(menu.Get_last_cmd() + 1, true);

	_out()();	
}

void c_ctx_menu::Get_info (void) {
	CTMenus menu_enum;
	if (__failed(menu_enum.Get_info())) { _out()(); return; }

	_out()();
}

#pragma endregion