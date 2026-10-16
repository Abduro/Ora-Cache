/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Oct-2026 at 19:37:29.424, UTC+4, Batumi, Thursday;
	This is virtual camera test cases' shortcut menu wrapper interface implementation file;
*/
#include "common.menu.h"

using namespace ::test::gui::menus;

#pragma region cls::CShortcut{}

CShortcut:: CShortcut (void) : m_h_menu(0), m_res_id(0) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("Shortcut menu is not created yet;"); }
CShortcut::~CShortcut (void) { this->Destroy(); }

err_code CShortcut::Destroy (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Is_valid() == false)
		return this->Error(); // just keeps the silence, no error;

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-destroymenu ;
	if (0 == ::DestroyMenu(this->m_h_menu))
		this->m_error.Last();
	else {
		this->m_h_menu = nullptr;
		this->m_res_id = 0; // clear cached resource identifier;
	}
	return this->Error();
}

TError&  CShortcut::Error (void) const { return this->m_error; }

bool CShortcut::Is_valid (void) const { return nullptr != this->m_h_menu && !!::IsMenu(this->m_h_menu); }

err_code CShortcut::Load (const uint16_t _res_id) {
	_res_id;
	this->m_error <<__METHOD__<<__s_ok;

	if (false) {}
	else if (this->Is_valid() && _res_id == this->m_res_id)
		return this->Error(); // there is no need to load the same menu twice;
	else if (this->Is_valid())
	     if (__failed(this->Destroy())) return this->Error();

	_pc_sz p_res = reinterpret_cast<t_char*>(static_cast<__int3264>(_res_id));

	// https://learn.microsoft.com/en-us/cpp/atl/reference/catlbasemodule-class ;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-loadmenua ;

	this->m_h_menu = ::LoadMenu(::ATL::_AtlBaseModule.GetResourceInstance(), p_res);

	if (this->Is_valid() == false)
		this->m_error.Last();
	else
		this->m_res_id = _res_id; // caches resource identifier;

	return this->Error();
}

uint32_t CShortcut::Track (const HWND _h_owner) {
	this->m_error <<__METHOD__<<__s_ok;
	point_t curs_pos = {0};
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getcursorpos ;
	if (0 == ::GetCursorPos(&curs_pos))
		return this->m_error.Last();
	else
		return this->Track(_h_owner, curs_pos);
}

uint32_t CShortcut::Track (const HWND _h_owner, const point_t& _pt_screen) {
	_h_owner; _pt_screen;
	this->m_error <<__METHOD__<<__s_ok;
	uint32_t u_cmd_id = 0;

	if (this->Is_valid() == false) {
		this->m_error <<__e_not_inited; return u_cmd_id;
	}
	if (false == !!::IsWindow(_h_owner)) {
		this->m_error <<__e_hwnd; return u_cmd_id;
	}
	static const uint32_t u_flags = TPM_HORIZONTAL|TPM_VERTICAL|TPM_NONOTIFY|TPM_RETURNCMD; 
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-trackpopupmenuex ;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getsubmenu ;
	u_cmd_id = ::TrackPopupMenuEx(::GetSubMenu(this->m_h_menu, 0), u_flags, _pt_screen.x, _pt_screen.y, _h_owner, nullptr);
	if (u_cmd_id == 0) {
		this->m_error.Last();
	} else {}
	return u_cmd_id;
}

CShortcut& CShortcut::operator << (uint16_t _res_id) {
	_res_id;
	this->Load (_res_id); return *this;
}

#pragma endregion