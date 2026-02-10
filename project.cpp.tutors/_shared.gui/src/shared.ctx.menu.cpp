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

CCtxMenu:: CCtxMenu (void) : TMenu() { TMenu::m_error >>__CLASS__; }
CCtxMenu::~CCtxMenu (void) { TMenu::Destroy(); }

uint32_t CCtxMenu::Track (const HWND _h_owner, const t_point _pt_screen) {
	_h_owner; _pt_screen;
	TMenu::m_error <<__METHOD__<<__s_ok;
	uint32_t u_cmd_id = 0;

	if (TMenu::Is_valid() == false) {
		TMenu::m_error <<__e_not_inited; return u_cmd_id;
	}
	if (false == !!::IsWindow(_h_owner)) {
		TMenu::m_error <<__e_hwnd; return u_cmd_id;
	}
	static const uint32_t u_flags = TPM_LEFTALIGN|TPM_TOPALIGN|TPM_NONOTIFY|TPM_RETURNCMD; 
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-trackpopupmenuex ;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getsubmenu ;
	u_cmd_id = ::TrackPopupMenuEx(::GetSubMenu(TMenu::Handle(), 0), u_flags, _pt_screen.x, _pt_screen.y, _h_owner, nullptr);
	if (u_cmd_id == 0) {
		TMenu::m_error.Last();
	}
	return u_cmd_id;
}

const
menus::CMenu& CCtxMenu::operator ()(void) const { return (TMenu&)*this; }
menus::CMenu& CCtxMenu::operator ()(void)       { return (TMenu&)*this; }

#pragma endregion