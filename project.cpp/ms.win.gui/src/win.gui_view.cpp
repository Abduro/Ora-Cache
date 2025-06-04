/*
	Created by Tech_dog (ebontrop@gmail.com) on 31-May-2025 at 02:33:20.860, UTC+4, Batumi, Saturday;
	This is Ebo Pack draw renderer test app main view interface implementation file;
*/
#include "win.gui_view.h"

using namespace ebo::boo::gui;

/////////////////////////////////////////////////////////////////////////////

CView:: CView (void) {
#if defined(_tst_case_01) && (_tst_case_01 > 0)
	this->Pane().Borders().Top().Thickness(1);
	this->Pane().Borders().Top().Color() << shared::Get_Theme().Get(TThemePart::e_panel, TThemeElement::e_border);

	this->Pane().Format().Bkgnd() << shared::Get_Theme().Get(TThemePart::e_form, TThemeElement::e_back);
#endif
}
CView::~CView (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code CView::Draw (const HDC _h_dc, const t_rect& _drw_area) const {
	_h_dc; _drw_area;
	err_code n_result = __s_ok;

	n_result = this->Pane().Draw(_h_dc, _drw_area); // *important*: the rectangle being received is entire window client area!

	return n_result;
}

#if defined(_tst_case_01) && (_tst_case_01 > 0)
const
CPane&   CView::Pane (void) const { return this->m_pane; }
CPane&   CView::Pane (void)       { return this->m_pane; }
#endif
const
CWindow& CView::Parent (void) const { return this->m_parent; }
CWindow& CView::Parent (void)       { return this->m_parent; }

/////////////////////////////////////////////////////////////////////////////

namespace shared {
	TView&  Get_View (void) {
		static TView main_view;
		return main_view;
	}
}