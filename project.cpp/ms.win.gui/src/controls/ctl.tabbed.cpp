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

	this->m_error << tabbed.Tabs().Append(1, _T("DirectX")); if (this->Error()) { return this->Error(); } // the tab page #0;
	this->m_error << tabbed.Tabs().Append(2, _T("OpenGL"));  if (this->Error()) { return this->Error(); } // the tab page #1; the total == CPages::n_count;

	tabbed.Tabs().Tab(0).Page().Borders().Thickness(1);
	tabbed.Tabs().Tab(1).Page().Borders().Thickness(1);

	for (uint16_t i_ = 0; i_ < CPages::n_count; i_++) {
		if (__failed(this->m_trackers[i_].At_1st())) {
			this->m_error = this->m_trackers[i_].Error(); break; // the all trackers has the same settings, so if it's somethig wrong, break;
		}
	}

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

	for (uint16_t i_ = 0; i_ < CPages::n_count; i_++) {
		const HWND h_page = tabbed.Tabs().Tab(i_).Page().Handle();
		if (__failed(this->m_trackers[i_].OnCreate(h_page))) {
			this->m_error = this->m_trackers[i_].Error(); break;
		}
	}
	return this->Error();
}

err_code CPages::OnDestroy(void) {
	this->m_error <<__METHOD__<<__s_ok;

	CTabbed& tabbed = this->Get();

	if (__failed(tabbed.Destroy()))
		this->m_error = tabbed.Error();

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-destroywindow ;
	// all trackers' windows are destroyed automatically because the page window is the parent one been destroyed first;

	for (uint16_t i_ = 0; i_ < CPages::n_count; i_++) {
		this->m_trackers[i_].OnDestroy(); // no error handling is required yet;
	}

	return this->Error();
}

#if (0)
CTracker& Get_facke_tracker (void) {
	static CTracker tracker; return tracker;
}

const
CTracker& CPages::Tracker (const uint16_t _n_index) const { if (_n_index > CPages::n_count - 1) return Get_facke_tracker(); else return this->m_trackers[_n_index]; }
CTracker& CPages::Tracker (const uint16_t _n_index)       { if (_n_index > CPages::n_count - 1) return Get_facke_tracker(); else return this->m_trackers[_n_index]; }
#else
const
CTracker* CPages::Tracker (const uint16_t _n_index) const { if (_n_index > CPages::n_count - 1) return nullptr; else return &this->m_trackers[_n_index]; }
CTracker* CPages::Tracker (const uint16_t _n_index)       { if (_n_index > CPages::n_count - 1) return nullptr; else return &this->m_trackers[_n_index]; }
#endif