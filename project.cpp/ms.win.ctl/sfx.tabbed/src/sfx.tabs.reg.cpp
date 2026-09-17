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

	class CPage_router {
	public:
	static constexpr _pc_sz p_pg_key_pat = _T("%s\\Pages");
	static constexpr _pc_sz p_pg_brd_pat = _T("%s\\Borders");
	static constexpr _pc_sz p_pg_brd_val = _T("Thickness");

		 CPage_router (void) = default; CPage_router (const CPage_router&) = delete; CPage_router (CPage_router&&) = delete;
		~CPage_router (void) = default;

		_pc_sz Borders (const uint32_t _ctrl_id) {
			return (_pc_sz)(this->m_cache = TString().Format(p_pg_brd_pat, this->Pages(_ctrl_id)));
		}
		_pc_sz Pages (const uint32_t _ctrl_id) {
			return (_pc_sz)(this->m_cache = TString().Format(p_pg_key_pat, CRouter_paths().Tab_ctrl(_ctrl_id)));
		}

	private:
		 CPage_router& operator = (const CPage_router&) = delete; CPage_router& operator = (CPage_router&&) = delete;
		 CString m_cache;
	};

}}}} using namespace ex_ui::controls::tabbed::_impl;

static _pc_sz p_err_ptr = _T("The pointer to tab control is not set");
static _pc_sz p_align_horz = _T("Align_Horz");
static _pc_sz p_align_vert = _T("Align_Vert");
static _pc_sz p_active_tab = _T("Active_Tab");
static _pc_sz p_cap_orient = _T("Cap_orient");

#pragma region cls::CBase{}

using CPersBase = ::ex_ui::controls::tabbed::storage::CBase;

CPersBase::CBase (void) : m_p_ctrl(0) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

_pc_sz   CPersBase::Class (void) { static CString cs_cls; if (cs_cls.IsEmpty()) cs_cls = __CLASS__; return (_pc_sz)cs_cls; }
TError&  CPersBase::Error (void) const { return this->m_error; }

bool  CPersBase::Is_valid (void) const { return this->m_p_ctrl != 0; }

CPersBase& CPersBase::operator <<(TabCtrl* _p_ctrl) { this->m_p_ctrl = _p_ctrl; return *this; }
bool CPersBase::operator () (void) const { return this->Is_valid(); }

#pragma endregion
#pragma region cls::CActive{}

using CActiveTab = ::ex_ui::controls::tabbed::storage::CTabs::CActive;

CActiveTab::CActive (void) : TBase() { TBase::m_error >>TString().Format(_T("%s::%s"), (_pc_sz)CPersBase::Class(), (_pc_sz)__CLASS__); }

err_code CActiveTab::Load (void) {
	TBase::m_error <<__METHOD__<<__s_ok;
	if (false == (*this)())
		return TBase::m_error << __e_pointer = p_err_ptr;

	TRegKeyEx reg_key;
	const int16_t tab_ndx = static_cast<int16_t>(reg_key.Value().GetDword(CRoot().Path(m_p_ctrl->Id()), p_active_tab));
	TBase::m_error << this->m_p_ctrl->Tabs().Active(tab_ndx);
	
	return TBase::Error();
}

err_code CActiveTab::Save (void) {
	TBase::m_error <<__METHOD__<<__s_ok;
	if (false == (*this)())
		return TBase::m_error << __e_pointer = p_err_ptr;

	TRegKeyEx reg_key;
	if (__failed(reg_key.Value().Set(CRoot().Path(m_p_ctrl->Id()), p_active_tab, this->m_p_ctrl->Tabs().Active()))) TBase::m_error = reg_key.Error();

	return TBase::Error();
}

#pragma endregion
#pragma region cls::CAlign{}

using CTabsAlign = ::ex_ui::controls::tabbed::storage::CTabs::CAlign;

CTabsAlign::CAlign (void) : TBase() { TBase::m_error >>TString().Format(_T("%s::%s"), (_pc_sz)CPersBase::Class(), (_pc_sz)__CLASS__); }

