/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Mar-2026 at 21:06:22.537, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL tutorials' trace console unit test adapter interface implementation file; 
*/
#include "ebo_test_$w$.con.h"

using namespace ebo::boo::test::con;

#pragma region cls::c_wrap{}

void c_wrap::Create (void) {

	c_con_wrap wrapper;

	wrapper.Create();
	wrapper.Detach();

	_out()();
}

#pragma endregion