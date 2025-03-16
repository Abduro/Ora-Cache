#ifndef _ORA_CACHE_BASE_H_INCLUDED
#define _ORA_CACHE_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Mar-2025 at 00:06:42.0043574, UTC+4, Batumi, Sunday;
	This is Ebo Pack Oracle database data cache base interface declaration file;
*/
#include <atlbase.h>
#include "sys.err.codes.h"
#include "sys.error.h"

#include "shared.types.h"

namespace ora { namespace cache {

	using namespace shared::types;
	using CError  = shared::sys_core::CError;
	using d_word  = dword ;  // ToDo: typedefs and usings must be made coincident with shared::types;
}}               		

#endif/*_ORA_CACHE_BASE_H_INCLUDED*/