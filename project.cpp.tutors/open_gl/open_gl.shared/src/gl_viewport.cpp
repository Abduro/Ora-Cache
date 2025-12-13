/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Oct-2025 at 19:30:37.003, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL viewport wrapper interface implementation file;
*/
#include "gl_viewport.h"
#include "shared.preproc.h"

#include "procs\gl_procs_surface.h"
#include "procs\gl_procs_vertex.h"
#include "procs\gl_procs_view.h"

#include "sys.registry.h"
#include "color.rgb.h"

#include "gl_renderer.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::color::rgb;

#ifndef __H
#define __H(rect) (rect.bottom - rect.top)
#endif
#ifndef __W
#define __W(rect) (rect.right - rect.left)
#endif

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

/////////////////////////////////////////////////////////////////////////////
#pragma region CColor
view::CColor:: CColor (void) : m_rgba{0.0f} {
	using CRegGrid = shared::sys_core::storage::CReg_router::CViewport::CGrid;
	CRegGrid& reg_grid = ::Get_reg_router().Viewport().Grid();

	TRegKeyEx reg_key;
	CString cs_clr = reg_key.Value().GetString(reg_grid.Root(), reg_grid.Clr_name());
	if (reg_key.Error()) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) reg_key.Error().Print(TError::e_print::e_req));
	}

	this->Set((rgb_color)CHex((_pc_sz) cs_clr));
}
view::CColor::~CColor (void) {}

float view::CColor::Get_a (void) const { return this->m_rgba[3]; } const float& view::CColor::A (void) const { return this->m_rgba[3]; }
float view::CColor::Get_b (void) const { return this->m_rgba[2]; } const float& view::CColor::B (void) const { return this->m_rgba[2]; }
float view::CColor::Get_g (void) const { return this->m_rgba[1]; } const float& view::CColor::G (void) const { return this->m_rgba[1]; }
float view::CColor::Get_r (void) const { return this->m_rgba[0]; } const float& view::CColor::R (void) const { return this->m_rgba[0]; }

void view::CColor::Set (const float _r, const float _g, const float _b, const float _a) {
	_r; _g; _b; _a;
	
	this->m_rgba[0] = (0.0f > _r ? 0.0f : (1.0f < _r ? 1.0f : _r));
	this->m_rgba[1] = (0.0f > _g ? 0.0f : (1.0f < _g ? 1.0f : _g));
	this->m_rgba[2] = (0.0f > _b ? 0.0f : (1.0f < _b ? 1.0f : _b));
	this->m_rgba[3] = (0.0f > _a ? 0.0f : (1.0f < _a ? 1.0f : _a));
}

void view::CColor::Set (const uint8_t _r, const uint8_t _g, const uint8_t _b, const uint8_t _a) {
	_r; _g; _b; _a;
	
	// the color channels' sequence: r-g-b-a;
	this->m_rgba[0] = CConvert::ToFloat(_r);
	this->m_rgba[1] = CConvert::ToFloat(_g);
	this->m_rgba[2] = CConvert::ToFloat(_b);
	this->m_rgba[3] = CConvert::ToFloat(_a);
}

void view::CColor::Set (const rgb_color _rgba) {
	_rgba;

	// the color channels' sequence: r-g-b-a;
	this->m_rgba[0] = CConvert::ToFloat(get_r_value(_rgba));
	this->m_rgba[1] = CConvert::ToFloat(get_g_value(_rgba));
	this->m_rgba[2] = CConvert::ToFloat(get_b_value(_rgba));
	this->m_rgba[3] = /*CConvert::ToFloat(get_a_value(_rgba))*/ 0.0f; // ToDo: it is required to save the alpha value in registry too;
}
#pragma endregion
/////////////////////////////////////////////////////////////////////////////
#pragma region CGrid::CCell
view::CGrid::CCell:: CCell (void) : m_size{0u} {

	using CRegCell = shared::sys_core::storage::CReg_router::CViewport::CGrid::CCell;
	CRegCell& reg_cell = ::Get_reg_router().Viewport().Grid().Cell();

	TRegKeyEx reg_key;
	m_size.cx = reg_key.Value().GetDword(reg_cell.Root(), (_pc_sz) reg_cell.Value(CRegCell::e_width));
	if (reg_key.Error()) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) reg_key.Error().Print(TError::e_print::e_req));
	}
	m_size.cy = reg_key.Value().GetDword(reg_cell.Root(), (_pc_sz) reg_cell.Value(CRegCell::e_height));
	if (reg_key.Error()) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) reg_key.Error().Print(TError::e_print::e_req));
	}
}
view::CGrid::CCell::~CCell (void) {}

