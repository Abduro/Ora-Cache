// https://www.allacronyms.com/common/abbreviated;
#ifndef _COM_STD_SFX_H_INCLUDED
#define _COM_STD_SFX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-Aug-2026 at 18:04:13.557, UTC+4, Batumi, Thursday;
	This is virtual camera test projects' common precompiled header include file;
	-----------------------------------------------------------------------------
	This file is not included explicitly to cpp files because the following project option is set:
	C/C++ >> Advanced >> Forced Include Files = shared._std_afx.h;%(ForcedIncludeFiles) ;
*/
#ifndef _WIN32_WINNT            // specifies that the minimum required platform is MS Windows 10;
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

#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

#endif/*_COM_STD_SFX_H_INCLUDED*/