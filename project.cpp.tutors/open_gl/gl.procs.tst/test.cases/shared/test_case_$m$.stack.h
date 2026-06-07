#ifndef _TEST_CASE_$M$_MAT_STACK_H_INCLUDED
#define _TEST_CASE_$M$_MAT_STACK_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Feb-2026 at 18:37:22.791, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL math lib matrix stack wrapper uint test interface declaration file for using in test cases' adapters;
*/
#include "test_adap_$p$.defs.h"
#include "matrix\gl_procs_mtx.stack.h"

namespace test { namespace open_gl { namespace ver_1_1 {

	using namespace ::open_gl::procs::ver_1_1;
	using namespace ::open_gl::procs::matrix::ver_1_1;

	class CTstMode {
	public:
		CTstMode (const bool _b_verbose = true); CTstMode (const CTstMode&) = delete; CTstMode (CTstMode&&) = delete; ~CTstMode(void) = default;

		err_code Get (void);
		err_code Set (const e_stk_mode);

		const
		CMode& operator ()(void) const;
		CMode& operator ()(void);

	private:
		CTstMode& operator = (const CTstMode&) = delete; CTstMode& operator = (CTstMode&&) = delete;
		CMode m_mode;
		bool  m_verbose;
	};

	class CTstStack {
	public:
		CTstStack (const bool _b_verbose = true); CTstStack (const CTstStack&) = delete; CTstStack (CTstStack&&) = delete; ~CTstStack(void) = default;

		err_code Push (const CMatrix&, const e_mat_type);
		err_code Pop  (void);

		const
		CStack& operator ()(void) const;
		CStack& operator ()(void);

	private:
		CTstStack& operator = (const CTstStack&) = delete; CTstStack& operator = (CTstStack&&) = delete;
		CStack  m_stack;
		bool    m_verbose;
	};

}}}

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