#ifndef _EBO_TEST_$2$_MEM_H_INCLUDED
#define _EBO_TEST_$2$_MEM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Aug-2024 at 10:58:32.7913639, UTC+4, Batumi, Wednesday;
	This is Ebo Pack shared lib memory management base interface declaration file; 
*/
#include "_log.h"
#include "shared.string.h"
#include "sys.error.h"

#include "sys.mem.global.h"
#include "sys.mem.handle.h"
#include "sys.mem.heap.h"

#pragma comment(lib, "sys.shared_v15.lib")   // is already included in shared lib ebo_test_$$$ test project;
#pragma comment(lib, "sys.err.core_v15.lib") // system error handling wrapper lib;
#pragma comment(lib, "sys.mem.core_v15.lib") // this one must be tested by this unit test project;

#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);

#endif/*_EBO_TEST_$2$_MEM_H_INCLUDED*/