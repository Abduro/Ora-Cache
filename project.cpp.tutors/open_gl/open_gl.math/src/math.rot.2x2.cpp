/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Mar-2026 at 09:26:14.318, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' generic data matrix 2x2 rotation implementation declaration file;
*/
#include "math.rot.2x2.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

#include "math.vec.2x2.h"

using namespace ex_ui::draw::open_gl::math;

static _pc_sz pc_sz_err_angle = _T("#__e_inv_arg: the rotate angle %.7f is less than epsilon;\n");

__inline bool __chk_angle (const float _f_angle) {
	if (defs::f_epsilon > abs(_f_angle)) {
		__trace_warn_2(pc_sz_err_angle, _f_angle);
		return false;
	}
	else return true;
}

#pragma region cls::c_rotate_2x2{}

c_rotate_2x2::c_rotate_2x2 (void) : TBase() {}
c_rotate_2x2::c_rotate_2x2 (const c_mat2x2& _src) : TBase(_src) {}
c_rotate_2x2::c_rotate_2x2 (const float _f_angle) : TBase() { *this << _f_angle; }

c_mat2x2& c_rotate_2x2::Do (const float _f_angle, c_mat2x2& _to_rot) {
	_f_angle; _to_rot;

	if (false == __chk_angle(_f_angle))
		return _to_rot;

	this->Prepare(_f_angle);
	return _to_rot *= (*this)();
}

vec_2& c_rotate_2x2::Do (const float _f_angle, const vec_2& _v_pivot, vec_2& _to_rot, const bool _b_use_eps/* = false*/) {
	_f_angle; _v_pivot; _to_rot; _b_use_eps;

	if (false == __chk_angle(_f_angle))
		return _to_rot;

	this->Prepare(_f_angle);

	_to_rot = (*this)() *= _to_rot;
	_to_rot += _v_pivot; // adds pivot point coords in order to take into account that the rotation is made around the pivot point;

	if (_b_use_eps) {
		_to_rot.Round();
	}

	return _to_rot;
}

c_mat2x2& c_rotate_2x2::Prepare (const float _f_angle) {
	_f_angle;
	if (false == __chk_angle(_f_angle))
		return *this;

	(*this)().Seed(0.0f);
	const float d_rad = ::defs::deg_2_rad * _f_angle;
	const float f_cos = ::std::cosf(d_rad);
	const float f_sin = ::std::sinf(d_rad);
	/* this is the matrix of rotate angle;
	cols:  #0             #1
	rows:  #0 cos(angle) -sin(angle)
	       #1 sin(angle)  cos(angle)
	*/
#if (0)
	(*this)().m_data = {f_cos, f_sin, -f_sin, f_cos}; // ready for multiplication with the matrix being rotated; it doesn't work;
#else
	TBase::m_data = {f_cos, f_sin, -f_sin, f_cos}; // through typedef it definitely works;
#endif
	return (*this)();
}

const
c_mat2x2& c_rotate_2x2::operator ()(void) const { return (TBase&)(*this); }
c_mat2x2& c_rotate_2x2::operator ()(void)       { return (TBase&)(*this); }

c_rotate_2x2& c_rotate_2x2::operator <<(const float _f_angle) { this->Prepare(_f_angle); return *this; }
c_mat2x2& c_rotate_2x2::operator ^ (c_mat2x2& _mat_2_rot) const {
	_mat_2_rot *= (*this)();
	return _mat_2_rot;
}

#pragma endregion