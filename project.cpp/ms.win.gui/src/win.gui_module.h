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
#include "ebo.sha.gui.theme.h"

#pragma comment(lib, "color_v15.lib")          // complementary colors;
#pragma comment(lib, "ctl.base_v15.lib")       // user control base;
#pragma comment(lib, "gdi.zbuf_v15.lib")       // in-memory device context for GUI elements;
#pragma comment(lib, "geometry.2D_v15.lib")    // generic shapes;
#pragma comment(lib, "render_v15.lib")         // graphic render;
#pragma comment(lib, "sfx.status_v15.lib")     // status bar user common control;
#pragma comment(lib, "sys.err.core_v15.lib")   // system error handling;
#pragma comment(lib, "sys.shared_v15.lib")     // shared macros for debug info output;
#pragma comment(lib, "win.popup_v15.lib")      // window message handlers;

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