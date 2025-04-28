#ifndef _DIRECT_X_TARGET_H_INCLUDED
#define _DIRECT_X_TARGET_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Apr-2025 at 18:26:29.828, UTC+4, Batumi, Saturday;
	This is Ebo Pack DirectX renderer target view wrapper interface declaration file; 
*/
#include "direct_x._iface.h"
#include "direct_x.device.1.h"
#include "direct_x.format.h"
#include "direct_x.swap.1.h"
#include "direct_x.swap.2.h"
#include "direct_x.texture.h"

namespace ex_ui { namespace draw { namespace direct_x {

namespace _11 {
	using namespace ex_ui::draw::direct_x;
	using CDevice = ex_ui::draw::direct_x::_11::CDevice;
	using CSwapChain = ex_ui::draw::direct_x::_11::CSwapChain;
	using CTexture = ex_ui::draw::direct_x::_11::_2D::CTexture;
	using TResPtr  = ex_ui::draw::direct_x::_11::_2D::TResPtr;

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_rtv_dimension ;
	typedef D3D11_RTV_DIMENSION TViewDim;

#define TViewDimAlias D3D11_RTV_DIMENSION

	class CViewDims {
	public:
		enum ToAccessAs : uint32_t {
		e_not_use       = TViewDim::D3D11_RTV_DIMENSION_UNKNOWN         , // not applicable; leads to fail of CreateRenderTargetView();
		e_buffer        = TViewDim::D3D11_RTV_DIMENSION_BUFFER          , // a resource will be accessed as a buffer;
		e_tex_1D        = TViewDim::D3D11_RTV_DIMENSION_TEXTURE1D       , // a resource will be accessed as a 1D texture;
		e_tex_1D_arr    = TViewDim::D3D11_RTV_DIMENSION_TEXTURE1DARRAY  , // a resource will be accessed as a 1D texture array;
		e_tex_2D        = TViewDim::D3D11_RTV_DIMENSION_TEXTURE2D       , // a resource will be accessed as a 2D texture;
		e_tex_2D_arr    = TViewDim::D3D11_RTV_DIMENSION_TEXTURE2DARRAY  , // a resource will be accessed as a 2D texture array;
		e_tex_2D_ms     = TViewDim::D3D11_RTV_DIMENSION_TEXTURE2DMS     , // a resource will be accessed as a 2D texture with multisampling;
		e_tex_2D_ms_arr = TViewDim::D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY, // a resource will be accessed as a 2D texture with multisampling array;
		e_tex_3D        = TViewDim::D3D11_RTV_DIMENSION_TEXTURE3D       , // a resource will be accessed as a 3D texture;
		};
	public:
		 CViewDims (void) = default; CViewDims (const CViewDims&) = delete; CViewDims (CViewDims&&) = delete;
		~CViewDims (void) = default;
#if defined(_DEBUG)
	public:
		static CString Print (const uint32_t _e_to_access_as);
#endif
	private:
		CViewDims&  operator = (const CViewDims&) = delete;
		CViewDims&  operator = (CViewDims&&) = delete;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_render_target_view_desc ;
	typedef D3D11_RENDER_TARGET_VIEW_DESC TViewDesc;
	typedef ::ATL::CComPtr<ID3D11RenderTargetView> TViewPtr;

	class CViewDesc {
	public:
		 CViewDesc (void) ; CViewDesc (const CViewDesc&) = delete; CViewDesc (CViewDesc&&) = delete;
		~CViewDesc (void) = default;

	public:
#if defined(_DEBUG)
		static
		CString   Print (const TViewDesc&, const e_print = e_print::e_all);
		CString   Print (const e_print = e_print::e_all) const;
#endif
		const
		TViewDesc& Raw (void) const;
		TViewDesc& Raw (void) ;

	private:
		CViewDesc& operator = (const CViewDesc&) = delete;
		CViewDesc& operator = (CViewDesc&&) = delete;
	private:
		TViewDesc m_desc;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_viewport ;
	typedef D3D11_VIEWPORT TViewPort;

	class CViewPort {
	public:
		 CViewPort (void); CViewPort (const CViewPort&) = delete; CViewPort (CViewPort&&) = delete;
		~CViewPort (void) {}

	public:
	#if defined(_DEBUG)
		static
		CString  Print (const TViewPort&, const e_print);
		CString  Print (const e_print);
	#endif
		const
		TViewPort& Raw (void) const;
		TViewPort& Raw (void) ;

		err_code   SetSize(HWND const _target);

	private:
		CViewPort& operator = (const CViewPort&) = delete;
		CViewPort& operator = (CViewPort&&) = delete;

	private:
		TViewPort m_port;
	};

	// this is a render target for drawing;
	class CTarget {
	public:
		 CTarget (void) ; CTarget (const CTarget&) = delete; CTarget (CTarget&&) = delete;
		~CTarget (void) = default;

	public:
		/*
		// https://learn.microsoft.com/en-us/windows/win32/direct3dgetstarted/work-with-dxgi#create-a-render-target-for-drawing ;
		// the following reqs must be met:
		// (1) resources are either Texture2D or Texture2DArray;
		// (2) the dimention of the desc must be set to either D3D11_RTV_DIMENSION_TEXTURE2D or D3D11_RTV_DIMENSION_TEXTURE2DARRAY;
		// (3) the format must be set to DXGI_FORMAT_R8G8B8A8_UNORM or similar;
		// (4) the buffer usage to DXGI_USAGE_RENDER_TARGET_OUTPUT;

		// *very important*:
			the Z-buffer or 2D-texture that inirets a resource interface is created by swap and chain object;
			the target is created by the device, the device uses the Z-buffer being created above!
		*/
		err_code  Create(void) ;
		const
		CViewDesc& Desc (void) const;
		CViewDesc& Desc (void) ;

		err_code  Draw  (const CClr_Float&) ;

		TError&   Error (void) const;
		bool   Is_valid (void) const;

#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
		const
		CViewPort& Port (void) const;
		CViewPort& Port (void) ;

		const
		TViewPtr& Ptr (void) const;
		err_code  Ptr (const TViewPtr&, const bool _b_upd_desc);

		err_code  Set (const CDevice&);     // does care in case when a device is already cached;
		err_code  Set (const CTexture&);    // does care in case when a texture is already cached;

		err_code  UpdateDesc (void);

	public:
		CTarget&  operator <<(const CDevice&);
		CTarget&  operator <<(const CTexture&);

	private:
		CTarget&  operator = (const CTarget&) = delete;
		CTarget&  operator = (CTarget&&) = delete;

	private:
		CError     m_error;
		CDevice    m_device;  // cached device object;
		CTexture   m_texture; // cached texture object;
		TViewPtr   m_view;
		CViewDesc  m_desc;
		CViewPort  m_port;
	};

}
namespace _12 {}

}}}

#endif/*_DIRECT_X_TARGET_H_INCLUDED*/