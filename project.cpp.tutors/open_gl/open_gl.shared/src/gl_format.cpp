/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Sep-2025 at 12:56:20.572, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' format wrapper interface implementation file; 
*/
#include "gl_format.h"
#include "gl_context.h"
#include "gl_procs_ctx.h"

using namespace ex_ui::draw::open_gl;
using namespace ex_ui::draw::open_gl::format;
using namespace ex_ui::draw::open_gl::format::arb;

#pragma region cls::CAtt{}

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

_pc_sz   CAtt::Name (void) const { return (_pc_sz)this->m_name; }
bool     CAtt::Name (_pc_sz _p_name) {
	_p_name;
	if (nullptr == _p_name)
		return false;
	CString cs_name(_p_name); cs_name.Trim();

	const bool b_changed = (cs_name.IsEmpty() == false && true == !!this->m_name.CompareNoCase(cs_name));
	if (b_changed)
		this->m_name = cs_name;

	return b_changed;
}

CAtt& CAtt::operator = (const CAtt& _src) { *this >> _src.Key() << _src.Value() << _src.Name(); return *this; }
CAtt& CAtt::operator = (CAtt&& _victim) { *this = const_cast<CAtt&>(_victim);  return *this; }

CAtt& CAtt::operator <<(const uint32_t _u_value) { this->Value(_u_value); return *this; }
CAtt& CAtt::operator >>(const uint32_t _u_key) { this->Key(_u_key); return *this; }

CAtt& CAtt::operator <<(_pc_sz _p_name) { this->Name(_p_name); return *this; }

#pragma endregion
#pragma region To_str()
CString CAccel::To_str (const e_tokens _e_value) {
	_e_value;
	switch (_e_value) {
	case CAccel::e_tokens::e_full : return CString(_T("__wgl_accel_full_arb")); break;
	case CAccel::e_tokens::e_none : return CString(_T("__wgl_accel_none_arb")); break;
	case CAccel::e_tokens::e_norm : return CString(_T("__wgl_accel_generic_arb")); break;
	case CAccel::e_tokens::e_supp : return CString(_T("__wgl_accel_support_arb")); break;	
	}
	return CString(_T("#undef"));
}

