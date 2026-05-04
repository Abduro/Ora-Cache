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

	// query: who to prevent allocated console window from resizing programmatically winapi c++ ;
	// https://stackoverflow.com/questions/47358043/can-i-prevent-the-user-of-my-program-to-resize-the-console-window-in-c ;

	/* windows events' hook:
	   https://learn.microsoft.com/en-us/windows/win32/winauto/registering-a-hook-function ;
	   https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwineventhook ;
	   https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-unhookwinevent ;
	   https://learn.microsoft.com/en-us/windows/win32/api/winuser/nc-winuser-wineventproc ;
	*/
	/* IAccessible for accessing methods and properties of the interface that cought by windows event hook; (oleacc.h)
	   https://learn.microsoft.com/en-us/windows/win32/api/oleacc/nn-oleacc-iaccessible ;s
	   https://learn.microsoft.com/en-us/windows/win32/api/oleacc/nf-oleacc-accessibleobjectfromevent ;
	   https://learn.microsoft.com/en-us/windows/win32/api/oleacc/nf-oleacc-accessibleobjectfrompoint ;
	   https://learn.microsoft.com/en-us/windows/win32/api/oleacc/nf-oleacc-accessibleobjectfromwindow ;
	*/
	class CLayout {
	public:
		 CLayout (void); CLayout (const CLayout&) = delete; CLayout (CLayout&&) = delete;
		~CLayout (void) = default;

		err_code Adjust_Pos (const bool _b_activate);   // instead of being a child window, this procedure glues the console window to one of the sides of the main app window;
		err_code Adjust_Pos (const t_rect& _rc_parent); // for gluing to the main window side, the rect is required, it was made for Windows Vista, but still be kept for history ;)
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