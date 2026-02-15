#ifndef _EBO_TEST_$M$_VIRT_CAM_H_INCLUDED
#define _EBO_TEST_$M$_VIRT_CAM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Feb-2026 at 22:05:26.280, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL math lib virtual camera unit test adapter interface declaration file; 
*/
#include "test_case_$m$.virt.cam.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {

	__class (c_virt_cam) {
	public:
		c_virt_cam (void); ~c_virt_cam (void) = default;

		__method (Create);  // creates virtual draw camera in order to check its initial state;
	};

}}}}}

#endif/*_EBO_TEST_$M$_VIRT_CAM_H_INCLUDED*/