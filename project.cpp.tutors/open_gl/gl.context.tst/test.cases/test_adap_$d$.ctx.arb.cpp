/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-May-2026 at 09:37:41.495, UTC+4, Batumi, Monday;
	This is OpenGL draw rendering/graphics context wrapper uint test adapter interface implementation file;
*/
#include "test_adap_$d$.ctx.arb.h"

using namespace test::open_gl::context::arb;

#pragma region cls::c_ctx{}

void c_ctx::Graphics (void) {
	
	CTstGraph graph;

	graph.Create();
	graph.Delete();

	_out()();
}

#pragma endregion