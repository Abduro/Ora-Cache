/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Dec-2025 at 12:20:51.182, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' generic data matrix rotation interface implementation file;
*/
#include "math.mat.rotate.h"

using namespace ex_ui::draw::open_gl::math;

#pragma region cls::c_rotate_3x3{}

c_rotate_3x3::c_rotate_3x3 (void) : TBase() {}
c_rotate_3x3::c_rotate_3x3 (const c_mat3x3& _src) : TBase(_src) {}
c_rotate_3x3::c_rotate_3x3 (const float _f_angle, const float _x, const float _y, const float _z) { (*this)(_f_angle, _x, _y, _z); }

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

c_mat3x3& c_rotate_3x3::operator ()(const float _f_angle, const float _x, const float _y, const float _z) { return this->Do(_f_angle, _x, _y, _z); }
const
c_mat3x3& c_rotate_3x3::operator ()(void) const { return (c_mat3x3&)*this; }
c_mat3x3& c_rotate_3x3::operator ()(void)       { return (c_mat3x3&)*this; }

#pragma endregion
#pragma region cls::c_rotate_4x4{}

c_rotate_4x4::c_rotate_4x4 (void) : c_mat4x4() {}

c_mat4x4& c_rotate_4x4::Do (const float _f_angle, const float _x, const float _y, const float _z) {
	_f_angle; _x; _y; _z;
	const float cos_ = ::cosf(_f_angle * ::defs::deg_2_rad);
	const float sin_ = ::sinf(_f_angle * ::defs::deg_2_rad); const float cos_1 = 1.0f - cos_;

	// copies original data before making the calculations;
	struct {
		float _x; // indices: 0|4|8|c;
		float _y; // indices: 1|5|9|d;
		float _z; // indices: 2|6|a|e;
	}
	col_0 {(*this)()(0, 0), (*this)()(0, 1), (*this)()(0, 2)}, // col_#_1: x, y, z; w:3 excluded;
	col_1 {(*this)()(1, 0), (*this)()(1, 1), (*this)()(1, 2)}, // col_#_2: x, y, z; w:7 excluded;
	col_2 {(*this)()(2, 0), (*this)()(2, 1), (*this)()(2, 2)}, // col_#_3: x, y, z; w:b excluded;
	col_3 {(*this)()(3, 0), (*this)()(3, 1), (*this)()(3, 2)}; // col_#_4: x, y, z; w:f excluded;

	c_rotate_3x3 rot(_f_angle, _x, _y, _z);

	// multiplies view matrix by rotation matrix;
	/* cols:     1st                              2nd                              3rd                              4th
	rows: x 1st  0 = r0 * 0' + r4 * 1' + r8 * 2'  4 = r0 * 4' + r4 * 5' + r8 * 6'  8 = r0 * 8' + r4 * 9' + r8 * a'  c = r0 * c' + r4 * d' + r8 * e'
	      y 2nd  1 = r1 * 0' + r5 * 1' + r9 * 2'  5 = r1 * 4' + r5 * 5' + r9 * 6'  9 = r1 * 8' + r5 * 9' + r9 * a'  d = r1 * c' + r5 * d' + r9 * e'
	      z 3rd  2 = r2 * 0' + r6 * 1' + ra * 2'  6 = r2 * 4' + r6 * 5' + ra * 6'  a = r2 * 8' + r6 * 9' + ra * a'  e = r2 * c' + r6 * d' + ra * e'
	      w : excluded;
	*/
	// col_#_1
    (*this)()(0, 0) = rot()(0, 0) * col_0._x + rot()(1, 0) * col_0._y + rot()(2, 0) * col_0._z;  // 0 = 1st row of rotate matrix [0|4|8] * 1st col of the view matrix [0|1|2];
    (*this)()(0, 1) = rot()(0, 1) * col_0._x + rot()(1, 1) * col_0._y + rot()(2, 1) * col_0._z;  // 1 = 2nd row of rotate matrix [1|5|9] * 1st col of the view matrix [0|1|2];
    (*this)()(0, 2) = rot()(0, 2) * col_0._x + rot()(1, 2) * col_0._y + rot()(2, 2) * col_0._z;  // 2 = 3rd row of rotate matrix [2|6|a] * 1st col of the view matrix [0|1|2];
	// col_#_2
    (*this)()(1, 0) = rot()(0, 0) * col_1._x + rot()(1, 0) * col_1._y + rot()(2, 0) * col_1._z;  // 4 = 1st row of rotate matrix [0|4|8] * 2nd col of the view matrix [4|5|6];
    (*this)()(1, 1) = rot()(0, 1) * col_1._x + rot()(1, 1) * col_1._y + rot()(2, 1) * col_1._z;  // 5 = 2nd row of rotate matrix [1|5|9] * 2nd col of the view matrix [4|5|6];
    (*this)()(1, 2) = rot()(0, 2) * col_1._x + rot()(1, 2) * col_1._y + rot()(2, 2) * col_1._z;  // 6 = 3rd row of rotate matrix [2|6|a] * 2nd col of the view matrix [4|5|6];
	// col_#_3
    (*this)()(2, 0) = rot()(0, 0) * col_2._x + rot()(1, 0) * col_2._y + rot()(2, 0) * col_2._z;  // 8 = 1st row of rotate matrix [0|4|8] * 3rd col of the view matrix [8|9|a];
    (*this)()(2, 1) = rot()(0, 1) * col_2._x + rot()(1, 1) * col_2._y + rot()(2, 1) * col_2._z;  // 9 = 2nd row of rotate matrix [1|5|9] * 3rd col of the view matrix [8|9|a];
    (*this)()(2, 2) = rot()(0, 2) * col_2._x + rot()(1, 2) * col_2._y + rot()(2, 2) * col_2._z;  // a = 3rd row of rotate matrix [2|6|a] * 3rd col of the view matrix [8|9|a];
	// col_#_4
    (*this)()(3, 0) = rot()(0, 0) * col_3._x + rot()(1, 0) * col_3._y + rot()(2, 0) * col_3._z;  // c = 1st row of rotate matrix [0|4|8] * 3rd col of the view matrix [c|d|e];
    (*this)()(3, 1) = rot()(0, 1) * col_3._x + rot()(1, 1) * col_3._y + rot()(2, 1) * col_3._z;  // d = 2nd row of rotate matrix [1|5|9] * 3rd col of the view matrix [c|d|e];
    (*this)()(3, 2) = rot()(0, 2) * col_3._x + rot()(1, 2) * col_3._y + rot()(2, 2) * col_3._z;  // e = 3rd row of rotate matrix [2|6|a] * 3rd col of the view matrix [c|d|e];

	return (*this)();
}

