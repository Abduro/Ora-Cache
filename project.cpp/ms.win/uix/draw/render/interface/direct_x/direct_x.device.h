#ifndef _DIRECT_X_DEVICE_H_INCLUDED
#define _DIRECT_X_DEVICE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Apr-2025 at 16:26:14.446, UTC+4, Batumi, Thursday;
	This is Ebo Pack DirectX device base wrapper interface declaration file;
*/
#include "direct_x._iface.h"
#include "direct_x.adapter.h"
#include "direct_x.feature.h"
#include "direct_x.format.h"
#include "direct_x.queue.h"

namespace ex_ui { namespace draw { namespace direct_x {

namespace _11 {
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_create_device_flag ;
	typedef D3D11_CREATE_DEVICE_FLAG TDevFlag_11;

	class CDev_Flag {
#define D3D11_CREATE_DEVICE_NO_OPTIMIZE  D3D11_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS
#define D3D11_CREATE_DEVICE_NO_REGISTRY  D3D11_CREATE_DEVICE_PREVENT_ALTERING_LAYER_SETTINGS_FROM_REGISTRY
#define D3D11_CREATE_DEVICE_NO_TIMEOUT   D3D11_CREATE_DEVICE_DISABLE_GPU_TIMEOUT
	public:
		enum e_flag : uint32_t {
		     e__undef  = 0x0,
		     e_bgra    = TDevFlag_11::D3D11_CREATE_DEVICE_BGRA_SUPPORT  , // creates a device that supports BGRA formats;
		     e_debug   = TDevFlag_11::D3D11_CREATE_DEVICE_DEBUG         , // creates a device that supports the debug layer; D3D11*SDKLayers.dll is required;
		     e_ref     = TDevFlag_11::D3D11_CREATE_DEVICE_SWITCH_TO_REF , // not supported in DX11;
		     e_shader  = TDevFlag_11::D3D11_CREATE_DEVICE_DEBUGGABLE    , // for shader debugging; D3D11_1SDKLayers.dll is required;
		     e_single  = TDevFlag_11::D3D11_CREATE_DEVICE_SINGLETHREADED, // for improving the performance, but if interfaces are called from multiple threads, undefined behavior might result;
		     e_warp    = TDevFlag_11::D3D11_CREATE_DEVICE_NO_OPTIMIZE   , // creates warp-device;
		     e_no_dbg  = TDevFlag_11::D3D11_CREATE_DEVICE_NO_REGISTRY   , // D3D runtime ignores registry settings that turn on the debug layer;
		     e_no_time = TDevFlag_11::D3D11_CREATE_DEVICE_NO_TIMEOUT    , // for GPU workloads that take more than two seconds;
		     e_wddm    = TDevFlag_11::D3D11_CREATE_DEVICE_VIDEO_SUPPORT , // leads to fail if the display driver is not implemented by WDDM driver;
		};
	private:
		CDev_Flag (void) = delete; CDev_Flag (const CDev_Flag&) = delete; CDev_Flag (CDev_Flag&&) = delete; ~CDev_Flag (void) = delete;
		CDev_Flag& operator = (const CDev_Flag&) = delete;
		CDev_Flag& operator = (CDev_Flag&&) = delete;
	};
}
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
	private:
		CDrv_Type (void) = delete; CDrv_Type (const CDrv_Type&) = delete; CDrv_Type (CDrv_Type&&) = delete; ~CDrv_Type (void) = delete;
	private:
		CDrv_Type& operator = (const CDrv_Type&) = delete;
		CDrv_Type& operator = (CDrv_Type&&) = delete;
	};

namespace _11 {
	
}
	
namespace _11 {
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11devicecontext      ; << draw and views;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11_1/nn-d3d11_1-id3d11devicecontext1 ; << shader buffers;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11_2/nn-d3d11_2-id3d11devicecontext2 ; << context;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11_3/nn-d3d11_3-id3d11devicecontext3 ; << HW protect;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11_3/nn-d3d11_3-id3d11devicecontext4 ; << fence;

	typedef ::ATL::CComPtr<ID3D11DeviceContext > TCtx0Ptr;
	typedef ::ATL::CComPtr<ID3D11DeviceContext4> TCtx4Ptr; // << d3d11_3.h is required;

	class CContext {
	public:
		 CContext (void); CContext (const CContext&) = delete; CContext (CContext&&) = delete;
		~CContext (void) = default;

	public:
		TError&   Error (void) const;
		bool   Is_valid (void) const;
#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
		const
		TCtx4Ptr& Ptr (void) const;
		TCtx4Ptr& Ptr (void) ;

		err_code  Set (const TCtx0Ptr&);  // tries to retrieve this context pointer from the pointer to base object;

	private:
		CContext& operator = (const CContext&) = delete;
		CContext& operator = (CContext&&) = delete;

