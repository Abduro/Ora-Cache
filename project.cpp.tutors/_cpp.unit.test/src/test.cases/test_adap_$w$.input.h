#ifndef _TEST_ADAP_$W$_INPUT_INCLUDED
#define _TEST_ADAP_$W$_INPUT_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Jul-2026 at 13:44:04.340, UTC+4, Batumi, Thursday;
	This is Ebo Pack generic input wrappers' unit test adapter interface declaration file; 
*/
#include "test_case_$w$.cmd.ln.h"

namespace test { namespace win_api { namespace input {

	/*testhost does not provide an ability to get command line arguments;*/
	__class (c_cmd_cln) {
	public:
		c_cmd_cln (void) = default; c_cmd_cln (const c_cmd_cln&) = delete; c_cmd_cln (c_cmd_cln&&) = delete; ~c_cmd_cln (void) = default;

		__method (Parse);

	private:
		c_cmd_cln& operator = (const c_cmd_cln&) = delete; c_cmd_cln& operator = (c_cmd_cln&&) = delete;
	};

}}}

#endif/*_TEST_ADAP_$W$_INPUT_INCLUDED*/