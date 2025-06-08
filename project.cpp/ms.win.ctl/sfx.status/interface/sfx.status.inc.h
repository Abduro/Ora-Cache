#ifndef _SFX_STATUS_INC_H_INCLUDED
#define _SFX_STATUS_INC_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Jun-2025 at 22:55:15.232, UTC+4, Batumi, Wednesday;
	This is Ebo Pack status bar user control include header(s) declaration file;
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

#pragma region __wnd_popup__
#include "wnd.base.h"
#include "wnd.layout.h"
#include "wnd.res.h"
#pragma endregion

#pragma region __ctl_base__
#include "ctl.base.border.h"
#include "ctl.base.layout.h"
#include "ctl.base.pane.h"
#include "ctl.base.props.h"
#pragma endregion

namespace ex_ui { namespace controls { namespace sfx {

	using namespace shared::types;
	using CError  = shared::sys_core::CError;
	using TError  = const CError;

	using CMargin = ex_ui::controls::layout::CMargin;
	using CBorders= ex_ui::controls::borders::CBorders_for_rect;
	using CBorder = ex_ui::controls::borders::CBorder;
	using CPoint  = geometry::_2D::base::CPoint;

	using CWindow = ::ATL::CWindow;
}}}

#endif/*_SFX_STATUS_INC_H_INCLUDED*/