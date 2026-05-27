#ifndef _TEST_CASE_$D$_CTX_ARB_H_INCLUDED
#define _TEST_CASE_$D$_CTX_ARB_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-May-2026 at 09:31:01.487, UTC+4, Batumi, Monday;
	This is OpenGL WinAPI graphics device context wrapper interface declaration file for using in test adapters;
*/
#include "test_case_$d$.ctx.h"

namespace test { namespace open_gl { namespace context { namespace arb { using namespace ebo::boo::test;

	using CGraphics = ::open_gl::context::arb::CGraphics; // taking into account the remderer of pipeline is used, the ARB support is required;

	class CTstGraph {
	public:
		CTstGraph (void) = default;
		CTstGraph (const CTstGraph&) = delete; CTstGraph (CTstGraph&&) = delete; ~CTstGraph (void) = default;

		err_code  Create (const bool _b_verbose = true);
		err_code  Delete (const bool _b_verbose = true);

		err_code  MakeCurrent (const bool _yes_or_no);
		err_code  Swap (void); // replaces graphics context by the target window device context, i.e. makes draw on the screen;

		const
		CGraphics&  operator ()(void) const;
		CGraphics&  operator ()(void) ;

	private:
		CTstGraph& operator = (const CTstGraph&) = delete; CTstGraph& operator = (CTstGraph&&) = delete;
		CTstDevice m_tst_dev;
		CGraphics  m_graph;
	};
}}}}

#endif/*_TEST_CASE_$D$_CTX_ARB_H_INCLUDED*/