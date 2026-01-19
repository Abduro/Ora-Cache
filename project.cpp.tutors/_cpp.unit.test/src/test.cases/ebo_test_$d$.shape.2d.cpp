/*
	Created by Tech_dog (eb0ntrop@gmail.com) on 19-Jan-2026 at 23:24:33.762, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL 2d shape wrapper unit test adapter interface implementation file.
*/
#include "ebo_test_$d$.shape.2d.h"

using namespace ebo::boo::test::open_gl::draw;

#pragma region cls::c_tria_2d{}

c_tria_2d::c_tria_2d (void) : m_pipe(e_object::e_tria) {}

const
TPipe& c_tria_2d::operator ()(void) const { return this->m_pipe; }
TPipe& c_tria_2d::operator ()(void)       { return this->m_pipe; }

#pragma endregion