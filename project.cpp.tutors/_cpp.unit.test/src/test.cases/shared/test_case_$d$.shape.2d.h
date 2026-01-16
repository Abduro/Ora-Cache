#ifndef _TEST_CASE_$D$_SHAPE_2D_H_INCLUDED
#define _TEST_CASE_$D$_SHAPE_2D_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Jan-2026 at 13:36:52.511, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL 2D shape wrapper interface declaration file for using in test cases adapters;
*/
#include "ebo_test_$d$.defs.h"
#include "shapes\gl_shape.2d.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {

	using namespace ex_ui::draw::open_gl;
#if (0) // the shape cache is used instead of this class;
	using CTriangle = shapes::CTriangle;

	class C3angle : public CTriangle { typedef CTriangle TShape;
	public:
		C3angle (void); C3angle (const C3angle&) = delete; C3angle (C3angle&&) = delete; ~C3angle (void) = default;

		err_code Init (void); // creates a simple triangle;

	private:
		C3angle& operator = (const C3angle&) = delete; C3angle& operator = (C3angle&&) = delete;
	};
#endif
}}}}}

#endif/*_TEST_CASE_$D$_SHAPE_2D_H_INCLUDED*/