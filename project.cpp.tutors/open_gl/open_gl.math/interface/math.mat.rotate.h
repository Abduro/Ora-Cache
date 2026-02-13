#ifndef __MATH_MAT_ROTATE_H_INCLUDED
#define __MATH_MAT_ROTATE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Dec-2025 at 12:16:52.310, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' generic data matrix rotation interface declaration file;
*/
#include "math.matrix.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace math {

	// https://en.wikipedia.org/wiki/Rotation_matrix ;
	class c_rotate_3x3 : public c_mat3x3 { typedef c_mat3x3 TBase;
	public:
		c_rotate_3x3 (void); c_rotate_3x3 (const c_rotate_3x3&) = delete; c_rotate_3x3 (c_rotate_3x3&&) = delete; ~c_rotate_3x3 (void) = default;
		c_rotate_3x3 (const c_mat3x3&);
		c_rotate_3x3 (const float _f_angle, const float _x, const float _y, const float _z);

		c_mat3x3& Do (const float _f_angle, const float _x, const float _y, const float _z);  // rotates by a given angle about an axis specified;
		c_mat3x3& Do (const float _f_angle, const vec_3& _axis);

		vec_3 Get_angle (void) const;  // gets rotation angle from this matrix {x:pitch;y:yaw;z:roll};

		c_mat3x3& operator ()(const float _f_angle, const float _x, const float _y, const float _z); // rotates this matrix by calling this::Do(...);

		const
		c_mat3x3& operator ()(void) const;
		c_mat3x3& operator ()(void);

	private:
		c_rotate_3x3& operator = (const c_rotate_3x3&) = delete; c_rotate_3x3& operator = (c_rotate_3x3&&) = delete;
	};

	class c_rotate_4x4 : public c_mat4x4 {
	public:
		c_rotate_4x4 (void); c_rotate_4x4 (const c_rotate_4x4&) = delete; c_rotate_4x4 (c_rotate_4x4&&) = delete; ~c_rotate_4x4 (void) = default;

		c_mat4x4& Do (const float _f_angle, const float _x, const float _y, const float _z); //  rotates angle(degree) about the given axix;
		c_mat4x4& Do (const float _f_angle, const vec_3&);

		vec_3 Get_angle(void) const;           // gets rotation angle from this matrix {x:pitch;y:yaw;z:roll};

		c_mat4x4& On_x (const float _f_angle); // rotates on X-axis, the angle is in degrees;
		c_mat4x4& On_y (const float _f_angle); // rotates on Y-axis, the angle is in degrees;
		c_mat4x4& On_z (const float _f_angle); // rotates on Z-axis, the angle is in degrees;

		const
		c_mat4x4& operator ()(void) const;
		c_mat4x4& operator ()(void) ;

	private:
		c_rotate_4x4& operator = (const c_rotate_4x4&) = delete; c_rotate_4x4& operator = (c_rotate_4x4&&) = delete;
	};
}}}}

#endif/*__MATH_MAT_ROTATE_H_INCLUDED*/