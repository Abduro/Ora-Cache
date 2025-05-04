/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Apr-2025 at 14:20:21.182, UTC+4, Batumi, Monday;
	This is Ebo Pack DirectX.11 draw renderer lib unit test interface implementation file;
*/
#include "ebo_test_$d$.render.1.h"

using namespace ebo::boo::test::draw::_11;

/////////////////////////////////////////////////////////////////////////////

CAdapter:: CAdapter (const bool _b_verb) : m_b_verb(_b_verb) {
	this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited;
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

/////////////////////////////////////////////////////////////////////////////

TError&  CAdapter::Error (void) const { return this->m_error; }
err_code CAdapter::Set (const TAdapter& _p_adapter) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}

	this->m_adapter.Ptr(_p_adapter.Ptr());
	if (this->m_adapter.Error()) {
		this->m_error = this->m_adapter.Error();
		_out() += this->m_adapter.Error().Print(TError::e_print::e_req);
	}
	else if (__failed(this->m_adapter.Outputs())) {
		this->m_error = this->m_adapter.Error();
		_out() += this->m_adapter.Error().Print(TError::e_print::e_req);
	}
	else {
		const TOutputs& outputs = ((const TAdapter&)this->m_adapter).Outputs();
		for (size_t i_ = 0; i_ < outputs.size(); i_+= 1) {
			const TOutput& output = outputs.at(i_);
			_out() += output.Print(e_print::e_all);
		}
	}

	_out()();
	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////

CAdapter_enum:: CAdapter_enum (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
	}
}

/////////////////////////////////////////////////////////////////////////////

void CAdapter_enum::Set (void) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}

	this->m_enum.Set();
	if (this->m_enum.Error()) {
		_out() += this->m_enum.Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}

	const TAdapters& adapters = this->m_enum.Cached();
	if (adapters.empty() == false) {
		for (size_t i_ = 0; i_ < adapters.size(); i_++) {
			const TAda_Warp& adapter = adapters.at(i_);  // this is not a reference to warp-adapter, but to generic adapter;
			_out() += adapter.Print();
		}
	}
	else
		_out() += _T("*result*: #no_adapters");

	_out()();
}

/////////////////////////////////////////////////////////////////////////////

namespace ebo { namespace boo { namespace test { namespace draw { namespace _impl {

	class CDevTest_Runner { // not is used yet;
	public:
		 CDevTest_Runner (void) { this->m_error >> __CLASS__ << __METHOD__ << __s_ok; }
		 CDevTest_Runner (const CDevTest_Runner&) = delete; CDevTest_Runner(CDevTest_Runner&&) = delete;
		~CDevTest_Runner (void) = default;

	public:
		TError& Error (void) const { return this->m_error; }

		err_code GetAdapter (const TDevice& _dev) {
			_dev;
			this->m_error << __METHOD__ << __s_ok;
			return this->Error();
		}

	private:
		CError  m_error;
	};

}}}}}
using namespace ebo::boo::test::draw::_impl;
/////////////////////////////////////////////////////////////////////////////

CDevice:: CDevice (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}
#if (0) // no automatic creation because it does not allow to test different methods of creating this device;
	if (false == this->m_device.Is_valid()) {
		this->m_device.Create();
		if (false == this->m_device.Is_valid()) {
			_out() += this->m_device.Error().Print(TError::e_print::e_req);
		}
		else
			_out() += this->m_device.Print(e_print::e_all);
	}
#endif
	_out()();
}
CDevice::~CDevice (void) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

/////////////////////////////////////////////////////////////////////////////

void CDevice::Create (void) {
	this->Create(TDrv_type::e_ref, true);
}

void CDevice::GetAdapter_ref (void) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}
#if (0)
	if (false == this->Ref().Is_valid()) {
		_out() += this->Ref().Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}
#else
	this->Create();
