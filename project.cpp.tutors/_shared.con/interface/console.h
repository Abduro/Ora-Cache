#ifndef _OUT_H_INCLUDED
#define _OUT_H_INCLUDED
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

namespace shared { namespace console {

	// https://learn.microsoft.com/en-us/windows/console/creation-of-a-console ;
	// https://learn.microsoft.com/en-us/windows/console/allocconsole ;
	// the excerpt from the above article: this function is primarily used by a graphical user interface (GUI) application to create a console window...;
  
	class CConsole {
	public:
		 CConsole (void); CConsole (const CConsole&) = delete; CConsole (CConsole&&) = delete;
		~CConsole (void);

		 err_code Close (void); // closes all IO handles; ::FreeConsole() is not used because there is no call to ::AttachConsole() was made before;
		 err_code Open  (const HWND _h_parent, const t_rect&, const bool _b_visible); // creates *new* console, inserts it as a chiled window to the parent one;

		 TError&  Error  (void) const;
		 HWND     Handle (void) const;
		 bool  Is_valid  (void) const; // checks validity of the console window handle;
		 
		 operator const HWND (void) const;

	private:
		 CConsole& operator = (const CConsole&) = delete; CConsole& operator = (CConsole&&) = delete;
		 mutable
		 CError    m_error;
		 HWND      m_con_wnd;
		 FILE*     m_streams[3]; // 0: is for std_input_handle; 1: is for std_output_handle; 2: is for std_err_handle;
	};

}}

typedef shared::console::CConsole out_;

/////////////////////////////////////////////////////////////////////////////

static out_ _out;

#endif/*_OUT_H_INCLUDED*/