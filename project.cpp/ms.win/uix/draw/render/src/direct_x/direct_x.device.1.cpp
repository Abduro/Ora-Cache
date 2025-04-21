/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Apr-2025 at 15:50:12.841, UTC+4, Batumi, Thursday;
	This is Ebo Pack DirectX 11 device base wrapper interface implementation file;
*/
#include "direct_x.device.1.h"

using namespace ex_ui::draw::direct_x::_11;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace direct_x { namespace _impl {
#if defined(_DEBUG)
	class CCfg_Fmt {
	public:
		 CCfg_Fmt (void) = default; CCfg_Fmt (const CCfg_Fmt&) = delete; CCfg_Fmt (CCfg_Fmt&&) = delete;
		~CCfg_Fmt (void) = default;

	public:
		CString Version(const uint32_t _n_ver) {
			_n_ver;
			CString cs_out;
			switch (_n_ver){
			case D3D11_SDK_VERSION: cs_out = _T("11"); break;
			default:
				cs_out.Format(_T("#undef:%d"), _n_ver);
			}
			return  cs_out;
		}

	private:
		CCfg_Fmt& operator = (const CCfg_Fmt&) = delete;
		CCfg_Fmt& operator = (CCfg_Fmt&&) = delete;
	};
#endif
}}}}
using namespace ex_ui::draw::direct_x::_impl;

/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
CString    CCtx_Type::Print (const uint32_t _n_type) {
	_n_type;
	CString cs_out;
	switch (_n_type) {
	case CCtx_Type::e_deferred : cs_out = _T("deferred"); break;
	case CCtx_Type::e_immediate: cs_out = _T("immediate"); break;
	default:
		cs_out.Format(_T("#inv_arg=%d"), _n_type);
	}
	return  cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

CContext:: CContext (void) : m_type((TCtxType)0) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }

/////////////////////////////////////////////////////////////////////////////

TError&    CContext::Error (void) const { return this->m_error; }
bool       CContext::Is_valid (void) const { return (nullptr != this->Ptr()); }
#if defined(_DEBUG)
CString    CContext::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{type=%s;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{type=%s;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{type=%s;valid=%s}");

	CString cs_type  = CCtx_Type::Print(this->Type());
	CString cs_valid = TStringEx().Bool(this->Is_valid());

	CString cs_out;
	if (e_print::e_all == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)cs_type, (_pc_sz)cs_valid);
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz)cs_type, (_pc_sz)cs_valid);
	}
	if (e_print::e_req == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz)cs_type, (_pc_sz)cs_valid); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif
const
TCtx4Ptr&  CContext::Ptr (void) const { return this->m_p_ctx; }
err_code   CContext::Ptr (const TCtx0Ptr& _p_base) {
	this->m_error << __METHOD__ << __s_ok;

	if (nullptr == _p_base)
		return (this->m_error << __e_pointer);

	if (this->Is_valid())
		return (this->m_error << (err_code)TErrCodes::eObject::eInited);

	TCtx4Ptr p_ptr_4;

	this->m_error << _p_base->QueryInterface(&p_ptr_4);
	if (false == this->Error()){
		this->m_p_ctx = p_ptr_4.Detach();
		this->m_type = _p_base->GetType(); // https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11devicecontext-gettype ;
	}

	return this->Error();
}

TCtxType   CContext::Type(void) const { return this->m_type; }

/////////////////////////////////////////////////////////////////////////////

using TLevels = CDev_Cfg::TLevels;
using TLevelsPtr = CDev_Cfg::TLevelsPtr;
using CLevels = CDev_Cfg::CLevels;

TLevelsPtr
const    CLevels::Ptr   (void) const { return CFeature_Lvl().Default().Levels(); }
uint32_t CLevels::Count (void) const { return CFeature_Lvl().Default().Count(); }

/////////////////////////////////////////////////////////////////////////////

CDev_Cfg:: CDev_Cfg (void) : m_desc{0} {}

err_code   CDev_Cfg::Default (const HWND hTarget) {
	hTarget;
	err_code n_result = __s_ok;
	if (nullptr == hTarget || false == !!::IsWindow(hTarget))
		return (n_result = __e_hwnd);

	// https://learn.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-devices-create-ref ;
	TSwapDesc& desc = this->m_desc;
	desc.BufferCount       =   1;
	desc.BufferDesc.Width  = 640;
	desc.BufferDesc.Height = 480;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hTarget;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;
	return n_result;
}

const
TSwapDesc& CDev_Cfg::Desc (void) const { return this->m_desc; }
TSwapDesc& CDev_Cfg::Desc (void)       { return this->m_desc; }

