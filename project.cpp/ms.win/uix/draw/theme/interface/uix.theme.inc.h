#ifndef _UIX_THEME_INC_H_INCLUDED
#define _UIX_THEME_INC_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Jun-2025 at 12:30:07.531, UTC+4, Batumi, Saturday;
	This is Ebo Pack color theme project include header(s) declaration file;
*/
#include <atlbase.h>
#include <atlapp.h>
#include <uxtheme.h>
#include <array>

#include "shared.preproc.h"
#include "shared.string.h"

#include "shared.types.h"
#include "sys.err.codes.h"
#include "sys.error.h"

#include "sys.shell.dwm.h"

#pragma region __colors
#include "color.alpha.h"
#include "color.gradient.h"
#include "color.rgb.h"
#include "color.compl.h"
#include "color.compl.predefs.h"
#include "color.named.h"
#include "color.shade.h"
#include "color.x11.h"
#pragma endregion

namespace ex_ui { namespace theme {

	using namespace shared::types;
	using CError  = shared::sys_core::CError;
	using TError  = const CError;

}}

#endif/*_UIX_THEME_INC_H_INCLUDED*/