c_mat4x4& c_rotate_4x4::Do (const float _f_angle, const vec_3& _coords) { return this->Do(_f_angle, _coords.x, _coords.y, _coords.z); }

vec_3  c_rotate_4x4::Get_angle (void) const {
	return c_rotate_3x3(c_mat3x3(
		{(*this)()(0, 0),(*this)()(0, 1),(*this)()(0, 2)},
		{(*this)()(1, 0),(*this)()(1, 1),(*this)()(1, 2)},
		{(*this)()(2, 0),(*this)()(2, 1),(*this)()(2, 2)})
	).Get_angle();
}

c_mat4x4& c_rotate_4x4::On_x (const float _f_angle) {
	_f_angle;
	const float cos_ = ::cosf(_f_angle * ::defs::deg_2_rad);
	const float sin_ = ::sinf(_f_angle * ::defs::deg_2_rad);
	// copies original data before making the calculations;
	struct {
		float _y; // indices: 1|5|9|d;
		float _z; // indices: 2|6|a|e;
	}
	col_0 {(*this)()(0, 1), (*this)()(0, 2)}, // col_#_1: y, z; x:0 & w:3 excluded;
	col_1 {(*this)()(1, 1), (*this)()(1, 2)}, // col_#_2: y, z; x:4 & w:7 excluded;
	col_2 {(*this)()(2, 1), (*this)()(2, 2)}, // col_#_3: y, z; x:8 & w:b excluded;
	col_3 {(*this)()(3, 1), (*this)()(3, 2)}; // col_#_4: y, z; x:c & w:f excluded;

	/* cols:     1st                        2nd                        3rd                        4th
	x-axis: 1st  0                          4                          8                          c :excluded;
	rows  : 2nd  1 = 1' * cos_ + 2' *-sin_  5 = 5' * cos_ + 6' *-sin_  9 = 9' * cos_ + a' *-sin_  d = d' * cos_ + e' *-sin_
	        3rd  2 = 1' * sin_ + 2' * cos_  6 = 5' * sin_ + 6' * cos_  a = 9' * sin_ + a' * cos_  e = d' * sin_ + e' * cos_
	w-dir : 4th  3                          7                          b                          f :excluded;
	*/
	// calculus: formula (applied to indices of this matrix data vector);
	// col_#_1
	(*this)()(0, 1) = col_0._y * cos_ + col_0._z *-sin_; // #this = #this * cos + #next *-sin ; where: cos is the math.cos(rotate angle in degrees);
	(*this)()(0, 2) = col_0._y * sin_ + col_0._z * cos_; // #this = #prev * sin + #this * cos ;        sin is the math.sin(rotate angle in degrees);
	// col_#_2
	(*this)()(1, 1) = col_1._y * cos_ + col_1._z *-sin_;
	(*this)()(1, 2) = col_1._y * sin_ + col_1._z * cos_;
	// col_#_3
	(*this)()(2, 1) = col_2._y * cos_ + col_2._z *-sin_;
	(*this)()(2, 2) = col_2._y * sin_ + col_2._z * cos_;
	// col_#_4
	(*this)()(3, 1) = col_3._y * cos_ + col_3._z *-sin_;
	(*this)()(3, 2) = col_3._y * sin_ + col_3._z * cos_;

	return (*this)();
}

