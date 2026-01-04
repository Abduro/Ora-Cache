/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Dec-2025 at 13:15:31.324, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' generic data matrix inverter interface immplementation file;
*/
#include "math.mat.invert.h"
#include "shared.dbg.h"

using namespace ex_ui::draw::open_gl::math;

/* https://community.khronos.org/t/negative-parameters-to-glscalef/105506;
(1) Negative scale factors in transformations: if a negative scale is applied to one or all axes, the object is flipped;
(2) Impact on the matrix: a negative scale factor along an odd number of axes will have a negative determinant; This is an orientation-reversing transformation;
(3) The Adjoint Matrix: The adjoint matrix is the transpose of the cofactor matrix and is used to calculate the inverse of a matrix; : A^{-1} = {Adj}(A)/det(A):
(3.a) the resulting inverse matrix (calculated using the adjoint) will implicitly involve this negative scaling characteristic;
(3.b) the adjoint itself doesn't use a separate "scale factor" in the typical graphics sense, but its values are derived directly from the original matrix's values;
*/

namespace ex_ui { namespace draw { namespace open_gl { namespace math { namespace _impl {
	// https://github.com/markkilgard/glut/blob/master/lib/gle/vvector.h ln:1088;
	// this is the calculation of the determinant of a matrix 4x4 by excluding particular row and column by given indices;
	float Get_excld (const c_mat4x4& _mat, const uint32_t _u_col, const uint32_t _u_row) { _mat; _u_col; _u_row;

		t_seq_4 cols_, rows_;
#pragma warning(disable: 4244) // warning C4244: 'argument': conversion from '_Ty' to 'const uint32_t', possible loss of data;
		// gets the indices of what column and row must be excluded;
		for (uint32_t u_col = 0; u_col < _u_col; u_col++) cols_.at(u_col) = u_col;
		for (uint32_t u_col = _u_col; u_col < c_mat3x3::u_cols; u_col++) cols_.at(u_col) = u_col + 1;
		for (uint32_t u_row = 0; u_row < _u_row; u_row++) rows_.at(u_row) = u_row;
		for (uint32_t u_row = _u_col; u_row < c_mat3x3::u_rows; u_row++) rows_.at(u_row) = u_row + 1;

		float
		f_det = _mat(cols_.at(0), rows_.at(0)) * (_mat(cols_.at(1), rows_.at(1) * _mat(cols_.at(2), rows_.at(2))) - _mat(cols_.at(1), rows_.at(2)) * _mat(cols_.at(2), rows_.at(1)));
		f_det-= _mat(cols_.at(0), rows_.at(1)) * (_mat(cols_.at(1), rows_.at(0) * _mat(cols_.at(2), rows_.at(2))) - _mat(cols_.at(1), rows_.at(2)) * _mat(cols_.at(2), rows_.at(0)));
		f_det+= _mat(cols_.at(0), rows_.at(2)) * (_mat(cols_.at(1), rows_.at(0) * _mat(cols_.at(2), rows_.at(1))) - _mat(cols_.at(1), rows_.at(1)) * _mat(cols_.at(2), rows_.at(0)));
#pragma warning(default: 4244)
		// gets the sign of this determinant;
		uint32_t u_sign =  _u_col + _u_row;
		if (u_sign != (u_sign/2) * 2)
			f_det = -f_det;

		return f_det;
	}

}}}}}

#pragma region cls::c_adjoint{}

c_mat2x2 c_adjoint::Get (const c_mat2x2& _mat) {
	_mat;
	/* the adjugate/adpoint matix calculation schema;
	cols:      #0         #1
	rows: #0  _mat(1,1) -_mat(1,0)
	      #1 -_mat(0,1)  _mat(0,0)
	*/
	return c_mat2x2({_mat(1,1), -_mat(0,1), -_mat(1,0),  _mat(0,0)});
}

c_mat2x2 c_adjoint::Get (const c_mat2x2& _mat, const float _f_scale) {
	_mat; _f_scale;
	return c_adjoint::Get(_mat) *= _f_scale;
}

