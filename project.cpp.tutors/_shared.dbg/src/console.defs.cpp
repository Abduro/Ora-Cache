/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Sep-2022 at 10:08:55.9180723, UTC+7, Novosibirsk, Friday;
	This is MS Windows console generic definition implementation file.
	-----------------------------------------------------------------------------
	The code is based on Pulsepay WWS Server Light Console class declared on 22-Dec-2013 at 12:49:13pm, GMT+4, Saint-Petersburg, Sunday;
*/
#include "console.defs.h"

using namespace shared::console;

namespace shared { namespace console { namespace _impl { void __warning_lnk_4221 (void) {}}}}

const HANDLE CHandles::Err (void) { return ::GetStdHandle(STD_ERROR_HANDLE);  }
const HANDLE CHandles::In  (void) { return ::GetStdHandle(STD_INPUT_HANDLE);  }
const HANDLE CHandles::Out (void) { return ::GetStdHandle(STD_OUTPUT_HANDLE); }