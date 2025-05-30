#ifndef _EBO_TEST_$D$_CLR_NAMED_H_INCLUDED
#define _EBO_TEST_$D$_CLR_NAMED_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-May-2025 at 00:22:12.428, UTC+4, Batumi, Friday;
	This is Ebo Pack shared draw named color unit test interface declaration file; 
*/
#include "ebo_test_$d$.clr.h"

namespace ebo { namespace boo { namespace test { namespace color { namespace named {

	__class(CNamed) {
	public:
		 CNamed (const bool _b_verb = false);
		~CNamed (void) = default;

	public:
		__ctor (_ctor);

	private:
		bool   m_b_verb;
	};

	__class(CNamed_X11) {
	public:
		 CNamed_X11 (const bool _b_verb = false);
		~CNamed_X11 (void) = default;

	public:
		__ctor (_ctor);

	private:
		bool   m_b_verb;
	};

}}}}}

#endif/*_EBO_TEST_$D$_CLR_NAMED_H_INCLUDED*/