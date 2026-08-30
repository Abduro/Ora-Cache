#ifndef _TEST_GUI_LAYOUT_H_INCLUDED
#define _TEST_GUI_LAYOUT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Aug-2026 at 23:25:25.402, UTC+4, Batumi, Saturday;
	This is virtual camera test desktop app main window layout interface declaration file;
*/
#include "common.defs.h"

namespace test { namespace app {

	class CLayout {
	public:
		 CLayout (void) ; CLayout (const CLayout&) = delete; CLayout (CLayout&&) = delete;
		~CLayout (void) = default;

		const
		CWindow& Window (void) const; // gets a reference to app main window handler; (ro)
		CWindow& Window (void) ;      // gets a reference to app main window handler; (rw)

		CLayout& operator <<(const HWND _h_app_wnd);

	private:
		CLayout& operator = (const CLayout&) = delete;
		CLayout& operator = (CLayout&&) = delete;

		CWindow  m_wnd; // main window handle;
	};

}}


#endif/*_TEST_GUI_LAYOUT_H_INCLUDED*/