#endif
	TAda_Warp adapter;
	this->Ref().Get(adapter);

	if (this->Ref().Error()) {
		_out() += this->Ref().Error().Print(TError::e_print::e_req);
	}
	else if (__failed(adapter.UpdateInfo())) {
		_out() += adapter.Error().Print(TError::e_print::e_req);
	}
	else {
		_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) adapter.Print(e_print::e_all));
	}
	_out()();
}

void CDevice::GetContext_ref (void) {
#if (0)
	if (false == this->Ref().Is_valid()) {
		_out() += this->Ref().Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}
#else
	this->Create();
#endif

	TContext ctx;
	this->Ref().Get(ctx);
	if (this->Ref().Error())
		_out() += this->Ref().Error().Print(TError::e_print::e_req);
	else if (false == ctx.Is_valid())
		_out() += ctx.Error().Print(TError::e_print::e_req);
	else
		_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) ctx.Print());
	_out()();
}

void CDevice::GetFeature_ref (void) {
#if (0)
	if (false == this->Ref().Is_valid()) {
		_out() += this->Ref().Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}
#else
	this->Create();
#endif

	TFeature_Thread feature_0;
	this->Ref().Get(feature_0);

	if (this->Ref().Error())
		_out() += this->Ref().Error().Print(TError::e_print::e_req);
	else
		_out() += feature_0.Print();

	TFeature_Format feature_1; feature_1.Ref().InFormat = TClrBits::DXGI_FORMAT_B8G8R8A8_UNORM;
	this->Ref().Get(feature_1);

	if (this->m_device.Error())
		_out() += this->Ref().Error().Print(TError::e_print::e_req);
	else
		_out() += TStringEx().Format(_T("*result*:%s;"), (_pc_sz) feature_1.Print());

	_out()();
}

void CDevice::GetTexture_ref (void) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}
#if (0)
	if (false == this->Ref().Is_valid()) {
		_out() += this->Ref().Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}
#else
	this->Create();
#endif

	TTex_2D tex_2d; tex_2d.Desc().Fake();
	this->Ref().Get(tex_2d);

	if (this->Ref().Error())
		_out() += this->Ref().Error().Print(TError::e_print::e_req);
	else {
		const TDescRaw& raw_ = tex_2d.Desc().Raw();
		_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) tex_2d.Print(e_print::e_all));
		_out() += TStringEx().Format(_T("*result*:tex_desc>>{%s}"), (_pc_sz) TDesc_2D::Print(raw_));
	}
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

void CDevice::GetAdapter_no_swap (void) {

	this->Create(TDrv_type::e_ref, false);

	TAda_Warp adapter;

	this->Ref().Get(adapter);

	if (this->Ref().Error()) {
		_out() += this->Ref().Error().Print(TError::e_print::e_req);
	}
	else if (__failed(adapter.UpdateInfo())) {
		_out() += adapter.Error().Print(TError::e_print::e_req);
	}
	else {
		_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) adapter.Print(e_print::e_all));
	}
	_out()();

}
void CDevice::GetContext_no_swap (void) {

	this->Create(TDrv_type::e_ref, false);

	TContext ctx;
	this->Ref().Get(ctx);

	if (this->Ref().Error())
		_out() += this->Ref().Error().Print(TError::e_print::e_req);
	else if (false == ctx.Is_valid())
		_out() += ctx.Error().Print(TError::e_print::e_req);
	else
		_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) ctx.Print());
	_out()();
}
void CDevice::GetFeature_no_swap (void) {

	this->Create(TDrv_type::e_ref, false);

	TFeature_Thread feature_0;
	this->Ref().Get(feature_0);

	if (this->Ref().Error())
		_out() += this->Ref().Error().Print(TError::e_print::e_req);
	else
		_out() += feature_0.Print();

	TFeature_Format feature_1; feature_1.Ref().InFormat = TClrBits::DXGI_FORMAT_B8G8R8A8_UNORM;
	this->Ref().Get(feature_1);

	if (this->m_device.Error())
		_out() += this->Ref().Error().Print(TError::e_print::e_req);
	else
		_out() += TStringEx().Format(_T("*result*:%s;"), (_pc_sz) feature_1.Print());

	_out()();
}
void CDevice::GetTexture_no_swap (void) {

	this->Create(TDrv_type::e_ref, false);

	TTex_2D tex_2d; tex_2d.Desc().Fake();
	this->Ref().Get(tex_2d);

	if (this->Ref().Error())
		_out() += this->Ref().Error().Print(TError::e_print::e_req);
	else {
		const TDescRaw& raw_ = tex_2d.Desc().Raw();
		_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) tex_2d.Print(e_print::e_all));
		_out() += TStringEx().Format(_T("*result*:tex_desc>>{%s}"), (_pc_sz) TDesc_2D::Print(raw_));
	}
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

