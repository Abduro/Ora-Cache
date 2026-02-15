/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Feb-2026 at 09:59:32.473, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL 3D virtual camera interface implementation file;
*/
#include "virt_camera.h"

#include "shared.preproc.h"
#include "shared.dbg.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::camera;
using namespace ex_ui::draw::open_gl::camera::opers;

#pragma region cls::CAxes{}

CAxes::CAxes (void) {}
const
vec_3& CAxes::Get (const e_axes _e_axis) const { return this->m_v_axes[_e_axis]; }
vec_3& CAxes::Get (const e_axes _e_axis)       { return this->m_v_axes[_e_axis]; }

#pragma endregion
#pragma region cls::CScene{}

CScene::CScene (void) {}

#pragma endregion
#pragma region cls::CForward{}

CForward::CForward (void) {}

#pragma endregion
#pragma region cls::CPosition{}

CPosition::CPosition(void) {}

const
vec_3& CPosition::Get (void) const { return this->m_coords; }
vec_3& CPosition::Get (void)       { return this->m_coords; }

void   CPosition::Reset (void) {
	this->m_coords.Set(0.0f, 0.0f, 0.0f);
}

#pragma endregion
#pragma region cls::CRotation{}

CRotation::CRotation (void) : m_b_oper(false), m_b_quat(false), m_f_dura(0.0f), m_f_time(0.0f) { this->Reset(); }
const
c_mat4x4& CRotation::Get (void) const { return this->m_rotate; }
c_mat4x4& CRotation::Get (void)       { return this->m_rotate; }
const
s_quat&   CRotation::Quat (void) const { return this->m_quat; }
s_quat&   CRotation::Quat (void)       { return this->m_quat; }

void CRotation::Reset(void) {
	this->Get().Identity();
	this->Quat().Set(0.0f, 0.0f, 0.0f, 1.0f);
}

void CRotation::Set  (const float _x_angle, const float _y_angle, const float _z_angle) {
	_x_angle; _y_angle; _z_angle;
	this->Set(s_vec_3(_x_angle, _y_angle, _z_angle));
}
/* sets transform matrix with rotation angles (degree);
   note: the angle is for camera, so yaw value must be negated for computation;
   the order of rotation is roll->yaw->pitch (rx * ry * rz): { rx - aboux x-axis, pitch; ry - about y-axis, yaw/heading; rz - about z-axis, roll; }
*/
void CRotation::Set  (const s_vec_3 _angles) {
	_angles;
}

const c_mat4x4& CRotation::To_matrix (void) {

	return this->m_rotate;
}
/* converts rotation angles (in degrees) to 4x4 matrix;
   note: the angle is for camera, so yaw angle must be reversed before matrix computation;
*/
const c_mat4x4& CRotation::To_matrix (const s_vec_3& _angle) {
	_angle;
	/*  rx                    ry                     rz
	[ 1, 0     ,  0     ]   [ cos(y), 0, sin(y)]   [ cos(z),-sin(z), 0 ]   
	[ 0, cos(x), -sin(x)] * [      0, 1, 0     ] * [ sin(z), cos(z), 0 ] 
	[ 0, sin(x),  cos(x)]   [-sin(y), 0, cos(y)]   [      0,      0, 1 ]   

	         [ cos(y) * cos(z)                           ,-cos(y) * sin(z),                                     sin(y)]
	       = [ sin(x) * sin(y) * cos(z) + cos(x) * sin(z),-sin(x) * sin(y) * sin(z) + cos(x) * cos(z),-sin(x) * cos(y)] ;
	         [-cos(x) * sin(y) * cos(z) + sin(x) * sin(z), cos(x) * sin(y) * sin(z) + sin(x) * cos(z), cos(x) * sin(y)]
	*/
	// https://en.wikipedia.org/wiki/Theta >> variable angle, particularly in trigonometry, angular position in physics;
	const t_set_3 a_theta = {_angle.x * defs::deg_2_rad, -_angle.y * defs::deg_2_rad, _angle.z * defs::deg_2_rad}; // y-axis angle is reversed;

	const t_set_3 a_cos = {::cosf(a_theta[0]), ::cosf(a_theta[1]), ::cosf(a_theta[2])}; // [0]x;[1]y;[2]z;
	const t_set_3 a_sin = {::sinf(a_theta[0]), ::sinf(a_theta[1]), ::sinf(a_theta[2])}; // [0]x;[1]y;[2]z;

	vec_3 v_left ( a_cos[1] * a_cos[2],  a_sin[0] * a_sin[1] * a_cos[2] + a_cos[0] * a_sin[2],-a_cos[0] * a_sin[1] * a_cos[2] + a_sin[0] * a_sin[2]);
	vec_3 v_up   (-a_cos[1] * a_sin[2], -a_sin[0] * a_sin[1] * a_sin[2] + a_cos[0] * a_cos[2], a_cos[0] * a_sin[1] * a_sin[2] + a_sin[0] * a_cos[2]);
	vec_3 v_frwd ( a_sin[1] ,-a_sin[0] * a_cos[1] , a_cos[0] * a_cos[1] );

	this->m_rotate.Cols().Set(0, v_left);
	this->m_rotate.Cols().Set(1, v_up  );
	this->m_rotate.Cols().Set(2, v_frwd);

	return this->m_rotate;
}

