#ifndef _DIRECT_X_DEVICE_H_INCLUDED
#define _DIRECT_X_DEVICE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Apr-2025 at 16:26:14.446, UTC+4, Batumi, Thursday;
	This is Ebo Pack DirectX device base wrapper interface declaration file;
*/
#include "direct_x._iface.h"
#include "direct_x.adapter.h"
#include "direct_x.adapter.1.h"
#include "direct_x.adapter.2.h"
#include "direct_x.feature.h"
#include "direct_x.format.h"
#include "direct_x.queue.h"

namespace ex_ui { namespace draw { namespace direct_x {

	// https://learn.microsoft.com/en-us/windows/win32/api/d3dcommon/ne-d3dcommon-d3d_driver_type ;
	typedef D3D_DRIVER_TYPE TDrvType;

	class CDrv_Type {
	public:
	enum e_type : uint32_t {
	     e__unk = TDrvType::D3D_DRIVER_TYPE_UNKNOWN  , // a driver type is unknown ;
	     e_hard = TDrvType::D3D_DRIVER_TYPE_HARDWARE , // a hardware driver, which implements Direct3D features in hardware; the best performance;
	     e_null = TDrvType::D3D_DRIVER_TYPE_NULL     , // a reference driver without render capability ;
	     e_ref  = TDrvType::D3D_DRIVER_TYPE_REFERENCE, // a reference driver implemented by a software ; for accuracy, but not for speed;
	     e_soft = TDrvType::D3D_DRIVER_TYPE_SOFTWARE , // a software implemented driver; it is slow;
	     e_warp = TDrvType::D3D_DRIVER_TYPE_WARP     , // https://learn.microsoft.com/en-us/windows/win32/direct3darticles/directx-warp; high speed;
	};
	public:
		 CDrv_Type (void) = default; CDrv_Type (const CDrv_Type&) = delete; CDrv_Type (CDrv_Type&&) = delete;
		~CDrv_Type (void) = default;
#if defined(_DEBUG)
		static
		CString  Print (const uint32_t _n_type);
#endif
	private:
		CDrv_Type& operator = (const CDrv_Type&) = delete;
		CDrv_Type& operator = (CDrv_Type&&) = delete;
	};

namespace _11 {

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_create_device_flag ;
	typedef D3D11_CREATE_DEVICE_FLAG EDevFlag;

	class CDev_Flags {
#define D3D11_CREATE_DEVICE_NO_OPTIMIZE  D3D11_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS
#define D3D11_CREATE_DEVICE_NO_REGISTRY  D3D11_CREATE_DEVICE_PREVENT_ALTERING_LAYER_SETTINGS_FROM_REGISTRY
#define D3D11_CREATE_DEVICE_NO_TIMEOUT   D3D11_CREATE_DEVICE_DISABLE_GPU_TIMEOUT
	public:
		enum ToDbg : uint32_t {
			e_device = EDevFlag::D3D11_CREATE_DEVICE_DEBUG       , // creates a device that supports the debug layer; D3D11*SDKLayers.dll is required;
			e_shader = EDevFlag::D3D11_CREATE_DEVICE_DEBUGGABLE  , // for shader debugging; D3D11_1SDKLayers.dll is required;
		};
		enum ToSup : uint32_t {
			e_bgra = EDevFlag::D3D11_CREATE_DEVICE_BGRA_SUPPORT  , // creates a device that supports BGRA formats;
			e_wddm = EDevFlag::D3D11_CREATE_DEVICE_VIDEO_SUPPORT , // leads to fail if the display driver is not implemented by WDDM driver;
		};
		enum ToNot : uint32_t {
			e_opt  = EDevFlag::D3D11_CREATE_DEVICE_NO_OPTIMIZE   , // creates warp-device;
			e_reg  = EDevFlag::D3D11_CREATE_DEVICE_NO_REGISTRY   , // D3D runtime ignores registry settings that turn on the debug layer;
			e_time = EDevFlag::D3D11_CREATE_DEVICE_NO_TIMEOUT    , // for GPU workloads that take more than two seconds;
		};
		enum ToPerf : uint32_t {
			e__undef = 0x0,
			e_ref = EDevFlag::D3D11_CREATE_DEVICE_SWITCH_TO_REF , // not supported in DX11;
			e_one = EDevFlag::D3D11_CREATE_DEVICE_SINGLETHREADED, // for improving the performance, no thread-safe;
		};
	public:
		 CDev_Flags (void) = default; CDev_Flags (const CDev_Flags&) = delete; CDev_Flags (CDev_Flags&&) = delete;
		~CDev_Flags (void) = default;
#if defined(_DEBUG)
	public:
		static CString Print (const uint32_t _n_flags, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n"));
#endif
	private:
		CDev_Flags& operator = (const CDev_Flags&) = delete;
		CDev_Flags& operator = (CDev_Flags&&) = delete;
	};

}

}}}

#endif/*_DIRECT_X_DEVICE_H_INCLUDED*/