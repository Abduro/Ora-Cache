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

#define __load(name)   TEST_MODULE_INITIALIZE(name) // this method is called by 'testhost.exe' on *loding* a user defined test case project dll; must to be checked;
#define __unload(name) TEST_MODULE_CLEANUP(name)    // this method is called by 'testhost.exe' on *unloding* a user defined test case project dll; must to be checked;

#define __init(name)   TEST_CLASS_INITIALIZE(name)  // defines method 'name' that runs *before* each test class is created;
#define __clean(name)  TEST_CLASS_CLEANUP(name)     // defines method 'name' that runs *after* each test class is created;

#define __class(name)  TEST_CLASS(name)      // *required* for each class containing test methods; it identifies 'name' as a test class;

#define __ctor(name)   TEST_METHOD(name)     // just for making a distinguishing between a method and a constructor of a class; not required;
#define __dtor(name)   TEST_METHOD(name)     // just for making a distinguishing between a method and a destructor of a class; not required;

#define __method(name)   TEST_METHOD(name)   // a test method must be declared in the scope of the test class; *required*;
#define __property(name) TEST_METHOD(name)   // just for a distinguishing between a method and a pproperty of a class; not required;

#define __befare_run(name) TEST_METHOD_INITIALIZE(name) // a method to be run *before each* test method is called; some sort of constructor of test case;
#define __after_run(name)  TEST_METHOD_CLEANUP(name)    // a method to be run *after each* test method; some sort of destructor of thest case;

}}}

#endif/*_DEFS_H_INCLUDED*/