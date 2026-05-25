#ifndef _TEST_ADAP_$D$_BUFFER_H_INCLUDED
#define _TEST_ADAP_$D$_BUFFER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Jan-2026 at 13:01:54.936, UTC+4, Batumi, Saturday;
	This is OpenGL vertex buffer object wrapper unit test adapter interface declaration file.
*/
#include "test_case_$d$.buffer.h"

namespace test { namespace open_gl { namespace vertex {

	__class (c_vert_buf) {
	public:
		c_vert_buf (void) = default; ~c_vert_buf (void) = default; c_vert_buf (const c_vert_buf&) = delete; c_vert_buf (c_vert_buf&&) = delete;

		__method (Data); // gets vertex buffer data of triangle shape;
		__method (Size); // gets vertex buffer size in bytes; if no buffer is bound the error is returned;

	private:
		c_vert_buf& operator = (const c_vert_buf&) = delete; c_vert_buf& operator = (c_vert_buf&&) = delete;
	};

}}}

#endif/*_TEST_ADAP_$D$_BUFFER_H_INCLUDED*/