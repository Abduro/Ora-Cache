#ifndef _EBO_TEST_$D$_PROG_H_INCLUDED
#define _EBO_TEST_$D$_PROG_H_INCLUDED
/*
	Created by Tech_dog (eb0ntrop@gmail.com) on 09-Jan-2026 at 22:01:05.284, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL tutorials' program wrapper unit test interface declaration file.
*/
#include "ebo_test_$d$.builder.h"

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

	__class (c_shaders) { // test class cannot be inherited from any class unfortunately;
	public:
		  c_shaders (const e_object = e_object::e_grid, const bool _b_verb = true);
		 ~c_shaders (void) = default;

		 __method (Create_all); // creates all shaders, before calling this proc, the device context must be created, otherwise procs loader throws the error;

		 __method (Get_frag);   // shaders belong to a program of the draw target object and the reference to the program can be gotten by target type only;
		 __method (Get_vert);   // shaders belong to a program of the draw target object and the reference to the program can be gotten by target type only;

	private:
		bool     m_b_verb;
		e_object m_target;
	};

}}}}}

#endif/*_EBO_TEST_$D$_PROG_H_INCLUDED*/