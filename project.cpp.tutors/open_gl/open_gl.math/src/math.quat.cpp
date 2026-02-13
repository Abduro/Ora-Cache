/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Feb-2026 at 11:17:23.834, UTC+4, Batumi, Friday;
	This is Ebo Pack math quaternion wrapper interface implementation file; 
*/
#include "math.quat.h"

using namespace ex_ui::draw::open_gl::math;

#pragma region s_quat{}

s_quat::s_quat (void) : w(0.0f) {}
s_quat::s_quat (const vec_3& _axis, const float _w) : v_3(_axis), w(_w) {}
s_quat::s_quat (const float _x, const float _y, const float _z, const float _w) : v_3(_x, _y, _z), w(_w) {}

s_quat& s_quat::Conjugate (void) {
	this->v_3.Negate(); return *this;
}

float   s_quat::Get_length (void) const {
	return ::sqrtf(this->Sum2());
}

c_mat4x4 s_quat::Get_mat4x4 (void) const {
	/* the result matrix for unit quaternion:
	[ 1 - (y * (y + y) + z * (z + z)), x * (y + y) - w * (z + z)      , x * (z + z) + w * (y + y)      , 0 ]
	[ x * (y + y) + w * (z + z)      , 1 - (x * (x + x) + z * (z + z)), y * (z + z) - w * (x + x)      , 0 ]
	[ x * (z + z) - w * (y + y)      , y * (z + z) + w * (x + x)      , 1 - (x * (x + x) + y * (y + y)), 0 ]
	[ 0                              , 0                              , 0                              , 1 ]
	*/
	const t_seq_3 x_y_z_0 = {this->v_3.x * 2.0f, this->v_3.y * 2.0f, this->v_3.z * 2.0f};                   // x + x | y + y | z + z ;
	const t_seq_3 x_y_z_1 = {this->v_3.x * x_y_z_0[0], this->v_3.x * x_y_z_0[1], this->v_3.x * x_y_z_0[2]}; // x * (x + x) | x * (y + y) | x * (z + z) ;
	const t_seq_3 x_y_z_2 = {this->v_3.y * x_y_z_0[1], this->v_3.y * x_y_z_0[2], this->v_3.z * x_y_z_0[2]}; // y * (y + y) | y * (z + z) | z * (z + z) ;
	const t_seq_3 x_y_z_3 = {this->w * x_y_z_0[0], this->w * x_y_z_0[1], this->w * x_y_z_0[2]};             // w * (x + x) | w * (y + y) | w * (z + z) ;

	return c_mat4x4(t_seq_4x4{
		/*col_#0*/ 1.0f - (x_y_z_2[0] + x_y_z_2[2]),         x_y_z_1[1] + x_y_z_3[2] ,         x_y_z_1[2] - x_y_z_3[1] , 0.0f,
		/*col_#1*/         x_y_z_1[1] - x_y_z_3[2] , 1.0f - (x_y_z_1[0] + x_y_z_2[2]),         x_y_z_2[1] + x_y_z_3[0] , 0.0f,
		/*col_#2*/         x_y_z_1[2] + x_y_z_3[1] ,         x_y_z_2[1] - x_y_z_3[0] , 1.0f - (x_y_z_1[0] + x_y_z_2[0]), 0.0f,
		/*col_#3*/                            0.0f ,                            0.0f ,                            0.0f , 1.0f
	});
	/* for non-union quaternion:
	[ w * w + x * x - y * y - z * z, 2 * x * y - 2 * w * z        , 2 * x * z + 2 * w * y        , 0 ]
	[ 2 * x * y + 2 * w * z        , w * w - x * x + y * y - z * z, 2 * y * z + 2 * w * x        , 0 ]
	[ 2 * x * z - 2 * w * y        , 2 * y * z - 2 * w * x        , w * w - x * x - y * y + z * z, 0 ]
	[ 0                            , 0                            , 0                            , 1 ]
	*/
}

s_quat& s_quat::Invert (void) {

	const float f_sum = this->Sum2();
	if (f_sum < ::defs::f_epsilon)
		return *this;

	s_quat q = *this; *this = q.Conjugate() * (1.0f / f_sum); 

	return *this;
}

s_quat& s_quat::Normalize (void) {

	const float f_sum = this->Sum2();
	if (f_sum < ::defs::f_epsilon)
		return *this;

	const float f_inv_len = 1.0f/::sqrtf(f_sum);
	this->v_3.x *=  f_inv_len;
	this->v_3.y *=  f_inv_len;
	this->v_3.z *=  f_inv_len;
	this->w *= f_inv_len; return *this;
}

s_quat& s_quat::Set (const float _x, const float _y, const float _z, const float _w) {
	_x;_y;_z;_w;
	this->v_3.Set(_x, _y, _z); this->w = _w;
	return *this;
}

s_quat& s_quat::Set (const vec_3& _axis, const float _angle) {
	_axis;_angle;
	// uses only half angle because of double multiplication, qpq*,
    // q at the front and its conjugate at the back;
	vec_3 axis_(_axis); axis_.Normalize(); // converts to unit vector;
	const float angle_ = ::sinf(_angle);   // converts given angle to radians;
	this->w = ::cosf(_angle);
	this->v_3.x = axis_.x * angle_;
	this->v_3.y = axis_.y * angle_;
	this->v_3.z = axis_.z * angle_; return *this;
}

float s_quat::Sum2 (void) const {
	return this->w * this->w + this->v_3.x * this->v_3.x + this->v_3.y * this->v_3.y + this->v_3.z * this->v_3.z;
}

s_quat  s_quat::operator * (const float _f) const {
	return s_quat(this->v_3.x * _f, this->v_3.y * _f, this->v_3.z * _f, this->w * _f);
}
s_quat  s_quat::operator * (const s_quat& _q) const {
	// qq' = [s,v] * [s',v'] = [(ss' - v . v'), v x v' + sv' + s'v] ;
	// *note*: quaternion multiplication is *not* commutative;
	vec_3 v_this (this->v_3);
	vec_3 v_that (_q.v_3);

	vec_3 v_cross = v_this.Get_cross(v_that); // v x v' (cross product);
	vec_3 v_res = v_cross + (this->w * v_that) + (_q.w * v_this);
	float f_dot = v_this.Get_dot(v_that);     // v . v' (inner product);

	return s_quat(v_res, this->w * _q.w - f_dot);
}

#pragma endregion