#ifndef _TEST_GUI_VIEW_H_INCLUDED
#define _TEST_GUI_VIEW_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Aug-2026 at 23:22:37.701, UTC+4, Batumi, Saturday;
	This is virtual camera test desktop app main window view interface declaration file;
*/
#include "common.defs.h"
#include "sfx.tabs.ctrl.h"

namespace test { namespace app { using namespace ::test::draw::defs;

	using CTabbed  = ex_ui::controls::sfx::tabbed::CControl;

	class CView {
	public:
		CView (void); CView (const CView&) = delete; CView (CView&&) = delete; ~CView (void) = default;
	private:
		CView& operator = (const CView&) = delete; CView& operator = (CView&&) = delete;
		CTabbed m_tabs;
	};

}}

#endif/*_TEST_GUI_VIEW_H_INCLUDED*/