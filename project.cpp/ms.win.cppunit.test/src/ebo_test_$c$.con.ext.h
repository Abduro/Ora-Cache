#ifndef _EBO_TEST_$C$_CON_EXT_H_INCLUDED
#define _EBO_TEST_$C$_CON_EXT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Sep-2024 at 21:41:57.411, UTC+4, Batumi, Thursday;
	This is Ebo Pack console extension lib unit test interface declaration file; 
*/
#include "_log.h"

#include "sys.error.h"

#include "console.event.h"
#include "console.font.h"
#include "console.notify.h"

#pragma comment(lib, "sys.err.core_v15.lib") // for using error object;
#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);
#pragma comment(lib, "console.ext_v15.lib")  // this is the target being tested;

#endif/*_EBO_TEST_$C$_CON_EXT_H_INCLUDED*/