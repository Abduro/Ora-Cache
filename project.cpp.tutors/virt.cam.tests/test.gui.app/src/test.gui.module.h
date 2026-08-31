#ifndef _TEST_GUI_MODULE_H_INCLUDED
#define _TEST_GUI_MODULE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-Aug-2026 at 21:22:48.638, UTC+4, Batumi, Tuesday;
	This is virtual camera test cases' desktop GUI app module interface declaration file;
*/
#include "common.defs.h"
#include "test.gui.window.h"

namespace test { namespace app { using namespace ::test::draw::defs;

	// https://learn.microsoft.com/en-us/cpp/atl/reference/catlexemodulet-class ;
	class CModule : public ATL::CAtlExeModuleT<CModule> { typedef ATL::CAtlExeModuleT<CModule> TModule;
	public:
		err_code PreMessageLoop(int nShowCmd); // it is just for debug purpose only yet;
	};

}}

#pragma comment(lib, "color_v15.lib")          // complementary colors;
#pragma comment(lib, "ctl.base_v15.lib")       // user control base;
#pragma comment(lib, "gdi.zbuf_v15.lib")       // in-memory device context for GUI elements;
#pragma comment(lib, "geometry.2D_v15.lib")    // generic shapes;
#pragma comment(lib, "sys.err.core_v15.lib")   // system error handling;
#pragma comment(lib, "sys.shell_v15.lib")      // system shell DWM wrapper;
#pragma comment(lib, "sys.shared_v15.lib")     // shared macros for debug info output;
#pragma comment(lib, "sfx.tabbed_v15.lib")     // tabbed pages common control;
#pragma comment(lib, "theme_v15.lib")          // color theme support;
#pragma comment(lib, "win.popup_v15.lib")      // window message handlers;

#endif/*_TEST_GUI_MODULE_H_INCLUDED*/