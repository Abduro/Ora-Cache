/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Feb-2026 at 13:50:07.486, UTC+4, Batumi, Monday;
	This is Ebo Pack shared window popup menu wrapper interface implementation file;
*/
#include "shared.menu.popup.h"
#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace shared::gui::menus;

#pragma region cls::CMenu{}

CMenu:: CMenu (const HMENU _h_menu, _pc_sz _p_caption) : m_h_menu(_h_menu), m_caption(_p_caption) { TBase::m_error >>__CLASS__<<__e_not_inited; }
CMenu:: CMenu (CMenu&& _victim) : CMenu() { *this = _victim(); }
CMenu::~CMenu (void) { this->Destroy(); }

err_code CMenu::Append (const HMENU _h_sub_menu, _pc_sz _p_caption) {
	_h_sub_menu;
	TBase::m_error <<__METHOD__<<__s_ok;
	if (this->Is_valid() == false) {
		TBase::m_error <<__e_not_inited = _T("The menu is not created yet"); __trace_err_ex_0(TBase::Error());
		return TBase::Error();
	}
	if (nullptr == _h_sub_menu || false == !!::IsMenu(_h_sub_menu)) {
		TBase::m_error <<__e_not_inited = _T("Invalid input argument"); __trace_err_ex_0(TBase::Error());
		return TBase::Error();
	}
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-appendmenuw ;
	if (0 == ::AppendMenu(this->Handle(), MF_POPUP, (__int3264)_h_sub_menu, _p_caption)) { // MF_STRING is useless in calling this function, the pointer to string makes the sense;
		TBase::m_error.Last(); __trace_err_ex_0(TBase::Error());
	}
	return TBase::Error();
}

const
CString& CMenu::Caption (void) const { return this->m_caption; }
CString& CMenu::Caption (void)       { return this->m_caption; }

err_code CMenu::Create  (_pc_sz _p_caption) {
	_p_caption;
	TBase::m_error <<__METHOD__<<__s_ok;
	if (this->Is_valid())
		return TBase::m_error << (err_code) TErrCodes::eObject::eExists = _T("popup menu is already created");

	this->Handle() = ::CreatePopupMenu();
	if (!this->Handle())
		 this->TBase::m_error.Last();
	else {
		this->Items() << this->Handle();
		this->Caption() = _p_caption;
		__trace_impt_2(_T("popup menu '%s' (handle = %s) is created;\n"), _p_caption, TString()._addr_of(this->Handle()));
	}
	return TBase::Error();
}

err_code CMenu::Destroy (void) {
	TBase::m_error <<__METHOD__<<__s_ok;
	if (this->Is_valid() == false)
		return TBase::Error(); // just keeps the silence, no error;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-destroymenu ;
	if (0 == ::DestroyMenu(this->Handle()))
		TBase::m_error.Last();
	else {
		__trace_impt_2(_T("popup menu (handle = %s) is destroyed;\n"), TString()._addr_of(this->Handle()));
		this->Handle() = nullptr;
	}
	return this->Error();
}

const
HMENU& CMenu::Handle (void) const { return this->m_h_menu; }
HMENU& CMenu::Handle (void)       { return this->m_h_menu; }

bool CMenu::Is_valid (void) const { return nullptr != this->Handle() && !!::IsMenu(this->Handle()); }
const
CItem_Coll& CMenu::Items (void) const { return this->m_items; }
CItem_Coll& CMenu::Items (void)       { return this->m_items; }

err_code CMenu::Load (const uint16_t _res_id) {
	_res_id;
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Is_valid())
		return this->m_error <<(err_code)TErrCodes::eObject::eExists;

	_pc_sz p_res = reinterpret_cast<t_char*>(static_cast<__int3264>(_res_id));

	// https://learn.microsoft.com/en-us/cpp/atl/reference/catlbasemodule-class ;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-loadmenua ;

	this->Handle() = ::LoadMenu(::ATL::_AtlBaseModule.GetResourceInstance(), p_res);

	if (this->Is_valid() == false)
		this->m_error.Last();

	return this->Error();
}

const
HMENU& CMenu::operator ()(void) const { return this->Handle(); }
HMENU& CMenu::operator ()(void)       { return this->Handle(); }

CMenu& CMenu::operator = (CMenu&& _victim) {
	this->Handle() = _victim.Handle(); _victim.Handle() = nullptr;
	this->Caption() = _victim.Caption();
	this->Items() = _victim.Items(); _victim.Items().Raw().clear();
	return *this;
}

CMenu& CMenu::operator <<(const HMENU _h_menu) { this->Handle() = _h_menu; return *this; }
CMenu& CMenu::operator <<(_pc_sz _p_caption) { this->Caption() = _p_caption; return *this; }
CMenu& CMenu::operator <<(const CString& _cs_caption) { this->Caption() = _cs_caption; return *this; }
CMenu& CMenu::operator <<(const CItem_Coll& _items) { this->Items() = _items; return *this; }

#pragma endregion