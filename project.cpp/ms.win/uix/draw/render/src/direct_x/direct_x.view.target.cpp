/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Apr-2025 at 18:30:30.820, UTC+4, Batumi, Saturday;
	This is Ebo Pack DirectX renderer target view wrapper interface implementation file; 
*/
#include "direct_x.view.target.h"

using namespace ex_ui::draw::direct_x;
using namespace ex_ui::draw::direct_x::views;
using namespace ex_ui::draw::direct_x::views::_11;

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace draw { namespace direct_x {
namespace _impl {
#if defined(_DEBUG)
	// concerning a print of a union:
	// https://stackoverflow.com/questions/14285238/can-you-explain-the-results-from-printing-members-of-a-union ;

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_buffer_rtv ;
	using TBuffer = D3D11_BUFFER_RTV; // it has two unions of UINT each of them;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_tex1d_rtv ;
	using TTex_1D = D3D11_TEX1D_RTV ;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_tex1d_array_rtv ;
	using TTex_1D_arr = D3D11_TEX1D_ARRAY_RTV ;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_tex2d_rtv ;
	using TTex_2D = D3D11_TEX2D_RTV ;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_tex2d_array_rtv ;
	using TTex_2D_arr = D3D11_TEX2D_ARRAY_RTV ;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_tex2dms_rtv ;
	using TTex_2D_ms = D3D11_TEX2DMS_RTV ; // it is not used;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_tex2dms_array_rtv ;
	using TTex_2D_ms_arr = D3D11_TEX2DMS_ARRAY_RTV;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_tex3d_rtv ;
	using TTex_3D = D3D11_TEX3D_RTV ;

	class CDesc_Fmt {
	public:
		 CDesc_Fmt (void){}; CDesc_Fmt (const CDesc_Fmt&) = delete; CDesc_Fmt (CDesc_Fmt&&) = delete;
		~CDesc_Fmt (void){}
	public:
		CString Buffer (const TBuffer& _buffer) {
			_buffer; // the input buffer can be concidered as structure that has two UINT fields;
			CString cs_out;
			        cs_out.Format(_T("buffer:{offset=%u;count|width=%u}"), _buffer.FirstElement, _buffer.NumElements);
			return  cs_out;
		}
		CString Tex_1D (const TTex_1D& _tex_1d) {
			_tex_1d;
			CString cs_out; cs_out.Format(_T("tex_1d:{slice=%u}"), _tex_1d.MipSlice);
			return  cs_out;
		}
		CString Tex_1D_arr (const TTex_1D_arr& _tex_arr) {
			_tex_arr;
			CString cs_out;
			        cs_out.Format(_T("tex_1d_arr:{slice=%u;ndx=%u;size=%u}"), _tex_arr.MipSlice, _tex_arr.FirstArraySlice, _tex_arr.ArraySize);
			return  cs_out;
		}
		CString Tex_2D (const TTex_2D& _tex_2d) {
			_tex_2d;
			CString cs_out; cs_out.Format(_T("tex_2d:{slice=%u}"), _tex_2d.MipSlice);
			return  cs_out;
		}
		CString Tex_2D_arr (const TTex_2D_arr& _tex_arr) {
			_tex_arr;
			CString cs_out;
			        cs_out.Format(_T("tex_2d_arr:{slice=%u;ndx=%u;size=%u}"), _tex_arr.MipSlice, _tex_arr.FirstArraySlice, _tex_arr.ArraySize);
			return  cs_out;
		}
		CString Tex_2D_ms (const TTex_2D_ms_arr& _tex_arr) {
			_tex_arr;
			CString cs_out;
			        cs_out.Format(_T("tex_2d_ms:{ndx=%u;size=%u}"), _tex_arr.FirstArraySlice, _tex_arr.ArraySize);
			return  cs_out;
		}
		CString Tex_3D (const TTex_3D& _tex_3d) {
			_tex_3d;
			CString cs_out;
			        cs_out.Format(_T("tex_3d:{slice=%u;depth=%u;levels=%u}"), _tex_3d.MipSlice, _tex_3d.FirstWSlice, _tex_3d.WSize);
			return  cs_out;
		}

	private:
		CDesc_Fmt& operator = (const CDesc_Fmt&) = delete;
		CDesc_Fmt& operator = (CDesc_Fmt&&) = delete;
	};
#endif
}

/////////////////////////////////////////////////////////////////////////////

#if defined(_DEBUG)
CString CTgtDims::Print (const uint32_t  _e_to_access_as) {
	_e_to_access_as;
	CString cs_out;
	switch (_e_to_access_as) {
	case ToAccessAs::e_buffer        : cs_out = _T("dim:e_buffer");        break;
	case ToAccessAs::e_not_use       : cs_out = _T("dim:e_not_use");       break;
	case ToAccessAs::e_tex_1D        : cs_out = _T("dim:e_tex_1D");        break;
	case ToAccessAs::e_tex_1D_arr    : cs_out = _T("dim:e_tex_1D_arr");    break;
	case ToAccessAs::e_tex_2D        : cs_out = _T("dim:e_tex_2D");        break;
	case ToAccessAs::e_tex_2D_arr    : cs_out = _T("dim:e_tex_2D_arr");    break;
	case ToAccessAs::e_tex_2D_ms     : cs_out = _T("dim:e_tex_2D_ms");     break;
	case ToAccessAs::e_tex_2D_ms_arr : cs_out = _T("dim:e_tex_2D_ms_arr"); break;
	case ToAccessAs::e_tex_3D        : cs_out = _T("dim:e_tex_3D");        break;
	default:
		cs_out.Format(_T("dim:#unspec(%d)"), _e_to_access_as);
	}
	return  cs_out;
}
#endif
/////////////////////////////////////////////////////////////////////////////
CTgtDesc:: CTgtDesc (void) : m_desc{0} {}
/////////////////////////////////////////////////////////////////////////////
#if defined(_DEBUG)
CString   CTgtDesc::Print (const TTgtDesc& _desc, const e_print _e_opt) {
	_e_opt;
	using ToAccessAs = CTgtDims::ToAccessAs;
	using CDesc_Fmt  = _impl::CDesc_Fmt;
	CString cs_desc;
	        cs_desc.Format(_T("fmt=%s;%s;"), (_pc_sz)CClrBits().Print(_desc.Format), (_pc_sz)CTgtDims::Print(_desc.ViewDimension));
	switch (_desc.ViewDimension) {
	case ToAccessAs::e_buffer        : cs_desc += CDesc_Fmt().Buffer(_desc.Buffer);  break;
	case ToAccessAs::e_not_use       : cs_desc += _T("#not_used");  break;
	case ToAccessAs::e_tex_1D        : cs_desc += CDesc_Fmt().Tex_1D(_desc.Texture1D);  break;
	case ToAccessAs::e_tex_1D_arr    : cs_desc += CDesc_Fmt().Tex_1D_arr(_desc.Texture1DArray);  break;
	case ToAccessAs::e_tex_2D        : cs_desc += CDesc_Fmt().Tex_2D(_desc.Texture2D);  break;
	case ToAccessAs::e_tex_2D_arr    : cs_desc += CDesc_Fmt().Tex_2D_arr(_desc.Texture2DArray);  break;
	case ToAccessAs::e_tex_2D_ms     : cs_desc += _T("#not_used");  break;
	case ToAccessAs::e_tex_2D_ms_arr : cs_desc += CDesc_Fmt().Tex_2D_ms(_desc.Texture2DMSArray);  break;
	case ToAccessAs::e_tex_3D        : cs_desc += CDesc_Fmt().Tex_3D(_desc.Texture3D);  break;
	}

	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{%s}");
	static _pc_sz pc_sz_pat_r = _T("%s");

	CString cs_out;
	if (e_print::e_all   == _e_opt){ cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)cs_desc); }
	if (e_print::e_no_ns == _e_opt){ cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz)cs_desc); }
	if (e_print::e_req   == _e_opt){ cs_out.Format(pc_sz_pat_r, (_pc_sz)cs_desc); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg=%u);"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _e_opt);

	return  cs_out;
}
CString   CTgtDesc::Print (const e_print _e_opt) const {
   return CTgtDesc::Print (this->Raw() , _e_opt);
}
#endif
const
TTgtDesc& CTgtDesc::Raw (void) const { return this->m_desc; }
TTgtDesc& CTgtDesc::Raw (void)       { return this->m_desc; }

