/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-Apr-2026 at 08:25:48.325, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL API procedure loader wrapper unit test adapter implementation declaration file.
*/
#include "test_adap_$d$.procs.h"

using namespace test::draw::open_gl;

#pragma region cls::c_proc_ext{}

void c_proc_ext::Load (void) {
	CTstProcExt().Load(); _out()();
}

void c_proc_ext::Unload (void) {
	CTstProcExt().Unload(); _out()();
}

#pragma endregion;