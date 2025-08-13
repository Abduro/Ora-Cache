/*
	Created by Tech_dog (ebontrop@gmail.com) on 31-May-2025 at 02:33:20.860, UTC+4, Batumi, Saturday;
	This is Ebo Pack draw renderer test app main view interface implementation file;
*/
#include "win.gui_view.h"
using namespace ebo::boo::gui;

#include "ebo.sha.gui.theme.h"
using namespace ebo::sha::theme::paths;

#if (0) // unfortunately the integration this project with test-cases one is not easy deal, thus it is stopped;

#include "ebo_test_$d$.image.case.h"
#include "ebo_test_$d$.theme.case.h"

using namespace ebo::boo::test::cases;
#endif

namespace ebo { namespace boo { namespace gui { namespace _impl {

	CString Get_entry_point (void) {
	
		static bool b_1st_time = false;
		static shared::sys_core::CSystemTime time;

		if (b_1st_time == false) {
			b_1st_time = true;

			time.Offset().Get()._hours = -12;
			time.Offset().Get()._mins  =  34;

			time.Offset().Alias(_T("The Moon"));
		}
		time.Current();
		CString cs_out = time.To_string(shared::sys_core::CDateTimeFmt::iso_8601::e_time_complete);
		cs_out += TStringEx().Format (_T(" (%s)"), time.Offset().Alias());

		return cs_out;
	}

}}}}

using namespace ebo::boo::gui::_impl;
/////////////////////////////////////////////////////////////////////////////

CFooter:: CFooter (void) : m_timer(*this) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CFooter::~CFooter (void) { if (m_timer.IsValid()) m_timer.Destroy(); }

/////////////////////////////////////////////////////////////////////////////

#define pane_borders_thick 1

err_code  CFooter::At_1st(void) {
	this->m_error <<__METHOD__<<__s_ok;

	CSta_bar& sta_bar = this->Get();

	if (sta_bar.Panes().Count())
		return this->m_error << (err_code) TErrCodes::eObject::eInited;

	// (1) gets path to the folder of the test images;

	using CPaths = ebo::sha::theme::paths::CStatus;
	CPaths paths;

	if (__failed(paths.Set())) {
		return this->m_error = paths.Error();
	}

	using namespace ex_ui::controls::sfx::status;

	// (2) loads images and appends them to the status bar image list;
	CImages& images = sta_bar.Images();

	if (__failed(images.List().Append((_pc_sz) paths.Get(0), TImgFmt::e_png))) return this->m_error = images.List().Error();
	if (__failed(images.List().Append((_pc_sz) paths.Get(1), TImgFmt::e_png))) return this->m_error = images.List().Error();

	// (3) adds panes to status bar:
	if (__failed(sta_bar.Panes().Add())) return this->m_error = this->Get().Panes().Error(); // (3.1) the status icon pane, no text is intended for it;
	if (__failed(sta_bar.Panes().Add())) return this->m_error = this->Get().Panes().Error(); // (3.2) text message pane;
	if (__failed(sta_bar.Panes().Add())) return this->m_error = this->Get().Panes().Error(); // (3.3) graphical clock representation control pane;

	// (4) sets properties of the panes; actually accessing directly the reference to the vector of the raw panes would make a sense;
	CPane&  pane_0 = this->Get().Panes().Pane(0); if (this->Get().Panes().Error()) return this->m_error = this->Get().Panes().Error();
	CPane&  pane_1 = this->Get().Panes().Pane(1); if (this->Get().Panes().Error()) return this->m_error = this->Get().Panes().Error();
	CPane&  pane_2 = this->Get().Panes().Pane(2); if (this->Get().Panes().Error()) return this->m_error = this->Get().Panes().Error();

	using CLay_Style = ex_ui::controls::sfx::status::layout::CStyle;

#pragma region pane_no_0
{
	pane_0.Format().Image().Index(0);    // it is supposed to be an image 'ready' status by default;

	ex_ui::controls::pane::CFormat& fmt_ = pane_0.Format(); fmt_;
	ex_ui::controls::sfx::status::TPn_Lay& out_ = pane_0.Layout(); out_;

	out_.Style().Width() << CLay_Style::CWidth::e_fixed;
	out_.Image().Margins().Set(0x2);   // sets 2px for margins of all sides in order to have some gap between the pane image and pane boundaries;
	out_.Image().Margins().Left(0x9);  // just for testing of the left side indentation ; the value is in accordance with the image being used;

	out_.Fixed(sta_bar.Layout().Height());
}
#pragma endregion

#pragma region pane_no_1
{
	ex_ui::controls::pane::CFormat& fmt_ = pane_1.Format(); fmt_;
	ex_ui::controls::sfx::status::TPn_Lay& out_ = pane_1.Layout(); out_;

	out_.Style().Width() << CLay_Style::CWidth::e_auto;
	out_.Padding().Left(0x5);

	pane_1.Text(_T("Ready"));
}
#pragma endregion

#pragma region pane_no_2
{
	ex_ui::controls::pane::CFormat& fmt_ = pane_2.Format(); fmt_;
	ex_ui::controls::sfx::status::TPn_Lay& out_ = pane_2.Layout(); out_;

	out_.Style().Stick() << CLay_Style::CStick::e_right;
	out_.Style().Width() << CLay_Style::CWidth::e_fixed;
	out_.Fixed(215); // ToDo: needs to have some calculation of the width from expected string pattern length;

	out_.Padding().Left(0x3);

	pane_2.Text(_T("00:00:00:000"));
#if defined(pane_borders_thick) && (pane_borders_thick != 0)
//	pane_2.Borders().Left()  << pane_borders_thick; the border class operator '<<' sets its ID and not the thickness of its base class 'line';
//	pane_2.Borders().Right() << pane_borders_thick; the same as above;
	pane_2.Borders().Left().Thickness(pane_borders_thick);
	pane_2.Borders().Right().Thickness(pane_borders_thick);
#if defined(_DEBUG)
	for (ex_ui::controls::borders::TRawBorders::const_iterator it_ = pane_2.Borders().Raw().begin(); it_ != pane_2.Borders().Raw().end(); ++it_) {
		const CBorder& border = it_->second;
		if (border.Is_valid() && !!border.Thickness()) {
			bool b_is_valid = false; b_is_valid = !b_is_valid;
		}
	}
#endif
#endif
}
#pragma endregion

	CGlyph& glyph = this->Get().Panes().Glyph();

	glyph.Format().Image().Index(1);
	glyph.Layout().Style().Width() << CLay_Style::CWidth::e_fixed;
	glyph.Layout().Fixed(sta_bar.Layout().Height());

	return this->Error();
}

