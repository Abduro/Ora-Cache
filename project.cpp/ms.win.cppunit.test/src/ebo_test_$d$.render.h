#ifndef _EBO_TEST_$D$_RENDER_H_INCLUDED
#define _EBO_TEST_$D$_RENDER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Apr-2025 at 04:40:50.58, UTC+4, Batumi, Wednesday;
	This is Ebo Pack 2D/3D draw renderer lib unit test interface declaration file;
	-----------------------------------------------------------------------------
	*Important* : this project must refer the same Windows SDK version as render project does (10.0.18362.0);
*/
#include "_log.h"

#include "direct_x._iface.h"

#include ".\adapter\direct_x.adapter.h"    // without specifying '.\' the compiler cannot find the file being included;
#include ".\adapter\direct_x.adapter.1.h"
#include ".\adapter\direct_x.adapter.2.h"

#include ".\device\direct_x.device.h"
#include ".\device\direct_x.device.1.h"
#include ".\device\direct_x.device.2.h"
#if (0) // included in ebo_test_$d$.render.impl.h ;
#include ".\factory\direct_x.factory.h"
#include ".\factory\direct_x.factory.1.h"
#include ".\factory\direct_x.factory.2.h"
#endif
#include "direct_x.queue.h"
#if (0) // included in ebo_test_$d$.render.impl.h ;
#include ".\swap\direct_x.swap.h"
#include ".\swap\direct_x.swap.1.h"
#include ".\swap\direct_x.swap.2.h"
#endif
#include ".\view\direct_x.view.h"
#include ".\view\direct_x.view.stencil.h"
#include ".\view\direct_x.view.target.h"

#include "render.base.h"
#include "ebo_test_$d$.render.impl.h"

namespace ebo { namespace boo { namespace test { namespace draw {

	using namespace ebo::boo::test;

	using TDrv_type = ex_ui::draw::direct_x::CDrv_Type::e_type;

	using IBufferSink = ex_ui::draw::direct_x::IBuffer_Sync;
	using TBuffer = ex_ui::draw::direct_x::CBuffer;
	using TUsage = ex_ui::draw::direct_x::CBuff_Usage::e_usage;

	using CBuff_Sync = ebo::boo::test::_impl::CBuff_Sync;

	__class(CBuffer) {
	public:
		 CBuffer (const bool _b_verb = false);
		~CBuffer (void) = default;

	public:
		__method (Set);

	private:
		bool m_b_verb;
		CBuff_Sync m_sync;
		TBuffer    m_buffer;
	};

	using TEffect = ex_ui::draw::direct_x::CEffect;
	using TSwapFlag = ex_ui::draw::direct_x::TSwapFlag;
	using TUsage = ex_ui::draw::direct_x::CBuff_Usage::e_usage;

	__class(CEffect) {
	public:
		 CEffect (const bool _b_verb = false);
		~CEffect (void) =default;

	public:
		__method (Set);

	private:
		bool m_b_verb;
		uint32_t m_sync = 0;
		TEffect  m_effect;
	};

	using ISample_Sync = ex_ui::draw::direct_x::ISample_Sync;
	using TSample = ex_ui::draw::direct_x::CSample;

	using CSample_Sync = ebo::boo::test::_impl::CSample_Sync;

	__class(CSample) {
	public:
		 CSample (const bool _b_verb = false);
		~CSample (void) = default;

	public:
		__method (Set);

	private:
		bool  m_b_verb;
		CSample_Sync m_sync;
		TSample m_sample;
	};

}}}}

#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);
#pragma comment(lib, "rnd.direct.x_v15.lib") // this one must be tested by this unit test project; actually, new test cases for direct x must be created;
#pragma comment(lib, "sys.err.core_v15.lib") // for using error object;
#pragma comment(lib, "sys.shared_v15.lib")   // this is the shared base;

#endif/*_EBO_TEST_$D$_RENDER_H_INCLUDED*/