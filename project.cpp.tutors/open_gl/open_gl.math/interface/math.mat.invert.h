#ifndef __MATH_MAT_INVERT_H_INCLUDED
#define __MATH_MAT_INVERT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Dec-2025 at 13:15:31.324, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' generic data matrix inverter interface declaration file;
*/
#include "math.matrix.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace math {
	/* the exerpt from the https://en.wikipedia.org/wiki/Adjugate_matrix :
	...In linear algebra, a minor of a matrix A is the determinant of some smaller square matrix generated from A by removing one or more of its rows and columns.
	   Minors obtained by removing just one row and one column from square matrices are required for calculating matrix *cofactors*,
	   which are useful for computing both the determinant and inverse of square matrices...
	*/
	class c_adjoint {
	public: c_adjoint (void) = default; c_adjoint (const c_adjoint&) = delete; c_adjoint (c_adjoint&&) = delete; ~c_adjoint (void) = default;

	static  c_mat2x2 Get (const c_mat2x2&);  // returns adjoint matrix that is just the transpose of the cofactor matrix;
	static  c_mat2x2 Get (const c_mat2x2&, const float _f_scale);

	static  c_mat3x3 Get (const c_mat3x3&);  // returns adjoint matrix that is just the transpose of the cofactor matrix;
	static  c_mat3x3 Get (const c_mat3x3&, const float _f_scale);

	static  c_mat4x4 Get (const c_mat4x4&);  // returns adjoint matrix that is just the transpose of the cofactor matrix;
	static  c_mat4x4 Get (const c_mat4x4&, const float _f_scale);

	private: c_adjoint& operator = (const c_adjoint&) = delete; c_adjoint& operator = (c_adjoint&&) = delete;
	};
	class c_cofactor {
	public: c_cofactor (void) = default; c_cofactor (const c_cofactor&) = delete; c_cofactor (c_cofactor&&) = delete; ~c_cofactor (void) = default;

	static  c_mat2x2 Get (const c_mat2x2&);
	static  c_mat3x3 Get (const c_mat3x3&);
	static  c_mat4x4 Get (const c_mat4x4&);

	private: c_cofactor& operator = (const c_cofactor&) = delete; c_cofactor& operator = (c_cofactor&&) = delete;
	};
	/* https://en.wikipedia.org/wiki/Determinant ;
	the determinant equals to 0 (zero) if:
	(1) a matrix contains either a row of zeros or a column of zeros;
	(2) 2 (two) rows or columns are the same;
	(3) square matrix rows (or columns) are linearly dependent;
	that leads to:
	(1) the transformation doesn't *invert* (it collapses some vectors to zero); https://www.reddit.com/r/learnmath/comments/rv1q52/any_other_ways_of_telling_that_the_determinant_of/ ;
	(2) geometrically the determinant is the area (for 2x2 matrices) or the volume (for 3x3 and so on);
	    thus, if the determinant equals to 0 (zero) there is no area or no volume; https://medium.com/@mathphye/determinant-equal-to-zero-error-404-not-at-all-c2bc24c4e43c ;
	*/
	class c_det {
	public: c_det (void) = default; c_det (const c_det&) = delete; c_det (c_det&&) = delete; ~c_det (void) = default;

	static float Get (const c_mat2x2&);
	static float Get (const c_mat3x3&);
	static float Get (const c_mat4x4&);

	static bool  Is  (const float f_value); // makes a comparison of input determinant value with epsilon value;

	private: c_det& operator = (const c_det&) = delete; c_det& operator = (c_det&&) = delete;
	};

	/* https://registry.khronos.org/OpenGL-Refpages/gl4/html/inverse.xhtml ;
	for getting the inverse of the matrix:
	(1) calculating the determinant of the natrix; if the determinant is zero, the matrix is singular and cannot be inverted;
	(2) calculating the adjugate matrix adj(A);
	(3) multiplying the adjugate by 1/det(A); the end of story;
	*/
	class c_inverter {
	public:
		c_inverter (void); c_inverter (const c_inverter&) = delete; c_inverter (c_inverter&&) = delete; ~c_inverter (void) = default;

	static c_mat2x2 Get (const c_mat2x2&, float* _p_det = nullptr); // gets the inverse of input matrix, if the matrix is not ivertible (det == 0) an identity matrix is returned;
	static c_mat3x3 Get (const c_mat3x3&, float* _p_det = nullptr); // gets the inverse of input matrix, if the matrix is not ivertible (det == 0) an identity matrix is returned;
	static c_mat4x4 Get (const c_mat4x4&, float* _p_det = nullptr); // gets the inverse of input matrix, if the matrix is not ivertible (det == 0) an identity matrix is returned;
	
	// https://en.wikipedia.org/wiki/Affine_transformation ;
	// https://en.wikipedia.org/wiki/Transformation_matrix#Affine_transformations ;
	static c_mat4x4 Get_affine (const c_mat4x4&); // gets the inverse of affine transform matrix; https://en.wiktionary.org/wiki/affine ;
	static c_mat4x4 Get_euclid (const c_mat4x4&); // gets the inverse of Euclidean transform matrix; https://en.wikipedia.org/wiki/Euclidean ;
	// https://en.wikipedia.org/wiki/Projection_(linear_algebra) ;
	// https://en.wikipedia.org/wiki/Projection_matrix ;
	static c_mat4x4 Get_proj   (const c_mat4x4&); // gets the inverse of projective matrix by using a partitioning;

	private:
		c_inverter& operator = (const c_inverter&) = delete; c_inverter& operator = (c_inverter&&) = delete;
	};

	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/transpose.xhtml ;
	class c_trans {
	public:
		c_trans (void); c_trans (const c_trans&) = delete; c_trans (c_trans&&) = delete; ~c_trans (void) = default;

	static c_mat2x2 Get (const c_mat2x2&); // gets the transpose of the input matrix;
	static c_mat3x3 Get (const c_mat3x3&); // gets the transpose of the input matrix;
	static c_mat4x4 Get (const c_mat4x4&); // gets the transpose of the input matrix;

	private:
		c_trans& operator = (const c_trans&) = delete; c_trans& operator = (c_trans&&) = delete;
	};
}}}}

#endif/*__MATH_MAT_INVERT_H_INCLUDED*/