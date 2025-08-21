#ifndef _OPEN_GL_TUTOR_0_MODULE_H_INCLUDED
#define _OPEN_GL_TUTOR_0_MODULE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) 0n 18-Aug-2025 at 22:08:03.216, UTC+4, Batumi, Monday;
	This is OpenGL fake content creation tutorial module interface declaration file;
*/
#include "shared.defs.h"
#include "shared.dbg.h"
#include "sys.err.trim.h"

#include "gl_defs.h" // reference to this header file is required, otherwise the linker is not available to link to OpenGL32.dll;

#pragma comment(lib, "shared.trim_v15.lib")
#pragma comment(lib, "gl.shared_v15.lib")

namespace ex_ui { namespace draw { namespace open_gl {  namespace fake {

	using namespace shared::defs;

	using CError = shared::sys_core::CError;
	using TError = const CError;

	// https://learn.microsoft.com/en-us/cpp/atl/reference/catlexemodulet-class ;
	class CFakeModule : public ATL::CAtlExeModuleT<CFakeModule> { typedef ATL::CAtlExeModuleT<CFakeModule> TModule;
	public:
		err_code PreMessageLoop(int nShowCmd); // it is just for debug purpose only yet;
	};

}}}}

#endif/*_OPEN_GL_TUTOR_0_MODULE_H_INCLUDED*/