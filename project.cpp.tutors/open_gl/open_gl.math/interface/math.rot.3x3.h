#ifndef __MATH_ROT_3x3_H_INCLUDED
#define __MATH_ROT_3x3_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Mar-2026 at 10:36:54.355, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' generic data matrix 3x3 rotation interface declaration file;
*/
#include "math.mat.3x3.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace math {

	/* query: what does entry in matrix 3x3 represent x and y in rotation terms >> (Google AI)
	The Rotation Sub-Matrix:
	For a 2D rotation in homogeneous coordinates: (the rotation angle value is marked as 'a');
	cols:      #0      #1     #2
	rows: #0 [ cos(a) -sin(a) tx ], where the top-left block is the rotation sub-matrix 2x2 [ cos(a) -sin(a) ]
	      #1 [ sin(a)  cos(a) ty ]                                                          [ sin(a)  cos(a) ] ;
	      #2 [ 0       0      1  ]  'tx' and 'ty' is translation values, these entries represent the linear shift of the X & Y coords across the plane.
	      *note*: Z translate coord value equals always to 1;
	Column Representation:
	for rotation sub-matrix 2x2 the column representation is the same as given above for c_rotate_2x2: (some info is being duplicated here);
	col_#0 [ cos(a) ] (X-basis)
	       [ sin(a) ] represents the position of the original unit vector (1, 0) after rotation;
	col_#1 [-sin(a) ] (Y-basis)
	       [ cos(a) ] represents the position of the original unit vector (0, 1) after rotation;
	Coordinate Calculation:
	  x' = x * cos(A) - y * sin(A);
	  y' = x * sin(A) + y * cos(A); applying the 3rd column translation value: these entries represent the linear shift of the X & Y coords across the plane.
	*/
	class c_rotate_3x3 : public c_mat3x3 { typedef c_mat3x3 TBase;
	public:
		c_rotate_3x3 (void); c_rotate_3x3 (const c_rotate_3x3&) = delete; c_rotate_3x3 (c_rotate_3x3&&) = delete; ~c_rotate_3x3 (void) = default;
		c_rotate_3x3 (const c_mat3x3&);
		c_rotate_3x3 (const float _f_angle, const float _x, const float _y, const float _z);

		c_mat3x3& Do (const float _f_angle, const float _x, const float _y, const float _z);  // rotates by a given angle about an axis specified;
		c_mat3x3& Do (const float _f_angle, const vec_3& _axis);

		vec_3 Get_angle (void) const;  // gets rotation angle from this matrix {x:pitch;y:yaw;z:roll};
		vec_3 Get_forward (void) const;
		vec_3 Get_left (void) const;
		vec_3 Get_up (void) const;

		c_mat3x3& operator ()(const float _f_angle, const float _x, const float _y, const float _z); // rotates this matrix by calling this::Do(...);

		const
		c_mat3x3& operator ()(void) const;
		c_mat3x3& operator ()(void);

	private:
		c_rotate_3x3& operator = (const c_rotate_3x3&) = delete; c_rotate_3x3& operator = (c_rotate_3x3&&) = delete;
	};

}}}}

typedef ex_ui::draw::open_gl::math::c_rotate_3x3 rot_3x3_t;

#endif/*__MATH_ROT_3x3_H_INCLUDED*/