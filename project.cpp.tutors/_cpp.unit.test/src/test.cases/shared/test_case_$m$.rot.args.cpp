/*
	Cretaed by Tech_dog (ebontrop@gmail.com) on 17-Mar-2026 at 09:58:45.541, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' vector rotation criteria interface implementation file;
*/
#include "test_case_$m$.rot.args.h"

using namespace ebo::boo::test::open_gl::math;

#pragma region struct::s_rot_criteria{}

s_rot_criteria::s_rot_criteria (void) : m_f_angle(0.0f), m_e_axis(axes_t::e_z_axis), m_b_print_cls(true) {}
s_rot_criteria::s_rot_criteria (const float _f_angle, const axes_t::e_axes _e_axis, const bool _b_print_cls)
	: m_f_angle(_f_angle), m_e_axis(_e_axis), m_b_print_cls(_b_print_cls) {
}

_pc_sz s_rot_cri_t::To_str (const float _f_angle, const axes_t::e_axes _e_axis, const bool _b_print/* = false*/) {
	_f_angle; _e_axis; _b_print;
	static CString cs_out; cs_out.Format(pc_sz_fmt_args, _f_angle, axes_t::To_str(_e_axis));
	if (_b_print) _out() += cs_out;
	return (_pc_sz)cs_out;
}

#pragma endregion
#pragma region struct::s_rot_cri_v2{}

s_rot_cri_v2::s_rot_cri_v2 (void) : m_b_use_eps(true) {} // pivot point is set to axes origin (0,0) by default;
s_rot_cri_v2::s_rot_cri_v2 (const t_set_2& _v_pivot, const bool _b_use_eps) : m_b_use_eps(_b_use_eps), m_v_pivot(_v_pivot) {}

const
s_rot_cri_t& s_rot_cri_v2::operator ()(void) const { return (s_rot_cri_t&)(*this); }
s_rot_cri_t& s_rot_cri_v2::operator ()(void)       { return (s_rot_cri_t&)(*this); }

s_rot_cri_v2& s_rot_cri_v2::operator << (const float _f_angle) { s_rot_cri_t::m_f_angle = _f_angle; return *this; }
s_rot_cri_v2& s_rot_cri_v2::operator << (const axes_t::e_axes _e_axis) { s_rot_cri_t::m_e_axis = _e_axis; return *this; }

#pragma endregion
#pragma region struct::s_rot_cri_v3{}

s_rot_cri_v3::s_rot_cri_v3 (void) : m_b_use_eps(true) {} // there is no pivot point;
s_rot_cri_v3::s_rot_cri_v3 (const bool _b_use_eps) : m_b_use_eps(_b_use_eps)/*, m_v_pivot(_v_pivot)*/ {}
const
s_rot_cri_t& s_rot_cri_v3::operator ()(void) const { return (s_rot_cri_t&)(*this); }
s_rot_cri_t& s_rot_cri_v3::operator ()(void)       { return (s_rot_cri_t&)(*this); }

s_rot_cri_v3& s_rot_cri_v3::operator << (const float _f_angle) { s_rot_cri_t::m_f_angle = _f_angle; return *this; }
s_rot_cri_v3& s_rot_cri_v3::operator << (const axes_t::e_axes _e_axis) { s_rot_cri_t::m_e_axis = _e_axis; return *this; }
#pragma endregion
#pragma region struct::s_rot_cri_v4{}

s_rot_cri_v4::s_rot_cri_v4 (void) : m_b_use_eps(true) {} // pivot point is set to axes origin (0,0,0) by default;
s_rot_cri_v4::s_rot_cri_v4 (const t_set_3& _v_pivot, const bool _b_use_eps) : s_rot_cri_v4() { *this << _v_pivot << _b_use_eps; }
const
s_rot_cri_t& s_rot_cri_v4::operator ()(void) const { return (s_rot_cri_t&)*this; }
s_rot_cri_t& s_rot_cri_v4::operator ()(void)       { return (s_rot_cri_t&)*this; }

s_rot_cri_v4& s_rot_cri_v4::operator << (const float  _f_angle) { this->m_f_angle = _f_angle; return *this; }
s_rot_cri_v4& s_rot_cri_v4::operator << (const axes_t::e_axes _e_axis) { this->m_e_axis = _e_axis; return *this; }
s_rot_cri_v4& s_rot_cri_v4::operator << (const vec_3& _v_pivot) { this->m_v_pivot = _v_pivot; return *this; }

#pragma endregion