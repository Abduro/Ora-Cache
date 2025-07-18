#ifndef _UIX_IMAGE_DEFS_H_INCLUDED
#define _UIX_IMAGE_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Jul-2025 at 20:29:18.730, UTC+4, Batumi, Wednesday;
	This is Ebo Pack image wrappers' project included references and common declaration file;
*/
#include <atlbase.h>
#include <atlcomcli.h>
#include <atlfile.h>

#include <commctrl.h>
#include <coml2api.h>

#pragma comment (lib, "Comctl32.lib")

#include "shared.props.h"
#include "shared.types.h"
#include "shared.preproc.h"
#include "shared.string.h"

#include "sys.error.h"
#include "sys.mem.global.h"

namespace ex_ui { namespace draw { namespace images {

	using namespace shared::types;
	using CError  = shared::sys_core::CError;
	using TError  = const CError;
	using TString = TStringEx;

	using namespace shared::memory;

}}}

#endif/*_UIX_IMAGE_DEFS_H_INCLUDED*/