/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Dec-2025 at 10:50:26.070, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL drawable components' interface implementation file;
*/
#include "gl_drawable.h"
#include "gl_renderer.h"
#include "gl_viewport.h"
#include "gl_uniform.h"

#include "shared.dbg.h"
#include "shared.preproc.h"
#include "shared.theme.h"
#include "sys.registry.h"

#include "gl_procs_surface.h"
#include "gl_procs_uniform.h"

#include "color._defs.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::color::rgb;

#pragma region cls::CBkgnd{}

using e_clear_ops = procs::CEraser::e_clear_ops;

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
	__trace_info_2(_T("grid line color: {%s};\n"), (_pc_sz) TBase::Print(e_print::e_req)); 
#endif
	return this->Error();
}

void CClr_flt::Set (const float _r, const float _g, const float _b, const float _a) {
	_r; _g; _b; _a;
	(*this)()[e_rgba::r] = (0.0f > _r ? 0.0f : (1.0f < _r ? 1.0f : _r));
	(*this)()[e_rgba::g] = (0.0f > _g ? 0.0f : (1.0f < _g ? 1.0f : _g));
	(*this)()[e_rgba::b] = (0.0f > _b ? 0.0f : (1.0f < _b ? 1.0f : _b));
	(*this)()[e_rgba::a] = (0.0f > _a ? 0.0f : (1.0f < _a ? 1.0f : _a));
}

void CClr_flt::Set (const uint8_t _r, const uint8_t _g, const uint8_t _b, const uint8_t _a) {
	_r; _g; _b; _a;
	(*this)()[e_rgba::r] = CConvert::ToFloat(_r);
	(*this)()[e_rgba::g] = CConvert::ToFloat(_g);
	(*this)()[e_rgba::b] = CConvert::ToFloat(_b);
	(*this)()[e_rgba::a] = CConvert::ToFloat(_a);
}

const
rgb::CFloat&  CClr_flt::operator ()(void) const { return (const TBase&)*this; }
rgb::CFloat&  CClr_flt::operator ()(void)       { return (TBase&)*this; }    

#pragma endregion
#pragma region cls::CGrid::CCell{}

using CCell = view::CGrid::CCell;

CCell:: CCell (void) : m_size{0u} {

	using CRegCell = shared::sys_core::storage::CGrid::CCell;
	CRegCell& reg_cell = ::Get_reg_router().Viewport().Grid().Cell();

	TRegKeyEx reg_key;
	m_size.cx = reg_key.Value().GetDword(reg_cell.Root(), (_pc_sz) reg_cell.Name(CRegCell::e_width));
	if (reg_key.Error()) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) reg_key.Error().Print(TError::e_print::e_req));
	}
	m_size.cy = reg_key.Value().GetDword(reg_cell.Root(), (_pc_sz) reg_cell.Name(CRegCell::e_height));
	if (reg_key.Error()) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) reg_key.Error().Print(TError::e_print::e_req));
	}
}

CCell::~CCell (void) {}

uint32_t CCell::H (void) const { return this->m_size.cy; } uint32_t CCell::Height (void) const { return this->H(); }
bool     CCell::H (const uint32_t _u_val) { if (this->Height() != _u_val) { this->m_size.cy = _u_val; return true; } else return false; } bool CCell::Height (const uint32_t _u_val) { return this->H(_u_val); }

bool     CCell::Is_valid (void) const { return this->H() && this->W(); }
bool     CCell::Is_valid (const t_size_u& _u_size, CError& _err) {
	_u_size; _err;
	if (0 == _u_size.cx || 0 == _u_size.cy) {
		_err <<__e_not_inited = TString().Format(_T("#__e_not_init: cell size {w=%u;h=%u} is invalid"), _u_size.cx, _u_size.cy);
	}
	return false == _err;
}

const
t_size_u& CCell::Get (void) const { return this->m_size; }
bool      CCell::Set (const uint32_t _u_width, const uint32_t _u_height) {
	_u_width; _u_height;
	bool b_changed = false;

	if (this->H(_u_height)) b_changed = true;
	if (this->W(_u_width)) b_changed = true;

	return b_changed;
}

uint32_t CCell::W (void) const { return this->m_size.cx; } uint32_t CCell::Width  (void) const { return this->W(); }
bool     CCell::W (const uint32_t _u_val) { if (this->Width()  != _u_val) { this->m_size.cx = _u_val; return true; } else return false; } bool CCell::Width (const uint32_t _u_val) { return this->W(_u_val); }

