/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Dec-2022 at 14:07:02.321, UTC+7, Novosibirsk, Thursday;
	This is Yandex Wanderer project hardware video/adapter interface implementation file;
*/
#include "direct_x.adapter.h"

using namespace ex_ui::draw::direct_x;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace direct_x { namespace _impl {

	class CAdapterInfo  // this class formats TAdapterInfo structure for output; TODO: the class must be renamed for better readability;
	{

	public: // neither copy constructor nor assign operator is required;
		CAdapterInfo (void) {/* does nothing and very looks like as useless*/}
		CAdapterInfo (const CAdapterInfo&) : CAdapterInfo() {/*useless*/}
		CAdapterInfo (const _12::CAdapter& _ada) : CAdapterInfo() { *this << _ada; }

	public:
		_pc_sz  Get (void) const { return this->m_formatted.GetString(); }
		_pc_sz  Put (const _12::CAdapter& _ada, _pc_sz _lp_sz_sep = _T("\n\t\t"), bool _aligned = true)
		{
			const _12::TAdapterInfo& info_ = _ada.Info();
			_pc_sz lp_sz_pat = this->Pattern(_aligned);
			m_formatted.Format(
				 lp_sz_pat,
				_lp_sz_sep, 0 == ::_tcslen(info_.Description) ? _T("#undef") : info_.Description,
				_lp_sz_sep, info_.VendorId   ,
				_lp_sz_sep, info_.DeviceId   ,
				_lp_sz_sep, info_.SubSysId   ,
				_lp_sz_sep, info_.Revision   ,
				_lp_sz_sep, info_.DedicatedVideoMemory  / 1024 / 1024,
				_lp_sz_sep, info_.DedicatedSystemMemory / 1024 / 1024,
				_lp_sz_sep, info_.SharedSystemMemory    / 1024 / 1024,
				_lp_sz_sep, info_.AdapterLuid.LowPart   , // only low part attribute is taken into account;
				_lp_sz_sep, (_pc_sz)this->Flags(info_.Flags),
				_lp_sz_sep, (_ada.Is_12_Supported() ? _T("true") : _T("false")),
				_lp_sz_sep, (_ada.Is_Hi_Performed() ? _T("true") : _T("false"))
			);
			return this->Get();
		}

	public:
		CAdapterInfo& operator << (const _12::CAdapter& _ada) { this->Put(_ada.Info()); return *this; }
		operator _pc_sz (void) const { return this->Get(); }

	private:
		CString  m_formatted;

	private:
		CString Flags   (UINT _flags) const // https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ne-dxgi-dxgi_adapter_flag ;
		{
			CString cs_flags;

			if (DXGI_ADAPTER_FLAG_REMOTE & _flags) cs_flags = _T("DXGI_ADAPTER_FLAG_REMOTE"); // useless, because this value is not used, but nevertheless;
			if (DXGI_ADAPTER_FLAG_SOFTWARE & _flags) // default software adapter has this flag value;
			{
				if (false == cs_flags.IsEmpty())
					cs_flags += _T("|");
				cs_flags += _T("DXGI_ADAPTER_FLAG_SOFTWARE");
			}
			if (DXGI_ADAPTER_FLAG_NONE == _flags) cs_flags = _T("DXGI_ADAPTER_FLAG_NONE"); // TODO: for performance it must be made first;
			
			return  cs_flags;
		}

		_pc_sz  Pattern (bool _aligned) const // aligning is okay for output to console or to multiline edit box, of course fixed size font must be applied;
		{
			static
			_pc_sz lp_sz_pat = nullptr;

			if (_aligned)
				lp_sz_pat = _T(
					"%sDescription           : %s"
					"%sVendorId              : %u"
					"%sDeviceId              : %u"
					"%sSubSysId              : %u"
					"%sRevision              : %u"
					"%sDedicatedVideoMemory  : %u MB"
					"%sDedicatedSystemMemory : %u MB"
					"%sSharedSystemMemory    : %u MB"
					"%sAdapterLuid           : %u"
					"%sFlags                 : %s"
					"%sDirectX12 supported   : %s"
					"%sHigh performance GPU  : %s"
				);
			else
				lp_sz_pat = _T(
					"%sDescription : %s"
					"%sVendorId : %u"
					"%sDeviceId : %u"
					"%sSubSysId : %u"
					"%sRevision : %u"
					"%sDedicatedVideoMemory : %u MB"
					"%sDedicatedSystemMemory : %u MB"
					"%sSharedSystemMemory : %u MB"
					"%sAdapterLuid : %u"
					"%sFlags : %s"
					"%sDirectX12 supported : %s"
					"%sHigh performance GPU : %s"
				);
			return lp_sz_pat;
		}
	};

	typedef ::ATL::CComPtr<IDXGIFactory6> TFac_6;

	class CAdapter_Finder {
	public:
		 CAdapter_Finder (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
		 CAdapter_Finder (const CAdapter_Finder&) = delete; CAdapter_Finder (CAdapter_Finder&&) = delete;
		~CAdapter_Finder (void) = default;

	public:
		TError&    Error (void) const { return this->m_error;  }
		err_code   IsFast (TFac_6& _fac_6, const LUID& _to_check, bool& _b_result) {

			this->m_error << __METHOD__ << __s_ok;

			_12::TAdapterInfo info_ = { 0 };
			_12::TAdapterPtr  adapter;
			uint32_t n_index = 0;

			_b_result = false;

			// according to official documents, an adapter that has the highest performance comes first;
			// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_6/nf-dxgi1_6-idxgifactory6-enumadapterbygpupreference ;
			for (
				n_index = 0;
				__s_ok == _fac_6->EnumAdapterByGpuPreference(n_index, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&adapter)) &&
				__s_ok == adapter->GetDesc1(&info_);
				n_index++
				)
			{
				_b_result = (info_.AdapterLuid.LowPart == _to_check.LowPart);
				if (_b_result)
					break;
				adapter = nullptr;
			}

			return this->Error();
		}

	private:
		CAdapter_Finder& operator = (const CAdapter_Finder&) = delete;
		CAdapter_Finder& operator = (CAdapter_Finder&&) = delete;

	private:
		CError  m_error;
	};
}}}}

