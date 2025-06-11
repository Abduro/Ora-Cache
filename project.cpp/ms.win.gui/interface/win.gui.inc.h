#ifndef _WIN_GUI_INC_H_INCLUDED
#define _WIN_GUI_INC_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-May-2025 at 20:50:56.847, UTC+4, Batumi, Sunday;
	This is Ebo Pack window popup desktop test app include header(s) declaration file;
*/
#pragma region __atl_&_stl__
#include <atlbase.h>
#include <atlwin.h>
#include <map>
#include <cstdint>             // for data type definitions, for example, uint32_t;
#pragma endregion

#pragma region __shared_&_sys_core__
#include "sys.error.h"
#include "shared.preproc.h"
#include "shared.string.h"
#include "shared.types.h"
#pragma endregion

#include "color.rgb.h"
#include "color.compl.h"
#include "color.compl.predefs.h"

#pragma region __wnd_popup__
#include "wnd.base.h"
#include "wnd.layout.h"
#include "wnd.res.h"
#pragma endregion

#pragma region __comm_ctrls__
#include "ctl.base.layout.h"
#include "ctl.base.pane.h"
#include "sfx.status.ctrl.h"
#include "sfx.tabs.ctrl.h"
#pragma endregion

#include "sys.shell.dwm.h"
#include "uix.theme.h"

namespace ebo { namespace boo { namespace gui {

	using CError = shared::sys_core::CError;
	using TError = const CError;

	using namespace shared::types;
	using CWindow = ::ATL::CWindow;

	// https://learn.microsoft.com/en-us/cpp/preprocessor/hash-if-hash-elif-hash-else-and-hash-endif-directives-c-cpp ;
	// https://en.cppreference.com/w/cpp/preprocessor/conditional ; << good example(s);

	// 0 : the test pane draw only; no surface of direct_x;
	// 1 : the status bar control is enabled;
	#define _test_case_lvl 1
}}}

#endif/*_WIN_GUI_INC_H_INCLUDED*/