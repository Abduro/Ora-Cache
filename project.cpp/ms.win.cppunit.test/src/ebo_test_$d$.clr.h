#ifndef _EBO_TEST_$D$_CLR_H_INCLUDED
#define _EBO_TEST_$D$_CLR_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Sep-2024 at 13:05:20.849, UTC+4, Batumi, Saturday;
	This is Ebo Pack shared draw color interface declaration file; 
*/
#include "_log.h"

#include "color._defs.h"
#include "color.alpha.h"
#include "color.rgb.h"

#include "color.named.h"
#include "color.x11.h"

#pragma comment(lib, "color_v15.lib")        // this one must be tested by this unit test project;
#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);

namespace ebo { namespace boo { namespace test { namespace color { namespace rgb {

	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using TPercent = TPct_Flt;

	__class(CAlpha) {
	public:
		__ctor(_ctor);
	};

	using TClrFloat = ex_ui::color::rgb::CClr_Float;
	using clr_type  = ex_ui::color::rgb::clr_type;

	__class(CClr_Float) {
	public:
		 CClr_Float (void) = default;
		~CClr_Float (void) = default;
	public:
		__method(RgbToFloat);
	};

}}}}}

#endif/*_EBO_TEST_$D$_CLR_H_INCLUDED*/