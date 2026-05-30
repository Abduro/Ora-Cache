#ifndef _TEST_CASE_$M$_MAT_STACK_H_INCLUDED
#define _TEST_CASE_$M$_MAT_STACK_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Feb-2026 at 18:37:22.791, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL math lib matrix stack wrapper uint test interface declaration file for using in test cases' adapters;
*/
#if (0)
#include "test_case_$d$.ctx.h"     // for using OpenGL API draw context must be created first;

namespace test { namespace open_gl { namespace math {

	using CTstGraph = test::open_gl::context::ver_1_1::CTstGraph;

	class c_stk_target : public c_mtx_base { typedef c_mtx_base TBase;
	public:
		c_stk_target (void); ~c_stk_target (void);

		err_code Get (void) const;
		err_code Set (const e_mat_type);

		const
		t_stk_target& operator ()(void) const;
		t_stk_target& operator ()(void);

	private:
		t_stk_target m_target;
		CTstGraph    m_graph ;
	};

	class c_mtx_stack : public c_mtx_base { typedef c_mtx_base TBase;
	public:
		c_mtx_stack (void); ~c_mtx_stack (void);

		err_code Get  (const e_mat_type, t_mat4x4& _mat);
		err_code Push (const c_mat4x4&, const e_mat_mode);
		err_code Push (const c_mat4x4&, const e_mat_type);
		err_code Pop  (void);

		const
		t_mat_stack& operator ()(void) const;
		t_mat_stack& operator ()(void);

	private:
		t_mat_stack m_stack;
		CTstGraph   m_graph;
	};
}}}
#endif

#endif/*_TEST_CASE_$M$_MAT_STACK_H_INCLUDED*/