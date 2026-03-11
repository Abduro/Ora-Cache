#ifndef _TEST_CASE_$M$_MAT2x2_H_INCLUDED
#define _TEST_CASE_$M$_MAT2x2_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Mar-2026 at 15:03:34.118, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL math lib matrix 2x2 uint test interface declaration file for using in test cases' adapters;
*/
#include "ebo_test_$m$.defs.h"
#include "math.mat.2x2.h"
#include "math.mat.rotate.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {

	using t_mat2x2 = ex_ui::draw::open_gl::math::c_mat2x2;

	class c_mtx_2x2 {
	public:
		 c_mtx_2x2 (void) = default;
		~c_mtx_2x2 (void) = default;

		static
		_pc_sz To_str (const t_mat2x2&, const bool _b_cls); // if 'b_cls' is set to 'true', this class name is added to the log record;
	};

	using t_rot2x2 = ex_ui::draw::open_gl::math::c_rotate_2x2;

	class c_rot_2x2 {
	public:
		 c_rot_2x2 (void) = default;
		~c_rot_2x2 (void) = default;

		t_rot2x2& Prepare (const float _f_angle, const bool _b_cls = true); // returns the matrix prepared for rotation; _b_cls is for class name output;
		t_mat2x2& Rotate  (const float _f_angle, t_mat2x2& _mat_to_rot);    // returns rotated input matrix;
		/* steps:
		(1) prepare the rotation matrix for rotate angle;
		(2) multiplies the prepared matrix by input vector;
		    result: the vector of changed vslues; that means the vector2 (the point of x&y) is rotated around origin of axes (0;0);
		*/
		vec_2& Rotate (const float _f_angle, vec_2& _to_rot, const bool _b_use_eps); // returns vertex pos rotated in 2D space; using epsilon is for better result readability, not accuracy;
		vec_2& Rotate (const float _f_angle, const vec_2& _v_pivot, vec_2& _to_rot, const bool _b_use_eps); // rotates the input vector around pivot point;

		const
		t_rot2x2& operator ()(void) const;
		t_rot2x2& operator ()(void);

	private:
		t_rot2x2 m_rot2x2;
	};
}}}}}

#endif/*_TEST_CASE_$M$_MAT2x2_H_INCLUDED*/