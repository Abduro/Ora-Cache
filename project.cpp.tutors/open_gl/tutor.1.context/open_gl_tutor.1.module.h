#ifndef _OPEN_GL_TUTOR_1_MODULE_H_INCLUDED
#define _OPEN_GL_TUTOR_1_MODULE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Sep-2025 at 12:58:11.803, UTC+4, Batumi, Wednesday;
	This is OpenGL context creation tutorial module interface declaration file;
*/
#include "gl_context.h"
#include "open_gl_tutor.0.defs.h" // has the reference to OpenGL32.lib;

namespace ex_ui { namespace draw { namespace open_gl {  namespace context {

	// https://learn.microsoft.com/en-us/cpp/atl/reference/catlexemodulet-class ;
	class CContextModule : public ATL::CAtlExeModuleT<CContextModule> { typedef ATL::CAtlExeModuleT<CContextModule> TModule;
	public:
		err_code PreMessageLoop(int nShowCmd); // it is just for debug purpose only yet;
	};

}}}}

#pragma comment(lib, "gl.shared_v15.lib")   // OpenGL tutorials shared lib; it is required for usage of shader API;
#pragma comment(lib, "gl.tutor.0.fake.lib") // this lib refers to shared.trim_v15.lib that is common for OpenGL and DirectX;
#pragma comment(lib, "gl.tutor.1.ctx.lib")  // this is this tutorial project static library;

#endif/*_OPEN_GL_TUTOR_1_MODULE_H_INCLUDED*/