#ifndef _EBO_TEST_$D$_ZBUF_H_INCLUDED
#define _EBO_TEST_$D$_ZBUF_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-May-2025 at 13:12:52.885, UTC+4, Batumi, Wednesday;
	This is Ebo Pack WinAPI GDI in-memory draw renderer lib unit test interface declaration file;
	-----------------------------------------------------------------------------
	*Important* : this project must refer the same Windows SDK version as render project does (10.0.18362.0);
*/
#include "_log.h"

#include "uix.gdi.defs.h"
#include "uix.gdi.blend.h"
#include "uix.gdi.shade.h"
#include "uix.gdi.object.h"
#include "uix.gdi.zbuf.h"

namespace ebo { namespace boo { namespace test { namespace draw {

	// https://learn.microsoft.com/en-us/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference ;
	// https://learn.microsoft.com/en-us/visualstudio/test/writing-unit-tests-for-c-cpp ;

	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using namespace shared::types;

	using CError  = shared::sys_core::CError;
	using TError  = const CError;
	using TString = TStringEx   ;

}}}}

#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);
#pragma comment(lib, "gdi.zbuf_v15.lib")     // this one must be tested by this unit test project;
#pragma comment(lib, "sys.err.core_v15.lib") // for using error object;
#pragma comment(lib, "sys.shared_v15.lib")   // this is the shared base;

#endif/*_EBO_TEST_$D$_ZBUF_H_INCLUDED*/