c_mat4x4& c_rotate_4x4::On_y (const float _f_angle) {
	_f_angle;
	const float cos_ = ::cosf(_f_angle * ::defs::deg_2_rad);
	const float sin_ = ::sinf(_f_angle * ::defs::deg_2_rad);
	// copies original data before making the calculations;
	struct {
		float _x; // indices: 0|4|8|c;
		float _z; // indices: 2|6|a|e;
	}
	col_0 {(*this)()(0, 0), (*this)()(0, 2)}, // col_#_1: x, z; y:1 & w:3 excluded;
	col_1 {(*this)()(1, 0), (*this)()(1, 2)}, // col_#_2: x, z; y:5 & w:7 excluded;
	col_2 {(*this)()(2, 0), (*this)()(2, 2)}, // col_#_3: x, z; y:9 & w:b excluded;
	col_3 {(*this)()(3, 0), (*this)()(3, 2)}; // col_#_4: x, z; y:d & w:f excluded;

	/* cols:     1st                        2nd                        3rd                        4th
	rows  : 1st  0 = 0' * cos + 2' * sin_  4 = 4' * cos_ + 6' * sin_  8 = 8' * cos_ + a' * sin_  c = c' * cos_ + e' * sin_
	y-axis: 2rd  1                          5                          9                          d :excluded;
	        3nd  2 = 0' *-sin_ + 2' * cos_  6 = 4' *-sin_ + 6' * cos_  a = 8' *-sin_ + a' * cos_  e = c' *-sin_ + e' * cos_
	w-dir : 4th  3                          7                          b                          f :excluded;
	*/
	// calculus: formula (applied to indices of this matrix data vector);
	// col_#_1
	(*this)()(0, 0) = col_0._x * cos_ + col_0._z * sin_; // #this = #this * cos  + #after_next * sin ; where: cos is the math.cos(rotate angle in degrees);
	(*this)()(0, 2) = col_0._x *-sin_ + col_0._z * cos_; // #this = #before_prev *-sin + #this * cos ;        sin is the math.sin(rotate angle in degrees);
	// col_#_2
	(*this)()(1, 0) = col_1._x * cos_ + col_1._z * sin_;
	(*this)()(1, 2) = col_1._x *-sin_ + col_1._z * cos_;
	// col_#_3
	(*this)()(2, 0) = col_2._x * cos_ + col_2._z * sin_;
	(*this)()(2, 2) = col_2._x *-sin_ + col_2._z * cos_;
	// col_#_4
	(*this)()(3, 0) = col_3._x * cos_ + col_3._z * sin_;
	(*this)()(3, 2) = col_3._x *-sin_ + col_3._z * cos_;

	return (*this)();
}

