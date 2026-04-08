#ifndef _TEST_ADAP_$DAT$_LIB_MODULE_H_INCLUDED
#define _TEST_ADAP_$DAT$_LIB_MODULE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-Apr-2026 at 14:43:55.391, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' data providers' unit test project module declaration file;
*/
#include "test_case_$dat$.defs.h"

namespace ebo { namespace boo { namespace test { namespace data {

	using CCoIniter = shared::sys_core::CCoIniter;
#if (1)
	/*these module level function cannot be shared through header file to several test cases, otherwise the linker error:
	LNK2005: struct Microsoft::VisualStudio::CppUnitTestFramework::GlobalMethodInfo const*
	          YOU_CAN_ONLY_DESIGNATE_ONE_FUNCTION_TO_BE_A_MODULE_CLEANUP_FUNCTION(void) ...
	*/
	__load (OnLoad);
	__unload (OnUnload);
#endif

}}}}

#endif/*_TEST_ADAP_$DAT$_LIB_MODULE_H_INCLUDED*/