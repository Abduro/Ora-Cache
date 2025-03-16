#ifndef _DEFS_H_INCLUDED
#define _DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 2-Apr-2024 at 09:38:48.4917163, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack UIX libs unit test common defenitions' declaration file;
*/
#include <atlbase.h>  // https://learn.microsoft.com/en-us/cpp/atl-mfc-shared/reference/csimplestringt ;
#include <atlstr.h>   // https://learn.microsoft.com/en-us/cpp/atl-mfc-shared/reference/cstringt-class ;
#include <CppUnitTest.h>

#include "shared.preproc.h"
#include "shared.string.h"
#include "shared.types.h"
/*
	the runtime of libraries being tested and this test project must be the same:
	   - Multi-threaded Debug (/MTd) ;
	   - Multi-threaded DLL (/MD)    ;
*/
#pragma comment(lib, "sys.shared_v15.lib") // this is the shared base lib project of Ebo pack solution that is adopted to Stroke Over projects;

namespace ebo { namespace boo { namespace test {

	// https://stackoverflow.com/questions/1950779/is-there-any-way-to-find-the-address-of-a-reference ;
#if defined WIN64
	uint64_t __address_of (const void* const _p_fun_ptr) ;
#else
	uint32_t __address_of (const void* const _p_fun_ptr) ;
#endif
	// https://learn.microsoft.com/en-us/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference ;
#define __class(name) TEST_CLASS(name)
#define __method(name) TEST_METHOD(name)
#define __property(name) TEST_METHOD(name)

#define __ctor(name) TEST_METHOD(name) // just for making a distinguishing between a method and a constructor of a class;
#define __dtor(name) TEST_METHOD(name) // just for making a distinguishing between a method and a destructor of a class;

#define __init(name) TEST_CLASS_INITIALIZE(name) // an event of loading a test class object ;
#define __term(name) TEST_CLASS_CLEANUP(name)

}}}

#endif/*_DEFS_H_INCLUDED*/