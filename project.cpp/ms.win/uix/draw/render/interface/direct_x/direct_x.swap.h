#ifndef _DIRECT_X_SWAP_H_INCLUDED
#define _DIRECT_X_SWAP_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Apr_2025 at 21:17:32.647, UTC+4, Batumi, Friday;
	This is Ebo Pack DirectX swap chain component wrapper interface declaration file;
*/
#include "direct_x._iface.h"
#include "direct_x.queue.h"

namespace ex_ui { namespace draw { namespace direct_x {
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_2/nn-dxgi1_2-idxgiswapchain1 ;
	// https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/dxgi-usage ;

	typedef DXGI_SWAP_CHAIN_DESC1 TSwapDesc;
	typedef ::ATL::CComPtr<IDXGISwapChain1> TChainPtr;

	typedef ::std::shared_ptr<TSwapDesc> TSwapDescPtr;

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_2/ne-dxgi1_2-dxgi_alpha_mode ;
	// https://learn.microsoft.com/en-us/windows/win32/api/dcommon/ne-dcommon-d2d1_alpha_mode ;
	typedef DXGI_ALPHA_MODE TAlphaMode;
	typedef D2D1_ALPHA_MODE TAlphaMode_2; // playing the same game;

	class CAlphaMode {
	public:
		enum e_mode : uint32_t {
		     e_unspec   = TAlphaMode::DXGI_ALPHA_MODE_UNSPECIFIED  ,
		     e_premulti = TAlphaMode::DXGI_ALPHA_MODE_PREMULTIPLIED,
		     e_straith  = TAlphaMode::DXGI_ALPHA_MODE_STRAIGHT     ,
		     e_ignore   = TAlphaMode::DXGI_ALPHA_MODE_IGNORE       ,
		};
	public:
		 CAlphaMode (void);
		 CAlphaMode (const TSwapDescPtr&);
		 CAlphaMode (const CAlphaMode&);
		 CAlphaMode (CAlphaMode&&) = delete; // not required yet;
		~CAlphaMode (void) = default;

	public:
		uint32_t   Get (void) const;      // gets alpha mode value;
		bool       Set (const uint32_t);  // sets alpha mode value; in case of value change 'true' is returned;
		// https://en.wikipedia.org/wiki/Sync ;
		const
		TSwapDescPtr& Sync (void) const;
		TSwapDescPtr& Sync (void) ;

	public:
		CAlphaMode&  operator = (const CAlphaMode&);
		CAlphaMode&  operator = (CAlphaMode&&) = delete; // not required yet;

		CAlphaMode&  operator <<(uint32_t _n_mode);
		CAlphaMode&  operator <<(const TSwapDescPtr& _p_sync);

	private:
		TSwapDescPtr m_desc; // this is the pointer to the structure that requires a value synchronization; by default is not set;
		uint32_t     m_mode;
	};

	// https://learn.microsoft.com/en-us/windows/win32/direct2d/supported-pixel-formats-and-alpha-modes ; << for images and bitmaps;
	class CBuff_Usage {
	public:
		enum e_usage : uint32_t { // https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/dxgi-usage ;
		     e__unspec = 0,                               // this is not acceptable value for the back buffer usage;
		     e_back    = DXGI_USAGE_BACK_BUFFER         , // the surface or resource is used as a back buffer;
		     e_descard = DXGI_USAGE_DISCARD_ON_PRESENT  , // this flag is for internal use only;
		     e_read    = DXGI_USAGE_READ_ONLY           , // read only access to a surface or resource;
		     e_shader  = DXGI_USAGE_SHADER_INPUT        , // a surface or resource as an input to a shader;
		     e_shared  = DXGI_USAGE_SHARED              , // a surface or resource is shared;
		     e_target  = DXGI_USAGE_RENDER_TARGET_OUTPUT, // a surface or resource is used as an output render target;
		     e_unorder = DXGI_USAGE_UNORDERED_ACCESS    , // a surface or resource has unordered access;
		};
	private:
		CBuff_Usage (void) = delete; CBuff_Usage (const CBuff_Usage&) = delete; CBuff_Usage (CBuff_Usage&&) = delete; ~CBuff_Usage (void) = delete;
	private:
		CBuff_Usage& operator = (const CBuff_Usage&) = delete;
		CBuff_Usage& operator = (CBuff_Usage&&) = delete;
	};
	class CBuffer {
	public:
		 CBuffer (const uint32_t _n_count = 1, const uint32_t _n_usage = CBuff_Usage::e_target);
		 CBuffer (const CBuffer&);
		 CBuffer (const TSwapDescPtr&);
		 CBuffer (CBuffer&&) = delete;
		~CBuffer (void) = default;

