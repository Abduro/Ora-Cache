/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Sep-2025 at 12:56:20.572, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' format wrapper interface implementation file; 
*/
#include "gl_format.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::format;
using namespace ex_ui::draw::open_gl::format::arb;

/////////////////////////////////////////////////////////////////////////////

CAtt:: CAtt (const uint32_t _u_key, const uint32_t _u_value, _pc_sz _p_name) : m_key(_u_key), m_val(_u_value), m_name(nullptr == _p_name ? _T("#undef") : _p_name) {}
CAtt:: CAtt (const CAtt& _src) : CAtt() { *this = _src; }
CAtt:: CAtt (CAtt&& _victim) : CAtt() { *this = _victim; }

uint32_t CAtt::Key (void) const { return this->m_key; }
bool     CAtt::Key (const uint32_t _u_key) {
	_u_key;
	const bool b_changed = this->Key() != _u_key;
	if (b_changed)
		this->m_key = _u_key;

	return b_changed;
}

uint32_t CAtt::Value (void) const { return this->m_val; }
bool     CAtt::Value (const uint32_t _u_val) {
	_u_val;
	const bool b_changed = this->Value() != _u_val;
	if (b_changed)
		this->m_val = _u_val;

	return b_changed;
}

CString  CAtt::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {key=%u(%s);value=%u}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {key=%u(%s);value=%u}");
	static _pc_sz pc_sz_pat_r = _T("key=%u(%s);value=%u");

	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format (pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, this->Key(), this->Name(), this->Value()); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format (pc_sz_pat_n, (_pc_sz)__CLASS__, this->Key(), this->Name(), this->Value()); }
	if (e_print::e_req   == _e_opt) { cs_out.Format (pc_sz_pat_r, this->Key(), this->Name(), this->Value()); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}

CAtt& CAtt::operator = (const CAtt& _src) { *this >> _src.Key() << _src.Value() << _src.Name(); return *this; }
CAtt& CAtt::operator = (CAtt&& _victim) { *this = const_cast<CAtt&>(_victim);  return *this; }

CAtt& CAtt::operator <<(const uint32_t _u_value) { this->Value(_u_value); return *this; }
CAtt& CAtt::operator >>(const uint32_t _u_key) { this->Key(_u_key); return *this; }

CAtt& CAtt::operator <<(_pc_sz _p_name) { this->Name(_p_name); return *this; }

/////////////////////////////////////////////////////////////////////////////

CString CAccel::To_str (const e_tokens _e_value) {
	_e_value;
	switch (_e_value) {
	case CAccel::e_tokens::e_full : return CString(_T("__wgl_full_accel_arb")); break;
	case CAccel::e_tokens::e_none : return CString(_T("__wgl_none_accel_arb")); break;
	case CAccel::e_tokens::e_norm : return CString(_T("__wgl_generic_accel_arb")); break;
	case CAccel::e_tokens::e_supp : return CString(_T("__wgl_support_accel_arb")); break;	
	}
	return CString(_T("#undef"));
}

CString CColor::To_str (const e_tokens _e_value) {
	_e_value;
	switch (_e_value) {
	case CColor::e_tokens::e_alpha : return CString(_T("__wgl_alpha_bits_arb")); break;
	case CColor::e_tokens::e_color : return CString(_T("__wgl_color_bits_arb")); break;
	case CColor::e_tokens::e_depth : return CString(_T("__wgl_depth_bits_arb")); break;
	}
	return CString(_T("#undef"));
}

CString CContext::CDebug::To_str (const e_tokens _e_value) {
	_e_value;
	switch (_e_value) {
	case CContext::CDebug::e_tokens::e_debug   : return CString(_T("__wgl_ctx_debug_arb")); break;
	case CContext::CDebug::e_tokens::e_forward : return CString(_T("__wgl_ctx_profile_forward_arb")); break;
	}
	return CString(_T("#undef"));
}

CString CContext::CProfile::To_str (const e_tokens _e_value) {
	_e_value;
	switch (_e_value) {
	case CContext::CProfile::e_tokens::e_core : return CString(_T("__wgl_ctx_profile_core_arb")); break;
	case CContext::CProfile::e_tokens::e_comp : return CString(_T("__wgl_ctx_profile_compatible_arb")); break;
	case CContext::CProfile::e_tokens::e_mask : return CString(_T("__wgl_ctx_profile_mask_arb")); break;	
	}
	return CString(_T("#undef"));
}

CString CContext::CVersion::To_str (const e_tokens _e_value) {
	_e_value;
	switch (_e_value) {
	case CContext::CVersion::e_tokens::e_major : return CString(_T("__wgl_ctx_ver_major_arb")); break;
	case CContext::CVersion::e_tokens::e_minor : return CString(_T("__wgl_ctx_ver_minor_arb")); break;
	}
	return CString(_T("#undef"));
}

CString CDraw::To_str (const CDraw::e_tokens _e_value) {
	_e_value;
	switch (_e_value) {
	case CDraw::e_tokens::e_bitmap  : return CString(_T("__wgl_draw_bitmap_arb")); break;
	case CDraw::e_tokens::e_window  : return CString(_T("__wgl_draw_window_arb")); break;
	case CDraw::e_tokens::e_formats : return CString(_T("__wgl_draw_formats_arb")); break;
	}
	return CString(_T("#undef"));
}

CString CSample::To_str (const CSample::e_tokens _e_value) {
	_e_value;
	switch (_e_value) {
	case CSample::e_tokens::e_multi : return CString(_T("__wgl_sample_multi_arb")); break;
	case CSample::e_tokens::e_count : return CString(_T("__wgl_sample_count_arb")); break;
	}
	return CString(_T("#undef"));
}

