/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Dec-2025 at 13:15:31.324, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' generic data matrix inverter interface immplementation file;
*/
#include "math.mat.invert.h"

using namespace ex_ui::draw::open_gl::math;

#pragma region cls::c_det{}

float Get (const c_mat2x2& _mat) {
	/* https://en.wikipedia.org/wiki/Determinant ;
	The determinant of a 2 × 2 matrix is:
	cols:     #0 #1
    rows: #0 | a b |
	      #1 | c d | = a*d - b*c;
	*/
	return _mat(0, 0) * _mat(1, 1) - _mat(0, 1) * _mat(1, 0);
}
float Get (const c_mat3x3& _mat) {
	/* https://en.wikipedia.org/wiki/Determinant ;
	The determinant of a 3 × 3 matrix is:
	cols:      #0   #1   #2
    rows: #0 | 0(a) 3(b) 6(c)| =   a*  e*  i +   b*  f*  g +   c*  d*  h -   c*  e*  g -   b*  d*  i -   a*  f*  h : in alphabet;
	      #1 | 1(d) 4(e) 7(f)| =   0*  4*  8 +   3*  7*  2 +   6*  1*  5 -   6*  4*  2 -   3*  1*  8 -   0*  7*  5 : in indices of vector elements; 
	      #2 | 2(g) 5(h) 8(i)| = 0:0*1:1*2:2 + 1:0*2:1*0:2 + 2:0*0:1*1:2 - 2:0*1:1*0:2 - 1:0*0:1*2:2 - 0:0*2:1*1:2 : in col:row indices of matrix;
	*/
#if (0)
	return _mat(0,0)*_mat(1,1)*_mat(2,2) + _mat(1,0)*_mat(2,1)*_mat(0,2) + _mat(2,0)*_mat(0,1)*_mat(1,2)
	      -_mat(2,0)*_mat(1,1)*_mat(0,2) - _mat(1,0)*_mat(0,1)*_mat(2,2) - _mat(0,0)*_mat(2,1)*_mat(1,2);
#else
	return _mat(0,0) * (_mat(1,1) * _mat(2,2) - _mat(1,2) * _mat(2,1))
          -_mat(0,1) * (_mat(1,0) * _mat(2,2) - _mat(1,2) * _mat(2,0))
          +_mat(0,2) * (_mat(1,0) * _mat(2,1) - _mat(1,1) * _mat(2,0));
#endif
}
float Get (const c_mat4x4& _mat) {
	// gets determinants (aka cofactor) of the minor matrix (3x3); ToDo: must be reviewed;
	const float f_co_facs[] = {
		c_det::Get(c_mat3x3(vec_3(_mat(1,1), _mat(1,2), _mat(1,3)), vec_3(_mat(2,1), _mat(2,2), _mat(2,3)), vec_3(_mat(3,1), _mat(3,2), _mat(3,3)))), // 0:0 * (col_#1!O:4, col_#2!O:8, col_#3!O:c) >> row_#0 is excluded;
		c_det::Get(c_mat3x3(vec_3(_mat(1,0), _mat(1,2), _mat(1,3)), vec_3(_mat(2,0), _mat(2,2), _mat(2,3)), vec_3(_mat(3,0), _mat(3,2), _mat(3,3)))), // 0:1 * (col_#1!O:5, col_#2!O:9, col_#3!O:d) >> row_#1 is excluded;
		c_det::Get(c_mat3x3(vec_3(_mat(1,0), _mat(1,1), _mat(1,3)), vec_3(_mat(2,0), _mat(2,1), _mat(2,3)), vec_3(_mat(3,0), _mat(3,1), _mat(3,3)))), // 0:2 * (col_#1!O:6, col_#2!O:a, col_#3!O:e) >> row_#2 is excluded;
		c_det::Get(c_mat3x3(vec_3(_mat(1,0), _mat(1,1), _mat(1,2)), vec_3(_mat(2,0), _mat(2,1), _mat(2,2)), vec_3(_mat(3,0), _mat(3,1), _mat(3,2))))  // 0:3 * (col_#1!O:7, col_#2!O:b, col_#3!O:f) >> row_#3 is excluded;
	};
	// calculates the determinant of this matrix;
	return f_co_facs[0] * _mat(0,0) - f_co_facs[1] * _mat(0,1) + f_co_facs[2] * _mat(0,2) - f_co_facs[3] * _mat(0,3);
}

#pragma endregion
#pragma region cls::c_inverter_4x4{}

c_inverter_4x4::c_inverter_4x4 (void) : c_mat4x4() {}

#pragma endregion