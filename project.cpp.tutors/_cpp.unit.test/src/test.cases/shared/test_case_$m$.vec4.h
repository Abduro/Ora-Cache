#ifndef _TEST_CASE_$M$_VEC4_H_INCLUDED
#define _TEST_CASE_$M$_VEC4_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Feb-2026 at 17:10:10.750, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL math lib vector of 4 elements uint test interface declaration file for using in test cases' adapters; 
*/
#include "ebo_test_$m$.defs.h"
#include "math.vector.h"
namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {

	class c_tvec_4 {
	public:
		c_tvec_4 (void); c_tvec_4 (const c_tvec_4&) = delete; c_tvec_4 (c_tvec_4&&) = delete; ~c_tvec_4 (void) = default;
		c_tvec_4 (const float _x, const float _y, const float _z, const float _w);

		float   Length (const bool _b_log = true) const;
		vec_4&  Negate (const bool _b_log = true);
		vec_4&  Normalize (const bool _b_fast, const bool _b_log = true); // normalizes the vector by using two methods: 'fast' and 'regular';

		const
		vec_4&  ref (void) const;
		vec_4&  ref (void);

		const
		vec_4&  operator ()(void) const;
		vec_4&  operator ()(void);

	private:
		c_tvec_4& operator = (const c_tvec_4&) = delete; c_tvec_4& operator = (c_tvec_4&&) = delete;
		vec_4 m_vec_4; // vector object being tested;
	};

}}}}}

#endif/*_TEST_CASE_$M$_VEC4_H_INCLUDED*/