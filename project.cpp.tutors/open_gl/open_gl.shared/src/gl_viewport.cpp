/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Oct-2025 at 19:30:37.003, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL viewport wrapper interface implementation file;
*/
#include "gl_viewport.h"
#include "shared.preproc.h"
#include "procs\gl_procs_view.h"
#include "sys.registry.h"
#include "color.rgb.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::color::rgb;

#ifndef __H
#define __H(rect) (rect.bottom - rect.top)
#endif
#ifndef __W
#define __W(rect) (rect.right - rect.left)
#endif

namespace ex_ui { namespace draw { namespace open_gl { namespace _impl {
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

float view::CColor::Get_a (void) const { return this->m_rgba[3]; }
float view::CColor::Get_b (void) const { return this->m_rgba[2]; }
float view::CColor::Get_g (void) const { return this->m_rgba[1]; }
float view::CColor::Get_r (void) const { return this->m_rgba[0]; }

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
	this->m_rgba[3] = /*CConvert::ToFloat(get_a_value(_rgba))*/ 1.0f; // ToDo: it is required to save the alpha value in registry too;
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
view::CArrObj&   view::CGrid::Array  (void) const { return this->m_arr_obj; }
view::CArrObj&   view::CGrid::Array  (void)       { return this->m_arr_obj; }

const
view::CVertBuff& view::CGrid::Buffer (void) const { return this->m_vert_buf; }
view::CVertBuff& view::CGrid::Buffer (void)       { return this->m_vert_buf; }
const
view::CGrid::CCell& view::CGrid::Cell (void) const { return this->m_cell; }
view::CGrid::CCell& view::CGrid::Cell (void)       { return this->m_cell; }

err_code view::CGrid::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;
	/*
	- glBindVertexArray(m_vaoID[1]);

	+ glGenBuffers(1, &m_vboID[2]);

	+ glBindBuffer(GL_ARRAY_BUFFER, m_vboID[2]);
	+ glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat), vert2, GL_STATIC_DRAW);
	- glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
	- glEnableVertexAttribArray(0);
	*/

	this->Array().Attrs().Clr().Is_used(false);
	this->Array().Attrs().Pos().Is_used(true);

	this->Array().Attrs().Pos().Name(_T("$grid::pos"));

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

