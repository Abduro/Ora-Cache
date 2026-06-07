#ifndef _TEST_ADAP_$P$_MODULE_H_INCLUDED
#define _TEST_ADAP_$P$_MODULE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-May-2026 at 19:19:18.780, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' draw components unit test project module declaration file;
*/
#include "test_adap_$p$.defs.h"

namespace test { namespace open_gl {

#if (1)
	/*these module level function cannot be shared through header file to several test cases, otherwise the linker error:
	LNK2005: struct Microsoft::VisualStudio::CppUnitTestFramework::GlobalMethodInfo const*
	          YOU_CAN_ONLY_DESIGNATE_ONE_FUNCTION_TO_BE_A_MODULE_CLEANUP_FUNCTION(void) ...
	*/
	__load (OnLoad);     // creates rendering and device contexts; it is very useful for getting rid off calling TCtx_Toggle() in every test case method;
	__unload (OnUnload); // destroyes the contexts;
#endif

}}

#endif/*_TEST_ADAP_$P$_MODULE_H_INCLUDED*/