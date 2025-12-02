/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Oct-2025 at 19:30:37.003, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL viewport wrapper interface implementation file;
*/
#include "gl_viewport.h"
#include "shared.preproc.h"
#include "procs\gl_procs_view.h"

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

view::CGrid::CCell:: CCell (void) : m_size{0u} {}
view::CGrid::CCell::~CCell (void) {}

uint32_t view::CGrid::CCell::Height (void) const { return this->m_size.cy; }
bool     view::CGrid::CCell::Height (const uint32_t _u_val) { if (this->Height() != _u_val) { this->m_size.cy = _u_val; return true; } else return false; }
uint32_t view::CGrid::CCell::Width  (void) const { return this->m_size.cx; }
bool     view::CGrid::CCell::Width  (const uint32_t _u_val) { if (this->Width()  != _u_val) { this->m_size.cx = _u_val; return true; } else return false; }

bool   view::CGrid::CCell::Is_valid (void) const { return this->Height() && this->Width(); }

bool   view::CGrid::CCell::Set (const uint32_t _u_width, const uint32_t _u_height) {
	_u_width; _u_height;
	bool b_changed = false;

	if (this->Height(_u_height)) b_changed = true;
	if (this->Width (_u_width)) b_changed = true;

	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////

view::CColor:: CColor (void) : m_rgba{0.0f} {}
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
	this->m_rgba[3] = CConvert::ToFloat(get_a_value(_rgba));
}

view::CGrid:: CGrid (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; /*this->Default();*/ }
view::CGrid::~CGrid (void) {}

const
view::CGrid::CCell& view::CGrid::Cell (void) const { return this->m_cell; }
view::CGrid::CCell& view::CGrid::Cell (void)       { return this->m_cell; }

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

	if (0 == _u_size.cx || 0 == _u_size.cy)
		return this->m_error <<__e_inv_arg;

	if (false == this->Cell().Is_valid())
		return this->m_error <<__e_not_inited = TString().Format(_T("#__e_not_init: cell size {w=%u;h=%u} is not valid"), this->Cell().Width(), this->Cell().Height());

	const t_point pt_center = {
		static_cast<long>(_u_size.cx / 2), static_cast<long>(_u_size.cy / 2)
	};

	try {
		if (this->m_vertices.Items().empty() == false)
			this->m_vertices.Items().clear();
	}
	catch (const ::std::bad_alloc&) { this->m_error << __e_no_memory; }

	return this->Error();
}

const
view::CVertArr& view::CGrid::Vertices (void) const { return this->m_vertices; }

/////////////////////////////////////////////////////////////////////////////

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

	if (0 == _u_height) return this->m_error << __e_inv_arg = _T("Height cannot be 0 (zero)");
	if (0 == _u_width) return this->m_error << __e_inv_arg = _T("Width cannot be 0 (zero)");

	this->m_size.cy = _u_height;
	this->m_size.cx = _u_width ;

	return this->Error();
}

err_code CViewPort::Set (const t_rect& _rect) {
	_rect;
	this->m_error << __METHOD__<<__s_ok;
	if (::IsRectEmpty(&_rect))
		return this->m_error <<__e_inv_arg;

	this->m_size.cy = __H(_rect);
	this->m_size.cx = __W(_rect);

	return this->Error();
}

bool CViewPort::Is_valid (void) const {
	return this->m_size.cy != 0 && this->m_size.cx != 0;
}

const
view::CGrid& CViewPort::Grid (void) const { return this->m_grid; }
view::CGrid& CViewPort::Grid (void)       { return this->m_grid; }

vertex::CCoord  CViewPort::ToPos (const long _x, const long _y) {
	_x; _y;
	if (false == this->Is_valid()) {
		this->m_error <<__METHOD__<<__e_inv_arg = TString().Format(_T("Screen size : x=0x%04x, y=0x%04x"), _x, _y);
		return vertex::CCoord(); // returns 'empty' or 'default' coord which has x|y = {0};
	}
	// ToDo: this requires testing to find out which expression works faster;
#if (1)
	// https://discourse.glfw.org/t/converting-between-screen-coordinates-and-pixels/1841/2 ; thanks @dougbinks for good answer;
	return vertex::CCoord(
		2.0f * (float)_x/(float)this->m_size.cx - 1.0f, 1.0f - 2.0f * (float)_y/(float)this->m_size.cy
	);
#else
	// https://stackoverflow.com/questions/40068191/opengl-screen-to-world-coordinates-conversion ;
	return vertex::CCoord(
		2.0f * ((float)_x + 0.5f)/(float)(this->m_size.cx / 2) - 1.0f, 1.0f - ((float)_y + 0.5f)/(float)(this->m_size.cy / 2)
	);
#endif
}

CViewPort&  CViewPort::operator << (const t_rect& _rect) { this->Set(_rect); return *this; }