const
CLevels&  CDev_Cfg::Levels (void) const { return this->m_def_set; }
uint32_t  CDev_Cfg::Version(void) const { return D3D11_SDK_VERSION; }

#if defined(_DEBUG)
CString   CDev_Cfg::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{desc=%s;type=%s;ver=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{desc=%s;type=%s;ver=%s}");
	static _pc_sz pc_sz_pat_r = _T("{desc=%s;type=%s;ver=%s}");

	CString cs_desc = CDesc_Wrap::Print(this->Desc());
	CString cs_type = CDrv_Type::Print(this->Type());
	CString cs_ver  = CCfg_Fmt().Version(this->Version());

	CString cs_out;
	if (e_print::e_all == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)cs_desc, (_pc_sz)cs_type, (_pc_sz)cs_ver);
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz)cs_desc, (_pc_sz)cs_type, (_pc_sz)cs_ver);
	}
	if (e_print::e_req == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz)cs_desc, (_pc_sz)cs_type, (_pc_sz)cs_ver); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif

TDrvType  CDev_Cfg::Type (void) const { return this->m_type; }
bool      CDev_Cfg::Type (const TDrvType _n_type) {
	_n_type;
	const bool b_changed = this->Type() != _n_type;
	if (b_changed)
		this->m_type = _n_type;

	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////
#define Level_Core EFeatureLvl::D3D_FEATURE_LEVEL_1_0_CORE
#define Level_11_1 EFeatureLvl::D3D_FEATURE_LEVEL_11_1

CDevice:: CDevice (void) : m_level(Level_Core) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CDevice::~CDevice (void) {}

/////////////////////////////////////////////////////////////////////////////
const
CDev_Cfg& CDevice::Cfg (void) const { return this->m_cfg; }
CDev_Cfg& CDevice::Cfg (void)       { return this->m_cfg; }
const
CContext& CDevice::Ctx (void) const { return this->m_ctx; }
CContext& CDevice::Ctx (void)       { return this->m_ctx; }

err_code  CDevice::Create (const CDrv_Type::e_type _drv_type, const bool _b_swap) {
	_drv_type; _b_swap;
	this->m_error <<__METHOD__ << __s_ok;

	if (this->Is_valid())
		return this->m_error << (err_code)TErrCodes::eObject::eExists;

	CDev_Cfg&  cfg = this->Cfg(); this->Cfg().Type((TDrvType)_drv_type);
	TSwapDesc& desc = cfg.Desc();

	TCtx0Ptr   p_ctx;
	TChainPtr  p_chain;
	TDevicePtr p_base; 

	D3D_FEATURE_LEVEL n_level = Level_11_1;

	if (_b_swap) {
		this->m_error << ::D3D11CreateDeviceAndSwapChain(
			nullptr, (D3D_DRIVER_TYPE)_drv_type,
			nullptr, CDev_Flags::e_one, cfg.Levels().Ptr(), cfg.Levels().Count(), cfg.Version(), &desc, &p_chain, &p_base, &n_level, &p_ctx
		);
	}
	else {
		// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-d3d11createdevice ;

		this->m_error << ::D3D11CreateDevice(
			nullptr, (D3D_DRIVER_TYPE)_drv_type,
			nullptr, CDev_Flags::e_one, cfg.Levels().Ptr(), cfg.Levels().Count(), cfg.Version(), &p_base, &n_level, &p_ctx
		);
	}

	if (false == this->Error()) {
		if (nullptr != p_base)  this->Ptr(p_base.Detach());
		if (nullptr != p_chain) this->SwapChain().Ptr(p_chain.Detach());
		if (nullptr != p_ctx)   this->Ctx().Ptr(p_ctx.Detach());

		this->m_level = n_level;
	}

	return this->Error();
}

err_code  CDevice::Get (CAdapter& _adapter) {
	_adapter;
	this->m_error << __METHOD__ << __s_ok;

	if (false == this->Is_valid())
		return (this->m_error << __e_not_inited);
#if (0) // getting IDXGIDevice3 is not required;
	::ATL::CComPtr<IDXGIDevice3> p_device_3;

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_3/nn-dxgi1_3-idxgidevice3 ;
	this->m_error << this->Ptr()->QueryInterface(__uuidof(IDXGIDevice3), (void**)&p_device_3);
	if (this->Error())
		return this->Error();

	TWarpPtr p_warp;

	this->m_error << p_device_3->GetAdapter(&p_warp);
	if (false == this->Error())
		_adapter.Ptr(p_warp);
#else
	TDevBasePtr p_base;
	this->m_error << this->Ptr()->QueryInterface(__uuidof(TDevBasePtr), (void**)&p_base);
	if (this->Error())
		return this->Error();
	
	TAdapterPtr p_adapter;
	this->m_error << p_base->GetAdapter(&p_adapter);
	if (false == this->Error()) {
		_adapter.Ptr(p_adapter.Detach());
	}

#endif
	return this->Error();
}

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
		_ctx.Ptr(p_ctx.Detach());
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

err_code  CDevice::Get (CTex_2D& _tex) {
	this->m_error << __METHOD__ << __s_ok;

	if (_tex.Is_valid())
		return (this->m_error << __e_invalid_arg) = _T("Input texture is valid;");

	if (false == this->Is_valid())
		return (this->m_error << __e_not_inited);

	using TTexPtr = ex_ui::draw::direct_x::_11::_2D::TTexPtr;
	TTexPtr p_tex;

	this->m_error << this->Ptr()->CreateTexture2D(&_tex.Desc().Raw(), nullptr, &p_tex);
	if (this->Error() == false)
		this->m_error << _tex.Ptr(p_tex.Detach());

	return this->Error();
}

uint32_t  CDevice::Level (void) const { return this->m_level; }

TError&   CDevice::Error (void) const { return this->m_error; }
bool   CDevice::Is_valid (void) const { return (nullptr != this->Ptr()); }
#if defined(_DEBUG)
CString   CDevice::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{level=%s;ctx=%s;type=%s;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{level=%s;ctx=%s;type=%s;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{level=%s;ctx=%s;type=%s;valid=%s}");

	CString cs_ctx   = this->Ctx().Print(e_print::e_req);
	CString cs_level = CFeature_Lvl().Print(this->Level());
	CString cs_type  = CDrv_Type::Print(this->Cfg().Type());
	CString cs_valid = TStringEx().Bool(this->Is_valid());

	CString cs_out;
	if (e_print::e_all == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)cs_level, (_pc_sz)cs_ctx, (_pc_sz)cs_type, (_pc_sz)cs_valid);
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz)cs_level, (_pc_sz)cs_ctx, (_pc_sz)cs_type, (_pc_sz)cs_valid);
	}
	if (e_print::e_req == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz)cs_level, (_pc_sz)cs_ctx, (_pc_sz)cs_type, (_pc_sz)cs_valid); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif
