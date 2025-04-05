/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Apr-2025 at 16:31:42.013, UTC+4, Batumi, Thursday;
	This is Ebo Pack DirectX device base wrapper interface implementation file;
*/
#include "direct_x.device.h"

using namespace ex_ui::draw::direct_x;

/////////////////////////////////////////////////////////////////////////////

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
bool   CDevice::Is_valid (void) const { return (nullptr != this->m_object); }

const
TDevicePtr& CDevice::Ptr (void) const { return this->m_object; }
TDevicePtr& CDevice::Ptr (void)       { return this->m_object; }

/////////////////////////////////////////////////////////////////////////////

CDevice_Warp:: CDevice_Warp (void) : TBase() {}

/////////////////////////////////////////////////////////////////////////////

err_code CDevice_Warp::Create (const CAda_Warp& _ada_warp) {
	_ada_warp;
	TBase::m_error << __METHOD__ << __s_ok;

	if (false == _ada_warp.Is())
		return (TBase::m_error << __e_invalid_arg) = _T("Warp adapter is not valid;");

	if (TBase::Is_valid())
		return (TBase::m_error <<(err_code)TErrCodes::eObject::eInited);

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d12/nf-d3d12-d3d12createdevice ;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3dcommon/ne-d3dcommon-d3d_feature_level ;
	TBase::m_error << ::D3D12CreateDevice(_ada_warp.Ptr(), D3D_FEATURE_LEVEL_11_0, __uuidof(TWarpAdaPtr), (void**)&TBase::Ptr());
	
	return TBase::Error();
}

/////////////////////////////////////////////////////////////////////////////

CDevice_HW:: CDevice_HW (void) : TBase() {}

/////////////////////////////////////////////////////////////////////////////

err_code  CDevice_HW::Create (const CAdapter& _adapter) {
	_adapter;
	TBase::m_error << __METHOD__ << __s_ok;

	if (false == _adapter.Is())
		return (TBase::m_error << __e_invalid_arg) = _T("Input adapter is not valid;");

	TBase::m_error << ::D3D12CreateDevice(_adapter.Ptr(), D3D_FEATURE_LEVEL_11_0, _uuidof(TAdapterPtr), (void**)&TBase::Ptr());

	return TBase::Error();
}