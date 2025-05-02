#ifndef _DIRECT_X_IFACE_H_INCLUDED
#define _DIRECT_X_IFACE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Dec-2022 at 04:01:19.9859510, UTC+7, Novosibirsk, Thursday;
	This is Yandex Wanderer project common definition(s) for MS DirectX wrapper project declaration file;
	-----------------------------------------------------------------------------
	***Notes***
	1) All prototypes are made from https://github.com/microsoft/DirectX-Graphics-Samples ;
	   the repository contains code that demonstrates how to build graphics *intensive* apps for Windows 10 by using DirectX 12;
	2) using ::std::wstring is replaced by using ::ATL::CString due to DirectX is used under Windows OS and ATL is the best choice;
	3) throwing ::std::exception is replaced by using COM error functions for showing error details, but do not stop running test/use cases;
	***Attention***
	Using the latest features of DirectX12 requires Windows Target Platform Version 10.0.17763.0 and above; ver 10.0.18362.0 is used;
*/
// https://learn.microsoft.com/en-us/windows/win32/direct3d12/directx-12-programming-environment-set-up ;
#include <d3d11.h>
#include <d3d11_3.h> // https://learn.microsoft.com/en-us/windows/win32/api/d3d11_3/nn-d3d11_3-id3d11devicecontext4 ;
#include <d3d12.h>   // https://learn.microsoft.com/en-us/windows/win32/api/d3d12/ ; << for command queue;
#include <dxgi.h>    // https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgifactory ; (deprecated on Windows 8/8.1/10);
#include <dxgi1_2.h> // https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_2/nn-dxgi1_2-idxgiswapchain1 << for swap chain definition;
#include <dxgi1_4.h> // https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_4/nn-dxgi1_4-idxgifactory4 ; << for getting WARP;
#include <dxgi1_6.h> // https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_6/nn-dxgi1_6-idxgifactory6 ; << for getting GPU adapter best;

#include <dcommon.h> // https://learn.microsoft.com/en-us/windows/win32/api/dcommon/ns-dcommon-d2d1_pixel_format ; << pixel format ;
#include <d2d1.h>    // https://learn.microsoft.com/en-us/windows/win32/direct2d/d2d1-size-u ; << for base datatypes ;

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib" )

#include "render.base.h"

namespace ex_ui { namespace draw { namespace direct_x {
	// https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/dxgi-error ; << FormatMessage() can be used, i.e. CError{} works;
	using shared::sys_core::CError;
	using TError = const CError;

	using namespace shared::types;
	using shared::sys_core::CSyncObject;
	using ex_ui::color::rgb::CClr_Float;

	using CSize_U = geometry::base::_2D::CSize_U;

namespace _11 {

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_cpu_access_flag ;
	using ECpu_Access = D3D11_CPU_ACCESS_FLAG;
	class CCpu_Access {
	public:
		 CCpu_Access (void) = default; CCpu_Access (const CCpu_Access&) = delete; CCpu_Access (CCpu_Access&&) = delete;
		~CCpu_Access (void) = default;
#if defined(_DEBUG)
	public:
		static
		CString  Print (uint32_t _n_access);
#endif
	private:
		CCpu_Access& operator = (const CCpu_Access&) = delete;
		CCpu_Access& operator = (CCpu_Access&&) = delete;
	};

	// https://learn.microsoft.com/en-us/windows/win32/direct3d11/how-to-use-direct3d-11 ;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-idxgioutput-getdisplaymodelist ;
	// https://learn.microsoft.com/en-us/previous-versions/windows/desktop/legacy/bb173064(v=vs.85) ;
	typedef DXGI_MODE_DESC TModeDesc;
	typedef ::std::vector< TModeDesc > TModeList;

	// https://21stcenturyav.com/what-is-the-difference-between-monitor-and-display/ ;
	
	class CDisplay {
	public:
		 CDisplay (void) ; CDisplay (const CDisplay&) = delete; CDisplay (CDisplay&&) = delete;
		~CDisplay (void) = default;
	public:
		TError&   Error (void) const;
		err_code  Get   (void) ;         // gets current resolution that is set to main/primary monitor of the PC;
		bool   Is_valid (void) const;    // returns true in case when resolution is received and set to this::m_rez;

		const
		TModeList& Modes (void) const;
		TModeList& Modes (void) ;

#if defined(_DEBUG)
		static
		CString   Print (const TModeDesc&);
		CString   Print (const e_print = e_print::e_all) const;
#endif
		const
		CSize_U&  Rez (void) const;      // returns a reference to size of the resolution that is currently set to primary monitor;

	private:
		CDisplay& operator = (const CDisplay&) = delete;
		CDisplay& operator = (CDisplay&&) = delete;

	private:
		CError    m_error;
		CSize_U   m_rez;    // https://www.abbreviations.com/abbreviation/resolution ;
		TModeList m_modes;  // is not required, only one mode is interested this time: display adapter;
	};
}
}}}

#endif/*_DIRECT_X_IFACE_H_INCLUDED*/