#pragma endregion

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl {

	typedef ::std::set<uint32_t> t_markers; // it is the marker data type for positioning horizontal and vertical grid dividers/lines in window client area coords;

	class CMarkers {
	private: CMarkers (const CMarkers&) = delete; CMarkers (CMarkers&&) = delete;
	private: CMarkers& operator = (const CMarkers&) = delete; CMarkers& operator = (CMarkers&&) = delete;
	public:
		CMarkers (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; } ~CMarkers (void) = default;

		err_code Count (const t_size_u& _view_size, const t_size_u& _cell_size) {
			_view_size; _cell_size;
			this->m_error <<__METHOD__<<__s_ok;

			if (CViewPort::Is_valid(_view_size, this->m_error) == false) {
				__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
				return this->Error();
			}

			if (false == view::CGrid::CCell::Is_valid(_cell_size, this->m_error)) {
				__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
				return this->Error();
			}

			t_point pt_center = {
				static_cast<long>(_view_size.cx / 2), static_cast<long>(_view_size.cy / 2)
			};

			this->m_x_mrks.insert(pt_center.x);
			this->m_y_mrks.insert(pt_center.y);

			int32_t x_iter = _view_size.cx / 2;

			// (1) marks line x-coords;
			// (1.a) from the center to the left side;
			while (x_iter - (int32_t)_cell_size.cx > 0) { this->m_x_mrks.insert(x_iter -= (int32_t)_cell_size.cx); }
			// (1.b) from the center to the right side;
			x_iter = _view_size.cx / 2;
			while (x_iter + _cell_size.cx < _view_size.cx) { this->m_x_mrks.insert(x_iter += (int32_t)_cell_size.cx); }

			int32_t y_iter = _view_size.cy / 2;

			// (2) marks line y-coords;
			// (2.a) from the center to the top side;
			while (y_iter - (int32_t)_cell_size.cy > 0) { m_y_mrks.insert(y_iter -= (int32_t)_cell_size.cy); }
			// (2.b) from the center to the bottom side;
			y_iter = _view_size.cy / 2;
			while (y_iter + _cell_size.cy < _view_size.cy) { m_y_mrks.insert(y_iter += (int32_t)_cell_size.cy); }

			return this->Error();
		}

		TError& Error (void) const { return this->m_error; }

		const t_markers&  Get_horz (void) const { return this->m_y_mrks; }
		const t_markers&  Get_vert (void) const { return this->m_x_mrks; }

	private:
		CError    m_error;
		t_markers m_x_mrks; // markers of vertical lines by x-axis;
		t_markers m_y_mrks; // markers of horizontal lines by y-axis;
	};

}}}}
using namespace ex_ui::draw::open_gl::_impl;

#pragma region cls::CGrid {}

using CGrid = view::CGrid;

CGrid:: CGrid (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; /*this->Default();*/ this->Clr().Get(e_object::e_grid); }
CGrid::~CGrid (void) {}

const
CCell&  CGrid::Cell (void) const { return this->m_cell; }
CCell&  CGrid::Cell (void)       { return this->m_cell; }

const
CClr_flt& CGrid::Clr (void) const { return this->m_color; }
CClr_flt& CGrid::Clr (void)       { return this->m_color; }

err_code CGrid::Create (void) { this->m_error <<__METHOD__<<__s_ok; return this->Error(); }
err_code CGrid::Destroy (void) { this->m_error <<__METHOD__<<__s_ok; return this->Error(); }

#if (0)
void CGrid::Default (void) {
	this->Clr().Set(0.5f, 0.5f, 0.5f, 1.0f);
	this->Size() = 10.0f;
	this->Step() = 01.0f;
}
#endif

err_code view::CGrid::Draw (void) {
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
		return this->m_error = prog.Error();
	}
	// (2) gets the vertex array in bound state;
	if (__failed(vao.Bind())) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) vao.Error().Print(TError::e_print::e_req));
		return this->m_error = vao.Error();
	}
	// (3) draws the grid lines;
	if (__failed(::__get_render_procs().DrawArrays(prog.Id().Get(), (uint32_t) e_line::e_lines, 0, vexes.Count()))) {
		this->m_error = ::__get_render_procs().Error();
		__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req)); // no return by this error;
	}
	// (4) gets the vertex array in unbound state;
	if (__failed(vertex::CArrObject::Unbind(this->m_error))) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}
	// (5) gets the program in unused state;
	if (__failed(CProgram::Unused(this->m_error))) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
	}
	return n_result;
}

TError& CGrid::Error (void) const { return this->m_error; }

