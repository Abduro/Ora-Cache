#ifndef _EBO_TEST_$D$_SHADER_H_INCLUDED
#define _EBO_TEST_$D$_SHADER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Jan-2026 at 16:11:29.597, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL tutorials' shader wrapper unit test adapter interface declaration file.
*/
#include "test_case_$d$.ctx.h"
#include "test_case_$d$.shader.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {
	using namespace ebo::boo::test;

	__class (c_persist) {
	public:
		c_persist (void); c_persist (const c_persist&) = delete; c_persist (c_persist&&) = delete; ~c_persist (void) = default;

		__method (Get_itmes);
		__method (Get_root);

	private:
		c_persist& operator = (const c_persist&) = delete; c_persist& operator = (c_persist&&) = delete;
	};

	__class (c_shaders) { // test class cannot be inherited from any class unfortunately;
	public:
		class COpts : private no_copy {
		public:
			COpts (void) ; ~COpts (void) = default;

			bool Compile (void) const; // gets the compile option value;
			bool Compile (const bool); // sets the compile option value, returns 'true' in case of option value change;

		private:
			bool m_b_cmpl; // this is the option of shader compilation when it is created; by default is true;
		};
		  c_shaders (const e_object = e_object::e_none, const bool _b_verb = true);
		 ~c_shaders (void) = default;

		 __method (Get_frag); // shaders belong to a program of the draw target object and the reference to the program can be gotten by target type only;
		 __method (Get_vert); // shaders belong to a program of the draw target object and the reference to the program can be gotten by target type only;

		 const
		 COpts&   Opts (void) const;
		 COpts&   Opts (void) ;

		 const
		 TPipe& operator ()(void) const;
		 TPipe& operator ()(void);

	private:
		bool   m_b_verb; // not used yet;
		COpts  m_opts;
		TPipe  m_pipe;
	};

	__class (c_test_cases) {
	public:
		c_test_cases (void); c_test_cases (const c_test_cases&) = delete; c_test_cases (c_test_cases&&) = delete; ~c_test_cases (void) = default;

		__method (Load);

	private:
		c_test_cases& operator = (const c_test_cases&) = delete; c_test_cases& operator = (c_test_cases&&) = delete;
	};
}}}}}

#endif/*_EBO_TEST_$D$_SHADER_H_INCLUDED*/