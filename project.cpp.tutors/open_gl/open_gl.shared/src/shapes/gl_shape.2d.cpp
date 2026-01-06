/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Oct-2025 at 15:29:58.463, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL generic 2D shape wrapper interface implementation file;
*/
#include "gl_shape.2d.h"
#include "gl_renderer.h"
#include "shared.preproc.h"

#include "gl_procs_surface.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::shapes;

namespace ex_ui { namespace draw { namespace open_gl {namespace _impl_4 {}}}}
using namespace _impl_4;

CTriangle:: CTriangle (void) : CShape() { CString cs_cls = TString().Format(_T("%s::%s"), CShape::m_error.Class(), (_pc_sz)__CLASS__);

	CShape::Target(e_object::e_tria);
	CShape::m_prim_mode = (uint32_t) procs::CPrimitives::e_triangle::e_triangles;
	CShape::m_error.Class(cs_cls, false);

	TRenderer& renderer  = ::Get_renderer();
	vertex::CArrObject& vao = renderer.Scene().ArrObjects().Get(e_object::e_tria);
	CVertArray& vert_arr = vao.VertArray();

	if (__failed(vert_arr.Count(CShape::n_min_vertex_count ))) {
		CShape::m_error = vert_arr.Error();
		__trace_err_2(_T("%s;\n"), (_pc_sz) CShape::Error().Print(TError::e_print::e_req));
	}
	else CShape::m_error <<__s_ok;
}
CTriangle::~CTriangle (void) {}
// ToDo: the control of getting the element by the index must be made in data container, for this case in CVertArray;
const
CVertex&    CTriangle::A (void) const { return CShape::VertArray().Get(e_vertices::e_a); }
CVertex&    CTriangle::A (void)       { return CShape::VertArray().Get(e_vertices::e_a); }
const
CVertex&    CTriangle::B (void) const { return CShape::VertArray().Get(e_vertices::e_b); }
CVertex&    CTriangle::B (void)       { return CShape::VertArray().Get(e_vertices::e_b); }
const
CVertex&    CTriangle::C (void) const { return CShape::VertArray().Get(e_vertices::e_c); }
CVertex&    CTriangle::C (void)       { return CShape::VertArray().Get(e_vertices::e_c); }

err_code    CTriangle::Draw (void) {
	CShape::m_error <<__METHOD__<<__s_ok;

	TRenderer& renderer  = ::Get_renderer();
	vertex::CArrObject& vao = renderer.Scene().ArrObjects().Get(e_object::e_tria);
	CVertArray& vert_arr = vao.VertArray();

	if (vert_arr.Is_valid() == false)
		return CShape::m_error = vert_arr.Error();

	CProgram& prog = renderer.Scene().Progs().Get(CShape::Target());

	if (false == prog.Id().Is_valid()) {
		CShape::m_error << __e_inv_arg = TString().Format(_T("'_u_prog_id' (%u) is invalid"), prog.Id().Get());
		__trace_err_2(_T("%s;\n"), (_pc_sz) CShape::Error().Print(TError::e_print::e_req));
		return CShape::m_error;
	}

	// (1) gets the program in use;
	if (__failed(prog.Use())) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) prog.Error().Print(TError::e_print::e_req));
		return CShape::m_error = prog.Error();
	}
	// (2) gets the vertex array in bound state;
	if (__failed(vao.Bind())) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) vao.Error().Print(TError::e_print::e_req));
		return CShape::m_error = vao.Error();
	}
	// (3) draws the triangle shape;
	if (__failed(::__get_render_procs().DrawArrays(prog.Id().Get(), (uint32_t) CShape::Primitive(), 0, vert_arr.Count()))) {
		CShape::m_error = ::__get_render_procs().Error();
		__trace_err_2(_T("%s;\n"), (_pc_sz) CShape::Error().Print(TError::e_print::e_req)); // no return by this error;
	}
	// (4) gets the vertex array in unbound state;
	if (__failed(vertex::CArrObject::Unbind(this->m_error))) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) CShape::Error().Print(TError::e_print::e_req));
	}
	// (5) gets the program in unused state;
	if (__failed(CProgram::Unused(this->m_error))) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) CShape::Error().Print(TError::e_print::e_req));
	}

	return CShape::Error();
}

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

bool  CTriangle::Is_valid (void) const { return ::Get_renderer().Scene().ArrObjects().Get(e_object::e_tria).VertArray().Is_valid(); }

err_code CTriangle::Update (void) {
	CShape::m_error <<__METHOD__<<__s_ok;

	TRenderer& renderer  = ::Get_renderer();
	vertex::CArrObject& vao = renderer.Scene().ArrObjects().Get(e_object::e_tria);
	CVertArray& vert_arr = vao.VertArray();

	if (__failed(vert_arr.Update())) {
		CShape::m_error = vert_arr.Error();
		__trace_err_2(_T("%s;\n"), (_pc_sz) CShape::Error().Print(TError::e_print::e_req)); return CShape::Error();
	}
	if (__failed(vao.SetData(vert_arr.Data_ref()))) {
		CShape::m_error = vao.Error();
		__trace_err_2(_T("%s;\n"), (_pc_sz) CShape::Error().Print(TError::e_print::e_req));
	}
	else __trace_info_2(_T("vertices' update completed;\n"));

	return CShape::Error();
}

TTriangle& ::Get_Tria_2d (void) {
	static TTriangle tria_2d;
	return tria_2d;
}