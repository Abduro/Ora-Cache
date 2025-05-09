/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Apr-2025 at 22:14:50.198, UTC+4, Batumi, Monday;
	This is Ebo Pack DirectX 11 adapter wrapper interface implementation file;
*/
#include "direct_x.adapter.1.h"
#include "direct_x.factory.1.h"
#include "direct_x.factory.2.h"

using namespace ex_ui::draw::direct_x::_11;

using CParent = CAdapter::CParent;
/////////////////////////////////////////////////////////////////////////////

CParent:: CParent (void) {}

/////////////////////////////////////////////////////////////////////////////

bool   CParent::Is_valid (void) const { return (nullptr != this->Ptr()); }
const
TParentPtr& CParent::Ptr (void) const { return this->m_p_parent; }
TParentPtr& CParent::Ptr (void)       { return this->m_p_parent; }

/////////////////////////////////////////////////////////////////////////////

CAdapter:: CAdapter (void) : m_info{0} { this->m_error >> __CLASS__ << __METHOD__  <<  __e_not_inited; }
CAdapter:: CAdapter (const CAdapter& _src) : CAdapter() { *this = _src; }
CAdapter:: CAdapter (CAdapter&& _victim) : CAdapter() { *this = _victim; }

/////////////////////////////////////////////////////////////////////////////

TError&   CAdapter::Error (void) const { return this->m_error; }

