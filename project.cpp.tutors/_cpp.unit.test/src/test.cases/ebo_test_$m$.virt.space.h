#ifndef _EBO_TEST_$M$_VIRT_SPACE_H_INCLUDED
#define _EBO_TEST_$M$_VIRT_SPACE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Feb-2026 at 12:04:51.267, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL math lib virtual space unit test adapter interface declaration file; 
*/
#include "test_case_$m$.virt.space.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {

	__class (c_axes_fix) {
	public:
		c_axes_fix (void); ~c_axes_fix (void) = default;

		__method (Create);
	};

	__class (c_axes_dyn) {
	public:
		c_axes_dyn (void); ~c_axes_dyn (void) = default;

		__method (Create);
	};

	__class (c_virt_space) {
	public:
		c_virt_space (void); ~c_virt_space (void) = default;

	};

}}}}}

#endif/*_EBO_TEST_$M$_VIRT_SPACE_H_INCLUDED*/