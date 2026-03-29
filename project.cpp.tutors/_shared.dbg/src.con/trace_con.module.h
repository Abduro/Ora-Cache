#ifndef _TRACE_CON_MODULE_H_INCLUDED
#define _TRACE_CON_MODULE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Mar-2026 at 13:18:10.358, UTC+4, Batumi, Tuesday;
	This is Ebo Pack tutorials' shared debug trace console entry point declaration file;
*/
#include "shared.defs.h"
#include <iostream>

#ifdef _UNICODE
#define in_t  ::std::wcin
#define out_t ::std::wcout
#else
#define in_t  ::std::cin
#define out_t ::std::cout
#endif

#pragma comment(lib, "shared.dbg_v15.lib")    // shared debug outpu/trace console;
#pragma comment(lib, "shared.gui_v15.lib")    // shared GUI lib for creating main/app window;
#pragma comment(lib, "shared.trim_v15.lib")   // shared wrappers of required system functionality;

#endif/*_TRACE_CON_MODULE_H_INCLUDED*/