err_code CTabsAlign::Load (void) {
	TBase::m_error <<__METHOD__<<__s_ok;
	if (false == (*this)())
		return TBase::m_error << __e_pointer = p_err_ptr;

	TRegKeyEx reg_key;
	THorzAlign::_value align_horz = THorzAlign::IndexToEnum(reg_key.Value().GetDword(CRoot().Path(m_p_ctrl->Id()), p_align_horz));
	this->m_p_ctrl->Layout().Ribbon().Tabs().Align().Horz().Value() = align_horz;

	TVertAlign::_value align_vert = TVertAlign::IndexToEnum(reg_key.Value().GetDword(CRoot().Path(m_p_ctrl->Id()), p_align_vert));
	this->m_p_ctrl->Layout().Ribbon().Tabs().Align().Vert().Value() = align_vert;
	
	return TBase::Error();
}
err_code CTabsAlign::Save (void) {
	this->m_error <<__METHOD__<<__s_ok;
	if (false == (*this)())
		return TBase::m_error << __e_pointer = p_err_ptr;

	TRegKeyEx reg_key;
	if (__failed(reg_key.Value().Set(CRoot().Path(m_p_ctrl->Id()), p_align_horz, this->m_p_ctrl->Layout().Ribbon().Tabs().Align().Horz().Value()))) TBase::m_error = reg_key.Error();

	return TBase::Error();
}

#pragma endregion
#pragma region cls::CBorders{}

using CPgBorders = ::ex_ui::controls::tabbed::storage::CPage::CBorders;

CPgBorders::CBorders (void) : TBase() { TBase::m_error >>TString().Format(_T("%s::%s"), (_pc_sz)CPersBase::Class(), (_pc_sz)__CLASS__); }

err_code CPgBorders::Load (void) {
	TBase::m_error <<__METHOD__<<__s_ok;
	if (false == (*this)())
		return TBase::m_error << __e_pointer = p_err_ptr;

	TRegKeyEx reg_key;
	dword_t brd_thick = reg_key.Value().GetDword(CPage_router().Borders(m_p_ctrl->Id()), CPage_router::p_pg_brd_val); brd_thick;

	return TBase::Error();
}

#pragma endregion
#pragma region cls::CCaption{}

using CTabsCap = ::ex_ui::controls::tabbed::storage::CTabs::CCaption;

CTabsCap::CCaption (void) : TBase() { TBase::m_error >>TString().Format(_T("%s::%s"), (_pc_sz)CPersBase::Class(), (_pc_sz)__CLASS__); }

err_code CTabsCap::Load (void) {
	TBase::m_error <<__METHOD__<<__s_ok;
	if (false == (*this)())
		return TBase::m_error << __e_pointer = p_err_ptr;

	using CCaps = CLayout::CTabs::CCaps;
	using e_orient = CCaps::e_orient;

	TRegKeyEx reg_key;
	e_orient  cap_orient = CCaps::DwordToEnum(reg_key.Value().GetDword(CRoot().Path(m_p_ctrl->Id()), p_cap_orient));
	this->m_p_ctrl->Layout().Ribbon().Tabs().Caps().Set_orient(cap_orient);

	return TBase::Error();
}

err_code CTabsCap::Save (void) {
	TBase::m_error <<__METHOD__<<__s_ok;
	if (false == (*this)())
		return TBase::m_error << __e_pointer = p_err_ptr;

	TRegKeyEx reg_key;
	if (__failed(reg_key.Value().Set(CRoot().Path(m_p_ctrl->Id()), p_cap_orient, this->m_p_ctrl->Layout().Ribbon().Tabs().Caps().Get_orient()))) TBase::m_error = reg_key.Error();

	return TBase::Error();
}

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

using CPersRbn = ::ex_ui::controls::tabbed::storage::CRibbon;
using CPersTabs = ::ex_ui::controls::tabbed::storage::CTabs;

CPersistent::CPersistent (void) : TBase() { TBase::m_error >>TString().Format(_T("%s::%s"), (_pc_sz)CPersBase::Class(), (_pc_sz)__CLASS__); }