void CDevice::GetAdapter_hw (void) {

	this->Create(TDrv_type::e_hard, false);

	TAda_Warp adapter;

	this->Ref().Get(adapter);

	if (this->Ref().Error()) {
		_out() += this->Ref().Error().Print(TError::e_print::e_req);
	}
	else if (__failed(adapter.UpdateInfo())) {
		_out() += adapter.Error().Print(TError::e_print::e_req);
	}
	else {
		_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) adapter.Print(e_print::e_all));
	}
	_out()();
}

void CDevice::GetContext_hw (void) {

	this->Create(TDrv_type::e_hard, false);

	TContext ctx;
	this->Ref().Get(ctx);

	if (this->Ref().Error())
		_out() += this->Ref().Error().Print(TError::e_print::e_req);
	else if (false == ctx.Is_valid())
		_out() += ctx.Error().Print(TError::e_print::e_req);
	else
		_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) ctx.Print());
	_out()();
}

void CDevice::GetFeature_hw (void) {

	this->Create(TDrv_type::e_hard, false);

	TFeature_Thread feature_0;
	this->Ref().Get(feature_0);

	if (this->Ref().Error())
		_out() += this->Ref().Error().Print(TError::e_print::e_req);
	else
		_out() += feature_0.Print();

	TFeature_Format feature_1; feature_1.Ref().InFormat = TClrBits::DXGI_FORMAT_B8G8R8A8_UNORM;
	this->Ref().Get(feature_1);

	if (this->m_device.Error())
		_out() += this->Ref().Error().Print(TError::e_print::e_req);
	else
		_out() += TStringEx().Format(_T("*result*:%s;"), (_pc_sz) feature_1.Print());

	_out()();
}

void CDevice::GetTexture_hw (void) {

	this->Create(TDrv_type::e_hard, false);

	TTex_2D tex_2d; tex_2d.Desc().Fake();
	this->Ref().Get(tex_2d);

	if (this->Ref().Error())
		_out() += this->Ref().Error().Print(TError::e_print::e_req);
	else {
		const TDescRaw& raw_ = tex_2d.Desc().Raw();
		_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) tex_2d.Print(e_print::e_all));
		_out() += TStringEx().Format(_T("*result*:tex_desc>>{%s}"), (_pc_sz) TDesc_2D::Print(raw_));
	}
	_out()();
}

/////////////////////////////////////////////////////////////////////////////
const
TDevCfg& CDevice::Cfg (void) const { return this->Ref().Cfg(); }
TDevCfg& CDevice::Cfg (void)       { return this->Ref().Cfg(); }

err_code CDevice::Create (const TDrv_type _drv_type, const bool _b_swap) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}

	CFake_Wnd fk_wnd;
	this->Ref().Cfg().Default(fk_wnd);

	err_code n_result = this->Ref().Create(_drv_type, _b_swap);
	if (this->Ref().Error()) {
		_out() += this->Ref().Error().Print(TError::e_print::e_req);
	}
	else {
		_out() += TStringEx().Format(_T("*result*:%s;"), (_pc_sz)this->Ref().Print());
		_out() += TStringEx().Format(_T("*result*:%s;"), (_pc_sz)this->Ref().SwapChain().Desc().Print(e_print::e_all));
	}

	_out()();
	return n_result;
}

