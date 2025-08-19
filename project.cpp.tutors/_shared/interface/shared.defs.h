#ifndef _SHARED_DEFS_H_INCLUDED
#define _SHARED_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Aug-2025 at 12:15:35.482, UTC+4, Batumi, Tuesday;
	This is Ebo Pack tutorial shared definitions' declaration file;
*/
#include <atlbase.h>
#include <atlwin.h>
#include <atlstr.h>
#include <cstdint>    // for declareing and/or defining data types such as: uint32_t for example;
// https://learn.microsoft.com/en-us/windows/win32/opengl/opengl-on-windows-nt--windows-2000--and-windows-95-98 ; << old but still valid;
#include <gl/gl.h>

#pragma comment(lib, "opengl32.lib")

#ifndef __e_not_inited
#define __e_not_inited OLE_E_BLANK
#endif

#ifndef __DwordToHresult
#define __DwordToHresult(_dword) HRESULT_FROM_WIN32(_dword)
#endif
#define __HresultToDword(_hres) (_hres & 0x0000FFFF)
#define __LastErrToHresult()   __DwordToHresult(::GetLastError())

#ifndef __s_ok
#define __s_ok S_OK
#endif

#define __is_okay(_hresult)     (S_OK == _hresult)     // warning C4005: '__success': macro redefinition, specstrings_strict.h(620);
#define __succeeded(_hresult)   (SUCCEEDED(_hresult))
#define __failed(_hresult)      (FAILED(_hresult))

namespace shared { namespace defs {

	typedef LPCTSTR _pc_sz; // since Win32 there is neither 'long' nor 'near' pointer types;
	typedef LPTSTR  _p_sz ;

	typedef long  err_code;

#if defined WIN64
	CString __address_of (const void* const _p_fun_or_obj_ptr);
	CString __address_of (const void* const _p_fun_or_obj_ptr, _pc_sz _p_format/* = _T("0x%08x")*/) ;
#else
	CString __address_of (const void* const _p_fun_or_obj_ptr);
	CString __address_of (const void* const _p_fun_or_obj_ptr, _pc_sz _p_format/* = _T("0x%08x")*/) ;
#endif

}}

#endif/*_SHARED_DEFS_H_INCLUDED*/