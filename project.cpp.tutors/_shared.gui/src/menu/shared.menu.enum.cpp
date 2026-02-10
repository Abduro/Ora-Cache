/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Feb-2026 at 01:06:54.552, UTC+4, Batumi, Monday;
	This is Ebo Pack shared window popup menu content enumerator interface implementation file;
*/
#include "shared.menu.enum.h"
#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace shared::gui::menus;
#pragma warning (disable: 4006) // it does not affect the linker due to #pragma works against compiler complaining; :-D
namespace shared { namespace gui { namespace menus { namespace _impl { CItem virt_item; }}}}
using namespace _impl;
#pragma warning (default: 4006)
#pragma region cls::CMenu_Enum{}

CMenu_Enum::CMenu_Enum (void) {}

err_code CMenu_Enum::Do (const HMENU _h_menu, TMenuMap& _map, CError& _err) {
	_h_menu; _map; _err;
	if (nullptr == _h_menu || false == !!::IsMenu(_h_menu))
		return _err <<__e_inv_arg = _T("#__e_inv_arg: '_h_menu' is not valid");

	if (_map.empty() == false)
		_map.clear();
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmenuitemcount ;
	const int32_t u_count = ::GetMenuItemCount(_h_menu);
	if (0 > u_count)
		return _err.Last();

	static const uint32_t u_req_len = 0x200; // 512 characters should be enough;

	for (uint32_t i_ = 0; i_ < static_cast<uint32_t>(u_count); i_++) {

		CString cs_caption;

		TItemInfo itm_info = {0}; // https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-menuiteminfow ;
		itm_info.cbSize = sizeof(TItemInfo);
		itm_info.fMask  = MIIM_SUBMENU|MIIM_STRING; // items which are submenus are interested only;
		itm_info.dwTypeData = cs_caption.GetBuffer(u_req_len);
		itm_info.cch = u_req_len;

		if (0 == ::GetMenuItemInfo(_h_menu, i_, true, &itm_info)) // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmenuiteminfow ;
			return _err.Last();
		if (nullptr == itm_info.hSubMenu)
			continue;

		menus::TItems items;
		if (__failed(CItem_Coll::Set(itm_info.hSubMenu, items, _err)))
			break;
		try {
		_map.insert(::std::make_pair(itm_info.hSubMenu, items));
		} catch (const ::std::bad_alloc&) { _err << __e_no_memory; break; }
	}
	return _err;
}

err_code CMenu_Enum::Get (const HMENU _h_top, TSubmenus& _sub_menus, CError& _err) {
	_h_top; _sub_menus; _err;
	if (nullptr == _h_top || false == !!::IsMenu(_h_top))
		return _err <<__e_inv_arg = _T("#__e_inv_arg: '_h_top' is not valid");
	if (_sub_menus.empty() == false)
		_sub_menus.clear();

	return _err;
}

const HMENU CMenu_Enum::Find (const HMENU _h_menu, const uint32_t _cmd_id, CError& _err) {
	_h_menu; _cmd_id; _err;
	HMENU h_found = nullptr;
	if (nullptr == _h_menu || false == !!::IsMenu(_h_menu)) {
		_err <<__e_inv_arg = _T("#__e_inv_arg: '_h_menu' is not valid");
		return h_found;
	}
	if (0 == _cmd_id) {
		_err <<__e_inv_arg = _T("#__e_inv_arg: command identifier is not valid");
		return h_found;
	}

	const uint32_t u_count = ::GetMenuItemCount(_h_menu);
	for (uint32_t i_ = 0; i_ < u_count; i_++) {
		const uint32_t u_itm_id = ::GetMenuItemID(_h_menu, i_); // tries to retrieve the menu item identifier;
		if (u_itm_id == _cmd_id) // the item is found;
			return _h_menu;
		if (0 > static_cast<int32_t>(u_itm_id)) { // a submenu item is found;
			const HMENU h_submenu = ::GetSubMenu(_h_menu, i_);
			if (nullptr == h_submenu) { break; }
			else return CMenu_Enum::Find(h_submenu, _cmd_id, _err);
		}
	}

	return h_found;
}

const CItem& CMenu_Enum::Find (const CMenu& _menu, const uint32_t _cmd_id, CError& _err) {
	_menu; _cmd_id; _err;
	if (_menu.Is_valid() == false) {
		_err <<__e_inv_arg = _T("#__e_inv_arg: menu handle is not valid");
		return virt_item;
	}
	if (0 == _cmd_id) {
		_err <<__e_inv_arg = _T("#__e_inv_arg: command identifier is not valid");
		return virt_item;
	}
	// (1) checks the input menu object first;
	const CItem& itm_found = _menu.Items().Find(_cmd_id);
	if (itm_found.Is_valid())
		return itm_found;

	return virt_item;
}

#pragma endregion