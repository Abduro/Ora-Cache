/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Dec-2025 at 10:50:26.070, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL drawable components' interface implementation file;
*/
#include "view.grid.h"
#include "gl_renderer.h"
#include "gl_procs_surface.h"
#include "gl_procs_light.h"

using namespace ::open_gl::views;
using namespace ::ex_ui::color::rgb;
using namespace ::open_gl::procs::matrix::ver_1_1;

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl {

	class CDraw_Helper {
	public:
		CDraw_Helper (void) = default; CDraw_Helper (const CDraw_Helper&) = delete; CDraw_Helper (CDraw_Helper&&) = delete; ~CDraw_Helper (void) = default;

		err_code Draw_Arb (CError& _error) {
			_error;
			err_code n_result = __s_ok;

			using e_line = procs::CPrimitives::e_line;
#if (0)
			if (__failed(::__get_attr_mod_procs().Modify_f4(0, this->Clr().Get_r(), this->Clr().Get_g(), this->Clr().Get_b(), this->Clr().Get_a()))) {
				this->m_error = ::__get_attr_mod_procs().Error();
				__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req)); // no return by this error;
			}
#endif
			vertex::CArrObject& vao = ::Get_renderer().Scene().ArrObjects().Get(e_object::e_grid); vao;
			const CVertArray& vexes = ::Get_renderer().Scene().ArrObjects().Get(e_object::e_grid).VertArray();

			if (vexes.Is_valid() == false)
				return n_result = vexes.Error();

			CProgram& prog = ::Get_renderer().Scene().Progs().Get(e_object::e_grid);
			// (1) gets the program in use;
			if (__failed(prog.Use())) {
				__trace_err_2(_T("%s;\n"), (_pc_sz) prog.Error().Print(TError::e_print::e_req));
				return _error = prog.Error();
			}
			// (2) gets the vertex array in bound state;
			if (__failed(vao.Bind())) {
				__trace_err_2(_T("%s;\n"), (_pc_sz) vao.Error().Print(TError::e_print::e_req));
				return _error = vao.Error();
			}
			// (3) draws the grid lines;
			if (__failed(::__get_render_procs().DrawArrays(prog.Id().Get(), (uint32_t) e_line::e_lines, 0, vexes.Count()))) {
				_error = ::__get_render_procs().Error();
				__trace_err_2(_T("%s;\n"), (_pc_sz) _error.Print(TError::e_print::e_req)); // no return by this error;
			}
			// (4) gets the vertex array in unbound state;
			if (__failed(vertex::CArrObject::Unbind(_error))) {
				__trace_err_2(_T("%s;\n"), (_pc_sz) _error.Print(TError::e_print::e_req));
			}
			// (5) gets the program in unused state;
			if (__failed(CProgram::Unused(_error))) {
				__trace_err_2(_T("%s;\n"), (_pc_sz) _error.Print(TError::e_print::e_req));
			}
			return n_result;
		}
		err_code Draw_Base (CGrid& _grid, CError& _error) {
			_grid; _error << __s_ok; // no check error this time;

			const float f_cells =  1.0f;
			const float f_step  =  0.1f;

			LtToggle(false);

			// to-do: all functions being called must be moved to procedure loader/wrapper project;
			
			::glLineWidth(1.0f); // https://learn.microsoft.com/en-us/windows/win32/opengl/gllinewidth ;
			::glBegin(GL_LINES); // https://learn.microsoft.com/en-us/windows/win32/opengl/glbegin ;

			const CPers& pers = _grid.Pers();
			const ex_ui::color::rgb::CFloat& clr = pers.Line().Clr();
			::glColor3f(clr.Get_r(), clr.Get_g(), clr.Get_b()); // https://learn.microsoft.com/en-us/windows/win32/opengl/glcolor3f ;
#if (0)
			uint32_t u_iter = 0;
			for (float i_ = 0.0f; i_ < f_cells; i_ += f_step) {
				// grid lines parallel to X-axis;
				if (u_iter < _grid.Pers().Grid().Rows()) {
				::glVertex3f(-f_cells,  i_, 0.0f); // https://learn.microsoft.com/en-us/windows/win32/opengl/glvertex3f ;
				::glVertex3f( f_cells,  i_, 0.0f);
				::glVertex3f(-f_cells, -i_, 0.0f);
				::glVertex3f( f_cells, -i_, 0.0f);
				}
				// grid lines parallel to Y-axis;
				if (u_iter < _grid.Pers().Grid().Cols()) {
				::glVertex3f( i_, -f_cells, 0.0f);
				::glVertex3f( i_,  f_cells, 0.0f);
				::glVertex3f(-i_, -f_cells, 0.0f);
				::glVertex3f(-i_,  f_cells, 0.0f);
				}
				u_iter += 1;
			}
#else
			CStack stack;
			stack.Push();

			using namespace ::open_gl::views::grid;
			CLayout& layout = _grid.Layout();
			const lines_t& lines = layout.Calc(); // it is supposed the grid rectangle is set;

			for (uint32_t i_ = 0; i_ < lines.size(); i_++) {
				const s_line_2d& line = lines.at(i_);

				::glVertex2f(line.Begin().m_x, line.Begin().m_y);
				::glVertex2f(line.End().m_x, line.End().m_y);
			}
#endif
			::glEnd(); // ::https://learn.microsoft.com/en-us/windows/win32/opengl/glend ;
			stack.Pop();

			return _error;
		}

	private:
		CDraw_Helper& operator = (const CDraw_Helper&) = delete; CDraw_Helper& operator = (CDraw_Helper&&) = delete;
	};

}}}}
using namespace ex_ui::draw::open_gl::_impl;

#pragma region cls::CGrid {}

CGrid:: CGrid (void) : m_layout(m_pers) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; /*this->Default(); this->Clr().Get(e_object::e_grid);*/ }
CGrid::~CGrid (void) {}

const
Color_f& CGrid::Clr (void) const { return this->m_color; }
Color_f& CGrid::Clr (void)       { return this->m_color; }

err_code CGrid::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;
	this->m_pers.Load(); if (this->m_pers.Error()) this->m_error = this->m_pers.Error(); return this->Error();
}
err_code CGrid::Destroy (void) {
	this->m_error <<__METHOD__<<__s_ok;
	this->m_pers.Save(); if (this->m_pers.Error()) this->m_error = this->m_pers.Error(); return this->Error();
}

err_code CGrid::Draw (void) {

	if (::Get_version().Is_base() || true)
	return CDraw_Helper().Draw_Base(*this, this->m_error);
	else
	return CDraw_Helper().Draw_Arb(this->m_error);
}

TError&  CGrid::Error (void) const { return this->m_error; }
const
CLayout& CGrid::Layout (void) const { return this->m_layout; }
CLayout& CGrid::Layout (void)       { return this->m_layout; }
const
CString& CGrid::Name (void) const { return this->m_name; }
bool     CGrid::Name (_pc_sz _p_name) {
	const bool b_changed = 0 != this->Name().CompareNoCase(_p_name); if (b_changed) this->m_name = _p_name; return b_changed;
}

const
CPers&   CGrid::Pers (void) const { return this->m_pers; }
CPers&   CGrid::Pers (void)       { return this->m_pers; }

#pragma endregion