c_mat4x4& c_rotate_4x4::On_z (const float _f_angle) {
	_f_angle;
	const float cos_ = ::cosf(_f_angle * ::defs::deg_2_rad);
	const float sin_ = ::sinf(_f_angle * ::defs::deg_2_rad);
	// copies original data before making the calculations;
	struct {
		float _x; // indices: 0|4|8|c;
		float _y; // indices: 1|5|9|d;
	}
	col_0 {(*this)()(0, 0), (*this)()(0, 1)}, // col_#_1: x, y; z:2 & w:3 excluded;
	col_1 {(*this)()(1, 0), (*this)()(1, 1)}, // col_#_2: x, y; z:6 & w:7 excluded;
	col_2 {(*this)()(2, 0), (*this)()(2, 1)}, // col_#_3: x, y; z:a & w:b excluded;
	col_3 {(*this)()(3, 0), (*this)()(3, 1)}; // col_#_4: x, y; z:e & w:f excluded;

	/* cols:     1st                         2nd                         3rd                         4th
	rows:   1st  0 = 0' * cos_ + 1' * -sin_  4 = 4' * cos_ + 5' * -sin_  8 = 8' * cos_ + 9' * -sin_  c = c' * cos_ + d' * -sin_
	        2nd  1 = 0' * sin_ + 1' *  cos_  5 = 4' * sin_ + 5' *  cos_  9 = 8' * sin_ + 9' *  cos_  d = c' * sin_ + d' *  cos_
	z-axis: 3rd  2                           6                           a                           e :excluded;
	w-dir : 4th  3                           7                           b                           f :excluded;
	*/
	// calculus: formula (applied to indices of this matrix data vector);
	// col_#_1
	(*this)()(0, 0) = col_0._x * cos_ + col_0._y *-sin_; // #this = #this * cos + #next * -sin ; where: cos is the math.cos(rotate angle in degrees);
	(*this)()(0, 1) = col_0._x * sin_ + col_0._y * cos_; // #this = #prev * sin + #this *  cos ;        sin is the math.sin(rotate angle in degrees);
	// col_#_2
	(*this)()(1, 0) = col_1._x * cos_ + col_1._y *-sin_;
	(*this)()(1, 1) = col_1._x * sin_ + col_1._y * cos_;
	// col_#_3
	(*this)()(2, 0) = col_2._x * cos_ + col_2._y *-sin_;
	(*this)()(2, 1) = col_2._x * sin_ + col_2._y * cos_;
	// col_#_4
	(*this)()(3, 0) = col_3._x * cos_ + col_3._y *-sin_;
	(*this)()(3, 1) = col_3._x * sin_ + col_3._y * cos_;

	return (*this)();
}

const
c_mat4x4& c_rotate_4x4::operator ()(void) const { return (c_rotate_4x4&)*this; }
c_mat4x4& c_rotate_4x4::operator ()(void)       { return (c_rotate_4x4&)*this; }

#pragma endregion