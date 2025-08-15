/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Aug-2025 at 11:59:37.635, (UTC+4), Batumi, Thursday;
	This is Ebo Pack Sfx  tabbed user control wrapper interface implementation file;
*/
#include "ctl.tabbed.h"

using namespace ebo::boo::gui::ctl;

#include "win.gui_view.h"

/////////////////////////////////////////////////////////////////////////////

CPages:: CPages (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CPages::~CPages (void) {}

err_code CPages::At_1st(void) {
	this->m_error <<__METHOD__<<__s_ok;

	CTabbed& tabbed = this->Get(); tabbed;
#if defined(_test_case_lvl) && (_test_case_lvl >= 2)

	using TSide = ex_ui::controls::layout::CMargins_of_rect::CSides::_part;

	tabbed.Layout().Tabs().LocatedOn(TSide::e_top);
	tabbed.Layout().Tabs().Align().Horz().Value() = THorzAlign::eLeft;
#if (0)
	this->m_error << tabbed.Tabs().Append(1, _T("DirectX")); if (this->Error()) { return this->Error(); } // the tab page #0;
	this->m_error << tabbed.Tabs().Append(2, _T("OpenGL"));  if (this->Error()) { return this->Error(); } // the tab page #1; the total == cfg::n_page_count;
#else
	this->m_error << tabbed.Tabs().Append(_T("DirectX")); if (this->Error()) { return this->Error(); } // the tab page #0;
	this->m_error << tabbed.Tabs().Append(_T("OpenGL"));  if (this->Error()) { return this->Error(); } // the tab page #1; the total == cfg::n_page_count;
#endif
	tabbed.Tabs().Tab(0).Page().Borders().Thickness(1);
	tabbed.Tabs().Tab(1).Page().Borders().Thickness(1);

	this->Trackers().At_1st(); // no error check yet;

#endif
	return this->Error();
}

TError&  CPages::Error (void) const { return this->m_error; }

const
CTabbed& CPages::Get (void) const { return this->m_tabbed; }
CTabbed& CPages::Get (void)       { return this->m_tabbed; }

bool CPages::Is_valid (void) const {
	this->m_error <<__METHOD__<<__s_ok;

	const CTabbed& tabbed = this->Get();
	const int16_t n_pages = static_cast<int16_t>(tabbed.Tabs().Count());

	if (0 == n_pages)
		return false == (this->m_error << __e_not_inited = _T("The tabbed control has no pages")).Is();

	for (int16_t i_ = 0; i_ < n_pages; i_++) {
		if (tabbed.Tabs().Tab(i_).Page().Is_valid() == false) {
			this->m_error << __e_hwnd = TString().Format(_T("The tab#%d has invalid page window"), i_); break;
		}
	}

	return false == this->Error();
}

err_code CPages::OnCreate (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Get().Is_valid())
		return this->m_error = (err_code) TErrCodes::eObject::eExists;

	if (!shared::Get_View().Parent())
		return this->m_error = __e_hwnd;

	CTabbed& tabbed = this->Get();
	// (1) creates tabbed user control;
	if (__failed(tabbed.Create(shared::Get_View().Parent(), 0xB)))
		return this->m_error = tabbed.Error();

	// (2) creates the trackball controls;
	if (__failed(this->Trackers().OnCreate()))
		return this->m_error = this->Trackers().Error();

	return this->Error();
}

err_code CPages::OnDestroy(void) {
	this->m_error <<__METHOD__<<__s_ok;

	this->Trackers().OnDestroy(); // no error check yet;

	CTabbed& tabbed = this->Get();

	if (__failed(tabbed.Destroy()))
		this->m_error = tabbed.Error();

	return this->Error();
}

const
CTrackers& CPages::Trackers(void) const { return this->m_tracks; }
CTrackers& CPages::Trackers(void)       { return this->m_tracks; }