using namespace ex_ui::draw::direct_x::_impl;
/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace direct_x { namespace _11 {
	using CParent = CAda_Warp::CParent;

/////////////////////////////////////////////////////////////////////////////

CParent:: CParent (void) {}

/////////////////////////////////////////////////////////////////////////////

bool      CParent::Is_valid (void) const { return (nullptr != this->Ptr()); }
const
TParentPtr& CParent::Ptr (void) const { return this->m_p_parent; }
TParentPtr& CParent::Ptr (void)       { return this->m_p_parent; }

/////////////////////////////////////////////////////////////////////////////

CAda_Warp:: CAda_Warp (void) : m_info{0} {}
CAda_Warp:: CAda_Warp (const CAda_Warp& _src) : CAda_Warp() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////

err_code    CAda_Warp::Get (CParent& _factory) {
	_factory;
	err_code n_result = __s_ok;

	if (_factory.Is_valid())
		return (n_result = (err_code)TErrCodes::eObject::eExists);
//	if (false == this->Is())
//		return (n_result = __e_not_inited);
//	cannot use the above check due to it looks like this adapter object is gotten by device and no adapter info is available yet;
	if (nullptr == this->Ptr())
		return (n_result = __e_not_inited);

	n_result = this->Ptr()->GetParent(__uuidof(TParentPtr), (void**)&_factory.Ptr());

	return n_result;
}
const
TAdaInfoWarp& CAda_Warp::Info (void) const { return this->m_info; }
TAdaInfoWarp& CAda_Warp::Info (void) { return this->m_info; }

bool CAda_Warp::Is (void) const { return (!!::_tcslen(this->Info().Description) && !!this->Info().AdapterLuid.LowPart); }

const
TWarpAdaPtr&  CAda_Warp::Ptr (void) const { return this->m_object; }
TWarpAdaPtr&  CAda_Warp::Ptr (void) { return this->m_object; }

/////////////////////////////////////////////////////////////////////////////

CAda_Warp&  CAda_Warp::operator = (const CAda_Warp& _src) { *this << _src.Ptr() << _src.Info(); return *this; }

CAda_Warp&  CAda_Warp::operator <<(const TWarpAdaPtr& _p_adapter) { this->Ptr() = _p_adapter; return *this; }
CAda_Warp&  CAda_Warp::operator <<(const TAdaInfoWarp& _p_info) { this->Info() = _p_info; return *this; }

/////////////////////////////////////////////////////////////////////////////

CEnum_Warp:: CEnum_Warp (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CEnum_Warp:: CEnum_Warp (const CEnum_Warp& _src) : CEnum_Warp() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////

TErrorRef    CEnum_Warp::Error (void) const { return this->m_error; }
const
CAda_Warp&   CEnum_Warp::Get (void) const { return this->m_ada_warp; }
err_code     CEnum_Warp::Set (void) {
	this->m_error << __METHOD__ << __s_ok;

	// https://stackoverflow.com/questions/42354369/idxgifactory-versions ;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_3/nf-dxgi1_3-createdxgifactory2 ;

	::ATL::CComPtr<IDXGIFactory4> factory_4;
	this->m_error << ::CreateDXGIFactory2(0, __uuidof(IDXGIFactory4), (void**)&factory_4);
	if (true == this->Error()) {
		return  this->Error();
	}
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgiadapter ;
	TWarpAdaPtr warp_ada;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_4/nf-dxgi1_4-idxgifactory4-enumwarpadapter ;
	this->m_error << factory_4->EnumWarpAdapter(__uuidof(IDXGIAdapter), (void**)&warp_ada);
	if (true == this->Error()) {
		return  this->Error();
	}
	else
		this->m_ada_warp.Ptr() = warp_ada;

	TAdaInfoWarp warp_info = { 0 };

	this->m_error << warp_ada->GetDesc(&warp_info);
	if (true == this->Error()) {
	    return  this->Error();
	}

	this->m_ada_warp.Info() = warp_info;
	bool b_is_fast = false;

	::ATL::CComPtr<IDXGIFactory6> factory6;
	if (__s_ok == (factory_4->QueryInterface(IID_PPV_ARGS(&factory6)))) {
		CAdapter_Finder finder;
		if (__succeeded(finder.IsFast(factory6, warp_info.AdapterLuid, b_is_fast))) {
	
		}
	}

	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////

CEnum_Warp&  CEnum_Warp::operator = (const CEnum_Warp& _src) { _src; return *this; }

}}}}