TError&   CFooter::Error (void) const { return this->m_error; }
const
CSta_bar& CFooter::Get (void) const { return this->m_bar; }
CSta_bar& CFooter::Get (void)       { return this->m_bar; }

err_code  CFooter::OnCreate (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Get().Is_valid())
		return this->m_error = (err_code) TErrCodes::eObject::eExists;

	if (!shared::Get_View().Parent())
		return this->m_error = __e_hwnd;

	CSta_bar& sta_bar = this->Get();
	// (1) creates status bar user control;
	if (__failed(sta_bar.Create(shared::Get_View().Parent(), 0xA)))
		return this->m_error = this->Get().Error();

	this->m_error << this->m_timer.Create(100);
	return this->Error();
}

err_code  CFooter::OnDestroy (void) {
	this->m_error <<__METHOD__<<__s_ok;

	CSta_bar& sta_bar = this->Get();

	if (__failed(sta_bar.Destroy()))
		this->m_error = sta_bar.Error();

	return this->Error();
}

void  CFooter::SetText(_pc_sz _p_text, const uint16_t _pane_ndx/* = 1*/) {
	_p_text; _pane_ndx;
	this->Get().Panes().Pane(_pane_ndx).Text(_p_text);
}

void  CFooter::IWaitable_OnComplete (void) {

	this->Get().Panes().Pane(2).Text((_pc_sz) Get_entry_point());
}

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

	return this->Error();
}

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
	
	return this->Error();
}
err_code  CTracker::OnDestroy(void) { return this->Error(); }

/////////////////////////////////////////////////////////////////////////////

