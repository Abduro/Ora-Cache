/*
	Created by Tech_dog (eb0ntrop@gmail.com) on 15-Jan-2026 at 22:25:17.555, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL tutorials' draw renderer wrapper unit test adapter interface implementation file.
*/
#include "ebo_test_$d$.render.h"

using namespace ebo::boo::test::open_gl::draw;

#pragma region cls::c_renderer{}

c_renderer::c_renderer (void) {}

void c_renderer::Draw (void) {
	CFake_renderer renderer; renderer.Draw();
}

#pragma endregion