#ifndef _EBO_TEST_$E$_CORE_H_INCLUDED
#define _EBO_TEST_$E$_CORE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Sep-2024 at 21:41:57.411, UTC+4, Batumi, Thursday;
	This is Ebo Pack system shell extension core lib unit test interface declaration file; 
*/
#include "_log.h"

#include "sys.error.h"
#include "shared.props.h"

#include "shell.base.h"
#include "shell.menu.h"
#include "shell.props.h"

#include "shell.cmd.ln.h"

#include "shell.verb.h"

#pragma comment(lib, "sys.shared_v15.lib")   // this is the base;
#pragma comment(lib, "sys.err.core_v15.lib") // for using error object;
#pragma comment(lib, "property_v15.lib")     // this is for using shell-core library testing;
#pragma comment(lib, "shell.core_v15.lib")   // this one must be tested by this unit test project;
#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);

#endif/*_EBO_TEST_$E$_CORE_H_INCLUDED*/