CView:: CView (void) {
#if defined(_test_case_lvl) && (_test_case_lvl == 0)
	this->Pane().Borders().Top().Thickness(1);
	this->Pane().Borders().Top().Color() << shared::Get_Theme().Get(TThemePart::e_panel, TThemeElement::e_border);

	this->Pane().Format().Bkgnd() << shared::Get_Theme().Get(TThemePart::e_form, TThemeElement::e_back);
#elif (1==0)
	this->Status().Borders().Top().Thickness(1);
	this->Status().Borders().Top().Color() << shared::Get_Theme().Get(TThemePart::e_panel, TThemeElement::e_border);
#endif
#if defined(_test_case_lvl) && (_test_case_lvl >= 2)
	using TSide = ex_ui::controls::layout::CMargins_of_rect::CSides::_part;

#define _use_case -1 // this set of unit tests is no longer used;

#if defined(_use_case) && (_use_case == 0)   // sets tabs layout on the top side and the horizontal align from the left side;
	this->Tabbed().Layout().Tabs().Side(TSide::e_top);
	this->Tabbed().Layout().Tabs().Align().Horz().Value() = THorzAlign::eLeft;
#elif defined(_use_case) && (_use_case == 1) // sets tabs layout on the top side and the horizontal align from the right side;
	this->Tabbed().Layout().Tabs().Side(TSide::e_top);
	this->Tabbed().Layout().Tabs().Align().Horz().Value() = THorzAlign::eRight;
#elif defined(_use_case) && (_use_case == 2) // sets tabs layout on the left side and the vertical align from the bottom side;
	// for this mode of tabs placement, a compact option must be considered;
	this->Tabbed().Layout().Tabs().Side(TSide::e_left);
	this->Tabbed().Layout().Tabs().Align().Vert().Value() = TVertAlign::eBottom;
#elif defined(_use_case) && (_use_case == 3) // sets tabs layout on the left side and the vertical align from the top side;
	this->Tabbed().Layout().Tabs().Side(TSide::e_left);
	this->Tabbed().Layout().Tabs().Align().Vert().Value() = TVertAlign::eTop;
#elif defined(_use_case) && (_use_case == 4) // sets tabs layout on the right side and the vertical align from the top side;
	// for this mode of tabs placement, a compact option must be considered too;
	this->Tabbed().Layout().Tabs().Side(TSide::e_right);
	this->Tabbed().Layout().Tabs().Align().Vert().Value() = TVertAlign::eTop;
#elif defined(_use_case) && (_use_case == 5) // sets tabs layout on the right side and the vertical align from the bottom side;
	// for this mode of tabs placement, a compact option must be considered too;
	this->Tabbed().Layout().Tabs().Side(TSide::e_right);
	this->Tabbed().Layout().Tabs().Align().Vert().Value() = TVertAlign::eBottom;
#elif defined(_use_case) && (_use_case == 6) // sets tabs layout on the bottom side and the horizontal align from the left side;
	this->Tabbed().Layout().Tabs().Side(TSide::e_bottom);
	this->Tabbed().Layout().Tabs().Align().Horz().Value() = THorzAlign::eLeft;
#elif defined(_use_case) && (_use_case == 7) // sets tabs layout on the bottom side and the horizontal align from the right side;
	this->Tabbed().Layout().Tabs().Side(TSide::e_bottom);
	this->Tabbed().Layout().Tabs().Align().Horz().Value() = THorzAlign::eRight;
#endif
	/*
		the exact name is very important and can be seen in the system font viewer:
		Control Panel >> Appearance and Personalization >> Fonts >> double click on 'Pirulen Regular' item;
		the font name is in the top-left corner (not in window caption);
	*/
// 	this->Tabbed().Tabs().Append(1, _T("A1G2U3X4")); // for testing 'Pirulen Rg' font;
#endif
}
CView::~CView (void) {}

/////////////////////////////////////////////////////////////////////////////
const
CFooter& CView::Footer (void) const { return this->m_footer; }
CFooter& CView::Footer (void)       { return this->m_footer; }

err_code CView::OnCreate (void) {

	err_code n_result = __s_ok;

	n_result = this->Footer().At_1st();
	n_result = this->Pages().At_1st();

	n_result = this->Footer().OnCreate(); if (__failed(n_result)) return n_result;
	n_result = this->Pages().OnCreate(); if (__failed(n_result)) return n_result; // it is very discussable to exit on error throw;

	return n_result;
}

err_code CView::OnDestroy (void) {
	err_code n_result = __s_ok;

	this->Footer().OnDestroy(); // no error handling is made yet;
	this->Pages().OnDestroy();
	this->Tracker().OnDestroy();

	return n_result;
}

err_code CView::OnDraw (const HDC _h_dc, const t_rect& _drw_area) {
	_h_dc; _drw_area;
	err_code n_result = __s_ok;
#if defined(_test_case_lvl) && (_test_case_lvl == 0)
	n_result = this->Pane().Draw(_h_dc, _drw_area); // *important*: the rectangle being received is entire window client area!
#endif
#if defined(_test_case_lvl) && (_test_case_lvl >= 1)
	n_result = this->Footer().Get().Refresh();
#endif
#if defined(_test_case_lvl) && (_test_case_lvl >= 2)
	n_result = this->Pages().Get().Refresh();
#endif
	return n_result;
}

#if defined(_test_case_lvl) && (_test_case_lvl == 0)
const
ex_ui::controls::sfx::CPane&    CView::Pane (void) const { return this->m_pane; }
ex_ui::controls::sfx::CPane&    CView::Pane (void)       { return this->m_pane; }
#endif
const
CWindow&  CView::Parent (void) const { return this->m_parent; }
CWindow&  CView::Parent (void)       { return this->m_parent; }
const
CPages&   CView::Pages  (void) const { return this->m_pages; }
CPages&   CView::Pages  (void)       { return this->m_pages; }
const
CSurface& CView::Surface(void) const { return this->m_surface; }
CSurface& CView::Surface(void)       { return this->m_surface; }
const
CTracker& CView::Tracker(void) const { return this->m_tracker; }
CTracker& CView::Tracker(void)       { return this->m_tracker; }

/////////////////////////////////////////////////////////////////////////////

namespace shared {
	TView&  Get_View (void) {
		static TView main_view;
		return main_view;
	}
}