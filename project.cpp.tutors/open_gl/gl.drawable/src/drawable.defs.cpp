/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Apr-2026 at 12:30:57.965, UTC+4, Batumi, Sunday;
	This is Ebo Pack drawable object common definition file;
*/
#include "drawable.defs.h"
#include "view.port.h"

using namespace shared::drawable;
using namespace ::open_gl::views;

namespace shared { namespace drawable { namespace _impl_d { void __warning_lnk_4221 (void) {}

}}} using namespace shared::drawable::_impl_d;

#pragma region cls::c_angle{}

using ex_ui::draw::open_gl::math::defs::deg_2_rad;
using ex_ui::draw::open_gl::math::defs::rad_2_deg;

c_angle::c_angle (const float _f_degrees) : m_degrees(0.0f), m_radians(0.0f) { *this << _f_degrees; }
c_angle::c_angle (const c_angle& _src) : c_angle() { *this = _src; }

float c_angle::Degrees (void) const  { return this->m_degrees; } 
float c_angle::Degrees (const float _f_degrees) { this->m_degrees = _f_degrees; return this->m_radians = (this->m_degrees * deg_2_rad); }

float c_angle::Radians (void) const  { return this->m_radians; } 
float c_angle::Radians (const float _f_radians) { this->m_radians = _f_radians; return this->m_degrees = (this->m_radians * rad_2_deg); }

float c_angle::operator << (const float _f_degrees) { return this->Degrees(_f_degrees); }
float c_angle::operator >> (const float _f_radians) { return this->Radians(_f_radians); }

c_angle& c_angle::operator = (const c_angle& _src) { this->m_degrees = _src.Degrees(); this->m_radians = _src.Radians(); return *this; }

CString c_angle::To_str (const bool _b_radians) const {
	_b_radians;
	static _pc_sz p_pat_deg = _T("%.7f deg.");
	static _pc_sz p_pat_rad = _T("%.7f rad.");

	CString cs_out; cs_out.Format(_b_radians ? p_pat_rad : p_pat_deg, _b_radians ? this->Radians() : this->Degrees());
	return  cs_out;
}

#pragma endregion
#pragma region cls::c_view_matrix{}

c_view_matrix::c_view_matrix (void) : base_t() {}
	/* cols:  #0   #1   #2   #3    entry/cell is of interest;
	rows: #0 1.0  0.0  0.0  X.X << for along x-axis shift;
	      #1 0.0  1.0  0.0  Y.Y << for along y-axis shift;
	      #2 0.0  0.0  1.0  Z.Z << for along z-axis shift; 
	      #3 0.0  0.0  0.0  1.0
	*/
float&  c_view_matrix::Shift_X (const int32_t _delta_x) {
	return ((*this)().Cell(3, 0) += ::Get_ViewPorts().Active().Get_X(_delta_x));
}

float&  c_view_matrix::Shift_Y (const int32_t _delta_y) {
	return ((*this)().Cell(3, 1) += ::Get_ViewPorts().Active().Get_Y(_delta_y));
}

float&  c_view_matrix::Shift_Z (const int32_t _wheel_value) {
	return ((*this)().Cell(3, 2) += float(_wheel_value));
}

const
c_mat4x4& c_view_matrix::operator ()(void) const { return (base_t&)*this; }
c_mat4x4& c_view_matrix::operator ()(void)       { return (base_t&)*this; }

#pragma endregion