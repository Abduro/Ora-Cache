#ifndef _DIRECT_X_SWAP_H_INCLUDED
#define _DIRECT_X_SWAP_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Apr_2025 at 21:17:32.647, UTC+4, Batumi, Friday;
	This is Ebo Pack DirectX swap chain component wrapper interface declaration file;
*/
#include "direct_x._iface.h"

namespace ex_ui { namespace draw { namespace direct_x {

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_2/nn-dxgi1_2-idxgiswapchain1 ;
	// https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/dxgi-usage ;

	typedef DXGI_SWAP_CHAIN_DESC1 TSwapDesc;
	typedef ::ATL::CComPtr<IDXGISwapChain1> TSwapPtr;

	class CSwapDesc {
	public:
		class CBuffer {
		public:
			 CBuffer (void) = delete;
			 CBuffer (TSwapDesc&);
			 CBuffer (const CBuffer&);
			 CBuffer (CBuffer&&) = delete;
			~CBuffer (void) = default;

		public:
			uint32_t  Count (void) const;      // gets buffer count value;
			bool      Count (const uint32_t);  // sets buffer count value; returns true on change;
			uint32_t  Usage (void) const;      // gets buffer usage value;
			bool      Usage (const uint32_t);  // sets buffer usage value; returns true on change;

		public:
			CBuffer&  operator = (const CBuffer&);
			CBuffer&  operator = (CBuffer&&) = delete;
			CBuffer&  operator <<(const uint32_t _n_count);
			CBuffer&  operator >>(const uint32_t _n_usage);

		private:
			TSwapDesc&  m_desc;
		};
	public:
		 CSwapDesc (void);
		 CSwapDesc (const CSwapDesc&);
		 CSwapDesc (CSwapDesc&&) = delete; // not required yet;
		~CSwapDesc (void) = default;

	public:
		const
		CBuffer&    Buffer (void) const;
		CBuffer&    Buffer (void) ;
		const
		TSwapDesc&  Raw (void) const;
		TSwapDesc&  Raw (void) ;

	public:
		CSwapDesc&  operator = (const CSwapDesc&);
		CSwapDesc&  operator = (CSwapDesc&&) = delete;

		CSwapDesc&  operator <<(const TSwapDesc&);

	private:
		TSwapDesc  m_desc;
		CBuffer    m_buffer;
	};

	class CSwapChain {
	public:
		 CSwapChain (void);
		 CSwapChain (const CSwapChain&);
		 CSwapChain (CSwapChain&&) = delete; // not required yet;
		~CSwapChain (void) = default;

	public:
		TError& Error (void) const;
		bool  Is_valid(void) const;
		const
		TSwapPtr& Ptr (void) const;
		TSwapPtr& Ptr (void) ;

	public:
		CSwapChain& operator = (const CSwapChain&);
		CSwapChain& operator = (CSwapChain&&) = delete; // not required yet;
		CSwapChain& operator <<(const TSwapPtr&);

	private:
		CError   m_error ;
		TSwapPtr m_p_swap;
	};

}}}

#endif/*_DIRECT_X_SWAP_H_INCLUDED*/