	return this->Error();
}

err_code view::CGrid::Destroy (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (this->Array().Is_bound()) {
		if (__failed(this->Array().Unbind()))
			return this->m_error = this->Array().Error();
	}
	if (__failed(this->Array().Delete()))
		return this->m_error = this->Array().Error();

	if (this->Buffer().Is_bound()) {
		if (__failed(this->Buffer().Unbind()))
			return this->m_error = this->Buffer().Error();
	}

	if (__failed(this->Buffer().Destroy())) {
		return this->m_error = this->Buffer().Error();
	}

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
#endif

TError& view::CGrid::Error (void) const { return this->m_error; }

err_code view::CGrid::Update (const t_size_u& _u_size) {
	_u_size;
	this->m_error <<__METHOD__<<__s_ok;

	if (CViewPort::Is_valid(_u_size, this->m_error) == false) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
		return this->Error();
	}

	const t_size_u& c_size = this->Cell().Get();

	if (false == view::CGrid::CCell::Is_valid(c_size, this->m_error)) {
		__trace_err_2(_T("%s;\n"), (_pc_sz) this->Error().Print(TError::e_print::e_req));
		return this->Error();
	}

	t_point pt_center = {
		static_cast<long>(_u_size.cx / 2), static_cast<long>(_u_size.cy / 2)
	}; pt_center;

	::std::set<uint32_t> x_markers;
	::std::set<uint32_t> y_markers;

	uint32_t iter = 0;

	try {
		x_markers.insert(pt_center.x);
		y_markers.insert(pt_center.y);

		int32_t x_iter = _u_size.cx / 2;

		// (1) marks line x-coords;
		// (1.a) from the center to the left side;
		while (x_iter - (int32_t)c_size.cx > 0) { x_markers.insert(x_iter -= (int32_t)c_size.cx); }
		// (1.b) from the center to the right side;
		x_iter = _u_size.cx / 2;
		while (x_iter + c_size.cx < _u_size.cx) { x_markers.insert(x_iter += (int32_t)c_size.cx); }

		int32_t y_iter = _u_size.cy / 2;

		// (2) marks line y-coords;
		// (2.a) from the center to the top side;
		while (y_iter - (int32_t)c_size.cy > 0) { y_markers.insert(y_iter -= (int32_t)c_size.cy); }
		// (2.b) from the center to the bottom side;
		y_iter = _u_size.cy / 2;
		while (y_iter + c_size.cy < _u_size.cy) { y_markers.insert(y_iter += (int32_t)c_size.cy); }

		// (3) calculates the number of required vertices for drawing grid lines;
		const uint32_t u_count = static_cast<uint32_t>((x_markers.size() + y_markers.size())) * 2;

		this->m_vert_dat.resize (u_count * 3);
		this->m_vert_dat.reserve(u_count * 3);

		t_set_3 coord = {0.0f};

		if (__failed(this->m_vertices.Count(u_count))) {
			return this->m_error = this->m_vertices.Error();
		}

		// (4) creates vertices for horizontal lines;
		for (::std::set<uint32_t>::const_iterator it_y = y_markers.begin(); it_y != y_markers.end(); ++it_y) {
		// (4.a) gets the left side point of the line;
			CViewPort::ToPos(_u_size, 0, *it_y, coord, this->m_error);
			this->m_vert_dat.at(iter++) = coord.at(0);
			this->m_vert_dat.at(iter++) = coord.at(1);
			this->m_vert_dat.at(iter++) = coord.at(2);
		// (4.b) gets the right side point of the line;
			CViewPort::ToPos(_u_size, _u_size.cx, *it_y, coord, this->m_error);
			this->m_vert_dat.at(iter++) = coord.at(0);
			this->m_vert_dat.at(iter++) = coord.at(1);
			this->m_vert_dat.at(iter++) = coord.at(2);
		}
		// (5) creates vertices for vertical lines;
		for (::std::set<uint32_t>::const_iterator it_x = x_markers.begin(); it_x != x_markers.end(); ++it_x) {
		// (4.a) gets the top side point of the line;
			CViewPort::ToPos(_u_size, *it_x, 0, coord, this->m_error);
			this->m_vert_dat.at(iter++) = coord.at(0);
			this->m_vert_dat.at(iter++) = coord.at(1);
			this->m_vert_dat.at(iter++) = coord.at(2);
		// (4.b) gets the bottom side point of the line;
			CViewPort::ToPos(_u_size, *it_x, _u_size.cy, coord, this->m_error);
			this->m_vert_dat.at(iter++) = coord.at(0);
			this->m_vert_dat.at(iter++) = coord.at(1);
			this->m_vert_dat.at(iter++) = coord.at(2);
		}
	}
	catch (const ::std::bad_alloc&) { return this->m_error << __e_no_memory; }
	catch (const ::std::out_of_range&) { return this->m_error << __e_no_memory = TString().Format(_T("#__e_out_of_range: ndx = %u; vec.size = %u"), iter, this->m_vert_dat.size()); }
#if (0) // at this point the buffer is not created yet;
	if (__failed(this->Buffer().SetData(this->m_vert_dat)))
		this->m_error = this->Buffer().Error();
#endif
	return this->Error();
}

const
view::CVertArr& view::CGrid::Vertices (void) const { return this->m_vertices; }
#pragma endregion
/////////////////////////////////////////////////////////////////////////////
#pragma region CViewport
CViewPort:: CViewPort (const uint32_t _u_width, const uint32_t _u_height) : m_size{_u_width, _u_height} {
	this->m_error >>__CLASS__<<__METHOD__<<(this->Is_valid() ? __s_ok : __e_not_inited);
}
CViewPort::~CViewPort (void) {}

TError& CViewPort::Error(void) const { return this->m_error; }

t_size  CViewPort::Get (void) const { return t_size{ (long)this->m_size.cx, (long)this->m_size.cy}; }
t_size_u& CViewPort::Get (void) {
	return this->m_size;
}

err_code CViewPort::Set (const uint32_t _u_width, const uint32_t _u_height) {
	_u_width; _u_height;
	this->m_error << __METHOD__<<__s_ok;

	if (0 == _u_height) return this->m_error << __e_inv_arg = _T("#__inv_arg: height cannot be 0 (zero)");
	if (0 == _u_width) return this->m_error << __e_inv_arg = _T("#__inv_arg: width cannot be 0 (zero)");

	this->m_size.cy = _u_height;
	this->m_size.cx = _u_width ;

	if (__failed(this->Grid().Update(this->m_size))) {
		this->m_error = this->Grid().Error();
	}

	return this->Error();
}

err_code CViewPort::Set (const t_rect& _rect) {
	_rect;
	this->m_error << __METHOD__<<__s_ok;
	if (::IsRectEmpty(&_rect))
		return this->m_error <<__e_inv_arg;

	this->m_size.cy = __H(_rect);
	this->m_size.cx = __W(_rect);

	if (__failed(this->Grid().Update(this->m_size))) {
		this->m_error = this->Grid().Error();
	}

	return this->Error();
}

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
const
view::CGrid& CViewPort::Grid (void) const { return this->m_grid; }
view::CGrid& CViewPort::Grid (void)       { return this->m_grid; }

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

CViewPort&  CViewPort::operator << (const t_rect& _rect) { this->Set(_rect); return *this; }
#pragma endregion