#ifndef _TEST_CASE_$M$_VEC3_H_INCLUDED
#define _TEST_CASE_$M$_VEC3_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Feb-2026 at 22:36:41.820, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL math lib vector of 3 elements uint test interface declaration file for using in test cases' adapters; 
*/
#include "ebo_test_$m$.defs.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {

	// (1) dot product: The lines are perpendicular (orthogonal) if and only if their dot product is zero.
	/* (2) cross product: The result vector is orthogonal to given two vectors: their cross product yields the normal vector;
	    it is essential for lighting calculations;
	*/
	class c_tvec_3 {
	public:
		c_tvec_3 (void); c_tvec_3 (const c_tvec_3&) = delete; c_tvec_3 (c_tvec_3&&) = delete; ~c_tvec_3 (void) = default;
		c_tvec_3 (const float _x, const float _y, const float _z);
		c_tvec_3 (const ::glm::vec3&);

		vec_3   Get_cross (const vec_3& _v_with); // gets cross product for given two input vectors;
		float   Get_dot (const vec_3&) const;     // gets dot product of two vectors: this one and the input one;

		float   Length (const bool _b_log = true) const;
		vec_3&  Negate (const bool _b_log = true);
		vec_3&  Normalize (const bool _b_bits, const bool _b_log = true); // normalizes the vector by using two methods: 'bits level' and '::std::sqrtf()';

		const
		vec_3&  ref (void) const;
		vec_3&  ref (void);

		const
		vec_3&  operator ()(void) const;
		vec_3&  operator ()(void);

		vec_3&  operator <<(const ::glm::vec3&);
		::glm::vec3& operator >> (::glm::vec3&) const;

	private:
		c_tvec_3& operator = (const c_tvec_3&) = delete; c_tvec_3& operator = (c_tvec_3&&) = delete;
		vec_3 m_vec_3; // vector object being tested;
	};

}}}}}

#endif/*_TEST_CASE_$M$_VEC3_H_INCLUDED*/