/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Jan-2026 at 13:01:54.936, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL vertex buffer object wrapper unit test adapter interface implementation file.
*/
#include "ebo_test_$d$.buffer.h"

using namespace ebo::boo::test::open_gl::draw;

#pragma region cls::c_vert_dat{}

c_vert_buf::c_vert_buf (void) {}

void c_vert_buf::Size (void) {

	CVertBuffer buffer; // no draw target is required yet;
	buffer.Size();

	_out()();
	_out()(false);
}

#pragma endregion