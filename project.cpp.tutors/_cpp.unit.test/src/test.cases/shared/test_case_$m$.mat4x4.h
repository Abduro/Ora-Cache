#ifndef _TEST_CASE_$M$_MAT4x4_H_INCLUDED
#define _TEST_CASE_$M$_MAT4x4_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Feb-2026 at 14:00:50.123, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL math lib matrix 4x4 uint test interface declaration file for using in test cases' adapters;
*/
#include "ebo_test_$m$.defs.h"
#include "math.mat.4x4.h"
#include "math.rot.4x4.h"
#include "math.mat.stack.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {

	using t_mat4x4 = ex_ui::draw::open_gl::math::c_mat4x4;
	using t_rot4x4 = ex_ui::draw::open_gl::math::c_rotate_4x4;

	// this class is an adapter for copying matrix data between glm::mat and math::c_mat4x4;
	class c_ada_4x4 {
	public:
		 c_ada_4x4 (void); c_ada_4x4 (t_mat4x4&); c_ada_4x4 (const c_ada_4x4&) = delete; c_ada_4x4 (c_ada_4x4&&) = delete;
		~c_ada_4x4 (void) = default;

		TError& Error (void) const;

		t_mat4x4& operator << (const ::glm::mat4x4&);
		::glm::mat4x4& operator >> (::glm::mat4x4&) const;

	private:
		c_ada_4x4& operator = (const c_ada_4x4&) = delete; c_ada_4x4& operator = (c_ada_4x4&&) = delete;
		t_mat4x4& m_mat_ref;
		mutable CError m_error;
	};

	/* matrix structure:
	   the first 3x3 elements (indices 0-2, 4-6, 8-10) represent rotation and scaling:
	   row #0: [0, 4, 8] is the pitch vector (x,y,z);
	   row #1: [1, 5, 9] is the yaw vector (x,y,x); (heading);
	   row #2: [2, 6, a] is the roll vector (x,y,z);
	   while the elements at indices 12, 13, and 14 represent the X, Y, and Z translation components, respectively.
	*/
	class c_mtx_4x4 {
	public:
		c_mtx_4x4 (void);
		c_mtx_4x4 (const ::glm::mat4x4&); ~c_mtx_4x4 (void) = default;

		static
		t_mat4x4 Generate (const float _f_min, const float _f_max); // generates matrix with random values in specified range;

		t_mat4x4& Identity  (void);   // checks the correctness of the matrix identity procedure;
		t_mat4x4& Translate (vec_3&); // translates input vertex position;
		t_mat4x4& Transpose (void);   // transforms the column-major matrix to the row-major matrix and vice versa;
		static
		_pc_sz To_str (const t_mat4x4&, const bool _b_cls); // returns just the string of input matrix content, no output to the logger yet;

		const
		t_mat4x4& operator ()(void) const;
		t_mat4x4& operator ()(void);

		t_mat4x4& operator << (const ::glm::mat4x4&);
		::glm::mat4x4& operator >> (::glm::mat4x4&) const;

	private:
		t_mat4x4 m_mat4x4;
	};

	class c_rot_4x4 {
	public:
		c_rot_4x4 (void); ~c_rot_4x4 (void) = default;
		c_rot_4x4 (const ::glm::mat4x4&);

		t_mat4x4& On_X (const float _f_angle); // rotates on set of different angles about x-axis; to-do: using error object is useless in this context;

		const
		t_rot4x4& operator ()(void) const;
		t_rot4x4& operator ()(void);

	private:
		t_rot4x4 m_rot4x4;
	};

}}}}}

#endif/*_TEST_CASE_$M$_MAT4x4_H_INCLUDED*/