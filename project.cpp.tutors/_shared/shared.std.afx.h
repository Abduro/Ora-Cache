#ifndef _SHARED_STD_AFX_H_INCLUDED
#define _SHARED_STD_AFX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Nov-2025 at 17:51:10.555, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpendGL tutorials' shared precompiled header include file;
	-----------------------------------------------------------------------------
	This file is not included explicitly to cpp files because the following project option is set:
	C/C++ >> Advanced >> Forced Include Files = shared._std_afx.h;%(ForcedIncludeFiles) ;
*/
#ifndef _WIN32_WINNT          // specifies that the minimum required platform is MS Windows 10;
#define _WIN32_WINNT   0x0A00
#endif

#ifndef WINVER
#define WINVER   _WIN32_WINNT
#endif

#ifndef STRICT
#define STRICT
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#pragma warning(disable: 4481)  // nonstandard extension used: override specifier 'override';
#pragma warning(disable: 4996)  // security warning: function or variable may be unsafe;

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE

#include "shared.defs.h"

#ifdef _DEBUG
	#define _ATL_DEBUG_INTERFACES
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <Sddl.h> // https://learn.microsoft.com/en-us/windows/win32/api/sddl/ ; security and identity in MS Windows operating system;

#endif/*_SHARED_STD_AFX_H_INCLUDED*/