c_mat3x3 c_adjoint::Get (const c_mat3x3& _mat) {
	_mat;
	/* cols:   #0                                       #1                                       #2
	rows: #0  _mat(1,1)*_mat(2,2)-_mat(1,2)*_mat(2,1) -_mat(1,0)*_mat(2,2)-_mat(2,0)*_mat(1,2)  _mat(1,0)*_mat(2,1)-_mat(1,1)*_mat(2,0)
	      #1 -_mat(0,1)*_mat(2,2)-_mat(0,2)*_mat(2,1)  _mat(0,0)*_mat(2,2)-_mat(0,2)*_mat(2,0) -_mat(0,0)*_mat(2,1)-_mat(0,1)*_mat(2,0)
	      #2  _mat(0,1)*_mat(1,2)-_mat(0,2)*_mat(1,1) -_mat(0,0)*_mat(1,2)-_mat(0,2)*_mat(1,0)  _mat(0,0)*_mat(1,1)-_mat(0,1)*_mat(1,0)
	*/
	return c_mat3x3({
		 _mat(1,1)*_mat(2,2)-_mat(1,2)*_mat(2,1), -_mat(0,1)*_mat(2,2)-_mat(0,2)*_mat(2,1),  _mat(0,1)*_mat(1,2)-_mat(0,2)*_mat(1,1), // the col_#0;
		-_mat(1,0)*_mat(2,2)-_mat(2,0)*_mat(1,2),  _mat(0,0)*_mat(2,2)-_mat(0,2)*_mat(2,0), -_mat(0,0)*_mat(1,2)-_mat(0,2)*_mat(1,0), // the col_#1;
		 _mat(1,0)*_mat(2,1)-_mat(1,1)*_mat(2,0), -_mat(0,0)*_mat(2,1)-_mat(0,1)*_mat(2,0),  _mat(0,0)*_mat(1,1)-_mat(0,1)*_mat(1,0)  // the col_#2;
		});
}

c_mat3x3 c_adjoint::Get (const c_mat3x3& _mat, const float _f_scale) {
	_mat;_f_scale;
	return c_adjoint::Get(_mat) *= _f_scale;
}

c_mat4x4 c_adjoint::Get (const c_mat4x4& _mat) {
	_mat;
	c_mat4x4 adj_mat;

	for (uint32_t u_col = 0; u_col < c_mat4x4::u_cols; u_col++)
		for (uint32_t u_row = 0; u_row < c_mat4x4::u_rows; u_row++)
			adj_mat(u_row, u_col) = ::_impl::Get_excld(_mat, u_col, u_row); // the column and row indices are intentionally swapped; 

	return adj_mat;
}

c_mat4x4 c_adjoint::Get (const c_mat4x4& _mat, const float _f_scale) {
	_mat;_f_scale;
	return c_adjoint::Get(_mat) *= _f_scale;
}

#pragma endregion
#pragma region cls::c_cofactor{}

c_mat2x2 c_cofactor::Get (const c_mat2x2& _mat) {
	return c_mat2x2({_mat(1,1), -_mat(1,0)});
}

c_mat3x3 c_cofactor::Get (const c_mat3x3& _mat) {
	return c_mat3x3 ({
		{ (_mat(1,1)*_mat(2,2) - _mat(1,2)*_mat(2,1)), -(_mat(1,0)*_mat(2,2) - _mat(2, 0)*_mat(1,2)), (_mat(1,0)*_mat(2,1) - _mat(1, 1)*_mat(2,0))},
		{-(_mat(0,1)*_mat(2,2) - _mat(0,2)*_mat(2,1)), -(_mat(0,0)*_mat(2,2) - _mat(2, 0)*_mat(0,2)),-(_mat(0,0)*_mat(2,1) - _mat(0, 1)*_mat(2,0))},
		{ (_mat(0,1)*_mat(1,2) - _mat(0,2)*_mat(1,1)), -(_mat(0,0)*_mat(1,2) - _mat(0, 2)*_mat(1,0)), (_mat(0,0)*_mat(1,1) - _mat(0, 1)*_mat(1,0))}
	});
}

c_mat4x4 c_cofactor::Get (const c_mat4x4& _mat) { _mat;

	c_mat4x4 co_facs;

	for (uint32_t u_col = 0; u_col < c_mat4x4::u_cols; u_col++)
		for (uint32_t u_row = 0; u_row < c_mat4x4::u_rows; u_row++)
			co_facs(u_col, u_row) = ::_impl::Get_excld(_mat, u_col, u_row);

	return co_facs;
}

