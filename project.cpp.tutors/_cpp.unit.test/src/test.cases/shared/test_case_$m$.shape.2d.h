#ifndef _TEST_CASE_$M$_SHAPE_2D_H_INCLUDED
#define _TEST_CASE_$M$_SHAPE_2D_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Mar-2026 at 14:03:05.722, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL math lib shape uint test interface declaration file for using in test cases' adapters; 
*/
#include "ebo_test_$m$.defs.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {

	class c_square {
	public:
		 c_square (void) = default; c_square (const c_square&) = delete; c_square (c_square&&) = delete;
		~c_square (void) = default;

	private:
		c_square& operator = (const c_square&) = delete; c_square& operator = (c_square&&) = delete;
	};

}}}}}

#endif/*_TEST_CASE_$M$_SHAPE_2D_H_INCLUDED*/