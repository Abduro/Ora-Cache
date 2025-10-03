#ifndef _SHARED_DEFS_H_INCLUDED
#define _SHARED_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Aug-2025 at 12:15:35.482, UTC+4, Batumi, Tuesday;
	This is Ebo Pack tutorial shared definitions' declaration file;
*/
#include <atlbase.h>
#include <atlwin.h>
#include <atlstr.h>
#include <cstdint>        // for declareing and/or defining data types such as: uint32_t for example;
#include <map>            // window message router uses this header;
#include <vector>         // preprocessor wrapper uses this header;
#include <typeinfo>       // typeinfo >> exception >> vcruntime_exception >> ::std::bad_alloc;

#include "sys.err.trim.h" // includes error codes;

namespace shared { namespace defs {

	using namespace shared::types;

	using CError = shared::sys_core::CError;
	using TError = const CError;

#if defined WIN64
	CString __address_of (const void* const _p_fun_or_obj_ptr);
	CString __address_of (const void* const _p_fun_or_obj_ptr, _pc_sz _p_format/* = _T("0x%08x")*/) ;
#else
	CString __address_of (const void* const _p_fun_or_obj_ptr);
	CString __address_of (const void* const _p_fun_or_obj_ptr, _pc_sz _p_format/* = _T("0x%08x")*/) ;
#endif

	class CString_Ex : public CString { typedef CString TBase;
	public:
		_pc_sz Bool (const bool) ; // sets this string value to text: false or true;
		_pc_sz Format(_pc_sz _p_pattern, ...);
	};
	// https://en.wikipedia.org/wiki/Fixed-point_arithmetic ;
	bool Is_equal (const float _f_lhv, const float _f_rhv, const float _f_threshold = 0.0000001f);

}}

typedef shared::defs::CString_Ex TString;

#endif/*_SHARED_DEFS_H_INCLUDED*/