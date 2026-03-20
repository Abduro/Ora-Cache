/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Dec-2025 at 08:10:22.332, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL math lib matrix uint test interface implementation file; 
*/
#include "ebo_test_$m$.matrix.h"
#include "shared.preproc.h"

using namespace ebo::boo::test::open_gl::math;

#pragma region cls::c_t_rotate_2x2{}

void c_t_rotate_2x2::Matrix (void) {

	t_mat2x2 m_2_rot({0.5f, 0.5f, 0.5f, 0.5f});
	c_rot_2x2 m_mat_rot;

	c_rot_2x2().Rotate(90.0f, m_2_rot);
	
	_out()();
}

void c_t_rotate_2x2::Pivot (void) {
	/*steps:
	(1) create the target vector with the target point on X-axis (x=1.0f;y=0.0f);
	(2) create the pivot point vector in axes origin (x=0.0f;y=0.0f);
	(3) prepare the rotate matrix;
	(4) rotate the target with taking into account the pivot point; 
	*/
	// the 1st test case with pivot point at orign of the axes;
	// expected result: no change for position of rotated vector;
	// (1),(2):
	vec_2  v_2_rot({1.0f, 0.0f}); // on X-axis;
	vec_2  v_pivot({0.0f, 0.0f}); // at the origin;

	// (3),(4):
	const float f_angle = 90.0f;
	c_rot_2x2 m_rot_2x2; m_rot_2x2.Rotate(f_angle, v_pivot, v_2_rot, true);

	// the 2nd test case with pivot point located at *not* the axes origin; 
	// expected result: rotated vector will be moved in accordance with pivot point;
	v_2_rot.Set(1.0f, 0.0f);
	v_pivot.Set(0.0f, 1.0f);

	m_rot_2x2.Rotate(f_angle, v_pivot, v_2_rot, true);

	// the 3rd test case with pivot point located at *not* the axes origin; 
	v_2_rot.Set(1.0f, 0.0f);
	v_pivot.Set(1.0f, 1.0f);

	m_rot_2x2.Rotate(f_angle, v_pivot, v_2_rot, true);

	_out()();
}

void c_t_rotate_2x2::Prepare (void) {

	c_rot_2x2().Prepare(+90.0f);
	c_rot_2x2().Prepare(-90.0f);
	_out()();
}

void c_t_rotate_2x2::Vector (void) {
	/*steps:
	(1) creating the vector with the target point on X-axis (x=1.0f;y=0.0f);
	(2) preparing the rotate matrix for 90 degree angle;
	(3) to get the expected result: x~=0.0f;y=1.0f; for better accuracy of the result values it seems using the comparison with epsilon is required;
	*/
	vec_2  v_2_rot({1.0f, 0.0f});
	c_rot_2x2 m_mat_rot;

	c_rot_2x2().Rotate(+90.0f, v_2_rot, true); v_2_rot.Set(1.0f, 0.0f); // restores the initial values;
	c_rot_2x2().Rotate(-90.0f, v_2_rot, true); v_2_rot.Set(1.0f, 0.0f); // expected result is: x=0.0f;y=-1.0f;
#if (0)
	c_rot_2x2().Rotate(+60.0f, v_2_rot, true); v_2_rot.Set(1.0f, 0.0f);
	/* how to get the sin() and cos() specific value;
	   the angle equals to asinf(val) and acosf(val), where val is required value of the sinf() or cosf(); it gives different angles;
	*/
	const float f_angle_cos = ::acosf(0.5f) * ::defs::rad_2_deg; f_angle_cos;
	const float f_angle_sin = ::asinf(0.5f) * ::defs::rad_2_deg; f_angle_sin;
#endif
	v_2_rot.Set(1.0f, 1.0f); // sets values for getting the angle that is required for these values;
	const float f_req = v_2_rot.Get_angle(true); v_2_rot.Set(1.0f, 0.0f); // restores origin values;

	c_rot_2x2().Rotate(f_req, v_2_rot, true);

	if (::defs::f_epsilon > ::abs(v_2_rot.x - v_2_rot.y)) // checks for valid result: x & y must have the same value for the angle 45;
	_out() += TString().Format(_T("The result is confirmed: x (%.7f) ~= y (%.7f)"), v_2_rot.x, v_2_rot.y); 
	else // equality of x and y coordinates by value (not sign) is available for the following angles only: 45, 135, 225, 315 counter clockwise;
	_out() += TString().Format(_T("[error] The result is not confirmed: x(%.7f) != y(%.7f);"), v_2_rot.x, v_2_rot.y);
	_out()();
}

#pragma endregion