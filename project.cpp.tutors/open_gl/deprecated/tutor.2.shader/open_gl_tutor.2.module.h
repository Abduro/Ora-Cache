#ifndef _OPEN_GL_TUTOR_2_MODULE_H_INCLUDED
#define _OPEN_GL_TUTOR_2_MODULE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) 0n 26-Aug-2025 at 02:35:44.496, UTC+4, Batumi, Tuesday;
	This is OpenGL shader creation tutorial module interface declaration file;
*/
#include "gl_defs.h"  // has the reference to OpenGL32.lib;
#include "open_gl_tutor.2.wnd.h"  // this is the target window class interface;

namespace ex_ui { namespace draw { namespace open_gl {  namespace shader {

	using namespace ex_ui::draw::open_gl;

	// https://learn.microsoft.com/en-us/cpp/atl/reference/catlexemodulet-class ;
	class CShaderModule : public ATL::CAtlExeModuleT<CShaderModule> { typedef ATL::CAtlExeModuleT<CShaderModule> TModule;
	public:
		err_code PreMessageLoop(int nShowCmd); // it is just for debug purpose only yet;
	};

}}}}

#pragma comment(lib, "shared.dbg_v15.lib")    // shared debug outpu/trace console;
#pragma comment(lib, "shared.gui_v15.lib")    // shared GUI lib for creating main/app window;
#pragma comment(lib, "shared.clr_v15.lib")    // shared color wrapper for applying to vertices of the shapes;

#pragma comment(lib, "gl.shared_v15.lib")     // OpenGL tutorials shared lib; it is required for usage of shader API;
#pragma comment(lib, "gl.procs_v15.lib" )     // OpenGL driver functions' loader;
#pragma comment(lib, "gl.tutor.2.shader.lib") // this is this tutorial project static library;

#endif/*_OPEN_GL_TUTOR_2_MODULE_H_INCLUDED*/