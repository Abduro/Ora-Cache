#ifndef _OBJ_PARSER_MODULE_H_INCLUDED
#define _OBJ_PARSER_MODULE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Jun-2026 at 11:46:26.558, UTC+4, Batumi, Sunday;
	This is 3D module object parser module interface declaration file;
*/
#include "obj_parser.defs.h"
#include "console.h"

namespace shared { namespace parsers { namespace obj { using namespace shared::defs;

#ifndef _USE_CONSOLE
	// https://learn.microsoft.com/en-us/cpp/atl/reference/catlexemodulet-class ;
	class CTraceConsole : public ATL::CAtlExeModuleT<CTraceConsole> { typedef ATL::CAtlExeModuleT<CTraceConsole> TModule;
	public:
		err_code PreMessageLoop(int nShowCmd); // it is just for debug purpose only yet;
	};
#endif

}}}

#pragma comment(lib, "shared.clr_v15.lib")    // shared color wrappers' library;
#pragma comment(lib, "shared.dbg_v15.lib")    // shared debug output/trace console;
#pragma comment(lib, "shared.gui_v15.lib")    // shared GUI wrappers' library: window, messages, theme;
#pragma comment(lib, "shared.trim_v15.lib")   // shared wrappers of required system functionality;

#endif/*_OBJ_PARSER_MODULE_H_INCLUDED*/