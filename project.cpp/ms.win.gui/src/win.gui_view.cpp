/*
	Created by Tech_dog (ebontrop@gmail.com) on 31-May-2025 at 02:33:20.860, UTC+4, Batumi, Saturday;
	This is Ebo Pack draw renderer test app main view interface implementation file;
*/
#include "win.gui_view.h"

using namespace ebo::boo::gui;

/////////////////////////////////////////////////////////////////////////////

CView:: CView (void) {}
CView::~CView (void) {}

/////////////////////////////////////////////////////////////////////////////
#if defined(_tst_case_01) && (_tst_case_01 > 0)
const
CPane&  CView::Pane (void) const { return this->m_sta_place; }
CPane&  CView::Pane (void)       { return this->m_sta_place; }
#endif
const
CWindow& CView::Parent (void) const { return this->m_parent; }
CWindow& CView::Parent (void)       { return this->m_parent; }

/////////////////////////////////////////////////////////////////////////////

TView&  _get_view (void) {
	static TView main_view;

	return main_view;
}