/////////////////////////////////////////////////////////////////////////////

CTarget:: CTarget (void) : TBase() { TBase::m_error >>__CLASS__; }

/////////////////////////////////////////////////////////////////////////////

err_code  CTarget::Create(void) {
	this->m_error << __METHOD__ << __s_ok;

	if (this->Is_valid())
		return this->m_error << (err_code)TErrCodes::eObject::eExists;

	if (false == this->m_device.Is_valid())
		return  (this->m_error << (err_code)TErrCodes::eExecute::eParameter) = _T("The device is invalid");
#if (1)
	if (false == this->m_texture.Is_valid())
		return  (this->m_error << (err_code)TErrCodes::eExecute::eParameter) = _T("The texture is invalid");
#else
	this->m_error << this->m_device.Get(this->m_texture);
	if (this->Error())
		return this->m_error = m_device.Error();

	if (false == this->m_texture.Is_valid())
		return  (this->m_error << (err_code)TErrCodes::eExecute::eParameter) = _T("The texture is invalid");
#endif
	TResPtr p_res;
	this->m_error << this->m_texture.Parent(p_res);
	if (this->Error())
		return this->Error();
#if (0)
	this->Desc().Raw().Format = (TFormatAlias) CClrBits::e_rgba_norm;
	this->Desc().Raw().ViewDimension = (TViewDimAlias) CViewDims::ToAccessAs::e_tex_2D;
#endif
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11device-createrendertargetview ;
	this->m_error << this->m_device.Ptr()->CreateRenderTargetView(
		p_res, /*&this->Desc().Raw()*/nullptr, &this->m_view
	);
	if (this->Error()) // it is required to return this object error, not from device one;
		this->Error();
	else
		this->m_error << this->UpdateDesc();
	// checks the device context object, it is required for calling methods of this context;
	if (this->m_device.Ctx().Is_valid() == false)
		return this->m_error = this->m_device.Ctx().Error();

	ID3D11RenderTargetView* pView = this->m_view;

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11devicecontext-omsetrendertargets ;
	if (this->Error() == false) {
		this->m_device.Ctx().Ptr()->OMSetRenderTargets(1, &pView, nullptr);
		this->m_port.SetSize(this->m_device.SwapChain().Desc().ref().OutputWindow); // does not care about an error for this time;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11devicecontext-rssetviewports ;
		this->m_device.Ctx().Ptr()->RSSetViewports(1, &this->m_port.Raw());
	}

	return this->Error();
}

