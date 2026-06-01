#ifndef _TEST_CASE_$P$_VIEWPORT_H_INCLUDED
#define _TEST_CASE_$P$_VIEWPORT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 31-May-2026 at 10:00:36.918, UTC+4, Batumi, Sunday;
	This is OpenGL viewport related procedures' wrapper interface declaration file for using in test cases adapters;
*/
#include "test_adap_$p$.defs.h"
#include "gl_procs_viewport.h"

namespace test { namespace open_gl { namespace procs {

	using CViewport = ::open_gl::procs::CViewport;
	using i_set_4   = ::open_gl::procs::i_set_4;
	using i_values  = ::open_gl::procs::viewport::i_values;
	using CParams   = ::open_gl::procs::viewport::CParams;

	class CTstViewport {
	public:
		 CTstViewport (const bool _b_verbose); CTstViewport (const CTstViewport&) = delete; CTstViewport (CTstViewport&&) = delete;
		~CTstViewport (void) = default;

		err_code   Get_Params (void);
		err_code   Is_valid   (void);
		err_code   Set_Params (const i_set_4&);

		bool Verbose (void) const;
		void Verbose (const bool);

		const
		CViewport& operator ()(void) const;
		CViewport& operator ()(void);

	private:
		CTstViewport& operator = (const CTstViewport&) = delete; CTstViewport& operator = (CTstViewport&&) = delete;
		CViewport m_viewport;
		bool      m_verbose;
	};
}
}}

#endif/*_TEST_CASE_$P$_VIEWPORT_H_INCLUDED*/