uint32_t view::CGrid::CCell::Height (void) const { return this->m_size.cy; }
bool     view::CGrid::CCell::Height (const uint32_t _u_val) { if (this->Height() != _u_val) { this->m_size.cy = _u_val; return true; } else return false; }
uint32_t view::CGrid::CCell::Width  (void) const { return this->m_size.cx; }
bool     view::CGrid::CCell::Width  (const uint32_t _u_val) { if (this->Width()  != _u_val) { this->m_size.cx = _u_val; return true; } else return false; }

bool   view::CGrid::CCell::Is_valid (void) const { return this->Height() && this->Width(); }
bool   view::CGrid::CCell::Is_valid (const t_size_u& _u_size, CError& _err) {
	_u_size; _err;
	if (0 == _u_size.cx || 0 == _u_size.cy) {
		_err <<__e_not_inited = TString().Format(_T("#__e_not_init: cell size {w=%u;h=%u} is invalid"), _u_size.cx, _u_size.cy);
	}
	return false == _err;
}
const
t_size_u& view::CGrid::CCell::Get (void) const { return this->m_size; }
bool      view::CGrid::CCell::Set (const uint32_t _u_width, const uint32_t _u_height) {
	_u_width; _u_height;
	bool b_changed = false;

	if (this->Height(_u_height)) b_changed = true;
	if (this->Width (_u_width)) b_changed = true;

	return b_changed;
}
#pragma endregion
#pragma region CGrid
view::CGrid:: CGrid (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; /*this->Default();*/ }
view::CGrid::~CGrid (void) {}

const
view::CGrid::CCell& view::CGrid::Cell (void) const { return this->m_cell; }
view::CGrid::CCell& view::CGrid::Cell (void)       { return this->m_cell; }

err_code view::CGrid::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;
#if (0)	
	this->Array().Attrs().Clr().Is_used(false);
	this->Array().Attrs().Pos().Is_used(true);
	this->Array().Attrs().Pos().Name(_T("$grid::pos"));
	this->Array().Attrs().Pos().Locate().Value(0);

	if (__failed(this->Array().Create())) return this->m_error = this->Array().Error();
	if (__failed(this->Array().Bind())) return this->m_error = this->Array().Error();
	if (__failed(this->Array().Enable(true))) this->m_error = this->Array().Error();

	if (this->Buffer().Is_valid() == false)
		if (__failed(this->Buffer().Create())) {
			return this->m_error = this->Buffer().Error();
		}

	using e_bind_targets = ex_ui::draw::open_gl::procs::e_bind_targets;

	if (__failed(this->Buffer().BindTo(e_bind_targets::e_array)))
		return this->m_error = this->Buffer().Error();

	if (__failed(this->Buffer().SetData(this->m_vert_dat)))
		this->m_error = this->Buffer().Error();

	if (__failed(CVertArr::Set_ptrs(this->Array().Attrs().Pos(), this->m_error))) {}
	if (__failed(this->Array().Enable(true))) {
		this->m_error = this->Array().Error();
	}
#endif
	return this->Error();
}

err_code view::CGrid::Destroy (void) {
	this->m_error <<__METHOD__<<__s_ok;
	return this->Error();
}

