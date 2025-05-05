#ifndef _DIRECT_X_SWAP_1_H_INCLUDED
#define _DIRECT_X_SWAP_1_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Apr-2025 at 16:59:11.021, UTC+4, Batumi, Wednesday;
	This is Ebo Pack DirectX 11 swap chain wrapper interface declaration file;
*/
#include "direct_x.swap.h"
#include "direct_x.texture.h"

namespace ex_ui { namespace draw { namespace direct_x { namespace _11 {

	using namespace ex_ui::draw::direct_x;
	using CSize_U = geometry::base::_2D::CSize_U;

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ns-dxgi-dxgi_swap_chain_desc ;
	typedef DXGI_SWAP_CHAIN_DESC TSwapDesc;

	class CDesc_Wrap {
	public:
		 CDesc_Wrap (void);
		 CDesc_Wrap (const CDesc_Wrap&); CDesc_Wrap (CDesc_Wrap&&) = delete;
		~CDesc_Wrap (void) = default;

	public:
#if defined(_DEBUG)
		// if the target window handle is provided the render target view is updated;
		// if the sync refresh is true ;
		void Fake (const HWND _h_target = nullptr, const bool _b_sync_refresh = true);
#endif
		TError&   Error (void) const;
		bool   Is_valid (void) const;
		const
		TSwapDesc&  ref (void) const;
		TSwapDesc&  ref (void)      ;  // when changing data of this desc struct sets this way the error object is not updated;
#if defined(_DEBUG)
		static
		CString     Print (const TSwapDesc&, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n"));
		CString     Print (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
		err_code    Set  (const TSwapDesc&); // preferable way to update desc data structure; target window handle is checked;

		const
		CSize_U&    Size (void) const;       // gets a reference to a preferable size of the client area of the target view window; (ra)
		CSize_U&    Size (void) ;            // gets a reference to a preferable size of the client area of the target view window; (rw)
		HWND const  Target (void) const;     // gets render target view window handle;
		err_code    Target (HWND const);     // sets render targer view window handle;

	public:
		CDesc_Wrap& operator = (const CDesc_Wrap& _src);
		CDesc_Wrap& operator = (CDesc_Wrap&& _victim) = delete;
		CDesc_Wrap& operator <<(const TSwapDesc&);
		CDesc_Wrap& operator <<(HWND const _h_target);

		operator const TSwapDesc& (void) const;
		operator       TSwapDesc& (void)      ;

	public:
		static err_code Is_valid (const TSwapDesc&);

	private:
		mutable
		CError     m_error;
		TSwapDesc  m_desc;
		CSize_U    m_size;  // target view size in pixels;
	};

	typedef ::std::shared_ptr<CDesc_Wrap> TDescWrapPtr;

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgiswapchain ;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-idxgiswapchain-getdesc ;

	typedef ::ATL::CComPtr<IDXGISwapChain> TChainPtr;
	// https://www.allacronyms.com/buffer/abbreviated ;
	using TZBuffer  = ex_ui::draw::direct_x::_11::_2D::CTexture;
	using TZBuffPtr = ex_ui::draw::direct_x::_11::_2D::TTexPtr ;

	class CSwapChain {
	public:
		 CSwapChain (void);
		 CSwapChain (const CSwapChain&);
		 CSwapChain (CSwapChain&&) = delete;      // is not required yet;
		~CSwapChain (void) = default;

	public:
		const
		CDesc_Wrap& Desc (void) const;
		CDesc_Wrap& Desc (void) ;

		TError& Error (void) const;
		bool  Is_valid(void) const;
		bool  Is_full_screen (void) const;

		err_code GetZBuffer(TZBuffer&); // https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-idxgiswapchain-getbuffer ;

		const
		TChainPtr&  Ptr (void) const;
		err_code    Ptr (const TChainPtr&, const bool _upd_desc) ;
#if defined (_DEBUG)
		CString     Print (const e_print = e_print::e_all) const;
#endif
		err_code    UpdateDesc (void) ;
	public:
		CSwapChain& operator = (const CSwapChain&);
		CSwapChain& operator = (CSwapChain&&) = delete; // is not required yet;
		CSwapChain& operator <<(const CDesc_Wrap&);
		CSwapChain& operator <<(const TChainPtr&);

	private:
		mutable
		CError     m_error  ;
		TChainPtr  m_p_chain;
		CDesc_Wrap m_desc   ;
	};
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_2/ns-dxgi1_2-dxgi_swap_chain_desc1 ;
	typedef DXGI_SWAP_CHAIN_DESC1 TSwapDesc_Ex;

	class CDescEx_Wrap {
	public:
		 CDescEx_Wrap (void); CDescEx_Wrap (const CDescEx_Wrap&) = delete; CDescEx_Wrap (CDescEx_Wrap&&) = delete;
		~CDescEx_Wrap (void) = default;

	public:
#if defined(_DEBUG)
		void     Fake (void);            // configures this struct for applying to test cases;
#endif
		bool     Is_valid (void) const;  // checks target window handle for validity only;
		const
		TSwapDesc_Ex& Ref (void) const;
		TSwapDesc_Ex& Ref (void) ;

		HWND const Target (void) const;
		err_code   Target (HWND const);

	public:
		CDescEx_Wrap&  operator <<(HWND const _h_target);

	private:
		CDescEx_Wrap&  operator = (const CDescEx_Wrap&) = delete;
		CDescEx_Wrap&  operator = (CDescEx_Wrap&&) = delete;

	private:
		TSwapDesc_Ex  m_desc;
		HWND  m_target;  // this window handle is for creating the swap chain object;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_2/nn-dxgi1_2-idxgiswapchain1 ;
	typedef ::ATL::CComPtr<IDXGISwapChain1> TChain_ExPtr;

	class CSwapChain_Ex {
	public:
		 CSwapChain_Ex (void); CSwapChain_Ex (const CSwapChain_Ex&) = delete; CSwapChain_Ex (CSwapChain_Ex&&) = delete;
		~CSwapChain_Ex (void) = default;

	public:
		const
		CDescEx_Wrap&  Desc (void) const;
		CDescEx_Wrap&  Desc (void) ;
		TError&  Error (void) const;
		bool  Is_valid (void) const;  // checks target window handle for validity only;

		const
		TChain_ExPtr&  Ptr (void) const;
		err_code       Ptr (const TChain_ExPtr&);

	private:
		CSwapChain_Ex&  operator = (const CSwapChain_Ex&) = delete;
		CSwapChain_Ex&  operator = (CSwapChain_Ex&&) = delete;

	private:
	mutable
		CError m_error;
		CDescEx_Wrap  m_desc;
		TChain_ExPtr  m_p_chain;
	};
}}}}

#endif/*_DIRECT_X_SWAP_1_H_INCLUDED*/