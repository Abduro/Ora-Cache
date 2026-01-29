#ifndef _DIRECT_X_FACTORY_H_INCLUDED
#define _DIRECT_X_FACTORY_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 04-Apr-2025 at 11:56:17.202, UTC+4, Batumi, Friday;
	This is Ebo Pack DirectX factory wrapper base interface declaration file;
*/
#include "direct_x._iface.h"
#include "direct_x.adapter.h"
#include "direct_x.device.1.h"
#include "direct_x.device.2.h"
#include "direct_x.queue.h"
#include "direct_x.swap.h"
#include "direct_x.swap.1.h"
#include "direct_x.swap.2.h"

namespace ex_ui { namespace draw { namespace direct_x {
	// https://www.abbreviations.com/abbreviation/factory ;
#pragma region __refs_0
// this class for enumerating *all* adapters uses method IDXGIFactory1::EnumAdapters1();
// https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/d3d10-graphics-programming-guide-dxgi ;
// actually, DXGIFactories have their own interface hirachy, like this:
// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgifactory1 (enumerates both adapters (video cards) with or without outputs);
// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_3/nn-dxgi1_3-idxgifactory3 (introduces the method for getting flags of graphic object creation);
// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_5/nn-dxgi1_5-idxgifactory5 (introduces checking feature support);
#pragma endregion

	typedef IDXGIFactory   IDXGIFactory0;
	typedef ::ATL::CComPtr<IDXGIFactory0> TFac0Ptr;
	typedef ::ATL::CComPtr<IDXGIFactory1> TFac1Ptr;
	typedef ::ATL::CComPtr<IDXGIFactory2> TFac2Ptr; // intended especially for creating swap chain of target window;
	typedef ::ATL::CComPtr<IDXGIFactory4> TFac4Ptr;
	typedef ::ATL::CComPtr<IDXGIFactory5> TFac5Ptr;
	typedef ::ATL::CComPtr<IDXGIFactory6> TFac6Ptr;

}}}

#endif/*_DIRECT_X_FACTORY_H_INCLUDED*/