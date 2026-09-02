/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Aug-2026 at 23:23:51.103, UTC+4, Batumi, Saturday;
	This is virtual camera test desktop app main window view interface implementation file;
*/
#include "test.gui.view.h"

using namespace ::test::app;

#pragma region cls::CPages{}

CPages:: CPages (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CPages::~CPages (void) {}

err_code CPages::At_1st(void) {
	this->m_error <<__METHOD__<<__s_ok;

	CTabbed& tabbed = this->Get(); tabbed;
#if defined(_test_case_lvl) && (_test_case_lvl >= 0)

	using TSide = ex_ui::controls::layout::CMargins_of_rect::CSides::_part;

	tabbed.Layout().Tabs().LocatedOn(TSide::e_top);
	tabbed.Layout().Tabs().Align().Horz().Value() = THorzAlign::eLeft;

	for (uint16_t i_ = 0; i_ < cfg::u_page_count; i_++) {
		this->m_error << tabbed.Tabs().Append(TString().Format(_T("Test #%u"), (i_ + 1))); if (this->Error()) { break; }
		tabbed.Tabs().Tab(i_).Page().Borders().Thickness(cfg::u_border_thick);
	}

#endif
	return this->Error();
}

TError&  CPages::Error (void) const { return this->m_error; }
const
CTabbed& CPages::Get (void) const { return this->m_tabs; }
CTabbed& CPages::Get (void)       { return this->m_tabs; }

bool CPages::Is_valid(void) const {
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
	if (__failed(tabbed.Create(shared::Get_View().Parent(), 0xB)))
		return this->m_error = tabbed.Error();

	return this->Error();
}

err_code CPages::OnDestroy(void) {
	this->m_error <<__METHOD__<<__s_ok;
	CTabbed& tabbed = this->Get();

	if (__failed(tabbed.Destroy()))
		this->m_error = tabbed.Error();

	return this->Error();
}

#pragma endregion
#pragma region cls::CView{}

CView:: CView (void) {}

err_code CView::OnCreate (void) {

	err_code n_result = __s_ok;
	n_result = this->Pages().At_1st();
	n_result = this->Pages().OnCreate(); if (__failed(n_result)) return n_result; // it is very discussable to exit on error throw;

	return n_result;
}

err_code CView::OnDestroy (void) {

	err_code n_result = this->Pages().OnDestroy();
	return n_result;
}

err_code CView::OnDraw (const HDC _h_dc, const rect_t& _drw_area) {
	_h_dc; _drw_area;
	err_code n_result = __s_ok;
	n_result = this->Pages().Get().Refresh();
	return n_result;
}
const
CWindow&  CView::Parent (void) const { return this->m_parent; }
CWindow&  CView::Parent (void)       { return this->m_parent; }
const
CPages&   CView::Pages  (void) const { return this->m_pages; }
CPages&   CView::Pages  (void)       { return this->m_pages; }

CView& CView::operator <<(const HWND _h_app_wnd) { this->m_parent = _h_app_wnd;  return *this; }


#pragma endregion

namespace shared {
	TView&  Get_View (void) {
		static TView main_view;
		return main_view;
	}
}