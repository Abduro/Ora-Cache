#ifndef _OPEN_GL_TUTOR_1_MODULE_H_INCLUDED
#define _OPEN_GL_TUTOR_1_MODULE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Sep-2025 at 12:58:11.803, UTC+4, Batumi, Wednesday;
	This is OpenGL context creation tutorial module interface declaration file;
*/
#include "gl_context.h"
#include "gl_version.h"
#include "open_gl_tutor.0.defs.h" // has the reference to OpenGL32.lib;
#include "open_gl_tutor.1.wnd.h"  // this is the target window class interface;

#include "console.h"
#include "console.font.h"
#include "win.gui.wnd.h"

namespace ex_ui { namespace draw { namespace open_gl {  namespace context {

	using namespace shared::console;
	using namespace shared::gui;
	using namespace ex_ui::draw::open_gl;

	// https://learn.microsoft.com/en-us/cpp/atl/reference/catlexemodulet-class ;
	class CContextModule : public ATL::CAtlExeModuleT<CContextModule> { typedef ATL::CAtlExeModuleT<CContextModule> TModule;
	public:
		err_code PreMessageLoop(int nShowCmd); // it is just for debug purpose only yet;
	};

}}}}

/**important*:
	shorcut menu command 'Project Only >> Clean Only' $(ProjectName) that is 'gl.tutor.1.ctx' removes the file 'gl.tutor.1.ctx.lib' too,
	so this project build will fail;
*/

#pragma comment(lib, "shared.dbg_v15.lib")  // shared debug outpu/trace console;
#pragma comment(lib, "shared.gui_v15.lib")  // shared GUI lib for creating main/app window;

#pragma comment(lib, "gl.shared_v15.lib")   // OpenGL tutorials shared lib; it is required for usage of shader API;
#pragma comment(lib, "gl.procs_v15.lib" )   // OpenGL driver functions' loader;
#pragma comment(lib, "gl.tutor.1.ctx.lib")  // this is this tutorial project static library;

#endif/*_OPEN_GL_TUTOR_1_MODULE_H_INCLUDED*/