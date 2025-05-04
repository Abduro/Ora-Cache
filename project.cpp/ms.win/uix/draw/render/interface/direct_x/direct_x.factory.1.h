#ifndef _DIRECT_X_FACTORY_1_H_INCLUDED
#define _DIRECT_X_FACTORY_1_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Apr-2025 at 12:14:04.300, UTC+4, Batumi, Wednesday;
	This is Ebo Pack DirectX 11 factory wrapper base interface declaration file;
*/
#include "direct_x.factory.h"

namespace ex_ui { namespace draw { namespace direct_x { namespace _11 {

	using namespace ex_ui::draw::direct_x;

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgifactory;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-createdxgifactory ;
	using CDevice = ex_ui::draw::direct_x::_11::CDevice;
	using CSwapDesc = ex_ui::draw::direct_x::_11::CDesc_Wrap;
	using CSwapChain = ex_ui::draw::direct_x::_11::CSwapChain;
	using CSwapChain_Ex = ex_ui::draw::direct_x::_11::CSwapChain_Ex;
	using CSwapDesc_Ex = ex_ui::draw::direct_x::_11::CDescEx_Wrap;
	/*
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-createdxgifactory1 :
		*Important*:
		Do not mix the use of DXGI 1.0 (IDXGIFactory) and DXGI 1.1 (IDXGIFactory1) in an application.
		Use IDXGIFactory or IDXGIFactory1, but not both in an application;
	*/

	class CFac_0 {
	public:
		 CFac_0 (void); CFac_0 (const CFac_0&) = delete; CFac_0 (CFac_0&&) = delete;
		~CFac_0 (void) = default;

	public:
		err_code Create(void);
		TError&  Error (void) const;
		bool  Is_valid (void) const;

#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif

		const
		TFac0Ptr& Ptr  (void) const;
		err_code  Ptr  (const TFac0Ptr&);

	private:
		CFac_0& operator = (const CFac_0&) = delete;
		CFac_0& operator = (CFac_0&&) = delete;

	private:
		TFac0Ptr m_p_fac;  // the pointer to IDXGIFactory;
		CError   m_error;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_2/nn-dxgi1_2-idxgifactory2 ; (for controlling swap chain creation);
	class CFac_2 {
	public:
		 CFac_2 (void); CFac_2 (const CFac_2&) = delete; CFac_2 (CFac_2&&) = delete;
		~CFac_2 (void) = default;

	public:
		err_code  Create(void);          // creates this factory object;

		TError&   Error (void) const;
		bool   Is_valid (void) const;

		err_code  Get (CSwapChain&);     // tries to create swap chain for cached device;
		err_code  Get (CSwapChain_Ex&);  // it is supposed the swap chain description is inside of in chain object;

#if defined (_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
		const
		TFac2Ptr& Ptr (void) const;
		err_code  Ptr (const TFac2Ptr&);

		err_code  Set (const CDevice&);  // sets the cached device object, checks for input arg; if the device is already cached, it is replaced;

	public:
		CFac_2& operator <<(const CDevice&);

	private:
		CFac_2& operator = (const CFac_2&) = delete;
		CFac_2& operator = (CFac_2&&) = delete;

	private:
		TFac2Ptr m_p_fac;
		CError   m_error;
		CDevice  m_device; // cached device object that is required for swap chain creation;
	};
}}}}


#endif/*_DIRECT_X_FACTORY_1_H_INCLUDED*/