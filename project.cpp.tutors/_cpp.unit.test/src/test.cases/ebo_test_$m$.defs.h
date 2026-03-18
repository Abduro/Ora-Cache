#ifndef _EBO_TEST_$M$_DEFS_H_INCLUDED
#define _EBO_TEST_$M$_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Dec-2025 at 09:05:40.726, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL math lib common definitions' uint test interface declaration file; 
*/
#include "_log.h"
#include "glm/glm.hpp"  // #define GLM_FORCE_CTOR_INIT is not required due to it creates identity matrix that is not the case, but glm::mat4x4 (0.0f);
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "math.defs.h"
#include "math.mat.3x3.h"
#include "math.rot.3x3.h"
#include "math.mat.4x4.h"
#include "math.rot.4x4.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {
	using namespace ebo::boo::test;
	using namespace ex_ui::draw::open_gl::math;
	using namespace shared::defs;
	/*
	...when a number with an infinite binary representation is stored in a float (which has a fixed, 32-bit size), it must be rounded to the nearest representable value...
	1.0f is shown as 0.99999994, which is the nearest representable float value that is not exactly 1;
	...how to manage this inexactness:
	use double for higher precision: the double data type uses 64 bits and provides about 15-18 significant decimal digits of precision, compared to float's 6-9 digits...
	*/
	using t_mat3x3 = ex_ui::draw::open_gl::math::c_mat3x3;
	using t_mat4x4 = ex_ui::draw::open_gl::math::c_mat4x4;
	using t_rot3x3 = ex_ui::draw::open_gl::math::c_rotate_3x3;
	using t_rot4x4 = ex_ui::draw::open_gl::math::c_rotate_4x4;

	// this class is an adapter for copying matrix data between glm::mat and math::c_mat4x4;
	class c_adapter {
	public:
		 c_adapter (void); c_adapter (const c_adapter&) = delete; c_adapter (c_adapter&&) = delete;
		~c_adapter (void) = default;

		TError& Error (void) const;

		t_mat3x3& operator << (const ::glm::mat3x3&);
		t_mat4x4& operator << (const ::glm::mat4x4&);

		::glm::mat3x3& operator >> (::glm::mat3x3&) const;
		::glm::mat4x4& operator >> (::glm::mat4x4&) const;

		c_adapter& operator << (const t_mat3x3&); // sets data to cached matrix3x3;
		c_adapter& operator << (const t_mat4x4&); // sets data to cached matrix4x4;

		const c_adapter& operator >> (t_mat3x3&) const; // gets data from cached matrix3x3;
		const c_adapter& operator >> (t_mat4x4&) const; // gets data from cached matrix4x4;

	private:
		c_adapter& operator = (const c_adapter&) = delete; c_adapter& operator = (c_adapter&&) = delete;
		mutable CError m_error;
	};

	class c_axes {
	public:
		 c_axes (void) = default; c_axes (const c_adapter&) = delete; c_axes (c_axes&&) = delete;
		~c_axes (void) = default;

		static ::glm::vec3 Get_axis (const axes_t::e_axes _e_axis);

	private:
		c_axes& operator = (const c_axes&) = delete; c_axes& operator = (c_axes&&) = delete;
	};

	class c_compare : public c_comparator { typedef c_comparator base_t;
	public:
		 c_compare (void) = default; c_compare (const c_compare&) = delete; c_compare (c_compare&&) = delete;
		~c_compare (void) = default;

		bool operator ()(const t_mat3x3& _lhs, const t_mat3x3& _rhs, const float _f_threshold = defs::f_epsilon);
		bool operator ()(const t_mat4x4& _lhs, const t_mat4x4& _rhs, const float _f_threshold = defs::f_epsilon);

		bool operator ()(const vec_3& _lhs, const vec_3& _rhs, const float _f_threshold = defs::f_epsilon);
		bool operator ()(const vec_4& _lhs, const vec_4& _rhs, const float _f_threshold = defs::f_epsilon);

	private:
		c_compare& operator = (const c_compare&) = delete; c_compare& operator = (c_compare&&) = delete;
	};

	class c_mtx_base {
	public:
		c_mtx_base (void); c_mtx_base (const c_mtx_base&) = delete; c_mtx_base (c_mtx_base&&) = delete; ~c_mtx_base (void) = default;

		TError& Error (void) const;

	protected:
		c_mtx_base& operator = (const c_mtx_base&) = delete; c_mtx_base& operator = (c_mtx_base&&) = delete;
		mutable CError m_error;
	};

	static _pc_sz pc_sz_fmt_args  = _T("Rotate args: angle = %.2f; around %s");
	static _pc_sz pc_sz_mat_equal = _T("[impt] result: matrices are equal;");
	static _pc_sz pc_sz_mat_diff  = _T("[error] result: matrices are *not* equal;");

}}}}}

#pragma comment(lib, "glm_v15.lib")      // OpenGL mathematics project;
#pragma comment(lib, "gl.procs_v15.lib") // OpenGL procs loader project;
#pragma comment(lib, "gl.math_v15.lib")  // this project is being tested by this unit test project;
#pragma comment(lib, "ebo_test_$$$.lib") // shared unit test library for common definition(s);
#pragma comment(lib, "ebo_test_$d$.shared.lib") // shared draw context test case library;

#endif/*_EBO_TEST_$M$_DEFS_H_INCLUDED*/