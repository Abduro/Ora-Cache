#ifndef _EBO_TEST_$D$_SHADER_H_INCLUDED
#define _EBO_TEST_$D$_SHADER_H_INCLUDED
/*
	Created by Tech_dog (eb0ntrop@gmail.com) on 11-Jan-2026 at 16:11:29.597, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL tutorials' shader wrapper unit test adapter interface declaration file.
*/
#include "test_case_$d$.ctx.h"
#include "test_case_$d$.shader.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {
	using namespace ebo::boo::test;

	__class (c_shaders) { // test class cannot be inherited from any class unfortunately;
	public:
		  c_shaders (const e_object = e_object::e_grid, const bool _b_verb = true);
		 ~c_shaders (void) = default;

		 __method (Create);   // creates all shaders, before calling this proc, the device context must be created, otherwise procs loader throws the error;

		 __method (Get_frag); // shaders belong to a program of the draw target object and the reference to the program can be gotten by target type only;
		 __method (Get_vert); // shaders belong to a program of the draw target object and the reference to the program can be gotten by target type only;

		 e_object Target (void) const;

	private:
		bool     m_b_verb;
		e_object m_target;
	};

}}}}}

#endif/*_EBO_TEST_$D$_SHADER_H_INCLUDED*/