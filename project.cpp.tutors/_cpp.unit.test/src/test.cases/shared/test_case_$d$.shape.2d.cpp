/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Jan-2026 at 13:39:05.751, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL 2D shape wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$d$.shape.2d.h"

using namespace ebo::boo::test::open_gl::draw;

#if (0) // the shape cache is used instead of this class;
#pragma region cls::CTria{}

C3angle::C3angle (void) : TShape() { TShape::m_error >>__CLASS__; }

err_code C3angle::Init (void) {
	TShape::m_error <<__METHOD__<<__s_ok;

	// (4) sets vertex position and color attributes of the triangle shape;
	// (4.a) sets vertex colors;
	TShape::A().Attrs().Clr().Set(1.0f, 0.0f, 0.0f, 1.0f);
	TShape::B().Attrs().Clr().Set(0.0f, 1.0f, 0.0f, 1.0f);
	TShape::C().Attrs().Clr().Set(0.0f, 0.0f, 1.0f, 1.0f);

	// (4.b) sets vertex positions;
	TShape::A().Attrs().Pos().Set(+0.0f, +0.5f);
	TShape::B().Attrs().Pos().Set(-0.5f, -0.5f);
	TShape::C().Attrs().Pos().Set(+0.5f, -0.5f);

	if (__failed(TShape::Update())) { // if an error occurs, the method prints it itself;
	}
	return TShape::Error();
}

#pragma endregion
#endif