	private:
		TCtx4Ptr  m_p_ctx;
		CError    m_error;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11device ; this is the base device;
	
	typedef ::ATL::CComPtr<ID3D11Device> TDevicePtr;

	class CDevice {
	public:
		 CDevice (void); CDevice(const CDevice&) = delete; CDevice (CDevice&&) = delete;
		~CDevice (void);

	public:
		err_code  Get (CAda_Warp&);    // gets warp adapter, i.e. the object that implements IDXGIAdapter interface;
		err_code  Get (CContext& );    // gets device context interface; useful for draw operations;
		err_code  Get (CFeature& );    // gets input feature data;

		TError&   Error (void) const;
		bool   Is_valid (void) const;
	
		const
		TDevicePtr& Ptr (void) const;
		TDevicePtr& Ptr (void) ;
	
	private:
		CDevice& operator = (const CDevice&) = delete;
		CDevice& operator = (CDevice&&) = delete;

	protected:
		CError     m_error;
		TDevicePtr m_object;
	};

	// https://en.wikipedia.org/wiki/List_of_computing_and_IT_abbreviations ;

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11_1/nn-d3d11_1-id3d11device1 ; shared res; blend; cmd list; dx11.1;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11_2/nn-d3d11_2-id3d11device2 ; deferred context; dx11.2;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11_3/nn-d3d11_3-id3d11device3 ; view and texture;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11_4/nn-d3d11_4-id3d11device4 ; removed event;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11_4/nn-d3d11_4-id3d11device5 ; to manage fence;

	class CDevice_HW : public CDevice { typedef CDevice TBase;
	public:
		 CDevice_HW (void); CDevice_HW (const CDevice_HW&) = delete; CDevice_HW (CDevice_HW&&) = delete;
		~CDevice_HW (void) = default;

	public:
		const
		CContext& Ctx (void) const;   // gets a reference to immediate context of this device; (ra);
		CContext& Ctx (void) ;        // gets a reference to immediate context of this device; (rw);
		// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-d3d11createdevice ; 
		err_code  Create (void);      // if no adapter pointer is used, the first adapter is applied from IDXGIFactory1::EnumAdapters();
		uint32_t  Level (void) const; // gets level of functionality that is supported by this device;
#if defined (_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
	public:
		CDevice_HW& operator = (const CDevice_HW&) = delete;
		CDevice_HW& operator = (CDevice_HW&&) = delete;

	private:
		EFeatureLvl m_level;  // the feature level that is supported by this device;
		CContext  m_imm_ctx;  // the immediate context which retrieved by create device function;
	};
}

namespace _12 {

	using CAda_Warp = ex_ui::draw::direct_x::_11::CAda_Warp;
	using TWarpAdaPtr = ex_ui::draw::direct_x::_11::TWarpAdaPtr;

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d12/nf-d3d12-id3d12device-createcommandqueue ;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d12/nf-d3d12-d3d12createdevice ;
	typedef ::ATL::CComPtr<ID3D12Device> TDevicePtr;

	class CDevice {
	public:
		 CDevice (void); CDevice(const CDevice&) = delete; CDevice (CDevice&&) = delete;
		~CDevice (void);

	public:
		err_code  Get (CCmdQueue&);    // creates command queue object;

		TError&   Error (void) const;
		bool   Is_valid (void) const;

		const
		TDevicePtr& Ptr (void) const;
		TDevicePtr& Ptr (void);

	private:
		CDevice& operator = (const CDevice&) = delete;
		CDevice& operator = (CDevice&&) = delete;

	protected:
		CError     m_error;
		TDevicePtr m_object;
	};

	class CDevice_HW : public CDevice { typedef CDevice TBase;
	public:
		 CDevice_HW (void); CDevice_HW (const CDevice_HW&) = delete; CDevice_HW (CDevice_HW&&) = delete;
		~CDevice_HW (void) = default;

	public:
		err_code  Create (const CAdapter&); // creates a device for input hardware adapter;

	public:
		CDevice_HW& operator = (const CDevice_HW&) = delete;
		CDevice_HW& operator = (CDevice_HW&&) = delete;
	};

	class CDevice_Warp : public CDevice { typedef CDevice TBase;
	public:
		 CDevice_Warp (void); CDevice_Warp(const CDevice_Warp&) = delete; CDevice_Warp (CDevice_Warp&&) = delete;
		~CDevice_Warp (void) = default;

	public:
		err_code Create (const CAda_Warp&); // creates this device object by using input wrap-adapter;

	private:
		CDevice_Warp& operator = (const CDevice_Warp&) = delete;
		CDevice_Warp& operator = (CDevice_Warp&&) = delete;
	};
}
}}}

#endif/*_DIRECT_X_DEVICE_H_INCLUDED*/