const
TDevice& CDevice::Ref (void) const { return this->m_device; }
TDevice& CDevice::Ref (void)       { return this->m_device; }

/////////////////////////////////////////////////////////////////////////////

void CDevice_HW::Create (void) {

	CFake_Wnd fk_wnd;
	this->Ref().Cfg().Default(fk_wnd);
	this->Ref().Create(true);

	if (this->Ref().Error())
		_out() += this->Ref().Error().Print(TError::e_print::e_req);
	else {
		_out() += this->Ref().Print(e_print::e_all);
		_out() += TStringEx().Format(_T("*result*:%s;"), (_pc_sz)this->Ref().SwapChain().Desc().Print(e_print::e_all));
	}
	_out()();
}

const
TDevice_HW& CDevice_HW::Ref (void) const { return this->m_dev_hw; }
TDevice_HW& CDevice_HW::Ref (void)       { return this->m_dev_hw; }

/////////////////////////////////////////////////////////////////////////////

void CDevice_Ref::Create (void) {
	
	CFake_Wnd fk_wnd;
	this->Ref().Cfg().Default(fk_wnd);
	this->Ref().Create(true);

	if (this->Ref().Error())
		_out() += this->Ref().Error().Print(TError::e_print::e_req);
	else {
		_out() += this->Ref().Print(e_print::e_all);
		_out() += TStringEx().Format(_T("*result*:%s;"), (_pc_sz)this->Ref().SwapChain().Desc().Print(e_print::e_all));
	}
	_out()();
}

const
TDevice_ref& CDevice_Ref::Ref (void) const { return this->m_dev_ref; }
TDevice_ref& CDevice_Ref::Ref (void)       { return this->m_dev_ref; }

/////////////////////////////////////////////////////////////////////////////

CDisplay:: CDisplay (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

void CDisplay::GetRez (void) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}

	this->m_display.Get();
	if (this->m_display.Error()) {
		_out() += this->m_display.Error().Print(TError::e_print::e_req);
	}
	else {
		_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_display.Print(e_print::e_all));
	}
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CFac_2:: CFac_2 (const bool _b_verb) : m_b_verb (_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

/////////////////////////////////////////////////////////////////////////////

void CFac_2::Create (void) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}
	this->m_fac_2.Create();
	// checking the error state is preferable, because it more reliable, especially, in case when factory object is created before;
	if (this->m_fac_2.Error())
		_out() += this->m_fac_2.Error().Print(TError::e_print::e_req);
	else
		_out() += TStringEx().Format(_T("*result*:%s)"), (_pc_sz)this->m_fac_2.Print(e_print::e_all));

	_out()();
}

void CFac_2::GetSwapChain (void) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}

	this->Create();
	if (this->m_fac_2.Error())
		return;

	// the device may be not able to create the swap chain, due to the device is created from the first adapter,
	// which possibly has no appropriate output, i.e. that is available for drawing operations;
	TDevice_HW device;
	device.Create();
	if (device.Error()) {
		_out() += this->m_fac_2.Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}

	CFake_Desc desc;
	if (desc.Error()) {
		_out() += desc.Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}

	TSwapChain chain; chain.Desc() = desc.Ref(); m_fac_2 << device;

	this->m_fac_2.Get(chain);
	if (this->m_fac_2.Error())
		_out() += this->m_fac_2.Error().Print(TError::e_print::e_req);
	else
		_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz)chain.Print(e_print::e_all));
	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CStencil:: CStencil (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

/////////////////////////////////////////////////////////////////////////////

void CStencil::Create (void) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}

	CFake_Wnd fk_wnd;
