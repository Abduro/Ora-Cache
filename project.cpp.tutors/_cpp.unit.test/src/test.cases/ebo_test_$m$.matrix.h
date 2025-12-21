#ifndef _EBO_TEST_$M$_MATRIX_H_INCLUDED
#define _EBO_TEST_$M$_MATRIX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Dec-2025 at 08:10:22.332, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL math lib matrix uint test interface declaration file; 
*/
#include "ebo_test_$m$.defs.h"
#include "math.matrix.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {

	using t_mat_2x2 = ex_ui::draw::open_gl::math::c_mat2x2;

	__class (c_mat2x2) {
	public:
		 c_mat2x2 (const bool _b_verb = false);
		~c_mat2x2 (void) = default;

		__ctor (_ctor);

	private:
		bool       m_b_verb;
		t_mat_2x2  m_mat_2x2;
	};

}}}}}

#endif/*_EBO_TEST_$M$_MATRIX_H_INCLUDED*/