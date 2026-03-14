#ifndef __MATH_ROT_2x2_H_INCLUDED
#define __MATH_ROT_2x2_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Mar-2026 at 09:26:14.318, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' generic data matrix 2x2 rotation interface declaration file;
*/
#include "math.mat.2x2.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace math {

	/* query: what does entry in matrix 2x2 represent x and y in rotation terms >> (Google AI)
	In a standard rotation matrix:
	the 1st column represents the transformed x-axis (the image of the unit vector),
	the 2nd column represents the transformed y-axis (the image of the unit vector).

	The Rotation Matrix:
	for a counterclockwise rotation by an angle 'A', the transformation matrix is defined as:
	cosl:      #0      #1
	rows: #0 [ cos(A) -sin(A) ]
	      #1 [ sin(A)  cos(A) ]
	where,
	the x-basis (col #0): [ cos(A) ] represents the new position of the point (1,0); how origin x-coord contributes to the new x and y values;
	                      [ sin(A) ]
	the y-baaia (col #1): [-sin(A) ] represents the new position of the point (0,1).
	                      [ cos(A) ]
	Coordinate Transformation:
	  when multiplying a vector [x] 
	                            [y] by this matrix, the resulting coordinates are:
	  x' = x * cos(A) - y * sin(A);
	  y' = x * sin(A) + y * cos(A);
	Key Consideration:
	  The first column is always the "destination" of the X unit vector, and the second column is the "destination" of the Y unit vector.
	  This is a fundamental property of all linear transformation matrices.
	*/
	class c_rotate_2x2 : public c_mat2x2 { typedef c_mat2x2 TBase;
	public:
		c_rotate_2x2 (void); c_rotate_2x2 (const c_rotate_2x2&) = delete; c_rotate_2x2 (c_rotate_2x2&&) = delete; ~c_rotate_2x2 (void) = default;
		c_rotate_2x2 (const c_mat2x2&);
		c_rotate_2x2 (const float _f_angle);

		c_mat2x2& Do (const float _f_angle, c_mat2x2& _to_rot); // rotates input matrix by given rotation angle around axes origin (0,0);
		vec_2&    Do (const float _f_angle, const vec_2& _v_pivot, vec_2& _to_rot, const bool _b_use_eps = false); // rotates point around pivot point;

		c_mat2x2& Prepare (const float _f_angle); // prepares the rotate matrix for angle in degree;

		const
		c_mat2x2& operator ()(void) const;
		c_mat2x2& operator ()(void);

		c_rotate_2x2& operator <<(const float _f_angle); // prepares this matrix for rotation;
		c_mat2x2& operator ^ (c_mat2x2&) const;      // rotates input matrix; it is assumed *this* matrix is prepared for rotation;

	private:
		c_rotate_2x2& operator = (const c_rotate_2x2&) = delete; c_rotate_2x2& operator = (c_rotate_2x2&&) = delete;
	};

}}}}

typedef ex_ui::draw::open_gl::math::c_rotate_2x2 rot_2x2_t;

#endif/*__MATH_ROT_2x2_H_INCLUDED*/