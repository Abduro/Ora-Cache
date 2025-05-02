#ifndef _DIRECT_X_VIEW_TARGET_H_INCLUDED
#define _DIRECT_X_VIEW_TARGET_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Apr-2025 at 18:26:29.828, UTC+4, Batumi, Saturday;
	This is Ebo Pack DirectX renderer target view wrapper interface declaration file; 
*/
#include "direct_x.view.h"

namespace ex_ui { namespace draw { namespace direct_x { namespace views {

namespace _11 {
	using namespace ex_ui::draw::direct_x;

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_rtv_dimension ;
	// https://www.abbreviations.com/abbreviation/Target ;
	typedef D3D11_RTV_DIMENSION TTgtDim;

#define TViewDimAlias D3D11_RTV_DIMENSION
#pragma region __defs_7
#define TgtDim_Unknown     D3D11_RTV_DIMENSION_UNKNOWN          // not applicable; leads to fail of CreateRenderTargetView();
#define TgtDim_Buffer      D3D11_RTV_DIMENSION_BUFFER           // a resource will be accessed as a buffer;
#define TgtDim_Tex_1D      D3D11_RTV_DIMENSION_TEXTURE1D        // a resource will be accessed as a 1D texture;
#define TgtDim_Tex_1D_a    D3D11_RTV_DIMENSION_TEXTURE1DARRAY   // a resource will be accessed as a 1D texture array;
#define TgtDim_Tex_2D      D3D11_RTV_DIMENSION_TEXTURE2D        // a resource will be accessed as a 2D texture;
#define TgtDim_Tex_2D_a    D3D11_RTV_DIMENSION_TEXTURE2DARRAY   // a resource will be accessed as a 2D texture array;
#define TgtDim_Tex_2D_ms   D3D11_RTV_DIMENSION_TEXTURE2DMS      // a resource will be accessed as a 2D texture with multisampling;
#define TgtDim_Tex_2D_ms_a D3D11_RTV_DIMENSION_TEXTURE2DMSARRAY // a resource will be accessed as a 2D texture with multisampling array;
#define TgtDim_Tex_3D      D3D11_RTV_DIMENSION_TEXTURE3D        // a resource will be accessed as a 3D texture;
#pragma endregion
	class CTgtDims {
	public:
		enum ToAccessAs : uint32_t {
		     e_not_use       = TTgtDim::TgtDim_Unknown        , // 
			 e_buffer        = TTgtDim::TgtDim_Buffer         , // 
			 e_tex_1D        = TTgtDim::TgtDim_Tex_1D         , // 
			 e_tex_1D_arr    = TTgtDim::TgtDim_Tex_1D_a       , // 
			 e_tex_2D        = TTgtDim::TgtDim_Tex_2D         , // 
			 e_tex_2D_arr    = TTgtDim::TgtDim_Tex_2D_a       , // 
			 e_tex_2D_ms     = TTgtDim::TgtDim_Tex_2D_ms      , // 
			 e_tex_2D_ms_arr = TTgtDim::TgtDim_Tex_2D_ms_a    , // 
			 e_tex_3D        = TTgtDim::TgtDim_Tex_3D         , // 
		};
	public:
		 CTgtDims (void) = default; CTgtDims (const CTgtDims&) = delete; CTgtDims (CTgtDims&&) = delete;
		~CTgtDims (void) = default;
#if defined(_DEBUG)
	public:
		static CString Print (const uint32_t _e_to_access_as);
#endif
	private:
		CTgtDims&  operator = (const CTgtDims&) = delete;
		CTgtDims&  operator = (CTgtDims&&) = delete;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_render_target_view_desc ;
	typedef D3D11_RENDER_TARGET_VIEW_DESC TTgtDesc;
	typedef ::ATL::CComPtr<ID3D11RenderTargetView> TTgtPtr;

	class CTgtDesc {
	public:
		 CTgtDesc (void) ; CTgtDesc (const CTgtDesc&) = delete; CTgtDesc (CTgtDesc&&) = delete;
		~CTgtDesc (void) = default;

	public:
#if defined(_DEBUG)
		static
		CString   Print (const TTgtDesc&, const e_print = e_print::e_all);
		CString   Print (const e_print = e_print::e_all) const;
#endif
		const
		TTgtDesc& Raw (void) const;
		TTgtDesc& Raw (void) ;

	private:
		CTgtDesc& operator = (const CTgtDesc&) = delete;
		CTgtDesc& operator = (CTgtDesc&&) = delete;
	private:
		TTgtDesc m_desc;
	};

	// this is a render target for drawing;
	class CTarget : public CView { typedef CView TBase;
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
		CTgtDesc& Desc (void) const;
		CTgtDesc& Desc (void) ;

		err_code  Draw  (const CClr_Float&) ;

		bool   Is_valid (void) const;

#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
		const
		CViewPort& Port (void) const;
		CViewPort& Port (void) ;

		const
		TTgtPtr&  Ptr (void) const;
		err_code  Ptr (const TTgtPtr&, const bool _b_upd_desc);

		err_code  UpdateDesc (void);

	public:
		CTarget&  operator <<(const CDevice&);
		CTarget&  operator <<(const CTexture&);

	private:
		CTarget&  operator = (const CTarget&) = delete;
		CTarget&  operator = (CTarget&&) = delete;

	private:
		CError     m_error;
		TTgtPtr    m_view;
		CTgtDesc   m_desc;
		CViewPort  m_port;
	};

}
namespace _12 {}

}}}}

#endif/*_DIRECT_X_VIEW_TARGET_H_INCLUDED*/