void CRotation::Turn (const float _time_frame) {
	_time_frame;
	this->m_f_time += _time_frame;
	if (this->m_f_time > this->m_f_dura) {
	}
	else {
	}
}

#pragma endregion
#pragma region cls::CTarget{}

CTarget::CTarget (void) : m_dist(CTarget::f_dflt_dist) {}

const
vec_3&  CTarget::Angle (void) const { return this->m_angle; }
vec_3&  CTarget::Angle (void)       { return this->m_angle; }
const
float&  CTarget::Distance (void) const { return this->m_dist; }
float&  CTarget::Distance (void)       { return this->m_dist; }
const
vec_3&  CTarget::Get (void) const { return this->m_coords; }
vec_3&  CTarget::Get (void)       { return this->m_coords; }

void    CTarget::Reset (void) {
	this->Distance() = CTarget::f_dflt_dist;
	this->Get().Set(0.0f, 0.0f, 0.0f);
}

CTarget& CTarget::operator <<(const float _f_dist) { this->Distance() = _f_dist; return *this; }

#pragma endregion
#pragma region cls::CVirtCamera{}

CVirtCamera::CVirtCamera (void) { this->m_error >>__CLASS__<<__METHOD__<<__s_ok; }

TError&  CVirtCamera::Error (void) const { return this->m_error; }

err_code CVirtCamera::Look_at (void) {
	return this->Look_at(this->Pos().Get(), this->Target().Get());
}
err_code CVirtCamera::Look_at (const vec_3& _pos, const vec_3& _tgt) {
	_pos; _tgt;
	this->m_error <<__METHOD__<<__s_ok;
	if (_pos == _tgt) {
	}

	return this->Error();
}
const
CPosition&  CVirtCamera::Pos (void) const { return this->m_pos; }
CPosition&  CVirtCamera::Pos (void)       { return this->m_pos; }

err_code CVirtCamera::Reset (void) {
	this->m_error <<__METHOD__<<__s_ok;

	this->Pos().Reset();
	this->Target().Reset();

	return this->Error();
}
const
CRotation&  CVirtCamera::Rotate (void) const { return this->m_rotate; }
CRotation&  CVirtCamera::Rotate (void)       { return this->m_rotate; }
const
CTarget&    CVirtCamera::Target (void) const { return this->m_target; }
CTarget&    CVirtCamera::Target (void)       { return this->m_target; }

TVirtCam& ::Get_virt_cam (void) {
	static TVirtCam virt_cam;
	return virt_cam;
}

#pragma endregion