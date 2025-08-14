/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Aug-2025 at 12:02:41.244, (UTC+4), Batumi, Thursday;
	This is Ebo Pack Sfx trackball user control wrapper interface implementation file;
*/
#include "ctl.trkball.h"
#include "win.gui_layout.h"

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

err_code  CTracker::OnCreate (const HWND _h_page) {
	_h_page;
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Get().Is_valid())
		return this->m_error = (err_code) TErrCodes::eObject::eExists;

	if (nullptr == _h_page || !::IsWindow(_h_page))
		return this->m_error << __e_hwnd = _T("Invalid parent window handle");

	const t_rect track_rect = ::shared::Get_Layout().Page().GetTrackerPos();
	if (::IsRectEmpty(&track_rect))
		return this->m_error = ::shared::Get_Layout().Page().Error();

	static uint32_t id_selector = 0;
	this->m_error << this->Get().Create(_h_page, 0xB + (++id_selector), track_rect);

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