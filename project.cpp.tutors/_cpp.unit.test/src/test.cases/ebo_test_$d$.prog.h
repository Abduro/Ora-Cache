#ifndef _EBO_TEST_$D$_PROG_H_INCLUDED
#define _EBO_TEST_$D$_PROG_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Jan-2026 at 22:01:05.284, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL tutorials' program wrapper unit test adapter interface declaration file.
*/
#include "test_case_$d$.ctx.h"
#include "test_case_$d$.prog.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {
	using namespace ebo::boo::test;

	/* creating device context and graphics must be made before creating a program object;
	*/
	__class (c_prog) {
	public:
		  c_prog (const e_object = e_object::e_none, const bool _b_verb = true);
		 ~c_prog (void) = default;

		 __method (Grid); // this test case sets the appropriate target to program that may be inconsistent with the target of this test class;
		 __method (Tria); // this test case sets the appropriate target to program that may be inconsistent with the target of this test class;

		 const
		 TPipe& operator ()(void) const;
		 TPipe& operator ()(void) ;

	private:
		bool  m_b_verb;
		TPipe m_pipe;
	};
}}}}}

#endif/*_EBO_TEST_$D$_PROG_H_INCLUDED*/