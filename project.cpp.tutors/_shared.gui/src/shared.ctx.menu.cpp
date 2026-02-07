/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Jan-2026 at 11:10:01.946, UTC+4, Batumi, Saturday;
	This is Ebo Pack shared window context menu wrapper interface implementation file;
*/
#include "shared.ctx.menu.h"

#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace shared::gui;
using namespace shared::gui::menus;

#pragma region cls::CBase{}

CBase:: CBase (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CBase:: CBase (const CBase& _src) : CBase() { *this = _src; }
CBase:: CBase (CBase&& _victim) : CBase() { *this = _victim; }
CBase::~CBase (void) { /*does nothing*/}

TError& CBase::Error (void) const { return this->m_error; }

CBase&  CBase::operator = (const CBase& _src) { this->m_error = _src.Error(); return *this; }
CBase&  CBase::operator = (CBase&& _victim) { *this = (const CBase&)_victim; return *this; }

#pragma endregion
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
#pragma region cls::CItem{}

#define u_mask_value MIIM_FTYPE|MIIM_ID|MIIM_STRING

CItem:: CItem (const uint32_t _u_cmd_id, _pc_sz _p_caption) : TBase(), m_cmd_id(_u_cmd_id), m_cs_cap(_p_caption), m_mask(u_mask_value) { TBase::m_error >>__CLASS__; }
CItem:: CItem (const CItem& _src) : CItem() { *this = _src; }
CItem:: CItem (CItem&& _victim) : CItem() { *this = _victim; }
CItem::~CItem (void) { /*does nothing yet*/}
const
CString& CItem::Caption (void) const { return this->m_cs_cap; }
CString& CItem::Caption (void)       { return this->m_cs_cap; }
bool     CItem::Caption (const _pc_sz _p_cap) {
	_p_cap;
	const bool b_changed = !!this->m_cs_cap.Compare(_p_cap); if (b_changed) { this->m_cs_cap = _p_cap; this->m_cs_cap.Trim(); } return b_changed;
}

uint32_t CItem::CmdId (void) const { return this->m_cmd_id; }
bool     CItem::CmdId (const uint32_t _u_cmd_id) {
	_u_cmd_id;
	const bool b_changed = this->CmdId() != _u_cmd_id; if (b_changed) this->m_cmd_id = _u_cmd_id;  return b_changed;
}

bool  CItem::Is_valid (void) const { return !!this->CmdId() && !this->m_cs_cap.IsEmpty(); }

uint32_t CItem::Mask  (void) const { return MIIM_FTYPE|MIIM_STATE|MIIM_ID|MIIM_STRING; }

err_code CItem::Set (const TItemInfo& _info) {
	_info;
	err_code n_result = __s_ok;

	return n_result;
}
const
CItem::CState& CItem::State (void) const { return this->m_state;}
CItem::CState& CItem::State (void)       { return this->m_state;}

_pc_sz  CItem::To_str (void) const {
	static _pc_sz pc_sz_pat = _T("cmd_id = 0x%04x; caption = '%s'");
	static CString cs_out; cs_out.Format(pc_sz_pat, this->CmdId(), (_pc_sz) this->Caption());
	return (_pc_sz) cs_out;
}

CItem&  CItem::operator = (const CItem& _src) { *this << _src.CmdId() << _src.Caption() << _src.State(); return *this; }
CItem&  CItem::operator = (CItem&& _victim) { *this = (const CItem&)_victim;  return *this; }
CItem&  CItem::operator <<(const uint32_t _u_cmd_id) { this->CmdId(_u_cmd_id); return *this; }
CItem&  CItem::operator <<(_pc_sz _p_caption) { this->Caption(_p_caption); return *this; }
CItem&  CItem::operator <<(const CState& _state) { this->State() = _state;  return *this; }

#pragma endregion
#pragma region cls::CItem::CState{}

using CState = CItem::CState;

CState::CState (void) : m_state{false} {}
CState::CState (const CState& _src) : CState() { *this = _src; }
CState::CState (CState&& _victim) : CState() { *this = _victim; }

bool CState::Get (const e_state _state) const {
	_state;
	return e_state::e_enabled == _state ? this->Is_enabled() : this->Is_checked();
}
err_code CState::Set (const TItemInfo& _info) {
	_info;
	err_code n_result = __s_ok;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-menuiteminfow ;
	this->m_state[e_state::e_checked] =  (_info.fState & MFS_CHECKED);
	this->m_state[e_state::e_enabled] = !(_info.fState & MFS_DISABLED);

	return n_result;
}

bool CState::Is_checked (void) const { return this->m_state[e_state::e_checked]; }
bool CState::Is_enabled (void) const { return this->m_state[e_state::e_enabled]; }

CState& CState::operator = (const CState& _src) {
	(*this)[e_state::e_checked] = _src.Is_checked();
	(*this)[e_state::e_enabled] = _src.Is_enabled(); return *this;
}

CState& CState::operator = (CState&& _victim) { *this = (const CState&)_victim;  return *this; }

bool& CState::operator [] (const e_state _state) { return this->m_state[_state]; }

#pragma endregion
#pragma region cls::CItem_Coll{}

CItem_Coll:: CItem_Coll (HMENU _h_menu) : TBase(), m_menu(_h_menu) { TBase::m_error >>__CLASS__; }
CItem_Coll::~CItem_Coll (void) {}

err_code CItem_Coll::Append (const CItem& _item) {
	_item;
	TBase::m_error <<__METHOD__<<__s_ok;

	if (false == this->Is_valid())
		return TBase::m_error <<__e_not_inited;

	CString cs_cap(_item.Caption()); MFT_STRING;

	TItemInfo itm_info = {
		sizeof(TItemInfo), _item.Mask(), MIIM_STRING, MFS_ENABLED, _item.CmdId(), 0, 0, 0, 0, cs_cap.GetBuffer(), static_cast<uint32_t>(cs_cap.GetLength())
	};
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-appendmenuw ;
	if (false == !!::AppendMenu((*this)(), MF_STRING, _item.CmdId(), (_pc_sz) _item.Caption()))
		TBase::m_error.Last();

	return TBase::Error();
}

err_code CItem_Coll::Insert (const uint32_t _u_before, const CItem& _item) {
	_u_before; _item;
	TBase::m_error <<__METHOD__<<__s_ok;

	if (false == this->Is_valid())
		return TBase::m_error <<__e_not_inited;

	CString cs_cap(_item.Caption());

	TItemInfo itm_info = {
		sizeof(TItemInfo), _item.Mask(), MIIM_STRING, MFS_ENABLED, _item.CmdId(), 0, 0, 0, 0, cs_cap.GetBuffer(), static_cast<uint32_t>(cs_cap.GetLength())
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-insertmenuitemw ;
	if (false == !!::InsertMenuItem((*this)(), _u_before, true, &itm_info))
		TBase::m_error.Last();

	return TBase::Error();
}

bool CItem_Coll::Is_valid (void) const { return !!::IsMenu(this->Menu()); }

HMENU    CItem_Coll::Menu (void) const { return this->m_menu; }
err_code CItem_Coll::Menu (const HMENU _h_menu) {
	_h_menu;
	TBase::m_error <<__METHOD__<<__s_ok;

	if (false == !!::IsMenu(_h_menu))
		TBase::m_error << __e_inv_arg = _T("the menu handle is invalid");
	else
		this->m_menu = _h_menu;

	return TBase::Error();
}

CItem_Coll& CItem_Coll::operator <<(const HMENU _h_menu) { this->Menu(_h_menu); return *this; }

HMENU CItem_Coll::operator ()(void) const { return this->Menu(); }

CItem_Coll& CItem_Coll::operator += (const CItem& _item) { this->Append(_item); return *this; }

#pragma endregion

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

	static const uint32_t u_req_len = 0x200;

	menus::CItem_Coll items;

	for (uint32_t i_ = 0; i_ < static_cast<uint32_t>(u_count); i_++) {

		CString cs_caption;

		TItemInfo itm_info = {0}; // https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-menuiteminfow ;
		itm_info.cbSize = sizeof(TItemInfo);
		itm_info.fMask  = MIIM_FTYPE|MIIM_ID|MIIM_STATE|MIIM_SUBMENU|MIIM_STRING;
		itm_info.dwTypeData = cs_caption.GetBuffer(u_req_len); // 512 characters should be enough;
		itm_info.cch = u_req_len;

		if (0 == ::GetMenuItemInfo(_h_menu, i_, true, &itm_info)) // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmenuiteminfow ;
			return _err.Last();

		CItem item(itm_info.wID, (_pc_sz)cs_caption);

		try {
		} catch (const ::std::bad_alloc&) { return _err << __e_no_memory; }
	}

	return _err;
}

#pragma endregion