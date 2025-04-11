/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Apr-2025 at 17:02:04.006, UTC+4, Batumi, Wednesday;
	This is Ebo Pack DirectX 11 swap chain wrapper interface implementation file;
*/
#include "direct_x.swap.1.h"

using namespace ex_ui::draw::direct_x::_11;

/////////////////////////////////////////////////////////////////////////////

CDesc_Wrap:: CDesc_Wrap (void) : m_desc{0} { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }

/////////////////////////////////////////////////////////////////////////////

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

	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////

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
const
TChainPtr&   CSwapChain::Ptr (void) const { return this->m_p_chain; }
TChainPtr&   CSwapChain::Ptr (void)       { return this->m_p_chain; }

/////////////////////////////////////////////////////////////////////////////

CSwapChain&  CSwapChain::operator <<(const TChainPtr& _p_chain) { this->Ptr() = _p_chain; return *this; }