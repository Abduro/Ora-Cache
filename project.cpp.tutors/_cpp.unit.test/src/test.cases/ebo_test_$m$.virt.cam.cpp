/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Feb-2026 at 22:14:27.302, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL math lib virtual camera unit test adapter interface implementation file; 
*/
#include "ebo_test_$m$.virt.cam.h"

using namespace ebo::boo::test::open_gl::math;

#pragma region cls::c_virt_cam{}

c_virt_cam::c_virt_cam (void){}

void c_virt_cam::Create(void) {

	CTVirtCam().Create();
	_out()();
}

#pragma endregion