CString CBuffer::To_str (const e_tokens _e_value) {
	_e_value;
	switch (_e_value) {
	case CBuffer::e_tokens::e_double : return CString(_T("__wgl_buffer_double_arb")); break;
	case CBuffer::e_tokens::e_stereo : return CString(_T("__wgl_buffer_stereo_arb")); break;
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

CString CContext::To_str (const e_tokens _e_value) {
	_e_value;
	switch (_e_value) {
	case CContext::e_tokens::e_flags   : return CString(_T("__wgl_ctx_flags_arb")); break;
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

CString CSupport::To_str (const CSupport::e_tokens _e_value) {
	_e_value;
	switch (_e_value) {
	case CSupport::e_tokens::e_gdi    : return CString(_T("__wgl_support_gdi_arb")); break;
	case CSupport::e_tokens::e_opengl : return CString(_T("__wgl_support_opengl_arb")); break;
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

#pragma endregion
#pragma region cls::CAtt_set_base{}

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

CString  CAtt_set_base::Print (const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s] >> {%s%s%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s] >> {%s%s%s}");
	static _pc_sz pc_sz_pat_r = _T("{%s%s%s}");

	CString cs_atts;
	if (m_atts.empty() == true) {
		cs_atts = TString().Format(_T("%s#empty"), _p_pfx);
	}
	else {
		for (uint32_t i_ = 0; i_ < this->m_atts.size(); i_++) {
			const CAtt& att = this->m_atts.at(i_);
			cs_atts += _p_pfx;
			cs_atts += att.Print(e_print::e_req);
			if (i_ < this->m_atts.size() - 1)
			cs_atts += _p_sfx;
		}
	}

	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, _p_sfx, (_pc_sz)cs_atts, _p_sfx); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, _p_sfx, (_pc_sz)cs_atts, _p_sfx); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, _p_sfx, (_pc_sz)cs_atts, _p_sfx); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%d);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}

CAtt_set_base& CAtt_set_base::operator += (const CAtt& _att) { this->Append(_att); return *this; }

#pragma endregion
#pragma region cls::CAtt_set*{}
CAtt_set_ctx:: CAtt_set_ctx (const uint32_t _u_major/* = 1*/, const uint32_t _u_minor/* = 1*/) : TBase() {

	err_code n_result = __s_ok;

	if (__is_okay(n_result)) n_result = TBase::Append(CAtt(arb::CContext::CVersion::e_major, _u_major, (_pc_sz) arb::CContext::CVersion::To_str(arb::CContext::CVersion::e_major)));
	if (__is_okay(n_result)) n_result = TBase::Append(CAtt(arb::CContext::CVersion::e_minor, _u_minor, (_pc_sz) arb::CContext::CVersion::To_str(arb::CContext::CVersion::e_minor)));
	if (__is_okay(n_result)) n_result = TBase::Append(
		CAtt(arb::CContext::CProfile::e_mask, arb::CContext::CProfile::e_core, (_pc_sz) arb::CContext::CProfile::To_str(arb::CContext::CProfile::e_mask)));
	if (__is_okay(n_result)) n_result = TBase::Append(CAtt(arb::CContext::e_flags, 0, (_pc_sz) arb::CContext::To_str(arb::CContext::e_flags)));
}

CAtt_set_pixels:: CAtt_set_pixels (void) : TBase() {

	err_code n_result = __s_ok;
	// -----------------------------------------------------+   att key   ---+---   att value   ---+---  att name ---+ ;
	if (__is_okay(n_result)) n_result = TBase::Append(CAtt(arb::CDraw::e_window   , _gl_true, (_pc_sz) arb::CDraw::To_str(arb::CDraw::e_window)));
	if (__is_okay(n_result)) n_result = TBase::Append(CAtt(arb::CSupport::e_opengl, _gl_true, (_pc_sz) arb::CSupport::To_str(arb::CSupport::e_opengl)));
//	if (__is_okay(n_result)) n_result = TBase::Append(CAtt(arb::CAccel::e_supp    , _gl_true, (_pc_sz) arb::CAccel::To_str(arb::CAccel::e_supp)));
	if (__is_okay(n_result)) n_result = TBase::Append(CAtt(arb::CBuffer::e_double , _gl_true, (_pc_sz) arb::CBuffer::To_str(arb::CBuffer::e_double)));
//	if (__is_okay(n_result)) n_result = TBase::Append(CAtt(arb::CSwap::e_exchange , arb::CSwap::e_copy, (_pc_sz) arb::CSwap::To_str(arb::CSwap::e_exchange)));
	if (__is_okay(n_result)) n_result = TBase::Append(CAtt(arb::CType::e_pixel    , arb::CType::e_rgba, (_pc_sz) arb::CType::To_str(arb::CType::e_pixel)));
//	if (__is_okay(n_result)) n_result = TBase::Append(CAtt(arb::CAccel::e_supp    , arb::CAccel::e_full, (_pc_sz) arb::CAccel::To_str(arb::CAccel::e_supp)));
//	if (__is_okay(n_result)) n_result = TBase::Append(CAtt(arb::CSwap::e_method   , arb::CSwap::e_copy, (_pc_sz) arb::CSwap::To_str(arb::CSwap::e_method)));
	if (__is_okay(n_result)) n_result = TBase::Append(CAtt(arb::CColor::e_alpha   ,  8, (_pc_sz) arb::CColor::To_str(arb::CColor::e_alpha)));
	if (__is_okay(n_result)) n_result = TBase::Append(CAtt(arb::CColor::e_color   , 32, (_pc_sz) arb::CColor::To_str(arb::CColor::e_color)));
	if (__is_okay(n_result)) n_result = TBase::Append(CAtt(arb::CColor::e_depth   , 24, (_pc_sz) arb::CColor::To_str(arb::CColor::e_depth)));
}
#pragma endregion
#pragma region struct::s_bits*{}

using s_bits = ex_ui::draw::open_gl::format::s_bits;
using s_bits_ex = ex_ui::draw::open_gl::format::s_bits_ex;

s_bits::s_bits (const uint16_t _u_clr, const uint16_t _u_depth, const uint16_t _u_stencil) : m_u_clr(_u_clr), m_u_depth(_u_depth), m_u_stencil(_u_stencil) {}
bool s_bits::Is_valid (void) const {
	return (8 == m_u_clr  || 16 == m_u_clr || 24 == m_u_clr || 32 == m_u_clr);
}

CString s_bits::To_str (const e_print e_opt) const {
	e_opt;
	static _pc_sz p_pat_all = _T("[%s] >> {clr=%u; depth=%u; stencil=%u}");
	static _pc_sz p_pat_req = _T("clr=%u; depth=%u; stencil=%u");

	CString cs_out;
	if (e_print::e_req == e_opt)
	     cs_out.Format(p_pat_req, m_u_clr, m_u_depth, m_u_stencil);
	else cs_out.Format(p_pat_all, (_pc_sz)__CLASS__, m_u_clr, m_u_depth, m_u_stencil);

	return  cs_out;
}

s_bits_ex::s_bits_ex (const uint16_t _u_clr, const uint16_t _u_depth, const uint16_t _u_stencil, const uint16_t _u_msaa) : s_bits(_u_clr, _u_depth, _u_stencil), m_u_msaa(_u_msaa) {}

bool s_bits_ex::Is_valid (void) const {
	return s_bits::Is_valid() &&
	       (1 == m_u_msaa || 2 == m_u_msaa || 4 == m_u_msaa || 8 == m_u_msaa || 16 == m_u_msaa);
}

CString s_bits_ex::To_str (const e_print e_opt) const {
	e_opt;
	static _pc_sz p_pat_all = _T("[%s] >> {%s; msaa=%u}");
	static _pc_sz p_pat_req = _T("{%s; msaa=%u}");

	CString cs_out;
	if (e_print::e_req == e_opt)
	     cs_out.Format(p_pat_req, (_pc_sz) s_bits::To_str(e_print::e_req), m_u_msaa);
	else cs_out.Format(p_pat_all, (_pc_sz)__CLASS__, (_pc_sz) s_bits::To_str(e_print::e_req), m_u_msaa);

	return  cs_out;
}

const
s_bits& s_bits_ex::operator ()(void) const { return (s_bits&)*this; }
s_bits& s_bits_ex::operator ()(void)       { return (s_bits&)*this; }

#pragma endregion
#pragma region cls::CFormat{}

namespace ex_ui { namespace draw { namespace _impl {

#define pfd_draw_to_bmp  PFD_DRAW_TO_BITMAP
#define pfd_draw_to_wnd  PFD_DRAW_TO_WINDOW
#define pfd_double_buffs PFD_DOUBLEBUFFER
#define pfd_gen_accel    PFD_GENERIC_ACCELERATED
#define pfd_gen_format   PFD_GENERIC_FORMAT
#define pfd_need_pallete PFD_NEED_PALETTE
#define pfd_need_sys_pal PFD_NEED_SYSTEM_PALETTE
#define pfd_stereo       PFD_STEREO
#define pfd_supp_gdi     PFD_SUPPORT_GDI
#define pfd_supp_open_gl PFD_SUPPORT_OPENGL
#define pfd_swap_buffers PFD_SWAP_LAYER_BUFFERS

	class CFmt_Helper {
	public:
		 CFmt_Helper (void) = default; CFmt_Helper (const CFmt_Helper&) = delete; CFmt_Helper (CFmt_Helper&&) = delete;
		~CFmt_Helper (void) = default;

		CString Flags_to_str (const dword dw_flags) {
			dw_flags;
			// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-pixelformatdescriptor ;
			CString cs_out;
			if (pfd_draw_to_bmp  & dw_flags) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("pfd_draw_to_bmp"); }
			if (pfd_draw_to_wnd  & dw_flags) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("pfd_draw_to_wnd"); }
			if (pfd_double_buffs & dw_flags) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("pfd_double_buffs"); }
			if (pfd_gen_accel    & dw_flags) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("pfd_gen_accel"); }
			if (pfd_gen_format   & dw_flags) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("pfd_gen_format"); }
			if (pfd_need_pallete & dw_flags) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("pfd_need_pallete"); }
			if (pfd_need_sys_pal & dw_flags) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("pfd_need_sys_pal"); }
			if (pfd_stereo       & dw_flags) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("pfd_stereo"); }
			if (pfd_supp_gdi     & dw_flags) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("pfd_supp_gdi"); }
			if (pfd_supp_open_gl & dw_flags) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("pfd_supp_open_gl"); }
			if (pfd_swap_buffers & dw_flags) { if (false == cs_out.IsEmpty()) cs_out += _T("|"); cs_out += _T("pfd_swap_buffers"); }

			if (cs_out.IsEmpty())
				cs_out = _T("#undef");

			return  cs_out;
		}

	private:
		CFmt_Helper& operator = (const CFmt_Helper&) = delete; CFmt_Helper& operator = (CFmt_Helper&&) = delete;
	};

}}} using namespace ex_ui::draw::_impl;

