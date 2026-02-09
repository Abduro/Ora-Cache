/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Feb-2026 at 01:06:54.552, UTC+4, Batumi, Monday;
	This is Ebo Pack shared window popup menu content enumerator interface implementation file;
*/
#include "shared.menu.enum.h"
#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace shared::gui::menus;

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

#pragma endregion