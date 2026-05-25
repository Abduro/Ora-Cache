/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Jan-2026 at 22:25:17.555, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL tutorials' draw renderer wrapper unit test adapter interface implementation file.
*/
#include "test_adap_$d$.render.h"

using namespace test::open_gl::draw;

#pragma region cls::c_renderer{}

c_renderer::c_renderer (const e_object _target) : m_pipe(_target) {}

void c_renderer::Draw (void) {
	CTstRenderer renderer((*this)()); renderer.Draw(); _out()();
}

const
TPipe& c_renderer::operator ()(void) const { return this->m_pipe; }
TPipe& c_renderer::operator ()(void)       { return this->m_pipe; }

#pragma endregion