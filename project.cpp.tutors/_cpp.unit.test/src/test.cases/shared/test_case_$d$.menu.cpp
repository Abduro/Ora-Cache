/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Feb-2026 at 09:44:29.979, UTC+4, Batumi, Saturday;
	This is Ebo Pack window shortcut menu wrapper interface declaration file for using in test cases adapters;
*/
#include "test_case_$d$.menu.h"

using namespace ebo::boo::test::win_api::menu;

namespace ebo { namespace boo { namespace test { namespace _impl {
uint32_t mnu_itm_id = 0;
uint32_t mnu_popup_no = 0;

_pc_sz _get_popup_cap (void) {
	static CString cs_out; cs_out.Format(_T("Popup menu #%u"), mnu_popup_no++);
	return (_pc_sz)cs_out;
}

}}}} using namespace ebo::boo::test::_impl;

#pragma region cls::CTMenu{}

CTMenu::CTMenu (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

err_code CTMenu::Create (_pc_sz _p_caption) {
	_p_caption;
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	if (__failed(this->m_menu.Create(_get_popup_cap()))) {
		this->m_error = this->m_menu.Error(); _out() += this->Error(); return this->Error();
	}

	CItem_Coll& items = this->m_menu.Items();
	uint32_t itm_count = 3;

	for (uint32_t i_ = 0; i_ < itm_count; i_ ++) {
		CItem item (++mnu_itm_id, TString().Format(_T("Item #%u"), mnu_itm_id));
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

err_code CTMenu::Check  (const uint32_t _u_cmd_id, const bool _b_on) {
	_u_cmd_id; _b_on;
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(_T("input args: _u_cmd_id = 0x%04x; _b_on = %s"), _u_cmd_id, TString().Bool(_b_on));

	if (__failed(this->Create())) { return this->Error(); }
	if (__failed(CState::Check((*this)()(), _u_cmd_id, _b_on, this->m_error))) { _out() += this->Error(); }
	else {
		CState the_result;
		if (__failed(CState::Get((*this)()(), _u_cmd_id, the_result, this->m_error))) { _out() += this->Error(); }
		else
			_out() += TString().Format(_T("[impt] result: %s;"), the_result.To_str());
	}

	return this->Error();
}
err_code CTMenu::Enable (const uint32_t _u_cmd_id, const bool _b_on) {
	_u_cmd_id; _b_on;
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(_T("input args: _u_cmd_id = 0x%04x; _b_on = %s"), _u_cmd_id, TString().Bool(_b_on));

	if (__failed(this->Create())) { return this->Error(); }
	if (__failed(CState::Enable((*this)()(), _u_cmd_id, _b_on, this->m_error))) { _out() += this->Error(); }
	else {
		CState the_result;
		if (__failed(CState::Get((*this)()(), _u_cmd_id, the_result, this->m_error))) { _out() += this->Error(); }
		else
			_out() += TString().Format(_T("[impt] result: %s;"), the_result.To_str());
	}
	return this->Error();
}

TError& CTMenu::Error (void) const { return this->m_error; }
uint32_t CTMenu::Get_last_cmd (void) const {
	return mnu_itm_id;
}

const
CMenu& CTMenu::operator ()(void) const { return this->m_menu; }
CMenu& CTMenu::operator ()(void)       { return this->m_menu; }

#pragma endregion
#pragma region cls::CTMenus{}

CTMenus::CTMenus (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

err_code CTMenus::Find (const uint32_t _cmd_id, HMENU& _h_result) {
	_cmd_id; _h_result;
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);

	CTMenu menu;
	if (__failed(menu.Create(_T("Popup menu")))) { return this->m_error = menu.Error(); /*_out() += this->Error(); return this->Error();*/ }
	else return this->Find(menu()(), _cmd_id, _h_result);
}

err_code CTMenus::Find (const HMENU _h_where, const uint32_t _cmd_id, HMENU& _h_result) {
	_h_where; _cmd_id; _h_result;
	this->m_error <<__METHOD__<<__s_ok;
	_out() += TString().Format(_T("[warn] cls::[%s::%s].%s():"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	_out() += TString().Format(_T("target menu handle=%s; cmd_id = 0x%04x;"), TString()._addr_of(_h_where), _cmd_id);

	_h_result = CMenu_Enum::Find(_h_where, _cmd_id, this->m_error);
	if (this->Error())
		_out() += this->Error();
	else if (nullptr == _h_result) { _out() += TString().Format(_T("[warn] The menu item (cmd_id = 0x%04x) is not found;"), _cmd_id); }
	else { _out() += TString().Format(_T("[impt] The menu item (cmd_id = 0x%04x) is found in menu handle = %s"), _cmd_id, TString()._addr_of(_h_result)); }

	return this->Error();
}

TError&  CTMenus::Error (void) const { return this->m_error; }

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