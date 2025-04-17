/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Apr-2025 at 17:02:04.006, UTC+4, Batumi, Wednesday;
	This is Ebo Pack DirectX 11 swap chain wrapper interface implementation file;
*/
#include "direct_x.swap.1.h"
#include "direct_x.target.h"

using namespace ex_ui::draw::direct_x::_11;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace direct_x { namespace _impl {
#if defined(_DEBUG)
	class CDesc_Fmt {
	public:
		 CDesc_Fmt (void) = default; CDesc_Fmt (const CDesc_Fmt&) = delete; CDesc_Fmt (CDesc_Fmt&&) = delete;
		~CDesc_Fmt (void) = default;

	public:
		// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ns-dxgi-dxgi_swap_chain_desc ;
		CString  Format(const TSwapDesc& _desc, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const {
			_desc; _p_pfx; _p_sfx;
			static _pc_sz pc_sz_pat = _T("%s;%s%seffect=%s;%s%ssample=%s;flags=%s;%s%s%s");

			CString cs_effect = CEffect::Print(_desc.SwapEffect);
			CString cs_flags  = CSwapFlags().Print(_desc.Flags );
			CString cs_sample = CSample::Print(_desc.SampleDesc);
			
			CString cs_out;
			        cs_out.Format( pc_sz_pat,
			      (_pc_sz)this->_buf_to_str(_desc), _p_sfx, _p_pfx,
			      (_pc_sz)cs_effect, _p_sfx, _p_pfx,
			      (_pc_sz)cs_sample, (_pc_sz)cs_flags, _p_sfx, _p_pfx,
			      (_pc_sz)this->_wnd_to_str(_desc)
			   );
			return  cs_out;
		}

	private:
		CString  _buf_to_str (const TSwapDesc& _desc) const {
			static _pc_sz pc_sz_pat = _T("buffer={count=%d;mode=%s;usage=%s}");
			CString cs_out;
			        cs_out.Format(pc_sz_pat, _desc.BufferCount,
			                    (_pc_sz)CDisplay().Print(_desc.BufferDesc),
			                    (_pc_sz)CBuff_Usage::Print(_desc.BufferUsage));
			return  cs_out;
		}
		CString  _wnd_to_str (const TSwapDesc& _desc) const {
			static _pc_sz pc_sz_pat = _T("target={hwnd=0x%p;windowed=%s}");
			CString cs_out;
			        cs_out.Format(pc_sz_pat, _desc.OutputWindow, TStringEx().Bool(_desc.Windowed));
			return  cs_out;
		}

	private:
		CDesc_Fmt& operator = (const CDesc_Fmt&) = delete;
		CDesc_Fmt& operator = (CDesc_Fmt&&) = delete;
	};
#endif
}}}}
using namespace ex_ui::draw::direct_x::_impl;
/////////////////////////////////////////////////////////////////////////////

CDesc_Wrap:: CDesc_Wrap (void) : m_desc{0} { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }

/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
void CDesc_Wrap::Fake (void) {

	// https://learn.microsoft.com/en-us/previous-versions/windows/desktop/legacy/bb173064(v=vs.85) ;
	this->ref().BufferDesc.Format = (DXGI_FORMAT)CClrBits::e_clr_bits::e_rgba_norm;
	this->ref().BufferDesc.Height = 100;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgicommon/ns-dxgicommon-dxgi_rational ;
	this->ref().BufferDesc.RefreshRate.Denominator = 0;
	this->ref().BufferDesc.RefreshRate.Numerator   = 0;
	// https://learn.microsoft.com/en-us/previous-versions/windows/desktop/legacy/bb173066(v=vs.85) ;
	this->ref().BufferDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_STRETCHED;
	// https://learn.microsoft.com/en-us/previous-versions/windows/desktop/legacy/bb173067(v=vs.85) ;
	this->ref().BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	this->ref().BufferDesc.Width = 100;
	this->ref().BufferCount = 2;         // required; if equals to 0 then leads to the exception: C0000005;
	this->ref().BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	this->ref().SampleDesc.Count = 1;    // required; otherwise 0 value leads to 'The parameter is incorrect.';
	this->ref().SampleDesc.Quality = 0;
	this->ref().Flags = DXGI_SWAP_CHAIN_FLAG::DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE; // this flag or zero works when CFac_2 creates the chain;
	this->ref().SwapEffect = TEffect::DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
}
#endif
TError& CDesc_Wrap::Error (void) const { return this->m_error; }

bool    CDesc_Wrap::Is_valid (void) const {
	this->m_error << __METHOD__ << __s_ok;	
	this->m_error << CDesc_Wrap::Is_valid(this->ref());

	return (false == this->Error());
}

const
TSwapDesc&  CDesc_Wrap::ref (void) const { return this->m_desc; }
TSwapDesc&  CDesc_Wrap::ref (void) { return this->m_desc; }

