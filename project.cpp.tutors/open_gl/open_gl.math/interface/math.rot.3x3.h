#ifndef __MATH_ROT_3x3_H_INCLUDED
#define __MATH_ROT_3x3_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Mar-2026 at 10:36:54.355, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorials' generic data matrix 3x3 rotation interface declaration file;
*/
#include "math.mat.3x3.h"
#include "math.rot.2x2.h"
#include "virt_space.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace math {

	/* query: what does entry in matrix 3x3 represent x and y in rotation terms >> (Google AI)
	The Rotation Sub-Matrix:
	For a 2D rotation in homogeneous coordinates: (the rotation angle value is marked as 'a');
	cols:      #0      #1     #2
	rows: #0 [ cos(a) -sin(a) tx ], where the top-left block is the rotation sub-matrix 2x2 [ cos(a) -sin(a) ]
	      #1 [ sin(a)  cos(a) ty ]                                                          [ sin(a)  cos(a) ] ;
	      #2 [ 0       0      1  ]  'tx' and 'ty' is translation (position offset) values that is the linear shift of the X & Y coords across the plane.
	      *note*: Z translate coord value equals always to 1;
	Column Representation:
	for rotation sub-matrix 2x2 the column representation is the same as given above for c_rotate_2x2: (some info is being duplicated here);
	col_#0 [ cos(a) ] (X-basis)
	       [ sin(a) ] represents the position (orientation) of the original unit vector (1, 0) *after* rotation;
	col_#1 [-sin(a) ] (Y-basis)
	       [ cos(a) ] represents the position (orientation) of the original unit vector (0, 1) *after* rotation;
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

		vec_2&    Do (const float _f_angle, vec_2& _to_rot, const bool _b_use_eps = false);   // rotates given point (vec_2) around Z-axis (z = 1);
		vec_2&    Do (const float _f_angle, const vec_2& _v_pivot, vec_2& _to_rot, const bool _b_use_eps = false); // pivot point is put as translation to this matrix;

		vec_3 Get_angle (void) const;  // gets rotation angle from this matrix {x:pitch;y:yaw;z:roll};
		vec_3 Get_forward (void) const;
		vec_3 Get_left (void) const;
		vec_3 Get_up (void) const;
		/*rotation around the X-axis (Pitch):
		cols:    #0 #1      #2     
		rows: #0  1  0       0       cell (0,0) == 1, because this is the rotation around X-axis;
		      #1  0  cos(a) -sin(a)  Y-axis coord values change;
		      #2  0  sin(a)  cos(a)  Z-axis coord values change;
		*/
		c_mat3x3& On_x (const float _f_angle); // rotates on X-axis, the angle is in degrees;
		/*rotation around the Y-axis (Yaw/Heading):
		cols:    #0     #1  #2     
		rows: #0  cos(a) 0   sin(a)  X-axis coord values change;
		      #1  0      1   0       cell (1,1) == 1, because this is the rotation around Y-axis;
		      #2 -sin(a) 0   cos(a)  Z-axis coord values change;
		*/
		c_mat3x3& On_y (const float _f_angle); // rotates on Y-axis, the angle is in degrees;
		/*rotation around the Z-axis (Roll):
		cols:    #0      #1     #2
		rows: #0  cos(a) -sin(a) 0   X-axis coord values change;
		      #1  sin(a)  cos(a) 0   Y-axis coord values change;
		      #2  0       0      1   cell (2,2) == 1, because this is the rotation around Z-axis;
		*/
		c_mat3x3& On_z (const float _f_angle); // rotates on Z-axis, the angle is in degrees;
		c_mat3x3& Prepare (const float _f_angle, const axes_t::e_axes = axes_t::e_z_axis); // prepares *this* matrix for making rotation by given angle;

		c_mat3x3& operator ()(const float _f_angle, const float _x, const float _y, const float _z); // rotates this matrix by calling this::Do(...);

		const
		c_mat3x3& operator ()(void) const;
		c_mat3x3& operator ()(void);

		c_mat3x3& operator <<(const vec_2& _v_pivot); // sets the pivot/translation point;
		const c_mat3x3& operator >>(vec_2& _v_pivot) const; // gets the pivot/translation point;

	private:
		c_rotate_3x3& operator = (const c_rotate_3x3&) = delete; c_rotate_3x3& operator = (c_rotate_3x3&&) = delete;
	};

}}}}

typedef ex_ui::draw::open_gl::math::c_rotate_3x3 rot_3x3_t;

#endif/*__MATH_ROT_3x3_H_INCLUDED*/