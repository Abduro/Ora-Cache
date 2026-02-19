#ifndef _TEST_CASE_$M$_MAT4x4_H_INCLUDED
#define _TEST_CASE_$M$_MAT4x4_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Feb-2026 at 14:00:50.123, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL math lib matrix 4x4 uint test interface declaration file for using in test cases' adapters;
*/
#include "test_case_$m$.mat3x3.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {

	using t_mat4x4 = ex_ui::draw::open_gl::math::c_mat4x4;
	using t_rot4x4 = ex_ui::draw::open_gl::math::c_rotate_4x4;

	class c_mtx_4x4 : public c_mtx_base { typedef c_mtx_base TBase;
	public:
		c_mtx_4x4 (void); ~c_mtx_4x4 (void) = default;

		err_code Identity();  // checks the correctness of the matrix identity procedure;
		err_code Translate(vec_3&); // translates input vertex position;

		_pc_sz To_str (const t_mat4x4&, const bool _b_cls); // returns just the string of input matrix content, no output to the logger yet;

		const
		t_mat4x4& operator ()(void) const;
		t_mat4x4& operator ()(void);
	private:
		t_mat4x4 m_mat4x4;
	};

}}}}}

#endif/*_TEST_CASE_$M$_MAT4x4_H_INCLUDED*/