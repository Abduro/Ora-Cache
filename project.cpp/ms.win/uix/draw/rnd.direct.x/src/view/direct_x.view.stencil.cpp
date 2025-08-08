/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Apr-2025 at 18:11:35.038, UTC+4, Batumi, Wednesday;
	This is Ebo Pack DirectX depth stencil view wrapper interface implementation file;
*/
#include "direct_x.view.stencil.h"

using namespace ex_ui::draw::direct_x::views;
using namespace ex_ui::draw::direct_x::views::_11;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace direct_x { namespace _impl {
#if defined(_DEBUG)
	// there is some code duplication with render target view description structure;

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_tex1d_dsv ;
	using TDsv_1D = D3D11_TEX1D_DSV ;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_tex1d_array_dsv ;
	using TDsv_1D_arr = D3D11_TEX1D_ARRAY_DSV ;
	// https://learn.microsoft.com/en-us/windows/desktop/api/d3d11/ns-d3d11-d3d11_tex2d_dsv ;
	using TDsv_2D = D3D11_TEX2D_DSV ;
	// https://learn.microsoft.com/en-us/windows/desktop/api/d3d11/ns-d3d11-d3d11_tex2d_array_dsv ;
	using TDsv_2D_arr = D3D11_TEX2D_ARRAY_DSV ;
	// https://learn.microsoft.com/en-us/windows/desktop/api/d3d11/ns-d3d11-d3d11_tex2dms_dsv ;
	using TDsv_2D_ms = D3D11_TEX2DMS_DSV ;  // *important*: it is not used;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_tex2dms_array_rtv ;
	using TDsv_2D_ms_arr = D3D11_TEX2DMS_ARRAY_DSV;
	
	class CDesc_Fmt {
	public:
		 CDesc_Fmt (void){}; CDesc_Fmt (const CDesc_Fmt&) = delete; CDesc_Fmt (CDesc_Fmt&&) = delete;
		~CDesc_Fmt (void){}
	public:
		CString Flags (const uint32_t _n_value) {
			CString cs_out;
			switch (_n_value) {
			case TDsvFlag::D3D11_DSV_READ_ONLY_DEPTH  : cs_out = _T("rd:depth"); break;
			case TDsvFlag::D3D11_DSV_READ_ONLY_STENCIL:	cs_out = _T("rd:stencil"); break;
			case 0: cs_out = _T("rw-accept"); break;
			default:
				cs_out.Format(_T("#inv_arg=%u"), _n_value);
			}
			return  cs_out;
		}
		CString Tex_1D (const TDsv_1D& _tex_1d) {
			_tex_1d;
			CString cs_out; cs_out.Format(_T("tex_1d:{slice=%u}"), _tex_1d.MipSlice);
			return  cs_out;
		}
		CString Tex_1D_arr (const TDsv_1D_arr& _tex_arr) {
			_tex_arr;
			CString cs_out;
			        cs_out.Format(_T("tex_1d_arr:{slice=%u;ndx=%u;size=%u}"), _tex_arr.MipSlice, _tex_arr.FirstArraySlice, _tex_arr.ArraySize);
			return  cs_out;
		}
		CString Tex_2D (const TDsv_2D& _tex_2d) {
			_tex_2d;
			CString cs_out; cs_out.Format(_T("tex_2d:{slice=%u}"), _tex_2d.MipSlice);
			return  cs_out;
		}
		CString Tex_2D_arr (const TDsv_2D_arr& _tex_arr) {
			_tex_arr;
			CString cs_out;
			        cs_out.Format(_T("tex_2d_arr:{slice=%u;ndx=%u;size=%u}"), _tex_arr.MipSlice, _tex_arr.FirstArraySlice, _tex_arr.ArraySize);
			return  cs_out;
		}
		CString Tex_2D_ms (const TDsv_2D_ms& _tex_ms) {
			_tex_ms;
			CString cs_out;
			        cs_out.Format(_T("tex_2d_ms:{ndx=%u;size=%u}"), 0, 0);
			return  cs_out;
		}
		CString Tex_2D_ms_arr (const TDsv_2D_ms_arr& _ms_arr) {
			_ms_arr;
			CString cs_out;
			        cs_out.Format(_T("tex_3d:{slice=%u;size=%u}"), _ms_arr.FirstArraySlice, _ms_arr.ArraySize);
			return  cs_out;
		}

	private:
		CDesc_Fmt& operator = (const CDesc_Fmt&) = delete;
		CDesc_Fmt& operator = (CDesc_Fmt&&) = delete;
	};
#endif
}}}}
using namespace ex_ui::draw::direct_x::_impl;
/////////////////////////////////////////////////////////////////////////////

