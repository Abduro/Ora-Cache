#ifndef _CTL_BASE_DEFS_H_INCLUDED
#define _CTL_BASE_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-May-2025 at 09:32:46.0138, UTC+4, Batumi, Saturday;
	This is Ebo Pack user control element base declaration file.
*/
#pragma region __atl_&_stl__
#include <atlbase.h>
#include <atlwin.h>
#include <map>
#pragma endregion

#pragma region __shared__
#include "sys.error.h"
#include "shared.preproc.h"
#include "shared.string.h"
#include "shared.types.h"
#include "shared.props.h"
#pragma endregion

#include "color.rgb.h"
#include "color.gradient.h"

#pragma region __2d_geometry__
#include "2d.base.h"
#include "2d.base.line.h"
#include "2d.shape.h"
#include "2d.shape.rect.h"
#pragma endregion

#include "uix.gdi.text.h"
#include "uix.gdi.zbuf.h"
#include "uix.gen.font.h"

#include "wnd.base.h"
#include "wnd.layout.h"

namespace ex_ui { namespace controls {

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-drawframecontrol << drawing system parts of GUI;

	using namespace shared::types;
	using CError = shared::sys_core::CError;
	using TError = const CError;

	using CZBuffer = ex_ui::draw::memory::CZBuffer;
	using ex_ui::draw::CFont;
	using ex_ui::draw::CFontOptions;

	using ex_ui::color::rgb::CGradient ;
}}

#endif/*_CTL_BASE_DEFS_H_INCLUDED*/