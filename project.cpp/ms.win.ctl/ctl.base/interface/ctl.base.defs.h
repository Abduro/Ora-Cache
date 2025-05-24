#ifndef _CTL_BASE_DEFS_H_INCLUDED
#define _CTL_BASE_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-May-2025 at 09:32:46.0138, UTC+4, Batumi, Saturday;
	This is Ebo Pack user control element base declaration file.
*/
#include <atlbase.h>
#include <atlwin.h>

#include "sys.error.h"
#include "shared.preproc.h"
#include "shared.string.h"
#include "shared.types.h"

#include "color.rgb.h"
#include "2d.base.h"
#include "2d.base.line.h"
#include "2d.shape.h"
#include "2d.shape.rect.h"

#include "wnd.base.h"

namespace ex_ui { namespace controls {

	using namespace shared::types;
	using CError = shared::sys_core::CError;
	using TError = const CError;

}}

#endif/*_CTL_BASE_DEFS_H_INCLUDED*/