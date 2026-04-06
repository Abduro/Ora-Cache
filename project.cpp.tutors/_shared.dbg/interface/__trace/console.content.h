#ifndef _CONSOLE_CONTENT_H_INCLUDED
#define _CONSOLE_CONTENT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Mar-2026 at 09:31:24.523, UTC+4, Batumi, Sunday;
	This is Ebo Pack console content wrapper interface declaration file;
*/
#include "console.defs.h"
#include "console.mode.h"

namespace shared { namespace console { namespace content { using namespace shared::console;
	/* query: to what part of the GUI can belong the the shortcut menu to window or to content of window;
	   A shortcut menu (or context menu) in a Graphical User Interface (GUI) can belong to both the window structure and the content of the window,
	   depending on where the user interacts.
	*/
	// https://learn.microsoft.com/en-us/windows/win32/uxguide/cmd-menus ;
	class CCtxMenu { // this is shortcut menu of the console window, or context menu in other words;
	public:
		 CCtxMenu (void); CCtxMenu (const CCtxMenu&) = delete; CCtxMenu (CCtxMenu&&) = delete;
		~CCtxMenu (void) = default;

		err_code Enable (const bool _b_state);
		TError&  Error (void) const;

	private:
		CCtxMenu& operator = (const CCtxMenu&) = delete; CCtxMenu& operator = (CCtxMenu&&) = delete;
		mutable
		CError  m_error;
	};
}}}

#endif/*_CONSOLE_CONTENT_H_INCLUDED*/