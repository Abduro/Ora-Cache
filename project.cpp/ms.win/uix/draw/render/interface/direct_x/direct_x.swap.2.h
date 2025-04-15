#ifndef _DIRECT_X_SWAP_2_H_INCLUDED
#define _DIRECT_X_SWAP_2_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 09-Apr-2025 at 17:04:11.282, UTC+4, Batumi, Wednesday;
	This is Ebo Pack DirectX 12 swap chain wrapper interface declaration file;
*/
#include "direct_x._iface.h"
#include "direct_x.swap.h"

namespace ex_ui { namespace draw { namespace direct_x { namespace _12 {

	using namespace ex_ui::draw::direct_x;

	// https://learn.microsoft.com/en-us/windows/win32/direct2d/supported-pixel-formats-and-alpha-modes ; << for images and bitmaps;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_2/ne-dxgi1_2-dxgi_alpha_mode ;
	// https://learn.microsoft.com/en-us/windows/win32/api/dcommon/ne-dcommon-d2d1_alpha_mode ;
	typedef DXGI_ALPHA_MODE TAlphaMode;
	typedef D2D1_ALPHA_MODE TAlphaMode_2; // playing the same game;

	// this class resides in the namespace '_12' because it is used in DXGI_SWAP_CHAIN_DESC1 structure only;
	class CAlphaMode {
	public:
		enum e_mode : uint32_t {
		     e_unspec   = TAlphaMode::DXGI_ALPHA_MODE_UNSPECIFIED  , // an alpha value might not be meaningful or is not taken into account;
		     e_premulti = TAlphaMode::DXGI_ALPHA_MODE_PREMULTIPLIED, // each color is first scaled by the alpha value; alpha remains the same;
		     e_straith  = TAlphaMode::DXGI_ALPHA_MODE_STRAIGHT     , // not-premultiplied; alpha channel indicates the transparency of the color;
		     e_ignore   = TAlphaMode::DXGI_ALPHA_MODE_IGNORE       , // alpha value is ignored; it likes GDI does;
		};
	public:
		 CAlphaMode (const uint32_t = e_mode::e_straith); // e_mode::e_straith is applied by default;
		 CAlphaMode (const CAlphaMode&);
		 CAlphaMode (CAlphaMode&&) = delete; // not required yet;
		~CAlphaMode (void) = default;

	public:
		uint32_t   Get (void) const;      // gets alpha mode value;
		bool       Set (const uint32_t);  // sets alpha mode value; in case of value change 'true' is returned;

		TAlphaMode Raw (void) const;
		// https://en.wikipedia.org/wiki/Sync ;
		                                  // input pointer address is not validated; it is assumed the outer object controls pointer's life cycle;
		void       Sync(uint32_t* const); // sets an address of outer variable to sync alpha value change with it; thread-safe;
#if defined(_DEBUG)
		CString    Print (const e_print = e_print::e_all) const;
#endif
#if (0)
		const
		TUint32Ptr&  Sync (void) const;
		TUint32Ptr&  Sync (void) ;
#endif
	public:
		CAlphaMode&  operator = (const CAlphaMode&);
		CAlphaMode&  operator = (CAlphaMode&&) = delete; // not required yet;

		CAlphaMode&  operator <<(uint32_t _n_mode);
		CAlphaMode&  operator <<(uint32_t* const _p_sync);

		operator TAlphaMode (void) const;

	private:
		uint32_t*  m_p_sync; // this is the pointer to the outer variable that requires a value synchronization; by default is not set;
		uint32_t   m_n_mode;
	};

	typedef CAlphaMode TAlpha;

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_2/ns-dxgi1_2-dxgi_swap_chain_desc1 ;
	typedef DXGI_SWAP_CHAIN_DESC1 TSwapDesc;

	class CDesc_Wrap {
	public:
		 CDesc_Wrap (void) : m_desc{0} {}
		 CDesc_Wrap (const CDesc_Wrap& _src) = delete;
		 CDesc_Wrap (CDesc_Wrap&& _victim) = delete;
		~CDesc_Wrap (void) = default;

	public:
		const
		TSwapDesc&  ref (void) const { return this->m_desc; }
		TSwapDesc&  ref (void)       { return this->m_desc; }

		operator const TSwapDesc& (void) const { return this->ref(); }
		operator       TSwapDesc& (void)       { return this->ref(); }
	
	private:
		TSwapDesc  m_desc;
	public:
		CDesc_Wrap& operator = (const CDesc_Wrap& _src) = delete;
		CDesc_Wrap& operator = (CDesc_Wrap&& _victim) = delete;
	};

	typedef ::std::shared_ptr<CDesc_Wrap> TDescWrapPtr;

	class CPxFormat {
	public:
		enum e_clr_bits : uint32_t { // just for those that used often;
		     e__unknown  = TClrBits::DXGI_FORMAT_UNKNOWN       , // is not acceptable actually;
		     e_rgba_norm = TClrBits::DXGI_FORMAT_B8G8R8A8_UNORM, // the commonly used format; very often;
		};
	public:
		 CPxFormat (const uint32_t _n_format = e_clr_bits::e_rgba_norm);
		 CPxFormat (const CPxFormat&);
		 CPxFormat (const TDescWrapPtr&);
		 CPxFormat (CPxFormat&&) = delete; // not required yet;
		~CPxFormat (void) = default;

	public:
		const
		CAlphaMode& Alpha (void) const;
		CAlphaMode& Alpha (void) ;
		uint32_t    Bits  (void) const;       // gets value of the pixel bits composition that is set from TClrBits enumeration;
		bool        Bits  (const TClrBits);   // sets value of the pixel bits composition; returns 'true' in case of value change;
		bool     Is_valid (void) const;       // returns 'true' in case when pixel format is set and alpha channel is applied;
		const
		TDescWrapPtr& Sync(void) const;
		TDescWrapPtr& Sync(void) ;      // the alpha mode does not get the update of sync; the better way is to use assign operator;
#if defined(_DEBUG)
		CString     Print (const e_print = e_print::e_all) const;
#endif
		TPxFormat   Raw (void) const;   // gets raw data structure object by value; it looks like for usage in .Net;

