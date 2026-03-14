#ifndef __MATH_ROT_4x4_H_INCLUDED
#define __MATH_ROT_4x4_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Mar-2026 at 10:36:54.355, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' generic data matrix 4x4 rotation interface declaration file;
*/
#include "math.rot.3x3.h"
#include "math.matrix.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace math {

	class c_rotate_4x4 : public c_mat4x4 {
	public:
		c_rotate_4x4 (const bool _b_identity = true); c_rotate_4x4 (const c_rotate_4x4&) = delete; c_rotate_4x4 (c_rotate_4x4&&) = delete; ~c_rotate_4x4 (void) = default;

		c_mat4x4& Do (const float _f_angle, const float _x, const float _y, const float _z); //  rotates angle(degree) about the given axix;
		c_mat4x4& Do (const float _f_angle, const vec_3&);

		vec_3 Get_angle(void) const; // gets rotation angle from this matrix {x:pitch;y:yaw;z:roll};
		/*rotation around the X-axis (Pitch):
		cols:    #0 #1      #2      #3
		rows: #0  1  0       0       0  cell (0,0) == 1, because this is the rotation around X-axis;
		      #1  0  cos(a) -sin(a)  0  Y-axis coord values change;
		      #2  0  sin(a)  cos(a)  0  Z-axis coord values change;
		      #3  0  0       0       1  *note*: rotation sub-matrix 2x2 at the center of this matrix;
		*/
		c_mat4x4& On_x (const float _f_angle); // rotates on X-axis, the angle is in degrees;
		/*rotation around the Y-axis (Yaw/Heading):
		cols:    #0     #1  #2      #3
		rows: #0  cos(a) 0   sin(a)  0  X-axis coord values change;
		      #1  0      1   0       0  cell (1,1) == 1, because this is the rotation around Y-axis;
		      #2 -sin(a) 0   cos(a)  0  Z-axis coord values change;
		      #3  0      0   0       1
		*/
		c_mat4x4& On_y (const float _f_angle); // rotates on Y-axis, the angle is in degrees;
		/*rotation around the Z-axis (Roll):
		cols:    #0      #1     #2  #3
		rows: #0  cos(a) -sin(a) 0   0  X-axis coord values change;
		      #1  sin(a   cos(a  0   0  Y-axis coord values change;
		      #2  0       0      1   0  cell (2,2) == 1, because this is the rotation around Z-axis;
		      #3  0       0      0   1  *note*: rotation sub-matrix 2x2 at the top-left corner of this matrix;
		*/
		c_mat4x4& On_z (const float _f_angle); // rotates on Z-axis, the angle is in degrees;

		const
		c_mat4x4& operator ()(void) const;
		c_mat4x4& operator ()(void) ;

	private:
		c_rotate_4x4& operator = (const c_rotate_4x4&) = delete; c_rotate_4x4& operator = (c_rotate_4x4&&) = delete;
	};
}}}}

typedef ex_ui::draw::open_gl::math::c_rotate_4x4 rot_4x4_t;

#endif/*__MATH_ROT_4x4_H_INCLUDED*/