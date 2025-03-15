/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-Aug-2024 at 20:09:45.3078333, UTC+4, Batumi, Tuesday;
	This is Ebo pack shared lib _variant_t class string wrapper interface implementation file;
*/
#include "shared.str.var.h"

using namespace shared::common;
/////////////////////////////////////////////////////////////////////////////

namespace shared { namespace common { namespace _impl {

	// https://learn.microsoft.com/en-us/windows/win32/properties/functions-propvarutil ;
	using var_type = VARTYPE;

	class CVar {
	public:
		CVar(void) = default; CVar(const CVar&) = delete; CVar(CVar&&) = delete; ~CVar(void) = default;

	public:
		bool get_array (CString _atts[CStr_Var::_count]) {
			_atts;
			bool b_result = true;

			return b_result;
		}

	private:
		CVar& operator = (const CVar&) = delete; CVar& operator = (CVar&&) = delete;
	};

}}}
using namespace shared::common::_impl;

/////////////////////////////////////////////////////////////////////////////

CStr_Var:: CStr_Var (void) : TBase() {}
CStr_Var:: CStr_Var (const CStr_Var& _src) : CStr_Var() { *this = _src; }
CStr_Var::~CStr_Var (void) {}

/////////////////////////////////////////////////////////////////////////////

_pc_sz  CStr_Var::Alias (void) const { return (_pc_sz)this->m_atts[_ndx::e_alias]; }
_pc_sz  CStr_Var::Desc  (void) const { return (_pc_sz)this->m_atts[_ndx::e_desc ]; }

bool CStr_Var::Set (const _variant_t& _var) {
	_var;
	bool b_result = true;

	CString& cs_alias = this->m_atts[_ndx::e_alias];
	CString& cs_desc  = this->m_atts[_ndx::e_desc ];
	CString& cs_type  = this->m_atts[_ndx::e_type ];

	if (false){} // these types are supported by _variant_t class as it mentioned in comutil.h, ln: 954;
	else if (VT_ARRAY == _var.vt) { cs_alias = _T(""); cs_desc = _T(""); cs_type = _T("vt_array"); }
	else if (VT_BYREF == _var.vt) { cs_alias = _T(""); cs_desc = _T(""); cs_type = _T("vt_byref"); } // not supported by _variant_t;
	else if (VT_BOOL  == _var.vt) { cs_alias = _T(""); cs_desc = _T(""); cs_type = _T("vt_bool" ); }
	else if (VT_BSTR  == _var.vt) { cs_alias = _T(""); cs_desc = _T(""); cs_type = _T("vt_bstr" ); }
	else if (VT_CY    == _var.vt) { cs_alias = _T(""); cs_desc = _T(""); cs_type = _T("vt_cy"); }
	else if (VT_DATE  == _var.vt) { cs_alias = _T(""); cs_desc = _T(""); cs_type = _T("vt_date"); }
	else if (VT_DECIMAL  == _var.vt) { cs_alias = _T(""); cs_desc = _T(""); cs_type = _T("vt_decimal");  }
	else if (VT_DISPATCH == _var.vt) { cs_alias = _T(""); cs_desc = _T(""); cs_type = _T("vt_dispatch"); }
	else if (VT_EMPTY == _var.vt) { cs_alias = _T(""); cs_desc = _T(""); cs_type = _T("vt_empty"); } // not supported by _variant_t;
	else if (VT_ERROR == _var.vt) { cs_alias = _T(""); cs_desc = _T(""); cs_type = _T("vt_error"); }
	else if (VT_I2    == _var.vt) { cs_alias = _T(""); cs_desc = _T(""); cs_type = _T("vt_i2"); }
	else if (VT_I4    == _var.vt) { cs_alias = _T(""); cs_desc = _T(""); cs_type = _T("vt_i4"); }
	else if (VT_R4    == _var.vt) { cs_alias = _T(""); cs_desc = _T(""); cs_type = _T("vt_r4"); }
	else if (VT_R8    == _var.vt) { cs_alias = _T(""); cs_desc = _T(""); cs_type = _T("vt_r8"); }
	else if (VT_UNKNOWN  == _var.vt) { cs_alias = _T(""); cs_desc = _T(""); cs_type = _T("vt_unknown"); }
	else { cs_alias = _T(""); cs_desc = _T(""); cs_type = _T("#unsupp"); }

	return (b_result = true);
}

_pc_sz  CStr_Var::Type  (void) const { return (_pc_sz)this->m_atts[_ndx::e_type ]; }
_pc_sz  CStr_Var::Value (void) const { return (_pc_sz)this->m_atts[_ndx::e_value]; }

/////////////////////////////////////////////////////////////////////////////

CStr_Var&  CStr_Var::operator = (const CStr_Var& _src) { (TBase&)*this = (const TBase&)_src; return *this; }