const
CTgtDesc& CTarget::Desc (void) const { return this->m_desc; }
CTgtDesc& CTarget::Desc (void)       { return this->m_desc; }

bool      CTarget::Is_valid (void) const { return nullptr != this->Ptr(); }

#if defined(_DEBUG)
CString   CTarget::Print (const e_print _e_opt) const {
	_e_opt;
	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{desc={%s};valid=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{desc={%s};valid=%s}");
	static _pc_sz pc_sz_pat_r = _T("{desc={%s};valid=%s}");

	CString cs_desc  = CTgtDesc::Print(this->Desc().Raw(), e_print::e_req);
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
CViewPort& CTarget::Port (void) const { return this->m_port; }
CViewPort& CTarget::Port (void)       { return this->m_port; }
const
TTgtPtr&  CTarget::Ptr (void) const { return this->m_view; }
err_code  CTarget::Ptr (const TTgtPtr& _p_view, const bool _b_upd_desc) {
	_p_view; _b_upd_desc;
	this->m_error << __METHOD__ << __s_ok;
	if (this->Is_valid())
		return this->m_error << (err_code)TErrCodes::eObject::eExists;

	if (nullptr == _p_view)
		return this->m_error << __e_pointer;

	this->m_view =_p_view;

	TViewPtr p_view;
	TBase::m_error << _p_view->QueryInterface(__uuidof(TViewPtr), (void**)&p_view);
	if (false == TBase::Error()) {
		TBase::m_p_view = nullptr;
		TBase::View(p_view);
	}


	if (_b_upd_desc)
		this->UpdateDesc();

	return this->Error();
}

err_code  CTarget::UpdateDesc (void) {
	this->m_error << __METHOD__ << __s_ok;

	if (this->Is_valid() == false)
		return this->m_error << __e_not_inited;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11rendertargetview-getdesc ;
	this->Ptr()->GetDesc(&this->Desc().Raw());

	return this->Error();
}

/////////////////////////////////////////////////////////////////////////////

err_code  CTarget::OnDraw (const CClr_Float& _clr) {
	// it looks like the device object does not require to be checked itself, due to there is no direct call to it here;
	err_code n_result = __s_ok;
	if (this->Is_valid()) {
		if (this->m_device.Ctx().Is_valid()) {
#if (0)
			float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red, green, blue, alpha;
			this->m_device.Ctx().Ptr()->ClearRenderTargetView(this->m_view, ClearColor);
#endif
			this->m_device.Ctx().Ptr()->ClearRenderTargetView(this->m_view, _clr.Get().data());

			if (this->m_device.SwapChain().Is_valid()) {
				// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-idxgiswapchain-present ;
				this->m_device.SwapChain().Ptr()->Present(0, 0);
			}
			else n_result = this->m_device.SwapChain().Error();
		} else n_result = this->m_device.Ctx().Error();
	} else n_result = this->Error();
	return n_result;
}

err_code  CTarget::OnSize (const RECT& _rc_allowed) {
	_rc_allowed;
	// https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/d3d10-graphics-programming-guide-dxgi#handling-window-resizing ;
	err_code n_result = __s_ok;
	if (::IsRectEmpty(&_rc_allowed))
		return (n_result = this->m_error << __e_rect);

	/*
		!attention! this target object must be re-created for applying new output/target rectangle;
		thus, before making this object destroyed each of participants of this operation must be checked;
	*/
	if (false) {}
	else if (false == this->Is_valid()) return n_result = this->Error();
	else if (false == this->m_device.Is_valid()) return n_result = this->m_device.Error();
	else if (false == this->m_device.Ctx().Is_valid()) return n_result = this->m_device.Ctx().Error();
	else if (false == this->m_device.SwapChain().Is_valid()) return n_result = this->m_device.SwapChain().Error();

	// (1) destroys this target view object;
	this->m_view = nullptr;

	// (2) removes bindings;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11devicecontext-omsetrendertargets ;
	this->m_device.Ctx().Ptr()->OMSetRenderTargets(0, nullptr, nullptr);

	// (3) preserves the existing buffer count and format;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-idxgiswapchain-resizebuffers ;
	n_result = this->m_device.SwapChain().Ptr()->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
	if (__failed(n_result)) {
#if defined(_DEBUG)
		this->m_error << n_result;
#endif
#if (0) // ignores the error for now;
		return n_result;
#endif
	}

	// (4) gets the back buffer object, i.e. texture 2D;
	using TTexPtr = ex_ui::draw::direct_x::_11::_2D::TTexPtr;
	TTexPtr p_buffer;

	n_result = this->m_device.SwapChain().Ptr()->GetBuffer(0, __uuidof(TTexPtr), (void**)&p_buffer);
	if (__failed(n_result))
	      return n_result;

	TTgtPtr p_view;
	
	// (5) re-creates the target view; ToDo: the view description data is not updated yet;
	n_result = this->m_device.Ptr()->CreateRenderTargetView(p_buffer, nullptr, &p_view);
	if (__failed(n_result))
	      return n_result;

	this->Ptr(p_view, true);
	if (this->Error())
		return n_result = this->Error();

	ID3D11RenderTargetView* pView = this->m_view;
	this->m_device.Ctx().Ptr()->OMSetRenderTargets(1, &pView, nullptr);

	TViewPort v_port = {
		float(_rc_allowed.left),
		float(_rc_allowed.top ),
		float(_rc_allowed.right - _rc_allowed.left),
		float(_rc_allowed.bottom -_rc_allowed.top ),
		0.0f, 1.0f
	};

	this->m_device.Ctx().Ptr()->RSSetViewports( 1, &v_port );

	return n_result;
}

/////////////////////////////////////////////////////////////////////////////

CTarget&  CTarget::operator <<(const CDevice& _device) { this->m_device = _device; return *this; }
CTarget&  CTarget::operator <<(const CTexture& _texture) { this->Set(_texture); return *this; }

}

namespace _12 {
}

}}