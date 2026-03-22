#ifndef _EBO_TEST_$W$_CON_H_INCLUDED
#define _EBO_TEST_$W$_CON_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Mar-2026 at 21:03:48.074, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL tutorials' trace console unit test adapter interface declaration file; 
*/
#include "test_case_$w$.con.h"

namespace ebo { namespace boo { namespace test { namespace console {

	__class (c_input) {
	public:
		 c_input (void) = default; c_input (const c_input&) = delete; c_input (c_input&&) = delete;
		~c_input (void) = default;

		__method (Get);
		__method (Set);

	private:
		c_input& operator = (const c_input&) = delete; c_input& operator = (c_input&&) = delete;
	};

	__class (c_output) {
	public:
		 c_output (void) = default; c_output (const c_output&) = delete; c_output (c_output&&) = delete;
		~c_output (void) = default;

		__method (Get);
		__method (Set);

	private:
		c_output& operator = (const c_output&) = delete; c_output& operator = (c_output&&) = delete;
	};

}}}}

#endif/*_EBO_TEST_$W$_CON_H_INCLUDED*/