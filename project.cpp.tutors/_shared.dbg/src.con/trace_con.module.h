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

#endif/*_TRACE_CON_MODULE_H_INCLUDED*/