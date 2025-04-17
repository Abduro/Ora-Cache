/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Apr-2025 at 22:19:32.116, UTC+4, Batumi, Monday;
	This is Ebo Pack DirectX 12 adapter wrapper interface implementation file;
*/
#include "direct_x.adapter.2.h"
#include "direct_x.factory.2.h"

using namespace ex_ui::draw::direct_x::_12;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace direct_x { namespace _impl {
#if defined(_DEBUG)

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
		CString Flags   (uint32_t _flags) const // https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ne-dxgi-dxgi_adapter_flag ;
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

#endif
#if (0)
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
#endif
}}}}
using namespace ex_ui::draw::direct_x::_impl;
/////////////////////////////////////////////////////////////////////////////

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
TAdapters&  CAdapter_Enum::Get (void) const { return this->m_adapters; }
err_code    CAdapter_Enum::Set (void)
{
	this->m_error << __METHOD__ << __s_ok;

	if (this->m_adapters.empty() == false)
		this->m_adapters.clear();

	TAdapterPtr p_adapter ;
	TFac1Ptr    p_fac_1 ;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-createdxgifactory1 ;
	this->m_error << ::CreateDXGIFactory1(__uuidof(TFac1Ptr), (void**)&p_fac_1);
	if (true == this->Error()) {
	    return  this->Error();
	}

	uint32_t n_index = 0;

	do {
		m_error << p_fac_1->EnumAdapters1(n_index, &p_adapter);
		if (true == m_error)
		{
			if (DXGI_ERROR_NOT_FOUND == this->Error().Result())
				this->m_error << __s_ok;
			break;
		}
		
		CAdapter ada_object;
		ada_object.Ptr(p_adapter.Detach());
		// checks a support of Direct3D 12; does not care about returned result;
		// https://learn.microsoft.com/en-us/windows/win32/api/d3d12/nf-d3d12-d3d12createdevice ;
		
		ada_object.Props().Dx_12(__succeeded(::D3D12CreateDevice(p_adapter, D3D_FEATURE_LEVEL_11_0, _uuidof(TDevicePtr), nullptr)));

		try // not checked how it may to concern regarding to vector::push_back, looks like is just for playing;
		{
			this->m_adapters.push_back(ada_object);
		}
		catch (const ::std::bad_alloc&)
		{
			this->m_error << __e_no_memory;
			break;
		}

		p_adapter = nullptr; // releases the COM interface pointer;
		n_index += 1;
	}
	while (false == this->Error());

	// the second step for getting high performance adapter(s)
	if (false == this->Error())
	{
#if (1) // it requires Windows SDK 10.0.17763.0 and above; https://developer.microsoft.com/en-us/windows/downloads/sdk-archive/ ;
		TFac6Ptr p_fac_6; // is required for getting adapter info by using GPU preference;

		if (__s_ok == (p_fac_1->QueryInterface(IID_PPV_ARGS(&p_fac_6))))
		{
			if (p_adapter) p_adapter = nullptr;
			n_index = 0;

			bool b_found = false;
			// according to official documents, an adapter that has the highest performance comes first;
			// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_6/nf-dxgi1_6-idxgifactory6-enumadapterbygpupreference ;
			for (
					n_index = 0;
					__s_ok == p_fac_6->EnumAdapterByGpuPreference(n_index, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&p_adapter));
					n_index++
			    )
			{
				CAdapter fast_run;
				fast_run.Ptr(p_adapter.Detach());

				for (size_t i_ = 0; i_ < this->m_adapters.size(); i_++) // just trying to find existing adapter for setting its attr to true;
				{
					if (fast_run == m_adapters[i_])
					{
						m_adapters[i_].Props().Hi_Perf(true); b_found = true; break;
					}
				}
				p_adapter = nullptr;
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