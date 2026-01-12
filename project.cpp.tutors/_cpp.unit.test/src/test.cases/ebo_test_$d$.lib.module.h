#ifndef _EBO_TEST_$D$_LIB_MODULE_H_INCLUDED
#define _EBO_TEST_$D$_LIB_MODULE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Jan-2026 at 20:49:51.756, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL tutorials' draw components unit test project module declaration file;
*/
#include "ebo_test_$d$.defs.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {

#if (1)
	/*these module level function cannot be shared through header file to several test cases, otherwise the linker error:
	LNK2005: struct Microsoft::VisualStudio::CppUnitTestFramework::GlobalMethodInfo const*
	          YOU_CAN_ONLY_DESIGNATE_ONE_FUNCTION_TO_BE_A_MODULE_CLEANUP_FUNCTION(void) ...
	*/
	__load (OnLoad);
	__unload (OnUnload);
#endif

}}}}}

#endif/*_EBO_TEST_$D$_LIB_MODULE_H_INCLUDED*/