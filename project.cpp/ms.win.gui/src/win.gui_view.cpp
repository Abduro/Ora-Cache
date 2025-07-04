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

err_code CView::Draw (const HDC _h_dc, const t_rect& _drw_area) {
	_h_dc; _drw_area;
	err_code n_result = __s_ok;
#if defined(_test_case_lvl) && (_test_case_lvl == 0)
	n_result = this->Pane().Draw(_h_dc, _drw_area); // *important*: the rectangle being received is entire window client area!
#endif
#if defined(_test_case_lvl) && (_test_case_lvl >= 1)
	n_result = this->Status().Refresh();
#endif
#if defined(_test_case_lvl) && (_test_case_lvl >= 2)
	n_result = this->Tabbed().Refresh();
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