/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-May-2026 at 11:57:20.177, UTC+4, Batumi, Sunday;
	This is OpenGL tutorials' version info uint test adapter interface implementation file;
*/
#include "test_adap_$d$.ver.h"

using namespace test::open_gl;

#pragma region cls::c_version{}

void c_version::Load (void) {
	CTstVersion().Load(); _out()();
}

#pragma endregion