/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Jun-2026 at 00:56:04.105, UTC+4, Batumi, Friday;
	This is triangle drawable shape interface implementation file.
*/
#include "shape.tria.h"

using namespace ::open_gl::shapes;

#pragma region cls::CTria{}

CTria::CTria (void) {}

void   CTria::Draw (void) {

//	CMode mode;
//	if (__failed(mode.Set(e_stk_mode::e_modelview))) { return; }

//	CMatrix mat_4x4;
//	if (__failed(mat_4x4.To_self())) { return; }

	CStack stack;
	stack.Push(/*mat_4x4.Data()*/);

	::glBegin(GL_TRIANGLES);

	for (uint32_t i_ = 0; i_ < (*this)().size(); i_++) {
		const CVertex& vert = (*this)().at(i_);

		::glColor3f (vert.Color().at(0), vert.Color().at(1), vert.Color().at(2));
		::glVertex3f(vert.Point().at(0), vert.Point().at(1), vert.Point().at(2));
	}

	::glEnd();
	stack.Pop();
}

void   CTria::Format (void) {

	for (uint32_t i_ = 0; i_ < (*this)().size(); i_++) {
		CVertex& vert = (*this)().at(i_);
		if (0 == i_) { vert.Point() = { 0.0f,  0.5f, 0.0f}; vert.Color()  = {1.0f, 0.0f, 0.0f}; }
		if (1 == i_) { vert.Point() = {-0.5f, -0.5f, 0.0f}; vert.Color()  = {0.0f, 1.0f, 0.0f}; }
		if (2 == i_) { vert.Point() = { 0.5f, -0.5f, 0.0f}; vert.Color()  = {0.0f, 0.0f, 1.0f}; }
	}
}

const
f_tria_vert& CTria::operator ()(void) const { return this->m_vert; }
f_tria_vert& CTria::operator ()(void)       { return this->m_vert; }

#pragma endregion;