#ifndef _EBO_TEST_$D$_DEFS_H_INCLUDED
#define _EBO_TEST_$D$_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Jan-2026 at 23:38:48.842, UTC+4, Batumi, Tauesday;
	Ebo Pack OpenGL draw context lib common definitions' uint test interface declaration file;
*/
#include "_log.h"
#include "gl_renderer.h" // to-do: this include must be made in places where test cases are related to renderer, but not here;
#include "gl_version.h"
#include "shared.dbg.h"
#include "shared.preproc.h"

namespace test { namespace draw { namespace open_gl {

	using namespace ebo::boo::test;

	/**important*: the main rules of error trace:
	(1) if a test case object throws the error, it should trace it itself;
	(2) if an error occurs outside the object, it must be tracked by that object, otherwise the error trace may be duplicated;
	*/
	using CVersion = ex_ui::draw::open_gl::CVersion;

	class CTstVersion {
	public:
		 CTstVersion (void) = default; CTstVersion (const CTstVersion&) = delete; CTstVersion (CTstVersion&&) = delete;
		~CTstVersion (void) = default;
		// version info class loads data automatically in its constructor, but this function is just for print out of the version or an error that may occur;
		err_code Load (const bool _cls_out = true);

		const
		CVersion& operator ()(void) const;
		CVersion& operator ()(void) ;

	private:
		CTstVersion& operator = (const CTstVersion&) = delete; CTstVersion& operator = (CTstVersion&&) = delete;
		CVersion m_ver;
	};

}}}

#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);
#pragma comment(lib, "gl.procs_v15.lib")     // open_gl procs loader lib;
#pragma comment(lib, "gl.shared_v15.lib")    // open_gl wrapper shared lib;

#endif/*_EBO_TEST_$D$_DEFS_H_INCLUDED*/