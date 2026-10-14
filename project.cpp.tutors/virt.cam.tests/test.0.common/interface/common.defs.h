#ifndef _COMMON_DEFS_H_INCLUDED
#define _COMMON_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Aug-2026 at 09:03:48.398, UTC+4, Batumi, Wednesday;
	This is virtual camera test cases' common declaration file;
*/
#include <atlbase.h>      // https://learn.microsoft.com/en-us/cpp/atl/reference/atl-classes ;
#include <atlwin.h>       // https://learn.microsoft.com/en-us/cpp/atl/reference/cwindow-class ;
#include <atlstr.h>       // https://learn.microsoft.com/en-us/cpp/atl-mfc-shared/reference/cstringt-class ;
#include <cstdint>
#include <tchar.h>

#include "shared.dbg.h"
#include "shared.types.h"
#include "sys.error.h"

#include "web.ie.browser.h"
#include "web.ie.locator.h"

namespace test { namespace draw { namespace defs {

	using namespace ::shared::types;
	using namespace ::shared::sys_core;
	using CError  = ::shared::sys_core::CError;
	using TError  = const CError;

}}}

#endif/*_COMMON_DEFS_H_INCLUDED*/