#ifndef _COMMON_ERROR_H_INCLUDED
#define _COMMON_ERROR_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Aug-2026 at 13:15:14.707, UTC+4, Batumi, Wednesday;
	This is virtual camera test cases' commom error wrapper declaration file;
*/
#include <winerror.h>  // h_result definition is kept for this version of the implementation;
#include "sys.error.h"

namespace test { namespace error {

	using namespace ::shared::sys_core;
	using CError = ::shared::sys_core::CError;
	using TError = const CError;

}}


#endif/*_COMMON_ERROR_H_INCLUDED*/