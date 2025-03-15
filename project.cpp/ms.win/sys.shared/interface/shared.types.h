#ifndef _SHARED_TYPFS_H_INCLUDED
#define _SHARED_TYPES_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 5-Feb-2025 at 11:24:55.955, UTC+4, Batumi, Wednesday;
	This Ebo Pack shared data types declaration file;
*/
#include <atlbase.h>
#include <atlstr.h>
#include <tchar.h>

namespace shared { namespace types {

	// these data types and structures are based on WinAPI, because the current implementation of Ebo Pack is intended for running under Windows OS;

	typedef LPCTSTR _pc_sz; // since Win32 there is neither 'long' nor 'near' pointer types;
	typedef LPTSTR  _p_sz ;
	typedef TCHAR  t_char ;

	typedef _GUID   _guid ;
	typedef USHORT  ushort;
	typedef ULONG   ulong ;
	typedef DWORD   dword ;

	typedef BOOL _bool ;
	typedef LONG _long ;
	typedef UINT _uint ;
	typedef WORD _word ;

	// https://en.wikipedia.org/wiki/err_code ;
	typedef HRESULT err_code;
	// for using in shared.mem project;
	typedef HGLOBAL global;
	typedef HANDLE  handle;
	// for using in win.popup projects;
	typedef LRESULT l_result;
	typedef WPARAM  w_param ;
	typedef LPARAM  l_param ;
	// for using in geometry and window projects;
	typedef POINT   t_point ; // it just is a base structure for holding point coordinate values;
	typedef RECT    t_rect  ;
	typedef SIZE    t_size  ; // it just is a base structure for holding shape size in two dimensional space;
}}


#endif/*_SHARED_TYPES_H_INCLUDED*/