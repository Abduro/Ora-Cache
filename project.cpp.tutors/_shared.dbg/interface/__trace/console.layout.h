#ifndef _CONSOLE_LAYOUT_H_INCLUDED
#define _CONSOLE_LAYOUT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Mar-2026 at 16:06:20.186, UTC+4, Batumi, Saturday;
	This is system console window and content layout wrapper interface declaration file;
*/
#include "console.defs.h"
#include "console.buffer.h"

namespace shared { namespace console { namespace layout { using namespace shared::console;

	class CHScroll {
	public:
		 CHScroll (void); CHScroll (const CHScroll&) = delete; CHScroll (CHScroll&&) = delete;
		~CHScroll (void) = default;

		TError&  Error (void) const;

		// https://stackoverflow.com/questions/50264637/add-horizontal-scroll-bar-to-console ;

		bool     Get (void) const;        // checks a horizontal scroll bar existance within screen buffer of the console;
		err_code Set (const bool _b_set); // adds/removes a horizontal scroll bar to/from screen buffer of the console;

	private:
		CHScroll& operator = (const CHScroll&&) = delete; CHScroll& operator = (CHScroll&&) = delete;
		CError m_error;
	};
}
	class CLayout {
	public:
		 CLayout (void); CLayout (const CLayout&) = delete; CLayout (CLayout&&) = delete;
		~CLayout (void) = default;

		err_code As_child (const HWND _h_parent, const t_rect&, const bool _b_visible); // sets console window as a child window of the main window of the app;

		TError&  Error (void) const;

	private:
		CLayout& operator = (const CLayout&) = delete; CLayout& operator = (CLayout&&) = delete;
		CError m_error;
	};
}}

#endif/*_CONSOLE_LAYOUT_H_INCLUDED*/