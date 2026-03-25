#ifndef _EBO_TEST_$W$_CON_H_INCLUDED
#define _EBO_TEST_$W$_CON_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Mar-2026 at 21:03:48.074, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL tutorials' trace console unit test adapter interface declaration file; 
*/
#include "test_case_$w$.con.h"

namespace ebo { namespace boo { namespace test { namespace con {

	__class (c_locator) {
	public:
		 c_locator (void) = default; c_locator (const c_locator&) = delete; c_locator (c_locator&&) = delete;
		~c_locator (void) = default;

		__method (Path);  // gets path to trace console executable;

	private:
		c_locator& operator = (const c_locator&) = delete; c_locator& operator = (c_locator&&) = delete;
	};

	__class (c_wrap) {
	public:
		 c_wrap (void) = default; c_wrap (const c_wrap&) = delete; c_wrap (c_wrap&&) = delete;
		~c_wrap (void) = default;

		__method(Create);
		__method(Path);    // checks the getting a path of test case dyna-lib, i.e. this test case dyna-lib;

	private:
		c_wrap& operator = (const c_wrap&) = delete; c_wrap& operator = (c_wrap&&) = delete;
	};

}}}}

#endif/*_EBO_TEST_$W$_CON_H_INCLUDED*/