#ifndef _TEST_CASE_$D$_CTX_H_INCLUDED
#define _TEST_CASE_$D$_CTX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Jan-2026 at 15:18:41.909, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL draw context wrapper interface declaration file for using in test cases adapters;
*/
#include "ebo_test_$d$.defs.h"
#include "gl_context.h"
#include "shared.wnd.fake.h"

namespace ebo { namespace boo { namespace test { namespace open_gl { namespace draw {

	using namespace ex_ui::draw::open_gl;

	using CFakeWnd  = ex_ui::popup::CMsgWnd;
	using CGraphics = ex_ui::draw::open_gl::CGraphics;
	using CDevice   = ex_ui::draw::open_gl::context::CDevice;

	class CDevCtx {
	public:
		CDevCtx (void);
		CDevCtx (const CDevCtx&) = delete; CDevCtx (CDevCtx&&) = delete; ~CDevCtx (void) = default;

		err_code Create (void);
		err_code Delete (void);
		TError&  Error  (void) const;
		const
		CFakeWnd& Window (void) const;
		CFakeWnd& Window (void) ;

	private:
		CDevCtx& operator = (const CDevCtx&) = delete; CDevCtx& operator = (CDevCtx&&) = delete;
		CError   m_error ;
		CFakeWnd m_fk_wnd;
	};

	class CGraphCtx {
	public:
		CGraphCtx (void) ;
		CGraphCtx (const CGraphCtx&) = delete; CGraphCtx (CGraphCtx&&) = delete; ~CGraphCtx (void) = default;

		err_code Create (const HWND _h_target); // for the test cases the fake window handle is used;
		err_code Delete (void);

		TError&  Error  (void) const;
	private:
		CGraphCtx& operator = (const CGraphCtx&) = delete; CGraphCtx& operator = (CGraphCtx&&) = delete;
		CError m_error;
	};

	/*
		this class creates the device and graphics contexts in its constructor and auto-deletes them in its destructor;
	*/
	class CCtx_auto {
	public:
		CCtx_auto (void); ~CCtx_auto (void);
		CCtx_auto (const CCtx_auto&) = delete; CCtx_auto (CCtx_auto&&) = delete;

		err_code Create (void);
		err_code Delete (void);

		const
		CDevCtx& Device (void) const;
		CDevCtx& Device (void) ;
		const
		CGraphCtx& Graph (void) const;
		CGraphCtx& Graph (void) ;

		TError&  Error  (void) const;
	private:
		CCtx_auto& operator = (const CCtx_auto&) = delete; CCtx_auto& operator = (CCtx_auto&&) = delete;
		CError    m_error;
		CDevCtx   m_device;
		CGraphCtx m_graphs;
	};

}}}}}

#endif/*_TEST_CASE_$D$_CTX_H_INCLUDED*/