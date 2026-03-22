#ifndef _EBO_TEST_$W$_DEFS_H_INCLUDED
#define _EBO_TEST_$W$_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Mar-2026 at 20:29:37.726, UTC+4, Batumi, Sunday;
	Ebo Pack OpenGL tutorials' WinApi related projects' uint test interface declaration file;
*/
#include "_log.h"
#include "shared.dbg.h"
#include "shared.preproc.h"

namespace ebo { namespace boo { namespace test { namespace win_api {
	using namespace ebo::boo::test;

	/**important*: the main rules of error trace:
	(1) if a test case object throws the error, it should trace it itself;
	(2) if an error occurs outside the object, it must be tracked by that object, otherwise the error trace may be duplicated;
	*/

}}}}

#pragma comment(lib, "ebo_test_$$$.lib")    // shared unit test library for common definition(s);
#pragma comment(lib, "shared.dbg_v15.lib")  // it is required for usage of the debug output;
#pragma comment(lib, "shared.trim_v15.lib") // it is required for usage of the error base API;

#endif/*_EBO_TEST_$W$_DEFS_H_INCLUDED*/