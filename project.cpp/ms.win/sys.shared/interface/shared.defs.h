#ifndef _SHARED_DEFS_H_INCLUDED
#define _SHARED_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Aug-2026 at 11:04:10.893, UTC+4, Batumi, Friday;
	This is shared library common declaration file;
*/
#include <atlbase.h>    // https://learn.microsoft.com/en-us/cpp/atl/reference/atl-classes ;
#include <atltrace.h>   // used in shared debug classes;
#pragma region __shared_str_ext
#include <atlstr.h>
#include <strsafe.h>    // ::StringCchVPrintfEx();
#include <stdlib.h>     // ::_ltoa_s; _tstol;

#include <cstdio>       // std::printf; https://en.cppreference.com/w/cpp/io/c/fprintf
#include <string>       // std::stoi, std::stol, std::stoll; https://en.cppreference.com/w/cpp/string/basic_string/stol ;
#include <vector>

#include <combaseapi.h> // CLSIDFromString(); https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-clsidfromstring ;
                        // StringFromGUID2(); https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-stringfromguid2 ;
#pragma endregion
#pragma region __shared_str_var
#include <comutil.h>    // _variant_t;
#include <wtypes.h>     // VARTYPE enum; https://learn.microsoft.com/en-us/windows/win32/api/wtypes/ne-wtypes-varenum ;
#pragma endregion
#pragma region __shared_random
#include <guiddef.h>
#include <limits>
namespace std {
#include <time.h>
}
#pragma endregion
#pragma region __shared_types
#include <tchar.h>
#include <cstdint>
#pragma endregion
#include <stdint.h>

#endif/*_SHARED_DEFS_H_INCLUDED*/