#ifndef _TEST_ADAP_$M$_ORTHO_H_INCLUDED
#define _TEST_ADAP_$M$_ORTHO_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Jun-2026 at 13:31:17.046, UTC+4, Batumi, Friday;
	This is OpenGL orthographic projection matrix wrapper unit test adapter interface declaration file.
*/
#include "test_case_$m$.ortho.h"
#include "test_case_$m$.matrix.h"
#include "test_case_$m$.stack.h"

namespace test { namespace open_gl { namespace ortho {

	using namespace ::test::open_gl::ver_1_1;

	__class (c_ortho) {
	public:
		c_ortho (void) = default; c_ortho (const c_ortho&) = delete; c_ortho (c_ortho&&) = delete; ~c_ortho (void) = default;

		/* The following steps are required:
		   step #0: sets current rendering context; !required! it is made automatically when this test module is being loaded;
		   step #1: sets the matrix mode to 'projection';
		   step #2: resets the matrix to identity;
		   step #3: creates the orthographic matrix; << this is the step being tested!
		   step #4: if matrix creation succeeded queries the changed matrix back;
		   step #5: restores 'modelview' mode to draw objects;
		*/
		__method (Set);

	public:
		c_ortho& operator = (const c_ortho&) = delete; c_ortho& operator = (c_ortho&&) = delete;
	};
}}}

#endif/*_TEST_ADAP_$M$_ORTHO_H_INCLUDED*/