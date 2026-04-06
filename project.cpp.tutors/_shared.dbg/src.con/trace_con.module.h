#ifndef _TRACE_CON_MODULE_H_INCLUDED
#define _TRACE_CON_MODULE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Mar-2026 at 13:18:10.358, UTC+4, Batumi, Tuesday;
	This is Ebo Pack tutorials' shared debug trace console entry point declaration file;
*/
#include "shared.defs.h"
#include "shared.preproc.h"
#include "shared.dbg.h"
#include <iostream>
#include "shared.wnd.atom.h"
#include "console.event.h"

#ifdef _UNICODE
#define in_t  ::std::wcin
#define out_t ::std::wcout
#else
#define in_t  ::std::cin
#define out_t ::std::cout
#endif

namespace shared { namespace console { namespace _impl { using namespace shared::defs;

	typedef l_result (__stdcall *pfn_WndProc)(HWND, _uint, w_param, l_param);

	class CInvader {
	public:
		 CInvader (void);
		~CInvader (void);
		 CInvader (const CInvader&) = delete; CInvader (CInvader&&) = delete;

		 err_code BringBack (void);
		 err_code Deprive (void);

		 TError Error (void) const;

		 static l_result WndProc (HWND, _uint, w_param, l_param);

	private:
		CInvader& operator = (const CInvader&) = delete; CInvader& operator = (CInvader&&) = delete;
		CError    m_error;
		static
		__int3264 m_proc_origin;
	};
#ifndef _USE_CONSOLE
	// https://learn.microsoft.com/en-us/cpp/atl/reference/catlexemodulet-class ;
	class CTraceConsole : public ATL::CAtlExeModuleT<CTraceConsole> { typedef ATL::CAtlExeModuleT<CTraceConsole> TModule;
	public:
		err_code PreMessageLoop(int nShowCmd); // it is just for debug purpose only yet;
	};
#endif
}}}

#pragma comment(lib, "shared.dbg_v15.lib")    // shared debug outpu/trace console;
#pragma comment(lib, "shared.gui_v15.lib")    // shared GUI lib for creating main/app window;
#pragma comment(lib, "shared.trim_v15.lib")   // shared wrappers of required system functionality;

#endif/*_TRACE_CON_MODULE_H_INCLUDED*/