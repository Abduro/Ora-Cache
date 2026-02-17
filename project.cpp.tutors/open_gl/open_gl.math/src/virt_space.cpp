/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Feb-2026 at 12:52:29.954, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL 3D virtual camera space interface inplementation file;
*/
#include "virt_space.h"
#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::space;

#pragma region axes::cls::CBase{}

axes::CBase::CBase (void) {}

#pragma endregion
#pragma region axes::cls::CDynamic{}

axes::CDynamic::CDynamic (void) {}
const
vec_3& axes::CDynamic::Get (const e_axes _e_axis) const { return this->m_v_axes[_e_axis]; }
vec_3& axes::CDynamic::Get (const e_axes _e_axis)       { return this->m_v_axes[_e_axis]; }

const vec_3& axes::CDynamic::Fwd (void) const { return this->Get(e_axes::e_fwd); } vec_3& axes::CDynamic::Fwd (void) { return this->Get(e_axes::e_fwd); }
const vec_3& axes::CDynamic::Left (void) const { return this->Get(e_axes::e_left); } vec_3& axes::CDynamic::Left (void) { return this->Get(e_axes::e_left); }
const vec_3& axes::CDynamic::Up (void) const { return this->Get(e_axes::e_up); } vec_3& axes::CDynamic::Up (void) { return this->Get(e_axes::e_up); }

#pragma endregion
#pragma region axes::cls::CFixed{}

axes::CFixed::CFixed (void) {}
const
vec_3& axes::CFixed::Get (const e_axes _e_axis) const { return this->m_v_axes[_e_axis]; }
vec_3& axes::CFixed::Get (const e_axes _e_axis)       { return this->m_v_axes[_e_axis]; }

const vec_3& axes::CFixed::X (void) const { return this->Get(e_axes::e_x_axis); } vec_3& axes::CFixed::X (void) { return this->Get(e_axes::e_x_axis); }
const vec_3& axes::CFixed::Y (void) const { return this->Get(e_axes::e_y_axis); } vec_3& axes::CFixed::Y (void) { return this->Get(e_axes::e_y_axis); }
const vec_3& axes::CFixed::Z (void) const { return this->Get(e_axes::e_z_axis); } vec_3& axes::CFixed::Z (void) { return this->Get(e_axes::e_z_axis); }

#pragma endregion
#pragma region cls::CBase{}

CBase::CBase (void) {}

#pragma endregion
#pragma region cls::CLocal{}

CLocal::CLocal (void) : CBase() {}
const
c_mat4x4& CLocal::Model (void) const { return this->m_model; }
c_mat4x4& CLocal::Model (void)       { return this->m_model; }

#pragma endregion
#pragma region cls::CView{}

CView::CView (void) : CBase() {}
const
CView::CAxes& CView::Axes (void) const { return this->m_axes; }
CView::CAxes& CView::Axes (void)       { return this->m_axes; }
const
c_mat4x4& CView::Get (void) const { return this->m_view; }
c_mat4x4& CView::Get (void)       { return this->m_view; }

#pragma endregion
#pragma region cls::CWorld{}

CWorld::CWorld (void) : CBase() {}
const
CWorld::CAxes& CWorld::Axes (void) const { return this->m_axes; }
CWorld::CAxes& CWorld::Axes (void)       { return this->m_axes; }

#pragma endregion