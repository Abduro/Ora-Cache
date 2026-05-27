#ifndef _TEST_ADAP_$P$_EXTS_H_INCLUDED
#define _TEST_ADAP_$P$_EXTS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-May-2026 at 23:38:48.777, UTC+4, Batumi, Tuesday;
	This is OpenGL version 1.1 extensions' loading procedures wrapper unit test adapter interface declaration file.
*/
#include "test_case_$p$.exts.h"

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

#endif/*_TEST_ADAP_$P$_EXTS_H_INCLUDED*/