/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Apr-2025 at 22:14:50.198, UTC+4, Batumi, Monday;
	This is Ebo Pack DirectX 11 adapter wrapper interface implementation file;
*/
#include "direct_x.adapter.1.h"
#include "direct_x.factory.h"

using namespace ex_ui::draw::direct_x::_11;

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
#if (0)
	bool b_is_fast = false;
	TFac6Ptr p_fac_6;
	if (__s_ok == (factory_4->QueryInterface(IID_PPV_ARGS(&p_fac_6)))) {
		CAdapter_Finder finder;
		if (__succeeded(finder.IsFast(p_fac_6, warp_info.AdapterLuid, b_is_fast))) {
	
		}
	}
#endif
	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////

CWarp_Enum&  CWarp_Enum::operator = (const CWarp_Enum& _src) { _src; return *this; }