/*
	Created by Tech_dog (ebontrop@gmail.com) on 31-May-2025 at 02:33:20.860, UTC+4, Batumi, Saturday;
	This is Ebo Pack draw renderer test app main view interface implementation file;
*/
#include "win.gui_view.h"

using namespace ebo::boo::gui;

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
#define _use_case 3
#if defined(_use_case) && (_use_case == 1) // for this mode of tabs placement, a compact option must be considered too;
	this->Tabbed().Layout().Tabs().Side(TSide::e_left);
#endif
#if defined(_use_case) && (_use_case == 2) // for this mode of tabs placement, a compact option must be considered too;
	this->Tabbed().Layout().Tabs().Side(TSide::e_right);
#endif
#if defined(_use_case) && (_use_case == 3)
	this->Tabbed().Layout().Tabs().Side(TSide::e_bottom);
#endif
	this->Tabbed().Tabs().Append(1, _T("DirectX"));
#endif
}
CView::~CView (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code CView::Draw (const HDC _h_dc, const t_rect& _drw_area) {
	_h_dc; _drw_area;
	err_code n_result = __s_ok;
#if defined(_test_case_lvl) && (_test_case_lvl == 0)
	n_result = this->Pane().Draw(_h_dc, _drw_area); // *important*: the rectangle being received is entire window client area!
#endif
#if defined(_test_case_lvl) && (_test_case_lvl >= 1)
	n_result = this->Status().Refresh();
#endif
	return n_result;
}

#if defined(_test_case_lvl) && (_test_case_lvl == 0)
const
CPane&    CView::Pane (void) const { return this->m_pane; }
CPane&    CView::Pane (void)       { return this->m_pane; }
#endif
const
CWindow&  CView::Parent (void) const { return this->m_parent; }
CWindow&  CView::Parent (void)       { return this->m_parent; }

const
CStatus&  CView::Status (void) const { return this->m_status; }
CStatus&  CView::Status (void)       { return this->m_status; }
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