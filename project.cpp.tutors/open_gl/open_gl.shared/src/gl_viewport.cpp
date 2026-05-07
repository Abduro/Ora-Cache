/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Oct-2025 at 19:30:37.003, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL viewport wrapper interface implementation file;
*/
#include "gl_viewport.h"

#include "gl_procs_surface.h"
#include "gl_procs_vertex.h"
#include "gl_procs_view.h"

#include "sys.registry.h"

#include "gl_renderer.h"
#include "gl_uniform.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::color::rgb;

#ifndef __H
#define __H(rect) (rect.bottom - rect.top)
#endif
#ifndef __W
#define __W(rect) (rect.right - rect.left)
#endif

#pragma region cls::CViewport {}
CViewPort:: CViewPort (const uint32_t _u_width, const uint32_t _u_height) : m_size{_u_width, _u_height} { this->m_error >>__CLASS__<<__METHOD__<<__s_ok;
	if (false == this->Is_valid()){/*error state is already set by this property;*/}
}
CViewPort:: CViewPort (const CViewPort& _src) : CViewPort() { *this= _src; }
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
//t_size_u& CViewPort::Get (void) { return this->m_size; }
float     CViewPort::Get_X (const int32_t _n_x) const {
	_n_x;
	if (0 == this->Get().cx) // the division by zero is not defined;
		return 0.0f;
	// https://en.wikipedia.org/wiki/Division_(mathematics) ; >> Dividend / Divisor = Quotient; (Remainder) : left amount;
#if (1)
	const float f_divisor = (float)this->Get().cx;
	return 2.0f * (float)_n_x/f_divisor - 1.0f;
#else
	return 2.0f * ((float)_n_x + 0.5f)/(float)(this->Get().cx / 2) - 1.0f
#endif
}
float     CViewPort::Get_Y (const int32_t _n_y) const {
	_n_y;
	if (0 == this->Get().cy) // the division by zero is not defined;
		return 0.0f;
#if (1)
	return 1.0f - 2.0f * (float)_n_y/(float)this->Get().cy;
#else
	return 1.0f - ((float)_n_y + 0.5f)/(float)(this->Get().cy / 2);
#endif
}

err_code  CViewPort::Set (const uint32_t _u_width, const uint32_t _u_height) {
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

err_code  CViewPort::Set (const t_rect& _rect) {
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

err_code  CViewPort::ToPos (const t_size_u& _u_size, const uint32_t _in_x, const uint32_t _in_y, t_set_3& _pos_out, CError& _err) {
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

err_code  CViewPort::Update (void) {
	this->m_error <<__METHOD__<<__s_ok;
#if (0)
	if (__failed(this->Grid().Update(this->m_size))) {
		this->m_error = this->Grid().Error();
	}
#endif
	return this->Error();
}

CViewPort&  CViewPort::operator = (const CViewPort& _src) { this->m_size = _src.m_size; this->m_error = _src.Error(); return *this; }
CViewPort&  CViewPort::operator << (const t_rect& _rect) { this->Set(_rect); return *this; }

float CViewPort::operator << (const int32_t _n_x) const { return this->Get_X(_n_x); }
float CViewPort::operator >> (const int32_t _n_y) const { return this->Get_Y(_n_y); }

#pragma endregion