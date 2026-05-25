/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Jan-2026 at 13:01:54.936, UTC+4, Batumi, Saturday;
	This is OpenGL vertex buffer object wrapper unit test adapter interface implementation file.
*/
#include "test_adap_$d$.buffer.h"

using namespace test::open_gl::vertex;

#pragma region cls::c_vert_dat{}


void c_vert_buf::Data (void) {

	CVertBufData buf_dat(e_object::e_tria); buf_dat.Get();
	
	_out()();
	_out()(false);
}

void c_vert_buf::Size (void) {

	CVertBuffer buffer; // no draw target is required yet;
	buffer.Size();

	_out()();
	_out()(false);
}

#pragma endregion