err_code CPersistent::Load (void) {
	TBase::m_error <<__METHOD__<<__s_ok;
	if (false == (*this)())
		return TBase::m_error << __e_pointer = p_err_ptr;

	if (__failed(this->Ribbon().Load())) return TBase::m_error = this->Ribbon().Error();
	if (__failed(this->Tabs().Load())) return TBase::m_error = this->Tabs().Error();
	
	return TBase::Error();
}

err_code CPersistent::Save (void) {
	TBase::m_error <<__METHOD__<<__s_ok;
	if (false == (*this)())
		return TBase::m_error << __e_pointer = p_err_ptr;

	return TBase::Error();
}
const
CPersRbn& CPersistent::Ribbon (void) const { return this->m_ribbon; }
CPersRbn& CPersistent::Ribbon (void)       { return this->m_ribbon; }
const
CPersTabs& CPersistent::Tabs (void) const { return this->m_tabs; }
CPersTabs& CPersistent::Tabs (void)       { return this->m_tabs; }

CPersistent& CPersistent::operator <<(TabCtrl* _p_ctrl) { 
	(TBase&)(*this) <<_p_ctrl; this->Tabs() << _p_ctrl; this->Ribbon() << _p_ctrl; return *this;
}

#pragma endregion
#pragma region cls::CRibbon{}

using CRbnSide = ::ex_ui::controls::tabbed::storage::CRibbon::CSide;

CPersRbn::CRibbon (void) : TBase() { TBase::m_error >>TString().Format(_T("%s::%s"), (_pc_sz)CPersBase::Class(), (_pc_sz)__CLASS__); }

err_code CPersRbn::Load (void) {
	this->m_error <<__METHOD__<<__s_ok;
	if (false == (*this)())
		return TBase::m_error << __e_pointer = p_err_ptr;

	if (__failed(this->LocatedOn().Load())) return TBase::m_error = this->LocatedOn().Error();

	return TBase::Error();
}
err_code CPersRbn::Save (void) {
	this->m_error <<__METHOD__<<__s_ok;
	if (false == (*this)())
		return TBase::m_error << __e_pointer = p_err_ptr;

	if (__failed(this->LocatedOn().Save()))  return TBase::m_error = this->LocatedOn().Error();

	return TBase::Error();
}
const
CRbnSide&  CPersRbn::LocatedOn (void) const { return this->m_side_on; }
CRbnSide&  CPersRbn::LocatedOn (void)       { return this->m_side_on; }

CPersRbn& CPersRbn::operator <<(TabCtrl* _p_ctrl) { (TBase&)(*this) <<_p_ctrl; this->LocatedOn() << _p_ctrl; return *this; }

#pragma endregion
#pragma region cls::CSide{}

CRbnSide::CSide (void) : TBase() { TBase::m_error >>TString().Format(_T("%s::%s"), (_pc_sz)CPersBase::Class(), (_pc_sz)__CLASS__); }

static _pc_sz p_side_nm = _T("Side");

err_code CRbnSide::Load (void) {
	this->m_error <<__METHOD__<<__s_ok;
	if (false == (*this)())
		return TBase::m_error << __e_pointer = p_err_ptr;

	TRegKeyEx reg_key;
	const TSide side = CSides::IndexToEnum(reg_key.Value().GetDword(CRoot().Path(m_p_ctrl->Id()), p_side_nm));
	this->m_p_ctrl->Layout().Ribbon().LocatedOn(side);

	return TBase::Error();
}

err_code CRbnSide::Save (void) {
	this->m_error <<__METHOD__<<__s_ok;
	if (false == (*this)())
		return TBase::m_error << __e_pointer = p_err_ptr;

	TRegKeyEx reg_key;
	if (__failed(reg_key.Value().Set(CRoot().Path(m_p_ctrl->Id()), p_side_nm, this->m_p_ctrl->Layout().Ribbon().LocatedOn()))) TBase::m_error = reg_key.Error();

	return TBase::Error();
}

#pragma endregion
#pragma region cls::CSize{}

using CTabSize = ::ex_ui::controls::tabbed::storage::CTabs::CSize;

CTabSize::CSize (void) : TBase() { TBase::m_error >>TString().Format(_T("%s::%s"), (_pc_sz)CPersBase::Class(), (_pc_sz)__CLASS__); }

