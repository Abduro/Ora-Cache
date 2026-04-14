/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Aug-2025 at 18:20:05.281, UTC+4, Batumi, Tuesday;
	This is Ebo Pack tutorial shared definitions' implementation file;
*/
#include "shared.defs.h"

using namespace shared::defs;

namespace shared { namespace defs {
namespace _impl {

	CString __get_inv_ptr_str (const void* const _p_fun_or_obj_ptr, _pc_sz _p_format) {

		CString cs_out;
		CString cs_val;

		if (false){}
		else if (!_p_fun_or_obj_ptr) {
			cs_val.Format(!!_p_format ? _p_format : _T("0x%x"), 0);
			cs_out.Format(_T("#nullptr (%s)"), (_pc_sz) cs_val);
		}
		else if (__e_handle == _p_fun_or_obj_ptr) {
			cs_val.Format(!!_p_format ? _p_format : _T("0x%x"), __e_handle);
			cs_out.Format(_T("#handle (%s)"), (_pc_sz) cs_val);
		}
		return cs_out;
	}

}
using namespace _impl;

#if defined WIN64
_pc_sz CString_Ex::_addr_of (const void* const _p_fun_or_obj_ptr, const bool _b_low_case) {
	return this->_addr_of (_p_fun_or_obj_ptr, _T("0x%x"), _b_low_case);
}

_pc_sz CString_Ex::_addr_of (const void* const _p_fun_or_obj_ptr, _pc_sz _p_format, const bool _b_low_case) {
	_p_fun_or_obj_ptr; _p_format; _b_low_case;

	(TBase&)*this = __get_inv_ptr_str(_p_fun_or_obj_ptr, _p_format);
	if (false == TBase::IsEmpty())
		return (_pc_sz)*this;

#if (0)
	// https://stackoverflow.com/questions/22846721/pointer-outputs  ;
	const
	uint64_t* p_address = reinterpret_cast<const uint64_t*>(_p_fun_or_obj_ptr);

	((TBase&)*this).Format(!!_p_format ? _p_format : _T("0x%x"), &p_address);
#else
	// https://stackoverflow.com/questions/2369541/where-is-p-useful-with-printf ;
	((TBase&)*this).Format(_T("0x%p"), _p_fun_or_obj_ptr);
	CString cs_loc = ((TBase&)*this).Right(8);
	((TBase&)*this).Format(_T("0x%s"), (_pc_sz) cs_loc);
#endif
	// https://learn.microsoft.com/en-us/cpp/atl-mfc-shared/reference/cstringt-class#makelower ;
	if (_b_low_case)
		((TBase&)*this).MakeLower();
	return (_pc_sz)*this;
}

#else

_pc_sz CString_Ex::_addr_of (const void* const _p_fun_or_obj_ptr, const bool _b_low_case) {
	return this->_addr_of (_p_fun_or_obj_ptr, _T("0x%x"), _b_low_case);
}

_pc_sz CString_Ex::_addr_of (const void* const _p_fun_or_obj_ptr, _pc_sz _p_format, const bool _b_low_case) {
	_p_fun_or_obj_ptr;

	(TBase&)*this = __get_inv_ptr_str(_p_fun_or_obj_ptr, _p_format);
	if (false == TBase::IsEmpty())
		return (_pc_sz)*this;

	const
	uint32_t* p_address = reinterpret_cast<const uint32_t*>(_p_fun_or_obj_ptr);
	uint32_t  n_address = (!!p_address ? *p_address : 0);

	((TBase&)*this).Format(!!_p_format ? _p_format : _T("0x%x"), n_address);
	if (_b_low_case)
		((TBase&)*this).MakeLower();

	return  (_pc_sz)*this;;
}
#endif

}}

using namespace shared::defs;

CString_Ex::CString_Ex (void) : TBase() {}
CString_Ex::CString_Ex (const CString& _src) : TBase(_src) {}

_pc_sz  CString_Ex::Bool  (const bool _b_value) {
	_b_value;
	(TBase&)*this = (_b_value ? _T("true") : _T("false"));

	return (_pc_sz)*this;
}

_pc_sz  CString_Ex::Dword(dword _u_value) {
	_u_value;
	TBase::Format(_T("%u"), _u_value);
	return (_pc_sz)*this;
}

