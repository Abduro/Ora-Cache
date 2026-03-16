#ifndef _EBO_TEST_$M$_MAT3X3_H_INCLUDED
#define _EBO_TEST_$M$_MAT3X3_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Mar-2026 at 11:56:31.170, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL math lib matrix3x3 unit test adapter interface declaration file; 
*/
#include "ebo_test_$m$.defs.h"
#include "test_case_$m$.mat3x3.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {

	__class (c_t_rotate_3x3) {
	public:
		 c_t_rotate_3x3 (void) = default;
		~c_t_rotate_3x3 (void) = default;

		__method (On_X);    // rotates 3d-vector around X-axis by certain angle;
		__method (On_Y);    // rotates 3d-vector around Y-axis by certain angle;
		__method (On_Z);    // rotates 3d-vector around Z-axis by certain angle;

		__method (Pivot);   // rotates 2d-point around pivot point in X,Y plane;
		__method (Point);   // rotates 2d-point around Z-axis from axes's origin (0,0);
		__method (Prepare); // prepares the matrix for rotation by certain angle and around particular axis (X, Y or Z);
	};

}}}}}

#endif/*_EBO_TEST_$M$_MAT3X3_H_INCLUDED*/