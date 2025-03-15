#ifndef _MS_CON_APP_H_INCLUDED
#define _MS_CON_APP_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 8-May-2024 at 19:00:28.8862746, UTC+7, Novosibirsk, Wednesday;
	This is Ebo Pack cppuinit test console app interface declaration file;
*/
#include <conio.h>

#pragma comment(lib, "sys.shared_v15.lib")
#pragma comment(lib, "sys.err.core_v15.lib")

#include "shared.string.h"
#include "ms.con.cmd.ln.h"

#include "shared.types.h"

#include "test_$1$_std_except.h"

namespace ebo { namespace boo { namespace con {

	using namespace shared::types;

	static _pc_sz const err_prfx = _T("\t[#err]");
	static _pc_sz const inf_prfx = _T("\t[info]");
	static _pc_sz const wrn_prfx = _T("\t[warn]");

}}}

#endif/*_MS_CON_APP_H_INCLUDED*/