	public:
		CPxFormat&  operator = (const CPxFormat&);
		CPxFormat&  operator = (CPxFormat&&) = delete;  // not required yet;
		CPxFormat&  operator <<(const CAlphaMode&);     // sync object is not changed in alpha mode;
		CPxFormat&  operator <<(const TClrBits);
		CPxFormat&  operator <<(const TDescWrapPtr&);   // alpha mode object is also updated;

		operator TPxFormat (void) const;

	private:
		CAlphaMode   m_alpha ;
		TDescWrapPtr m_desc  ;      // the swap chain desc structure has two fields for synch;
		TClrBits     m_clr_bits;    // how color channel is composed; what kind of bits layout is applied;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_2/ne-dxgi1_2-dxgi_scaling ;
	typedef DXGI_SCALING TScale; // the enumeration of scaling values;

	// https://learn.microsoft.com/en-us/windows/win32/direct2d/d2d1-size-u ;
	typedef D2D_SIZE_U TSize_U;
	// there is no Is_valid property for this class yet, because 0 value is acceptable in case of creating swap chain for a window;
	class CSize {
	public:
		 CSize (void);
		 CSize (const CSize&);
		 CSize (const TDescWrapPtr&);
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
#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif
		const
		TDescWrapPtr& Sync (void) const;
		TDescWrapPtr& Sync (void) ;

	public:
		CSize& operator = (const CSize&);
		CSize& operator = (CSize&&) = delete;

		CSize& operator <<(const uint32_t _n_width);
		CSize& operator >>(const uint32_t _n_height);

		CSize& operator <<(const TSize_U&);
		CSize& operator <<(const TDescWrapPtr&);

	private:
		TSize_U      m_size;
		TDescWrapPtr m_p_sync;
	};

	class CSwapDesc : public IBuffer_Sync, public ISample_Sync {
	public:
		 CSwapDesc (void);
		 CSwapDesc (const CSwapDesc&);
		 CSwapDesc (CSwapDesc&&) = delete; // not required yet;
		~CSwapDesc (void) = default;

	public:
		const
		TAlpha&     Alpha (void) const;
		TAlpha&     Alpha (void) ;
		const
		CBuffer&    Buffer(void) const;
		CBuffer&    Buffer(void) ;
		const
		CEffect&    Effect(void) const;
		CEffect&    Effect(void) ;
		uint32_t    Flags (void) const;
		bool        Flags (const uint32_t);
		const
		CPxFormat&  Pixels(void) const;
		CPxFormat&  Pixels(void) ;
#if defined(_DEBUG)
		CString     Print (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
		const
		TSwapDesc&  Raw (void) const;
		TSwapDesc&  Raw (void) ;
		const
		CSample&    Sample(void) const;
		CSample&    Sample(void) ;
		TScale      Scale (void) const;
		bool        Scale (const TScale);
		const
		CSize&      Size (void) const;
		CSize&      Size (void) ;
		bool   Stereo (void) const;   // returns stereo mode value;
		bool   Stereo (const bool);   // sets the stereo mode value; if 'true', the effect must be set to DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL ;

	public:
		CSwapDesc&  operator = (const CSwapDesc&);
		CSwapDesc&  operator = (CSwapDesc&&) = delete;

		CSwapDesc&  operator <<(const TSwapDesc&);

	private:
		virtual bool IBuffer_OnCount (const uint32_t _n_value) override final;
		virtual bool IBuffer_OnUsage (const uint32_t _n_value) override final;

		virtual bool ISample_OnCount (const uint32_t _n_value) override final;
		virtual bool ISample_OnQuality (const uint32_t _n_value) override final;

	private:
		TDescWrapPtr m_p_desc;  // for data sync swap chain data is used as wrapper;
		CAlphaMode	 m_alpha ;
		CBuffer	     m_buffer;
		CEffect		 m_effect;
		CPxFormat    m_pixels;
		CSample      m_sample;
		CSize		 m_size  ;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_2/nn-dxgi1_2-idxgiswapchain1 ;
	typedef ::ATL::CComPtr<IDXGISwapChain1> TChainPtr;

	class CSwapChain {
	public:
		 CSwapChain (void);
		 CSwapChain (const CSwapChain&);
		 CSwapChain (CSwapChain&&) = delete; // not required yet;
		~CSwapChain (void) = default;

	public:
		const
		CSwapDesc&  Desc (void) const;
		CSwapDesc&  Desc (void) ;

		TError& Error (void) const;
		bool  Is_valid(void) const;
		const
		TChainPtr& Ptr (void) const;
		TChainPtr& Ptr (void) ;
		const
		CCmdQueue& Queue (void) const;
		CCmdQueue& Queue (void) ;
#if defined(_DEBUG)
		CString    Print (const e_print = e_print::e_all) const;
#endif
		HWND Target (void) const;
		bool Target (const HWND);

	public:
		CSwapChain& operator = (const CSwapChain&);
		CSwapChain& operator = (CSwapChain&&) = delete; // not required yet;
		CSwapChain& operator <<(const _12::TChainPtr&);

	private:
		CError    m_error  ;
		TChainPtr m_p_chain;
		CCmdQueue m_queue  ;
		HWND      m_target ;  // this is the output window handle;
		CSwapDesc m_desc   ;
	};
}}}}

#endif/*_DIRECT_X_SWAP_2_H_INCLUDED*/