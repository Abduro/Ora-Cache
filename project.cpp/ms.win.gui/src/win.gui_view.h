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

#include "shared.timer.h"
#include "sys.gen.time.h"

#include "ctl.status.h"
#include "ctl.tabbed.h"

namespace ebo { namespace boo { namespace gui {

	using namespace ebo::boo::gui::ctl;

	using CPane    = ex_ui::controls::sfx::status::CPane;
	using CSurface = ebo::boo::gui::render::CSurface;

	// this is the view of the main window;
	class CView {
	using CStatus = ebo::boo::gui::ctl::CStatus;
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
		CStatus&  Status (void) const;
		CStatus&  Status (void) ;

		err_code  OnCreate (void);     // it is supposed that the parent/main window handle is already set;
		err_code  OnDestroy(void);     // it suould be called from main window destroy event handler;
		err_code  OnDraw (const HDC, const t_rect& _drw_area);
		const
		CPages&   Pages (void) const;
		CPages&   Pages (void) ;
		const
		CWindow&  Parent (void) const; // this is main window handle actually; (ro)
		CWindow&  Parent (void) ;      // this is main window handle actually; (rw)

		const
		CSurface& Surface(void) const;
		CSurface& Surface(void) ;

	public:
		CView& operator = (const CView&) = delete;
		CView& operator = (CView&&) = delete;

	private:
#if defined(_test_case_lvl) && (_test_case_lvl == 0)
		ex_ui::controls::sfx::CPane m_pane;
#endif
		CStatus  m_status ;
		CPages   m_pages  ;
		CSurface m_surface;
		CWindow  m_parent ;  // this is the main window of this app;
	};

}}}

typedef ebo::boo::gui::CView TView;

namespace shared {
	TView&  Get_View (void); // all references to the target/this view are requested from main thread, that means sync access is acceptable;
}
#endif/*_WIN_GUI_VIEW_H_INCLUDED*/