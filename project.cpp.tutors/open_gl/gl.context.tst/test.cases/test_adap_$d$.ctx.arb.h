#ifndef _TEST_ADAP_$D$_CTX_ARB_H_INCLUDED
#define _TEST_ADAP_$D$_CTX_ARB_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-May-2026 at 09:37:41.495, UTC+4, Batumi, Monday;
	This is OpenGL draw rendering/graphics context wrapper uint test adapter interface declaration file;
*/
#include "test_case_$d$.ctx.arb.h"

namespace test { namespace open_gl { namespace context { namespace arb {
	using namespace ebo::boo::test;

	__class (c_ctx) {
	public:
		  c_ctx (void) = default; c_ctx (const c_ctx&) = delete; c_ctx (c_ctx&&) = delete;
		 ~c_ctx (void) = default;

		 __method (Graphics); // creates the open_gl graphics context of arb namespace;

	private:
		bool m_b_verb;
	};

}}}}

#endif/*_TEST_ADAP_$D$_CTX_ARB_H_INCLUDED*/