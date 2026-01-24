#ifndef _EBO_TEST_$D$_BUFFER_H_INCLUDED
#define _EBO_TEST_$D$_BUFFER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Jan-2026 at 13:01:54.936, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL vertex buffer object wrapper unit test adapter interface declaration file.
*/
#include "test_case_$d$.buffer.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {
	using namespace ebo::boo::test;

	__class (c_vert_buf) {
	public:
		c_vert_buf (void); ~c_vert_buf (void) = default;

		__method (Size); // gets vertex buffer size in bytes; if no buffer is bound the error is returned;
	};

}}}}}

#endif/*_EBO_TEST_$D$_BUFFER_H_INCLUDED*/