#ifndef _EBO_TEST_$1$_ERR_H_INCLUDED
#define _EBO_TEST_$1$_ERR_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Aug-2024 at 01:35:22.1013935, UTC+4, Batumi, Friday;
	This is Ebo pack system error wrapper library unit test declaration file; 
*/
#include "_log.h"
#include "shared.string.h"
#include "sys.error.h"
#include "sys.seh.code.h"    // system exception record codes' enumeration;
#include "sys.seh.flag.h"    // system standard error exception flags' wrapper;
#include "sys.seh.number.h"  // system error numbers;

#pragma comment(lib, "sys.shared_v15.lib")   // is already included in shared lib ebo_test_$$$ test project;
#pragma comment(lib, "sys.err.core_v15.lib") // this one must be tested by this unit test project;

#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);

#endif/*_EBO_TEST_$1$_ERR_H_INCLUDED*/