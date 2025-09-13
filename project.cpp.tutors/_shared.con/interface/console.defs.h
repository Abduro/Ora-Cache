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
#include <stdio.h>    // https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/printf-printf-l-wprintf-wprintf-l ;
#include <iostream>

namespace shared { namespace console {

	// https://learn.microsoft.com/en-us/windows/console/console-functions ;
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/format-specification-syntax-printf-and-wprintf-functions ;

	using namespace shared::defs;
}}

#endif/*_CONSOLE_DEFS_H_INCLUDED*/