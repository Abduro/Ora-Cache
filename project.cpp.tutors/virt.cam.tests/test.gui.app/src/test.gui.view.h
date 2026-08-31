#ifndef _TEST_GUI_VIEW_H_INCLUDED
#define _TEST_GUI_VIEW_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Aug-2026 at 23:22:37.701, UTC+4, Batumi, Saturday;
	This is virtual camera test desktop app main window view interface declaration file;
*/
#include "test.gui.defs.h"
#include "sfx.tabs.ctrl.h"

namespace test { namespace app { using namespace ::test::draw::defs;

	using CTabbed  = ex_ui::controls::sfx::tabbed::CControl;

	class CPages {
	public:
		 CPages (void); CPages (const CPages&) = delete; CPages (CPages&&) = delete;
		~CPages (void);

		err_code  At_1st(void) ;      // this is just *before* creating tabbed control window: all tabs and their pages must be formatted and added;
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
		CError  m_error;
		CTabbed m_tabs;
	};

	class CView {
	public:
		CView (void); CView (const CView&) = delete; CView (CView&&) = delete; ~CView (void) = default;

		err_code  OnCreate (void);     // it is supposed that the parent/main window handle is already set;
		err_code  OnDestroy(void);     // it suould be called from main window destroy event handler;
		err_code  OnDraw (const HDC, const rect_t& _drw_area);
		const
		CPages&   Pages (void) const;
		CPages&   Pages (void) ;
		const
		CWindow&  Parent (void) const; // this is main window handle actually; (ro)
		CWindow&  Parent (void) ;      // this is main window handle actually; (rw)

		CView& operator <<(const HWND _h_app_wnd);

	private:
		CView& operator = (const CView&) = delete; CView& operator = (CView&&) = delete;
		CPages   m_pages;
		CWindow  m_parent;  // this is the main window handle wrapper of this app;
	};

}}

typedef ::test::app::CView TView;

namespace shared {
	TView&  Get_View (void); // all references to the target/this view are requested from main thread, that means sync access is acceptable;
}

#endif/*_TEST_GUI_VIEW_H_INCLUDED*/