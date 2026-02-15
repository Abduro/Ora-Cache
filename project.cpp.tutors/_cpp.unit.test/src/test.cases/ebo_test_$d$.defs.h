#ifndef _EBO_TEST_$D$_DEFS_H_INCLUDED
#define _EBO_TEST_$D$_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Jan-2026 at 23:38:48.842, UTC+4, Batumi, Tauesday;
	Ebo Pack OpenGL draw context lib common definitions' uint test interface declaration file;
*/
#include "_log.h"
#include "gl_renderer.h"
#include "shared.dbg.h"
#include "shared.preproc.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {
	using namespace ebo::boo::test;

	/**important*: the main rules of error trace:
	(1) if a test case object throws the error, it should trace it itself;
	(2) if an error occurs outside the object, it must be tracked by that object, otherwise the error trace may be duplicated;
	*/

}}}}}

#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);
#pragma comment(lib, "gl.procs_v15.lib")     // open_gl procs loader lib;
#pragma comment(lib, "gl.shared_v15.lib")    // open_gl wrapper shared lib;

#endif/*_EBO_TEST_$D$_DEFS_H_INCLUDED*/