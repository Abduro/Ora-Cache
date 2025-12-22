#ifndef _EBO_TEST_$M$_VECTOR_H_INCLUDED
#define _EBO_TEST_$M$_VECTOR_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Dec-2025 at 16:33:25.764, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL math lib vector uint test interface declaration file; 
*/
#include "ebo_test_$m$.defs.h"
#include "math.vector.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace math {

	__class (c_vec3) {
	public:
		 c_vec3 (const bool _b_verb = true);
		~c_vec3 (void) = default;

		__ctor (_ctor);
		__method (Set);     // sets some data to the vector after its creation, that means does not using this class constructor;

		const
		vec_3&  ref (void) const;
		vec_3&  ref (void) ;
		CString To_str (_pc_sz _p_pfx = predefs::_p_pfx, _pc_sz _p_sep = _T("; "), _pc_sz _p_sfx = predefs::_p_sfx) const;

	private:
		bool  m_b_verb;
		vec_3 m_vec_3;
	};

}}}}}

#endif/*_EBO_TEST_$M$_VECTOR_H_INCLUDED*/