#ifndef _CONSOLE_DEFS_H_INCLUDED
#define _CONSOLE_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Sep-2022 at 09:52:51.8319344, UTC+7, Novosibirsk, Friday;
	This is MS Windows console generic definition declaration file.
	-----------------------------------------------------------------------------
	The code is based on Pulsepay WWS Server Light Console class declared on 22-Dec-2013 at 12:29:53pm, GMT+4, Saint-Petersburg, Sunday;
	Adopted to File Guardian project on 6-Jan-2016 at 9:26:48am, GMT+7, Phuket, Rawai, Wednesday;
*/
#include "shared.defs.h"
#include <conio.h>
#include <stdio.h>        // https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/printf-printf-l-wprintf-wprintf-l ;
#include <iostream>
#include <consoleapi2.h>  // for CONSOLE_SCREEN_BUFFER_INFOEX;
#include <io.h>           // for _open_osfhandle ;
#include <fcntl.h>        // for constant decl, like to _O_TEXT ;

namespace shared { namespace console {

	// https://learn.microsoft.com/en-us/windows/console/console-functions ;
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/format-specification-syntax-printf-and-wprintf-functions ;

	using namespace shared::defs;

	class CAccessor {
	public:
		 CAccessor (void) = default;  CAccessor (const CAccessor&) = delete; CAccessor (CAccessor&&) = delete;
		~CAccessor (void) = default;

		/* https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getactivewindow ;
		   https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getforegroundwindow ;
		   this is for other processes or diffrenet threads:
		   https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getguithreadinfo ;
		   https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-guithreadinfo ;
		*/

		bool Is_active (void) const;  // returns 'true' in case GetActiveWindow() or GetForgroundWindow() returns handle of this console window;
		void Is_active (void) ;       // sets this console window as the foreground one;

		bool Is_visible (void) const; // gets console window visibility;
		void Is_visible (const bool); // sets console window visibility;

		HWND operator ()(void) const;
		HWND operator ()(CError&) const;

		operator HWND (void) const;

		CAccessor& operator <<(const bool _b_show_or_hide);
	};

	class CHandles {
	public:
		enum e_index : uint32_t { e_input = 0, e_output, e_error };
		static const uint32_t u_count = 3;

		 CHandles (void); CHandles (const CHandles&) = delete; CHandles (CHandles&&) = delete;
		~CHandles (void);

		void*  Get (const e_index) const;
		void   Set (void);

		void On_close (void);

	// https://learn.microsoft.com/en-us/windows/console/getstdhandle ;
	// these functions may return nullptr in case of error and the get_last_error is required for details;
		static void* Err (void);
		static void* In  (void);
		static void* Out (void);

	private:
		CHandles& operator = (const CHandles&) = delete; CHandles& operator = (CHandles&&) = delete;
		void*     m_handles[u_count]; // 0: is for std_input_handle; 1: is for std_output_handle; 2: is for std_err_handle;
	};

#define __err_handle CHandles::Err()
#define __in_handle  CHandles::In ()
#define __out_handle CHandles::Out()

}}

typedef shared::console::CAccessor TConAccess; // it may be useful for direct access to the console window handle;

#endif/*_CONSOLE_DEFS_H_INCLUDED*/