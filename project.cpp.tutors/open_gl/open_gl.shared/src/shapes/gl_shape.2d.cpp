/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Oct-2025 at 15:29:58.463, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL generic 2D shape wrapper interface implementation file;
*/
#include "gl_shape.2d.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::shapes;

namespace ex_ui { namespace draw { namespace open_gl {namespace _impl_4 {}}}}
using namespace _impl_4;

CTriangle:: CTriangle (void) : CShape() { CString cs_cls = TString().Format(_T("%s::%s"), CShape::m_error.Class(), (_pc_sz)__CLASS__);
	CShape::m_error.Class(cs_cls, false);
	if (__failed(CShape::m_vertices.Count(n_min_vertex_count)))
		CShape::m_error = CShape::m_vertices.Error(); else CShape::m_error <<__s_ok;
	if (CShape::Error()) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) CShape::Error().Print(TError::e_print::e_req));
	}
}
CTriangle::~CTriangle (void) {}
// ToDo: the control of getting the element by the index must be made in data container, for this case in CVertArray;
const
CVertex&    CTriangle::A (void) const { return CShape::m_vertices.Get(e_vertices::e_a); }
CVertex&    CTriangle::A (void)       { return CShape::m_vertices.Get(e_vertices::e_a); }
const
CVertex&    CTriangle::B (void) const { return CShape::m_vertices.Get(e_vertices::e_b); }
CVertex&    CTriangle::B (void)       { return CShape::m_vertices.Get(e_vertices::e_b); }
const
CVertex&    CTriangle::C (void) const { return CShape::m_vertices.Get(e_vertices::e_c); }
CVertex&    CTriangle::C (void)       { return CShape::m_vertices.Get(e_vertices::e_c); }

const
CVertex&    CTriangle::Get (const e_vertices e_vert) const {
	e_vert;
	if (false) {}
	else if (e_vertices::e_a == e_vert) return this->A();
	else if (e_vertices::e_b == e_vert) return this->B();
	else return this->C();
}
CVertex&    CTriangle::Get (const e_vertices e_vert) {
	e_vert;
	if (false) {}
	else if (e_vertices::e_a == e_vert) return this->A();
	else if (e_vertices::e_b == e_vert) return this->B();
	else return this->C();
}

bool  CTriangle::Is_valid (void) const { return CShape::m_vertices.Is_valid(); }

err_code CTriangle::Update (void) {
	CShape::m_error <<__METHOD__<<__s_ok;

	if (__failed(CShape::m_vertices.Update())) {
		CShape::m_error = CShape::m_vertices.Error();
	}
	else __trace_info_2(_T("vertices' update completed;\n"));

	return CShape::Error();
}