#ifndef _DIRECT_X_FACTORY_H_INCLUDED
#define _DIRECT_X_FACTORY_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Apr-2025 at 11:56:17.202, UTC+4, Batumi;
	This is Ebo Pack DirectX factory wrapper base interface declaration file;
*/
#include "direct_x._iface.h"
#include "direct_x.adapter.h"
#include "direct_x.device.h"
#include "direct_x.queue.h"
#include "direct_x.swap.h"
#include "direct_x.swap.1.h"
#include "direct_x.swap.2.h"

namespace ex_ui { namespace draw { namespace direct_x {
	// https://www.abbreviations.com/abbreviation/factory ;
#pragma region __refs
// this class for enumerating *all* adapters uses method IDXGIFactory1::EnumAdapters1();
// https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/d3d10-graphics-programming-guide-dxgi#new-info-about-enumerating-adapters-for-windows-8 ;
// actually, DXGIFactories have their own interface hirachy, like this:
// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgifactory1 (enumerates both adapters (video cards) with or without outputs);
// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_2/nn-dxgi1_2-idxgifactory2 (introduces a lot of methods for controlling swap chain creation);
// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_3/nn-dxgi1_3-idxgifactory3 (introduces the method for getting flags of graphic object creation);
// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_5/nn-dxgi1_5-idxgifactory5 (introduces checking feature support);
#pragma endregion

	typedef IDXGIFactory   IDXGIFactory0;
	typedef ::ATL::CComPtr<IDXGIFactory0> TFac0Ptr;
	typedef ::ATL::CComPtr<IDXGIFactory4> TFac4Ptr;
	typedef ::ATL::CComPtr<IDXGIFactory5> TFac5Ptr;
	typedef ::ATL::CComPtr<IDXGIFactory6> TFac6Ptr;

namespace _11 {
	class CFac_0 {
	public:
		 CFac_0 (void); CFac_0 (const CFac_0&) = delete; CFac_0 (CFac_0&&) = delete;
		~CFac_0 (void) = default;

	public:
		TError&  Error (void) const;
		bool  Is_valid (void) const;

		const
		TFac0Ptr& Ptr  (void) const;
		TFac0Ptr& Ptr  (void);

	private:
		CFac_0& operator = (const CFac_0&) = delete;
		CFac_0& operator = (CFac_0&&) = delete;

	private:
		TFac0Ptr m_p_fac;
		CError   m_error;
	};
}
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-idxgifactory-createsoftwareadapter ;
	// https://learn.microsoft.com/en-us/windows/win32/direct3darticles/directx-warp ;
	// it looks like the only one warp adapter may exist in the system;
namespace _12 {

	using CAda_Warp = ex_ui::draw::direct_x::_11::CAda_Warp;
	using TWarpAdaPtr = ex_ui::draw::direct_x::_11::TWarpAdaPtr;
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
}
}}}

#endif/*_DIRECT_X_FACTORY_H_INCLUDED*/