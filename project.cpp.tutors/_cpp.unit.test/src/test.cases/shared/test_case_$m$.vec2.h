#ifndef _TEST_CASE_$M$_VEC2_H_INCLUDED
#define _TEST_CASE_$M$_VEC2_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Mar-2026 at 17:31:52.541, UTC+4, Batumi, Thursday;
	This is Ebo Pack OpenGL tutorials' math lib vector of 2 elements uint test interface declaration file for using in test cases' adapters; 
*/
#include "ebo_test_$m$.defs.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {

	class c_tvec_2 {
	public:
		 c_tvec_2 (void) = default; c_tvec_2 (const c_tvec_2&) = delete; c_tvec_2 (c_tvec_2&&) = delete;
		~c_tvec_2 (void) = default;

		float Get_angle (const vec_2&, const vec_2&, const bool _b_cls_out = true); // gets an angle between two given vectors;
		float Get_dot (const vec_2&, const vec_2&, const bool _b_cls_out = true); // gets value of dot product of two given vectors;

	private:
		c_tvec_2& operator = (const c_tvec_2&) = delete; c_tvec_2& operator = (c_tvec_2&&) = delete;
	};

}}}}}

#endif/*_TEST_CASE_$M$_VEC2_H_INCLUDED*/