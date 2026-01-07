#ifndef _EBO_TEST_$D$_CTX_H_INCLUDED
#define _EBO_TEST_$D$_CTX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Jan-2026 at 00:55:23.370, UTC+4, Batumi, Wednesday;
	Ebo Pack OpenGL draw context of regular device and of renderer uint test interface declaration file;
*/
#include "_log.h"
#include "gl_context.h"
#include "gl_renderer.h"
#include "shared.wnd.fake.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {
	using namespace ebo::boo::test;

	using CFakeWnd = ex_ui::popup::CMsgWnd;
	using CContext = ex_ui::draw::open_gl::CContext;
	using CDevice  = ex_ui::draw::open_gl::context::CDevice;

	__class (c_ctx) {
	public:
		  c_ctx (const bool _b_verb = true);
		 ~c_ctx (void);

		 __ctor (_ctor);
		 __method (Device);  // creates the regular device context compatible with open_gl rendering;

		 const
		 CFakeWnd& Fake_wnd (void) const;
		 CFakeWnd& Fake_wnd (void) ;

	private:
		bool      m_b_verb;
		CFakeWnd  m_fk_wnd;
	};

}}}}}

#endif/*_EBO_TEST_$D$_CTX_H_INCLUDED*/