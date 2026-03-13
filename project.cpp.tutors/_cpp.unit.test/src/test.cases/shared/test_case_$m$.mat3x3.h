#ifndef _TEST_CASE_$M$_MAT3x3_H_INCLUDED
#define _TEST_CASE_$M$_MAT3x3_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Feb-2026 at 15:10:08.201, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL math lib matrix 3x3 uint test interface declaration file for using in test cases' adapters;
*/
#include "ebo_test_$m$.defs.h"
#include "math.mat.3x3.h"
#include "math.rot.3x3.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {

	using t_mat3x3 = ex_ui::draw::open_gl::math::c_mat3x3;
	using t_rot3x3 = ex_ui::draw::open_gl::math::c_rotate_3x3;

	class c_mtx_3x3 {
	public:
		 c_mtx_3x3 (void) = default; c_mtx_3x3 (const c_mtx_3x3&) = delete; c_mtx_3x3 (c_mtx_3x3&&) = delete;
		~c_mtx_3x3 (void) = default;
		static
		_pc_sz To_str (const t_mat3x3&, const bool _b_cls); // if 'b_cls' is set to 'true', this class name is added to the log record;

	private:
		c_mtx_3x3& operator = (const c_mtx_3x3&) = delete; c_mtx_3x3& operator = (c_mtx_3x3&&) = delete;
	};

	class c_rot_3x3 {
	public:
		 c_rot_3x3 (void) = default; c_rot_3x3 (const c_rot_3x3&) = delete; c_rot_3x3 (c_rot_3x3&&) = delete;
		~c_rot_3x3 (void) = default;

		t_rot3x3& Prepare (const float _f_angle, const bool _b_cls = true); // returns the matrix prepared for rotation; _b_cls is for class name output;

		const
		t_rot3x3& operator ()(void) const;
		t_rot3x3& operator ()(void);

	private:
		c_rot_3x3& operator = (const c_rot_3x3&) = delete; c_rot_3x3& operator = (c_rot_3x3&&) = delete;
		t_rot3x3 m_rot3x3;
	};
}}}}}

#endif/*_TEST_CASE_$M$_MAT3x3_H_INCLUDED*/