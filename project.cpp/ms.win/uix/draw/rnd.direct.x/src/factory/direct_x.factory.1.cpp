/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Apr-2025 at 12:17:02.291, UTC+4, Batumi, Wednesday;
	This is Ebo Pack DirectX 11 factory wrapper base interface implementation file;
*/
#include "direct_x.factory.1.h"

using namespace ex_ui::draw::direct_x::_11;

/////////////////////////////////////////////////////////////////////////////

CFac_0:: CFac_0 (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }

/////////////////////////////////////////////////////////////////////////////

err_code CFac_0::Create(void) {
	this->m_error << __METHOD__ << __s_ok;

	if (this->Is_valid())
		return this->m_error << (err_code)TErrCodes::eObject::eExists;

	TFac0Ptr p_object;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-createdxgifactory ;
	this->m_error << ::CreateDXGIFactory(__uuidof(TFac0Ptr), (void**)&p_object);
	if (__succeeded(this->Error()))
		this->m_p_fac = p_object/*.Detach()*/;

	return this->Error();
}

TError&  CFac_0::Error (void) const { return this->m_error; }
bool     CFac_0::Is_valid (void) const { return nullptr != this->Ptr(); }

#if defined (_DEBUG)
CString  CFac_0::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{valid=%s}");

	CString cs_valid = TStringEx().Bool(this->Is_valid());
	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)cs_valid); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz)cs_valid); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz)cs_valid); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif

const
TFac0Ptr& CFac_0::Ptr  (void) const { return this->m_p_fac; }
err_code  CFac_0::Ptr  (const TFac0Ptr& _p_fac) {
	this->m_error << __METHOD__ << __s_ok;

	if (nullptr == _p_fac)
		return this->m_error << __e_pointer;

	if (this->Is_valid())
		return this->m_error << (err_code) TErrCodes::eObject::eExists;

	this->m_p_fac = _p_fac;

	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////

CFac_2:: CFac_2 (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }

/////////////////////////////////////////////////////////////////////////////

err_code CFac_2::Create(void) {
	this->m_error << __METHOD__ << __s_ok;

	if (this->Is_valid())
		return (this->m_error << (err_code)TErrCodes::eObject::eInited);

	// https://stackoverflow.com/questions/42354369/idxgifactory-versions ;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_3/nf-dxgi1_3-createdxgifactory2 ;

	this->m_error << ::CreateDXGIFactory2(0, __uuidof(TFac2Ptr), (void**)&this->m_p_fac);

	return this->Error();
}

TError&  CFac_2::Error (void) const { return this->m_error; }
bool     CFac_2::Is_valid (void) const { return nullptr != this->Ptr(); }

err_code CFac_2::Get (CSwapChain& _chain) {
	_chain;
	this->m_error << __METHOD__ << __s_ok;

	if (_chain.Is_valid())
		return (this->m_error << (err_code)TErrCodes::eObject::eExists);

	const CSwapDesc& desc_ = _chain.Desc();

	if (false == this->m_device.Is_valid())
	     return  this->m_error = this->m_device.Error();
	if (false == desc_.Is_valid())
	     return (this->m_error << (err_code)TErrCodes::eObject::eHandle) = _T("Swap chain desc is not valid;");

	TChainPtr p_chain;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-idxgifactory-createswapchain ;
	this->m_error << this->Ptr()->CreateSwapChain(
		this->m_device.Ptr(), (DXGI_SWAP_CHAIN_DESC*)&desc_.ref(), &p_chain
	);
	if (this->Is_valid())
		_chain.Ptr(p_chain/*.Detach()*/, true);

	return this->Error();
}

err_code  CFac_2::Get (CSwapChain_Ex& _chain) {
	_chain;
	this->m_error << __METHOD__ << __s_ok;

	if (_chain.Is_valid())
		return (this->m_error << (err_code)TErrCodes::eObject::eExists);

	if (false == this->m_device.Is_valid())
	      return this->m_error = this->m_device.Error();
	if (false == _chain.Desc().Is_valid())
	      return(this->m_error << (err_code)TErrCodes::eObject::eHandle) = _T("Swap chain desc is not valid;");

	const CSwapDesc_Ex& desc_ex = _chain.Desc();
	
	TChain_ExPtr p_chain;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_2/nf-dxgi1_2-idxgifactory2-createswapchainforhwnd ;
	this->m_error << this->Ptr()->CreateSwapChainForHwnd(
		this->m_device.Ptr(), desc_ex.Target(), (DXGI_SWAP_CHAIN_DESC1*)&desc_ex.Ref(), nullptr, nullptr, &p_chain
	);
	return this->Error();
}

#if defined (_DEBUG)
CString  CFac_2::Print(const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{valid=%s}");

	CString cs_valid = TStringEx().Bool(this->Is_valid());
	CString cs_out;
	if (e_print::e_all == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)cs_valid); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz)cs_valid); }
	if (e_print::e_req == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz)cs_valid); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif

const
TFac2Ptr& CFac_2::Ptr (void) const { return this->m_p_fac; }
err_code  CFac_2::Ptr (const TFac2Ptr& _p_fac) {
	this->m_error << __METHOD__ << __s_ok;

	if (this->Is_valid())
		return this->m_error << (err_code)TErrCodes::eObject::eExists;

	if (nullptr == _p_fac)
		return this->m_error << __e_pointer;
	else
		this->m_p_fac = _p_fac;

	return this->Error();
}

err_code  CFac_2::Set (const CDevice& _device) {
	_device;
	this->m_error << __METHOD__ << __s_ok;

	if (false == _device.Is_valid())
		return this->m_error = _device.Error();

	this->m_device = _device;

	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////

CFac_2&   CFac_2::operator <<(const CDevice& _device) { this->Set(_device); return *this; }