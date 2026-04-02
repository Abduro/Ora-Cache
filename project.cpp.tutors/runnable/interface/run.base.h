#ifndef _RUN_BASE_H_INCLUDED
#define _RUN_BASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 3-Dec-2024 at 16:13:19.564, UTC+4, Batumi, Tuesday;
	This is Ebo pack shared runnable thread project base interface declaration file;
*/
#include "shared.defs.h"
#include <atlwin.h>   // for creating message-only-window;
#include <comdef.h>   // _variant_t;
#include <memory>     // for using smart-pointers, such as unique_ptr;
#include <typeinfo>   // ::std::bad_alloc;
#include "sys.sync_obj.h"
#include "shared.preproc.h"
#include "shared.dbg.h"

namespace shared { namespace runnable {

	using namespace shared::defs;
	using CLocker = shared::sys_core::CSyncObject;

	using d_word = dword ;  // ToDo: typedefs and usings must be made coincident with shared::types;

	struct c_unknown {
	 c_unknown (void) = default; c_unknown (const c_unknown&) = default; c_unknown (c_unknown&&) = default;
	~c_unknown (void) = default;
	 c_unknown& operator = (const c_unknown&) = default;
	 c_unknown& operator = (c_unknown&&) = default;
	 virtual void operator ()(c_unknown* p_this) { delete p_this; p_this = 0; } 
	};
	typedef ::std::unique_ptr<c_unknown, c_unknown> unk_ptr_t;
}}

// error LNK2019: unresolved external symbol __imp_CompareObjectHandles referenced in function "public: bool __cdecl shared::runnable::CEvent::operator==...
// https://stackoverflow.com/questions/76035778/compareobjecthandleshandle-handle-windows-function << example of how to solve the above linking error;
#pragma comment(lib, "mincore")

#endif/*_RUN_BASE_H_INCLUDED*/