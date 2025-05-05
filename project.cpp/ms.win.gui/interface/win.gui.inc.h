#ifndef _WIN_GUI_INC_H_INCLUDED
#define _WIN_GUI_INC_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-May-2025 at 20:50:56.847, UTC+4, Batumi, Sunday;
	This is Ebo Pack window popup desktop test app include header(s) declaration file;
*/
#include <atlbase.h>
#include <atlwin.h>
#include <map>
#include <cstdint>             // for data type definitions, for example, uint32_t;

#include "sys.error.h"
#include "shared.preproc.h"
#include "shared.string.h"
#include "shared.types.h"

#include "color.rgb.h"
#include "wnd.layout.h"
#include "wnd.res.h"

namespace ebo { namespace boo { namespace gui {

	using CError = shared::sys_core::CError;
	using TError = const CError;

	using namespace shared::types;

}}}

#endif/*_WIN_GUI_INC_H_INCLUDED*/