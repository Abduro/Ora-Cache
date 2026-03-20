/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Mar-2026 at 15:27:26.133, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' rectamgular 2d shape corner points' matrix 2x4 interface implementation file;
*/
#include "math.rect.2d.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl::math;

namespace ex_ui { namespace draw { namespace open_gl { namespace math { namespace _impl {

}}}}}
using namespace ex_ui::draw::open_gl::math::_impl;

#pragma region cls::c_corners{}

using c_corners = c_rect::c_corners;

c_corners::c_corners (c_rect& _rect) : m_rect(_rect) {}
const
vec_2&  c_corners::A (void) const { return this->Get(e_corners::e_a); }
//vec_2&  c_corners::A (void)     { return this->Get(e_corners::e_a); }
const
vec_2&  c_corners::B (void) const { return this->Get(e_corners::e_b); }
//vec_2&  c_corners::B (void)     { return this->Get(e_corners::e_b); }
const
vec_2&  c_corners::C (void) const { return this->Get(e_corners::e_c); }
//vec_2&  c_corners::C (void)     { return this->Get(e_corners::e_c); }
const
vec_2&  c_corners::D (void) const { return this->Get(e_corners::e_d); }
//vec_2&  c_corners::D (void)     { return this->Get(e_corners::e_d); }
const
vec_2&  c_corners::Get (const e_corners _e_corner) const {
	if (e_corners::e_a == _e_corner) return this->m_rect.m_data[0];
	else if (e_corners::e_b == _e_corner) return this->m_rect.m_data[1];
	else if (e_corners::e_c == _e_corner) return this->m_rect.m_data[2];
	else return this->m_rect.m_data[3];
}
vec_2&  c_corners::Get (const e_corners _e_corner) {
	if (e_corners::e_a == _e_corner) return this->m_rect.m_data[0];
	else if (e_corners::e_b == _e_corner) return this->m_rect.m_data[1];
	else if (e_corners::e_c == _e_corner) return this->m_rect.m_data[2];
	else return this->m_rect.m_data[3];
}

void c_corners::Set_Bottom (const float _f_y) { this->Get(e_corners::e_c).y = _f_y; this->Get(e_corners::e_d).y = _f_y; }
void c_corners::Set_Left (const float _f_x) { this->Get(e_corners::e_a).x = _f_x; this->Get(e_corners::e_d).x = _f_x; }

void c_corners::Set_LeftTop (const float _f_left, const float _f_top) { this->Set_Left(_f_left); this->Set_Top(_f_top); }
void c_corners::Set_Right (const float _f_x) { this->Get(e_corners::e_b).x = _f_x; this->Get(e_corners::e_c).x = _f_x; }

void c_corners::Set_RightBottom (const float _f_right, const float _f_bottom) { this->Set_Bottom(_f_bottom); this->Set_Right(_f_right); }
void c_corners::Set_Top (const float _f_y) { this->Get(e_corners::e_a).y = _f_y; this->Get(e_corners::e_b).y = _f_y; }

_pc_sz c_corners::To_str (const e_corners _e_corner, const vec_2 _v_corner) {
	_e_corner; _v_corner;
	static _pc_sz pc_sz_pat = _T("corner '%s'; %s");
	static CString  cs_out; cs_out.Empty();

	switch (_e_corner) {
	case c_rect::e_corners::e_a: cs_out.Format(pc_sz_pat, _T("A"), (_pc_sz) _v_corner.To_str()); break;
	case c_rect::e_corners::e_b: cs_out.Format(pc_sz_pat, _T("B"), (_pc_sz) _v_corner.To_str()); break;
	case c_rect::e_corners::e_c: cs_out.Format(pc_sz_pat, _T("C"), (_pc_sz) _v_corner.To_str()); break;
	case c_rect::e_corners::e_d: cs_out.Format(pc_sz_pat, _T("D"), (_pc_sz) _v_corner.To_str()); break;
	default: cs_out = _T("corner: #undef;");
	}
	return (_pc_sz) cs_out;
}

#pragma endregion
#pragma region cls::c_rect{}

c_rect::c_rect (void) : m_corners(*this) { this->Init(); }
c_rect::c_rect (const c_rect& _src) : c_rect() { *this = _src; }

const
c_corners& c_rect::Corners (void) const { return this->m_corners; }
c_corners& c_rect::Corners (void)       { return this->m_corners; }

float c_rect::Height (void) const { return (*this)().A().y - (*this)().D().y; } // it is not necessary to check B().y - C().y;

void c_rect::Init (void) {
	/* (a) = {x:0;y:1}; (b) = {x:1;y:1};
	   (d) = {x:0;y:0}; (c) = {x:1;y:0};
	*/
	this->Corners().Get(e_corners::e_a).Set(0.0f, 1.0f);
	this->Corners().Get(e_corners::e_b).Set(1.0f, 1.0f);
	this->Corners().Get(e_corners::e_c).Set(1.0f, 0.0f);
	this->Corners().Get(e_corners::e_d).Set(0.0f, 0.0f);

	return;
}

bool c_rect::Is_empty (void) const {
	return 0.0f == this->Height() || 0.0f == this->Width();
}
bool c_rect::Is_valid (void) const {
	// (1) checks all corners for being to right, i.e. to be equal to 90 degrees;
	//     adjacent vector means it is not along horizontally or vertically to the vector which it is adjusted to;
	if (0.0f != ::Get_dot((*this)().A(), (*this)().D())) return false; // gets the angle of the corner A with the adjacent corner D;
	if (0.0f != ::Get_dot((*this)().B(), (*this)().C())) return false; // gets the angle of the corner B with the adjacent corner C;
	// (2) emptiness of this rectangle is not checked yet;
	return true;
}

float c_rect::Width (void) const { return (*this)().A().x - (*this)().B().x; } // it is not necessary to check D().x - C().x;

const
c_corners& c_rect::operator ()(void) const { return this->Corners(); }
c_corners& c_rect::operator ()(void)       { return this->Corners(); }

#pragma endregion
#pragma region cls::c_rot_rect{}

c_rot_rect::c_rot_rect (void) : c_rect() {}

c_rect& c_rot_rect::Do (const float _f_angle) {
	_f_angle;
	if (false == __chk_angle(_f_angle))
		return (*this)();

	c_rotate_2x2 rot_2x2; rot_2x2.Prepare(_f_angle); // to-do: the check of the rotation angle is already made above, but Prepare() does it again;

	for (uint32_t i_ = 0; i_ < c_rect::u_corners; i_++) {
		if (0.0f == c_rect::m_data[i_].x && 0.0f == c_rect::m_data[i_].y) // if the point is already at origin there is no sense to rotate it;
			continue;
		rot_2x2() *= c_rect::m_data[i_];
	}
	return (*this)();
}

const
c_rect& c_rot_rect::operator ()(void) const { return (c_rect&)*this; }
c_rect& c_rot_rect::operator ()(void)       { return (c_rect&)*this; }

#pragma endregion