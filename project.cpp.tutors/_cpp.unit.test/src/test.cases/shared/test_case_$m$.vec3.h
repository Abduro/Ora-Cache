#ifndef _TEST_CASE_$M$_VEC3_H_INCLUDED
#define _TEST_CASE_$M$_VEC3_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Feb-2026 at 22:36:41.820, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL math lib vector of 3 elements uint test interface declaration file for using in test cases' adapters; 
*/
#include "ebo_test_$m$.defs.h"
#include "math.vector.h"
namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {

	class c_tvec_3x3 {
	public:
		c_tvec_3x3 (void); c_tvec_3x3 (const c_tvec_3x3&) = delete; c_tvec_3x3 (c_tvec_3x3&&) = delete; ~c_tvec_3x3 (void) = default;
		c_tvec_3x3 (const float _x, const float _y, const float _z);

		float   Length (const bool _b_log = true) const;
		vec_3&  Normalize (const bool _b_fast, const bool _b_log = true); // normalizes the vector by using two methods: 'fast' and 'regular';

		const
		vec_3&  ref (void) const;
		vec_3&  ref (void);

		const
		vec_3&  operator ()(void) const;
		vec_3&  operator ()(void);

	private:
		c_tvec_3x3& operator = (const c_tvec_3x3&) = delete; c_tvec_3x3& operator = (c_tvec_3x3&&) = delete;
		vec_3 m_vec_3; // vector object being tested;
	};

}}}}}

#endif/*_TEST_CASE_$M$_VEC3_H_INCLUDED*/