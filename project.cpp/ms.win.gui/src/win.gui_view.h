#ifndef _WIN_GUI_VIEW_H_INCLUDED
#define _WIN_GUI_VIEW_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 31-May-2025 at 02:33:20.860, UTC+4, Batumi, Saturday;
	This is Ebo Pack draw renderer test app main view interface declaration file;
*/
#include "win.gui.inc.h"
#include "win.gui_layout.h"

#include "direct_x.surface.h"
#include "direct_x.wrap.h"

#include "ebo.sha.gui.theme.h"

namespace ebo { namespace boo { namespace gui {

	using namespace ebo::sha::theme;

	using CPane = ex_ui::controls::CPane;    // this is the pane control class that is not windowed yet;
	using CStatus = ex_ui::controls::sfx::status::CControl;
	using CSurface = ebo::boo::gui::render::CSurface;

	// this is the view of the main window;
	class CView {
	public:
		 CView (void) ; CView (const CView&) = delete; CView (CView&&) = delete;
		~CView (void) ;

	public:

		err_code  Draw (const HDC, const t_rect& _drw_area) const;

#if defined(_test_case_lvl) && (_test_case_lvl == 0)
		const
		CPane&    Pane (void) const;
		CPane&    Pane (void) ;
#endif
		const
		CWindow&  Parent (void) const;
		CWindow&  Parent (void) ;
		const
		CStatus&  Status (void) const;
		CStatus&  Status (void) ;
		const
		CSurface& Surface(void) const;
		CSurface& Surface(void) ;

	public:
		CView& operator = (const CView&) = delete;
		CView& operator = (CView&&) = delete;

	private:
#if defined(_test_case_lvl) && (_test_case_lvl == 0)
		CPane   m_pane;
#endif
		CWindow  m_parent ;  // this is the main window of this app;
		CSurface m_surface;
		CStatus  m_status ;
	};

}}}

typedef ebo::boo::gui::CView TView;

namespace shared {
	TView&  Get_View (void);
}
#endif/*_WIN_GUI_VIEW_H_INCLUDED*/