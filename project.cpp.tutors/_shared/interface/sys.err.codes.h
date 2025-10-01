#ifndef _SYS_ERROR_CODES_H_INCLUDED
#define _SYS_ERROR_CODES_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Oct-2018 at 11:36:28p, UTC+7, Novosibirsk, Tuesday;
	This is Windows operating system error code declaration file.
	-----------------------------------------------------------------------------
	Adopted to Geometry Curve project on 17-Feb-2024 at 07:47:19.5498651, UTC+7, Novosibirsk, Saturday;
*/
#include <winerror.h>  // h_result definition is kept for this version of the implementation;

#include "shared.types.h"

#pragma region _err_code_defs
// making things a little bit inconspicuous;
#ifndef __e_aborted
#define __e_aborted E_ABORT
#endif
#ifndef __e_fail
#define __e_fail E_FAIL
#endif
#ifndef __e_handle
#define __e_handle INVALID_HANDLE_VALUE // (uint32_t)(-1)
#endif
#ifndef __e_index
#define __e_index DISP_E_BADINDEX
#endif
#ifndef __e_invalid_arg
#define __e_invalid_arg E_INVALIDARG
#define __e_inv_arg   __e_invalid_arg
#endif
#ifndef __e_no_iface
#define __e_no_iface E_NOINTERFACE
#endif
#ifndef __e_no_memory
#define __e_no_memory E_OUTOFMEMORY
#endif
#ifndef __e_not_impl
#define __e_not_impl E_NOTIMPL
#endif
#ifndef __e_not_inited
#define __e_not_inited OLE_E_BLANK
#endif
#ifndef __e_rect
#define __e_rect OLE_E_INVALIDRECT
#endif
#ifndef __e_hwnd
#define __e_hwnd OLE_E_INVALIDHWND
#endif
#ifndef __e_pointer
#define __e_pointer E_POINTER
#endif
#ifndef __e_not_expect
#define __e_not_expect E_UNEXPECTED
#endif

#ifndef __s_ok
#define __s_ok S_OK
#endif
#ifndef __s_false
#define __s_false S_FALSE
#endif

#pragma endregion

// hresult & error code conversions to each other;
#ifndef __DwordToHresult
#define __DwordToHresult(_dword) HRESULT_FROM_WIN32(_dword)
#endif
#define __HresultToDword(_hres) (_hres & 0x0000FFFF)
#define __LastErrToHresult()   __DwordToHresult(::GetLastError())
// tries to analyze what result is being gotten;
#define __is_okay(_hresult)     (S_OK == _hresult)     // warning C4005: '__success': macro redefinition, specstrings_strict.h(620);
#define __succeeded(_hresult)   (SUCCEEDED(_hresult))
#define __failed(_hresult)      (FAILED(_hresult))

namespace shared { namespace sys_core {

