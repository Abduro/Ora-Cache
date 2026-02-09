/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-Feb-2026 at 11:13:21.538, UTC+4, Batumi, Sunday;
	This is Ebo Pack shared window popup menu item wrapper interface implementation file;
*/
#include "shared.menu.item.h"
#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace shared::gui::menus;

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

const
CState& CItem::State (void) const { return this->m_state;}
CState& CItem::State (void)       { return this->m_state;}

_pc_sz  CItem::To_str (void) const {
	static _pc_sz pc_sz_pat = _T("cmd_id = 0x%04x; caption = '%s'; state = {%s}");
	static CString cs_out; cs_out.Format(pc_sz_pat, this->CmdId(), (_pc_sz) this->Caption(), this->State().To_str());
	return (_pc_sz) cs_out;
}

CItem&  CItem::operator = (const CItem& _src) { *this << _src.CmdId() << _src.Caption() << _src.State(); return *this; }
CItem&  CItem::operator = (CItem&& _victim) { *this = (const CItem&)_victim;  return *this; }
CItem&  CItem::operator <<(const uint32_t _u_cmd_id) { this->CmdId(_u_cmd_id); return *this; }
CItem&  CItem::operator <<(_pc_sz _p_caption) { this->Caption(_p_caption); return *this; }
CItem&  CItem::operator <<(const CState& _state) { this->State() = _state;  return *this; }

#pragma endregion
#pragma region cls::CItem_Coll{}

CItem_Coll:: CItem_Coll (HMENU _h_menu) : TBase(), m_menu(_h_menu) { TBase::m_error >>__CLASS__; }
CItem_Coll:: CItem_Coll (const CItem_Coll& _src) : CItem_Coll() { *this = _src; }
CItem_Coll:: CItem_Coll (CItem_Coll&& _victim) : CItem_Coll() { *this = _victim; }
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
const
TItems&  CItem_Coll::Raw (void) const { return this->m_items; }
TItems&  CItem_Coll::Raw (void)       { return this->m_items; }

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

err_code CItem_Coll::Set  (const HMENU _h_menu, TItems& _items, CError& _err) {
	_h_menu; _items; _err;
	if (nullptr == _h_menu || false == !!::IsMenu(_h_menu))
		return _err <<__e_inv_arg = _T("#__e_inv_arg: '_h_menu' is not valid");
	if (_items.empty() == false)
		_items.clear();
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmenuitemcount ;
	const int32_t u_count = ::GetMenuItemCount(_h_menu);
	if (0 > u_count)
		return _err.Last();

	static const uint32_t u_req_len = 0x200; // 512 characters should be enough;

	for (uint32_t i_ = 0; i_ < static_cast<uint32_t>(u_count); i_++) {
		CString cs_caption;

		TItemInfo itm_info = {0}; // https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-menuiteminfow ;
		itm_info.cbSize = sizeof(TItemInfo);
		itm_info.fMask  = MIIM_FTYPE|MIIM_ID|MIIM_STATE|MIIM_SUBMENU|MIIM_STRING;
		itm_info.dwTypeData = cs_caption.GetBuffer(u_req_len);
		itm_info.cch = u_req_len;

		if (0 == ::GetMenuItemInfo(_h_menu, i_, true, &itm_info)) // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmenuiteminfow ;
			return _err.Last();

		CItem item(itm_info.wID, (_pc_sz)cs_caption); item.State().Set(itm_info);
		try {
			_items.push_back(item);
		} catch (const ::std::bad_alloc&) { _err << __e_no_memory; break; }
	}

	return _err;
}

CItem_Coll& CItem_Coll::operator <<(const HMENU _h_menu) { this->Menu(_h_menu); return *this; }
CItem_Coll& CItem_Coll::operator <<(const TItems& _items) { this->Raw() = _items; return *this; }

HMENU CItem_Coll::operator ()(void) const { return this->Menu(); }

CItem_Coll& CItem_Coll::operator += (const CItem& _item) { this->Append(_item); return *this; }
CItem_Coll& CItem_Coll::operator = (const CItem_Coll& _src) { this->Raw() = _src.Raw(); return *this; }
CItem_Coll& CItem_Coll::operator = (CItem_Coll&& _victim) { *this = (const CItem_Coll&)_victim; return *this; }

#pragma endregion