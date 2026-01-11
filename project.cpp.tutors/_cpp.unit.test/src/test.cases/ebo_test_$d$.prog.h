#ifndef _EBO_TEST_$D$_PROG_H_INCLUDED
#define _EBO_TEST_$D$_PROG_H_INCLUDED
/*
	Created by Tech_dog (eb0ntrop@gmail.com) on 09-Jan-2026 at 22:01:05.284, UTC+4, Batumi, Friday;
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
		  c_prog (const bool _b_verb = true);
		 ~c_prog (void) = default;

		 __method (Grid);

	private:
		bool m_b_verb;
	};
}}}}}

#endif/*_EBO_TEST_$D$_PROG_H_INCLUDED*/