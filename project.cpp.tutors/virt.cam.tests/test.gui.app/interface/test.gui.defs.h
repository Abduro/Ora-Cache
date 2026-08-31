#ifndef _TEST_GUI_DEFS_H_INCLUDED
#define _TEST_GUI_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Aug-2026 at 16:27:58.190, UTC+4, Batumi, Sunday;
	This is virtual camera test desktop app common declarations' file;
*/
#include "common.defs.h"
#include "sys.error.h"
#include "sfx.tabs.ctrl.h"
#include "shared.str.ext.h"
#include "shared.types.h"

namespace test { namespace app { using namespace ::test::draw::defs; using namespace ::shared::types;

	using CError   = ::shared::sys_core::CError;
	using TError   = const CError;
	using CPadding = ::ex_ui::controls::layout::CPadding_of_rect;
	using CTabbed  = ::ex_ui::controls::sfx::tabbed::CControl;
	using CWndBase = ::ex_ui::popup::CWndBase;

	using IDrawEvtSink = ex_ui::message::handlers::draw::IDrawEventSink;
	using IFormEvtSink = ex_ui::message::handlers::frame::IFrameEventSink;
	using ILifeEvtSink = ex_ui::message::handlers::life::ILifeEvtSink;
	using ISysEvtSink  = ex_ui::message::handlers::IMsgSysEventSink;

namespace cfg {
	const uint16_t u_page_count = 5;   // this is the number of tab control pages: one page per test case of the virtual cam;
	const uint16_t u_border_thick = 1; // tab control border thickness;
}

	// https://learn.microsoft.com/en-us/cpp/preprocessor/hash-if-hash-elif-hash-else-and-hash-endif-directives-c-cpp ;
	// https://en.cppreference.com/w/cpp/preprocessor/conditional ; << good example(s);

	#define _test_case_lvl 0  // tabbed control is created with required test cases tab pages (stubs only);
}}

#endif/*_TEST_GUI_DEFS_H_INCLUDED*/