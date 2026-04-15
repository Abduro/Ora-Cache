#ifndef _TEST_ADAP_$W$_CON_PERS_H_INCLUDED
#define _TEST_ADAP_$W$_CON_PERS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Apr-2026 at 20:27:37.278, UTC+4, Batumi, Wednesday;
	This is Ebo Pack console persistency unit test adapter interface declaration file.
*/
#include "test_case_$w$.con.pers.h"

namespace test { namespace win_api { namespace console {

	__class (c_pers) {
	public:
		 c_pers (void) = default; c_pers (const c_pers&) = delete; c_pers (c_pers&&) = delete;
		~c_pers (void) = default;

		__method (Load);
		__method (Save);

	private:
		c_pers& operator = (const c_pers&) = delete; c_pers& operator = (c_pers&&) = delete;
	};

}}}

#endif/*_TEST_ADAP_$W$_CON_PERS_H_INCLUDED*/