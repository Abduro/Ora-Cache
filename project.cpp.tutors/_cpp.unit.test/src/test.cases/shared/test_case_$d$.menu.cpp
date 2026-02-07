/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Feb-2026 at 09:44:29.979, UTC+4, Batumi, Saturday;
	This is Ebo Pack window shortcut menu wrapper interface declaration file for using in test cases adapters;
*/
#include "test_case_$d$.menu.h"

using namespace ebo::boo::test::win_api::menu;

#pragma region cls::CTMenu{}

CTMenu::CTMenu (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

err_code CTMenu::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed(this->m_menu.Create())) {
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
CCtxMenu& CTMenu::operator ()(void) const { return this->m_menu; }
CCtxMenu& CTMenu::operator ()(void)       { return this->m_menu; }

#pragma endregion
#pragma region cls::CTMenus{}

CTMenus::CTMenus (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& CTMenus::Error (void) const { return this->m_error; }

err_code CTMenus::Do (void) {
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += _T("Creating the popup menu...");

	CTMenu menu;

	if (__failed(menu.Create())) return this->m_error = menu.Error();

	TMenuMap map; 
	CMenu_Enum::Do(menu().Handle(), map, this->m_error);


	return this->Error();
}

#pragma endregion