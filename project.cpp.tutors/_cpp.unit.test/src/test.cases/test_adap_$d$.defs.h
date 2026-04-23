#ifndef _TEST_ADAP_$D$_DEFS_H_INCLUDED
#define _TEST_ADAP_$D$_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-Apr-2026 at 08:45:06.936, UTC+4, Batumi, Monday;
	This is OpenGL tutorials' draw functionality common definitions interface file.
*/
#include "_log.h"
#include "shared.dbg.h"
#include "shared.preproc.h"

namespace test { namespace draw { namespace open_gl {
	using namespace shared::defs;

	__class (c_version) {
	public:
		 c_version (void) = default; c_version (const c_version&) = delete; c_version (c_version&&) = delete;
		~c_version (void) = default;

		__method (Load);  // just shows what OpenGL version is available on this OS;

	private:
		c_version& operator = (const c_version&) = delete; c_version& operator = (c_version&&) = delete;
	};
}}}

#endif/*_TEST_ADAP_$D$_DEFS_H_INCLUDED*/