const
view::CColor& view::CGrid::Clr (void) const { return this->m_color; }
view::CColor& view::CGrid::Clr (void)       { return this->m_color; }

#if (0)
void view::CGrid::Default (void) {
	this->Clr().Set(0.5f, 0.5f, 0.5f, 1.0f);
	this->Size() = 10.0f;
	this->Step() = 01.0f;
}
#endif
#if (0) // it does not work such way due to the draw must be made to vertex buffer, otherwise nothing;
err_code view::CGrid::Draw (void) {

	err_code n_result = __s_ok;

    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);

    glColor4f(this->Clr().Get_r(), this->Clr().Get_g(), this->Clr().Get_b(), this->Clr().Get_a());

    for (float i_ = this->Step(); i_ <= this->Size(); i_ += this->Step()) {

        glVertex3f(-this->Size(), +i_, 0.0f);
        glVertex3f( this->Size(), +i_, 0.0f);
        glVertex3f(-this->Size(), -i_, 0.0f);
        glVertex3f( this->Size(), -i_, 0.0f);

        glVertex3f(+i_, -this->Size(), 0.0f);
        glVertex3f(+i_,  this->Size(), 0.0f);
        glVertex3f(-i_, -this->Size(), 0.0f);
        glVertex3f(-i_,  this->Size(), 0.0f);
    }

    glEnd();
    glEnable(GL_LIGHTING);

	return n_result;
}
#else
err_code view::CGrid::Draw (void) {
	err_code n_result = __s_ok;

	using e_line = procs::CPrimitives::e_line;
	using e_prog = CProg_enum::e_prog_ndx;
	using e_arr_ndx = vertex::CArrObj_enum::e_arr_ndx;

#if (1)
	if (__failed(::__get_attr_mod_procs().Modify_f4(0, this->Clr().Get_r(), this->Clr().Get_g(), this->Clr().Get_b(), this->Clr().Get_a()))) {
		this->m_error = ::__get_attr_mod_procs().Error();
		__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req)); // no return by this error;
	}
#endif

	const CProgram& prog = ::Get_renderer().Scene().Progs().Get(e_prog::e_grid);
	
	vertex::CArrObject& vao = ::Get_renderer().Scene().ArrObjs().Get(e_arr_ndx::e_grid); vao;
	const CVertArray& vexes = ::Get_renderer().Scene().ArrObjs().Get(e_arr_ndx::e_grid).VertArray();

	if (vexes.Is_valid() == false)
		return n_result = vexes.Error();

//	if (__failed(vao.Bind()))
//		return n_result = vao.Error();

	if (__failed(::__get_render_procs().DrawArrays(prog.Id().Get(), (uint32_t) e_line::e_lines, 0, vexes.Count()))) {
		this->m_error = ::__get_render_procs().Error();
		__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req)); // no return by this error;
	}

	return n_result;
}
#endif

TError& view::CGrid::Error (void) const { return this->m_error; }

