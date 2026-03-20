#ifndef _EBO_TEST_$M$_MATRIX_H_INCLUDED
#define _EBO_TEST_$M$_MATRIX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Dec-2025 at 08:10:22.332, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL math lib matrix uint test interface declaration file; 
*/
#include "test_case_$d$.ctx.h"     // for using OpenGL API draw context must be created first;
#include "test_case_$m$.mat2x2.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {

	__class (c_t_rotate_2x2) {
	public:
		 c_t_rotate_2x2 (void) = default;
		~c_t_rotate_2x2 (void) = default;

		__method (Matrix);  // rotates the given matrix 2x2 by certain angle;
		__method (Pivot);   // rotates the vec_2 around pivot point for certain angle;
		__method (Prepare); // prepares the matrix for rotation by certain angle;
		__method (Vector);  // rotates the given vector 2 by certain angle;
	};

}}}}}

#endif/*_EBO_TEST_$M$_MATRIX_H_INCLUDED*/