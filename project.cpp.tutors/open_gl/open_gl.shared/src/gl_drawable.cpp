/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Dec-2025 at 10:50:26.070, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL drawable components' interface implementation file;
*/
#include "gl_drawable.h"
#include "gl_renderer.h"
#include "gl_viewport.h"
#include "gl_uniform.h"
#include "gl_grid_layout.h"

#include "shared.theme.h"
#include "sys.registry.h"

#include "gl_procs_surface.h"
#include "gl_procs_uniform.h"

#include "color._defs.h"

using namespace open_gl::views;
using namespace ex_ui::color::rgb;

#pragma region cls::CBkgnd{}

using e_clear_ops = ex_ui::draw::open_gl::procs::CEraser::e_clear_ops;

CBkgnd:: CBkgnd (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CBkgnd::~CBkgnd (void) {}

err_code CBkgnd::Draw (void) {
	this->m_error <<__METHOD__<<__s_ok;

	// (1) gets the background color from the registry; the background is drawn in anyway, regardless of renderer drawable object settings;
	const v_color& clr_bkgnd = ::Get_theme().Bkgnd_flt();
	if (4 > clr_bkgnd.size()) {
		return this->m_error << __e_inv_arg = TString().Format(_T("#__e_inv_arg: the float color vector size = %u"), clr_bkgnd.size());
	}
	// (1.a) sets the color for using by background eraser;
	if (__failed(::__get_eraser_procs().Clr(clr_bkgnd.at(0), clr_bkgnd.at(1), clr_bkgnd.at(2), clr_bkgnd.at(3)))) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) ::__get_eraser_procs().Error().Print(TError::e_print::e_req));
		return this->m_error = ::__get_eraser_procs().Error();
	}
	/* setting e_clear_ops::e_depth for clean operation requires:
	...ensure depth testing is enabled (glEnable(GL_DEPTH_TEST)) and clear the depth buffer, at the beginning of each frame to correctly handle overlapping geometry...
	*/
#if (0)
	using e_caps = TCapsProcs::e_caps;
	if (__failed(::__get_caps_procs().Enable(true, e_caps::e_depth_tst))) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) ::__get_caps_procs().Error().Print(TError::e_print::e_req));
		return this->m_error = ::__get_caps_procs().Error();
	}
#endif
	// (1.b) applies the background color; the same color is also applied to the console of the debug output;
	if (__failed(::__get_eraser_procs().All(e_clear_ops::e_color|e_clear_ops::e_depth))) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) ::__get_eraser_procs().Error().Print(TError::e_print::e_req));
		return this->m_error = ::__get_eraser_procs().Error();
	}

	return this->Error();
}

TError&  CBkgnd::Error (void) const { return this->m_error; }

#pragma endregion
#pragma region cls::CClr_flt{}

CClr_flt:: CClr_flt (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }
CClr_flt::~CClr_flt (void) {}

TError&  CClr_flt::Error (void) const { return this->m_error; }
#if (0)
err_code CClr_flt::Get (const e_object _target) {
	_target;
	this->m_error <<__METHOD__<<__s_ok;

	CString cs_key;   // registry key path;
	CString cs_name;  // registry key value name;

	if (e_object::e_grid == _target) {
		using CRegGrid = shared::sys_core::storage::route::CGrid;
		CRegGrid& reg_grid = ::Get_reg_router().Viewport().Grid();

		cs_key = reg_grid.Root(); cs_name = reg_grid.Clr_name();
	}

	if (cs_key.IsEmpty())
		return this->m_error <<__e_inv_arg = TString().Format(_T("#__e_inv_val: the object (%u) is unsupported"), _target);

	TRegKeyEx reg_key;
	CString cs_clr = reg_key.Value().GetString((_pc_sz) cs_key, (_pc_sz) cs_name);
	if (reg_key.Error()) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) reg_key.Error().Print(TError::e_print::e_req));
	}

	TBase::Set((rgb_color)CHex((_pc_sz) cs_clr)); // alpha channel is set to 0 (zero), but it is not important for because it is not taken into account yet;
#if defined(_DEBUG)
	if (e_object::e_grid == _target) {
	__trace_info_2(_T("grid line color: {%s};\n"), (_pc_sz) TBase::Print(e_print::e_req)); 
	}
#endif
	return this->Error();
}
#endif
err_code CClr_flt::Set (const float _r, const float _g, const float _b, const float _a) {
	_r; _g; _b; _a;
	(*this)()[e_rgba::r] = (0.0f > _r ? 0.0f : (1.0f < _r ? 1.0f : _r));
	(*this)()[e_rgba::g] = (0.0f > _g ? 0.0f : (1.0f < _g ? 1.0f : _g));
	(*this)()[e_rgba::b] = (0.0f > _b ? 0.0f : (1.0f < _b ? 1.0f : _b));
	(*this)()[e_rgba::a] = (0.0f > _a ? 0.0f : (1.0f < _a ? 1.0f : _a));
	return __s_ok;
}

err_code CClr_flt::Set (const uint8_t _r, const uint8_t _g, const uint8_t _b, const uint8_t _a) {
	_r; _g; _b; _a;
	(*this)()[e_rgba::r] = CConvert::ToFloat(_r);
	(*this)()[e_rgba::g] = CConvert::ToFloat(_g);
	(*this)()[e_rgba::b] = CConvert::ToFloat(_b);
	(*this)()[e_rgba::a] = CConvert::ToFloat(_a);
	return __s_ok;
}

err_code CClr_flt::Set (const CString& _cs_clr) {
	this->m_error >>__CLASS__<<__METHOD__<<__s_ok;
	if (_cs_clr.IsEmpty())
		return this->m_error <<__e_inv_arg = _T("#__e_inv_arg: input color string is empty");

	TBase::Set((rgb_color)CHex((_pc_sz)_cs_clr)); // alpha channel is set to 0 (zero), but it is not important for because it is not taken into account yet;
#if defined(_DEBUG)
//	if (e_object::e_grid == _target) {
//	__trace_info_2(_T("grid line color: {%s};\n"), (_pc_sz) TBase::Print(e_print::e_req)); 
//	}
#endif
	return this->Error();
}

const
rgb::CFloat&  CClr_flt::operator ()(void) const { return (TBase&)*this; }
rgb::CFloat&  CClr_flt::operator ()(void)       { return (TBase&)*this; }    

#pragma endregion

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

			// to-do: all functions being called must be moved to procedure loader project;
			
			::glLineWidth(1.0f); // https://learn.microsoft.com/en-us/windows/win32/opengl/gllinewidth ;

			::glDisable(GL_LIGHTING); // https://learn.microsoft.com/en-us/windows/win32/opengl/gldisable ;
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
			::glEnable(GL_LIGHTING); // https://learn.microsoft.com/en-us/windows/win32/opengl/glenable ;

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
CClr_flt& CGrid::Clr (void) const { return this->m_color; }
CClr_flt& CGrid::Clr (void)       { return this->m_color; }

err_code CGrid::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;
	this->m_pers.Load(); if (this->m_pers.Error()) this->m_error = this->m_pers.Error(); return this->Error();
}
err_code CGrid::Destroy (void) {
	this->m_error <<__METHOD__<<__s_ok;
	this->m_pers.Save(); if (this->m_pers.Error()) this->m_error = this->m_pers.Error(); return this->Error();
}

err_code CGrid::Draw (void) {

	if (::Get_version().Is_base())
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