#ifndef _TEST_ADAP_$P$_VIEWPORT_H_INCLUDED
#define _TEST_ADAP_$P$_VIEWPORT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 31-May-2026 at 10:11:57.099, UTC+4, Batumi, Sunday;
	This is OpenGL viewport related  procedures wrapper unit test adapter interface declaration file.
*/
#include "test_case_$p$.viewport.h"

namespace test { namespace open_gl { namespace procs {
namespace ver_1_1 {

	__class (c_viewport) {
	public:
		 c_viewport (void) = default; c_viewport (const c_viewport&) = delete; c_viewport (c_viewport&&) = delete;
		~c_viewport (void) = default;

		__method (Get_Params);
		__method (Is_valid);
		__method (Set_Params);

	private:
		c_viewport& operator = (const c_viewport&) = delete; c_viewport& operator = (c_viewport&&) = delete;
	};

}}}}

#endif/*_TEST_ADAP_$P$_VIEWPORT_H_INCLUDED*/