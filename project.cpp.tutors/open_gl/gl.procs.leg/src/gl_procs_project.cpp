/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-May-2026 at 09:24:11.246, UTC+4, Batumi, Wednesday;
	This is OpenGL projection related function set wrapper interface implementation file;
*/
#include "gl_procs_project.h"

using namespace ::open_gl::procs::projection;

#pragma region str::f_rect{}

f_rect::f_rect (void) : f_left(0.0f), f_top(0.0f), f_right(0.0f), f_bottom(0.0f) {}
f_rect::f_rect (const f_rect& _src) : f_rect() { *this = _src; }
f_rect::f_rect (const t_rect& _src) : f_rect() { *this <<_src; }
f_rect::f_rect (const float _left, const float _top, const float _right, const float _bottom) : f_rect() { this->Set(_left, _top, _right, _bottom); }

bool   f_rect::Is_empty (const float _threshold /*= ::open_gl::math::defs::f_epsilon*/) const {
	_threshold;
	if (abs(_threshold) > abs(this->f_right - this->f_left)) return true;
	if (abs(_threshold) > abs(this->f_bottom - this->f_top)) return true;
	return false;
}

void   f_rect::Set (const f_rect& _src) {
	this->Set(_src.f_left, _src.f_top, _src.f_right, _src.f_bottom);
}

void   f_rect::Set (const t_rect& _src) {
	if (::IsRectEmpty(&_src)) {
		__trace_warn_2(_T("imput rect is empty!\n")); return;
	}
	this->f_left   = static_cast<float>(_src.left);  this->f_top    = static_cast<float>(_src.top) ;
	this->f_right  = static_cast<float>(_src.right); this->f_bottom = static_cast<float>(_src.bottom);
}

void   f_rect::Set (const float _left, const float _top, const float _right, const float _bottom) {
	this->f_left = _left; this->f_top = _top; this->f_right = _right; this->f_bottom = _bottom;
}

_pc_sz f_rect::To_str (void) const {
	return f_rect::To_str(*this);
}

_pc_sz f_rect::To_str (const f_rect& _rect) {
	static _pc_sz p_f_rect_pat = _T("[left=%.7f;top=%.7f;right==%.7f;bottom=%.7f]");
	static  CString cs_out; cs_out.Format(p_f_rect_pat, _rect.f_left, _rect.f_top, _rect.f_right, _rect.f_bottom);
	return (_pc_sz) cs_out;
}

f_rect& f_rect::operator = (const f_rect& _src) { this->Set(_src);  return *this; }
bool    f_rect::operator <<(const t_rect& _src) { if (::IsRectEmpty(&_src)) return false; this->Set(_src); return true; }

#pragma endregion
#pragma region str::d_rect{}

d_rect::d_rect (void) : d_left(0.0), d_top(0.0), d_right(0.0), d_bottom(0.0) {}
d_rect::d_rect (const d_rect& _src) : d_rect() { *this = _src; }
d_rect::d_rect (const double _left, const double _top, const double _right, const double _bottom) : d_rect() { this->Set(_left, _top, _right, _bottom); }
d_rect::d_rect (const f_rect& _src) : d_rect() { *this << _src; }

void  d_rect::Set (const d_rect& _src) {
	this->Set(_src.d_left, _src.d_top, _src.d_right, _src.d_bottom); // mwmory copy would be better?
}
void  d_rect::Set (const f_rect& _src) {
	this->Set(static_cast<double>(_src.f_left), static_cast<double>(_src.f_top), static_cast<double>(_src.f_right), static_cast<double>(_src.f_bottom));
}

void  d_rect::Set (const double _left, const double _top, const double _right, const double _bottom) {
	this->d_left = _left; this->d_top = _top; this->d_right = _right; this->d_bottom = _bottom;
}

d_rect& d_rect::operator = (const d_rect& _src) { this->Set(_src); return *this; }
d_rect& d_rect::operator <<(const f_rect& _src) { this->Set(_src); return *this; }
const
d_rect& d_rect::operator >>(f_rect& _rect) const {
	_rect.f_left  = static_cast<float>(this->d_left);  _rect.f_top = static_cast<float>(this->d_top);
	_rect.f_right = static_cast<float>(this->d_right); _rect.f_bottom = static_cast<float>(this->d_bottom);
	return *this;
}

#pragma endregion
#pragma region str::f_planes{}

f_planes::f_planes (void) : f_near(0.0f), f_far(0.0f) {}
f_planes::f_planes (const f_planes& _src) : f_planes() { *this = _src; }
f_planes::f_planes (const float _near,  const float _far) : f_planes() { this->Set(_near, _far); }

bool f_planes::Is_singular (const f_planes& _src, CError& _error) {
	_src; _error;

	using namespace ::open_gl::math::defs;

	if (f_epsilon > abs(_src.f_far - _src.f_near) ||
		f_epsilon > abs(_src.f_near - _src.f_far)) {_error <<__e_inv_arg = _T("The z_near and z_far planes have the same value"); return true; }

	return false;
}

err_code f_planes::Is_valid (const f_planes& _src, CError& _error) {
	_src; _error;

	using namespace ::open_gl::math;

	if (true  == Is_negative(_src.f_near) && false == Is_negative(_src.f_far)) return _error <<__e_inv_arg = p_err_neg_value;
	if (false == Is_negative(_src.f_near) && true  == Is_negative(_src.f_far)) return _error <<__e_inv_arg = p_err_neg_value;
	if (true  == Is_negative(_src.f_near) && true  == Is_negative(_src.f_far)) {
		__trace_warn_2(p_warn_no_draw);
		return _error <<__s_false = p_warn_no_draw;
	}

	return _error <<__s_ok;
}

void f_planes::Set (const f_planes& _src) {
	*this = _src;
}
void f_planes::Set (const float _near, const float _far) {
	this->f_near = _near; this->f_far = _far;
}

_pc_sz f_planes::To_str (void) const { return f_planes::To_str(*this); }
_pc_sz f_planes::To_str (const f_planes& _planes) {
	_planes;
	static _pc_sz p_planes_pat = _T("near=%.2f;far=%.2f");
	static  CString cs_out; cs_out.Format(p_planes_pat, _planes.f_near, _planes.f_far);
	return (_pc_sz) cs_out;
}

f_planes&  f_planes::operator = (const f_planes& _src) { this->Set(_src); return *this; }

#pragma endregion
#pragma region str::d_planes{}

d_planes::d_planes (void) : d_near(0.0), d_far(0.0) {}
d_planes::d_planes (const d_planes& _src) : d_planes() { *this = _src; }
d_planes::d_planes (const double _near, const double _far) : d_planes() { this->Set(_near, _far); }
d_planes::d_planes (const f_planes& _src) : d_planes() { *this << _src; }

void d_planes::Set (const d_planes& _src) {
	*this = _src;
}
void d_planes::Set (const f_planes& _src) {
	*this = {static_cast<double>(_src.f_near), static_cast<float>(_src.f_far)};
}
void d_planes::Set (const double _near, const double _far) {
	*this = {_near, _far};
}

d_planes& d_planes::operator = (const d_planes& _src) { this->Set(_src); return *this; }
d_planes& d_planes::operator <<(const f_planes& _src) { this->Set(_src); return *this; }
const
d_planes& d_planes::operator >>(f_planes& _target) const {
	_target = {static_cast<float>(this->d_near), static_cast<float>(this->d_far)}; return *this;
}

#pragma endregion