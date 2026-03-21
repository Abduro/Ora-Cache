#ifndef _CONSOLE_H_INCLUDED
#define _CONSOLE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-Sep-2020 at 6:54:34p, UTC+7, Novosibirsk, Thursday;
	This is FakeGPS driver version 2 desktop client console interface declaration file;
	-----------------------------------------------------------------------------
	Adopted to Wanderer Path Finder project on 6-Jan-2021 at 11:42:05.633 am, UTC+7, Novosibirsk, Tuesday;
	Adopted to Yandex Wanderer project on 11-Dec-2022 at 07:38:02.6575746, UTC+7, Novosibirsk, Sunday;
	-----------------------------------------------------------------------------
	This code is the excerpt from console project of Ebo_Pack package static library code;
*/
#include "console.defs.h"
#include "console.layout.h"

namespace shared { namespace console {
	/* query: how to create console process with hidden window winapi (Google AI):
	   To create a console process with a hidden window using the Win32 API,
	   the most effective method is using the CreateProcess function with specific flags;
	(1) Using CREATE_NO_WINDOW flag: no console window is created for a process. This avoids the "flicker" of a window appearing and then disappearing;
	(2) Using STARTUPINFO with SW_HIDE: { dwFlags = STARTF_USESHOWWINDOW; wShowWindow = SW_HIDE; }
	*/
	class CWrap {
	public:
		 CWrap (void); CWrap (const CWrap&) = delete; CWrap (CWrap&&) = delete;
		~CWrap (void);

		err_code Create (const bool _b_visible); // creates the console process through CreateProcess() procs;
		TError&  Error (void) const;

	private:
		CWrap& operator = (const CWrap&) = delete; CWrap& operator = (CWrap&&) = delete;
		CError m_error;
		void*  m_hwnd ;  // console window handle; winnt.h: typedef void* HANDLE;
	};

	/* query: to what part of the GUI can belong the the shortcut menu to window or to content of window;
	   A shortcut menu (or context menu) in a Graphical User Interface (GUI) can belong to both the window structure and the content of the window,
	   depending on where the user interacts.
	*/
	// https://learn.microsoft.com/en-us/windows/win32/uxguide/cmd-menus ;
	class CCtxMenu { // this is context menu of the console window, or context menu in other words;
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

	// https://learn.microsoft.com/en-us/windows/console/creation-of-a-console ;
	// https://learn.microsoft.com/en-us/windows/console/allocconsole ;
	// the excerpt from the above article: this function is primarily used by a graphical user interface (GUI) application to create a console window...;

	class CConsole {	
	public:
		 CConsole (void); CConsole (const CConsole&) = delete; CConsole (CConsole&&) = delete;
		~CConsole (void);

		 err_code Close (void); // closes all IO handles; ::FreeConsole() is not used because there is no call to ::AttachConsole() was made before;
		 err_code Open  (const HWND _h_parent, const t_rect&, const bool _b_visible); // creates *new* console, inserts it as a child window to the parent one;

		 TError&  Error  (void) const;	
		 HWND     Handle (void) const; // returns console window handle;
		 bool  Is_valid  (void) const; // checks validity of the console window handle;

		 void*   Get_err (void) const; // gets std::error handle;
		 void*   Get_in  (void) const; // gets std::input handle;
		 void*   Get_out (void) const; // gets std::output handle;
		 
		 operator const HWND (void) const;

	private:
		 CConsole& operator = (const CConsole&) = delete; CConsole& operator = (CConsole&&) = delete;
		 mutable
		 CError    m_error;
		 HWND      m_con_wnd;
	};
}}

typedef shared::console::CConsole out_; static out_ _con;

#endif/*_CONSOLE_H_INCLUDED*/