CFormat::CFormat (void) : m_hdc(0), m_desc{0}, m_found(0) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = _T("#__e_state: pixel format is not found yet"); }
CFormat::CFormat (const CFormat& _src) : CFormat() { *this = _src; }
const
px_fmt_desc_t& CFormat::Get (void) const { return this->m_desc; }

TError&  CFormat::Error (void) const { return this->m_error; }
err_code CFormat::Find  (const s_bits& _bits, uint32_t& _found_ndx) {
	_bits; _found_ndx = 0;
	this->m_error <<__METHOD__<<__s_ok;
	this->m_found = 0; // resets to 'not found' state;
	
	if (false == this->Is_valid())
		return this->Error();

	if (false == _bits.Is_valid()) {
		return this->m_error <<__e_inv_arg = TString().Format(_T("#e__inv_arg: input bits %s is invalid"), (_pc_sz) _bits.To_str());
	}

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-pixelformatdescriptor ;
	PIXELFORMATDESCRIPTOR pfd = {0};
	int32_t n_mode_ndx = 1; // in accordance with the documentation the index is 1-based;

	struct {
		uint32_t u_current;
		uint32_t u_the_best;
	} s_scores = {0};

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-describepixelformat ;
	for (n_mode_ndx; 0 < ::DescribePixelFormat(this->m_hdc, n_mode_ndx, sizeof(pfd), &pfd); n_mode_ndx++) {
		if (false) {}
		else if (0 == (PFD_SUPPORT_OPENGL & pfd.dwFlags)) continue;
		else if (0 == (PFD_DRAW_TO_WINDOW & pfd.dwFlags)) continue;
		else if (0 != (PFD_NEED_PALETTE   & pfd.dwFlags) || PFD_TYPE_RGBA != pfd.iPixelType) continue;
		else if (0 == (PFD_DOUBLEBUFFER   & pfd.dwFlags)) continue;

		s_scores.u_current = 0;

		if (_bits.m_u_clr <= pfd.cColorBits) s_scores.u_current++;
        if (_bits.m_u_clr == pfd.cColorBits) s_scores.u_current++;

		if (_bits.m_u_depth <= pfd.cDepthBits) s_scores.u_current++;
        if (_bits.m_u_depth == pfd.cDepthBits) s_scores.u_current++;

		if (_bits.m_u_stencil <= pfd.cStencilBits) s_scores.u_current++;
        if (_bits.m_u_stencil == pfd.cStencilBits) s_scores.u_current++;

		if (0 < pfd.cAlphaBits) s_scores.u_current++;

		if (s_scores.u_the_best < s_scores.u_current) {
			s_scores.u_the_best = s_scores.u_current;
			
			this->m_found = _found_ndx = n_mode_ndx;
		}
	}
	if (_found_ndx > 1)
		::DescribePixelFormat(this->m_hdc, _found_ndx, sizeof(pfd), &this->m_desc); // it is required, otherwise the descriptor data is not updated;
	else
		this->m_desc = pfd;

	return this->Error();
}

