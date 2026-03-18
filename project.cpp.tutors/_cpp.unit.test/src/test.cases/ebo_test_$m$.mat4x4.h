#ifndef _EBO_TEST_$M$_MAT4X4_H_INCLUDED
#define _EBO_TEST_$M$_MAT4X4_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Mar-2026 at 12:27:16.475, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL math lib matrix4x4 unit test adapter interface declaration file; 
*/
#include "ebo_test_$m$.defs.h"
#include "test_case_$m$.mat4x4.h"
#include "test_case_$m$.vec3.h"
#include "test_case_$m$.vec4.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {
	/*note:
	test case method cannot have 'const' qualifier, otherwise the compiler throws the error: ...C2440: 'static_cast': cannot convert from 'void'.... ;
	Translate function test case must consist of the following steps:
	(1) creating identity matrix, it is indicating the position by cell[3.3] == 1, otherwise direction '0' cannot be translated/transfered;
	(2) creating the vertex position vector;
	(3) multiplying the matrix by the vector;
	(4) result matrix is the transformed vector; it is not different from input vector, because the matrix is the identity one; 
	*/
	__class (c_mat_4x4) {
	public:
		 c_mat_4x4 (void) = default;
		~c_mat_4x4 (void) = default;

		__method (Identity);  // checks the correctness of the matrix identity procedure;
		__method (Translate); // translates input coordinates in world space to camera view matrix (camera local coordinates);
		__method (Transpose); // converts a matrix from column-major to row-major matrix and vice versa;
	};

	__class (c_t_rotate_4x4) {
	public:
		 c_t_rotate_4x4 (void) = default;
		~c_t_rotate_4x4 (void) = default;

		__method (Around_X);  // rotates 3d-vector around X-axis by certain angle;
		__method (Around_Y);  // rotates 3d-vector around Y-axis by certain angle;
		__method (Around_Z);  // rotates 3d-vector around Z-axis by certain angle;

		__method (Prepare);   // prepares the matrix for rotation by certain angle and around particular axis (X, Y or Z);
		__method (Sequence);  // multiplies rotations matrices in order Z * Y * X (or roll-yaw-pitch);
	};

}}}}}

#endif/*_EBO_TEST_$M$_MAT4X4_H_INCLUDED*/