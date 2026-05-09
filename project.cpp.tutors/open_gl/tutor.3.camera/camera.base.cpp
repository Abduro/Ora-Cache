/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-May-2026 at 02:02:39.322, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' virtual camera base interface implementation file;
*/
#include "camera.base.h"

using namespace ::open_gl;
using namespace ::open_gl::camera;

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
#pragma region cls::CCamera{}

CCamera::CCamera (void) : m_dist(0.0f) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

const
s_angles& CCamera::Angles (void) const { return this->m_angles; }
s_angles& CCamera::Angles (void)       { return this->m_angles; }

err_code  CCamera::Create (void) {
	this->m_error <<__METHOD__<<__s_ok;

	return this->Error();
}
err_code  CCamera::Destroy(void) {
	this->m_error <<__METHOD__<<__s_ok;

	return this->Error();
}
float     CCamera::Dist (void) const { return this->m_view(3,2); }  // references to z-coord of tranclate column;
float&    CCamera::Dist (void)       { return this->m_view(3,2); }     

TError&   CCamera::Error  (void) const { return this->m_error; }
const
s_pos&    CCamera::Pos (void) const { return this->m_pos; }
s_pos&    CCamera::Pos (void)       { return this->m_pos; }
const
c_mat4x4& CCamera::View (void) const { return this->m_view; }
c_mat4x4& CCamera::View (void)       { return this->m_view; }

#pragma endregion