err_code CFormat::Find  (const s_bits_ex& _bits) {
	_bits;
	this->m_error <<__METHOD__<<__s_ok;

	uint32_t u_index = 0;

	if (__failed(this->Find(_bits(), u_index)))
		return this->Error();

	if (false == _bits.Is_valid()) {
		return this->m_error <<__e_inv_arg = TString().Format(_T("#e__inv_arg: input bits %s is invalid"), (_pc_sz) _bits.To_str());
	}

	px_fmt_desc_t px_fmt_desc = {0};

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-choosepixelformat ;
	if (false == !!::SetPixelFormat(this->m_hdc, u_index, &px_fmt_desc)) {
		return this->m_error.Last();
	}

	// (4.b) chooses the pixel format;
	CAtt_set_pixels pxl_atts; // no error check for this time yet;

	uint32_t n_count = 0;
	int32_t p_formats = 0;

	// https://registry.khronos.org/OpenGL/extensions/ARB/WGL_ARB_pixel_format.txt ; this file contains the function description;
	// https://www.khronos.org/opengl/wiki/Creating_an_OpenGL_Context_(WGL) ; << there is the example of how to use the function;

	const int32_t n_result = ::__get_ctx_procs().ChoosePxFormatArb(
		this->m_hdc, pxl_atts.IAtt_Get_Int_Ptr(), nullptr, 1, &p_formats, &n_count
	);

	bool b_can_go_ahead = false;

	if (0 == n_result) { // the failure has occurred: the format cannot be chosen for creating the context;
		if (__get_ctx_procs().Error()) { // checks for failure of loading the function pointer;
		//	__get_ctx_procs().Error().Show();
		}
		else { // otherwise checks the OpenGL error that has been thrown; to-do: expect to do not work, it requires a re-view of this code block;
			this->m_error.Last();
		//	this->m_error.Show();
		}
		__trace_err_ex_2(this->Error());
	}
	else if (nullptr != &p_formats && true == !!n_count) { b_can_go_ahead = true; }
	else { b_can_go_ahead = true; }

	if (false == b_can_go_ahead)
		return this->Error();

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-describepixelformat ;
	if (0 == ::DescribePixelFormat(this->m_hdc, p_formats, sizeof(px_fmt_desc_t), &px_fmt_desc)) { // it is required, otherwise the descriptor data is not updated;
		return this->m_error .Last();
	}
	return this->Error();
}

