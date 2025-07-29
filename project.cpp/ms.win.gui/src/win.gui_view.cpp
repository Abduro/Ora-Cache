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

/////////////////////////////////////////////////////////////////////////////

CFooter:: CFooter (void) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CFooter::~CFooter (void) {}

/////////////////////////////////////////////////////////////////////////////

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

	if (__failed(sta_bar.Create(shared::Get_View().Parent(), 0xA)))
		return this->m_error = this->Get().Error();

	using namespace ex_ui::controls::sfx::status;
	using namespace ex_ui::draw::images;

	CFormat& format = sta_bar.Format(); format;  // nothing to do: status bar format default method makes the deal;
	CImages& images = sta_bar.Images(); images;

	using CPaths = ebo::sha::theme::paths::CStatus;
	CPaths paths;

	if (__failed(paths.Set())) {
		return this->m_error = paths.Error();
	}

	if (__failed(images.List().Append((_pc_sz) paths.Get(0), TImgFmt::e_png)))
		return this->m_error = images.List().Error();

	if (__failed(this->Get().Panes().Add(_T("")))) // adds the status icon pane, no text is intended for this pane;
		return this->m_error = this->Get().Panes().Error();

	CPane&  pane_0 = this->Get().Panes().Pane(0);
	if (this->Get().Panes().Error()) // actually it should not occur due to error handling above, but nevertheless;
		return this->m_error = this->Get().Panes().Error();

	pane_0.Format().Image_Ndx(0);    // it is supposed to be an image 'ready' status by default;

	ex_ui::controls::pane::CFormat& fmt_0 = pane_0.Format(); fmt_0;

	return this->Error();
}

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

#define _use_case 0

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
 	this->Tabbed().Tabs().Append(1, _T("DirectX"));
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

	n_result = this->Footer().OnCreate();

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
	n_result = this->Tabbed().Refresh();
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
#if (0)
const
CStatus&  CView::Status (void) const { return this->m_status; }
CStatus&  CView::Status (void)       { return this->m_status; }
#endif
const
CSurface& CView::Surface(void) const { return this->m_surface; }
CSurface& CView::Surface(void)       { return this->m_surface; }

const
CTabbed&  CView::Tabbed (void) const { return this->m_tabbed; }
CTabbed&  CView::Tabbed (void)       { return this->m_tabbed; }

/////////////////////////////////////////////////////////////////////////////

namespace shared {
	TView&  Get_View (void) {
		static TView main_view;
		return main_view;
	}
}