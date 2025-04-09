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
	Using the latest features of DirectX12 requires Windows Target Platform Version 10.0.17763.0 and above; this can be applied via VC project settings;
*/
// https://learn.microsoft.com/en-us/windows/win32/direct3d12/directx-12-programming-environment-set-up ;
#include <d3d11.h>
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

#if defined(_DEBUG)
	enum e_print : uint32_t {
	     e_all   = 0x0,  // prints out the class name and namespace path, class attribute value(s);
	     e_no_ns = 0x1,  // prints out as the option above, but no namespace path;
	     e_req   = 0x2,  // prints out the class object attribute value(s) only;
	};
#endif

}}}

#endif/*_DIRECT_X_IFACE_H_INCLUDED*/