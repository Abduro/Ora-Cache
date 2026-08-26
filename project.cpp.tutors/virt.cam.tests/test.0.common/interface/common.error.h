#ifndef _COMMON_ERROR_H_INCLUDED
#define _COMMON_ERROR_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Aug-2026 at 13:15:14.707, UTC+4, Batumi, Wednesday;
	This is virtual camera test cases' commom error wrapper declaration file;
*/
#include <winerror.h>  // h_result definition is kept for this version of the implementation;

#ifndef __s_ok
#define __s_ok S_OK
#endif
#ifndef __s_false
#define __s_false S_FALSE
#endif

#ifndef __DwordToHresult
#define __DwordToHresult(_dword) HRESULT_FROM_WIN32(_dword)
#endif
#define __HresultToDword(_hres) (_hres & 0x0000FFFF)
#define __LastErrToHresult()   __DwordToHresult(::GetLastError())
// tries to analyze what result is being gotten;
#define __is_okay(_hresult)     (S_OK == _hresult)     // warning C4005: '__success': macro redefinition, specstrings_strict.h(620);
#define __succeeded(_hresult)   (SUCCEEDED(_hresult))
#define __failed(_hresult)      (FAILED(_hresult))

namespace test { namespace error {}}


#endif/*_COMMON_ERROR_H_INCLUDED*/