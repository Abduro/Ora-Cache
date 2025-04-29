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
CStr_Var:: CStr_Var (const _variant_t& _var) : CStr_Var() { *this << _var; }
CStr_Var:: CStr_Var (const CStr_Var& _src) : CStr_Var() { *this = _src; }
CStr_Var::~CStr_Var (void) {}

/////////////////////////////////////////////////////////////////////////////

_pc_sz  CStr_Var::Alias (void) const { return (_pc_sz)this->m_atts[_ndx::e_alias]; }
_pc_sz  CStr_Var::Desc  (void) const { return (_pc_sz)this->m_atts[_ndx::e_desc ]; }

_pc_sz  CStr_Var::Att (const _ndx e_ndx) const {
	e_ndx;
	switch (e_ndx) {
	case _ndx::e_alias: 
	case _ndx::e_desc : 
	case _ndx::e_type : 
	case _ndx::e_value: return this->m_atts[e_ndx].GetString();
	}
	static
	CString cs_inv; cs_inv.Format(_T("#out_of_range:%d;"), e_ndx);
	return  cs_inv;
}

CString CStr_Var::Get (_pc_sz _p_sep, _pc_sz _p_pfx, _pc_sz _p_psx) const {
	_p_sep; _p_pfx; _p_psx;
	CString cs_out(_T("#not_impl;"));
	return  cs_out;
}
#if defined(_DEBUG)
CString CStr_Var::Print (const e_print _e_opt) const {
	_e_opt;
	CString cs_out(_T("#not_impl;"));
	return  cs_out;
}
#endif
bool    CStr_Var::Set (const _variant_t& _var) {
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

CString CStr_Var::Field(const _variant_t&) { return CString(_T("#not_impl;")); }
CString CStr_Var::Type (const _variant_t&) { return CString(_T("#not_impl;")); }

/////////////////////////////////////////////////////////////////////////////

CStr_Var&  CStr_Var::operator = (const CStr_Var& _src) { (TBase&)*this = (const TBase&)_src; return *this; }
CStr_Var&  CStr_Var::operator <<(const _variant_t&) { return *this; }