const
TDevicePtr& CDevice::Ptr (void) const { return this->m_p_dev; }
err_code    CDevice::Ptr (const TDevicePtr& _p_dev) {
	_p_dev;
	if (this->Is_valid())
		return this->m_error << (err_code)TErrCodes::eObject::eExists;

	if (nullptr == _p_dev)
		return this->m_error << __e_pointer;

	this->m_p_dev = _p_dev;

	return this->Error();
}

const
CSwapChain& CDevice::SwapChain (void) const { return this->m_chain; }
CSwapChain& CDevice::SwapChain (void)       { return this->m_chain; }

/////////////////////////////////////////////////////////////////////////////

CDevice_HW::CDevice_HW (void) : TBase() {}

/////////////////////////////////////////////////////////////////////////////

err_code  CDevice_HW::Create (const bool _b_with_swap) {
	_b_with_swap;
	TBase::m_error << __METHOD__ << __s_ok;
	TBase::Cfg().Type((TDrvType)CDrv_Type::e_type::e_hard);
	TBase::Create(CDrv_Type::e_type::e_hard, _b_with_swap);

	return TBase::Error();
}

#if defined (_DEBUG)
CString   CDevice_HW::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{level=%s;context=%s;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{level=%s;context=%s;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{level=%s;context=%s;valid=%s}");

	CString cs_ctx   = this->Ctx().Print(e_print::e_req);
	CString cs_level = CFeature_Lvl().Print(TBase::Level());
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

/////////////////////////////////////////////////////////////////////////////

CDevice_Ref:: CDevice_Ref (void) : TBase() { TBase::m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }

/////////////////////////////////////////////////////////////////////////////

err_code CDevice_Ref::Create (const bool _b_with_swap) {
	TBase::m_error << __METHOD__ << __s_ok;
	TBase::Cfg().Type((TDrvType)CDrv_Type::e_type::e_ref);
	TBase::Create(CDrv_Type::e_type::e_ref, _b_with_swap);

	return TBase::Error();
}
#if defined(_DEBUG)

CString  CDevice_Ref::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{level=%s;context=%s;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{level=%s;context=%s;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{level=%s;context=%s;valid=%s}");

	CString cs_ctx   = this->Ctx().Print(e_print::e_req);
	CString cs_level = CFeature_Lvl().Print(TBase::Level());
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

/////////////////////////////////////////////////////////////////////////////