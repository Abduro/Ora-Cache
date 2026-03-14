/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Mar-2026 at 10:50:10.607, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL 3D virtual camera view interface implementation file;
*/
#include "virt_view.h"

#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::views;

#pragma region cls::CBase{}

CBase::CBase (void) {}

const
vec_3&    CBase::Angle (void) const { return this->m_angle; }
vec_3&    CBase::Angle (void)       { return this->m_angle; }
const
c_mat4x4& CBase::Get_matrix (void) const { return this->m_mat(); }
c_mat4x4& CBase::Get_matrix (void)       { return this->m_mat(); }
const
vec_3&    CBase::Pos (void) const { return this->m_pos; }
vec_3&    CBase::Pos (void)       { return this->m_pos; }

#pragma endregion
#pragma region cls::CModel{}

CModel::CModel (void) : CBase() {}
const
CModel::CAxes& CModel::Axes (void) const { return this->m_axes; }
CModel::CAxes& CModel::Axes (void)       { return this->m_axes; }

void    CModel::Update (void) {
	CBase::m_mat.Identity();
	CBase::m_mat.On_z(CBase::Angle().z);
	CBase::m_mat.On_y(CBase::Angle().y);
	CBase::m_mat.On_x(CBase::Angle().x);
	CBase::m_mat.Translate(CBase::Pos());
}

#pragma endregion
#pragma region cls::CView{}

CView::CView (void) : CBase() {}
const
CView::CAxes& CView::Axes (void) const { return this->m_axes; }
CView::CAxes& CView::Axes (void)       { return this->m_axes; }

void CView::Update (void) {

	CBase::m_mat.Identity();
	CBase::m_mat.Translate(-CBase::Pos());
	CBase::m_mat.On_x( CBase::Angle().x);
	CBase::m_mat.On_y(-CBase::Angle().y);
	CBase::m_mat.On_z( CBase::Angle().z);
}

const
CWorld& CView::World (void) const { return this->m_world; }
CWorld& CView::World (void)       { return this->m_world; }

#pragma endregion
#pragma region cls::CWorld{}

CWorld::CWorld (void) : CBase() {}
const
CWorld::CAxes& CWorld::Axes (void) const { return this->m_axes; }
CWorld::CAxes& CWorld::Axes (void)       { return this->m_axes; }
const
c_mat4x4& CWorld::Get_model_view (void) const { return CBase::Get_matrix(); }
c_mat4x4& CWorld::Get_model_view (void)       { return CBase::Get_matrix(); }
const
CModel&   CWorld::Model (void) const { return this->m_model; }
CModel&   CWorld::Model (void)       { return this->m_model; }

#pragma endregion