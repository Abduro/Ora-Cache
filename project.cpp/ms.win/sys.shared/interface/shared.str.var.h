#ifndef _SHARED_STR_VAR_H_INCLUDED
#define _SHARED_STR_VAR_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-Aug-2024 at 20:05:33.2385865, UTC+4, Batumi, Tuesday;
	This is Ebo pack shared lib _variant_t class string wrapper interface declaration file;
*/
#include <atlstr.h>
#include <comutil.h> // _variant_t;
#include <wtypes.h>  // VARTYPE enum; https://learn.microsoft.com/en-us/windows/win32/api/wtypes/ne-wtypes-varenum ;

#include "shared.types.h"
namespace shared { namespace common {

	using namespace shared::types;

	using _var  = _variant_t; // https://learn.microsoft.com/en-us/cpp/cpp/variant-t-class ; 
	                          // https://learn.microsoft.com/en-us/windows/win32/api/oaidl/ns-oaidl-variant ;
	class CStr_Var : public CString { typedef CString TBase;
	public:
		enum _ndx {
			e_alias = 0, e_desc = 1, e_type = 2, e_value = 3, _count = e_value + 1
		};
	public:
		 CStr_Var (void);
		 CStr_Var (const _variant_t&);
		 CStr_Var (const CStr_Var&);
		 CStr_Var (CStr_Var&&) = delete;
		~CStr_Var (void);

	public:
		_pc_sz  Alias (void) const;
		_pc_sz  Desc  (void) const;

		_pc_sz  Att (const _ndx) const;

		CString Get (_pc_sz _p_sep = _T(";"), _pc_sz _p_pfx = nullptr, _pc_sz _p_psx = nullptr) const;
		bool    Set (const _variant_t& _var);    // returns tue in case when analyzing input variant succeeds, otherwise false;
#if defined(_DEBUG)
		CString Print (const e_print = e_print::e_all) const;
#endif
		_pc_sz  Type  (void) const;
		_pc_sz  Value (void) const;

	public:
		static CString Field(const _variant_t&); // returns a brief description of the field that is used in accordance with input variant type;
		static CString Type (const _variant_t&); // variant types that are supported by _variant_t class, if necessary the list of types may be extended; 

	public:
		CStr_Var& operator = (const CStr_Var&);
		CStr_Var& operator = (CStr_Var&&) = delete;
		CStr_Var& operator <<(const _variant_t&);

	private:
		CString  m_atts[_ndx::_count]; // 0 - alias; 1 - desc; 2 = type; 3 - value;
	};
}}

#endif/*_SHARED_STR_VAR_H_INCLUDED*/