namespace ex_ui { namespace draw { namespace direct_x { namespace _12 {

CAdapter:: CAdapter (void) : m_info{0}, m_performance(false), m_support_12(false) {}
CAdapter:: CAdapter (const CAdapter& _ref) : CAdapter() { *this = _ref; }
CAdapter:: CAdapter (const TAdapterInfo& _info) : CAdapter() { *this << _info; }
CAdapter:: CAdapter (CAdapter&& _victim) : CAdapter() { *this = _victim; }
CAdapter::~CAdapter (void) {}

/////////////////////////////////////////////////////////////////////////////

err_code   CAdapter::Info (const TAdapterInfo& _info) {
	_info;
	err_code n_result = __s_ok;

	const errno_t t_err = ::memcpy_s(&this->Info(), sizeof(TAdapterInfo), &_info, sizeof(TAdapterInfo));
	if (__s_ok != t_err)
		n_result = __e_no_memory;

	return n_result;
}
const
TAdapterInfo& CAdapter::Info (void) const { return this->m_info; }
TAdapterInfo& CAdapter::Info (void)       { return this->m_info; }

// https://learn.microsoft.com/en-us/windows/win32/api/ntdef/ns-ntdef-luid ;
// checking description attribute is *not* enough, the pointer to object must be checked too, otherwise, the desc must be moved to its own class;
bool    CAdapter::Is (void) const { return (nullptr != this->Ptr() && !!::_tcslen(this->Info().Description) && !!this->Info().AdapterLuid.LowPart); }

bool    CAdapter::Is_12_Supported (void) const  { return this->m_support_12;   }
void    CAdapter::Is_12_Supported (bool _value) { this->m_support_12 = _value; }

bool    CAdapter::Is_Hi_Performed (void) const  { return this->m_performance;   }
void    CAdapter::Is_Hi_Performed (bool _value) { this->m_performance = _value; }
#if defined(_DEBUG)
CString CAdapter::Print(_pc_sz _lp_sz_sep, bool _aligned) const
{
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]{%s%s}");