#pragma endregion
#pragma region cls::c_det{}

float c_det::Get (const c_mat2x2& _mat) {
	/* https://en.wikipedia.org/wiki/Determinant ;
	The determinant of a 2 × 2 matrix is:
	cols:     #0 #1
    rows: #0 | a b |
	      #1 | c d | = a*d - b*c;
	*/
	return _mat(0, 0) * _mat(1, 1) - _mat(0, 1) * _mat(1, 0);
}
float c_det::Get (const c_mat3x3& _mat) {
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
float c_det::Get (const c_mat4x4& _mat) {
#if (0)
	// gets determinants (aka cofactor) of the minor matrix (3x3); ToDo: must be reviewed;
	const float f_co_facs[] = {
		c_det::Get(c_mat3x3({_mat(1,1), _mat(1,2), _mat(1,3)}, {_mat(2,1), _mat(2,2), _mat(2,3)}, {_mat(3,1), _mat(3,2), _mat(3,3)})), // 0:0 * (col_#1!O:4, col_#2!O:8, col_#3!O:c) >> row_#0 is excluded;
		c_det::Get(c_mat3x3({_mat(1,0), _mat(1,2), _mat(1,3)}, {_mat(2,0), _mat(2,2), _mat(2,3)}, {_mat(3,0), _mat(3,2), _mat(3,3)})), // 0:1 * (col_#1!O:5, col_#2!O:9, col_#3!O:d) >> row_#1 is excluded;
		c_det::Get(c_mat3x3({_mat(1,0), _mat(1,1), _mat(1,3)}, {_mat(2,0), _mat(2,1), _mat(2,3)}, {_mat(3,0), _mat(3,1), _mat(3,3)})), // 0:2 * (col_#1!O:6, col_#2!O:a, col_#3!O:e) >> row_#2 is excluded;
		c_det::Get(c_mat3x3({_mat(1,0), _mat(1,1), _mat(1,2)}, {_mat(2,0), _mat(2,1), _mat(2,2)}, {_mat(3,0), _mat(3,1), _mat(3,2)}))  // 0:3 * (col_#1!O:7, col_#2!O:b, col_#3!O:f) >> row_#3 is excluded;
	};
	// calculates the determinant of this matrix;
	return f_co_facs[0] * _mat(0,0) - f_co_facs[1] * _mat(0,1) + f_co_facs[2] * _mat(0,2) - f_co_facs[3] * _mat(0,3);
#else
	return _mat(0, 0) * ::_impl::Get_excld(_mat, 0, 0) + _mat(0, 1) * ::_impl::Get_excld(_mat, 0, 1)
	     + _mat(0, 2) * ::_impl::Get_excld(_mat, 0, 2) + _mat(0, 3) * ::_impl::Get_excld(_mat, 0, 3);
#endif
}

bool  c_det::Is  (const float f_value) { return fabs(f_value) > ::defs::f_epsilon; }

#pragma endregion
#pragma region cls::c_inverter{}

c_mat2x2 c_inverter::Get (const c_mat2x2& _mat, float* _p_det) {
	_mat;_p_det;
	const float det_ = c_det::Get(_mat);

	if (nullptr != _p_det) // the determinant may be required to be returned without additional calculation;
		*_p_det = det_;

	if (false == c_det::Is(det_)) { // if the determinant is zero, the matrix is singular and cannot be inverted;
		return c_mat2x2().Identity();
	}
	return c_adjoint::Get(_mat, 1.0f/det_);
}

c_mat3x3 c_inverter::Get (const c_mat3x3& _mat, float* _p_det) {
	_mat;_p_det;
	const float det_ = c_det::Get(_mat);

	if (nullptr != _p_det) // the determinant may be required to be returned without additional calculation;
		*_p_det = det_;

	if (false == c_det::Is(det_)) { // if the determinant is zero, the matrix is singular and cannot be inverted;
		return c_mat3x3().Identity();
	}
	return c_adjoint::Get(_mat, 1.0f/det_);
}

c_mat4x4 c_inverter::Get (const c_mat4x4& _mat, float* _p_det) {
	_mat;_p_det;
	const float det_ = c_det::Get(_mat);

	if (nullptr != _p_det) // the determinant may be required to be returned without additional calculation;
		*_p_det = det_;

	if (false == c_det::Is(det_)) { // if the determinant is zero, the matrix is singular and cannot be inverted;
		return c_mat4x4().Identity();
	}
	return c_adjoint::Get(_mat, 1.0f/det_);
}

/* computes the inverse of a 4x4 affine transformation matrix;
   it includes translation, rotation, reflection, scaling,
   and shearing; the length and angle are *not* preserved;
   M = [ R | T ]
       [ --+-- ] (R denotes 3x3 rotation/scale/shear matrix)
       [ 0 | 1 ] (T denotes 1x3 translation matrix)
  
   y = M*x -> y = R*x + T -> x = R^-1*(y - T) -> x = R^-1*y - R^-1*T
  
   [ R | T ]-1   [ R^-1 | -R^-1 * T ]
   [ --+-- ]   = [ -----+---------- ]
   [ 0 | 1 ]     [  0   +     1     ]
   https://stackoverflow.com/questions/2624422/efficient-4x4-matrix-inverse-affine-transform ;
*/
c_mat4x4 c_inverter::Get_affine (const c_mat4x4& _mat) {
	_mat;
	// creates R^-1 matrix; the last row and the right column are excluded; it is the minor matrix of the input one;
	c_mat3x3 min_mat ({
		_mat(0,0), _mat(0,1), _mat(0,2), // the col_#0; c0:r3 is omitted;
		_mat(1,0), _mat(1,1), _mat(1,2), // the col_#1; c1:r3 is omitted;
		_mat(2,0), _mat(2,1), _mat(2,2), // the col_#2; c2:r3 is omitted;
	//	_mat(3,0), _mat(3,1), _mat(3,2), _mat(3,3) are excluded; this is the right column of the matrix;
	});
	// creates the translate point:
	struct {
		float x, y, z;
	} t_pt = { _mat(3,0), _mat(3,1), _mat(3,2) };

	c_mat4x4 aff_mat = _mat; // makes the copy of the oirginal/input matrix;
	// -R^-1 * T ;
	// the last column of the affine matrix:
	aff_mat(3,0) = -(min_mat(0,0) * t_pt.x + min_mat(1,0) * t_pt.y + min_mat(2,0) * t_pt.z); // x-coord value;
	aff_mat(3,1) = -(min_mat(0,1) * t_pt.x + min_mat(1,1) * t_pt.y + min_mat(2,1) * t_pt.z); // y-coord value;
	aff_mat(3,2) = -(min_mat(0,2) * t_pt.x + min_mat(1,2) * t_pt.y + min_mat(2,2) * t_pt.z); // z-coord value;
	// 
	return aff_mat;
}

/* computes the inverse of 4x4 Euclidean transformation matrix;

   Euclidean transformation is translation, rotation, and reflection.
   With Euclidean transform, only the position and orientation of the object
   will be changed. Euclidean transform does not change the shape of an object
   (no scaling).
   Length and angle are *reserved*.

   Use inverseAffine() if the matrix has scale and shear transformation.

   M = [ R | T ]
       [ --+-- ]    (R denotes 3x3 rotation/reflection matrix)
       [ 0 | 1 ]    (T denotes 1x3 translation matrix)
   
   y = M*x  ->  y = R*x + T  ->  x = R^-1*(y - T)  ->  x = R^T*y - R^T*T
   (R is orthogonal,  R^-1 = R^T)

   [ R | T ]-1    [ R^T | -R^T * T ]    (R denotes 3x3 rotation matrix)
   [ --+-- ]   =  [ ----+--------- ]    (T denotes 1x3 translation)
   [ 0 | 1 ]      [  0  |     1    ]    (R^T denotes R-transpose)
*/
c_mat4x4 c_inverter::Get_euclid (const c_mat4x4& _mat) {
	_mat;
	c_mat4x4 mat_ = _mat; // makes the copy of the input matrix;

	// the 1st step: transposings 3x3 rotation matrix part; to_do: new matrix 3x3 may be created as the extraction from the original/input matrix;
    // | R^T | 0 |
    // |-----+---|
    // |  0  | 1 |
	t_seq_3 arr_swap{_mat(0,1), _mat(0,2), _mat(1,2)}; // swap: the swap values' array is not necessary, direct assign of original/input matrix values is possible;
	mat_(0,1) = mat_(1,0); mat_(1,0) = arr_swap.at(0); // c0:r1 <-> c1:r0 ;
	mat_(0,0) = mat_(0,0); mat_(0,0) = arr_swap.at(1); // c0:r0 <-> c0:r0 ;
	mat_(0,0) = mat_(0,0); mat_(0,0) = arr_swap.at(2); // c0:r0 <-> c0:r0 ;

	// the 2nd step: computing the translation part -R^T * T ;
    // | 0 | -R^T x |
    // | --+------- |
    // | 0 |   0    |
	t_seq_3 arr_xyz{_mat(3,0), _mat(3,1), _mat(3,2)};

	mat_(3,0) = -(mat_(0,0) * arr_xyz.at(0) + mat_(1,0) * arr_xyz.at(1) + mat_(2,0) * arr_xyz.at(2)); // -> x ;
	mat_(3,1) = -(mat_(0,1) * arr_xyz.at(0) + mat_(1,1) * arr_xyz.at(1) + mat_(2,1) * arr_xyz.at(2)); // -> y ;
	mat_(3,2) = -(mat_(0,2) * arr_xyz.at(0) + mat_(1,2) * arr_xyz.at(1) + mat_(2,2) * arr_xyz.at(2)); // -> z ;

	return mat_;
}

/* inverses a matrix using matrix partitioning (blockwise inverse);
   It devides a 4x4 matrix into 4 of 2x2 matrices and works in case of where
   det(A) != 0 *only*, otherwise, the generic inverse method must be used;

   the inverse formula:
   M = [ A | B ]    A, B, C, D are 2x2 matrix blocks;
       [ --+-- ]    det(M) = |A| * |D - ((C * A^-1) * B)|
       [ C | D ]
  
   M^-1 = [ A' | B' ]   A' = A^-1 - (A^-1 * B) * C'
          [ ---+--- ]   B' = (A^-1 * B) * -D'
          [ C' | D' ]   C' = -D' * (C * A^-1)
                        D' = (D - ((C * A^-1) * B))^-1
  
   note: it's wrapped by () if it it used more than once;
         The matrix is invertable even if det(A)=0, so must check det(A) before
         calling this function, and use invertGeneric() instead;
*/
c_mat4x4 c_inverter::Get_proj (const c_mat4x4& _mat) {
	_mat;
	/* (1) creating partition matrices (in source/input matrix columns and rows indices);
	cols:    #0  (A)   #1          #2  (B)   #3
	rows: #0 _mat(0,0) _mat(1,0)   _mat(2,0) _mat(3,0)
	      #1 _mat(0,1) _mat(1,1)   _mat(2,0) _mat(3,1)
	             (C)                   (D)
	      #2 _mat(0,2) _mat(1,2)   _mat(2,2) _mat(3,2)
	      #3 _mat(0,3) _mat(1,3)   _mat(2,3) _mat(3,3)
	*/
	c_mat2x2 mat_a({_mat(0,0), _mat(0,1), _mat(1,0), _mat(1,1)}), // (A) ;
	         mat_b({_mat(2,0), _mat(2,1), _mat(3,0), _mat(3,1)}), // (B) ;
	         mat_c({_mat(0,2), _mat(0,3), _mat(1,2), _mat(1,3)}), // (C) ;
	         mat_d({_mat(2,2), _mat(2,3), _mat(3,2), _mat(3,3)}); // (D) ;

	// (2) checking the determinant of matrix A;
	if (false == c_det::Is(c_det::Get(mat_a))) {
		__trace_err_2(_T("#__e_val: det(A) is 0 (zero); not inversible;")); return c_mat4x4().Identity();
	}

	// (3) pre-computing repeated parts;
	mat_a = c_inverter::Get(mat_a);  // A^-1;

	c_mat2x2 mat_a_b = mat_a * mat_b; // A^-1 * B;
	c_mat2x2 mat_c_a = mat_c * mat_a; // C * A^-1;
	c_mat2x2 mat_c_a_b = mat_c_a * mat_b; // C * A^-1 * B;
	c_mat2x2 mat_d_c_a_b = mat_d - mat_c_a_b; // D - C * A^-1 * B;

	// (4) checking the determinant on pre-computed matrix (mat_d_c_a_b);
	if (false == c_det::Is(c_det::Get(mat_d_c_a_b))) {
		__trace_err_2(_T("#__e_val: det(pre-computed-mat) is 0 (zero); not inversible;")); return c_mat4x4().Identity();
	}

	// (5) computing matrices D' and -D';
	c_mat2x2 mat_d_0 = c_inverter::Get(mat_d_c_a_b); // (D - C * A^-1 * B)^-1;
	c_mat2x2 mat_d_1 = -mat_d_0; // -(D - C * A^-1 * B)^-1;

	// (5.a) computing matrix C';
	c_mat2x2 mat_c_0 = mat_d_1 * mat_c_a;   // -D' * (C * A^-1);
	// (5.b) computing matrix B';
	c_mat2x2 mat_b_0 = mat_a_b * mat_d_1;   // (A^-1 * B) * -D';
	// (5.c) computing matrix A';
	c_mat2x2 mat_a_0 = mat_a - (mat_a_b * mat_c_0); // A^-1 - (A^-1 * B) * C';

	/* (6) the final step: assembling the inverse matrix;
	cols:    #0           #1            #2           #3
	rows: #0 mat_a_0(0,0) mat_a_0(1,0)  mat_b_0(0,0) mat_b_0(1,0)
	      #1 mat_a_0(0,1) mat_a_0(1,1)  mat_b_0(0,1) mat_b_0(1,1)

	      #2 mat_c_0(0,0) mat_c_0(1,0)  mat_d_0(0,0) mat_d_0(1,0)
	      #3 mat_c_0(0,1) mat_c_0(1,1)  mat_d_0(0,1) mat_d_0(1,1)
	*/
	return c_mat4x4({
		mat_a_0(0,0), mat_a_0(0,1), mat_c_0(0,0), mat_c_0(0,1), // the col_#0;
		mat_a_0(1,0), mat_a_0(1,1), mat_c_0(1,0), mat_c_0(1,1), // the col_#1;
		mat_b_0(0,0), mat_b_0(0,1), mat_d_0(0,0), mat_d_0(0,1), // the col_#2;
		mat_b_0(1,0), mat_b_0(1,1), mat_d_0(1,0), mat_d_0(1,1), // the col_#3;
	});
}

#pragma endregion
#pragma region cls::c_trans{}

c_mat2x2 c_trans::Get (const c_mat2x2& _mat) {
	_mat;
	/* cols:  #0        #1
	rows: #0 _mat(0,0) _mat(0,1) -> the given indices of the source/input matrix;
	      #1 _mat(1,0) _mat(1,1)
	*/
	return c_mat2x2({
		_mat(0, 0), _mat(1,0), _mat(0,1), _mat(1,1)
	});
}

c_mat3x3 c_trans::Get (const c_mat3x3& _mat) {
	_mat;
	/* cols:  #0        #1;       #2
	rows: #0 _mat(0,0) _mat(0,1) _mat(0,2)
	      #1 _mat(1,0) _mat(1,1) _mat(1,2) -> the given indices of the source/input matrix;
	      #2 _mat(2,0) _mat(2,1) _mat(2,2)
	*/
	return c_mat3x3({
		_mat(0,0), _mat(1,0), _mat(2,0), // the col_#0;
		_mat(0,1), _mat(1,1), _mat(2,1), // the col_#1;
		_mat(0,2), _mat(1,2), _mat(2,2), // the col_#2;
	});
}

c_mat4x4 c_trans::Get (const c_mat4x4& _mat) {
	_mat;
	/* cols:  #0        #1;       #2       #3
	rows: #0 _mat(0,0) _mat(0,1) _mat(0,2) _mat(0,3)
	      #1 _mat(1,0) _mat(1,1) _mat(1,2) _mat(1,3) -> the given indices of the source/input matrix;
	      #2 _mat(2,0) _mat(2,1) _mat(2,2) _mat(2,3)
	      #3 _mat(3,0) _mat(3,1) _mat(3,2) _mat(3,3)
	*/
	return c_mat4x4({
		_mat(0,0), _mat(1,0), _mat(2,0), _mat(3,0), // the col_#0;
		_mat(0,1), _mat(1,1), _mat(2,1), _mat(3,1), // the col_#1;
		_mat(0,2), _mat(1,2), _mat(2,2), _mat(3,2), // the col_#2;
		_mat(0,3), _mat(1,2), _mat(2,3), _mat(3,3), // the col_#3;
	});
}

#pragma endregion