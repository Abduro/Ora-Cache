#ifndef _WIN_GUI_MODULE_H_INCLUDED
#define _WIN_GUI_MODULE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Nov-2024 at 20:29:18.731, UTC+4, Batumi, Monday;
	This is Ebo Pack draw renderer test app base module declaration file;
	Using the latest features of DirectX12 requires Windows Target Platform Version not less than 10.0.17763.0, 10.0.18362.0 is used;
*/
#include "win.gui.inc.h"
#include "win.gui_frame.h"
#include "direct_x.wrap.h"

#pragma comment(lib, "color_v15.lib")          // complementary colors;
#pragma comment(lib, "ctl.base_v15.lib")       // user control base;
#pragma comment(lib, "gdi.zbuf_v15.lib")       // in-memory device context for GUI elements;
#pragma comment(lib, "geometry.2D_v15.lib")    // generic shapes;
#pragma comment(lib, "image_v15.lib")          // image cache ;
#pragma comment(lib, "rnd.direct.x_v15.lib")   // DirectX graphic render;

#pragma comment(lib, "sfx.status_v15.lib")     // status bar user common control;
#pragma comment(lib, "sfx.tabbed_v15.lib")     // tabbed control common control;

#pragma comment(lib, "sys.com.core_v15.lib")   // component object model wrapper;
#pragma comment(lib, "sys.err.core_v15.lib")   // system error handling;
#pragma comment(lib, "sys.shared_v15.lib")     // shared macros for debug info output;

#pragma comment(lib, "theme_v15.lib")          // color theme support;
#pragma comment(lib, "win.popup_v15.lib")      // window message handlers;
#if (0) // it is required to remove the output to the 'test output' panel that uses test framework reference;
#pragma comment(lib, "ebo_test_$$t.case.draw.lib")  // test cases of draw helpers, such as, loading image files and adding them to the image list;
#pragma comment(lib, "ebo_test_$$t.case.theme.lib") // test cases of theme lib that allow to get path to theme images' files;
#endif
namespace ebo { namespace boo { namespace gui {

	using CError = shared::sys_core::CError;
	using TError = const CError;

	using namespace shared::types;

	// https://learn.microsoft.com/en-us/cpp/atl/reference/catlexemodulet-class ;

	class CWinGuiModule : public ATL::CAtlExeModuleT<CWinGuiModule> { typedef ATL::CAtlExeModuleT<CWinGuiModule> TBase;
	public:
		err_code PreMessageLoop(int nShowCmd); // it is just for debug purpose only yet; 
	};

}}}

#endif/*_WIN_GUI_MODULE_H_INCLUDED*/