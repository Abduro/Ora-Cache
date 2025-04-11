/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Dec-2022 at 14:07:02.321, UTC+7, Novosibirsk, Thursday;
	This is Yandex Wanderer project hardware video/adapter interface implementation file;
*/
#include "direct_x.adapter.h"
#include "direct_x.factory.h"

using namespace ex_ui::draw::direct_x;

/////////////////////////////////////////////////////////////////////////////

CProps:: CProps (void) : m_12_vers(false), m_hi_perf(false), m_lo_power(false) {}
CProps:: CProps (const CProps& _src) : CProps() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////

bool  CProps::Dx_12   (void) const { return this->m_12_vers; }
bool  CProps::Dx_12   (const bool _b_value) {
	const bool b_changed = (this->Dx_12() != _b_value); if (b_changed) this->m_12_vers = _b_value; return b_changed;
}

bool  CProps::Hi_Perf (void) const { return this->m_hi_perf; }
bool  CProps::Hi_Perf (const bool _b_value) {
	const bool b_changed = (this->Hi_Perf() != _b_value); if (b_changed) this->m_hi_perf = _b_value; return b_changed;
}

bool  CProps::Lo_Power(void) const { return this->m_lo_power; }
bool  CProps::Lo_Power(const bool _b_value) {
	const bool b_changed = (this->Lo_Power() != _b_value); if (b_changed) this->m_lo_power = _b_value; return b_changed;
}

#if defined(_DEBUG)
CString  CProps::Print(const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{dx_12=%s;hi_perf=%s;lo_power=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{dx_12=%s;hi_perf=%s;lo_power=%s}");
	static _pc_sz pc_sz_pat_r = _T("{dx_12=%s;hi_perf=%s;lo_power=%s}");

	CString cs_dx_12 = TStringEx().Bool(this->Dx_12());
	CString cs_hi_perf = TStringEx().Bool(this->Hi_Perf());
	CString cs_lo_power = TStringEx().Bool(this->Lo_Power());

	CString cs_out;
	if (e_print::e_all == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__,
			(_pc_sz)cs_dx_12, (_pc_sz)cs_hi_perf, (_pc_sz)cs_lo_power);
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__,
			(_pc_sz)cs_dx_12, (_pc_sz)cs_hi_perf, (_pc_sz)cs_lo_power);
	}
	if (e_print::e_req == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz)cs_dx_12, (_pc_sz)cs_hi_perf, (_pc_sz)cs_lo_power); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////

