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

namespace ebo { namespace boo { namespace gui {

	using CPane    = ex_ui::controls::sfx::status::CPane;
	using CSta_bar = ex_ui::controls::sfx::status::CControl;
	using CTabbed  = ex_ui::controls::sfx::tabbed::CControl;

	using CSurface = ebo::boo::gui::render::CSurface;

	class CFooter {
	public:
		 CFooter (void); CFooter (const CFooter&) = delete; CFooter (CFooter&&) = delete;
		~CFooter (void);

	public:
		err_code  At_1st(void) ;     // this is just *before* creating status bar control window: all sections/panes must be defined;
		TError&   Error (void) const;
		const
		CSta_bar& Get (void) const;
		CSta_bar& Get (void) ;

		err_code  OnCreate  (void) ; // this method must be called from main window on 'create' event handler; *status bar* must be ready;

		void  SetText(_pc_sz _p_text, const uint16_t _pane_ndx = 1);

	private:
		CFooter& operator = (const CFooter&) = delete; CFooter& operator = (CFooter&&) = delete;
		CError   m_error;
		CSta_bar m_bar;
	};

	// this is the view of the main window;
	class CView {
	public:
		 CView (void) ; CView (const CView&) = delete; CView (CView&&) = delete;
		~CView (void) ;

	public:

#if defined(_test_case_lvl) && (_test_case_lvl == 0)
		const
		ex_ui::controls::sfx::CPane&    Pane (void) const;
		ex_ui::controls::sfx::CPane&    Pane (void) ;
#endif
		const
		CFooter&  Footer (void) const;
		CFooter&  Footer (void) ;

		err_code  OnCreate (void);     // it is supposed that the parent/main window handle is already set;  
		err_code  OnDraw (const HDC, const t_rect& _drw_area);

		const
		CWindow&  Parent (void) const; // this is main window handle actually; (ro)
		CWindow&  Parent (void) ;      // this is main window handle actually; (rw)
#if (0)
		const
		CStatus&  Status (void) const;
		CStatus&  Status (void) ;
#endif
		const
		CSurface& Surface(void) const;
		CSurface& Surface(void) ;

		const
		CTabbed&  Tabbed (void) const;
		CTabbed&  Tabbed (void) ;

	public:
		CView& operator = (const CView&) = delete;
		CView& operator = (CView&&) = delete;

	private:
#if defined(_test_case_lvl) && (_test_case_lvl == 0)
		ex_ui::controls::sfx::CPane m_pane;
#endif
		CFooter  m_footer ;
		CWindow  m_parent ;  // this is the main window of this app;
		CSurface m_surface;
#if (0)
		CStatus  m_status ;
#endif
		CTabbed  m_tabbed ;
	};

}}}

typedef ebo::boo::gui::CView TView;

namespace shared {
	TView&  Get_View (void); // all references to the target/this view are requested from main thread, that means sync access is acceptable;
}
#endif/*_WIN_GUI_VIEW_H_INCLUDED*/