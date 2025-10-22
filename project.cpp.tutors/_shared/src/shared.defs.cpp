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
CString __address_of (const void* const _p_fun_or_obj_ptr) {
	return __address_of (_p_fun_or_obj_ptr, _T("0x%x"));
}

CString __address_of (const void* const _p_fun_or_obj_ptr, _pc_sz _p_format) {
	_p_fun_or_obj_ptr; _p_format;

	CString cs_out = __get_inv_ptr_str(_p_fun_or_obj_ptr, _p_format);
	if (false == cs_out.IsEmpty())
		return cs_out;

#if (1)
	// https://stackoverflow.com/questions/22846721/pointer-outputs  ;
	const
	uint64_t* p_address = reinterpret_cast<const uint64_t*>(_p_fun_or_obj_ptr);

	cs_out.Format(!!_p_format ? _p_format : _T("0x%x"), &p_address);

#else
	// https://stackoverflow.com/questions/2369541/where-is-p-useful-with-printf ;
	cs_out.Format(_T("0x%p"), _p_fun_or_obj_ptr);
#endif
	return  cs_out;
}

#else

CString __address_of (const void* const _p_fun_or_obj_ptr) {
	return __address_of (_p_fun_or_obj_ptr, _T("0x%x"));
}

CString __address_of (const void* const _p_fun_or_obj_ptr, _pc_sz _p_format) {
	_p_fun_or_obj_ptr;

	CString cs_out = __get_inv_ptr_str(_p_fun_or_obj_ptr, _p_format);
	if (false == cs_out.IsEmpty())
		return cs_out;

	const
	uint32_t* p_address = reinterpret_cast<const uint32_t*>(_p_fun_or_obj_ptr);
	uint32_t  n_address = (!!p_address ? *p_address : 0);

	cs_out.Format(!!_p_format ? _p_format : _T("0x%x"), n_address);
	return  cs_out;
}
#endif

}}

using namespace shared::defs;

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

_pc_sz  CString_Ex::Float (float _f_value, t_fmt_spec _spec) {
	_f_value; _spec;

//	https://stackoverflow.com/questions/45068641/c-format-code-for-positive-and-negative-float-numbers ;
	_pc_sz lp_sz_fmt = (t_fmt_spec::e_hex == _spec ? _T("%a") : (t_fmt_spec::e_scientific == _spec ? _T("%+e") : _T("%+f")));

	TBase::Format(lp_sz_fmt, _f_value);
	
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

_pc_sz  CString_Ex::Long  (long _l_value) {
	_l_value;
	TBase::Format(_T("%d"), _l_value);
	return (_pc_sz)*this;
}

bool Is_equal (const float _f_lhv, const float _f_rhv, const float _f_threshold) {
	return (::std::fabs(_f_lhv-_f_rhv) < _f_threshold);
}