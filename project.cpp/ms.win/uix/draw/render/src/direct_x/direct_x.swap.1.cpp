/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Apr-2025 at 17:02:04.006, UTC+4, Batumi, Wednesday;
	This is Ebo Pack DirectX 11 swap chain wrapper interface implementation file;
*/
#include "direct_x.swap.1.h"
#include "direct_x.target.h"

using namespace ex_ui::draw::direct_x::_11;

/////////////////////////////////////////////////////////////////////////////

CDesc_Wrap:: CDesc_Wrap (void) : m_desc{0} { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }

/////////////////////////////////////////////////////////////////////////////

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

TError& CDesc_Wrap::Error (void) const { return this->m_error; }

bool    CDesc_Wrap::Is_valid (void) const {
	this->m_error << __METHOD__ << __s_ok;
	bool b_result = false;
	// the swap description structure must have the valid handle to target/output window;
	if (nullptr == this->ref().OutputWindow || !::IsWindow(this->ref().OutputWindow))
		this->m_error << (err_code)TErrCodes::eData::eInvalid = _T("Output window handle is not valid;");
	else
		b_result = true;
	return (b_result);
}

const
TSwapDesc&  CDesc_Wrap::ref (void) const { return this->m_desc; }
TSwapDesc&  CDesc_Wrap::ref (void) { return this->m_desc; }

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
	else
		this->m_p_chain = _p_chain;

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

/////////////////////////////////////////////////////////////////////////////

CSwapChain&  CSwapChain::operator <<(const TChainPtr& _p_chain) { this->Ptr(_p_chain); return *this; }