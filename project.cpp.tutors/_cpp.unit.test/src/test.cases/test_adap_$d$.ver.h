#ifndef _TEST_ADAP_$D$_VER_H_INCLUDED
#define _TEST_ADAP_$D$_VER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-May-2026 at 11:55:00.692, UTC+4, Batumi, Sunday;
	This is OpenGL tutorials' version info uint test adapter interface declaration file;
*/
#include "test_case_$d$.ver.h"

namespace test { namespace open_gl {

	__class (c_version) {
	public:
		 c_version (void) = default; c_version (const c_version&) = delete; c_version (c_version&&) = delete;
		~c_version (void) = default;

		__method (Load);  // just shows what OpenGL version is available on this OS;

	private:
		c_version& operator = (const c_version&) = delete; c_version& operator = (c_version&&) = delete;
	};
}}

#endif/*_TEST_ADAP_$D$_VER_H_INCLUDED*/