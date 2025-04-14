#ifndef _DIRECT_X_SWAP_1_H_INCLUDED
#define _DIRECT_X_SWAP_1_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Apr-2025 at 16:59:11.021, UTC+4, Batumi, Wednesday;
	This is Ebo Pack DirectX 11 swap chain wrapper interface declaration file;
*/
#include "direct_x.swap.h"

namespace ex_ui { namespace draw { namespace direct_x { namespace _11 {

	using namespace ex_ui::draw::direct_x;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ns-dxgi-dxgi_swap_chain_desc ;
	typedef DXGI_SWAP_CHAIN_DESC TSwapDesc;

	class CDesc_Wrap {
	public:
		 CDesc_Wrap (void);
		 CDesc_Wrap (const CDesc_Wrap&) = delete; CDesc_Wrap (CDesc_Wrap&&) = delete;
		~CDesc_Wrap (void) = default;

	public:

		void Fake (void);

		TError&   Error (void) const;
		bool   Is_valid (void) const;
		const
		TSwapDesc&  ref (void) const;
		TSwapDesc&  ref (void)      ;

		HWND const  Target (void) const;
		err_code    Target (HWND const);

	public:
		CDesc_Wrap& operator <<(HWND const _h_target);

		operator const TSwapDesc& (void) const;
		operator       TSwapDesc& (void)      ;
	
	private:
		mutable
		CError     m_error;
		TSwapDesc  m_desc;
		
	private:
		CDesc_Wrap& operator = (const CDesc_Wrap& _src) = delete;
		CDesc_Wrap& operator = (CDesc_Wrap&& _victim) = delete;
	};

	typedef ::std::shared_ptr<CDesc_Wrap> TDescWrapPtr;

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgiswapchain ;

	typedef ::ATL::CComPtr<IDXGISwapChain> TChainPtr;

	class CSwapChain {
	public:
		 CSwapChain (void);
		 CSwapChain (const CSwapChain&) = delete; // is not required yet;
		 CSwapChain (CSwapChain&&) = delete;      // is not required yet;
		~CSwapChain (void) = default;

	public:
		const
		CDesc_Wrap&  Desc (void) const;
		CDesc_Wrap&  Desc (void) ;

		TError& Error (void) const;
		bool  Is_valid(void) const;
		bool  Is_full_screen (void) const;

		const
		TChainPtr& Ptr (void) const;
		err_code   Ptr (const TChainPtr&) ;
#if defined (_DEBUG)
		CString    Print (const e_print = e_print::e_all) const;
#endif
	public:
		CSwapChain& operator = (const CSwapChain&) = delete; // is not required yet;
		CSwapChain& operator = (CSwapChain&&) = delete;      // is not required yet;
		CSwapChain& operator <<(const TChainPtr&);

	private:
		mutable
		CError     m_error  ;
		TChainPtr  m_p_chain;
		CDesc_Wrap m_desc   ;
	};
}}}}

#endif/*_DIRECT_X_SWAP_1_H_INCLUDED*/