CString CSwap::To_str (const CSwap::e_tokens _e_value) {
	_e_value;
	switch (_e_value) {
	case CSwap::e_tokens::e_copy     : return CString(_T("__wgl_swap_copy_arb")); break;
	case CSwap::e_tokens::e_exchange : return CString(_T("__wgl_swap_exchange_arb")); break;
	case CSwap::e_tokens::e_layers   : return CString(_T("__wgl_swap_layers_arb")); break;
	case CSwap::e_tokens::e_method   : return CString(_T("__wgl_swap_method_arb")); break;
	case CSwap::e_tokens::e_undef    : return CString(_T("__wgl_swap_undef_arb")); break;
	}
	return CString(_T("#undef"));
}

CString CType::To_str (const CType::e_tokens _e_value) {
	_e_value;
	switch (_e_value) {
	case CType::e_tokens::e_pixel : return CString(_T("__wgl_type_pixel_arb")); break;
	case CType::e_tokens::e_rgba  : return CString(_T("__wgl_type_rgba_arb")); break;
	case CType::e_tokens::e_index : return CString(_T("__wgl_type_index_arb")); break;
	}
	return CString(_T("#undef"));
}

/////////////////////////////////////////////////////////////////////////////

CAtt_set_base:: CAtt_set_base (void) {
	try { // ends up the result vectors by zero (0);	

		this->m_raw_int.push_back(0);
		this->m_raw_flt.push_back(0.0f);
	}
	catch (const ::std::bad_alloc&) {}
}

const float* const  CAtt_set_base::IAtt_Get_Flt_Ptr (void) const {

	if (this->m_raw_flt.empty() == false)
		this->m_raw_flt.clear();

	try {
		for (uint32_t i_ = 0; i_ < this->m_atts.size(); i_++) {
			const CAtt& att = m_atts.at(i_);
			this->m_raw_flt.push_back(static_cast<float>(att.Key()));
			this->m_raw_flt.push_back(static_cast<float>(att.Value()));
		}
		this->m_raw_flt.push_back(0.0f); // mandatory requirement;
	}
	catch (const ::std::bad_alloc&) {
	}

	return this->m_raw_flt.data();
}

const int*   const  CAtt_set_base::IAtt_Get_Int_Ptr (void) const {

	if (this->m_raw_int.empty() == false)
		this->m_raw_int.clear();

	try {
		for (uint32_t i_ = 0; i_ < this->m_atts.size(); i_++) {
			const CAtt& att = m_atts.at(i_);
			this->m_raw_int.push_back(static_cast<int>(att.Key()));
			this->m_raw_int.push_back(static_cast<int>(att.Value()));
		}
		this->m_raw_int.push_back(0); // mandatory requirement;
	}
	catch (const ::std::bad_alloc&) {
	}

	return this->m_raw_int.data();
}

err_code CAtt_set_base::Append (const CAtt& _att) {
	_att;
	err_code n_result = __s_ok;
	try {
		this->m_atts.push_back(_att);
	}
	catch (const ::std::bad_alloc&) {
		n_result = __e_no_memory;
	}
	return n_result;
}

err_code CAtt_set_base::Append (const uint32_t _u_key, uint32_t _u_val, _pc_sz _p_name) {
	_u_key; _u_val; _p_name;
	CAtt att(_u_key, _u_val, _p_name);
	return this->Append(att);
}

CAtt_set_base& CAtt_set_base::operator += (const CAtt& _att) { this->Append(_att); return *this; }

/////////////////////////////////////////////////////////////////////////////

CAtt_set_pixels:: CAtt_set_pixels (void) : TBase() {

	err_code n_result = __s_ok;
	// -----------------------------------------------------+     att key   -+-   att value   -+-  att name ;  
	if (__succeeded(n_result)) n_result = TBase::Append(CAtt(arb::CDraw::e_window, _gl_true, (_pc_sz) arb::CDraw::To_str(arb::CDraw::e_window)));
	if (__succeeded(n_result)) n_result = TBase::Append(CAtt(arb::CAccel::e_supp, _gl_true, (_pc_sz) arb::CAccel::To_str(arb::CAccel::e_supp)));
	if (__succeeded(n_result)) n_result = TBase::Append(CAtt(arb::CBuffer::e_double, _gl_true, (_pc_sz) arb::CBuffer::To_str(arb::CBuffer::e_double)));
	if (__succeeded(n_result)) n_result = TBase::Append(CAtt(arb::CSwap::e_exchange, arb::CSwap::e_copy, (_pc_sz) arb::CSwap::To_str(arb::CSwap::e_exchange)));
	if (__succeeded(n_result)) n_result = TBase::Append(CAtt(arb::CType::e_pixel, arb::CType::e_rgba, (_pc_sz) arb::CType::To_str(arb::CType::e_pixel)));
	if (__succeeded(n_result)) n_result = TBase::Append(CAtt(arb::CAccel::e_supp, arb::CAccel::e_full, (_pc_sz) arb::CAccel::To_str(arb::CAccel::e_supp)));
	if (__succeeded(n_result)) n_result = TBase::Append(CAtt(arb::CSwap::e_method, arb::CSwap::e_copy, (_pc_sz) arb::CSwap::To_str(arb::CSwap::e_method)));
	if (__succeeded(n_result)) n_result = TBase::Append(CAtt(arb::CColor::e_alpha,  8, (_pc_sz) arb::CColor::To_str(arb::CColor::e_alpha)));
	if (__succeeded(n_result)) n_result = TBase::Append(CAtt(arb::CColor::e_color, 32, (_pc_sz) arb::CColor::To_str(arb::CColor::e_color)));
	if (__succeeded(n_result)) n_result = TBase::Append(CAtt(arb::CColor::e_depth, 24, (_pc_sz) arb::CColor::To_str(arb::CColor::e_depth)));
}