#ifndef _EBO_TEST_$M$_VECTOR_H_INCLUDED
#define _EBO_TEST_$M$_VECTOR_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Dec-2025 at 16:33:25.764, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL math lib vector uint test interface declaration file; 
*/
#include "test_case_$m$.vec3.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {

	__class (c_vec3) {
	public:
		c_vec3 (void); ~c_vec3 (void) = default;

		__method (Length);
		__method (Normalize);
	};
	/*
		Unfortunately there is no possibility to create test method with input arguments,
		it can be solved by using Google test units, or through outside storage of required input arguments without hardcode and re-compiling the test project,
		for example the usage of the system registry or ini-file;
	*/
	__class (c_vec4) {
	public:
		 c_vec4 (const bool _b_verb = true);
		 c_vec4 (const float _x, const float _y, const float _z, const float _w, const bool _b_verb = true);
		~c_vec4 (void) = default;

		__ctor (_ctor);
		__method (Set);     // sets some data to the vector after its creation, that means does not using this class constructor;

		const
		vec_4&  ref (void) const;
		vec_4&  ref (void) ;
		CString To_str (_pc_sz _p_pfx = predefs::_p_pfx, _pc_sz _p_sep = _T("; "), _pc_sz _p_sfx = predefs::_p_sfx) const;
		const
		vec_4&  operator ()(void) const;
		vec_4&  operator ()(void);
		

	private:
		bool  m_b_verb;
		vec_4 m_vec_4;
	};

}}}}}

#endif/*_EBO_TEST_$M$_VECTOR_H_INCLUDED*/