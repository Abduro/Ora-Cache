#ifndef _RENDER_BASE_H_INCLUDED
#define _RENDER_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 31-Mar-2025 at 23:24:24.634, UTC+4, Batumi, Monday;
	This is Ebo Pack renderer base interface declaration file;
*/
#include <atlbase.h>
#include <vfw.h>              // https://learn.microsoft.com/en-us/windows/win32/api/vfw/ ;
#include <xmmintrin.h>        // https://learn.microsoft.com/en-us/cpp/cpp/m128 ;

#include <algorithm>          // std::clamp since C++ 17 ;
#include <cstdint>            // uint8_t ;
#include <memory>             // https://en.cppreference.com/w/cpp/memory/shared_ptr ;

#include "color._defs.h"
#include "color.rgb.h"
#include "2d.base.h"

#if defined(_DEBUG)
#include "shared.preproc.h"
#include "shared.string.h"
#endif
#include "shared.types.h"
#include "sys.sync_obj.h"
#include "sys.error.h"

#pragma comment(lib, "vfw32") // https://github.com/ojdkbuild/tools_toolchain_sdk10_1607/tree/master/Lib/10.0.14393.0/um ;

namespace ex_ui { namespace draw { namespace render {
	// https://discussions.unity.com/t/a-question-about-renderer/900817 ;
	using namespace shared::types;
	using shared::sys_core::CSyncObject;

	// https://learn.microsoft.com/en-us/windows/win32/api/unknwn/nf-unknwn-iunknown-queryinterface(refiid_void) ;
	// *very important* >> it returns a pointer to that interface after calling IUnknown::AddRef on it;

	// https://stackoverflow.com/questions/26687569/atl-ccomptr-attach-detach-and-destructor ;
	// https://learn.microsoft.com/en-us/cpp/atl/reference/ccomptrbase-class ;
	// *very important* >> Attach/Detach don't affect reference counter;
}}}

#endif/*_RENDER_BASE_H_INCLUDED*/