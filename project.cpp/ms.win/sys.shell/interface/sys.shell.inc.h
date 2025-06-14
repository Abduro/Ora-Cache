#ifndef _SYS_SHELL_INC_H_INCLUDED
#define _SYS_SHELL_INC_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Jun-2025 at 22:33:56.009, UTC+4, Batumi, Saturday;
	This is Ebo Pack system file explorer shell wrapper include header(s) declaration file;
*/
#include <atlbase.h>
#include <dwmapi.h>
#include <shlobj.h>     // for font enumeration in the system 'Font' folder;
#include <sysinfoapi.h> // for getting OS version, it is required for DwmGetWindowAttribute() & DwmSetWindowAttribute();
#include <winreg.h>     // required to be included after 'atlbase.h', otherwise the error C1189: "No Target Architecture";

#include "shared.preproc.h"
#include "shared.string.h"

#include "shared.types.h"
#include "sys.err.codes.h"
#include "sys.error.h"

#define STRICT_TYPED_ITEMIDS // https://learn.microsoft.com/en-us/windows/win32/api/shtypes/ns-shtypes-itemidlist ;

namespace shared { namespace sys_core { namespace shell {

	using namespace shared::types;
	using CError  = shared::sys_core::CError;
	using TError  = const CError;

}}}

#pragma comment(lib, "Dwmapi.lib")

#endif/*_SYS_SHELL_INC_H_INCLUDED*/