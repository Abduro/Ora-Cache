#ifndef _EBO_TEST_$D$_DEFS_H_INCLUDED
#define _EBO_TEST_$D$_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Jan-2026 at 23:38:48.842, UTC+4, Batumi, Tauesday;
	Ebo Pack OpenGL draw context lib common definitions' uint test interface declaration file;
*/
#include "_log.h"
#include "gl_renderer.h"
#include "shared.dbg.h"
#include "shared.preproc.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {
	using namespace ebo::boo::test;
#if (0)
	/*these module level function cannot be shared through header file to several test cases, otherwise the linker error:
	LNK2005: struct Microsoft::VisualStudio::CppUnitTestFramework::GlobalMethodInfo const*
	          YOU_CAN_ONLY_DESIGNATE_ONE_FUNCTION_TO_BE_A_MODULE_CLEANUP_FUNCTION(void) ...
	*/
	__load (OnLoad);
	__unload (OnUnload);
#endif
}}}}}

#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);

#endif/*_EBO_TEST_$D$_DEFS_H_INCLUDED*/