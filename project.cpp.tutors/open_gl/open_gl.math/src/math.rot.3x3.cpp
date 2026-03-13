/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Mar-2026 at 10:38:15.907, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' generic data matrix 3x3 rotation interface implementation file;
*/
#include "math.rot.3x3.h"

#include "shared.dbg.h"
#include "shared.preproc.h"

using namespace ex_ui::draw::open_gl::math;

#pragma region cls::c_rotate_3x3{}

c_rotate_3x3::c_rotate_3x3 (void) : TBase() {}
c_rotate_3x3::c_rotate_3x3 (const c_mat3x3& _src) : TBase(_src) {}
c_rotate_3x3::c_rotate_3x3 (const float _f_angle, const float _x, const float _y, const float _z) { (*this)(_f_angle, _x, _y, _z); }

vec_2&    c_rotate_3x3::Do (const float _f_angle, vec_2& _to_rot, const bool _b_use_eps/* = false*/) {
	_f_angle; _to_rot; _b_use_eps;
	// (1) prepares this matrix for rotation by given ahgle; this->Prepate uses matrix_2x2::Prepare();
	this->Prepare(_f_angle);
	// (2) calculates the target point coords: x and y; this is also the work for matrix_2x2;
	((c_mat2x2)(*this)()).Mltply(_to_rot);
	// (3) applies the translate point;
	_to_rot += vec_2((*this)()(2,0), (*this)()(2,1));
	return _to_rot;
}

c_mat3x3& c_rotate_3x3::Do (const float _f_angle, const float _x, const float _y, const float _z) {
	_f_angle; _x; _y; _z;
	const float cos_ = ::cosf(_f_angle * ::defs::deg_2_rad);
	const float sin_ = ::sinf(_f_angle * ::defs::deg_2_rad); const float cos_1 = 1.0f - cos_;

	// build rotation matrix [3x3];
	/* cols:     1st                           2nd                           3rd                      
	rows: x 1st  0 = x * x * cos_1 + 0 + cos_  4 = x * y * cos_1 + z *-sin_  8 = x * z * cos_1 + y * sin_
	      y 2nd  1 = y * x * cos_1 + z * sin_  5 = y * y * cos_1 + 0 + cos_  9 = y * z * cos_1 + x *-sin_
	      z 3rd  2 = z * x * cos_1 + y *-sin_  6 = z * y * cos_1 + x * sin_  a = z * z * cos_1 + 0 + cos_
	*/
	// col_#_1
	(*this)()(0, 0) = _x * _x * cos_1 + 0 + cos_; // 0 x
	(*this)()(0, 1) = _y * _x * cos_1 +_z * sin_; // 1 y
	(*this)()(0, 2) = _z * _x * cos_1 -_y * sin_; // 2 z would be: z * x * cos_1 + y *-sin_
	// col_#_2
	(*this)()(1, 0) = _x * _y * cos_1 -_z * sin_; // 4 x would be: x * y * cos_1 + z *-sin_
	(*this)()(1, 1) = _y * _y * cos_1 + 0 + cos_; // 5 y
	(*this)()(1, 2) = _z * _y * cos_1 +_x * sin_; // 6 z
	// col_#_3
	(*this)()(2, 0) = _x * _z * cos_1 +_y * sin_; // 8 x
	(*this)()(2, 1) = _y * _z * cos_1 -_x * sin_; // 9 y would be: y * z * cos_1 + x *-sin_
	(*this)()(2, 2) = _z * _z * cos_1 + 0 + cos_; // a z

	return (c_mat3x3&)*this;
}

