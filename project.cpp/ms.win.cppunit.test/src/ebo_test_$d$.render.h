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

namespace ebo { namespace boo { namespace test { namespace draw {

	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using namespace shared::types;

	using CError  = shared::sys_core::CError;
	using TError  = const CError;
	using TString = TStringEx   ;

	using e_print = ex_ui::draw::direct_x::e_print;

}}}}

#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);
#pragma comment(lib, "sys.err.core_v15.lib") // for using error object;
#pragma comment(lib, "sys.shared_v15.lib")   // this is the shared base;
#pragma comment(lib, "render_v15.lib")       // this one must be tested by this unit test project;

#endif/*_EBO_TEST_$D$_RENDER_H_INCLUDED*/