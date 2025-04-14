/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Apr-2025 at 14:20:21.182, UTC+4, Batumi, Monday;
	This is Ebo Pack DirectX.11 draw renderer lib unit test interface implementation file;
*/
#include "ebo_test_$d$.render.1.h"

using namespace ebo::boo::test::draw::_11;

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
	this->m_device.GetSwapChain().Desc().Fake();
	this->m_device.GetSwapChain().Desc().ref().Flags |= D3D11_CREATE_DEVICE_SINGLETHREADED;
	this->m_device.GetSwapChain().Desc().Target(fake_wnd);
	// (2) the swap chain is created finally;
	this->m_device.SetSwapChain();
	if (this->m_device.Is_valid()) {
		_out() += this->m_device.Print();
		_out() += TStringEx().Format(_T("*result*:%s"), (_pc_sz) this->m_device.GetSwapChain().Print(e_print::e_all));
	}
	else
		_out() += this->m_device.Error().Print(TError::e_print::e_req);

	_out()();
}