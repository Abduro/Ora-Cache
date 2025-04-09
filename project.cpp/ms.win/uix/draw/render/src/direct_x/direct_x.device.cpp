/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Apr-2025 at 16:31:42.013, UTC+4, Batumi, Thursday;
	This is Ebo Pack DirectX device base wrapper interface implementation file;
*/
#include "direct_x.device.h"

using namespace ex_ui::draw::direct_x;

/////////////////////////////////////////////////////////////////////////////
namespace ex_ui { namespace draw { namespace direct_x { namespace _11 {

CFeature:: CFeature (void) : m_p_data(nullptr), m_size (0), m_type(EFeature::D3D11_FEATURE_THREADING) {}
#if (0)
CFeature:: CFeature (const CFeature& _src) : CFeature() { *this = _src; }
#endif
/////////////////////////////////////////////////////////////////////////////

err_code   CFeature::Clear (void) {
	err_code n_result = __s_ok;

	if (false == this->Is_valid())
		return (n_result = TErrCodes::eData::eInvalid);
	try {
		::memset(this->Data(), 0, this->Size());
	}
	catch (...) {
		n_result = TErrCodes::eAccess::eDenied;
	}
	return n_result;
}
const
void* const CFeature::Data (void) const { return this->m_p_data; }
void* const CFeature::Data (void)       { return this->m_p_data; }

bool  CFeature::Is_valid (void) const { return (nullptr != this->Data() && !!this->Size()); }

uint32_t  CFeature::Size (void) const { return this->m_size; }
bool      CFeature::Size (const uint32_t _n_size) {
	const bool b_changed = (this->Size() != _n_size);
	if (b_changed)
		this->m_size = _n_size;
	return b_changed;
}

EFeature  CFeature::Type (void) const { return this->m_type; }
bool      CFeature::Type (const EFeature _e_type) {
	const bool b_changed = (this->Type() != _e_type);
	if (b_changed)
		this->m_type = _e_type;
	return b_changed;
}

/////////////////////////////////////////////////////////////////////////////
#if (0)
CFeature& CFeature::operator = (const CFeature& _src) { *this << _src.Data() << _src.Size() << _src.Type(); return *this; }
#endif
CFeature& CFeature::operator <<(const EFeature _e_type) { this->Type(_e_type); return *this; }
CFeature& CFeature::operator <<(const uint32_t _n_size) { this->Size(_n_size); return *this; }

/////////////////////////////////////////////////////////////////////////////

CFeature_Thread::CFeature_Thread (void) : TBase() {
	TBase::m_p_data = &this->m_data;
	TBase::m_size   = sizeof(this->m_data);
	TBase::m_type   = EFeature::D3D11_FEATURE_THREADING;
}

/////////////////////////////////////////////////////////////////////////////
const
TDataThread& CFeature_Thread::Ref (void) const { return this->m_data; }
TDataThread& CFeature_Thread::Ref (void)       { return this->m_data; }
#if defined(_DEBUG)
CString      CFeature_Thread::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{concurrent=%s;commands=%s;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{concurrent=%s;commands=%s;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{concurrent=%s;commands=%s;valid=%s}");

	CString cs_concurrent = TStringEx().Bool(this->Ref().DriverConcurrentCreates);
	CString cs_commands = TStringEx().Bool(this->Ref().DriverCommandLists);
	CString cs_valid = TStringEx().Bool(TBase::Is_valid());

	CString cs_out;
	if (e_print::e_all   == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)cs_concurrent, (_pc_sz)cs_commands, (_pc_sz)cs_valid);
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz)cs_concurrent, (_pc_sz)cs_commands, (_pc_sz)cs_valid);
	}
	if (e_print::e_req   == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz)cs_concurrent, (_pc_sz)cs_commands, (_pc_sz)cs_valid); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////

CFeature_Format:: CFeature_Format (void) : TBase() {
	TBase::m_p_data = &this->m_data;
	TBase::m_size   = sizeof(this->m_data);
	TBase::m_type   = EFeature::D3D11_FEATURE_FORMAT_SUPPORT;
}

/////////////////////////////////////////////////////////////////////////////
const
TDataFromat& CFeature_Format::Ref (void) const { return this->m_data; }
TDataFromat& CFeature_Format::Ref (void)       { return this->m_data; }
#if defined(_DEBUG)
CString      CFeature_Format::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{fmt_in=%s;supported=%s;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{fmt_in=%s;supported=%s;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{fmt_in=%s;supported=%s;valid=%s}");

	CString cs_fmt_in  = TStringEx().Dword(this->Ref().InFormat);
	CString cs_fmt_out = TStringEx().Dword(this->Ref().OutFormatSupport);
	CString cs_valid   = TStringEx().Bool(TBase::Is_valid());

	CString cs_out;
	if (e_print::e_all == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)cs_fmt_in, (_pc_sz)cs_fmt_out, (_pc_sz)cs_valid);
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz)cs_fmt_in, (_pc_sz)cs_fmt_out, (_pc_sz)cs_valid);
	}
	if (e_print::e_req == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz)cs_fmt_in, (_pc_sz)cs_fmt_out, (_pc_sz)cs_valid); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////

CDevice:: CDevice (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CDevice::~CDevice (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code  CDevice::Get (CFeature& _feature) {
	this->m_error << __METHOD__ << __s_ok;

	if (false == _feature.Is_valid())
		return (this->m_error << __e_invalid_arg) = _T("Input feature is not valid;");

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

	this->m_error << p_device_3->GetAdapter(&_adapter.Ptr());

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

err_code  CDevice_HW::Create (void) {
	TBase::m_error << __METHOD__ << __s_ok;

	if (TBase::Is_valid())
		return (TBase::m_error << (err_code)TErrCodes::eObject::eExists);

	const D3D_FEATURE_LEVEL a_levels[] = {
	//	D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3 , D3D_FEATURE_LEVEL_9_2 , D3D_FEATURE_LEVEL_9_1 ,
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-d3d11createdevice ;
	TBase::m_error << ::D3D11CreateDevice(
		nullptr, (D3D_DRIVER_TYPE)CDrv_Type::e_ref, nullptr, CDev_Flag::e_single, &a_levels[0], 3, D3D11_SDK_VERSION, &TBase::Ptr(), nullptr, nullptr
	);
	// D3D11_SDK_VERSION      - must be applied;
	// D3D_FEATURE_LEVEL_11_0 - must be not applied;

	return TBase::Error();
}

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