#ifndef _EBO_TEST_$M$_MATRIX_H_INCLUDED
#define _EBO_TEST_$M$_MATRIX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Dec-2025 at 08:10:22.332, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL math lib matrix uint test interface declaration file; 
*/
#include "ebo_test_$m$.defs.h"
#include "ebo_test_$m$.vector.h"
#include "math.matrix.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {

	using t_mat4x4 = ex_ui::draw::open_gl::math::c_mat4x4;

	/*note:
	test case method cannot have 'const' qualifier, otherwise the compiler throws the error: ...C2440: 'static_cast': cannot convert from 'void'.... ; 
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

}}}}}

#endif/*_EBO_TEST_$M$_MATRIX_H_INCLUDED*/