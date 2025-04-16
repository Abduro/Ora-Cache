#ifndef _EBO_TEST_$D$_RENDER_H_INCLUDED
#define _EBO_TEST_$D$_RENDER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 02-Apr-2025 at 04:40:50.58, UTC+4, Batumi, Wednesday;
	This is Ebo Pack 2D/3D draw renderer lib unit test interface declaration file;
	-----------------------------------------------------------------------------
	*Important* : this project must refer the same Windows SDK version as render project does (10.0.18362.0);
*/
#include "_log.h"

#include "sys.error.h"
#include "direct_x._iface.h"
#include "direct_x.adapter.h"
#include "direct_x.adapter.1.h"
#include "direct_x.adapter.2.h"
#include "direct_x.device.h"
#include "direct_x.device.1.h"
#include "direct_x.device.2.h"
#include "direct_x.factory.h"
#include "direct_x.queue.h"

#include "direct_x.swap.h"
#include "direct_x.swap.1.h"
#include "direct_x.swap.2.h"
#include "direct_x.target.h"

#include "render.base.h"
#include "ebo_test_$d$.render.impl.h"

namespace ebo { namespace boo { namespace test { namespace draw {

	// https://learn.microsoft.com/en-us/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference ;
	// https://learn.microsoft.com/en-us/visualstudio/test/writing-unit-tests-for-c-cpp ;

	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using namespace shared::types;

	using namespace ebo::boo::test::_impl;

	using CError  = shared::sys_core::CError;
	using TError  = const CError;
	using TString = TStringEx   ;

	using e_print = ex_ui::draw::direct_x::e_print;
	using IBufferSink = ex_ui::draw::direct_x::IBuffer_Sync;
	using TBuffer = ex_ui::draw::direct_x::CBuffer;
	using TUsage = ex_ui::draw::direct_x::CBuff_Usage::e_usage;

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
#pragma comment(lib, "render_v15.lib")       // this one must be tested by this unit test project;
#pragma comment(lib, "sys.err.core_v15.lib") // for using error object;
#pragma comment(lib, "sys.shared_v15.lib")   // this is the shared base;

#endif/*_EBO_TEST_$D$_RENDER_H_INCLUDED*/