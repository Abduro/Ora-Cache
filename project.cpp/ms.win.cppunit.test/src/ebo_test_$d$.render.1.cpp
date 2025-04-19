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

CDevice:: CDevice (const bool _b_verb) : m_b_verb(_b_verb) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}
	if (false == this->m_device.Is_valid()) {
		this->m_device.Create();
		if (false == this->m_device.Is_valid()) {
			_out() += this->m_device.Error().Print(TError::e_print::e_req);
		}
		else
			_out() += this->m_device.Print(e_print::e_all);
	}
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

void CDevice::GetAdapter (void) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}
	if (false == this->m_device.Is_valid()) {
		_out() += this->m_device.Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}
	TAda_Warp adapter;
	this->m_device.Get(adapter);
	if (this->m_device.Error()) {
		_out() += this->m_device.Error().Print(TError::e_print::e_req);
	}
	else if (__failed(adapter.UpdateInfo())) {
		_out() += adapter.Error().Print(TError::e_print::e_req);
	}
	else {
		_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) adapter.Print(e_print::e_all));
	}
	_out()();
}

void CDevice::GetContext() {
	if (false == this->m_device.Is_valid()) {
		_out() += this->m_device.Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}

	TContext ctx;
	this->m_device.Get(ctx);
	if (this->m_device.Error())
		_out() += this->m_device.Error().Print(TError::e_print::e_req);
	else if (false == ctx.Is_valid())
		_out() += ctx.Error().Print(TError::e_print::e_req);
	else
		_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) ctx.Print());
	_out()();
}

void CDevice::GetFeature(void) {
	if (false == this->m_device.Is_valid()) {
		_out() += this->m_device.Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}

	TFeature_Thread feature_0;
	this->m_device.Get(feature_0);

	if (this->m_device.Error())
		_out() += this->m_device.Error().Print(TError::e_print::e_req);
	else
		_out() += feature_0.Print();

	TFeature_Format feature_1; feature_1.Ref().InFormat = TClrBits::DXGI_FORMAT_B8G8R8A8_UNORM;
	this->m_device.Get(feature_1);

	if (this->m_device.Error())
		_out() += this->m_device.Error().Print(TError::e_print::e_req);
	else
		_out() += feature_1.Print();

	_out()();
}

void CDevice::GetSwapChain (void) {
	if (this->m_b_verb) {
		_out() += TLog_Acc::e_new_line;
		_out() += TStringEx().Format(_T("cls::[%s::%s].%s()"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__);
	}
	if (false == this->m_device.Is_valid()) {
		_out() += this->m_device.Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}
	// (1) target window must be created first;
	CFake_Wnd fake_wnd;
	this->m_device.SwapChain().Desc().Fake();
	this->m_device.SwapChain().Desc().ref().Flags |= D3D11_CREATE_DEVICE_SINGLETHREADED;
	this->m_device.SwapChain().Desc().Target(fake_wnd);
	// (2) the swap chain is created finally;
	this->m_device.SetSwapChain();
	if (this->m_device.Is_valid()) {
		_out() += this->m_device.Print();
		_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_device.SwapChain().Print(e_print::e_all));
	}
	else
		_out() += this->m_device.Error().Print(TError::e_print::e_req);

	_out()();
}

/////////////////////////////////////////////////////////////////////////////

void CDevice_Ref::Create (void) {
	CFake_Wnd fk_wnd;
	this->m_dev_ref.Default(fk_wnd);
	this->m_dev_ref.Create();
	if (this->m_dev_ref.Error())
		_out() += this->m_dev_ref.Error().Print(TError::e_print::e_req);
	else {
		_out() += TStringEx().Format(_T("*result*:%s;"), (_pc_sz)this->m_dev_ref.SwapChain().Desc().Print(e_print::e_all));
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
		_out() += this->m_fac_2.Print(e_print::e_all);
	else
		_out() += this->m_fac_2.Error().Print(TError::e_print::e_req);

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

	TSwapChain chain;

	this->m_fac_2.Get(device, desc.Ref(), chain);
	if (this->m_fac_2.Error())
		_out() += this->m_fac_2.Error().Print(TError::e_print::e_req);
	else
		_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz)chain.Print(e_print::e_all));
	_out()();
}

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

	TDevice_HW device;
	device.Create();

	if (device.Error()) {
		_out() += device.Error().Print(TError::e_print::e_req);
		_out()();
		return;
	}
	this->m_target << device;

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

	this->m_target.Set(chain_);

	this->m_target.Create();
	if (this->m_target.Error()) {
		_out() += this->m_target.Error().Print(TError::e_print::e_req);
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