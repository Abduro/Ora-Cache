#ifndef _WIN_GUI_MODULE_H_INCLUDED
#define _WIN_GUI_MODULE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Nov-2024 at 20:29:18.731, UTC+4, Batumi, Monday;
	This is Window popup test app base declaration file;
*/
#include <atlbase.h>

#include "sys.error.h"
#include "shared.preproc.h"
#include "shared.string.h"

#include "win.gui_frame.h"

#pragma comment(lib, "color_v15.lib")          // complementary colors;
#pragma comment(lib, "geometry.2D_v15.lib")    // generic shapes;
#pragma comment(lib, "sys.err.core_v15.lib")   // system error handling;
#pragma comment(lib, "sys.shared_v15.lib")     // shared macros for debug info output;
#pragma comment(lib, "win.popup_v15.lib")      // window message handlers;

namespace ebo { namespace boo { namespace gui {

	// https://learn.microsoft.com/en-us/cpp/atl/reference/catlexemodulet-class ;

	class CWinGuiModule : public ATL::CAtlExeModuleT<CWinGuiModule> { typedef ATL::CAtlExeModuleT<CWinGuiModule> TBase;
	public:
		err_code PreMessageLoop(int nShowCmd); // it is just for debug purpose only yet; 
	};

}}}

#endif/*_WIN_GUI_MODULE_H_INCLUDED*/