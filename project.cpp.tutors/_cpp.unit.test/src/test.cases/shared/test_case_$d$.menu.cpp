/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Feb-2026 at 09:44:29.979, UTC+4, Batumi, Saturday;
	This is Ebo Pack window shortcut menu wrapper interface declaration file for using in test cases adapters;
*/
#include "test_case_$d$.menu.h"

using namespace ebo::boo::test::win_api::menu;

#pragma region cls::CTMenu{}

CTMenu::CTMenu (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

err_code CTMenu::Create (_pc_sz _p_caption) {
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed(this->m_menu.Create(_p_caption))) {
		this->m_error = this->m_menu.Error(); _out() += this->Error().Print(TError::e_print::e_req); return this->Error();
	}

	CItem_Coll& items = this->m_menu.Items();
	uint32_t itm_count = 3;

	for (uint32_t i_ = 0; i_ < itm_count; i_ ++) {
		CItem item (i_ + 1, TString().Format(_T("Item #%u"), i_ + 1));
		if (__failed(items.Append(item))) { this->m_error = items.Error(); _out() += this->Error().Print(TError::e_req); break;}
		else { _out() += TString().Format(_T("menu item {%s} is appended;"), item.To_str()); }
	}
	return this->Error();
}

err_code CTMenu::Delete (void) {
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	return this->Error();
}

TError& CTMenu::Error (void) const { return this->m_error; }

const
CMenu& CTMenu::operator ()(void) const { return this->m_menu; }
CMenu& CTMenu::operator ()(void)       { return this->m_menu; }

#pragma endregion
#pragma region cls::CTMenus{}

CTMenus::CTMenus (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& CTMenus::Error (void) const { return this->m_error; }

err_code CTMenus::Get_info (void) {
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += _T("Creating the popup menu...");

	CTMenu menu, sub_menu;

	if (__failed(menu.Create(_T("Popup menu #0")))) return this->m_error = menu.Error();
	if (__failed(sub_menu.Create(_T("Sub-menu #0-0")))) return this->m_error = menu.Error();
	if (__failed(menu().Append(sub_menu()(), _T("Sub-menu #0-0")))) return this->m_error = menu.Error();

	_out() += TString().Format(_T("[impt] Submenu '%s' is appended to '%s';"), (_pc_sz) sub_menu().Caption(), (_pc_sz) menu().Caption());
	_out() += _T("Retrieving the popup menu content...");

	TMenuMap map; 
	CMenu_Enum::Do(menu().Handle(), map, this->m_error);

	if (this->Error()) { _out() += this->Error().Print(TError::e_req); return this->Error(); }

	CString cs_out;
	cs_out.Format(_T("[impt] the content of menu (handle=%s):"), TString()._addr_of(menu().Handle()));
	_out() += cs_out;

	const menus::TItems& items = map.begin()->second;
	if (items.empty()) {
		_out() += _T("#no_items"); return this->Error();
	}
	_out() += TString().Format(_T("Submenu (handle=%s):"), TString()._addr_of(map.begin()->first));
	for (uint32_t i_ = 0; i_ < items.size(); i_++) { const CItem& item = items.at(i_); _out() += item.To_str(); }

	return this->Error();
}

#pragma endregion