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

using CDefaults = CShape_enum::CDefaults;

namespace ex_ui { namespace draw { namespace open_gl {namespace _impl_3 { void __warning_lnk_4221 (void) {}
CShape inv_shape;
}}}}

#pragma region cls::CDefaults{}

CDefaults::CDefaults (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError& CDefaults::Error (void) const { return this->m_error; }

err_code CDefaults::SetTo (const e_object _target) {
	_target;
	this->m_error <<__METHOD__<<__s_ok;
	switch (_target) {
	case e_object::e_tria: {
		CTriangle& tria = ::Get_Tria_2d();
		// (4) sets vertex position and color attributes of the triangle shape;
		// (4.a) sets vertex colors;
		tria.A().Attrs().Clr().Set(1.0f, 0.0f, 0.0f, 1.0f);
		tria.B().Attrs().Clr().Set(0.0f, 1.0f, 0.0f, 1.0f);
		tria.C().Attrs().Clr().Set(0.0f, 0.0f, 1.0f, 1.0f);

		// (4.b) sets vertex positions;
		tria.A().Attrs().Pos().Set(+0.0f, +0.5f);
		tria.B().Attrs().Pos().Set(-0.5f, -0.5f);
		tria.C().Attrs().Pos().Set(+0.5f, -0.5f);

		if (__failed(tria.Update())) { this->m_error = tria.Error(); } // if an error occurs, the method prints it itself;
	} break;
	default:
		this->m_error <<(err_code)TErrCodes::eData::eUnsupport = TString().Format(_T("#__e_type: defaults for '%s' not supported"), TPipe::To_str(_target));
	}

	return this->Error();
}

#pragma endregion
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

const
CDefaults& CShape_enum::Defaults (void) const { return this->m_defs; }
CDefaults& CShape_enum::Defaults (void)       { return this->m_defs; }     

TError& CShape_enum::Error (void) const { return this->m_error; }

const
CShape& CShape_enum::Get (const e_object _object) const { if (e_object::e_tria == _object) return ::Get_Tria_2d(); this->m_error <<__METHOD__<<__e_inv_arg = _T("Invalid target object"); return _impl_3::inv_shape; }
CShape& CShape_enum::Get (const e_object _object)       { if (e_object::e_tria == _object) return ::Get_Tria_2d(); this->m_error <<__METHOD__<<__e_inv_arg = _T("Invalid target object"); return _impl_3::inv_shape; }
const
CShape& CShape_enum::Ref (const uint32_t _ndx) const { if (e_object::e_tria == _ndx) return ::Get_Tria_2d(); this->m_error <<__METHOD__<<__e_inv_arg = TString().Format(_T("Invalid index (%u)"), _ndx); return _impl_3::inv_shape; }
CShape& CShape_enum::Ref (const uint32_t _ndx)       { if (e_object::e_tria == _ndx) return ::Get_Tria_2d(); this->m_error <<__METHOD__<<__e_inv_arg = TString().Format(_T("Invalid index (%u)"), _ndx); return _impl_3::inv_shape; }

TShapes&  ::Get_shapes (void) {
	static TShapes shapes;
	return shapes;
}

#pragma endregion