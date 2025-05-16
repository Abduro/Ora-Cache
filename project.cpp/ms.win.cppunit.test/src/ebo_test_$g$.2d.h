#ifndef _EBO_TEST_$G$_2D_H_INCLUDED
#define _EBO_TEST_$G$_2D_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Oct-2024 at 09:18:10.448, UTC+4, Batumi, Tuesday;
	This is Ebo Pack 2D space geometry lib unit test common definition file; 
*/
#include "_log.h"

#include "sys.error.h"

#include "2d.base.h"
#include "2d.shape.h"
#include "2d.shape.line.h"

namespace ebo { namespace boo { namespace test {

	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using CError  = shared::sys_core::CError;
	using TError  = const CError;
	using TString = TStringEx   ;

}}}

#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);
#pragma comment(lib, "color_v15.lib")        // color management library;
#pragma comment(lib, "geometry.2d_v15.lib")  // this one must be tested by this unit test project;
#pragma comment(lib, "sys.err.core_v15.lib") // for using error object;
#pragma comment(lib, "sys.shared_v15.lib")   // this is the base;

#endif/*_EBO_TEST_$G$_2D_H_INCLUDED*/