#if defined(_DEBUG)
CString     CDesc_Wrap::Print (const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{%s%s%s;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{%s;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{%s;valid=%s}");

	CString cs_desc  = CDesc_Fmt().Format(this->ref());
	CString cs_valid = TStringEx().Bool(this->Is_valid());

	CString cs_out;
	if (e_print::e_all == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, _p_sfx, _p_pfx, (_pc_sz)cs_desc, (_pc_sz)cs_valid);
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz)cs_desc, (_pc_sz)cs_valid);
	}
	if (e_print::e_req == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz)cs_desc, (_pc_sz)cs_valid); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif

err_code    CDesc_Wrap::Set (const TSwapDesc& _desc) {
	this->m_error << __METHOD__ << __s_ok;

	if (__failed(CDesc_Wrap::Is_valid(_desc)))
		return (this->m_error << __e_invalid_arg);

	this->m_desc = _desc;

	return this->Error();
}

HWND const  CDesc_Wrap::Target (void) const { return this->ref().OutputWindow; }
err_code    CDesc_Wrap::Target (HWND const _h_target) {
	this->m_error << __METHOD__ << __s_ok;

	if (nullptr == _h_target || !::IsWindow(_h_target))
		return (this->m_error << (err_code)TErrCodes::eObject::eHandle) = _T("Input target window handle is not valid;");

	this->ref().OutputWindow = _h_target;
	this->ref().Windowed = true; // sets this parameter to true; no fullscreen mode is necessary. especially in debug mode ;
	// DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH ;
	// https://stackoverflow.com/questions/45558600/d3d11createdeviceandswapchain-fails-with-s-false-on-different-computer ;
	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////

err_code   CDesc_Wrap::Is_valid (const TSwapDesc& _desc) {
	_desc;
	err_code n_result = __s_ok;
	// the swap description structure must have the valid handle to target/output window;
	if (nullptr == _desc.OutputWindow || !::IsWindow(_desc.OutputWindow))
		n_result = OLE_E_INVALIDHWND;

	return n_result;
}

/////////////////////////////////////////////////////////////////////////////

CDesc_Wrap& CDesc_Wrap::operator <<(HWND const _h_target) { this->Target(_h_target); return *this; }

CDesc_Wrap::operator const TSwapDesc& (void) const { return this->ref(); }
CDesc_Wrap::operator TSwapDesc& (void) { return this->ref(); }

/////////////////////////////////////////////////////////////////////////////

CSwapChain:: CSwapChain (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }

/////////////////////////////////////////////////////////////////////////////
const
CDesc_Wrap&  CSwapChain::Desc (void) const { return this->m_desc; }
CDesc_Wrap&  CSwapChain::Desc (void)       { return this->m_desc; }

TError&      CSwapChain::Error (void) const { return this->m_error; }
bool         CSwapChain::Is_valid (void) const { return (nullptr != this->Ptr()); }

bool CSwapChain::Is_full_screen (void) const {
	this->m_error << __METHOD__ << __s_ok;
	TOutputPtr p_out;

	BOOL b_full_screen = false;

	if (this->Is_valid()) {
		this->m_error << this->m_p_chain->GetFullscreenState(&b_full_screen, &p_out);
		if (this->Error() == false)
			return !!b_full_screen;
	}

	return !!b_full_screen;
}

const
TChainPtr&   CSwapChain::Ptr (void) const { return this->m_p_chain; }
err_code     CSwapChain::Ptr (const TChainPtr& _p_chain) {
	_p_chain;
	this->m_error << __METHOD__ << __s_ok;

	if (this->Is_valid())
		return this->m_error << (err_code)TErrCodes::eObject::eExists;

	if (nullptr == _p_chain)
		return this->m_error << __e_pointer;
	else {
		this->m_p_chain = _p_chain;
		this->UpdateDesc();
	}

	return this->Error();
}

#if defined (_DEBUG)
CString      CSwapChain::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{valid=%s}");

	CString cs_valid = TStringEx().Bool(this->Is_valid());

	CString cs_out;
	if (e_print::e_all == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)cs_valid);
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz)cs_valid);
	}
	if (e_print::e_req == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz)cs_valid); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif

err_code     CSwapChain::UpdateDesc (void) {
	this->m_error << __METHOD__ << __s_ok;

	if (false == this->Is_valid())
		return this->m_error << __e_not_inited;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-idxgiswapchain-getdesc ;
	TSwapDesc desc;
	this->m_error << this->Ptr()->GetDesc(&desc);
	if (false == this->Error())
		this->m_error << this->Desc().Set(desc);

	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////

CSwapChain&  CSwapChain::operator <<(const TChainPtr& _p_chain) { this->Ptr(_p_chain); return *this; }