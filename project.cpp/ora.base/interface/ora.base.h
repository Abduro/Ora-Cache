#ifndef _ORA_BASE_H_INCLUDED
#define _ORA_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Mar-2025 at 23:59:06.9670086, UTC+4, Batumi, Saturday;
	This is Ebo Pack Oracle database base wrappers' interface declaration file;
*/
#include <atlbase.h>
#include "sys.err.codes.h"
#include "sys.error.h"

#include "shared.types.h"

namespace ora { namespace base {

	using namespace shared::types;
	using CError  = shared::sys_core::CError;
	using d_word  = dword ;  // ToDo: typedefs and usings must be made coincident with shared::types;
}}               		

#endif/*_ORA_BASE_H_INCLUDED*/