	public:
		uint32_t  Count (void) const;      // gets buffer count value; must be at least 1 (one) buffer count, i.e. front buffer;
		bool      Count (const uint32_t);  // sets buffer count value; returns true on change;
		uint32_t  Usage (void) const;      // gets buffer usage value; by default is set to DXGI_USAGE_RENDER_TARGET_OUTPUT;
		bool      Usage (const uint32_t);  // sets buffer usage value; returns true on change;

		bool Is_valid   (void) const;      // returns true in case when buffer count and usage values are not equal to zero both;
		bool Set (const uint32_t _n_count, const uint32_t _n_usage);

		const
		TSwapDescPtr& Sync (void) const;
		TSwapDescPtr& Sync (void) ;

	public:
		CBuffer&  operator = (const CBuffer&);
		CBuffer&  operator = (CBuffer&&) = delete;
		CBuffer&  operator <<(const uint32_t _n_count);
		CBuffer&  operator >>(const uint32_t _n_usage);

		CBuffer&  operator <<(const TSwapDescPtr&);

	private:
		uint32_t  m_count;
		uint32_t  m_usage;
		TSwapDescPtr  m_desc;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ne-dxgi-dxgi_swap_effect ;
	typedef DXGI_SWAP_EFFECT TEffect;
	class CEffect {
	public:
		enum e_value : uint32_t {
		     e_discard  = TEffect::DXGI_SWAP_EFFECT_DISCARD        , // not supported in dx12;
		     e_sequent  = TEffect::DXGI_SWAP_EFFECT_SEQUENTIAL     , // not supported in dx12;
		     e_flp_seq  = TEffect::DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL, // supported in dx12;
		     e_flp_disc = TEffect::DXGI_SWAP_EFFECT_FLIP_DISCARD   , // supported in dx12;
		};
	public:
		 CEffect (void) ;
		 CEffect (const CEffect&) ;
		 CEffect (const TSwapDescPtr&);
		 CEffect (CEffect&&) = delete;
		~CEffect (void) = default;

	public:
		uint32_t Get (void) const;
		bool     Set (const uint32_t);
		const
		TSwapDescPtr& Sync (void) const;
		TSwapDescPtr& Sync (void) ;

	private:
		CEffect&  operator = (const CEffect&);
		CEffect&  operator = (CEffect&&) = delete;

		CEffect&  operator <<(const TSwapDescPtr&);
		CEffect&  operator <<(const uint32_t _n_effect);

	private:
		e_value   m_value;
		TSwapDescPtr m_desc;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgiformat/ne-dxgiformat-dxgi_format ;
	// https://learn.microsoft.com/en-us/windows/win32/api/dcommon/ns-dcommon-d2d1_pixel_format ;

	typedef DXGI_FORMAT TResFormat;
	typedef D2D1_PIXEL_FORMAT TPxFormat;

	class CPxFormat {
	public:
		 CPxFormat (void);
		 CPxFormat (const CPxFormat&);
		 CPxFormat (const TSwapDescPtr&);
		 CPxFormat (CPxFormat&&) = delete; // not required yet;
		~CPxFormat (void) = default;

	public:
		const
		CAlphaMode& Alpha (void) const;
		CAlphaMode& Alpha (void) ;
		uint32_t   Format (void) const;       // gets value of the pixel format that is set from TResFormat enumeration;
		bool       Format (const TResFormat); // sets value of the pixel format; returns 'true' in case of value change;
		const
		TSwapDescPtr& Sync(void) const;
		TSwapDescPtr& Sync(void) ;      // the alpha mode does not get the update of sync; the better way is to use assign operator;

		TPxFormat   Raw (void) const;   // gets raw data structure object by value;

	public:
		CPxFormat&  operator = (const CPxFormat&);
		CPxFormat&  operator = (CPxFormat&&) = delete;  // not required yet;
		CPxFormat&  operator <<(const CAlphaMode&);     // sync object is not changed in alpha mode;
		CPxFormat&  operator <<(const TResFormat);
		CPxFormat&  operator <<(const TSwapDescPtr&);   // alpha mode object is also updated;