CDsvDesc:: CDsvDesc (void) : m_desc{0}{}

/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
CString    CDsvDesc::Print (const TDsvDesc& _desc, const e_print _e_opt) {
	_desc; _e_opt;
	/*
		DXGI_FORMAT         Format;        << https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_format_support ;
		D3D11_DSV_DIMENSION ViewDimension; << https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_dsv_dimension  ;
		UINT                Flags;         << https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_dsv_flag       ;
		union {
			D3D11_TEX1D_DSV         Texture1D;
			D3D11_TEX1D_ARRAY_DSV   Texture1DArray;
			D3D11_TEX2D_DSV         Texture2D;
			D3D11_TEX2D_ARRAY_DSV   Texture2DArray;
			D3D11_TEX2DMS_DSV       Texture2DMS;
			D3D11_TEX2DMS_ARRAY_DSV Texture2DMSArray;
		};
	*/
	static _pc_sz pc_sz_pat = _T("fmt=%s;%s;");

	using ToAccessAs = CDsvDims::ToAccessAs;

	CString cs_fmt = CClrBits::Print(_desc.Format);
	CString cs_dim = CDsvDims::Print(_desc.ViewDimension);
	CString cs_flg = CDesc_Fmt().Flags(_desc.Flags);

	CString cs_desc;
	        cs_desc.Format(_T("fmt=%s;%s;flag:%s;"), (_pc_sz) cs_fmt, (_pc_sz) cs_dim, (_pc_sz) cs_flg);

	switch (_desc.ViewDimension) {
	case ToAccessAs::e_unknown   : cs_desc += _T("#not_used");  break;
	case ToAccessAs::e_tex_1d    : cs_desc += CDesc_Fmt().Tex_1D(_desc.Texture1D);  break;
	case ToAccessAs::e_tex_1d_arr: cs_desc += CDesc_Fmt().Tex_1D_arr(_desc.Texture1DArray);  break;
	case ToAccessAs::e_tex_2d    : cs_desc += CDesc_Fmt().Tex_2D(_desc.Texture2D);  break;
	case ToAccessAs::e_tex_2d_arr: cs_desc += CDesc_Fmt().Tex_2D_arr(_desc.Texture2DArray);  break;
	case ToAccessAs::e_tex_2d_ms : cs_desc += _T("#not_used");  break;
	case ToAccessAs::e_tex_ms_arr: cs_desc += CDesc_Fmt().Tex_2D_ms_arr(_desc.Texture2DMSArray);  break;
	default:;
	}

	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{%s}");
	static _pc_sz pc_sz_pat_r = _T("%s");

	CString cs_out = cs_desc;

	if (e_print::e_all   == _e_opt){ cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)cs_desc); }
	if (e_print::e_no_ns == _e_opt){ cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz)cs_desc); }
	if (e_print::e_req   == _e_opt){ cs_out.Format(pc_sz_pat_r, (_pc_sz)cs_desc); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
CString    CDsvDesc::Print (const e_print _e_opt) const {
	return CDsvDesc::Print (this->Raw() , _e_opt);
}
#endif
const
TDsvDesc&  CDsvDesc::Raw (void) const { return this->m_desc; }
TDsvDesc&  CDsvDesc::Raw (void)       { return this->m_desc; }

/////////////////////////////////////////////////////////////////////////////

#if defined(_DEBUG)

CString    CDsvDims::Print (const uint32_t _n_dim) {
	_n_dim;
	static _pc_sz pc_sz_pat = _T("dim=%d(%s)");
	CString cs_out;
	switch (_n_dim) {
	case CDsvDims::ToAccessAs::e_unknown    : cs_out.Format(pc_sz_pat, _n_dim, _T("unknown"))   ; break;
	case CDsvDims::ToAccessAs::e_tex_1d     : cs_out.Format(pc_sz_pat, _n_dim, _T("tex_1d"))    ; break;
	case CDsvDims::ToAccessAs::e_tex_1d_arr : cs_out.Format(pc_sz_pat, _n_dim, _T("tex_1d_arr")); break;
	case CDsvDims::ToAccessAs::e_tex_2d     : cs_out.Format(pc_sz_pat, _n_dim, _T("tex_2d"))    ; break;
	case CDsvDims::ToAccessAs::e_tex_2d_arr : cs_out.Format(pc_sz_pat, _n_dim, _T("tex_2d_arr")); break;
	case CDsvDims::ToAccessAs::e_tex_2d_ms  : cs_out.Format(pc_sz_pat, _n_dim, _T("tex_ms"))    ; break;
	case CDsvDims::ToAccessAs::e_tex_ms_arr : cs_out.Format(pc_sz_pat, _n_dim, _T("tex_ms_arr")); break;
	default:
		cs_out.Format(_T("#inv_arg=%d"), _n_dim);
	}
	return  cs_out;
}

#endif

/////////////////////////////////////////////////////////////////////////////

CStencil:: CStencil (void) : TBase() { TBase::m_error >> __CLASS__; }

/////////////////////////////////////////////////////////////////////////////

#if defined(_DEBUG)
err_code   CStencil::Create (const bool _b_create_tex) {
	_b_create_tex;
	TBase::m_error << __METHOD__  << __s_ok;

	if (false == TBase::m_device.Is_valid()) {
		return TBase::m_error << (err_code) TErrCodes::eObject::eHandle = _T("The device is not valid;");
	}

	if (false == TBase::m_texture.Is_valid()){

		using TTexDesc = ex_ui::draw::direct_x::_11::_2D::TTexDesc;
		TTexDesc& desc = this->m_texture.Desc().Raw();

		desc.Width     = 256;
		desc.Height    = 256;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;
		desc.SampleDesc.Count   = 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage          = D3D11_USAGE_DEFAULT;
		desc.BindFlags      = D3D11_BIND_DEPTH_STENCIL;
		desc.CPUAccessFlags = 0; 
		desc.MiscFlags      = 0;
#if (0)
		using TTexPtr = ex_ui::draw::direct_x::_11::_2D::TTexPtr;
		TTexPtr p_tex;
#endif
		TBase::m_error << TBase::m_device.Get(TBase::m_texture);
		if (TBase::Error())
			return TBase::Error();
	}
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11device-createdepthstencilview ;
	TStenPtr p_sten_raw;
	TResPtr  p_res;

	TBase::m_error << TBase::m_texture.Parent(p_res);
	if (TBase::Error())
		return TBase::Error();
	// no reference to the description must be provided, otherwise the error is thrown: invalid parameter;
	TBase::m_error << TBase::m_device.Ptr()->CreateDepthStencilView(
			p_res, /*&this->Desc().Raw()*/nullptr, &p_sten_raw
		);

	if (TBase::Error())
		return TBase::Error();

	this->Ptr(p_sten_raw, true); // updates a stencil view description; ToDo: using Detouch() is not good approach;

	return TBase::Error();
}
#else
err_code   CStencil::Create (void) {
	TBase::m_error << __METHOD__  << __s_ok;

	if (false == TBase::m_device.Is_valid()) {
	      return TBase::m_error << (err_code) TErrCodes::eObject::eHandle = _T("The device is not valid;");
	}

	if (false == TBase::m_texture.Is_valid()){
	      return TBase::m_error << (err_code) TErrCodes::eObject::eHandle = _T("The texture is not valid;");
	}

	return TBase::Error();
}
#endif
const
CDsvDesc&  CStencil::Desc (void) const { return this->m_desc; }
CDsvDesc&  CStencil::Desc (void)       { return this->m_desc; }
#if defined(_DEBUG)
CString    CStencil::Print(const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{desc={%s};valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{desc={%s};valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("desc=%s;valid={%s}");

	CString cs_desc  = CDsvDesc::Print(this->Desc().Raw(), e_print::e_req);
	CString cs_valid = TStringEx().Bool(this->Is_valid());

	CString cs_out;
	if (e_print::e_all == _e_opt) {
		cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)cs_desc, (_pc_sz)cs_valid);
	}
	if (e_print::e_no_ns == _e_opt) {
		cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz)cs_desc, (_pc_sz)cs_valid);
	}
	if (e_print::e_req == _e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz)cs_desc, (_pc_sz)cs_valid); }

	if (true == cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);
	return  cs_out;
}
#endif
const
TStenPtr&  CStencil::Ptr  (void) const { return this->m_p_sten; }
err_code   CStencil::Ptr  (const TStenPtr& _p_sten, const bool _b_update_desc) {
	_p_sten; _b_update_desc;
	TBase::m_error << __METHOD__ << __s_ok;

	if (nullptr == _p_sten)
		return TBase::m_error << __e_pointer;

	if (this->Is_valid())
		return TBase::m_error << (err_code) TErrCodes::eObject::eExists;

	this->m_p_sten = _p_sten;
	if (_b_update_desc)
		this->UpdateDesc();

	return TBase::Error();
}

err_code   CStencil::UpdateDesc (void) {
	TBase::m_error << __METHOD__  << __s_ok;

	if (false == this->Is_valid())
		return TBase::m_error << __e_not_inited;

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11depthstencilview-getdesc ;
	this->Ptr()->GetDesc(&this->Desc().Raw());

	return TBase::Error();
}

bool  CStencil::Is_valid (void) const {
	return nullptr != this->Ptr();
}