CProps&  CProps::operator = (const CProps& _src) {
	this->Dx_12(_src.Dx_12()); this->Hi_Perf(_src.Hi_Perf()); this->Lo_Power(_src.Lo_Power());
	return *this;
}

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace direct_x { namespace _impl {

	class CAdapterInfo  // this class formats TAdapterInfo structure for output; TODO: the class must be renamed for better readability;
	{
		using CAdapter = ex_ui::draw::direct_x::_12::CAdapter;

	public: // neither copy constructor nor assign operator is required;
		CAdapterInfo (void) {/* does nothing and very looks like as useless*/}
		CAdapterInfo (const CAdapterInfo&) : CAdapterInfo() {/*useless*/}
		CAdapterInfo (const _12::CAdapter& _ada) : CAdapterInfo() { *this << _ada; }

	public:
		_pc_sz  Get (void) const { return this->m_formatted.GetString(); }
		_pc_sz  Put (const CAdapter& _ada, _pc_sz _lp_sz_sep = _T("\n\t\t"), bool _aligned = true)
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
				_lp_sz_sep, (_ada.Props().Dx_12() ? _T("true") : _T("false")),
				_lp_sz_sep, (_ada.Props().Hi_Perf() ? _T("true") : _T("false")),
				_lp_sz_sep, (_ada.Props().Lo_Power() ? _T("true") : _T("false"))
			);
			return this->Get();
		}

	public:
		CAdapterInfo& operator << (const CAdapter& _ada) { this->Put(_ada); return *this; }
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
					"%sLow power consume     : %s"
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
					"%sLow power consume : %s"
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

bool   CParent::Is_valid (void) const { return (nullptr != this->Ptr()); }
const
TParentPtr& CParent::Ptr (void) const { return this->m_p_parent; }
TParentPtr& CParent::Ptr (void)       { return this->m_p_parent; }

/////////////////////////////////////////////////////////////////////////////

CAda_Warp:: CAda_Warp (void) : m_info{0} { this->m_error >> __CLASS__ << __METHOD__  <<  __e_not_inited; }
CAda_Warp:: CAda_Warp (const CAda_Warp& _src) : CAda_Warp() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////

TError&   CAda_Warp::Error (void) const { return this->m_error; }

err_code  CAda_Warp::Get (CParent& _parent) {
	_parent;
	this->m_error << __METHOD__ << __s_ok;

	if (_parent.Is_valid())
		return (this->m_error << (err_code)TErrCodes::eObject::eExists);

	if (nullptr == this->Ptr())
		return (this->m_error << __e_not_inited);

	this->m_error << this->Ptr()->GetParent(__uuidof(TParentPtr), (void**)&_parent.Ptr());

	return this->Error();
}

const
TInfo&    CAda_Warp::Info (void) const { return this->m_info; }
TInfo&    CAda_Warp::Info (void)       { return this->m_info; }

#if (0)
bool CAda_Warp::Is (void) const { return (!!::_tcslen(this->Info().Description) && !!this->Info().AdapterLuid.LowPart); }
#else
bool CAda_Warp::Is (void) const { return (nullptr != this->Ptr()); }
#endif

#if defined(_DEBUG)
CString  CAda_Warp::Print(const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{desc=%s;luid=%d;props=%s;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{desc=%s;luid=%d;props=%s;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{desc=%s;luid=%d;props=%s;valid=%s}");

	CString cs_desc(this->Info().Description);
	if (cs_desc.IsEmpty())
		cs_desc = _T("#not_set");

	CString cs_valid = TStringEx().Bool(this->Is());
	CString cs_props = this->Props().Print(e_print::e_req);

	CString cs_out;
	if (e_print::e_all   == _e_opt) {
		cs_out.Format(pc_sz_pat_a,
			(_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)cs_desc, this->Info().AdapterLuid.LowPart, (_pc_sz)cs_props, (_pc_sz)cs_valid
		);
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n,
			(_pc_sz)__CLASS__, (_pc_sz)cs_desc, this->Info().AdapterLuid.LowPart, (_pc_sz)cs_props, (_pc_sz)cs_valid
		);
	}
	if (e_print::e_req   == _e_opt) {
		cs_out.Format(pc_sz_pat_r, 
			(_pc_sz)cs_desc, this->Info().AdapterLuid.LowPart, (_pc_sz)cs_props, (_pc_sz)cs_valid
		);
	}

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif

const
CProps&   CAda_Warp::Props(void) const { return this->m_props; }
CProps&   CAda_Warp::Props(void)       { return this->m_props; }

const
TWarpPtr& CAda_Warp::Ptr (void) const { return this->m_object; }
err_code  CAda_Warp::Ptr (const TWarpPtr& _p_ptr) {
	_p_ptr;
	this->m_error << __METHOD__ << __s_ok;

	if (this->Is())
		return this->m_error << (err_code)TErrCodes::eObject::eExists;

	if (nullptr == _p_ptr)
		return this->m_error << __e_pointer;

	using CFac_6 = ex_ui::draw::direct_x::_12::CFac_6;

	this->m_object = _p_ptr;
	this->UpdateInfo();
	// updates the supporting dx12;
	this->Props().Dx_12(__succeeded(::D3D12CreateDevice(_p_ptr, D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr)));
	this->Props().Hi_Perf(CFac_6().Is_Hi_Perf(this->Info().AdapterLuid.LowPart));
	this->Props().Lo_Power(CFac_6().Is_Lo_Power(this->Info().AdapterLuid.LowPart));


	return this->Error();
}

err_code  CAda_Warp::UpdateInfo (void) {
	this->m_error << __METHOD__ << __s_ok;

	if (false == this->Is())
		return this->m_error << __e_not_inited;

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-idxgiadapter-getdesc ;

	this->m_error << this->Ptr()->GetDesc(&this->Info());
	
	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////

CAda_Warp&  CAda_Warp::operator = (const CAda_Warp& _src) { *this << _src.Ptr() << _src.Info(); return *this; }

CAda_Warp&  CAda_Warp::operator <<(const TWarpAdaPtr& _p_adapter) { this->Ptr(_p_adapter); return *this; }
CAda_Warp&  CAda_Warp::operator <<(const TAdaInfoWarp& _p_info)  { this->Info() = _p_info; return *this; }

/////////////////////////////////////////////////////////////////////////////

CWarp_Enum:: CWarp_Enum (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CWarp_Enum:: CWarp_Enum (const CWarp_Enum& _src) : CWarp_Enum() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////

TErrorRef    CWarp_Enum::Error (void) const { return this->m_error; }
const
CAda_Warp&   CWarp_Enum::Get (void) const { return this->m_ada_warp; }
err_code     CWarp_Enum::Set (void) {
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
		this->m_ada_warp.Ptr(warp_ada);

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

CWarp_Enum&  CWarp_Enum::operator = (const CWarp_Enum& _src) { _src; return *this; }

}}}}

namespace ex_ui { namespace draw { namespace direct_x { namespace _12 {

CAdapter:: CAdapter (void) : m_info{0} { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CAdapter:: CAdapter (const CAdapter& _ref) : CAdapter() { *this = _ref; }
CAdapter:: CAdapter (CAdapter&& _victim) : CAdapter() { *this = _victim; }
CAdapter::~CAdapter (void) {}

/////////////////////////////////////////////////////////////////////////////

TError&    CAdapter::Error (void) const { return this->m_error; }

err_code   CAdapter::Info (const TInfo& _info) {
	_info;
	this->m_error << __METHOD__ << __s_ok;

	const errno_t t_err = ::memcpy_s(&this->Info(), sizeof(TAdapterInfo), &_info, sizeof(TAdapterInfo));
	if (__s_ok != t_err)
		this->m_error << __e_no_memory;

	return this->Error();
}
const
TInfo&  CAdapter::Info (void) const { return this->m_info; }
TInfo&  CAdapter::Info (void)       { return this->m_info; }

// https://learn.microsoft.com/en-us/windows/win32/api/ntdef/ns-ntdef-luid ;
// checking description attribute is *not* enough, the pointer to object must be checked too, otherwise, the desc must be moved to its own class;
bool    CAdapter::Is (void) const {
	return (nullptr != this->Ptr() && !!::_tcslen(this->Info().Description) && !!this->Info().AdapterLuid.LowPart);
}

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
CProps& CAdapter::Props(void) const { return this->m_props; }
CProps& CAdapter::Props(void)       { return this->m_props; }
const
TAdapterPtr& CAdapter::Ptr (void) const { return this->m_p_adapter; }
err_code     CAdapter::Ptr (const TAdapterPtr& _p_ptr) {
	_p_ptr;
	if (this->Is())
		return m_error << (err_code)TErrCodes::eObject::eExists;
	if (nullptr == _p_ptr)
		return m_error << __e_pointer;

	this->m_p_adapter = _p_ptr;
	// updates the description;
	m_error << _p_ptr->GetDesc1(&this->m_info);
	// updates the supporting dx12;
	this->Props().Dx_12(__succeeded(::D3D12CreateDevice(_p_ptr, D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr)));
	this->Props().Hi_Perf(CFac_6().Is_Hi_Perf(this->Info().AdapterLuid.LowPart));
	this->Props().Lo_Power(CFac_6().Is_Lo_Power(this->Info().AdapterLuid.LowPart));

	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////

CAdapter&  CAdapter::operator = (const CAdapter& _ref) { *this << _ref.Info() << _ref.Ptr() << _ref.Props(); return *this; }

CAdapter&  CAdapter::operator = (CAdapter&& _victim) {
	*this = _victim; return *this; // no move operation is actually made;
}

CAdapter&  CAdapter::operator <<(const CProps& _props) { this->Props() = _props; return *this; }
CAdapter&  CAdapter::operator <<(const TAdapterInfo& _info) { this->Info(_info); return *this; }
CAdapter&  CAdapter::operator <<(const TAdapterPtr& _p_adapter) { this->Ptr(_p_adapter); return *this; }

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

	uint32_t n_index = 0;

	do {
		m_error << factory->EnumAdapters1(n_index, &adapter);
		if (true == m_error)
		{
			if (DXGI_ERROR_NOT_FOUND == this->Error().Result())
				this->m_error << __s_ok;
			break;
		}
		
		CAdapter ada_object;
		ada_object.Ptr(adapter.Detach());
		// checks a support of Direct3D 12; does not care about returned result;
		// https://learn.microsoft.com/en-us/windows/win32/api/d3d12/nf-d3d12-d3d12createdevice ;
		
		ada_object.Props().Dx_12(__succeeded(::D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr)));

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
					__s_ok == factory6->EnumAdapterByGpuPreference(n_index, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&adapter));
					n_index++
			    )
			{
				CAdapter fast_run;
				fast_run.Ptr(adapter.Detach());

				for (size_t i_ = 0; i_ < this->m_adapters.size(); i_++) // just trying to find existing adapter for setting its attr to true;
				{
					if (fast_run == m_adapters[i_])
					{
						m_adapters[i_].Props().Hi_Perf(true); b_found = true; break;
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