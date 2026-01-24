#ifndef _EBO_TEST_$D$_SHAPE_2D_H_INCLUDED
#define _EBO_TEST_$D$_SHAPE_2D_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Jan-2026 at 23:19:11.472, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL 2d shape wrapper unit test adapter interface declaration file.
*/
#include "test_case_$d$.shape.2d.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {
	using namespace ebo::boo::test;

	__class (c_tria_2d) {
	public:
		c_tria_2d (void); ~c_tria_2d (void) = default;

		__method (Create_n_Delete);  // this is for creating triangle shape with all required draw objects: vao, vbo and vertex attrs;
		__method (Draw);             // tests the draw operation of the triangle shape;

		const
		TPipe& operator ()(void) const;
		TPipe& operator ()(void) ;

	private:
		TPipe m_pipe; // perhaps it is not required because the triangle test case class has the pipe with predefined draw target 'e_tria';
	};

}}}}}

#endif/*_EBO_TEST_$D$_SHAPE_2D_H_INCLUDED*/