err_code view::CGrid::Update (const t_size_u& _u_size) {
	_u_size;
	this->m_error <<__METHOD__<<__s_ok;

	const render::CCfg& cfg = ::Get_renderer().Cfg();
	if (false == cfg.Is_drawable(e_object::e_grid))
			return this->Error();

	CMarkers markers;
	// (1);(2): calculates markets' places and its count for horizontal and vertical lines of the grid;
	if (__failed(markers.Count(_u_size, this->Cell().Get()))) {
		return this->m_error = markers.Error();
	}
	using CBuffer = vertex::CBuffer;

	TRenderer& renderer  = ::Get_renderer();
	vertex::CArrObject& vao = renderer.Scene().ArrObjects().Get(e_object::e_grid);
	CVertArray& vert_arr = vao.VertArray();

	// (3) calculates the number of required vertices for drawing grid lines;
	const uint32_t u_count = static_cast<uint32_t>((markers.Get_horz().size() + markers.Get_vert().size())) * 2;

	if (__failed(vert_arr.Count(u_count ))) {
		return this->m_error = vert_arr.Error();
	}

	CClr_flt& clr = this->Clr();

	t_set_3 coord = {0.0f};
	uint32_t u_ndx = 0;

	try {
		// (4) creates vertices for horizontal lines from the left to the right sides of the grid; 
		for (t_markers::const_iterator it_y = markers.Get_horz().begin(); it_y != markers.Get_horz().end(); ++it_y) {

		// (4.a) gets the left side point of the line;
			CViewPort::ToPos(_u_size, 0, *it_y, coord, this->m_error);
			vert_arr.Get(u_ndx).Attrs().Pos().Set(coord.at(0), coord.at(1), coord.at(2));
			vert_arr.Get(u_ndx).Attrs().Clr().Set(clr.Get_r(), clr.Get_g(), clr.Get_b(), clr.Get_a());

		//	vert_arr.Get(u_ndx).Attrs().Clr().Is_used(false);
			u_ndx += 1;

		// (4.b) gets the right side point of the line;
			CViewPort::ToPos(_u_size, _u_size.cx, *it_y, coord, this->m_error);
			vert_arr.Get(u_ndx).Attrs().Pos().Set(coord.at(0), coord.at(1), coord.at(2));
			vert_arr.Get(u_ndx).Attrs().Clr().Set(clr.Get_r(), clr.Get_g(), clr.Get_b(), clr.Get_a());
			u_ndx += 1;
		}
		// (5) creates vertices for vertical lines from the top to the bottom sides of the grid;
		for (::std::set<uint32_t>::const_iterator it_x = markers.Get_vert().begin(); it_x != markers.Get_vert().end(); ++it_x) {
		// (5.a) gets the top side point of the line;
			CViewPort::ToPos(_u_size, *it_x, 0, coord, this->m_error);
			vert_arr.Get(u_ndx).Attrs().Pos().Set(coord.at(0), coord.at(1), coord.at(2));
			vert_arr.Get(u_ndx).Attrs().Clr().Set(clr.Get_r(), clr.Get_g(), clr.Get_b(), clr.Get_a());
			u_ndx += 1;

		// (5.b) gets the bottom side point of the line;
			CViewPort::ToPos(_u_size, *it_x, _u_size.cy, coord, this->m_error);
			vert_arr.Get(u_ndx).Attrs().Pos().Set(coord.at(0), coord.at(1), coord.at(2));
			vert_arr.Get(u_ndx).Attrs().Clr().Set(clr.Get_r(), clr.Get_g(), clr.Get_b(), clr.Get_a());
			u_ndx += 1;
		}
	}
	catch (const ::std::bad_alloc&) { return this->m_error << __e_no_memory; }
	catch (const ::std::out_of_range&) { return this->m_error << __e_no_memory = TString().Format(_T("#__e_out_of_range: ndx = %u; vec.size = %u"), u_ndx, vert_arr.Count()); }

	if (__failed(vert_arr.Update())) {
		return this->m_error = vert_arr.Buffer().Error();
	}

	if (__failed(vao.SetData(vert_arr.Data_ref())))
		this->m_error = vao.Error();
	else {
		CProgram& prog = renderer.Scene().Progs().Get(e_object::e_grid); // the program reference cannot be 'const' or 'read-only' due to the program needs to be activated;
		const int32_t clr_ndx = ::__get_uni_procs().Locate(prog.Id().Get(), _T("clr_line_in"));
		if (::__get_uni_procs().Error()) {
			this->m_error = ::__get_uni_procs().Error();
			__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
			return this->Error();
		}
		// before setting the color value to uniform variable of the fragment shader the programm must be active, otherwise the error is generated;
		if (false == prog.Status().Is_used())
			if (__failed(prog.Use())) {
				this->m_error = prog.Error();
				__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
				return this->Error();
			}
#if (0) // for usniform vars test case only;
		using CUni_enum = vars::CUniform_enum; CUni_enum u_vars;
		const uint32_t var_count = u_vars.Count();
		if (u_vars.Error()) {
			return this->m_error = u_vars.Error();
		}
#endif
	//	using t_uniform_4f = procs::vars::t_uniform_4f; t_uniform_4f clr_4f{clr.Get_r(), clr.Get_g(), clr.Get_b(), clr.Get_a()};
#if (1)
		if (__failed(::__get_uni_val_procs().Set_4fs(clr_ndx, {clr.Get_r(), clr.Get_g(), clr.Get_b(), /*clr.Get_a()*/1.0f}))) {
			this->m_error = ::__get_uni_val_procs().Error();
			__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
			return this->Error();
		}
#endif
	}
	return this->Error();
}

#pragma endregion