	private:
		CAlphaMode   m_alpha ;
		TSwapDescPtr m_desc  ;
		TResFormat   m_format;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgicommon/ns-dxgicommon-dxgi_sample_desc ;

	typedef DXGI_SAMPLE_DESC TSampleDesc;

	class CSample {
	public:
		 CSample (void);
		 CSample (const CSample&);
		 CSample (const TSwapDescPtr&);
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

		const
		TSwapDescPtr& Sync (void) const;
		TSwapDescPtr& Sync (void) ;

	public:
		CSample&  operator = (const CSample&);
		CSample&  operator = (CSample&&) = delete;
		CSample&  operator <<(const uint32_t _n_count);
		CSample&  operator >>(const uint32_t _n_quality);

		CSample&  operator <<(const TSwapDescPtr&);

	private:
		TSampleDesc  m_desc;
		TSwapDescPtr m_p_sync;
	};

	// https://learn.microsoft.com/en-us/windows/win32/direct2d/d2d1-size-u ;
	typedef D2D_SIZE_U TSize_U;

	class CSize {
	public:
		 CSize (void);
		 CSize (const CSize&);
		 CSize (const TSwapDescPtr&);
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

		const
		TSize_U& Raw (void) const;
		TSize_U& Raw (void) ;

		bool   Set (const uint32_t _n_width, const uint32_t _n_height);

		const
		TSwapDescPtr& Sync (void) const;
		TSwapDescPtr& Sync (void) ;

	public:
		CSize& operator = (const CSize&);
		CSize& operator = (CSize&&) = delete;

		CSize& operator <<(const uint32_t _n_width);
		CSize& operator >>(const uint32_t _n_height);

		CSize& operator <<(const TSize_U&);
		CSize& operator <<(const TSwapDescPtr&);

	private:
		TSize_U      m_size;
		TSwapDescPtr m_p_sync;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_2/ns-dxgi1_2-dxgi_swap_chain_desc1 ;

	class CSwapDesc {		
	public:
		 CSwapDesc (void);
		 CSwapDesc (const CSwapDesc&);
		 CSwapDesc (CSwapDesc&&) = delete; // not required yet;
		~CSwapDesc (void) = default;

	public:
		const
		CAlphaMode& Alpha (void) const;
		CAlphaMode& Alpha (void) ;
		const
		CBuffer&    Buffer (void) const;
		CBuffer&    Buffer (void) ;
		const
		CEffect&    Effect (void) const;
		CEffect&    Effect (void) ;
		const
		CPxFormat&  Format (void) const;
		CPxFormat&  Format (void) ;
		const
		TSwapDesc&  Raw (void) const;
		TSwapDesc&  Raw (void) ;
		const
		CSample&  Sample (void) const;
		CSample&  Sample (void) ;
		const
		CSize& Size (void) const;
		CSize& Size (void) ;
		bool   Stereo (void) const;            // returns stereo mode value;
		bool   Stereo (const bool);            // sets the stereo mode value; if 'true', the effect must be set to DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL ;

	public:
		CSwapDesc&  operator = (const CSwapDesc&);
		CSwapDesc&  operator = (CSwapDesc&&) = delete;

		CSwapDesc&  operator <<(const TSwapDesc&);

	private:
		TSwapDescPtr m_sync  ;
		TSwapDesc	 m_desc  ;
		CAlphaMode	 m_alpha ;
		CBuffer		 m_buffer;
		CEffect		 m_effect;
		CPxFormat	 m_format;
		CSample		 m_sample;
		CSize		 m_size  ;
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
		TChainPtr& Ptr (void) const;
		TChainPtr& Ptr (void) ;
		const
		CCmdQueue& Queue (void) const;
		CCmdQueue& Queue (void) ;

		HWND Target (void) const;
		bool Target (const HWND);
;
	public:
		CSwapChain& operator = (const CSwapChain&);
		CSwapChain& operator = (CSwapChain&&) = delete; // not required yet;
		CSwapChain& operator <<(const TChainPtr&);

	private:
		CError    m_error  ;
		TChainPtr m_p_chain;
		CCmdQueue m_queue  ;
		HWND      m_target ;  // this is the output window handle;
	};

}}}

#endif/*_DIRECT_X_SWAP_H_INCLUDED*/