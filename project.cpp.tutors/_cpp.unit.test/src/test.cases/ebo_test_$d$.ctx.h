#ifndef _EBO_TEST_$D$_CTX_H_INCLUDED
#define _EBO_TEST_$D$_CTX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Jan-2026 at 00:55:23.370, UTC+4, Batumi, Wednesday;
	Ebo Pack OpenGL draw context of regular device and of renderer uint test interface declaration file;
*/
#include "test_case_$d$.ctx.h"

namespace test { namespace draw { namespace open_gl {
	using namespace ebo::boo::test;

	__class (c_ctx) {
	public:
		  c_ctx (const bool _b_verb = true);
		 ~c_ctx (void);

		 __clean (OnClean);   // is called after destroying this class instance;
		 __init (OnInit);     // is called before creating this class instance;

		 __ctor (_ctor);      // just for testing the test case when this class in new and has no method yet, otherwise not required;
		 __method (Device);   // creates the regular device context compatible with open_gl rendering;

		 __method (Graphics); // creates the open_gl graphics context;

	private:
		bool m_b_verb;
	};

	__class (c_px_format) {
	public:
		 c_px_format (void) = default; c_px_format (const c_px_format&) = delete; c_px_format (c_px_format&&) = delete;
		~c_px_format (void) = default;

		__method (Find_ndx); // finds the pixel format descriptor that matches input arguments;

	private:
		c_px_format& operator = (const c_px_format&) = delete; c_px_format& operator = (c_px_format&&) = delete;
	};

}}}

#endif/*_EBO_TEST_$D$_CTX_H_INCLUDED*/