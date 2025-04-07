/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Apr-2025 at 12:04:59.319, UTC+4, Batumi;
	This is Ebo Pack DirectX factory wrapper base interface implementation file;
*/
#include "direct_x.factory.h"

using namespace ex_ui::draw::direct_x;

/////////////////////////////////////////////////////////////////////////////

CFac_4:: CFac_4 (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CFac_4:: CFac_4 (const CFac_4& _src) : CFac_4() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////

err_code CFac_4::Create(void) {
	this->m_error << __METHOD__ << __s_ok;

	if (this->Is_valid())
		return (this->m_error << (err_code) TErrCodes::eObject::eInited);

	// https://stackoverflow.com/questions/42354369/idxgifactory-versions ;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_3/nf-dxgi1_3-createdxgifactory2 ;

	this->m_error << ::CreateDXGIFactory2(0, __uuidof(IDXGIFactory4), (void**)&this->m_p_fac);

	return this->Error();
}
TError&  CFac_4::Error (void) const { return this->m_error; }
bool     CFac_4::Is_valid (void) const { return nullptr != this->Ptr(); }

err_code  CFac_4::Get  (CAdapter& _adapter) {
	this->m_error << __METHOD__ << __s_ok;

	if (_adapter.Is())
		return (this->m_error << (err_code)TErrCodes::eObject::eExists);

	if (false == this->Is_valid())
		return (this->m_error << __e_not_inited);
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d12/nf-d3d12-d3d12createdevice ;
	TAdapterPtr p_adapter;
	uint32_t n_index = 0;
	err_code n_error = __s_ok;
	do {
		n_error = this->Ptr()->EnumAdapters1(n_index, &p_adapter);
		if (__failed(n_error))
			break;
		// checks the adapter pointer for capability of creating a device; no device is actually created: the last arg is nullptr;
		n_error = ::D3D12CreateDevice(p_adapter, D3D_FEATURE_LEVEL_11_0, _uuidof(TAdapterPtr), nullptr);
		if (__succeeded(n_error)) {

			TAdapterInfo info_ = { 0 };
			this->m_error << p_adapter->GetDesc1(&info_);
			if (false == this->m_error) {
				_adapter.Ptr() = p_adapter;
				_adapter.Info() = info_;
				break;
			}
		}
		n_index += 1; // goes ahead;
	} while (__succeeded(n_error));

	return this->Error();
}

err_code  CFac_4::Get  (CAda_Warp& _adapter) {
	this->m_error << __METHOD__ << __s_ok;

	if (_adapter.Is())
		return (this->m_error << (err_code)TErrCodes::eObject::eExists);

	if (false == this->Is_valid())
		return (this->m_error << __e_not_inited);

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgiadapter ;
	TWarpAdaPtr warp_ada;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_4/nf-dxgi1_4-idxgifactory4-enumwarpadapter ;
	this->m_error << this->Ptr()->EnumWarpAdapter(__uuidof(IDXGIAdapter), (void**)&warp_ada);
	if (true == this->Error()) {
		return  this->Error();
	}
	else
		_adapter.Ptr() = warp_ada;

	TAdaInfoWarp warp_info = { 0 };

	this->m_error << warp_ada->GetDesc(&warp_info);
	if (true == this->Error()) {
		return  this->Error();
	}
	else
		_adapter.Info() = warp_info;

	return this->Error();
}
#if (0)
err_code  CFac_4::Get  (CSwapChain& _swap) {
	this->m_error << __METHOD__ << __s_ok;

	if (_swap.Is_valid())
		return (this->m_error << (err_code)TErrCodes::eObject::eExists);

	if (false == this->Is_valid())
		return (this->m_error << __e_not_inited);

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_2/nf-dxgi1_2-idxgifactory2-createswapchainforhwnd ;

	return this->Error();
}
#endif
const
TFac4Ptr& CFac_4::Ptr  (void) const { return this->m_p_fac; }
TFac4Ptr& CFac_4::Ptr  (void)       { return this->m_p_fac; }

/////////////////////////////////////////////////////////////////////////////

CFac_4&  CFac_4::operator = (const CFac_4& _src) { *this << _src.Ptr(); return *this; }
CFac_4&  CFac_4::operator <<(const TFac4Ptr& _p_fac) { this->Ptr() = _p_fac; return *this; }

CFac_4&  CFac_4::operator >>(CAda_Warp& _adapter) { this->Get(_adapter); return *this; }

/////////////////////////////////////////////////////////////////////////////