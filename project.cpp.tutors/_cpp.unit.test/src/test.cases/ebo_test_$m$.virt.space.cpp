/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Feb-2026 at 12:06:36.319, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL math lib virtual space unit test adapter interface implementation file; 
*/
#include "ebo_test_$m$.virt.space.h"

using namespace ebo::boo::test::open_gl::math;

#pragma region cls::c_axes_dyn{}

c_axes_dyn::c_axes_dyn (void) {}

void c_axes_dyn::Create (void) {
	_out() += CTAxes_Dyn::To_str(TAxes_Dyn()); _out()();
}

#pragma endregion
#pragma region cls::c_axes_fix{}

c_axes_fix::c_axes_fix (void) {}

void c_axes_fix::Create (void) {
	_out() += CTAxes_Fix::To_str(TAxes_Fix()); _out()();
}

#pragma endregion