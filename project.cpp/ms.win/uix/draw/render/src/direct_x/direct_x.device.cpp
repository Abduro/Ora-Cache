/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Apr-2025 at 16:31:42.013, UTC+4, Batumi, Thursday;
	This is Ebo Pack DirectX device base wrapper interface implementation file;
*/
#include "direct_x.device.h"

using namespace ex_ui::draw::direct_x;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace direct_x { namespace _11 {

/////////////////////////////////////////////////////////////////////////////

CContext:: CContext (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }

/////////////////////////////////////////////////////////////////////////////

TError&    CContext::Error (void) const { return this->m_error; }
bool       CContext::Is_valid (void) const { return (nullptr != this->Ptr()); }
#if defined(_DEBUG)
CString    CContext::Print (const e_print _e_opt) const {
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
const
TCtx4Ptr&  CContext::Ptr (void) const { return this->m_p_ctx; }
TCtx4Ptr&  CContext::Ptr (void)       { return this->m_p_ctx; }

err_code   CContext::Set (const TCtx0Ptr& _p_base) {
	this->m_error << __METHOD__ << __s_ok;

	if (nullptr == _p_base)
		return (this->m_error << __e_pointer);

	if (this->Is_valid())
		return (this->m_error << (err_code)TErrCodes::eObject::eInited);

	this->m_error << _p_base->QueryInterface(&this->Ptr());

	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace direct_x { namespace _impl {

	class CDev_Cfg {
	public:
		typedef CFeature_Lvl::CDefault TLevels;
		typedef EFeatureLvl* TArrayPtr;
	public:
		class CLevels {
		public:
			 CLevels (void) = default; CLevels (const CLevels&) = delete; CLevels (CLevels&&) = delete;
			~CLevels (void) = default;

		public:
			uint32_t  Count (void) const { return CFeature_Lvl().Default().Count(); }
			TArrayPtr const Ptr (void) const { return CFeature_Lvl().Default().Levels(); }

		private:
			CLevels& operator = (const CLevels&) = delete;
			CLevels& operator = (CLevels&&) = delete;
		};
	public:
		 CDev_Cfg (void) = default; CDev_Cfg (const CDev_Cfg&) = delete;  CDev_Cfg (CDev_Cfg&&) = delete;
		~CDev_Cfg (void) = default;

	public:
		const
		CLevels&  Levels (void) const { return this->m_def_set; }
		uint32_t  Version (void) const { return D3D11_SDK_VERSION; }

	private:
		CLevels m_def_set;

	private:
		CDev_Cfg&  operator = (const CDev_Cfg&) = delete;
		CDev_Cfg&  operator = (CDev_Cfg&&) = delete;
	};

}}}}
using namespace ex_ui::draw::direct_x::_impl;
/////////////////////////////////////////////////////////////////////////////

CDevice:: CDevice (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CDevice::~CDevice (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code  CDevice::Get (CContext& _ctx) {
	this->m_error << __METHOD__ << __s_ok;

	if (_ctx.Is_valid())
		return (this->m_error << __e_invalid_arg) = _T("Input context is valid;");

	if (false == this->Is_valid())
		return (this->m_error << __e_not_inited);

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11device-getimmediatecontext ;
	TCtx0Ptr p_ctx;

	this->Ptr()->GetImmediateContext(&p_ctx);
	if (p_ctx) {
		_ctx.Set(p_ctx);
	}

	return this->Error();
}

err_code  CDevice::Get (CFeature& _feature) {
	this->m_error << __METHOD__ << __s_ok;

	if (false == _feature.Is_valid())
		return (this->m_error << __e_invalid_arg) = _T("Input feature is valid;");

	if (false == this->Is_valid())
		return (this->m_error << __e_not_inited);
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11device-checkfeaturesupport ;
	this->m_error << this->Ptr()->CheckFeatureSupport(
		_feature.Type(), _feature.Data(), _feature.Size()
	);

	return this->Error();
}

err_code  CDevice::Get (CAda_Warp& _adapter) {
	_adapter;
	this->m_error << __METHOD__ << __s_ok;

	if (false == this->Is_valid())
		return (this->m_error << __e_not_inited);

	::ATL::CComPtr<IDXGIDevice3> p_device_3;

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_3/nn-dxgi1_3-idxgidevice3 ;
	this->m_error << this->Ptr()->QueryInterface(__uuidof(IDXGIDevice3), (void**)&p_device_3);
	if (this->Error())
		return this->Error();

	TWarpPtr p_warp;

	this->m_error << p_device_3->GetAdapter(&p_warp);
	if (false == this->Error())
		_adapter.Ptr(p_warp);

	return this->Error();
}

TError&   CDevice::Error (void) const { return this->m_error; }
bool   CDevice::Is_valid (void) const { return (nullptr != this->Ptr()); }

const
TDevicePtr& CDevice::Ptr (void) const { return this->m_object; }
TDevicePtr& CDevice::Ptr (void)       { return this->m_object; }

/////////////////////////////////////////////////////////////////////////////

CDevice_HW::CDevice_HW (void) : TBase(), m_level(EFeatureLvl::D3D_FEATURE_LEVEL_1_0_CORE){}

/////////////////////////////////////////////////////////////////////////////

const
CContext& CDevice_HW::Ctx (void) const { return this->m_imm_ctx; }
CContext& CDevice_HW::Ctx (void)       { return this->m_imm_ctx; }

err_code  CDevice_HW::Create (void) {
	TBase::m_error << __METHOD__ << __s_ok;

	if (TBase::Is_valid())
		return (TBase::m_error << (err_code)TErrCodes::eObject::eExists);

	if (this->Ctx().Is_valid())
		return (TBase::m_error << (err_code)TErrCodes::eObject::eExists) = _T("Context object is already created;");

	CDev_Cfg cfg;
	TCtx0Ptr p_base_ctx;

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-d3d11createdevice ;

	TBase::m_error << ::D3D11CreateDevice(
		nullptr, (D3D_DRIVER_TYPE)CDrv_Type::e_ref,
		nullptr, CDev_Flag::e_single, cfg.Levels().Ptr(), cfg.Levels().Count(), cfg.Version(), &TBase::Ptr(), &this->m_level, &p_base_ctx
	);
	// D3D11_SDK_VERSION      - must be applied;
	// D3D_FEATURE_LEVEL_11_0 - may be applied for reference driver type;
	// D3D_FEATURE_LEVEL_11_1 - may be applied for reference driver type;
	if (false == TBase::Error()) {
		this->Ctx().Set(p_base_ctx);
		if (false == this->Ctx().Is_valid())
			TBase::m_error = this->Ctx().Error();
	}
	return TBase::Error();
}
err_code  CDevice_HW::Create_Swap (void) {
	TBase::m_error << __METHOD__ << __s_ok;

	if (TBase::Is_valid())
		return (TBase::m_error << (err_code)TErrCodes::eObject::eExists) = _T("The device is already created;");

	if (this->Ctx().Is_valid())
		return (TBase::m_error << (err_code)TErrCodes::eObject::eExists) = _T("Context object is already created;");

	if (this->Swap().Is_valid())
		return (TBase::m_error << (err_code)TErrCodes::eObject::eExists) = _T("Swap chain object is already created;");

	if (false == this->Swap().Desc().Is_valid())
		return (TBase::m_error = this->Swap().Desc().Error());

	CDev_Cfg   cfg;
	TCtx0Ptr   p_base_ctx;
	TChainPtr  p_swap;

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-d3d11createdeviceandswapchain ;

	TBase::m_error << ::D3D11CreateDeviceAndSwapChain(
		nullptr, (D3D_DRIVER_TYPE)CDrv_Type::e_hard,
		nullptr, CDev_Flag::e_single, cfg.Levels().Ptr(), cfg.Levels().Count(), cfg.Version(),
		nullptr, &p_swap, &TBase::Ptr(), &this->m_level, &p_base_ctx
	);
	if (false == TBase::Error()) {
	}
	return TBase::Error();
}
uint32_t  CDevice_HW::Level (void) const { return this->m_level; }
#if defined (_DEBUG)
CString   CDevice_HW::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{level=%s;context=%s;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{level=%s;context=%s;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{level=%s;context=%s;valid=%s}");

	CString cs_ctx   = this->Ctx().Print(e_print::e_req);
	CString cs_level = CFeature_Lvl().Print(this->Level());
	CString cs_valid = TStringEx().Bool(TBase::Is_valid());

	CString cs_out;
	if (e_print::e_all == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)cs_level, (_pc_sz)cs_ctx, (_pc_sz)cs_valid);
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz)cs_level, (_pc_sz)cs_ctx, (_pc_sz)cs_valid);
	}
	if (e_print::e_req == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz)cs_level, (_pc_sz)cs_ctx, (_pc_sz)cs_valid); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif

const
CSwapChain& CDevice_HW::Swap (void) const { return this->m_chain; }
CSwapChain& CDevice_HW::Swap (void)       { return this->m_chain; }

}}}}

