#ifndef _OPEN_GL_TUTOR_0_DEFS_H_INCLUDED
#define _OPEN_GL_TUTOR_0_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Aug-2025 at 22:08:29.106, UTC+4, Batumi, Friday;
	This is Ebo Pack OpenGL tutorial of the creating fake window declaration file;
*/
#include "shared.defs.h"
#include "sys.err.trim.h"

#include "gl_defs.h" // reference to this header file is required, otherwise the linker is not available to link to OpenGL32.dll;

namespace ex_ui { namespace draw { namespace open_gl {

	using namespace shared::defs;

	using CError = shared::sys_core::CError;
	using TError = const CError;

namespace fake {}}}}

#pragma comment(lib, "shared.dbg_v15.lib")  // it is required for usage of the debug output;
#pragma comment(lib, "shared.trim_v15.lib") // it is required for usage of the error base API;

#endif/*_OPEN_GL_TUTOR_0_DEFS_H_INCLUDED*/