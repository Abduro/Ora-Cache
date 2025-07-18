#ifndef _EBO_TEST_$D$_THEME_H_INCLUDED
#define _EBO_TEST_$D$_THEME_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 28-Jun-2025 at 08:27:45.072, UTC+4, Batumi, Saturday;
	This is Ebo Pack custom color theme base interface unit test declaration file; 
*/
#include "ebo_test_$d$.theme.defs.h"

#include "color.rgb.h"

namespace ebo { namespace boo { namespace test { namespace theme {

	__class (CMarker) {
	public:
		 CMarker (const bool _b_verb = false);
		~CMarker (void) = default;

	public:
		__ctor (_ctor);
		__method (Get);

	private:
		bool    m_b_verb;
		TMarker m_marker;
	};

}}}}

#endif/*_EBO_TEST_$D$_THEME_H_INCLUDED*/