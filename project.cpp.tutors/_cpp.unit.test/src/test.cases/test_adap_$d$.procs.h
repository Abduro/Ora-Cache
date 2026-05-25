#ifndef _TEST_ADAP_$D$_PROCS_H_INCLUDED
#define _TEST_ADAP_$D$_PROCS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-Apr-2026 at 08:23:47.671, UTC+4, Batumi, Monday;
	This is OpenGL API procedure loader wrapper unit test adapter interface declaration file.
*/
#include "test_case_$d$.procs.h"

namespace test { namespace open_gl { namespace procs {

	__class (c_proc_ext) {
	public:
		 c_proc_ext (void) = default; c_proc_ext (const c_proc_ext&) = delete; c_proc_ext (c_proc_ext&&) = delete;
		~c_proc_ext (void) = default;

		__method (Is_arb);
		__method (Is_remote);
		__method (Load);

	private:
		c_proc_ext& operator = (const c_proc_ext&) = delete; c_proc_ext& operator = (c_proc_ext&&) = delete;
	};

}}}

#endif/*_TEST_ADAP_$D$_PROCS_H_INCLUDED*/