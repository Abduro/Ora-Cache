#ifndef _RUN_BASE_H_INCLUDED
#define _RUN_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 3-Dec-2024 at 16:13:19.564, UTC+4, Batumi, Tuesday;
	This is Ebo pack shared runnable thread project base interface declaration file;
*/
#include <atlbase.h>
#include <atlwin.h>   // for creating message-only-window;
#include <comdef.h>   // _variant_t;
#include <typeinfo>   // ::std::bad_alloc;

#include "sys.err.codes.h"
#include "sys.error.h"

#include "shared.types.h"

namespace shared { namespace runnable {

	using namespace shared::types;

	#define _pure PURE

	using CError = shared::sys_core::CError;
	using d_word = dword ;  // ToDo: typedefs and usings must be made coincident with shared::types;

}}

#endif/*_RUN_BASE_H_INCLUDED*/