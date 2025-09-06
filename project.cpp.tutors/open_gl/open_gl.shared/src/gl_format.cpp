/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Sep-2025 at 12:56:20.572, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' format wrapper interface implementation file; 
*/
#include "gl_format.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::format;
using namespace ex_ui::draw::open_gl::format::arb;

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