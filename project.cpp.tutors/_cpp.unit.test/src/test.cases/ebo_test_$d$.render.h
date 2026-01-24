#ifndef _EBO_TEST_$D$_UNIFORM_H_INCLUDED
#define _EBO_TEST_$D$_UNIFORM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Jan-2026 at 22:23:24.532.906, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL tutorials' draw renderer wrapper unit test adapter interface declaration file.
*/
#include "test_case_$d$.render.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {
	using namespace ebo::boo::test;

	__class (c_renderer) {
	public:
		  c_renderer (const e_object = e_object::e_none);
		 ~c_renderer (void) = default;

		 __method (Draw);

		 const
		 TPipe& operator ()(void) const;
		 TPipe& operator ()(void) ;

	private:
		TPipe  m_pipe;
	};

}}}}}

#endif/*_EBO_TEST_$D$_UNIFORM_H_INCLUDED*/