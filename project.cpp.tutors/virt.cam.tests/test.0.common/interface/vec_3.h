#ifndef _VEC_3_H_INCLUDED
#define _VEC_3_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Aug-2026 at 23:40:58.325, UTC+4, Batumi, Wednesday;
	This is virtual camera test cases' 3D vertex interface declaration file;
*/
#include <cmath>

namespace test { namespace draw { namespace data {

	struct s_vec_3 {
		float x = 0.0f, y = 0.0f, z= 0.0f; // it is strictly forbidden in C, but fully supported in C++ (since C++11);

		s_vec_3 (const float _x = 0.0f, const float _y = 0.0f, const float _z = 0.0f);
		s_vec_3 (const s_vec_3&);
		s_vec_3 (s_vec_3&&) = default; ~s_vec_3 (void) = default;

		float dot (const s_vec_3&) const;
		bool  normalize (void);           // returns 'true' in case if normalization is completed, otherwise 'false';

		s_vec_3& operator = (const s_vec_3&);

		s_vec_3  operator + (const s_vec_3&) const;
		s_vec_3  operator - (const s_vec_3&) const;
		s_vec_3  operator * (const s_vec_3&) const;
	};

}}}

#endif/*_VEC_3_H_INCLUDED*/