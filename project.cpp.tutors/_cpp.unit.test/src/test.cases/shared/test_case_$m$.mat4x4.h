#ifndef _TEST_CASE_$M$_MAT4x4_H_INCLUDED
#define _TEST_CASE_$M$_MAT4x4_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Feb-2026 at 14:00:50.123, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL math lib matrix 4x4 uint test interface declaration file for using in test cases' adapters;
*/
#include "test_case_$m$.rot.args.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {

	/* matrix structure:
	   the first 3x3 elements (indices 0-2, 4-6, 8-10) represent rotation and scaling:
	   row #0: [0, 4, 8] is the pitch vector (x,y,z);
	   row #1: [1, 5, 9] is the yaw vector (x,y,z); (heading);
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
		 c_rot_4x4 (void) = default; c_rot_4x4 (const c_rot_4x4&) = delete; c_rot_4x4 (c_rot_4x4&&) = delete;
		~c_rot_4x4 (void) = default;

		vec_4& Do (const s_rot_cri_v4&, vec_4& _to_rot); // rotates the given vector around particular axis specified in input args;

		t_rot4x4& Prepare (const s_rot_cri_t&); // returns the matrix prepared for rotation; _b_cls is for class name output;

		const
		t_rot4x4& operator ()(void) const;
		t_rot4x4& operator ()(void);

	private:
		c_rot_4x4& operator = (const c_rot_4x4&) = delete; c_rot_4x4& operator = (c_rot_4x4&&) = delete;
		t_rot4x4 m_rot4x4;
	};

}}}}}

#endif/*_TEST_CASE_$M$_MAT4x4_H_INCLUDED*/