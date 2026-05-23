/*
	Created by Tech_dog (ebontrop@gmail.com) on 06-Sep-2025 at 12:56:20.572, UTC+4, Batumi, Saturday;
	This is Ebo Pack OpenGL tutorials' format wrapper interface implementation file; 
*/
#include "gl_px_format.h"
#include "gl_context.h"
#include "gl_procs_ctx.h"

using namespace win_api;
using namespace open_gl::context;
using namespace win_api::format;

#pragma region struct::s_bits*{}

using s_bits = win_api::format::s_bits;
using s_bits_ex = win_api::format::s_bits_ex;

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
#pragma region cls::CPxFormat{}

namespace win_api { namespace draw { namespace _impl {

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

}}} using namespace win_api::draw::_impl;

static _pc_sz p_err_format_not_found = _T("#__e_state: pixel format is not found yet");

CPxFormat::CPxFormat (void) : m_hdc(0), m_desc{0}, m_found(0) { this->m_error >>__CLASS__<<__METHOD__<<__e_not_inited = p_err_format_not_found; }
CPxFormat::CPxFormat (const CPxFormat& _src) : CPxFormat() { *this = _src; }

const
px_fmt_desc_t& CPxFormat::Get (void) const { return this->m_desc; }

TError&  CPxFormat::Error (void) const { return this->m_error; }
err_code CPxFormat::Find  (const s_bits& _bits, uint32_t& _found_ndx) {
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

err_code CPxFormat::Find  (const s_bits_ex& _bits) {
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
	// https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-describepixelformat ;
	if (0 == ::DescribePixelFormat(this->m_hdc, u_index, sizeof(px_fmt_desc_t), &px_fmt_desc)) { // it is required, otherwise the descriptor data is not updated;
		return this->m_error .Last();
	}
	return this->Error();
}

uint32_t CPxFormat::Index (void) const { return this->m_found; }
bool  CPxFormat::Is_found (void) const { return !!this->Index(); }
bool  CPxFormat::Is_valid (void) const {
	this->m_error <<__METHOD__<<__s_ok;

	if (false == open_gl::context::CDevice::Is_DC(this->m_hdc))
		this->m_error <<__e_inv_arg = _T("#__e_inv_arg: target device context is invalid");

	return true != this->Error();
}

err_code CPxFormat::Set (void) {
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

CString  CPxFormat::To_str (const px_fmt_desc_t& _px_desc) {
	_px_desc;
	static _pc_sz p_fmt_desc_pat = _T("clr=%ub;depth=%ub;stencil=%ub;flags: %s");
	CString cs_out; cs_out.Format(p_fmt_desc_pat,
		_px_desc.cColorBits, _px_desc.cDepthBits, _px_desc.cStencilBits, (_pc_sz) CFmt_Helper().Flags_to_str(_px_desc.dwFlags)
	);
	return  cs_out;
}

CPxFormat& CPxFormat::operator = (const CPxFormat& _src) { *this << _src.m_hdc << _src.Get() << _src.Index(); this->m_error = _src.Error(); return *this; }
CPxFormat& CPxFormat::operator <<(const HDC& _hdc) { this->m_hdc = _hdc; return *this; }

CPxFormat& CPxFormat::operator <<(const px_fmt_desc_t& _px_desc) { this->m_desc = _px_desc; return *this; }
CPxFormat& CPxFormat::operator <<(const uint32_t _u_index) { this->m_found = _u_index; return *this; }

#pragma endregion