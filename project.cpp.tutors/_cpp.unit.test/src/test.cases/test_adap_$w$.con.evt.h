#ifndef _TEST_ADAP_$W$_CON_EVT_H_INCLUDED
#define _TEST_ADAP_$W$_CON_EVT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Mar-2026 at 09:31:04.061, UTC+4, Batumi, Monday;
	This is Ebo Pack trace console event unit test adapter interface declaration file; 
*/
#include "test_case_$w$.con.evt.h"

namespace test { namespace win_api { namespace console {
namespace events {
	__class (c_ctrl_router) {
	public:
		 c_ctrl_router (void) = default; c_ctrl_router (const c_ctrl_router&) = delete; c_ctrl_router (c_ctrl_router&&) = delete;
		~c_ctrl_router (void) = default;

		__method (Turn_off);
		__method (Turn_on);

	private:
		c_ctrl_router& operator = (const c_ctrl_router&) = delete; c_ctrl_router& operator = (c_ctrl_router&&) = delete;
	};

	__class (c_input_router) {
	public:
		 c_input_router (void) = default; c_input_router (const c_input_router&) = delete; c_input_router (c_input_router&&) = delete;
		~c_input_router (void) = default;

		__method (Turn_off);
		__method (Turn_on);

	private:
		c_input_router& operator = (const c_input_router&) = delete; c_input_router& operator = (c_input_router&&) = delete;
	};
}
}}}

#endif/*_TEST_ADAP_$W$_CON_EVT_H_INCLUDED*/