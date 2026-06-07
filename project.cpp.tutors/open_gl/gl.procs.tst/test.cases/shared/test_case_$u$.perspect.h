#ifndef _TEST_CASE_$U$_PERSPECT_H_INCLUDED
#define _TEST_CASE_$U$_PERSPECT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmai.com) on 05-Jun-2026 at 12:47:38.767, UTC+4, Batumi, Friday;
	This is OpenGL v_1_1 GLU related procedures' wrapper interface declaration file for using in test cases' adapters;
*/
#include "test_adap_$p$.defs.h"
#include "utils\gl_procs_perspect.h"
#include "gl_procs_matrix.h"

namespace test { namespace open_gl { namespace utils { namespace ver_1_1 {

	using namespace ::open_gl::procs::ver_1_1;
	using namespace ::open_gl::procs::utils::ver_1_1;

	// this is the test case of wrapper of gluPerspective procedure from GLU library; it is replaced by GLM library;
	class CTstPerspect {
	public:
		CTstPerspect (const bool _b_verbose); CTstPerspect (const CTstPerspect&) = delete; CTstPerspect (CTstPerspect&&) = delete; ~CTstPerspect (void) = default;

		err_code Get (void);
		err_code Set (const s_pers_args&);

		const
		CPerspect& operator ()(void) const;
		CPerspect& operator ()(void) ;

	private:
		CTstPerspect& operator = (const CTstPerspect&) = delete; CTstPerspect& operator = (CTstPerspect&&) = delete;
		CPerspect m_perspect;
		bool      m_verbose;
	};

}}}}

#endif/*_TEST_CASE_$U$_PERSPECT_H_INCLUDED*/