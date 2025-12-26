#ifndef _EBO_TEST_$M$_DEFS_H_INCLUDED
#define _EBO_TEST_$M$_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Dec-2025 at 09:05:40.726, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL math lib common definitions' uint test interface declaration file; 
*/
#include "_log.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {
	using namespace ebo::boo::test;
	/*
	...when a number with an infinite binary representation is stored in a float (which has a fixed, 32-bit size), it must be rounded to the nearest representable value...
	1.0f is shown as 0.99999994, which is the nearest representable float value that is not exactly 1;
	...how to manage this inexactness:
	use double for higher precision: the double data type uses 64 bits and provides about 15-18 significant decimal digits of precision, compared to float's 6-9 digits...
	*/
}}}}}

#pragma comment(lib, "gl.math_v15.lib")      // this project is being tested by this unit test project;
#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);

#endif/*_EBO_TEST_$M$_DEFS_H_INCLUDED*/