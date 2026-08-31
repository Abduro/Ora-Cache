#ifndef _TEST_GUI_LAYOUT_H_INCLUDED
#define _TEST_GUI_LAYOUT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 29-Aug-2026 at 23:25:25.402, UTC+4, Batumi, Saturday;
	This is virtual camera test desktop app main window layout interface declaration file;
*/
#include "test.gui.defs.h"

namespace test { namespace app {

	class CLayout {
	public:
		 CLayout (void) ; CLayout (const CLayout&) = delete; CLayout (CLayout&&) = delete;
		~CLayout (void) = default;
		const
		rect_t&   DrawArea (void) ;       // const is temporarilly removed due to this::Update() sets or changes value of the draw area;
		TError&   Error    (void) const;
		bool      Is_valid (void) const;  // checks the main window validity;
		const
		CPadding& Padding (void) const;
		CPadding& Padding (void) ;

		err_code  Update (void) ;         // gets main window client area rectangle and calls this::Update(rect);
		err_code  Update (const rect_t&); // recalculates the main view layout; the client rect can be provided on window sizing event;
		const
		CWindow&  Window (void) const;    // gets a reference to app main window handler; (ro)
		CWindow&  Window (void) ;         // gets a reference to app main window handler; (rw)

		CLayout&  operator <<(const HWND _h_app_wnd);

	private:
		CLayout&  operator = (const CLayout&) = delete;
		CLayout&  operator = (CLayout&&) = delete;
		mutable
		CError    m_error;
		rect_t    m_draw_area; // main window draw area rectangle; the padding is already applied;
		CPadding  m_padding;   // main window client rectangle draw area padding;
		CWindow   m_wnd;       // main window handle;
	};
}}

typedef ::test::app::CLayout TLayout;

namespace shared {
	TLayout&  Get_Layout (void);
}


#endif/*_TEST_GUI_LAYOUT_H_INCLUDED*/