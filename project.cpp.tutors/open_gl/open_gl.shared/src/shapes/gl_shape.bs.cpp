/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Oct-2025 at 22:08:22.288, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL generic 2D/3D shape wrapper interface implementation file;
*/
#include "gl_shape.bs.h"
#include "gl_shape.2d.h"
#include "gl_renderer.h"

#include "shared.preproc.h"
#include "gl_procs_surface.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::shapes;

namespace ex_ui { namespace draw { namespace open_gl {namespace _impl_3 { void __warning_lnk_4221 (void) {}

CShape inv_shape;

}}}}

#pragma region cls::CShape{}
CShape:: CShape (void) : m_prim_mode((uint32_t)procs::CPrimitives::e_others::e_points) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CShape::~CShape (void) {}

_pc_sz   CShape::Class (void) { CString cs_cls = __CLASS__; return (_pc_sz) cs_cls; }
err_code CShape::Draw  (void) { return __e_not_impl; }
TError&  CShape::Error (void) const { return this->m_error; }

err_code CShape::Prepare (void) { return __e_not_impl; }
uint32_t CShape::Primitive (void) const { return this->m_prim_mode; }
const
CVertArray&  CShape::VertArray (void) const { return ::Get_renderer().Scene().ArrObjects().Get(CPipeline::Target()).VertArray(); }
CVertArray&  CShape::VertArray (void)       { return ::Get_renderer().Scene().ArrObjects().Get(CPipeline::Target()).VertArray(); }

#pragma endregion
#pragma region cls::CShape_enum{}

CShape_enum:: CShape_enum (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CShape_enum::~CShape_enum (void) {}

TError& CShape_enum::Error (void) const { return this->m_error; }

const
CShape& CShape_enum::Get (const e_object _object) const { if (e_object::e_tria == _object) return ::Get_Tria_2d(); return _impl_3::inv_shape; }
CShape& CShape_enum::Get (const e_object _object)       { if (e_object::e_tria == _object) return ::Get_Tria_2d(); return _impl_3::inv_shape; }
const
CShape& CShape_enum::Ref (const uint32_t _ndx) const { if (e_object::e_tria == _ndx) return ::Get_Tria_2d(); return _impl_3::inv_shape; }
CShape& CShape_enum::Ref (const uint32_t _ndx)       { if (e_object::e_tria == _ndx) return ::Get_Tria_2d(); return _impl_3::inv_shape; }

TShapes&  ::Get_shapes (void) {
	static TShapes shapes;
	return shapes;
}

#pragma endregion