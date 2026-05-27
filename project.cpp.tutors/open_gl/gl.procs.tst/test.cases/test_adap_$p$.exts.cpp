/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-May-2026 at 23:38:48.888, UTC+4, Batumi, Tuesday;
	This is OpenGL version 1.1 extensions' loading procedures wrapper unit test adapter interface implementation declaration file.
*/
#include "test_adap_$p$.exts.h"

using namespace test::open_gl::procs;

#pragma region cls::c_proc_ext{}

void c_proc_ext::Is_arb (void) {
	CTstProcExt().Is_arb(); _out()();
}

void c_proc_ext::Is_remote (void) {
	CTstProcExt().Is_remote(); _out()();
}

void c_proc_ext::Load (void) {
	CTstProcExt().Load(); _out()();
}

#pragma endregion;