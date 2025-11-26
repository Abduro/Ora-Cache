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

namespace shared { namespace console {

	// https://learn.microsoft.com/en-us/windows/console/console-functions ;
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/format-specification-syntax-printf-and-wprintf-functions ;

	using namespace shared::defs;

	class CHandles {
	public:
		CHandles (void) = default; CHandles (const CHandles&) = delete; CHandles (CHandles&&) = delete; ~CHandles (void) = default;

		static const HANDLE Err (void);
		static const HANDLE In  (void);
		static const HANDLE Out (void);

	private:
		CHandles& operator = (const CHandles&) = delete; CHandles& operator = (CHandles&&) = delete;
	};

#define __err_handle CHandles::Err()
#define __in_handle  CHandles::In ()
#define __out_handle CHandles::Out()

}}

#endif/*_CONSOLE_DEFS_H_INCLUDED*/