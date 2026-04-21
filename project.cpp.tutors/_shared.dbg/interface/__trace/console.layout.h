#ifndef _CONSOLE_LAYOUT_H_INCLUDED
#define _CONSOLE_LAYOUT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Mar-2026 at 16:06:20.186, UTC+4, Batumi, Saturday;
	This is system console window and content layout wrapper interface declaration file;
*/
#include "console.defs.h"
#include "console.buffer.h"
#include "console.pers.h"

namespace shared { namespace console {
namespace layout { using namespace shared::console;

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
	struct s_create_data {
		HWND m_parent;
		RECT m_rect;
		bool m_visible;

		s_create_data (const HWND = nullptr, const RECT& = {0}, const bool _b_visible = true);
		CString To_str (void) const;
	};

	class CLayout {
	public:
		 CLayout (void); CLayout (const CLayout&) = delete; CLayout (CLayout&&) = delete;
		~CLayout (void) = default;

		err_code As_child (const s_create_data&); // sets console window as a child window;

		TError&  Error (void) const;
		err_code OnClose  (void);                 // saves the position of the console window;
		err_code OnCreate (void);                 // sets console window position stored in the registry;
		err_code OnCreate (const s_create_data&); // sets console window position in accordance with its pin state on console window create event;

	private:
		CLayout& operator = (const CLayout&) = delete; CLayout& operator = (CLayout&&) = delete;
		CError m_error;
	};
}}

#endif/*_CONSOLE_LAYOUT_H_INCLUDED*/