_pc_sz  CString_Ex::Float (float _f_value, _pc_sz _p_format) {
	return this->Float(_f_value, t_fmt_spec::e_decimal, _p_format);
}

_pc_sz  CString_Ex::Float (float _f_value, t_fmt_spec _spec, _pc_sz _p_format) {
	_f_value; _spec; _p_format;
//	https://stackoverflow.com/questions/29200635/convert-float-to-string-with-precision-number-of-decimal-digits-specified ;
//	https://stackoverflow.com/questions/45068641/c-format-code-for-positive-and-negative-float-numbers ;
	if (t_fmt_spec::e_decimal == _spec && !!_p_format)
		TBase::Format(_p_format, _f_value);
	else {
		_pc_sz lp_sz_fmt = (t_fmt_spec::e_hex == _spec ? _T("%a") : (t_fmt_spec::e_scientific == _spec ? _T("%+e") : _T("%+f")));
		TBase::Format(lp_sz_fmt, _f_value);
	}
	return (_pc_sz)*this;
}

_pc_sz  CString_Ex::Format (_pc_sz _p_pattern, ...) {
	_p_pattern;
	if (nullptr == _p_pattern || 0 == ::lstrlen(_p_pattern)) {
		(TBase&)*this = _T("#inv_arg");
		return TBase::GetString();
	}
	va_list args;
	va_start (args, _p_pattern);
	TBase::FormatV(_p_pattern, args);
	va_end (args);
	return TBase::GetString();
}

_guid   CString_Ex::Guid  (void) const {

	static const _guid empty_ = __guid_null;

	_guid result_ = empty_;

	if (TBase::IsEmpty())
		return result_;
	// https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-clsidfromstring ;
	HRESULT hr_ = ::CLSIDFromString(TBase::GetString(), &result_);
	if (FAILED(hr_))
		return empty_; // looks like the result is already set to this value;

	return result_;
}

_pc_sz  CString_Ex::Guid  (const _guid& _guid) {
	_guid;
	if (TBase::IsEmpty() == false)
		TBase::Empty();

	static const _pc_sz lp_sz_pat = _T("{xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}");
	static const size_t n_req_size = ::_tcslen(lp_sz_pat) + 1; // adds one char for ending by zero;

	::std::vector<TCHAR> v_buffer(n_req_size, _T('\0'));
	// https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-stringfromclsid ;
	// https://learn.microsoft.com/en-us/windows/win32/api/combaseapi/nf-combaseapi-stringfromguid2 ;
	const int n_copied = ::StringFromGUID2(_guid, &v_buffer[0], static_cast<int>(n_req_size));

	const bool b_result = 0 != n_copied;
	if (b_result)
		(TBase&)(*this) = v_buffer.data();

	return TBase::GetString();
}

_pc_sz  CString_Ex::Long  (long _l_value) {
	_l_value;
	TBase::Format(_T("%d"), _l_value);
	return (_pc_sz)*this;
}
#if (0)
bool Is_equal (const float _f_lhv, const float _f_rhv, const float _f_threshold) {
	return (::std::fabs(_f_lhv-_f_rhv) < _f_threshold);
}
#endif
TParts  CString_Ex::Split (_pc_sz _lp_sz_sep, const bool _b_preserve_sep) const {
	TParts  vec_;
	if (NULL == _lp_sz_sep || 0 == ::lstrlen(_lp_sz_sep))
		return vec_;
	INT n_pos = 0;
	CString cs_item = TBase::Tokenize(_lp_sz_sep, n_pos); if (cs_item.IsEmpty() == false) cs_item.Trim();

	while (cs_item.IsEmpty() == false) {
		try {
			if (_b_preserve_sep) {
				CString cs_preserved = cs_item; cs_preserved += _lp_sz_sep;
				vec_.push_back(cs_preserved);
			}
			else
			vec_.push_back(cs_item);
		}
		catch (::std::bad_alloc&) {
			return vec_;
		}
		cs_item = TBase::Tokenize(_lp_sz_sep, n_pos); if (cs_item.IsEmpty() == false) cs_item.Trim();
	}

	return vec_;
}

const
CString& CString_Ex::operator ()(void) const { return (TBase&)*this; }
CString& CString_Ex::operator ()(void)       { return (TBase&)*this; }