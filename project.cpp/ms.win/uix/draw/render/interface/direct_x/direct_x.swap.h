#ifndef _DIRECT_X_SWAP_H_INCLUDED
#define _DIRECT_X_SWAP_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Apr_2025 at 21:17:32.647, UTC+4, Batumi, Friday;
	This is Ebo Pack DirectX swap chain component wrapper interface declaration file;
*/
#include "direct_x._iface.h"

namespace ex_ui { namespace draw { namespace direct_x {

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_2/ne-dxgi1_2-dxgi_alpha_mode ;
	// https://learn.microsoft.com/en-us/windows/win32/api/dcommon/ne-dcommon-d2d1_alpha_mode ;
	typedef DXGI_ALPHA_MODE TAlphaMode;
	class CAlphaMode {
	public:
		enum e_mode : uint32_t {
		     e_unspec   = TAlphaMode::DXGI_ALPHA_MODE_UNSPECIFIED  ,
		     e_premulti = TAlphaMode::DXGI_ALPHA_MODE_PREMULTIPLIED,
		     e_straith  = TAlphaMode::DXGI_ALPHA_MODE_STRAIGHT     ,
		     e_ignore   = TAlphaMode::DXGI_ALPHA_MODE_IGNORE       ,
		};
	public:
		 CAlphaMode (void) = default; CAlphaMode (const CAlphaMode&) = delete; CAlphaMode (CAlphaMode&&) = delete;
		~CAlphaMode (void) = default;

	private:
		CAlphaMode&  operator = (const CAlphaMode&) = delete;
		CAlphaMode&  operator = (CAlphaMode&&) = delete;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgiformat/ne-dxgiformat-dxgi_format ;
	// https://learn.microsoft.com/en-us/windows/win32/api/dcommon/ns-dcommon-d2d1_pixel_format ;
	typedef DXGI_FORMAT TResFormat;
	typedef D2D1_PIXEL_FORMAT TPxFormat;

	// https://learn.microsoft.com/en-us/windows/win32/direct2d/supported-pixel-formats-and-alpha-modes ; << for images and bitmaps;

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ne-dxgi-dxgi_swap_effect ;
	typedef DXGI_SWAP_EFFECT TSwapEffect;
	class CSwpEffect {
	public:
		enum e_value : uint32_t {
		     e_discard  = DXGI_SWAP_EFFECT_DISCARD        ,
		     e_sequent  = DXGI_SWAP_EFFECT_SEQUENTIAL     ,
		     e_flp_seq  = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL,
		     e_flp_disc = DXGI_SWAP_EFFECT_FLIP_DISCARD   ,
		};
	public:
		 CSwpEffect (void) = default; CSwpEffect (const CSwpEffect&) = delete; CSwpEffect (CSwpEffect&&) = delete;
		~CSwpEffect (void) = default;

	private:
		CSwpEffect&  operator = (const CSwpEffect&) = delete;
		CSwpEffect&  operator = (CSwpEffect&&) = delete;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_2/nn-dxgi1_2-idxgiswapchain1 ;
	// https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/dxgi-usage ;

	typedef DXGI_SWAP_CHAIN_DESC1 TSwapDesc;
	typedef ::ATL::CComPtr<IDXGISwapChain1> TSwapPtr;

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgicommon/ns-dxgicommon-dxgi_sample_desc ;

	typedef DXGI_SAMPLE_DESC TSampleDesc;

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_2/ns-dxgi1_2-dxgi_swap_chain_desc1 ;

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
		class CSample {
		public:
			 CSample (void) = delete;
			 CSample (TSwapDesc&);
			 CSample (const CSample&);
			 CSample (CSample&&) = delete;
			~CSample (void) = default;

		public:
			uint32_t Count (void) const;
			bool     Count (const uint32_t);
			uint32_t Quality (void) const;
			bool     Quality (const uint32_t);

			bool Set (const uint32_t _n_count, const uint32_t _n_quality);

			const
			TSampleDesc& Raw (void) const;
			TSampleDesc& Raw (void) ;

		public:
			CSample&  operator = (const CSample&);
			CSample&  operator = (CSample&&) = delete;
			CSample&  operator <<(const uint32_t _n_count);
			CSample&  operator >>(const uint32_t _n_quality);

		private:
			TSwapDesc& m_desc;
		};
		// https://learn.microsoft.com/en-us/windows/win32/direct2d/d2d1-size-u ;
		class CSize {
		public:
			 CSize (void) = delete;
			 CSize (TSwapDesc&);
			 CSize (const CSize&);
			 CSize (CSize&&) = delete;
			~CSize (void) = default;

		public:
			uint32_t Height (void) const;
			bool     Height (const uint32_t);
			uint32_t H (void) const;
			bool     H (const uint32_t);

			uint32_t Width (void) const;
			bool     Width (const uint32_t);
			uint32_t W (void) const;
			bool     W (const uint32_t);

			bool   Set (const uint32_t _n_width, const uint32_t _n_height);

		public:
			CSize& operator = (const CSize&);
			CSize& operator = (CSize&&) = delete;
			CSize& operator <<(const uint32_t _n_width);
			CSize& operator >>(const uint32_t _n_height);

		private:
			TSwapDesc& m_desc;
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
		const
		CSample&  Sample (void) const;
		CSample&  Sample (void) ;
		const
		CSize& Size (void) const;
		CSize& Size (void) ;

	public:
		CSwapDesc&  operator = (const CSwapDesc&);
		CSwapDesc&  operator = (CSwapDesc&&) = delete;

		CSwapDesc&  operator <<(const TSwapDesc&);

	private:
		TSwapDesc  m_desc;
		CBuffer    m_buffer;
		CSize      m_size;
		CSample    m_sample;
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