#ifndef _EBO_TEST_$D$_BUFFER_H_INCLUDED
#define _EBO_TEST_$D$_BUFFER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Jan-2026 at 13:01:54.936, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL vertex buffer object wrapper unit test adapter interface declaration file.
*/
#include "test_case_$d$.buffer.h"

namespace test { namespace draw { namespace open_gl {
	using namespace ebo::boo::test;

	__class (c_vert_buf) {
	public:
		c_vert_buf (void); ~c_vert_buf (void) = default;

		__method (Data); // gets vertex buffer data of triangle shape;
		__method (Size); // gets vertex buffer size in bytes; if no buffer is bound the error is returned;
	};

}}}

#endif/*_EBO_TEST_$D$_BUFFER_H_INCLUDED*/