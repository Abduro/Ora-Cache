#ifndef _SHARED_STR_EXT_H_INCLUDED
#define _SHARED_STR_EXT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-Oct-2018 at 11:57:12p, UTC+7, Novosibirsk, Wednesday;
	This is Ebo Pack shared lite library string common functionality interface declaration file.
	-----------------------------------------------------------------------------
	Adopted to Geometry Curve project on 17-Feb-2024 at 07:04:17.4393844, UTC+7, Novosibirsk, Saturday;
*/
#include <strsafe.h> // ::StringCchVPrintfEx();
#include <atlstr.h>
#include <stdlib.h>  // ::_ltoa_s; _tstol;

#include <cstdio>    // std::printf; https://en.cppreference.com/w/cpp/io/c/fprintf
#include <string>    // std::stoi, std::stol, std::stoll; https://en.cppreference.com/w/cpp/string/basic_string/stol ;
#include <vector>

#include <combaseapi.h> // CLSIDFromString(); https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-clsidfromstring ;
                        // StringFromGUID2(); https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-stringfromguid2 ;

#include "shared.types.h"
#include "shared.str.var.h"

#ifndef __guid_null
#define __guid_null {0x00000000L, 0x0000, 0x0000, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} 
#endif

#ifndef _T
#ifndef  _UNICODE
#define _T(x)      x
#else
#define _T(x) L ## x
#endif
#endif

namespace shared { namespace common {

	using namespace shared::types;

	typedef ::std::vector<CString> TParts;

	class CFormat_Spec {
	public:
		enum _spec : uint32_t {
			e_decimal    , // %f, format float number as is (default) ;
			e_scientific , // %e, for example, 1.500000e+00;
			e_hex        , // %a, for example, 0x1;
		};
	};

	typedef CFormat_Spec::_spec t_fmt_spec;

	// a number to string:
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/strtof-strtof-l-wcstof-wcstof-l ; not used yet;
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/itoa-s-itow-s ;
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/locale ;
	// and back:
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/data-conversion ;
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/itoa-s-itow-s ;
	// https://stackoverflow.com/questions/4459987/convert-float-to-string-without-losing-precision ;
	/*
		***note***
		using _variant_t class looks like much better: it provides all necessary data type conversion functions 
		and this class is much easier (perhaps) to use in comparison with manual conversions;
	*/
	class CString_Ex : public CString { typedef CString TBase;
	public:
		 CString_Ex (const bool );
		 CString_Ex (const dword);
		 CString_Ex (const float);
		 CString_Ex (const long );
		 CString_Ex (_pc_sz _lp_sz_value = nullptr);
		 CString_Ex (const CString_Ex&);
		 CString_Ex (CString_Ex&&) = delete;
		~CString_Ex (void) = default;

	public: // data conversion from numeric/boolean to string and vice versa;
		ushort  Bytes(void) const ;      // returns string length in bytes, including zero-terminated symbol at the end of string;

		bool    Bool (void) const ;      // gets this string value as a boolean data type;
		_pc_sz  Bool (const bool) ;      // sets this string value to text: false or true;

		dword   Dword(void) const;       // gets this string as unsigned long data type;
		_pc_sz  Dword(dword) ;           // sets this string to unsigned long value;

		float   Float(void) const ;      // gets this string value as a float data type;
		_pc_sz  Float(float, t_fmt_spec = t_fmt_spec::e_decimal); // https://en.cppreference.com/w/cpp/io/c/fprintf ;

		_guid   Guid (void) const ;      // converts string to guid; if error occurs, GUID_NULL is returned;
		_pc_sz  Guid (const _guid&);     // converts guid to string;

		long    Long (void) const ;      // gets this string as a long data type;
		_pc_sz  Long (long) ;            // sets this string to long value;

		bool    Is   (void) const;       // returns true if this string is not empty;

//		_var    Var  (void) const;       // converts string to _variant_t;
//		_pc_sz  Var  (const _var&, _pc_sz _fmt = _T("type=%s;value=%s")); // converts _variant_t to string in accordance with format pattern provided;

		// https://stackoverflow.com/questions/1950779/is-there-any-way-to-find-the-address-of-a-reference ;
#if defined WIN64
		_pc_sz __address_of (const void* const _p_fun_or_obj_ptr) ;
#else
		_pc_sz __address_of (const void* const _p_fun_or_obj_ptr) ;
#endif
		/*
			Regarding the base class StringT::Format(...) method:
				unfortunately it does not provide any description of an error that may occur during matching the format specification
				to input variant list arguments, also the format pattern may contain unsupported or unknowing specifiers;
				...
				the base class format method in case of error just shows debug dialog with the error simplified description and may call
				system doctor Watson function that terminates the process that has thrown this exception;
			ToDo:
				It would be better to generate an error object and to throw the object to the caller of the format method;
		*/
	public:
		_pc_sz   Before(t_char _lp_sz_sep = _T('\\'), _pc_sz _lp_sz_pfx = _T("..."), const bool _b_exc_sep = true);
		_pc_sz   Format(_pc_sz _lp_sz_fmt, ...);
		_pc_sz   Format(_pc_sz _lp_sz_fmt, va_list);
		TParts   Split (_pc_sz _lp_sz_sep, const bool _b_preserve_sep = false) const;   // splits string by separator specified;
#if(0) // already exists in base clase;
	public:
		CString_Ex& operator=(const _variant_t&);
#endif
	public:
		CString_Ex& operator = (const CString_Ex&);
		CString_Ex& operator <<(bool  _b_value);  // sets this string value from boolean data;
		CString_Ex& operator <<(dword _d_value);  // sets this string value from dword data (unsigned long);
		CString_Ex& operator <<(float _f_value);  // sets this string value from float data;
		CString_Ex& operator <<(long  _l_value);  // sets this string value from long  data;
		CString_Ex& operator <<(_pc_sz _lp_sz_value);
		CString_Ex& operator <<(_guid& _guid_value );

	public:
		operator CString (void) const; // returns this string value as object; makes a copy of the string;
		operator bool    (void) const; // returns this string value as boolean;
		operator dword   (void) const; // returns this string value as unsigned long (dword);
		operator float   (void) const; // returns this string value as float;
		operator _guid   (void) const; // returns this string value as GUID structure;
		operator long    (void) const; // returns this string value as long;
		operator _pc_sz  (void) const; // returns this string value as string;
	};

	class CString_2 : public CString { typedef CString TBase;
	public:
		 CString_2 (void);
		~CString_2 (void);

	public:
		void Format (_pc_sz _p_sz_format, ...);
	};
}}

typedef shared::common::CString_Ex  TStringEx;

#endif/*_SHARED_STR_EXT_H_INCLUDED*/