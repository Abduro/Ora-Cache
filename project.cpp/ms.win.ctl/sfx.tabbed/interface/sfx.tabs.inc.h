#ifndef _SFX_TABS_INC_H_INCLUDED
#define _SFX_TABS_INC_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-Jun-2025 at 02:20:22.293, UTC+4, Batumi, Tuesday;
	This is Ebo Pack Sfx tab control include file(s) declaration file.
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
#include "sys.sync_obj.h"
#pragma endregion

#pragma region __wnd_popup__
#include "wnd.base.h"
#include "wnd.layout.h"
#include "wnd.res.h"
#pragma endregion

#pragma region __ctl_base__
#include "ctl.base.border.h"
#include "ctl.base.format.h"
#include "ctl.base.layout.h"
#include "ctl.base.pane.h"
#include "ctl.base.props.h"
#pragma endregion

#include "uix.theme.h"

namespace ex_ui { namespace controls { namespace sfx {

	using namespace shared::types;
	using CError  = shared::sys_core::CError;
	using TError  = const CError;

	using CMargin = ex_ui::controls::layout::CMargin;
	using CBorders= ex_ui::controls::borders::CBorders_for_rect;
	using CBorder = ex_ui::controls::borders::CBorder;
	using CPoint  = geometry::_2D::base::CPoint;

	using CAlign  = ex_ui::draw::text::output::vertical::CAlign;
	using TVert_Flags = ex_ui::draw::text::output::vertical::CAlign_Vert::e_value;

	using CWindow = ::ATL::CWindow;
}}}

#endif/*_SFX_TABS_INC_H_INCLUDED*/