#ifndef _OPEN_GL_TUTOR_0_MODULE_H_INCLUDED
#define _OPEN_GL_TUTOR_0_MODULE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) 0n 18-Aug-2025 at 22:08:03.216, UTC+4, Batumi, Monday;
	This is OpenGL fake context creation tutorial module interface declaration file;
*/
#include "open_gl_tutor.0.defs.h"

#pragma comment(lib, "gl.tutor.0.fake.lib.vcxproj")

namespace ex_ui { namespace draw { namespace open_gl {  namespace fake {

	using namespace ex_ui::draw::open_gl;

	// https://learn.microsoft.com/en-us/cpp/atl/reference/catlexemodulet-class ;
	class CFakeModule : public ATL::CAtlExeModuleT<CFakeModule> { typedef ATL::CAtlExeModuleT<CFakeModule> TModule;
	public:
		err_code PreMessageLoop(int nShowCmd); // it is just for debug purpose only yet;
	};

}}}}

#endif/*_OPEN_GL_TUTOR_0_MODULE_H_INCLUDED*/