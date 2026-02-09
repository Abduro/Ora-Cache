/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Jan-2026 at 11:10:01.946, UTC+4, Batumi, Saturday;
	This is Ebo Pack shared window context menu wrapper interface implementation file;
*/
#include "shared.ctx.menu.h"

#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace shared::gui;
using namespace shared::gui::menus;

#pragma region cls::CCtxCfg{}
#if (0)
CCtxCfg::CCtxCfg (void) : TBase(), m_h_align(e_h_align::e_left), m_v_align(e_v_align::e_top) { TBase::m_error >>__CLASS__; }

err_code CCtxCfg::Get (void) {
	TBase::m_error <<__METHOD__<<__s_ok;
#if (0)
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getsystemmetrics ;
	this->m_h_align = !!::GetSystemMetrics(SM_MENUDROPALIGNMENT) ? e_h_align::e_right : e_h_align::e_left;
#endif
	uint32_t u_result = 0;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-systemparametersinfoa ;
	if (false == !!SystemParametersInfo(SPI_GETMENUDROPALIGNMENT, 0, &u_result, 0)) {
		TBase::m_error.Last(); __trace_err_2(_T("%s;\n"), (_pc_sz) TBase::Error().Print(TError::e_print::e_req));
	} else this->m_h_align = !!u_result ? e_h_align::e_right : e_h_align::e_left;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-calculatepopupwindowposition ;
	// it seems look like using the default values is much appropriate and in cases if necessary the track function will take care of correct position of the menu;
	return TBase::Error();
}
#endif
#pragma endregion
#pragma region cls::CCtxMenu{}

CCtxMenu:: CCtxMenu (void) : m_menu(nullptr) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CCtxMenu::~CCtxMenu (void) { this->Destroy(); }

err_code CCtxMenu::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;
	if (this->Is_valid())
		return this->m_error << (err_code) TErrCodes::eObject::eExists = _T("popup menu is already created");

	this->m_menu = ::CreatePopupMenu();
	if (!this->m_menu)
		this->m_error.Last();
	else {
		this->m_items << this->m_menu;
		__trace_impt_2(_T("popup menu (handle = %s) is created;\n"), TString()._addr_of(this->Handle(), _T("0x%08x")));
	}
	return this->Error();
}

err_code CCtxMenu::Destroy (void) {
	this->m_error <<__METHOD__<<__s_ok;
	if (this->Is_valid() == false)
		return this->Error(); // just keeps the silence, no error;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-destroymenu ;
	if (0 == ::DestroyMenu(this->m_menu))
		this->m_error.Last();
	else {
		__trace_impt_2(_T("popup menu (handle = %s) is destroyed;\n"), TString()._addr_of(this->Handle(), _T("0x%08x")));
		this->m_menu = nullptr;
	}
	return this->Error();
}

TError& CCtxMenu::Error (void) const { return this->m_error; }
HMENU CCtxMenu::Handle (void) const { return this->m_menu; }

bool CCtxMenu::Is_valid (void) const { return nullptr != this->m_menu && !!::IsMenu(this->m_menu); }
const
CItem_Coll& CCtxMenu::Items (void) const { return this->m_items; }
CItem_Coll& CCtxMenu::Items (void)       { return this->m_items; }

err_code CCtxMenu::Load (const uint16_t _res_id) {
	_res_id;
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Is_valid())
		return this->m_error <<(err_code)TErrCodes::eObject::eExists;

	_pc_sz p_res = reinterpret_cast<t_char*>(static_cast<__int3264>(_res_id));

	// https://learn.microsoft.com/en-us/cpp/atl/reference/catlbasemodule-class ;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-loadmenua ;

	this->m_menu = ::LoadMenu(::ATL::_AtlBaseModule.GetResourceInstance(), p_res);

	if (this->Is_valid() == false)
		this->m_error.Last();

	return this->Error();
}

uint32_t CCtxMenu::Track (const HWND _h_owner, const t_point _pt_screen) {
	_h_owner; _pt_screen;
	this->m_error <<__METHOD__<<__s_ok;
	uint32_t u_cmd_id = 0;

	if (this->Is_valid() == false) {
		this->m_error <<__e_not_inited; return u_cmd_id;
	}
	if (false == !!::IsWindow(_h_owner)) {
		this->m_error <<__e_hwnd; return u_cmd_id;
	}
	static const uint32_t u_flags = TPM_LEFTALIGN|TPM_TOPALIGN|TPM_NONOTIFY|TPM_RETURNCMD; 
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-trackpopupmenuex ;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getsubmenu ;
	u_cmd_id = ::TrackPopupMenuEx(::GetSubMenu((*this)(), 0), u_flags, _pt_screen.x, _pt_screen.y, _h_owner, nullptr);
	if (u_cmd_id == 0) {
		this->m_error.Last();
	}

	return u_cmd_id;
}

CCtxMenu::operator HMENU (void) const { return this->m_menu; }
HMENU CCtxMenu::operator ()(void) const { return this->m_menu; }

#pragma endregion