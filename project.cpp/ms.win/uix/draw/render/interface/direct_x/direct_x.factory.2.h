#ifndef _DIRECT_X_FACTORY_2_H_INCLUDED
#define _DIRECT_X_FACTORY_2_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Apr-2025 at 12:17:56.831, UTC+4, Batumi, Wednesday;
	This is Ebo Pack DirectX 12 factory wrapper base interface declaration file;
*/
#include "direct_x.factory.h"

namespace ex_ui { namespace draw { namespace direct_x { namespace _12 {

	using namespace ex_ui::draw::direct_x;

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_6/ne-dxgi1_6-dxgi_gpu_preference ;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_6/nf-dxgi1_6-idxgifactory6-enumadapterbygpupreference;
	// the retrieved adapters are sorted in descending order: the first one is the most appropriate to requested preference;
	typedef DXGI_GPU_PREFERENCE TGpuPrefs;
	class CGpu_Prefs {
	public:
		enum e_prefs : uint32_t {
			e__unspec  = TGpuPrefs::DXGI_GPU_PREFERENCE_UNSPECIFIED     ,
			e_hi_perf  = TGpuPrefs::DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
			e_lo_power = TGpuPrefs::DXGI_GPU_PREFERENCE_MINIMUM_POWER   ,
		};
	public:
		 CGpu_Prefs (void) = default; CGpu_Prefs (const CGpu_Prefs&) = delete; CGpu_Prefs (CGpu_Prefs&&) = delete;
		~CGpu_Prefs (void) = default;

	private:
		CGpu_Prefs& operator = (const CGpu_Prefs&) = delete;
		CGpu_Prefs& operator = (CGpu_Prefs&&) = delete;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-idxgifactory-createsoftwareadapter ;
	// https://learn.microsoft.com/en-us/windows/win32/direct3darticles/directx-warp ;
	// it looks like the only one warp adapter may exist in the system;

	using CAda_Warp = ex_ui::draw::direct_x::_11::CAdapter;
	using TWarpAdaPtr = ex_ui::draw::direct_x::_11::TAdapterPtr;
	using TAdaInfoWarp = ex_ui::draw::direct_x::_11::TAdaInfoWarp;

	class CFac_4 {
	public:
		 CFac_4 (void);
		 CFac_4 (const CFac_4&);
		 CFac_4 (CFac_4&&) = delete;
		~CFac_4 (void) = default;

	public:
		err_code Create(void);          // creates this factory object;
		TError&  Error (void) const;
		bool  Is_valid (void) const;

		err_code  Get  (CAdapter&);     // retrieves the hardware adapter;
		err_code  Get  (CAda_Warp&);    // retrieves the warp adapter from this factory;
		err_code  Get  (CSwapChain&);   // creates the swap chain for an output window;
#if defined (_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
		const
		TFac4Ptr& Ptr  (void) const;
		TFac4Ptr& Ptr  (void);

		err_code  Set  (const CCmdQueue&);
		err_code  Set  (const CDevice&);

	public:
		CFac_4&  operator = (const CFac_4&);
		CFac_4&  operator = (CFac_4&&) = delete;
		CFac_4&  operator <<(const TFac4Ptr&);
		CFac_4&  operator <<(const CDevice&);

		CFac_4&  operator >>(CAda_Warp&);

	private:
		TFac4Ptr   m_p_fac;
		CError     m_error;
		TDevicePtr m_p_device;  // just cached for swap chain creation;
		TCmdQuePtr m_p_queue;   // just cached for swap chain creation;
	};

	class CFac_6 {
	public:
		 CFac_6 (void);
		 CFac_6 (const CFac_6&) = delete; CFac_6 (CFac_6&&) = delete;
		~CFac_6 (void) = default;
	public:
		const
		TAdapters& Cached (void) const;

		err_code   Create (void);           // creates this factory object;
		TError&    Error  (void) const;

		bool    Is_valid  (void) const;

		bool    Is_Hi_Perf (const uint32_t _luid_low); // not optimized yet;
		bool    Is_Lo_Power(const uint32_t _luid_low); // not optimized yet;

		err_code   Get_Hi_Perf (void);
		err_code   Get_Lo_Power (void);
		
		const
		TFac6Ptr&  Ptr (void) const;
		err_code   Ptr (const TFac6Ptr&);
#if defined(_DEBUG)
		CString    Print (const e_print = e_print::e_all) const;
#endif

	private:
		CFac_6& operator = (const CFac_6&) = delete;
		CFac_6& operator = (CFac_6&&) = delete;

	private:
		TFac6Ptr  m_p_fac ;
		CError    m_error ;
		TAdapters m_cached;
	};
}}}}

#endif/*_DIRECT_X_FACTORY_2_H_INCLUDED*/