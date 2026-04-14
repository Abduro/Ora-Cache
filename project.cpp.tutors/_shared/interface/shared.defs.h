#ifndef _SHARED_DEFS_H_INCLUDED
#define _SHARED_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Aug-2025 at 12:15:35.482, UTC+4, Batumi, Tuesday;
	This is Ebo Pack tutorial shared definitions' declaration file;
*/
#pragma region __includes
#include <atlbase.h>      // https://learn.microsoft.com/en-us/cpp/atl-mfc-shared/reference/csimplestringt ;
#include <atlwin.h>
#include <atlstr.h>       // https://learn.microsoft.com/en-us/cpp/atl-mfc-shared/reference/cstringt-class ;
#include <atlfile.h>      // for loading disk file, e.g. shader source code;
#include <cstdint>        // for declareing and/or defining data types such as: uint32_t for example;
#include <array>          // for using fixed-size data sets;
#include <map>            // window message router uses this header;
#include <set>            // is used for cache of draw objects' identifiers;
#include <stdexcept>      // required for std::out_of_range;
#include <thread>         // for using std::thread class;
#include <ctime>          // for using in time & date wrappers, random iface is also uses it;
#include <typeinfo>       // typeinfo >> exception >> vcruntime_exception >> ::std::bad_alloc;
#include <vector>         // preprocessor wrapper uses this header;
#pragma endregion
#include "sys.err.trim.h" // includes error codes;

#ifndef __guid_null
#define __guid_null {0x00000000L, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} 
#endif

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
	typedef ::std::vector<CString> TParts;

	class CString_Ex : public CString { typedef CString TBase;
	public:
		CString_Ex (void);
		CString_Ex (const CString&);
		// https://stackoverflow.com/questions/1950779/is-there-any-way-to-find-the-address-of-a-reference ;
#if defined WIN64
		_pc_sz _addr_of (const void* const _p_fun_or_obj_ptr, const bool _b_low_case = true);
		_pc_sz _addr_of (const void* const _p_fun_or_obj_ptr, _pc_sz _p_format/* = _T("0x%08x")*/, const bool _b_low_case = true) ;
#else
		_pc_sz _addr_of (const void* const _p_fun_or_obj_ptr, const bool _b_low_case = true);
		_pc_sz _addr_of (const void* const _p_fun_or_obj_ptr, _pc_sz _p_format/* = _T("0x%08x")*/, const bool _b_low_case = true) ;
#endif
		_pc_sz Bool  (const bool);   // sets this string value to text: 'false' or 'true';
		_pc_sz Dword (dword);        // sets this string to unsigned long value;
		_pc_sz Float (float, _pc_sz _p_format /*_T("%.8f")*/);
		_pc_sz Float (float, t_fmt_spec = t_fmt_spec::e_decimal, _pc_sz _p_format = nullptr/*_T("%.2f")*/); // https://en.cppreference.com/w/cpp/io/c/fprintf ;
		_pc_sz Format (_pc_sz _p_pattern, ...);

		_guid  Guid (void) const ;  // converts string to guid; if error occurs, GUID_NULL is returned;
		_pc_sz Guid (const _guid&); // converts guid to string;

		_pc_sz Long (long) ;         // sets this string to long value;
		TParts Split (_pc_sz _lp_sz_sep, const bool _b_preserve_sep = false) const;   // splits string by separator specified;

		const
		CString& operator ()(void) const;
		CString& operator ()(void);
	};
#if (0)
	// https://en.wikipedia.org/wiki/Fixed-point_arithmetic ;
	bool Is_equal (const float _f_lhv, const float _f_rhv, const float _f_threshold = 0.0000001f); // is already defined in color._defs.h
#endif
}}

typedef shared::defs::CString_Ex TString;

#endif/*_SHARED_DEFS_H_INCLUDED*/