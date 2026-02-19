#ifndef _TEST_CASE_$M$_MAT3x3_H_INCLUDED
#define _TEST_CASE_$M$_MAT3x3_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Feb-2026 at 15:10:08.201, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL math lib matrix 3x3 uint test interface declaration file for using in test cases' adapters;
*/
#include "ebo_test_$m$.defs.h"
#include "math.matrix.h"
#include "math.mat.rotate.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {

	using t_mat3x3 = ex_ui::draw::open_gl::math::c_mat3x3;
	using t_rot3x3 = ex_ui::draw::open_gl::math::c_rotate_3x3;

	class c_mtx_base {
	public:
		c_mtx_base (void); c_mtx_base (const c_mtx_base&) = delete; c_mtx_base (c_mtx_base&&) = delete; ~c_mtx_base (void) = default;

		TError& Error (void) const;

	protected:
		c_mtx_base& operator = (const c_mtx_base&) = delete; c_mtx_base& operator = (c_mtx_base&&) = delete;
		CError  m_error;
	};

	class c_mtx_3x3 : public c_mtx_base { typedef c_mtx_base TBase;
	public:
		c_mtx_3x3 (void); ~c_mtx_3x3 (void) = default;

		_pc_sz To_str (const t_mat3x3&, const bool _b_cls); // if 'b_cls' is set to 'true', this class name is added to the log record;
	};
}}}}}

#endif/*_TEST_CASE_$M$_MAT3x3_H_INCLUDED*/