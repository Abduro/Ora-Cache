#ifndef _TEST_ADAP_$M$_FRUSTUM_H_INCLUDED
#define _TEST_ADAP_$M$_FRUSTUM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-May-2026 at 19:16:48.217, UTC+4, Batumi, Tuesday;
	This is OpenGL virtual camera frustum unit test adapter interface declaration file; 
*/
#include "test_case_$m$.frustum.h"

namespace test { namespace open_gl { namespace frustum {

	__class (c_frustum) {
	public:
		c_frustum (void) = default; c_frustum (const c_frustum&) = delete; c_frustum (c_frustum&&) = delete; ~c_frustum (void) = default;

		__method (Get_perspect); // calculates perspective projection matrix;
		__method (Set_aspect);   // sets pre-defined surface window size;
		__method (Set_defaults); // gets default configuration values;

	private:
		c_frustum& operator = (const c_frustum&) = delete; c_frustum& operator = (c_frustum&&) = delete;
	};

}}}

#endif/*_TEST_ADAP_$M$_FRUSTUM_H_INCLUDED*/