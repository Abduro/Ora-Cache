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

namespace ebo { namespace boo { namespace gui {

	using CPane    = ex_ui::controls::sfx::status::CPane;
	using CSta_bar = ex_ui::controls::sfx::status::CControl;
	using CTabbed  = ex_ui::controls::sfx::tabbed::CControl;
	using CTrkball = ex_ui::controls::sfx::track::CControl;

	using CSurface = ebo::boo::gui::render::CSurface;

	class CFooter : private shared::common::IWaitable_Events {
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
		err_code  OnDestroy (void) ;

		void  SetText(_pc_sz _p_text, const uint16_t _pane_ndx = 1);

	private:
		void IWaitable_OnComplete (void) override final;

	private:
		CFooter& operator = (const CFooter&) = delete; CFooter& operator = (CFooter&&) = delete;
		CError   m_error;
		CSta_bar m_bar  ;
		shared::common::CStdTimer m_timer;
	};

	class CTracker {
	public:
		 CTracker (void); CTracker (const CTracker&) = delete; CTracker (CTracker&&) = delete;
		~CTracker (void);

	public:
		err_code  At_1st(void);
		TError&   Error (void) const;
		const
		CTrkball& Get (void) const;
		CTrkball& Get (void) ;

		err_code  OnCreate (const HWND _h_page) ;
		err_code  OnDestroy(void) ;

	private:
		CTracker& operator = (const CTracker&) = delete; CTracker& operator = (CTracker&&) = delete;
		CError   m_error ;
		CTrkball m_tracker;
	};

	class CPages {
	static const uint16_t n_count = 2; // how many tabs will be appended to the tabbed control;
	public:
		 CPages (void); CPages (const CPages&) = delete; CPages (CPages&&) = delete;
		~CPages (void);

	public:
		err_code  At_1st(void) ;     // this is just *before* creating tabbed control window: all tabs and their pages must be formatted and added;
		TError&   Error (void) const;
		const
		CTabbed&  Get (void) const;
		CTabbed&  Get (void) ;

		bool Is_valid (void) const;  // validates each page window handle;

		err_code  OnCreate (void) ;
		err_code  OnDestroy(void) ;

	private:
		CPages& operator = (const CPages&) = delete; CPages& operator = (CPages&&) = delete;
		mutable
		CError   m_error ;
		CTabbed  m_tabbed;
		CTracker m_trackers[CPages::n_count];
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
		const
		CTracker& Tracker(void) const;
		CTracker& Tracker(void) ;

	public:
		CView& operator = (const CView&) = delete;
		CView& operator = (CView&&) = delete;

	private:
#if defined(_test_case_lvl) && (_test_case_lvl == 0)
		ex_ui::controls::sfx::CPane m_pane;
#endif
		CFooter  m_footer ;
		CPages   m_pages  ;
		CTracker m_tracker;
		CSurface m_surface;
		CWindow  m_parent ;  // this is the main window of this app;
	};

}}}

typedef ebo::boo::gui::CView TView;

namespace shared {
	TView&  Get_View (void); // all references to the target/this view are requested from main thread, that means sync access is acceptable;
}
#endif/*_WIN_GUI_VIEW_H_INCLUDED*/