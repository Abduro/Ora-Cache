#ifndef _DEFS_H_INCLUDED
#define _DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 2-Apr-2024 at 09:38:48.4917163, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack UIX libs unit test common defenitions' declaration file;
*/
#include "shared.defs.h"
#include <CppUnitTest.h>
/*
	the runtime of libraries being tested and this test project must be the same:
	   - Multi-threaded Debug (/MTd) ;
*/
#pragma comment(lib, "shared.trim_v15.lib") // this is the shared base lib project of Ebo pack solution that is adopted to Stroke Over projects;
#pragma comment(lib, "shared.dbg_v15.lib")  // this lib is used for output debug messages to test output console;

namespace ebo { namespace boo { namespace test {

	using namespace shared::defs;

	// https://learn.microsoft.com/en-us/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference ;
	// https://learn.microsoft.com/en-us/visualstudio/test/writing-unit-tests-for-c-cpp ;

	using namespace Microsoft::VisualStudio::CppUnitTestFramework;

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