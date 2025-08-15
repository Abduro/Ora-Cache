/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Aug-2025 at 12:02:41.244, (UTC+4), Batumi, Thursday;
	This is Ebo Pack Sfx trackball user control wrapper interface implementation file;
*/
#include "ctl.trkball.h"
#include "ctl.tabbed.h"
#include "win.gui_layout.h"
#include "win.gui_view.h"

using namespace ebo::boo::gui::ctl;

/////////////////////////////////////////////////////////////////////////////

CTracker:: CTracker (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CTracker::~CTracker (void) {}

err_code  CTracker::At_1st(void) {
	this->m_error <<__METHOD__<<__s_ok;
#if defined(_test_case_lvl) && (_test_case_lvl >= 2)
	CTrkball& tracker = this->Get(); tracker;
#endif
	return this->Error();
}

TError&   CTracker::Error (void) const { return this->m_error; }
const
CTrkball& CTracker::Get (void) const { return this->m_tracker; }
CTrkball& CTracker::Get (void)       { return this->m_tracker; }

err_code  CTracker::OnCreate (const CTab& _tab) {
	_tab;
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Get().Is_valid())
		return this->m_error = (err_code) TErrCodes::eObject::eExists;

	if (_tab.Page().Is_valid() == false)
		return this->m_error << __e_hwnd = _T("Invalid tabbed page window handle");

	layout::CTrack& track = ::shared::Get_Layout().Tracks().Get(_tab.Index());

	const t_rect track_rect = track.GetPos(_tab);
	if (::IsRectEmpty(&track_rect))
		return this->m_error = track.Error();

	static uint32_t id_selector = 0;
	this->m_error << this->Get().Create(_tab.Page().Handle(), 0xB + (++id_selector), track_rect);

	if (this->Error())
		return this->Error();

	return this->Error();
}

err_code  CTracker::OnDestroy(void) {
	this->m_error <<__METHOD__<<__s_ok;

	if ((*this)().Is_valid() == false)
		return this->Error(); // no generating the error this time; it is not required yet;

	this->m_error << (*this)().Destroy();

	return this->Error();
}
const
CTrkball& CTracker::operator ()(void) const { return this->Get(); }
CTrkball& CTracker::operator ()(void)       { return this->Get(); }

/////////////////////////////////////////////////////////////////////////////

CTrackers:: CTrackers (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CTrackers::~CTrackers (void) {}

err_code CTrackers::At_1st(void) {
	this->m_error <<__METHOD__<<__s_ok;

	for (uint16_t i_ = 0; i_ < cfg::n_page_count; i_++) {
		if (__failed(this->m_trackers[i_].At_1st())) {
			this->m_error = this->m_trackers[i_].Error(); break; // the all trackers has the same settings, so if it's somethig wrong, break;
		}
	}

	return this->Error();
}

TError&  CTrackers::Error (void) const { return this->m_error; }

err_code CTrackers::OnCreate (void) {
	this->m_error <<__METHOD__<<__s_ok;

	const CPages& pages = ::shared::Get_View().Pages();

	for (uint16_t i_ = 0; i_ < cfg::n_page_count; i_++) {

		const ex_ui::controls::sfx::tabbed::CTab& tab_ = pages.Get().Tabs().Tab(i_);

		if (__failed(this->m_trackers[i_].OnCreate(tab_))) {
			this->m_error = this->m_trackers[i_].Error(); break;
		}
	}

	return this->Error();
}

err_code CTrackers::OnDestroy(void) {
	this->m_error <<__METHOD__<<__s_ok;

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-destroywindow ;
	// all trackers' windows are destroyed automatically because the page window is the parent one been destroyed first;
	// that means this method must be called before tabbed control destroyng, because on destroying some resources must be freed;

	for (uint16_t i_ = 0; i_ < cfg::n_page_count; i_++) {
		if (__failed(this->m_trackers[i_].OnDestroy()))
			this->m_error = this->m_trackers[i_].Error(); // no error handling is required yet;
	}

	return this->Error();
}

#if (0)
CTracker& Get_facke_tracker (void) {
	static CTracker tracker; return tracker;
}

const
CTracker& CTrackers::Get (const uint16_t _n_index) const { if (_n_index > cfg::n_page_count - 1) return Get_facke_tracker(); else return this->m_trackers[_n_index]; }
CTracker& CTrackers::Get (const uint16_t _n_index)       { if (_n_index > cfg::n_page_count - 1) return Get_facke_tracker(); else return this->m_trackers[_n_index]; }
#else
const
CTracker* CTrackers::Get (const uint16_t _n_index) const { if (_n_index > cfg::n_page_count - 1) return nullptr; else return &this->m_trackers[_n_index]; }
CTracker* CTrackers::Get (const uint16_t _n_index)       { if (_n_index > cfg::n_page_count - 1) return nullptr; else return &this->m_trackers[_n_index]; }
#endif