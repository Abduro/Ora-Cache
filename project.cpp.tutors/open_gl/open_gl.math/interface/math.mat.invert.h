#ifndef __MATH_MAT_INVERT_H_INCLUDED
#define __MATH_MAT_INVERT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Dec-2025 at 13:15:31.324, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' generic data matrix inverter interface declaration file;
*/
#include "math.matrix.h"

namespace ex_ui { namespace draw { namespace open_gl { namespace math {

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
	public: c_det (void) = default; c_det (const c_det&) = delete;

	static float Get (const c_mat2x2&);
	static float Get (const c_mat3x3&);
	static float Get (const c_mat4x4&);

	static bool  Is  (const float f_value); // makes a comparison of input determinant value with epsilon value;

	private: c_det& operator = (const c_det&) = delete; c_det& operator = (c_det&&) = delete;
	};

	// https://registry.khronos.org/OpenGL-Refpages/gl4/html/inverse.xhtml ;
	class c_inverter_4x4 : public c_mat4x4 {
	public:
		c_inverter_4x4 (void); c_inverter_4x4 (const c_inverter_4x4&) = delete; c_inverter_4x4 (c_inverter_4x4&&) = delete; ~c_inverter_4x4 (void) = default;

		c_mat4x4& Affine (void); // returns the inverse of affine transform matrix;

		const
		c_mat4x4& operator ()(void) const; // returns the reference to the parent class object; (ro)
		c_mat4x4& operator ()(void) ;      // returns the reference to the parent class object; (rw)

	private:
		c_inverter_4x4& operator = (const c_inverter_4x4&) = delete; c_inverter_4x4& operator = (c_inverter_4x4&&) = delete;
	};


}}}}

#endif/*__MATH_MAT_INVERT_H_INCLUDED*/