/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Apr-2025 at 15:52:25.528, UTC+4, Batumi, Thursday;
	This is Ebo Pack DirectX 11 device base wrapper interface implementation file;
*/
#include "direct_x.device.2.h"

using namespace ex_ui::draw::direct_x::_12;

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

	this->m_error << this->m_p_dev->CreateCommandQueue(&_queue.Desc(), __uuidof(TCmdQuePtr), (void**)&_queue.Ptr());

	return this->Error();
}

TError&   CDevice::Error (void) const { return this->m_error; }
bool   CDevice::Is_valid (void) const { return (nullptr != this->Ptr()); }

#if defined (_DEBUG)
CString   CDevice::Print (const e_print _e_opt) const {
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

/////////////////////////////////////////////////////////////////////////////

CDevice_HW::CDevice_HW (void) : TBase() {}

/////////////////////////////////////////////////////////////////////////////

err_code  CDevice_HW::Create (const CAdapter& _adapter) {
	_adapter;
	TBase::m_error << __METHOD__ << __s_ok;

	if (false == _adapter.Is())
		return (TBase::m_error << __e_invalid_arg) = _T("Input adapter is not valid;");

	if (TBase::Is_valid())
		return TBase::m_error << (err_code)TErrCodes::eObject::eExists;

	TDevicePtr p_base;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d12/nf-d3d12-d3d12createdevice ;
	TBase::m_error << ::D3D12CreateDevice(_adapter.Ptr(), D3D_FEATURE_LEVEL_11_0, _uuidof(TAdapterPtr), (void**)&p_base);
	if (false == this->Error())
		this->m_p_dev = p_base.Detach();

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

	TDevicePtr p_base;

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d12/nf-d3d12-d3d12createdevice ;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3dcommon/ne-d3dcommon-d3d_feature_level ;
	TBase::m_error << ::D3D12CreateDevice(_ada_warp.Ptr(), D3D_FEATURE_LEVEL_1_0_CORE, __uuidof(TWarpAdaPtr), (void**)&p_base);
	if (false == TBase::Error())
		TBase::Ptr(p_base.Detach());

	return TBase::Error();
}