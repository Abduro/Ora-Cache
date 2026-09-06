/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Sep-2026 at 17:40:58.238, UTC+4, Batumi, Thursday;
	The is SFX tabbed control registry storage wrapper interface implementation file;
*/
#include "sfx.tabs.reg.h"
#include "sfx.tabs.lay.h"

using namespace ::ex_ui::controls::tabbed;
using namespace ::ex_ui::controls::tabbed::storage;
using namespace ::ex_ui::controls::sfx::tabbed;

namespace ex_ui { namespace controls { namespace tabbed { namespace _impl {

	class CRouter_paths {
	public:
		 CRouter_paths (void) = default; CRouter_paths (const CRouter_paths&) = delete; CRouter_paths (CRouter_paths&&) = delete;
		~CRouter_paths (void) = default;

		_pc_sz  Tab_ctrl (const uint32_t _ctrl_id) {
			// https://en.cppreference.com/cpp/utility/to_chars ; for using standard library;
			return (_pc_sz)(m_cache = TString().Format(_T("0x04x"), _ctrl_id));
		}

	private:
		CRouter_paths& operator = (const CRouter_paths&) = delete; CRouter_paths& operator = (CRouter_paths&&) = delete;
		CString m_cache;
	};

}}}}

static _pc_sz p_err_ptr = _T("The pointer to tab control is not set");
static _pc_sz p_align_horz = _T("Align_Horz");
static _pc_sz p_align_vert = _T("Align_Vert");
static _pc_sz p_active_tab = _T("Active_Tab");

#pragma region cls::CActive{}

CPersistent::CActive::CActive (void) : m_p_ctrl(0) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError&  CPersistent::CActive::Error (void) const { return this->m_error; }

err_code CPersistent::CActive::Load (void) {
	this->m_error <<__METHOD__<<__s_ok;
	if (this->m_p_ctrl == 0)
		return this->m_error << __e_pointer = p_err_ptr;

	TRegKeyEx reg_key;
	const int16_t tab_ndx = static_cast<int16_t>(reg_key.Value().GetDword(CRoot().Path(m_p_ctrl->Id()), p_active_tab));
	this->m_error << this->m_p_ctrl->Tabs().Active(tab_ndx);
	
	return this->Error();
}

CPersistent::CActive& CPersistent::CActive::operator <<(TabCtrl* _p_ctrl) { this->m_p_ctrl = _p_ctrl; return *this; }

#pragma endregion	
#pragma region cls::CAlign{}

CPersistent::CAlign::CAlign (void) : m_p_ctrl(0) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError&  CPersistent::CAlign::Error (void) const { return this->m_error; }

err_code CPersistent::CAlign::Load (void) {
	this->m_error <<__METHOD__<<__s_ok;
	if (this->m_p_ctrl == 0)
		return this->m_error << __e_pointer = p_err_ptr;

	TRegKeyEx reg_key;
	THorzAlign::_value align_horz = THorzAlign::IndexToEnum(reg_key.Value().GetDword(CRoot().Path(m_p_ctrl->Id()), p_align_horz));
	this->m_p_ctrl->Layout().Ribbon().Tabs().Align().Horz().Value() = align_horz;

	TVertAlign::_value align_vert = TVertAlign::IndexToEnum(reg_key.Value().GetDword(CRoot().Path(m_p_ctrl->Id()), p_align_vert));
	this->m_p_ctrl->Layout().Ribbon().Tabs().Align().Vert().Value() = align_vert;
	
	return this->Error();
}
err_code CPersistent::CAlign::Save (void) {
	this->m_error <<__METHOD__<<__s_ok;
	if (this->m_p_ctrl == 0)
		return this->m_error << __e_pointer = p_err_ptr;

	TRegKeyEx reg_key;
	if (__failed(reg_key.Value().Set(CRoot().Path(m_p_ctrl->Id()), p_align_horz, this->m_p_ctrl->Layout().Ribbon().Tabs().Align().Horz().Value()))) this->m_error = reg_key.Error();

	return this->Error();
}

CPersistent::CAlign& CPersistent::CAlign::operator <<(TabCtrl* _p_ctrl) { this->m_p_ctrl = _p_ctrl; return *this; }

#pragma endregion
#pragma region cls::CRoot{}

_pc_sz  CRoot::Path (void) const {
	static CString cs_root;
	if (cs_root.IsEmpty()) {
		cs_root = TString().Format(_T("%s\\Tabbed"), TBase::Path());
	}
	return (_pc_sz) cs_root;
}

_pc_sz  CRoot::Path (const uint32_t _ctrl_id) const {
	static CString cs_node;
	cs_node = TString().Format(_T("%s\\0x%04x"), this->Path(), _ctrl_id);
	return (_pc_sz) cs_node;
}

const
CRoot_ctrl& CRoot::operator ()(void) const { return (TBase&)*this; }
CRoot_ctrl& CRoot::operator ()(void)       { return (TBase&)*this; }

#pragma endregion
#pragma region cls::CPersistent{}

CPersistent::CPersistent (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& CPersistent::Error (void) const { return this->m_error; }
const
CPersistent::CSide&  CPersistent::Side (void) const { return this->m_side; }
CPersistent::CSide&  CPersistent::Side (void)       { return this->m_side; }

#pragma endregion
#pragma region cls::CSide{}

using CSide = CPersistent::CSide;

CSide::CSide (void) : m_p_ctrl(0) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& CSide::Error (void) const { return this->m_error; }

static _pc_sz p_side_nm = _T("Side");

err_code CSide::Load (void) {
	this->m_error <<__METHOD__<<__s_ok;
	if (this->m_p_ctrl == 0)
		return this->m_error << __e_pointer = p_err_ptr;

	TRegKeyEx reg_key;
	const TSide side = CSides::IndexToEnum(reg_key.Value().GetDword(CRoot().Path(m_p_ctrl->Id()), p_side_nm));
	this->m_p_ctrl->Layout().Ribbon().LocatedOn(side);

	return this->Error();
}

err_code CSide::Save (void) {
	this->m_error <<__METHOD__<<__s_ok;
	if (m_p_ctrl == 0)
		return this->m_error << __e_pointer = p_err_ptr;

	TRegKeyEx reg_key;
	if (__failed(reg_key.Value().Set(CRoot().Path(m_p_ctrl->Id()), p_side_nm, this->m_p_ctrl->Layout().Ribbon().LocatedOn()))) this->m_error = reg_key.Error();

	return this->Error();
}

CSide& CSide::operator <<(TabCtrl* _p_ctrl) { this->m_p_ctrl = _p_ctrl; return *this; }

#pragma endregion