c_mat3x3& c_rotate_3x3::Do (const float _f_angle, const vec_3& _axis) { return this->Do(_f_angle, _axis.x, _axis.y, _axis.z); }
/* retrieves angles in degree from rotation matrix, M = rx * ry * rz:
   where, rx - the rotation about x-axis or 'pitch', ry - the rotation about y-axis or 'yaw/heading' and rx - the rotation about z-axis or 'roll';
*/
vec_3 c_rotate_3x3::Get_angle (void) const {
	/*          rx('pitch')            ry('yaw')              rz('roll')
	cols:       0  1       2           0       1  2           0        1       2 
	rows: 0   [ 1, 0     , 0     ]   [ cos(y), 0, sin(y)]   [ cos(z), -sin(z), 0 ]
	      1   [ 0, cos(x),-sin(x)] * [      0, 1, 0     ] * [ sin(z),  cos(z), 0 ]
	      2   [ 0, sin(x), cos(x)]   [-sin(y), 0, cos(y)]   [ 0     ,  0     , 1 ]
	result:
	      0   [ cos(y) * cos(z)                           , -cos(y) * sin(z)                           ,  sin(y)         ]
	      1 = [ sin(x) * sin(y) * cos(z) + cos(x) * sin(z), -sin(x) * sin(y) * sin(z) + cos(x) * cos(z), -sin(x) * cos(y)]
	      2   [-cos(x) * sin(y) * cos(z) + sin(x) * sin(z),  cos(x) * sin(y) * sin(z) + sin(x) * cos(z),  cos(x) * cos(y)]
	*/
	struct angles { float _pitch; float _roll; float _yaw; } s_angles { 0.0f, 0.0f, 0.0f };
	// (1) _patch = atan(-m[7] / m[8]);
	// (2) _roll  = atan(-m[3] / m[0]);
	if (-(::defs::f_epsilon) < /*m[0]*/(*this)()(0, 0) &&/*m[0]*/(*this)()(0, 0) < ::defs::f_epsilon) {
		s_angles._pitch = ::defs::rad_2_deg * ::atan2f(/*+m[1]*/+(*this)()(0, 1), /*m[4]*/(*this)()(1, 1));
	} else {
		s_angles._pitch = ::defs::rad_2_deg * ::atan2f(/*-m[7]*/-(*this)()(2, 1), /*m[8]*/(*this)()(2, 2));
		s_angles._roll  = ::defs::rad_2_deg * ::atan2f(/*-m[3]*/-(*this)()(1, 0), /*m[0]*/(*this)()(0, 0));
	}
	// (3) _yaw   = asin(m[6]) ;
	s_angles._yaw = ::defs::rad_2_deg * ::asinf(/*m[6]*/(*this)()(2, 0));
	if (0.0f > /*m[8]*/(*this)()(2, 1)) { // uses z-value of forward vector;
		if(0.0f <= s_angles._yaw)         // note: asin() returns -90 ~ +90, so correct the angle range is [-180.0f...+180.0f];
		     s_angles._yaw = 180.0f - s_angles._yaw;
		else s_angles._yaw =-180.0f - s_angles._yaw;
	}
	return vec_3(s_angles._pitch, s_angles._yaw, s_angles._roll);
}

vec_3 c_rotate_3x3::Get_forward (void) const { return vec_3((*this)()(2, 0), (*this)()(2, 1), (*this)()(2, 2)); } // gets data of col_#2 'z';
vec_3 c_rotate_3x3::Get_left (void) const { return vec_3((*this)()(0, 0), (*this)()(0, 1), (*this)()(0, 2)); } //  gets data of col_#0 'x';
vec_3 c_rotate_3x3::Get_up (void) const { return vec_3((*this)()(0, 0), (*this)()(0, 1), (*this)()(0, 2)); } //  gets data of col_#1 'y';

c_mat3x3& c_rotate_3x3::Prepare (const float _f_angle) {
	_f_angle;
	/* create the rotation matrix: it is done by creating rotation sub-matrix 2x2;
	        mat_2x2            this mat_3x3
	cols:   #0      #1         #0  #1  #2
	rows:#0 cos(a) -sin(a) >>  m2  m2   0
	     #1 sin(a)  cos(a)     m2  m2   0
	     #2                     0   0   1
	*/
	(*this)().Identity();
	(*this)().Set(c_rotate_2x2().Prepare(_f_angle));

	return (*this)();
}

c_mat3x3& c_rotate_3x3::operator ()(const float _f_angle, const float _x, const float _y, const float _z) { return this->Do(_f_angle, _x, _y, _z); }
const
c_mat3x3& c_rotate_3x3::operator ()(void) const { return (c_mat3x3&)*this; }
c_mat3x3& c_rotate_3x3::operator ()(void)       { return (c_mat3x3&)*this; }

#pragma endregion