namespace ex_ui { namespace draw { namespace direct_x { namespace _12 {

CDevice:: CDevice (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CDevice::~CDevice (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code  CDevice::Get (CCmdQueue& _queue) {
	this->m_error << __METHOD__ << __s_ok;

	if (_queue.Is_valid())
		return (this->m_error << (err_code)TErrCodes::eObject::eExists);

	if (false == this->Is_valid())
		return (this->m_error << __e_not_inited);

	this->m_error << this->m_object->CreateCommandQueue(&_queue.Desc(), __uuidof(TCmdQuePtr), (void**)&_queue.Ptr());

	return this->Error();
}

TError&   CDevice::Error (void) const { return this->m_error; }
bool   CDevice::Is_valid (void) const { return (nullptr != this->Ptr()); }

const
TDevicePtr& CDevice::Ptr (void) const { return this->m_object; }
TDevicePtr& CDevice::Ptr (void)       { return this->m_object; }

/////////////////////////////////////////////////////////////////////////////

CDevice_HW::CDevice_HW (void) : TBase() {}

/////////////////////////////////////////////////////////////////////////////

err_code  CDevice_HW::Create (const CAdapter& _adapter) {
	_adapter;
	TBase::m_error << __METHOD__ << __s_ok;

	if (false == _adapter.Is())
		return (TBase::m_error << __e_invalid_arg) = _T("Input adapter is not valid;");
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d12/nf-d3d12-d3d12createdevice ;
	TBase::m_error << ::D3D12CreateDevice(_adapter.Ptr(), D3D_FEATURE_LEVEL_11_0, _uuidof(TAdapterPtr), (void**)&TBase::Ptr());

	return TBase::Error();
}

/////////////////////////////////////////////////////////////////////////////

CDevice_Warp::CDevice_Warp (void) : TBase() {}

/////////////////////////////////////////////////////////////////////////////

err_code CDevice_Warp::Create (const CAda_Warp& _ada_warp) {
	_ada_warp;
	TBase::m_error << __METHOD__ << __s_ok;

	if (false == _ada_warp.Is())
		return (TBase::m_error << __e_invalid_arg) = _T("Warp adapter is not valid;");

	if (TBase::Is_valid())
		return (TBase::m_error << (err_code)TErrCodes::eObject::eInited);

	::ATL::CComPtr<ID3D12Device> p_device;

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d12/nf-d3d12-d3d12createdevice ;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3dcommon/ne-d3dcommon-d3d_feature_level ;
	TBase::m_error << ::D3D12CreateDevice(_ada_warp.Ptr(), D3D_FEATURE_LEVEL_1_0_CORE, __uuidof(TWarpAdaPtr), (void**)&p_device);
	if (false == TBase::Error())
		TBase::Ptr() = p_device;

	return TBase::Error();
}
}}}}