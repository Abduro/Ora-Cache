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
#include <set>            // is used for cache of draw objects' identifiers;
#include <vector>         // preprocessor wrapper uses this header;
#include <typeinfo>       // typeinfo >> exception >> vcruntime_exception >> ::std::bad_alloc;
#include <stdexcept>      // required for std::out_of_range;

#include "sys.err.trim.h" // includes error codes;

namespace shared { namespace defs {

	using namespace shared::types;
	using CString = ::ATL::CAtlString;

	using CError = shared::sys_core::CError;
	using TError = const CError;

	class CFormat_Spec {
	public:
		enum _spec : uint32_t {
			e_decimal    , // %f, format float number as is (default) ;
			e_scientific , // %e, for example, 1.500000e+00;
			e_hex        , // %a, for example, 0x1;
		};
	};

	typedef CFormat_Spec::_spec t_fmt_spec;

	class CString_Ex : public CString { typedef CString TBase;
	public:
#if defined WIN64
		_pc_sz _addr_of (const void* const _p_fun_or_obj_ptr, const bool _b_low_case = true);
		_pc_sz _addr_of (const void* const _p_fun_or_obj_ptr, _pc_sz _p_format/* = _T("0x%08x")*/, const bool _b_low_case = true) ;
#else
		_pc_sz _addr_of (const void* const _p_fun_or_obj_ptr, const bool _b_low_case = true);
		_pc_sz _addr_of (const void* const _p_fun_or_obj_ptr, _pc_sz _p_format/* = _T("0x%08x")*/, const bool _b_low_case = true) ;
#endif
		_pc_sz Bool (const bool) ; // sets this string value to text: 'false' or 'true';
		_pc_sz Dword (dword) ;     // sets this string to unsigned long value;
		_pc_sz Float(float, t_fmt_spec = t_fmt_spec::e_decimal); // https://en.cppreference.com/w/cpp/io/c/fprintf ;
		_pc_sz Format (_pc_sz _p_pattern, ...);
		_pc_sz Long (long) ;       // sets this string to long value;
	};
#if (0)
	// https://en.wikipedia.org/wiki/Fixed-point_arithmetic ;
	bool Is_equal (const float _f_lhv, const float _f_rhv, const float _f_threshold = 0.0000001f); // is already defined in color._defs.h
#endif
}}

typedef shared::defs::CString_Ex TString;

#endif/*_SHARED_DEFS_H_INCLUDED*/