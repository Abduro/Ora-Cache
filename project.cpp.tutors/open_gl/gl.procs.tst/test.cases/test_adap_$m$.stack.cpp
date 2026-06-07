/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Mar-2026 at 09:29:52.165, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL math lib matrix stack uint test adapter interface implementation file; 
*/
#include "test_adap_$m$.stack.h"

using namespace test::open_gl::ver_1_1;

#pragma region cls::c_stk_mode{}

void c_stk_mode::Get (void) {
	CTstMode().Get(); _out()(); 
}
void c_stk_mode::Set (void) {

	CTstMode mode(true);
	mode.Set(e_stk_mode::e_project);
	_out()();
}

#pragma endregion
#pragma region cls::c_mat_stack{}

void c_mat_stack::Get (void) {
	_out()();
}

void c_mat_stack::Pop (void) {
	_out()();
}

void c_mat_stack::Push (void) {
	_out()();
}

#pragma endregion