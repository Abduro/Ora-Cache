#ifndef _OPEN_GL_TUTOR_2_MODULE_H_INCLUDED
#define _OPEN_GL_TUTOR_2_MODULE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) 0n 26-Aug-2025 at 02:35:44.496, UTC+4, Batumi, Tuesday;
	This is OpenGL shader creation tutorial module interface declaration file;
*/
#include "open_gl_tutor.0.defs.h"

#pragma comment(lib, "gl.tutor.0.fake.lib")

namespace ex_ui { namespace draw { namespace open_gl {  namespace shader {

	// https://learn.microsoft.com/en-us/cpp/atl/reference/catlexemodulet-class ;
	class CShaderModule : public ATL::CAtlExeModuleT<CShaderModule> { typedef ATL::CAtlExeModuleT<CShaderModule> TModule;
	public:
		err_code PreMessageLoop(int nShowCmd); // it is just for debug purpose only yet;
	};

}}}}

#endif/*_OPEN_GL_TUTOR_2_MODULE_H_INCLUDED*/