	CString cs_out; cs_out.Format(
		pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (CAdapterInfo()).Put(*this, _lp_sz_sep, _aligned), _lp_sz_sep
	);
	return  cs_out;
}
#endif
const
TAdapterPtr& CAdapter::Ptr (void) const { return this->m_p_adapter; }
TAdapterPtr& CAdapter::Ptr (void)       { return this->m_p_adapter; }

/////////////////////////////////////////////////////////////////////////////

CAdapter&  CAdapter::operator = (const CAdapter& _ref) {
	*this << _ref.Info() << _ref.Ptr();

	this->Is_12_Supported(_ref.Is_12_Supported());
	this->Is_Hi_Performed(_ref.Is_Hi_Performed());

	return *this;
}

CAdapter&  CAdapter::operator = (CAdapter&& _victim) {
	*this = _victim; return *this; // no move operation is actually made;
}

CAdapter&  CAdapter::operator <<(const TAdapterInfo& _info) { this->Info(_info); return *this; }
CAdapter&  CAdapter::operator <<(const TAdapterPtr& _p_adapter) { this->Ptr() = _p_adapter; return *this; }

bool CAdapter::operator == (const CAdapter& _ref) const { return *this == _ref.Info(); }
bool CAdapter::operator == (const TAdapterInfo& _ref) const { return (this->Info().AdapterLuid.LowPart == _ref.AdapterLuid.LowPart); }

/////////////////////////////////////////////////////////////////////////////

CAdapter_Enum:: CAdapter_Enum (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CAdapter_Enum:: CAdapter_Enum (const CAdapter_Enum& _ref) : CAdapter_Enum() { *this = _ref; }
CAdapter_Enum::~CAdapter_Enum (void) {}

/////////////////////////////////////////////////////////////////////////////

TErrorRef   CAdapter_Enum::Error (void) const { return this->m_error; }
const
TAdapters&  CAdapter_Enum::Get   (void) const { return this->m_adapters; }
err_code    CAdapter_Enum::Set   (void)
{
	this->m_error << __METHOD__ << __s_ok;

	if (this->m_adapters.empty() == false)
		this->m_adapters.clear();

	::ATL::CComPtr<IDXGIAdapter1> adapter ;
	::ATL::CComPtr<IDXGIFactory1> factory ;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-createdxgifactory1 ;
	this->m_error << ::CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&factory);
	if (true == this->Error()) {
	    return  this->Error();
	}

	UINT n_index = 0;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-idxgiadapter1-getdesc1 ;
	TAdapterInfo info_ = {0};

	do {
		m_error << factory->EnumAdapters1(n_index, &adapter);
		if (true == m_error)
		{
			if (DXGI_ERROR_NOT_FOUND == this->Error().Result())
				this->m_error << __s_ok;
			break;
		}
		
		this->m_error << adapter->GetDesc1(&info_);
		if (true == m_error)
			break;
		// checks a support of Direct3D 12; does not care about returned result;
		// https://learn.microsoft.com/en-us/windows/win32/api/d3d12/nf-d3d12-d3d12createdevice ;
		CAdapter ada_object(info_);
		ada_object.Is_12_Supported(__succeeded(::D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr)));
		ada_object.Ptr() = adapter.Detach();

		try // not checked how it may to concern regarding to vector::push_back, looks like is just for playing;
		{
			this->m_adapters.push_back(ada_object);
		}
		catch (const ::std::bad_alloc&)
		{
			this->m_error << __e_no_memory;
			break;
		}

		adapter  = nullptr; // releases the COM interface pointer;
		n_index += 1;
	}
	while (false == this->Error());

	// the second step for getting high performance adapter(s)
	if (false == this->Error())
	{
#if (1) // it requires Windows SDK 10.0.17763.0 and above; https://developer.microsoft.com/en-us/windows/downloads/sdk-archive/ ;
		::ATL::CComPtr<IDXGIFactory6> factory6; // is required for getting adapter info by using GPU preference;

		if (__s_ok == (factory->QueryInterface(IID_PPV_ARGS(&factory6))))
		{
			if (adapter) adapter = nullptr;
			n_index = 0;

			bool b_found = false;
			// according to official documents, an adapter that has the highest performance comes first;
			// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_6/nf-dxgi1_6-idxgifactory6-enumadapterbygpupreference ;
			for (
					n_index = 0;
					__s_ok == factory6->EnumAdapterByGpuPreference(n_index, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&adapter)) &&
					__s_ok == adapter ->GetDesc1(&info_);
					n_index++
			    )
			{
				CAdapter fast_run(info_);
				for (size_t i_ = 0; i_ < this->m_adapters.size(); i_++) // just trying to find existing adapter for setting its attr to true;
				{
					if (fast_run == m_adapters[i_])
					{
						m_adapters[i_].Is_Hi_Performed(true); b_found = true; break;
					}
				}
				adapter = nullptr;
				if (b_found)
					break;
			} 
		}
#endif
	}
	return this->Error();
}
const
CAdapter&   CAdapter_Enum::Get (const TFlag _e_flag) const {
	_e_flag;
	static const CAdapter ada_undef;
	if (this->Get().empty())
		return ada_undef;
	for (size_t i_ = 0; i_ < this->Get().size(); i_++) {
		switch (_e_flag) {
		case TFlag::DXGI_ADAPTER_FLAG_SOFTWARE: {
			const CAdapter& adapter = this->Get().at(i_);
			if (adapter.Info().Flags == (uint32_t)_e_flag) {
			}
		} break;
		}
	}
	return ada_undef;
}

/////////////////////////////////////////////////////////////////////////////

CAdapter_Enum&  CAdapter_Enum::operator = (const CAdapter_Enum& _ref) { this->m_error = _ref.Error(); return *this; }

}}}}