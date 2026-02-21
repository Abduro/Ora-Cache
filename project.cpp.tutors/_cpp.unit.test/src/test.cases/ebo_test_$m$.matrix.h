#ifndef _EBO_TEST_$M$_MATRIX_H_INCLUDED
#define _EBO_TEST_$M$_MATRIX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Dec-2025 at 08:10:22.332, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL math lib matrix uint test interface declaration file; 
*/
#include "test_case_$m$.mat3x3.h"
#include "test_case_$m$.mat4x4.h"
#include "test_case_$m$.vec3.h"
#include "test_case_$m$.vec4.h"
#include "ebo_test_$m$.vector.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {

	__class (c_mat3x3) {
	public:
		 c_mat3x3 (const bool _b_verb = true);
		~c_mat3x3 (void) = default;

		__ctor (_ctor);
		__method (Set);

		const
		t_mat3x3&  ref (void) const;
		t_mat3x3&  ref (void) ;

		CString To_str (_pc_sz _p_pfx = predefs::_p_pfx, _pc_sz _p_sep = _T(" "), _pc_sz _p_sfx = predefs::_p_sfx) const;

		const
		t_mat3x3&  operator ()(void) const;
		t_mat3x3&  operator ()(void) ;

	private:
		mutable bool     m_b_verb;
		mutable t_mat3x3 m_mat3x3;
	};

	/*note:
	test case method cannot have 'const' qualifier, otherwise the compiler throws the error: ...C2440: 'static_cast': cannot convert from 'void'.... ;
	Translate function test case must consist of the following steps:
	(1) creating identity matrix, it is indicating the position by cell[3.3] == 1, otherwise direction '0' cannot be translated/transfered;
	(2) creating the vertex position vector;
	(3) multiplying the matrix by the vector;
	(4) result matrix is the transfored vector; it is not different from input vector, because the matrix is the identity one; 
	*/
	__class (c_mat4x4) {
	public:
		 c_mat4x4 (const bool _b_verb = false);
		~c_mat4x4 (void) = default;

		__ctor (_ctor);       // this is visible for test framework, emulates the constructor of the class object being tested;
		__method (Identity);  // checks the correctness of the matrix identity procedure;
		__method (Translate); // translates imput coordinates in world space to camera view matrix (camera local coordinates);

		const
		t_mat4x4&  ref (void) const;
		t_mat4x4&  ref (void) ;
		CString To_str (_pc_sz _p_pfx = predefs::_p_pfx, _pc_sz _p_sep = _T(" "), _pc_sz _p_sfx = predefs::_p_sfx) const;

	private:
		mutable bool     m_b_verb;
		mutable t_mat4x4 m_mat4x4;
	};

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

	__class (c_rot_4x4) {
	public:
		 c_rot_4x4 (const bool _b_verb = true);
		~c_rot_4x4 (void) = default;

		__ctor (_ctor);

		__method (Rotate_free); // rotates on set of different angles about any axis specified by particular vector data ;

		__method (Rotate_x);    // rotates on set of different angles about x-axis;
		__method (Rotate_y);    // rotates on set of different angles about y-axis;
		__method (Rotate_z);    // rotates on set of different angles about z-axis;
		__method (Set);         // sets initial data for passing rotation test cases, there is no result with 0-filled matrix;

		const
		t_rot4x4&  ref (void) const;
		t_rot4x4&  ref (void) ;
		CString To_str (void) const;

	private:
		bool     m_b_verb;
		t_rot4x4 m_rot4x4;
	};

}}}}}

#endif/*_EBO_TEST_$M$_MATRIX_H_INCLUDED*/