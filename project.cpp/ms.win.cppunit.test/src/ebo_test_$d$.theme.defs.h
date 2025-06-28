#ifndef _EBO_TEST_$D$_THEME_DEFS_H_INCLUDED
#define _EBO_TEST_$D$_THEME_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Jun-2025 at 08:11:59.496, UTC+4, Batumi, Saturday;
	This is Ebo Pack custom color theme unit test include headers' and common declarations' file; 
*/
#include "_log.h"

#include "uix.theme.h"
#include "uix.theme.named.h"

namespace ebo { namespace boo { namespace test { namespace themes {

	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using TPercent = TPct_Flt;
	using clr_type = ex_ui::color::rgb::clr_type;

}}}}

#pragma comment(lib, "theme_v15.lib")        // this one must be tested by this unit test project;
#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);

#endif/*_EBO_TEST_$D$_THEME_DEFS_H_INCLUDED*/