err_code view::CGrid::Update (const t_size_u& _u_size) {
	_u_size;
	this->m_error <<__METHOD__<<__s_ok;

	CMarkers markers;
	// (1);(2): calculates markets' places and its count for horizontal and vertical lines of the grid;
	if (__failed(markers.Count(_u_size, this->Cell().Get()))) {
		return this->m_error = markers.Error();
	}

	using e_arr_ndx = vertex::CArrObj_enum::e_arr_ndx;
	using CBuffer   = vertex::CBuffer;

	TRenderer& renderer  = ::Get_renderer();
	CVertArray& vert_arr = renderer.Scene().ArrObjs().Get(e_arr_ndx::e_grid).VertArray();

	// (3) calculates the number of required vertices for drawing grid lines;
	const uint32_t u_count = static_cast<uint32_t>((markers.Get_horz().size() + markers.Get_vert().size())) * 2;

	if (__failed(vert_arr.Count(u_count ))) {
		return this->m_error = vert_arr.Error();
	}

	view::CColor& clr = this->Clr();

	t_set_3 coord = {0.0f};
	uint32_t u_ndx = 0;

	try {
		// (4) creates vertices for horizontal lines from the left to the right sides of the grid; 
		for (t_markers::const_iterator it_y = markers.Get_horz().begin(); it_y != markers.Get_horz().end(); ++it_y) {

		// (4.a) gets the left side point of the line;
			CViewPort::ToPos(_u_size, 0, *it_y, coord, this->m_error);
			vert_arr.Get(u_ndx).Attrs().Pos().Set(coord.at(0), coord.at(1), coord.at(2));
			vert_arr.Get(u_ndx).Attrs().Clr().Set(clr.R(), clr.G(), clr.B(), clr.A());
			u_ndx += 1;

		// (4.b) gets the right side point of the line;
			CViewPort::ToPos(_u_size, _u_size.cx, *it_y, coord, this->m_error);
			vert_arr.Get(u_ndx).Attrs().Clr().Set(clr.R(), clr.G(), clr.B(), clr.A());
			vert_arr.Get(u_ndx).Attrs().Pos().Set(coord.at(0), coord.at(1), coord.at(2));
			u_ndx += 1;
		}
		// (5) creates vertices for vertical lines from the top to the bottom sides of the grid;
		for (::std::set<uint32_t>::const_iterator it_x = markers.Get_vert().begin(); it_x != markers.Get_vert().end(); ++it_x) {
		// (5.a) gets the top side point of the line;
			CViewPort::ToPos(_u_size, *it_x, 0, coord, this->m_error);
			vert_arr.Get(u_ndx).Attrs().Pos().Set(coord.at(0), coord.at(1), coord.at(2));
			vert_arr.Get(u_ndx).Attrs().Clr().Set(clr.R(), clr.G(), clr.B(), clr.A());
			u_ndx += 1;

		// (5.b) gets the bottom side point of the line;
			CViewPort::ToPos(_u_size, *it_x, _u_size.cy, coord, this->m_error);
			vert_arr.Get(u_ndx).Attrs().Pos().Set(coord.at(0), coord.at(1), coord.at(2));
			vert_arr.Get(u_ndx).Attrs().Clr().Set(clr.R(), clr.G(), clr.B(), clr.A());
			u_ndx += 1;
		}
	}
	catch (const ::std::bad_alloc&) { return this->m_error << __e_no_memory; }
	catch (const ::std::out_of_range&) { return this->m_error << __e_no_memory = TString().Format(_T("#__e_out_of_range: ndx = %u; vec.size = %u"), u_ndx, vert_arr.Count()); }

	if (__failed(vert_arr.Update())) {
		return this->m_error = vert_arr.Buffer().Error();
	}
#if (0)
	if (__failed(vert_arr.Buffer().SetData(vert_arr.Data_ref())))
		this->m_error = vert_arr.Buffer().Error();
#else
	if (__failed(renderer.Scene().ArrObjs().Get(e_arr_ndx::e_grid).SetData(vert_arr.Data_ref())))
		this->m_error =renderer.Scene().ArrObjs().Get(e_arr_ndx::e_grid).Error();
#endif
	return this->Error();
}

#pragma endregion
/////////////////////////////////////////////////////////////////////////////
#pragma region CViewport
CViewPort:: CViewPort (const uint32_t _u_width, const uint32_t _u_height) : m_size{_u_width, _u_height} {
	this->m_error >>__CLASS__<<__METHOD__<<(this->Is_valid() ? __s_ok : __e_not_inited);
}
CViewPort::~CViewPort (void) {}

TError& CViewPort::Error(void) const { return this->m_error; }

bool CViewPort::Is_valid (void) const {
	return CViewPort::Is_valid(this->m_size, this->m_error);
}
bool CViewPort::Is_valid (const t_size_u& _u_size, CError& _err) {
	_u_size; _err;
	if (0 == _u_size.cx || 0 == _u_size.cy) {
		_err <<__METHOD__<<__e_inv_arg = TString().Format(_T("#__e_inv_size: cx=0x%04x, cy=0x%04x"), _u_size.cx, _u_size.cy);
		return false;
	}
	else return true;
}

