#ifndef _RENDER_BASE_H_INCLUDED
#define _RENDER_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 31-Mar-2025 at 23:24:24.634, UTC+4, Batumi, Monday;
	This is Ebo Pack renderer base interface declaration file;
*/
#include <atlbase.h>
#include <vfw.h>              // https://learn.microsoft.com/en-us/windows/win32/api/vfw/ ;
#include <xmmintrin.h>        // https://learn.microsoft.com/en-us/cpp/cpp/m128 ;

#include "color._defs.h"
#if defined(_DEBUG)
#include "shared.preproc.h"
#include "shared.string.h"
#endif
#include "shared.types.h"

#include "sys.error.h"

#pragma comment(lib, "vfw32") // https://github.com/ojdkbuild/tools_toolchain_sdk10_1607/tree/master/Lib/10.0.14393.0/um ;

namespace ex_ui { namespace draw { namespace render {
	// https://discussions.unity.com/t/a-question-about-renderer/900817 ;
	using namespace shared::types;

}}}

#endif/*_RENDER_BASE_H_INCLUDED*/