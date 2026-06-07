#ifndef _TEST_ADAP_$M$_MATRIX_H_INCLUDED
#define _TEST_ADAP_$M$_MATRIX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 05-Jun-2026 at 13:02:17.371, UTC+4, Batumi, Friday;
	This is OpenGL version 1.1 matrix wrapper unit test adapter interface declaration file.
*/
#include "test_case_$m$.matrix.h"

namespace test { namespace open_gl { namespace ver_1_1 {

	__class (c_matrix) {
	public:
		c_matrix (void) = default; c_matrix (const c_matrix&) = delete; c_matrix (c_matrix&&) = delete; ~c_matrix (void) = default;

		__method (Get);
		__method (To_self);

	public:
		c_matrix& operator = (const c_matrix&) = delete; c_matrix& operator = (c_matrix&&) = delete;
	};
}}}

#endif/*_TEST_ADAP_$M$_MATRIX_H_INCLUDED*/