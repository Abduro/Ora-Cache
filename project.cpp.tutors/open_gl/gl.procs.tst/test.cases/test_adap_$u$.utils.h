#ifndef _TEST_ADAP_$U$_UTILS_H_INCLUDED
#define _TEST_ADAP_$U$_UTILS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-Jun-2026 at 12:58:31.572, UTC+4, Batumi, Friday;
	This is OpenGL version 1.1 GLU related procedures' wrapper unit test adapter interface declaration file.
*/
#include "test_case_$m$.matrix.h"
#include "test_case_$m$.stack.h"
#include "test_case_$p$.viewport.h"
#include "test_case_$u$.perspect.h"
#include "test_case_$u$.vsync.h"

namespace test { namespace open_gl { namespace utils { namespace ver_1_1 {

	using namespace ::test::open_gl::ver_1_1;
	using namespace ::test::open_gl::procs;
	/* for setting perspective matrix, the following steps are required:
	step #1 sets viewport to desirable size;
	step #2 sets current matrix stack to projection mode;
	step #3 sets the projection matrix; << this is the actual test case of calling gluPerspective;
	step #4 returns back the modelview mode;
	*/
	__class (c_perspect) {
	public:
		c_perspect (void) = default; c_perspect (const c_perspect&) = delete; c_perspect (c_perspect&&) = delete; ~c_perspect (void) = default;
		__method (Get);  // gets the projection perspective matrix;
		__method (Set);  // sets the projection perspective matrix;
	private:
		c_perspect& operator = (const c_perspect&) = delete; c_perspect& operator = (c_perspect&&) = delete;
	};

	__class (c_vsync) {
	public:
		c_vsync (void) = default; c_vsync (const c_vsync&) = delete; c_vsync (c_vsync&&) = delete; ~c_vsync (void) = default;
		__method (Get);  // gets the frame count that is currently set for buffers' swap;
		__method (Set);  // sets the frame count for buffers' swap;
	private:
		c_vsync& operator = (const c_vsync&) = delete; c_vsync& operator = (c_vsync&&) = delete;
	};

}}}}

#endif/*_TEST_ADAP_$U$_UTILS_H_INCLUDED*/