#if (0)
	TDevice_HW device;
#else
	TDevice_ref device;
#endif
	device.Cfg().Default(fk_wnd);
	device.Create(true);

	if (device.Error()) {
		_out() += device.Error().Print(TError::e_print::e_all);
		_out()();
		return;
	}
	this->m_stencil.Set(device);
	this->m_stencil.Create(true);

	if (this->m_stencil.Error())
		_out() += this->m_stencil.Error().Print(TError::e_print::e_all);
	else
		_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_stencil.Print(e_print::e_all));

	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CSwapChain:: CSwapChain (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb){
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

/////////////////////////////////////////////////////////////////////////////
#if (0)
void CSwapChain::Create(void) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}

	CDevice device;
	device.CreateWithSwap();
	if (device.Ref().Error()) {
		return;
	}

	this->m_swp_chain.Ptr(device.Ref().SwapChain().Ptr());
	if (this->m_swp_chain.Error()) {
		_out() += this->m_swp_chain.Print(e_print::e_all);
	}
	else {
		TZBuffer z_buffer;
		this->m_swp_chain.GetZBuffer(z_buffer);
		if (this->m_swp_chain.Error()) {
			_out() += this->m_swp_chain.Error().Print(TError::e_print::e_req);
		}
		else if (false == z_buffer.Is_valid()) {
			_out() += z_buffer.Error().Print(TError::e_print::e_req);
		}
		else {
			_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz)z_buffer.Print(e_print::e_all));
		}
	}

	_out()();
}
#endif
/////////////////////////////////////////////////////////////////////////////

CTarget:: CTarget (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
		_out()();
	}
}

/////////////////////////////////////////////////////////////////////////////

void CTarget::Create (void) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}

	CFake_Wnd fk_wnd;
	TDevice_HW device;
	device.Cfg().Default(fk_wnd);
	device.Create(true);

	if (device.Error()) {
		_out() += device.Error().Print(TError::e_print::e_all);
		_out()();
		return;
	}
	this->m_target << device;
#if (0)
	CFake_Desc desc;
	CFake_Swap swap;  // would be better to set name likes 'fake_chain';
	swap.Create();

	if (swap.Error()) {
		_out() += swap.Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}

	TSwapChain chain_;
	chain_.Desc().ref() = desc.Ref();
	chain_.Ptr (swap.Ref().Ptr());
#endif
	TTex_2D tex_2d;
#if (0)
	tex_2d.Desc().Fake();
	device.Get(tex_2d);
	if (device.Error()) {
		_out() += device.Error().Print(TError::e_print::e_all);
		_out()();
		return;
	}
#endif
	TSwapChain& swp_chain = device.SwapChain();
	swp_chain.GetZBuffer(tex_2d);
	if (swp_chain.Error()) {
		_out() += swp_chain.Error().Print(TError::e_print::e_all);
		_out()();
		return;
	}

	this->m_target.Set(tex_2d);
	this->m_target.Create();
	if (this->m_target.Error()) {
		_out() += this->m_target.Error().Print(TError::e_print::e_all);
	}
	else
		_out() += this->m_target.Print(e_print::e_all);

	_out()();
}

/////////////////////////////////////////////////////////////////////////////

CWarp_enum:: CWarp_enum (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}
}

/////////////////////////////////////////////////////////////////////////////

void CWarp_enum::Do (void) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}
#if (0) // enumerating all adapters is not required;
	this->m_enum.Set();
	if (this->m_enum.Error()) {
		_out() += this->m_enum.Error().Print(TError::e_print::e_req);
	}
#endif
	TAda_Warp adapter;
	this->m_enum.GetWarp(adapter);

	if (this->m_enum.Error()) {
		_out() += this->m_enum.Error().Print(TError::e_print::e_req);
	}
	else {
		_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) adapter.Print(e_print::e_all));
	}
	_out()();
}