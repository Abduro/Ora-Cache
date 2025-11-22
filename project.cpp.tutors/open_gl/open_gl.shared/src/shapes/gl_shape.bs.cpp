/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Oct-2025 at 22:08:22.288, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL generic 2D/3D shape wrapper interface implementation file;
*/
#include "gl_shape.bs.h"
#include "shared.preproc.h"
#include "procs\gl_procs_surface.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::shapes;

namespace ex_ui { namespace draw { namespace open_gl {namespace _impl_3 { void __warning_lnk_4221 (void) {}}}}}

CShape:: CShape (void) : m_prim_mode((uint32_t)procs::CPrimitives::e_others::e_points) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited; }
CShape::~CShape (void) {}

CString  CShape::Class (void) { return __CLASS__; }

TError&  CShape::Error (void) const { return this->m_error; }

uint32_t CShape::Primitive (void) const { return this->m_prim_mode; }

const
CVertArray&  CShape::Vertices (void) const { return this->m_vertices; }