	using namespace shared::types;
	// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-erref/18d8fbe8-a967-4f1c-ae50-99ca8e491d2d ;
	// https://learn.microsoft.com/en-us/windows/win32/debug/system-error-codes--0-499- ;
	struct CErr_Codes { 
	public:
		struct eAccess { enum _value : err_code {
			eDenied    = __DwordToHresult(ERROR_ACCESS_DENIED)          , // Access is denied.
			eInvalid   = __DwordToHresult(ERROR_INVALID_ACCESS)         , // The access code is invalid.
			eLocked    = __DwordToHresult(ERROR_LOCKED)                 , // The segment is locked and cannot be reallocated.
			eNotLocked = __DwordToHresult(ERROR_NOT_LOCKED)             , // The segment is already unlocked.
		};};
		struct eData { enum _value : err_code {
			eBuffer    = __DwordToHresult(ERROR_INSUFFICIENT_BUFFER)    , // The data area passed to a system call is too small.
			eEmpty     = __DwordToHresult(ERROR_EMPTY)                  , // The library, drive, or media pool is empty.
			eInvalid   = __DwordToHresult(ERROR_INVALID_DATA)           , // The data is invalid.
			eMismatch  = __DwordToHresult(ERROR_DATATYPE_MISMATCH)      , // Data supplied is of wrong type.
			eMore      = __DwordToHresult(ERROR_MORE_DATA)              , // More data is available.
			eNone      = __DwordToHresult(ERROR_NO_DATA)                , // The pipe is being closed.
			eNotFound  = __DwordToHresult(ERROR_NOT_FOUND)              , // Element not found.
			eUnsupport = __DwordToHresult(ERROR_UNSUPPORTED_TYPE)       , // Data of this type is not supported.
			eType      = __DwordToHresult(ERROR_INVALID_DATATYPE)       , // The environment specified is invalid.
		};};
		struct eDatabase { enum _value : err_code {
			eBlock     = __DwordToHresult(ERROR_INVALID_BLOCK)          , // The storage control block address is invalid.
			eFailure   = __DwordToHresult(ERROR_DATABASE_FAILURE)       , // Unable to read from or write to the database.
			eQuery     = __DwordToHresult(ERROR_BAD_QUERY_SYNTAX)       , // SQL query syntax invalid or unsupported.
		};};
		struct eDevice { enum _value : err_code {
			eAssigned  = __DwordToHresult(ERROR_ALREADY_ASSIGNED)       , // The local device name is already in use.
			eInUse     = __DwordToHresult(ERROR_DEVICE_NOT_AVAILABLE)   , // The device is not ready for use.
		};};
		struct eExecute { enum _value : err_code {
			eAddress   = __DwordToHresult(ERROR_INVALID_ADDRESS)        , // Attempt to access invalid address.
			eFormat    = __DwordToHresult(ERROR_BAD_FORMAT)             , // An attempt was made to load a program with an incorrect format.
			eFunction  = __DwordToHresult(ERROR_INVALID_FUNCTION)       , // Incorrect function.
			eEnviron   = __DwordToHresult(ERROR_BAD_ENVIRONMENT)        , // The environment is incorrect.
			eInternal  = __DwordToHresult(ERROR_INTERNAL_ERROR)         , // An internal error occurred.
			eOperate   = __DwordToHresult(ERROR_INVALID_OPERATION)      , // The operation identifier is not valid.
			eOverflow  = __DwordToHresult(ERROR_ARITHMETIC_OVERFLOW)    , // Arithmetic result exceeded 32 bits.
			eParameter = __DwordToHresult(ERROR_INVALID_PARAMETER)      , // The parameter is incorrect.
			eState     = __DwordToHresult(ERROR_INVALID_STATE)          , // The group or resource is not in the correct state to perform the requested operation.
		};};
		struct eFont   { enum _value : err_code {
			eNoFamily  =   DWRITE_E_NOFONT        , // Indicates the specified font does not exist.
			eNoStyle   =   eData::eUnsupport      , // gdi+, one of the functions throws such a kind of the error;
			eTrueType  =   eData::eMismatch       , // gdi+, not true type font;
		};};
		struct eMemory { enum _value : err_code {
			NotEnough  = __DwordToHresult(ERROR_NOT_ENOUGH_MEMORY)      , // Not enough storage is available to process this command.
		};};
		struct eObject { enum _value : err_code {
			eBusy      = __DwordToHresult(ERROR_BUSY)                   , // The requested resource is in use.
			eExists    = __DwordToHresult(ERROR_OBJECT_ALREADY_EXISTS)  , // The object already exists.
			eHandle    = __DwordToHresult(ERROR_INVALID_HANDLE)         , // The handle is invalid.
			eInited    = __DwordToHresult(ERROR_ALREADY_INITIALIZED)    , // An attempt was made to perform an initialization operation that has already been completed.
			eNotFound  = __DwordToHresult(ERROR_OBJECT_NOT_FOUND)       , // The object identifier does not represent a valid object.
			eProperty  = __DwordToHresult(ERROR_UNKNOWN_PROPERTY)       , // Unknown property.
		};};
		struct ePath { enum _value : err_code {
			eExists    = __DwordToHresult(ERROR_ALREADY_EXISTS)         , // Cannot create a file when that file already exists.
			eName      = __DwordToHresult(ERROR_BAD_PATHNAME)           , // The specified path is invalid.
			eNoFile    = __DwordToHresult(ERROR_FILE_NOT_FOUND)         , // The system cannot find the file specified.
			eNoPath    = __DwordToHresult(ERROR_PATH_NOT_FOUND)         , // The system cannot find the path specified.
			eShared    = __DwordToHresult(ERROR_SHARING_VIOLATION)      , // The process cannot access the file because it is being used by another process.
		};};
		struct eRequest { enum _value : err_code {
			eAborted   = __DwordToHresult(ERROR_REQUEST_ABORTED)        , // The request was aborted.
			eRequested = __DwordToHresult(ERROR_BUSY)                   , // The requested resource is in use.
		};};
		struct eResource { enum _value : err_code {
			eNotFound  = __DwordToHresult(ERROR_RESOURCE_DATA_NOT_FOUND), // The specified image file did not contain a resource section.
			eNotPresent= __DwordToHresult(ERROR_RESOURCE_NOT_PRESENT)   , // The resource required for this operation does not exist.
			eLanguage  = __DwordToHresult(ERROR_RESOURCE_LANG_NOT_FOUND), // The specified resource language ID cannot be found in the image file.
			eVersion   = __DwordToHresult(ERROR_PRODUCT_VERSION)        , // Another version of this product is already installed.
		};};
		struct eUser { enum _value : err_code {
			eAlias     = __DwordToHresult(ERROR_ALIAS_EXISTS)           , // The specified local group already exists.
		};};
		struct eWindow { enum _value : err_code {
			eHandle    = __DwordToHresult(ERROR_INVALID_WINDOW_HANDLE)  , // Invalid window handle.
		};};
		static const err_code no_error = 0; // no error, everything looks to be very fine, possibly;
	}; 
	
}}

typedef shared::sys_core::CErr_Codes TErrCodes;
typedef shared::sys_core::err_code   err_code ;

#endif/*_SYS_ERROR_CODES_H_INCLUDED*/