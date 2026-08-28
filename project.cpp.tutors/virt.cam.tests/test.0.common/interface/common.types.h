#ifndef _COMMON_TYPFS_H_INCLUDED
#define _COMMON_TYPES_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Aug-2026 at 12:25:11.300, UTC+4, Batumi, Wednesday;
	This is virtual camera test cases' commom data types declaration file;
*/
#include <atlbase.h>      // https://learn.microsoft.com/en-us/cpp/atl/reference/atl-classes ;
#include <atlwin.h>       // https://learn.microsoft.com/en-us/cpp/atl/reference/cwindow-class ;
#include <atlstr.h>       // https://learn.microsoft.com/en-us/cpp/atl-mfc-shared/reference/cstringt-class ;
#include <cstdint>
#include <tchar.h>

namespace test { namespace data { namespace types {

	// these data types and structures are based on WinAPI, because the current implementation of Ebo Pack is intended for running under Windows OS;
	// https://learn.microsoft.com/en-us/cpp/cpp/data-type-ranges ;

	typedef BOOL    bool_t  ;   // https://learn.microsoft.com/en-us/windows/win32/winprog/windows-data-types  ;
	typedef _GUID   guid_t  ;   // https://learn.microsoft.com/en-us/windows/win32/api/guiddef/ns-guiddef-guid ;
	typedef HRESULT err_code;   // https://en.wikipedia.org/wiki/err_code ;
	typedef DWORD   dword_t ;   // https://learn.microsoft.com/en-us/windows/win32/winprog/windows-data-types  ;
	typedef LONG    long_t  ;

#pragma region wnd_message_handle   // https://stackoverflow.com/questions/2515261/what-are-the-definitions-for-lparam-and-wparam ;
	typedef LPARAM  l_param ;   // a long (signed 32-bit) on win32 and __int64 (signed 64-bit) on x86_64;
	typedef LRESULT l_result;   // a long (signed 32-bit) on win32 and __int64 (signed 64-bit) on x86_64;
	typedef WPARAM  w_param ;   // unsigned int (unsigned 32-bit) on win32 and unsigned __int64 (unsigned 64-bit) on x86_64;
#pragma endregion
}}}

#endif/*_COMMON_TYPES_H_INCLUDED*/