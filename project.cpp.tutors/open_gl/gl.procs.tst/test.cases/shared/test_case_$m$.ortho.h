#ifndef _TEST_CASE_$M$_ORTHO_H_INCLUDED
#define _TEST_CASE_$M$_ORTHO_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 08-Jun-2026 at 13:20:18.587, UTC+4, Batumi, Monday;
	This is OpenGL orthographic projection matrix wrapper interface declaration file for using in test cases' adapters;
*/
#include "test_adap_$p$.defs.h"
#include "gl_procs_ortho.h"

namespace test { namespace open_gl { namespace ortho {

	using namespace ::test::open_gl;
	using namespace ::open_gl::procs;
	using namespace ::open_gl::procs::projection::ver_1_1;

	class CTstOrtho {
	public:
		CTstOrtho (const bool _b_verbose = true); CTstOrtho (const CTstOrtho&) = delete; CTstOrtho (CTstOrtho&&) = delete; ~CTstOrtho (void) = default;

		err_code  Set (const t_rect& _clip, const f_planes&);

		const
		COrtho& operator ()(void) const;
		COrtho& operator ()(void) ;

		CTstOrtho& operator <<(const bool _b_verbose);

	private:
		CTstOrtho& operator = (const CTstOrtho&) = delete; CTstOrtho& operator = (CTstOrtho&&) = delete;
		COrtho m_ortho;
		bool   m_verbose;
	};

}}}

#endif/*_TEST_CASE_$M$_ORTHO_H_INCLUDED*/