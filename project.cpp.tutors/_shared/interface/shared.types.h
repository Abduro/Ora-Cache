#ifndef _SHARED_TYPFS_H_INCLUDED
#define _SHARED_TYPES_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 5-Feb-2025 at 11:24:55.955, UTC+4, Batumi, Wednesday;
	This Ebo Pack shared data types declaration file;
*/
#include <atlbase.h>
#include <atlstr.h>
#include <tchar.h>
#include <cstdint>

namespace shared { namespace types {

#if defined(_DEBUG_)    // leads to error C2011: 'shared::types::e_print': 'unsigned enum' type redefinition ;
	// https://en.cppreference.com/w/cpp/language/enum ;
	enum class e_print : uint32_t {
		e_all   = 0x0,  // prints out the class name and namespace path, class field value(s);
		e_no_ns = 0x1,  // prints out as the option above, but no namespace path;
		e_req   = 0x2   // prints out the class object field value(s) only;
	};
	CString e_print_to_str (void);
#endif
#if (1)
	// these data types and structures are based on WinAPI, because the current implementation of Ebo Pack is intended for running under Windows OS;
	// https://learn.microsoft.com/en-us/cpp/cpp/data-type-ranges ;

	typedef _GUID     _guid ;   // https://learn.microsoft.com/en-us/windows/win32/api/guiddef/ns-guiddef-guid ;
	typedef BOOL      _bool ;   // https://learn.microsoft.com/en-us/windows/win32/winprog/windows-data-types  ;
	typedef BYTE      _byte ;
	typedef DWORD     dword ;   // https://learn.microsoft.com/en-us/windows/win32/winprog/windows-data-types  ;
	typedef HANDLE    handle;   // for using in shared.mem project;
	typedef HGLOBAL   global;   // for using in shared.mem project;
	typedef HRESULT err_code;   // https://en.wikipedia.org/wiki/err_code ;
	typedef LONG      _long ;
	typedef LPARAM  l_param ;   // for using in win.popup projects;
	typedef LPCTSTR   _pc_sz;   // since Win32 there is neither 'long' nor 'near' pointer types;
	typedef LPTSTR    _p_sz ;
	typedef LRESULT l_result;   // for using in win.popup projects;
	typedef POINT   t_point ;   // it just is a base structure for holding point coordinate values;
	typedef RECT    t_rect  ;   // for using in geometry and window projects;
	typedef SIZE    t_size  ;   // it just is a base structure for holding shape size in two dimensional space;
	typedef TCHAR    t_char ;   // https://learn.microsoft.com/en-us/office/client-developer/outlook/mapi/tchar ;
	typedef UINT      _uint ;
	typedef ULONG     ulong ;
	typedef USHORT    ushort;
	typedef WORD      _word ;
	typedef WPARAM  w_param ;   // for using in win.popup projects;

#endif
}}


#endif/*_SHARED_TYPES_H_INCLUDED*/