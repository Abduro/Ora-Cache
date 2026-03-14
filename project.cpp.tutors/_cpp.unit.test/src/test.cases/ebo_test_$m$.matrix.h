#ifndef _EBO_TEST_$M$_MATRIX_H_INCLUDED
#define _EBO_TEST_$M$_MATRIX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Dec-2025 at 08:10:22.332, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL math lib matrix uint test interface declaration file; 
*/
#include "test_case_$d$.ctx.h"     // for using OpenGL API draw context must be created first;
#include "test_case_$m$.mat2x2.h"
#include "test_case_$m$.mat3x3.h"
#include "test_case_$m$.mat4x4.h"
#include "test_case_$m$.vec3.h"
#include "test_case_$m$.vec4.h"
#include "test_case_$m$.stack.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {

	__class (c_mat_3x3) {
	public:
		 c_mat_3x3 (void) = default;
		~c_mat_3x3 (void) = default;

	};
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
#if (0)
	__class (c_rot_3x3) {
	public:
		 c_rot_3x3 (const bool _b_verb = true);
		~c_rot_3x3 (void) = default;

		__ctor (_ctor);
		__method (Rotate_x);   // rotates on set of different angles alon x-axis;
		__method (Rotate_y);   // rotates on set of different angles alon y-axis;
		__method (Rotate_z);   // rotates on set of different angles alon z-axis;
		const
		t_rot3x3&  ref (void) const;
		t_rot3x3&  ref (void) ;
		CString To_str (void) const;

	private:
		bool     m_b_verb;
		t_rot3x3 m_rot3x3;
	};
#endif
#if (0)
	__class (c_rot_4x4) {
	public:
		__method (Rotate_free); // rotates on set of different angles about any axis specified by particular vector data ;

		__method (Rotate_y);    // rotates on set of different angles about y-axis;
		__method (Rotate_z);    // rotates on set of different angles about z-axis;
		__method (Set);         // sets initial data for passing rotation test cases, there is no result with 0-filled matrix;

		CString To_str (void) const;

	private:
		t_rot4x4 m_rot4x4;
	};
#endif
	__class (c_t_rotate_2x2) {
	public:
		 c_t_rotate_2x2 (void) = default;
		~c_t_rotate_2x2 (void) = default;

		__method (Matrix);  // rotates the given matrix 2x2 by certain angle;
		__method (Pivot);   // rotates the vec_2 around pivot point for certain angle;
		__method (Prepare); // prepares the matrix for rotation by certain angle;
		__method (Vector);  // rotates the given vector 2 by certain angle;
	};

	__class (c_t_rotate_3x3) {
	public:
		 c_t_rotate_3x3 (void) = default;
		~c_t_rotate_3x3 (void) = default;

		__method (Pivot);   // rotates point around pivot point;
		__method (Point);   // rotates point around Z-axis from axes origin (0,0);
		__method (Prepare); // prepares the matrix for rotation by certain angle and around particular axis (x, y or z);
	};

	__class (c_t_rotate_4x4) {
	public:
		 c_t_rotate_4x4 (void) = default;
		~c_t_rotate_4x4 (void) = default;

		__method (On_X); // rotates on set of different angles about x-axis;
	};
	/* The matrix stack functionality (glMatrixMode, glGetFloatv, glLoadIdentity, etc.) is part of the "fixed-function pipeline" and has been deprecated since OpenGL 3.1.
	   OpenGL (3.1+ Core Profile, OpenGL ES 2.0+) requires to manage matrices in application code and pass them to shaders using uniforms;
	   Thus, testing functionality of classes below is useless:
	   cls::[CError]>>{code=0x0502;result=0x80070502;desc='#__e_state: Invalid state for getting the pointer';context=CBase::CParam::Get_ptr()}
	*/
	__class (c_stk_current) {
	public:
		 c_stk_current (void);
		~c_stk_current (void) = default;

	__method (Get);
	__method (Set);
	};

	__class (c_mat_stack) {
	public:
		 c_mat_stack (void);
		~c_mat_stack (void) = default;

	__method (Get);
	__method (Pop);
	__method (Push);
	};

}}}}}

#endif/*_EBO_TEST_$M$_MATRIX_H_INCLUDED*/