err_code  CAdapter::Get (CParent& _parent) {
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
TInfo&    CAdapter::Info (void) const { return this->m_info; }
TInfo&    CAdapter::Info (void)       { return this->m_info; }

#if (0)
bool CAdapter::Is (void) const { return (!!::_tcslen(this->Info().Description) && !!this->Info().AdapterLuid.LowPart); }
#else
bool CAdapter::Is (void) const { return (nullptr != this->Ptr()); }
#endif

const
TOutputs& CAdapter::Outputs (void) const { return this->m_outs; }
err_code  CAdapter::Outputs (void) {
	this->m_error << __METHOD__ << __s_ok;

	if (false == this->Is())
		return this->m_error << __e_not_inited;

	if (this->m_outs.empty() == false)
		this->m_outs.clear();

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-idxgiadapter-enumoutputs ;
	uint32_t n_index = 0;
	TOutputPtr p_out;

	TAdaptDxgPtr p_dxg;
	this->m_error << this->Ptr()->QueryInterface(__uuidof(TAdaptDxgPtr), (void**)&p_dxg);
	if (this->Error())
		return this->Error();

	err_code n_result = __s_ok;
	do {
		n_result = p_dxg->EnumOutputs(n_index, &p_out);
		if (DXGI_ERROR_NOT_FOUND == n_result)
			break;
		else if (__failed(n_result)) {
			this->m_error << n_result;
			break;
		}

		COutput output;
		output.Ptr(p_out/*.Detach()*/);
		try {
			this->m_outs.push_back(output);
		}
		catch (const ::std::bad_alloc&) {
			this->m_error << __e_no_memory;
			break;
		}

		n_index += 1;
	} while (false == this->Error());

	return this->Error();
}

#if defined(_DEBUG)
CString   CAdapter::Print(const e_print _e_opt, _pc_sz _p_pfx, _pc_sz _p_sfx) const {
	_e_opt; _p_pfx; _p_sfx;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{desc=%s;luid=%d;props=%s;output=%s;valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{desc=%s;luid=%d;props=%s;output=%s;valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{desc=%s;luid=%d;props=%s;output=%s;valid=%s}");

	CString cs_desc(this->Info().Description);
	if (cs_desc.IsEmpty())
		cs_desc = _T("#not_set");

	CString cs_valid = TStringEx().Bool(this->Is());
	CString cs_props = this->Props().Print(e_print::e_req);
	CString cs_outs  = this->Outputs().empty() ? _T("#undef") : _T("");

	if (this->Outputs().empty())
		cs_outs = _T("#undef");
	else {
		for (size_t i_ = 0; i_ < this->Outputs().size(); i_++) {
			const COutput& output = this->Outputs().at(i_);
			if (cs_outs.IsEmpty() == false)
				cs_outs += _T("|");
				cs_outs += output.Print(e_print::e_req);
		}
		cs_outs = TStringEx().Format(_T("{%s}"), (_pc_sz) cs_outs);
	}

	CString cs_out;
	if (e_print::e_all   == _e_opt) {
		cs_out.Format(pc_sz_pat_a,
			(_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)cs_desc, this->Info().AdapterLuid.LowPart, (_pc_sz)cs_props, (_pc_sz)cs_outs, (_pc_sz)cs_valid
		);
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n,
			(_pc_sz)__CLASS__, (_pc_sz)cs_desc, this->Info().AdapterLuid.LowPart, (_pc_sz)cs_props, (_pc_sz)cs_outs, (_pc_sz)cs_valid
		);
	}
	if (e_print::e_req   == _e_opt) {
		cs_out.Format(pc_sz_pat_r, 
			(_pc_sz)cs_desc, this->Info().AdapterLuid.LowPart, (_pc_sz)cs_props, (_pc_sz)cs_outs, (_pc_sz)cs_valid
		);
	}

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif

const
CProps&   CAdapter::Props(void) const { return this->m_props; }
CProps&   CAdapter::Props(void)       { return this->m_props; }

const
TAdapterPtr& CAdapter::Ptr (void) const { return this->m_p_obj; }
err_code     CAdapter::Ptr (const TAdapterPtr& _p_ptr) {
	_p_ptr;
	this->m_error << __METHOD__ << __s_ok;

	if (this->Is())
		return this->m_error << (err_code)TErrCodes::eObject::eExists;

	if (nullptr == _p_ptr)
		return this->m_error << __e_pointer;

	using CFac_6 = ex_ui::draw::direct_x::_12::CFac_6;

	this->m_p_obj = _p_ptr;
	this->UpdateInfo();
	// updates the supporting dx12;
	this->Props().Dx_12(__succeeded(::D3D12CreateDevice(_p_ptr, D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr)));
	this->Props().Hi_Perf(CFac_6().Is_Hi_Perf(this->Info().AdapterLuid.LowPart));
	this->Props().Lo_Power(CFac_6().Is_Lo_Power(this->Info().AdapterLuid.LowPart));

	this->Outputs(); // adapter outputs are updated;

	return this->Error();
}

err_code  CAdapter::UpdateInfo (void) {
	this->m_error << __METHOD__ << __s_ok;

	if (false == this->Is())
		return this->m_error << __e_not_inited;

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-idxgiadapter-getdesc ;

	this->m_error << this->Ptr()->GetDesc(&this->Info());
	
	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////

CAdapter& CAdapter::operator = (const CAdapter& _src) { *this << _src.Ptr() << _src.Info(); return *this; }

CAdapter& CAdapter::operator = (CAdapter&& _victim) {
	_victim;
	*this = (const CAdapter&)_victim; // clear operation is made automatically on destroying the input object;
	return *this;
}

CAdapter& CAdapter::operator <<(const TAdapterPtr&  _p_ptr ) { this->Ptr(_p_ptr); return *this; }
CAdapter& CAdapter::operator <<(const TAdaInfoWarp& _p_info) { this->Info() = _p_info; return *this; }

/////////////////////////////////////////////////////////////////////////////

CAdapter_Enum:: CAdapter_Enum (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CAdapter_Enum:: CAdapter_Enum (const CAdapter_Enum& _src) : CAdapter_Enum() { *this = _src; }

/////////////////////////////////////////////////////////////////////////////
const
TAdapters& CAdapter_Enum::Cached (void) const { return this->m_cached; }

TErrorRef  CAdapter_Enum::Error (void) const { return this->m_error; }

err_code   CAdapter_Enum::GetWarp (CAdapter& _adapter) {
	this->m_error << __METHOD__ << __s_ok;

	if (_adapter.Is())
		return (this->m_error << __e_invalid_arg) = _T("The input adapter is already created;");
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_3/nf-dxgi1_3-createdxgifactory2 << for loading debug dll;
	// https://stackoverflow.com/questions/42354369/idxgifactory-versions ;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_3/nf-dxgi1_3-createdxgifactory2 ;
	TFac4Ptr p_fac_4;

	this->m_error << ::CreateDXGIFactory2(0, __uuidof(TFac4Ptr), (void**)&p_fac_4);
	if (true == this->Error()) {
		return  this->Error();
	}

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgiadapter ;
	TWarpPtr warp_ptr;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_4/nf-dxgi1_4-idxgifactory4-enumwarpadapter ;
	this->m_error << p_fac_4->EnumWarpAdapter(__uuidof(TAdapterPtr), (void**)&warp_ptr);
	if (true == this->Error()) {
		return  this->Error();
	}
	else
		_adapter.Ptr(warp_ptr/*.Detach()*/);

	return this->Error();
}

err_code   CAdapter_Enum::Set (void) {
	this->m_error << __METHOD__ << __s_ok;

	CFac_0 fac_0;
	fac_0.Create();
	if (fac_0.Error())
		return this->m_error = fac_0.Error();

	if (this->m_cached.empty() == false)
		this->m_cached.clear();

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-idxgifactory-enumadapters ;
	uint32_t n_index = 0;
	TAdapterPtr p_adapter;

	err_code n_result = __s_ok;

	do {
		n_result =  fac_0.Ptr()->EnumAdapters(n_index, &p_adapter);
		if (DXGI_ERROR_NOT_FOUND == n_result)
			break;

		CAdapter adapter;
		adapter.Ptr(p_adapter/*.Detach()*/);

		try {	
			this->m_cached.push_back(adapter);
		}
		catch (const ::std::bad_alloc&) {
			this->m_error << __e_no_memory;
			break;
		}
		n_index += 1;
	} while (false == this->Error());

	return this->Error();
}


/////////////////////////////////////////////////////////////////////////////

CAdapter_Enum&  CAdapter_Enum::operator = (const CAdapter_Enum& _src) { _src; return *this; }