t_size    CViewPort::Get (void) const { return t_size{ (long)this->m_size.cx, (long)this->m_size.cy}; }
t_size_u& CViewPort::Get (void) {
	return this->m_size;
}

const
view::CGrid& CViewPort::Grid (void) const { return this->m_grid; }
view::CGrid& CViewPort::Grid (void)       { return this->m_grid; }

err_code CViewPort::Set (const uint32_t _u_width, const uint32_t _u_height) {
	_u_width; _u_height;
	this->m_error << __METHOD__<<__s_ok;

	if (0 == _u_height) return this->m_error << __e_inv_arg = _T("#__inv_arg: height cannot be 0 (zero)");
	if (0 == _u_width) return this->m_error << __e_inv_arg = _T("#__inv_arg: width cannot be 0 (zero)");

	this->m_size.cy = _u_height;
	this->m_size.cx = _u_width ;
#if (0) // this function is for setting the size of this viewport and no more;
	if (__failed(this->Grid().Update(this->m_size))) {
		this->m_error = this->Grid().Error();
	}
#endif
	return this->Error();
}

err_code CViewPort::Set (const t_rect& _rect) {
	_rect;
	this->m_error << __METHOD__<<__s_ok;
	if (::IsRectEmpty(&_rect))
		return this->m_error <<__e_inv_arg = TString().Format(_T("#__inv_arg: empty rect = {w:%04d|h:%04d}"), __W(_rect), __H(_rect));
#if (0) // it is not the point for updating the grid, because this function is intended for setting the size of viewport only;
	this->m_size.cy = __H(_rect);
	this->m_size.cx = __W(_rect);

	if (__failed(this->Grid().Update(this->m_size))) {
		this->m_error = this->Grid().Error();
	}
#else
	this->Set(__W(_rect), __H(_rect));
#endif
	return this->Error();
}

vertex::CCoord  CViewPort::ToPos (const long _x, const long _y) {
	_x; _y;
	t_set_3 coord{0.0f};
	CViewPort::ToPos(this->m_size, _x, _y, coord,this->m_error);
	if (this->Error())
		return vertex::CCoord(); // returns 'empty' or 'default' coord which has x|y|z = {0.0f};
	else
		return vertex::CCoord(coord[0], coord[1], coord[2]);
}

err_code CViewPort::ToPos (const t_size_u& _u_size, const uint32_t _in_x, const uint32_t _in_y, t_set_3& _pos_out, CError& _err) {
	_u_size; _in_x; _in_y; _pos_out; _err;
	if (CViewPort::Is_valid(_u_size, _err) == false)
		return _err;
	// ToDo: this requires testing to find out which expression works faster;
#if (1)
	// https://discourse.glfw.org/t/converting-between-screen-coordinates-and-pixels/1841/2 ; thanks @dougbinks for good answer;
	_pos_out[0] = 2.0f * (float)_in_x/(float)_u_size.cx - 1.0f; // x;
	_pos_out[1] = 1.0f - 2.0f * (float)_in_y/(float)_u_size.cy; // y;
	_pos_out[2] = 0.0f; // z;
#else
	// https://stackoverflow.com/questions/40068191/opengl-screen-to-world-coordinates-conversion ;
	_pos_out = {2.0f * ((float)_in_x + 0.5f)/(float)(_u_size.cx / 2) - 1.0f, 1.0f - ((float)_in_y + 0.5f)/(float)(_u_size.cy / 2), 0.0f};
#endif
	return _err;
}

err_code CViewPort::Update (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (__failed(this->Grid().Update(this->m_size))) {
		this->m_error = this->Grid().Error();
	}

	return this->Error();
}

CViewPort&  CViewPort::operator << (const t_rect& _rect) { this->Set(_rect); return *this; }
#pragma endregion