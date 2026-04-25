#ifndef _TEST_ADAP_$W$_CON_MODE_H_INCLUDED
#define _TEST_ADAP_$W$_CON_MODE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Mar-2026 at 09:30:24.208, UTC+4, Batumi, Monday;
	This is Ebo Pack trace console mode unit test adapter interface declaration file; 
*/
#include "test_case_$w$.con.mode.h"

namespace test { namespace win_api { namespace console {
namespace modes {
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
}
}}}

#endif/*_TEST_ADAP_$W$_CON_MODE_H_INCLUDED*/