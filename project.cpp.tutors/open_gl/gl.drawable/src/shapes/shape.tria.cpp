/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Jun-2026 at 00:56:04.105, UTC+4, Batumi, Friday;
	This is triangle drawable shape interface implementation file.
*/
#include "shape.tria.h"
#include "gl_procs_light.h"

using namespace ::open_gl::shapes;

#pragma region cls::CTria{}

CTria::CTria (void) : TBase() {}

void   CTria::Draw (void) {

//	CMode mode;
//	if (__failed(mode.Set(e_stk_mode::e_modelview))) { return; }

//	CMatrix mat_4x4;
//	if (__failed(mat_4x4.To_self())) { return; }

	LtToggle(false);

	CStack stack;

	const bool b_moved = TBase::Move().Is_changed();
	if (b_moved) {
		stack.Push();

		COpers opers;
		const f_set_3 f_move = /*{1.0f, 1.0f, 1.0f}*/ TBase::Move().Get();
		if (__failed(opers.Translate(f_move.at(0), f_move.at(1), f_move.at(2)))) {
			__trace_err_ex_2(opers.Error());
		}
	}

	stack.Push();

	::glBegin(GL_TRIANGLES);

	for (uint32_t i_ = 0; i_ < (*this)().size(); i_++) {
		const CVertex& vert = (*this)().at(i_);

		::glColor3f (vert.Color().at(0), vert.Color().at(1), vert.Color().at(2));
		::glVertex3f(vert.Point().at(0), vert.Point().at(1), vert.Point().at(2));
	}
	::glEnd();
	if (b_moved)
	stack.Pop();
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