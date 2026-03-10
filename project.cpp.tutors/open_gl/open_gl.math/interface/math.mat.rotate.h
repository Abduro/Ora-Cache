#ifndef __MATH_MAT_ROTATE_H_INCLUDED
#define __MATH_MAT_ROTATE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Dec-2025 at 12:16:52.310, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' generic data matrix rotation interface declaration file;
*/
#include "math.matrix.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace math {

	// https://en.wikipedia.org/wiki/Rotation_matrix ;
	/*query: what does entry in matrix 2x2 represent x and y in rotation terms >> (Google AI)
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

		c_mat2x2& Prepare (const float _f_angle); // prepares the rotate matrix for angle in degree;

		const
		c_mat2x2& operator ()(void) const;
		c_mat2x2& operator ()(void);

		c_rotate_2x2& operator <<(const float _f_angle); // prepares this matrix for rotation;
		c_mat2x2& operator ^ (c_mat2x2&) const;      // rotates input matrix; it is assumed this matrix is prepared for rotation;

	private:
		c_rotate_2x2& operator = (const c_rotate_2x2&) = delete; c_rotate_2x2& operator = (c_rotate_2x2&&) = delete;
	};
	/*query: what does entry in matrix 3x3 represent x and y in rotation terms >> (Google AI)
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
		      #3  0       0      0   1  *note*: rotation sub-matrix 2x2 at the top-left cerner of this matrix;
		*/
		c_mat4x4& On_z (const float _f_angle); // rotates on Z-axis, the angle is in degrees;

		const
		c_mat4x4& operator ()(void) const;
		c_mat4x4& operator ()(void) ;

	private:
		c_rotate_4x4& operator = (const c_rotate_4x4&) = delete; c_rotate_4x4& operator = (c_rotate_4x4&&) = delete;
	};
}}}}

typedef ex_ui::draw::open_gl::math::c_rotate_2x2 rot_2x2_t;
typedef ex_ui::draw::open_gl::math::c_rotate_4x4 rot_4x4_t;

#endif/*__MATH_MAT_ROTATE_H_INCLUDED*/