#ifndef _TEST_CASE_$D$_CTX_H_INCLUDED
#define _TEST_CASE_$D$_CTX_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Jan-2026 at 15:18:41.909, UTC+4, Batumi, Sunday;
	This is Ebo Pack OpenGL draw context wrapper interface declaration file for using in test cases adapters;
*/
#include "test_adap_$d$.defs.h"
#include "gl_context.h"

namespace test { namespace open_gl { namespace context {

	using namespace ebo::boo::test;
	using CDevice   = ::open_gl::context::CDevice;
	using CFake_Ctx = ::open_gl::CFake_Ctx;
	using CGraphics = ::open_gl::context::ver_1_1::CGraphics;

	class CTstDevice {
	public:
		CTstDevice (void) = default;
		CTstDevice (const CTstDevice&) = delete; CTstDevice (CTstDevice&&) = delete; ~CTstDevice (void) = default;

		err_code Create (const bool _b_verbose = true);
		err_code Delete (const bool _b_verbose = true);

		const
		CFake_Ctx& operator ()(void) const;
		CFake_Ctx& operator ()(void) ;
		 
	private:
		CTstDevice& operator = (const CTstDevice&) = delete; CTstDevice& operator = (CTstDevice&&) = delete;
		CFake_Ctx m_fk_ctx;
	};

namespace ver_1_1 {

	class CTstGraph {
	public:
		CTstGraph (void) = default;
		CTstGraph (const CTstGraph&) = delete; CTstGraph (CTstGraph&&) = delete; ~CTstGraph (void) = default;

		err_code  Create (const bool _b_verbose = true);
		err_code  Delete (const bool _b_verbose = true);

		err_code  MakeCurrent (const bool _yes_or_no);
		err_code  Swap (void); // replaces graphics context by the target window device context, i.e. makes draw on the screen;

		const
		CGraphics& operator ()(void) const;
		CGraphics& operator ()(void) ;

	private:
		CTstGraph& operator = (const CTstGraph&) = delete; CTstGraph& operator = (CTstGraph&&) = delete;
		CTstDevice m_tst_dev;
		CGraphics  m_graph;
	};

	using CFake_Ctx = ::open_gl::CFake_Ctx;

	class CCtxToggle : private CFake_Ctx { typedef CFake_Ctx TBase;
	public:
		 CCtxToggle (void); CCtxToggle (const CCtxToggle&) = delete; CCtxToggle (CCtxToggle&&) = delete;
		~CCtxToggle (void);
		const
		CFake_Ctx& operator ()(void) const;
		CFake_Ctx& operator ()(void);

	private:
		 CCtxToggle& operator = (const CCtxToggle&) = delete; CCtxToggle& operator = (CCtxToggle&&) = delete;
		 CFake_Ctx m_fk_ctx;
	};
}
	using CPxFormat = ::win_api::CPxFormat;
	using SPxBits   = ::win_api::format::s_bits;

	class CTstFormat {
	public:
		 CTstFormat (void) = default; CTstFormat (const CTstFormat&) = delete; CTstFormat (CTstFormat&&) = delete;
		~CTstFormat (void) = default;

		err_code  Find (const SPxBits&);

		const
		CPxFormat&  operator ()(void) const;
		CPxFormat&  operator ()(void) ;

	private:
		CTstFormat& operator = (const CTstFormat&) = delete; CTstFormat& operator = (CTstFormat&&) = delete;
		CPxFormat m_px_fmt;
	};
}}}

typedef test::open_gl::context::ver_1_1::CCtxToggle TToggle;
#endif/*_TEST_CASE_$D$_CTX_H_INCLUDED*/