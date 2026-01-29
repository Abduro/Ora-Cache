#ifndef _DIRECTX_VIEW_STENCIL_H_INCLUDED
#define _DIRECTX_VIEW_STENCIL_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Apr-2025 at 18:04:58.088, UTC+4, Batumi, Wednesday;
	This is Ebo Pack DirectX depth stencil view wrapper interface declaration file;
*/
#include "direct_x.view.h"

namespace ex_ui { namespace draw { namespace direct_x { namespace views {

namespace _11 {

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_dsv_flag ;
	typedef D3D11_DSV_FLAG TDsvFlag; 

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_depth_stencil_view_desc ;
	typedef D3D11_DEPTH_STENCIL_VIEW_DESC TDsvDesc; // looks like DSV is shorthand for depth stencil view;

	class CDsvDesc {
	public:
		 CDsvDesc (void); CDsvDesc (const CDsvDesc&) = delete; CDsvDesc (CDsvDesc&&) = delete;
		~CDsvDesc (void) = default;

	public:
#if defined(_DEBUG)
		static
		CString   Print (const TDsvDesc&, const e_print = e_print::e_all);
		CString   Print (const e_print = e_print::e_all) const;
#endif
		const
		TDsvDesc& Raw (void) const;
		TDsvDesc& Raw (void) ;

	private:
		CDsvDesc& operator = (const CDsvDesc&) = delete;
		CDsvDesc& operator = (CDsvDesc&&) = delete;

	private:
		TDsvDesc  m_desc;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_dsv_dimension ;
	typedef D3D11_DSV_DIMENSION  TDsvDim; // this enumeration is almost the same with D3D11_RTV_DIMENSION ;
#pragma region __defs_6
#define DimUnknown    D3D11_DSV_DIMENSION_UNKNOWN           //
#define DimTex1D      D3D11_DSV_DIMENSION_TEXTURE1D         //
#define DimTex1D_a    D3D11_DSV_DIMENSION_TEXTURE1DARRAY    //
#define DimTex2D      D3D11_DSV_DIMENSION_TEXTURE2D         //
#define DimTex2D_a    D3D11_DSV_DIMENSION_TEXTURE2DARRAY    //
#define DimTex2D_ms   D3D11_DSV_DIMENSION_TEXTURE2DMS       //
#define DimTex2d_ms_a D3D11_DSV_DIMENSION_TEXTURE2DMSARRAY  //
#pragma endregion
	class CDsvDims {
	public:
		enum ToAccessAs : uint32_t {
		     e_unknown    = TDsvDim::DimUnknown   , // is not a valid value and is not used;
		     e_tex_1d     = TDsvDim::DimTex1D     , // a resource is accessed as a 1D texture;
		     e_tex_1d_arr = TDsvDim::DimTex1D_a   , // a resource is accessed as an array of 1D textures;
		     e_tex_2d     = TDsvDim::DimTex2D     , // a resource is accessed as a 2D texture;
		     e_tex_2d_arr = TDsvDim::DimTex2D_a   , // a resource is accessed as an array of 2D textures;
		     e_tex_2d_ms  = TDsvDim::DimTex2D_ms  , // a resource is accessed as a 2D texture with multisampling;
		     e_tex_ms_arr = TDsvDim::DimTex2d_ms_a, // a resource is accessed as an array of 2D textures with multisampling;
		};
	public:
		 CDsvDims (void) = default; CDsvDims (const CDsvDims&) = delete; CDsvDims (CDsvDims&&) = delete;
		~CDsvDims (void) = default;

	public:
#if defined(_DEBUG)
	static
	CString  Print (const uint32_t _n_dim);
#endif

	private:
		CDsvDims& operator = (const CDsvDims&) = delete;
		CDsvDims& operator = (CDsvDims&&) = delete;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11depthstencilview ;
	// https://learn.microsoft.com/en-us/windows/win32/direct3d11/d3d10-graphics-programming-guide-depth-stencil ;
	typedef ::ATL::CComPtr<ID3D11DepthStencilView>  TStenPtr;

	// https://en.wikipedia.org/wiki/Stencil ;

	class CStencil : public CView { typedef CView TBase;
	public:
		 CStencil (void);  CStencil (const CStencil&) = delete; CStencil (CStencil&&) = delete;
		~CStencil (void) = default;

	public:
	#if defined(_DEBUG)
		err_code  Create (const bool _b_create_tex); // if input arg is 'true', creates a texture if it is not created yet;
	#else
		err_code  Create (void);     // creates depth stencil view by using TBase::device and TBase::texture cached objects;
	#endif
		const
		CDsvDesc& Desc (void) const;
		CDsvDesc& Desc (void) ;
		bool  Is_valid (void) const; // overrides the method of the base class;
	#if defined(_DEBUG)
		CString   Print(const e_print = e_print::e_all) const;
	#endif
		const
		TStenPtr& Ptr  (void) const;
		err_code  Ptr  (const TStenPtr&, const bool _b_update_desc = false);

		err_code  UpdateDesc (void);

	private:
		CStencil& operator = (const CStencil&) = delete;
		CStencil& operator = (CStencil&&) = delete;

	private:
		TStenPtr  m_p_sten;
		CDsvDesc  m_desc;
	};
}

}}}}

#endif/*_DIRECTX_VIEW_STENCIL_H_INCLUDED*/