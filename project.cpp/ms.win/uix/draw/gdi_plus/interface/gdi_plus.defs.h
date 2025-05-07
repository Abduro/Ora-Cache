#ifndef _GDI_PLUS_DEFS_INCLUDED
#define _GDI_PLUS_DEFS_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Jan-2010 at 11:26:44pm, GMT+3, Rostov-on-Don, Saturday;
	This is Sfx Pack drawing service provider class declaration file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack on 11-Aug-2018 at 4:14:00p, UTC+7, Novosibirsk, Saturday;
	Adopted to Geometry Curve project on 17-Feb-2024 at 10:51:26.3687197, UTC+7, Novosibirsk, Saturday;
*/
#include <atlbase.h> // *important*::this header must be included first, otherwise gdi+ headers generate compile error!
#include <map>       // for enumerating possible errors of gdi+ internal state;

// https://stackoverflow.com/questions/27126860/how-to-turn-on-gdi-1-1-instead-of-1-0-in-mfc-project/27128349
#define __manifest_gdiplus_dependency                                        \
    "\"/manifestdependency:type='Win32' "                                    \
    "name='Microsoft.Windows.GdiPlus' version='1.1.0.0' "                    \
    "processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\""

#pragma comment(linker, __manifest_gdiplus_dependency )
#ifdef  GDIPVER
#undef  GDIPVER
#endif
#define GDIPVER 0x0110

/*
	Manifest file must include the dependency of GDI+ version like this:
	<assemblyIdentity
		type="win32"
		name="Microsoft.Windows.Common-Controls" version="6.0.0.0"
		processorArchitecture="*"
		publicKeyToken="6595b64144ccf1df"
		language="*"
	/>
	or linker instruction like this (in one line):
	#pragma comment(linker,
	"\"/manifestdependency:type='Win32' "
	"name='Microsoft.Windows.GdiPlus' version='1.1.0.0' "
	"processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\""
	)
*/

#pragma warning(disable: 4458)  // declaration of 'abcd' hides class member (GDI+)
#include <gdiplus.h>
#include <gdiplusheaders.h>
#include <gdiplusgraphics.h>

#pragma comment(lib, "gdiplus.lib")

#include "shared.types.h"
#include "sys.error.h"

#if defined(_DEBUG)
#include "shared.preproc.h"
#include "shared.string.h"
#endif

namespace ex_ui { namespace draw { namespace gdi_pls {

	// https://learn.microsoft.com/en-us/windows/win32/api/_gdiplus/ >> complete API of GDI+;
	typedef Gdiplus::Bitmap TBitmap;

	using namespace shared::types;

	using CError = shared::sys_core::CError;
	using TError = const CError;

}}}

#endif/*_GDI_PLUS_DEFS_INCLUDED*/