static _pc_sz  p_height_nm = _T("Height");
static _pc_sz  p_width_nm = _T("Width");
static _pc_sz  p_tab_size = _T("%s\\Tab_size");

err_code CTabSize::Load (void) {
	this->m_error <<__METHOD__<<__s_ok;
	if (false == (*this)())
		return TBase::m_error << __e_pointer = p_err_ptr;

	CString cs_key = TString().Format(p_tab_size, CRoot().Path(TBase::m_p_ctrl->Id()));

	TRegKeyEx reg_key;
	const uint32_t u_height = reg_key.Value().GetDword((_pc_sz)cs_key, p_height_nm);
	const uint32_t u_width  = reg_key.Value().GetDword((_pc_sz)cs_key, p_width_nm);

	TBase::m_p_ctrl->Layout().Ribbon().Tabs().Size().Set(u_width, u_height); // the 'Set()' function checks input argument values;

	return TBase::Error();
}

err_code CTabSize::Save (void) {
	this->m_error <<__METHOD__<<__s_ok;
	if (false == (*this)())
		return TBase::m_error << __e_pointer = p_err_ptr;

	CString cs_key = TString().Format(p_tab_size, CRoot().Path(TBase::m_p_ctrl->Id()));

	TRegKeyEx reg_key;
	if (__failed(reg_key.Value().Set((_pc_sz)cs_key, p_height_nm, TBase::m_p_ctrl->Layout().Ribbon().Tabs().Size().Height().Get()))) TBase::m_error = reg_key.Error();
	if (__failed(reg_key.Value().Set((_pc_sz)cs_key, p_width_nm , TBase::m_p_ctrl->Layout().Ribbon().Tabs().Size().Width().Get()))) TBase::m_error = reg_key.Error();

	return TBase::Error();
}

#pragma endregion
#pragma region cls::CTabs{}

CPersTabs::CTabs (void) : TBase() { TBase::m_error >>TString().Format(_T("%s::%s"), (_pc_sz)CPersBase::Class(), (_pc_sz)__CLASS__); }

const
CActiveTab& CPersTabs::Active (void) const { return this->m_active; }
CActiveTab& CPersTabs::Active (void)       { return this->m_active; }
const
CTabsAlign& CPersTabs::Align (void) const { return this->m_align; }
CTabsAlign& CPersTabs::Align (void)       { return this->m_align; }
const
CTabsCap& CPersTabs::Caption (void) const { return this->m_caption; }
CTabsCap& CPersTabs::Caption (void)       { return this->m_caption; }

err_code CPersTabs::Load (void) {
	TBase::m_error <<__METHOD__<<__s_ok;
	if (false == (*this)())
		return TBase::m_error << __e_pointer = p_err_ptr;

	if (__failed(this->Active().Load()))  return TBase::m_error = this->Active().Error();
	if (__failed(this->Align().Load()))   return TBase::m_error = this->Align().Error();
	if (__failed(this->Caption().Load())) return TBase::m_error = this->Caption().Error();
	if (__failed(this->Size().Load()))    return TBase::m_error = this->Size().Error();

	return TBase::Error();
}
err_code CPersTabs::Save (void) {
	this->m_error <<__METHOD__<<__s_ok;
	if (false == (*this)())
		return TBase::m_error << __e_pointer = p_err_ptr;

	if (__failed(this->Active().Save()))  return TBase::m_error = this->Active().Error();
	if (__failed(this->Align().Save()))   return TBase::m_error = this->Align().Error();
	if (__failed(this->Caption().Save())) return TBase::m_error = this->Caption().Error();
	if (__failed(this->Size().Save()))    return TBase::m_error = this->Size().Error();

	return TBase::Error();
}

const
CTabSize& CPersTabs::Size (void) const { return this->m_size; }
CTabSize& CPersTabs::Size (void)       { return this->m_size; }

CPersTabs& CPersTabs::operator <<(TabCtrl* _p_ctrl) {
	(TBase&)(*this) <<_p_ctrl; this->Active() << _p_ctrl; this->Align() << _p_ctrl; this->Caption() << _p_ctrl; this->Size() << _p_ctrl; return *this;
}

#pragma endregion