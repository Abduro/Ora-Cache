/*
	Created by Tech_dog (ebontrop@gmail.com) on 19-Aug-2025 at 18:20:05.281, UTC+4, Batumi, Tuesday;
	This is Ebo Pack tutorial shared definitions' implementation file;
*/
#include "shared.defs.h"


namespace shared { namespace defs {

#if defined WIN64
CString __address_of (const void* const _p_fun_or_obj_ptr) {
	return __address_of (_p_fun_or_obj_ptr, _T("0x%x"));
}

CString __address_of (const void* const _p_fun_or_obj_ptr, _pc_sz _p_format) {
	_p_fun_or_obj_ptr; _p_format;

	if (!_p_fun_or_obj_ptr) {
		return CString(_T("#null"));
	}

	if (INVALID_HANDLE_VALUE == _p_fun_or_obj_ptr) {
		return CString(_T("#inv_val"));
	}

	CString cs_out;
#if (1)
	// https://stackoverflow.com/questions/22846721/pointer-outputs  ;
	const
	uint64_t* p_address = reinterpret_cast<const uint64_t*>(_p_fun_or_obj_ptr);
	if (nullptr == _p_format)
		cs_out.Format(_T("0x%x"), &p_address);
	else
		cs_out.Format(_p_format , &p_address);
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

	if (!_p_fun_or_obj_ptr) {
		return CString(_T("#null"));
	}

	if (INVALID_HANDLE_VALUE == _p_fun_or_obj_ptr) {
		return CString(_T("#inv_val"));
	}

	CString cs_out;

	const
	uint32_t* p_address = reinterpret_cast<const uint32_t*>(_p_fun_or_obj_ptr);
	uint32_t  n_address = (!!p_address ? *p_address : 0);
	
	if (nullptr == _p_format)
		cs_out.Format(_T("0x%x"), n_address);
	else
		cs_out.Format(_p_format , n_address);

	return  cs_out;
}
#endif

}}