uint32_t CFormat::Index (void) const { return this->m_found; }
bool  CFormat::Is_found (void) const { return !!this->Index(); }
bool  CFormat::Is_valid (void) const {
	this->m_error <<__METHOD__<<__s_ok;

	if (false == context::CDevice::Is_DC(this->m_hdc))
		this->m_error <<__e_inv_arg = _T("#__e_inv_arg: target device context is invalid");

	return true != this->Error();
}

err_code CFormat::Set (void) {
	this->m_error <<__METHOD__<<__s_ok;

	if (false == this->Is_valid())
		return this->Error();

	if (false == Is_found())
		return this->m_error <<(err_code)TErrCodes::eExecute::eState = _T("#__e_state: pixel format descriptor is not found yet");

	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-setpixelformat ;
	if (false == !!::SetPixelFormat(this->m_hdc, this->Index(), &this->Get())) {
		return this->m_error.Last();
	}

	return this->Error();
}

CString  CFormat::To_str (const px_fmt_desc_t& _px_desc) {
	_px_desc;
	static _pc_sz p_fmt_desc_pat = _T("clr=%ub;depth=%ub;stencil=%ub;flags: %s");
	CString cs_out; cs_out.Format(p_fmt_desc_pat,
		_px_desc.cColorBits, _px_desc.cDepthBits, _px_desc.cStencilBits, (_pc_sz) CFmt_Helper().Flags_to_str(_px_desc.dwFlags)
	);
	return  cs_out;
}

CFormat& CFormat::operator = (const CFormat& _src) { *this << _src.m_hdc << _src.Get() << _src.Index(); this->m_error = _src.Error(); return *this; }
CFormat& CFormat::operator <<(const HDC& _hdc) { this->m_hdc = _hdc; return *this; }

CFormat& CFormat::operator <<(const px_fmt_desc_t& _px_desc) { this->m_desc = _px_desc; return *this; }
CFormat& CFormat::operator <<(const uint32_t _u_index) { this->m_found = _u_index; return *this; }

#pragma endregion