#ifndef _EBO_TEST_$D$_UNIFORM_H_INCLUDED
#define _EBO_TEST_$D$_UNIFORM_H_INCLUDED
/*
	Created by Tech_dog (eb0ntrop@gmail.com) on 14-Jan-2026 at 17:57:21.906, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' uniform data type wrapper unit test adapter interface declaration file.
*/
#include "test_case_$d$.ctx.h"
#include "test_case_$d$.prog.h"
#include "test_case_$d$.uniform.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {
	using namespace ebo::boo::test;

	/* creating device context and graphics must be made before creating a program object;
	*/
	__class (c_uni_enum) {
	public:
		  c_uni_enum (const e_object = e_object::e_none, const bool _b_verb = true); // the test framework requires default constructor;
		 ~c_uni_enum (void) = default;

		 __method (Count);
		 __method (Get);    // using this test case does not produce success in result: uniform vars are empty - no shader code is executed;
		 __method (OnDraw); // this test case includes a renderer that draws something for running the 'main()' functions of shaders script;

		 const
		 TPipe&  Pipe (void) const;
		 TPipe&  Pipe (void) ;

		 const
		 TPipe&  operator ()(void) const;
		 TPipe&  operator ()(void) ;

	private:
		bool  m_b_verb; // looks like useless, but still remain perhaps for future use;
		TPipe m_pipe;   // for 
	};
}}}}}

#endif/*_EBO_TEST_$D$_UNIFORM_H_INCLUDED*/