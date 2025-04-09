/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Apr-2025 at 12:04:59.319, UTC+4, Batumi;
	This is Ebo Pack DirectX factory wrapper base interface implementation file;
*/
#include "direct_x.factory.h"

using namespace ex_ui::draw::direct_x;

/////////////////////////////////////////////////////////////////////////////
namespace ex_ui { namespace draw { namespace direct_x { namespace _11 {
CFac_0:: CFac_0 (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }

/////////////////////////////////////////////////////////////////////////////

TError&  CFac_0::Error (void) const { return this->m_error; }
bool     CFac_0::Is_valid (void) const { return nullptr != this->Ptr(); }

const
TFac0Ptr& CFac_0::Ptr  (void) const { return this->m_p_fac; }
TFac0Ptr& CFac_0::Ptr  (void)       { return this->m_p_fac; }
}}}}
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
namespace ex_ui { namespace draw { namespace direct_x { namespace _12 {

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

	::std::vector<CAdapter> found;

	do {
		n_error = this->Ptr()->EnumAdapters1(n_index, &p_adapter); // p_adapter must be not created, otherwise com-error is thrown;
		if (__failed(n_error))
			break;
		// checks the adapter pointer for capability of creating a device; no device is actually created: the last arg is nullptr;
		n_error = ::D3D12CreateDevice(p_adapter, D3D_FEATURE_LEVEL_11_0, _uuidof(TAdapterPtr), nullptr);
		if (__succeeded(n_error)) {

			TAdapterInfo info_ = { 0 };
			this->m_error << p_adapter->GetDesc1(&info_);
			if (false == this->m_error) {
				_adapter.Ptr() = p_adapter.Detach();
				_adapter.Info() = info_;
				found.push_back(_adapter);
			//	continue;
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
#if (1)
err_code  CFac_4::Get  (CSwapChain& _swap) {
	this->m_error << __METHOD__ << __s_ok;

	if (_swap.Is_valid())
		return (this->m_error << (err_code)TErrCodes::eObject::eExists);

	if (false == this->Is_valid())
		return (this->m_error << __e_not_inited);
	// (1) the device must be checked first due to it can create the command queue;
	if (nullptr == this->m_p_device)
		return (this->m_error << (err_code)TErrCodes::eObject::eHandle) = _T("The device is not set;");

	if (nullptr == this->m_p_queue)
		return (this->m_error << (err_code)TErrCodes::eObject::eHandle) = _T("The queue is not set;");

	HWND h_target = _swap.Target();
	if (!h_target)
		return (this->m_error << (err_code)TErrCodes::eObject::eHandle) = _T("Invalid target window handle;");

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_2/nf-dxgi1_2-idxgifactory2-createswapchainforhwnd ;
	this->m_error << m_p_fac->CreateSwapChainForHwnd(
		this->m_p_device, h_target, &_swap.Desc().Raw(), nullptr, nullptr, &_swap.Ptr()
	);

	return this->Error();
}
#endif
#if defined (_DEBUG)
CString   CFac_4::Print(const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{valid=%s}");

	CString cs_valid = TStringEx().Bool(this->Is_valid());
	CString cs_out;
	if (e_print::e_all   == _e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_valid); }
	if (e_print::e_no_ns == _e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_valid); }
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_valid); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif
const
TFac4Ptr& CFac_4::Ptr  (void) const { return this->m_p_fac; }
TFac4Ptr& CFac_4::Ptr  (void)       { return this->m_p_fac; }

err_code  CFac_4::Set  (const CCmdQueue& _queue) {
	this->m_error << __METHOD__ << __s_ok;

	if (_queue.Is_valid() == false) {
		return (this->m_error = _queue.Error()) = _T("Input queue is invalid;");
	}

	return this->Error();
}

err_code  CFac_4::Set  (const CDevice& _device) {
	this->m_error << __METHOD__ << __s_ok;

	if (_device.Is_valid() == false) {
		return (this->m_error = _device.Error()) = _T("Input device is invalid;");
	}

	this->m_p_device = _device.Ptr();

	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////

CFac_4&  CFac_4::operator = (const CFac_4& _src) { *this << _src.Ptr(); return *this; }
CFac_4&  CFac_4::operator <<(const TFac4Ptr& _p_fac) { this->Ptr() = _p_fac; return *this; }

CFac_4&  CFac_4::operator <<(const CDevice& _device) { this->Set(_device); return *this; }

CFac_4&  CFac_4::operator >>(CAda_Warp& _adapter) { this->Get(_adapter); return *this; }

}}}}