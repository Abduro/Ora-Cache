#ifndef _DIRECT_X_DEVICE_H_INCLUDED
#define _DIRECT_X_DEVICE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Apr-2025 at 16:26:14.446, UTC+4, Batumi, Thursday;
	This is Ebo Pack DirectX device base wrapper interface declaration file;
*/
#include "direct_x._iface.h"
#include "direct_x.adapter.h"
#include "direct_x.queue.h"

namespace ex_ui { namespace draw { namespace direct_x {

	using TError = const shared::sys_core::CError;
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
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_feature ;
	typedef D3D11_FEATURE EFeature;

	class CFeature {
	public:
		 CFeature (void);                     // by default feature type is set to D3D11_FEATURE_THREADING (0);
		 CFeature (const CFeature&) = delete; // not is required yet;
		 CFeature (CFeature&&) = delete;      // not required yet;
		~CFeature (void) = default;

	public:
		err_code  Clear(void) ;          // just sets the data block bytes to zero;
		const
		void* const Data (void) const;   // no management of data lyfe cycle is provided by this class;
		void* const Data (void) ;

		bool Is_valid (void) const;      // no memory address validation is made; it is supposed the pointer is of actual data structire;

		uint32_t Size (void) const;      // returns the size of the memory block;
		bool     Size (const uint32_t);  // no check is made for input value; any value is accepted; returs 'true' in case of size value change;

		EFeature Type (void) const;
		bool     Type (const EFeature);

	public:
		CFeature& operator = (const CFeature&) = delete; // is not required yet;
		CFeature& operator = (CFeature&&) = delete;      // is not required yet;

		CFeature& operator <<(const EFeature _e_type);
		CFeature& operator <<(const uint32_t _n_size);

	protected:
		void*     m_p_data;  // points to data structure that is defined by child class;
		uint32_t  m_size;    // the size of data structure being retrieved from the device;
		EFeature  m_type;    // feature type that is requested from the device;
	};
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_feature_data_threading ;
	typedef D3D11_FEATURE_DATA_THREADING TDataThread;

	class CFeature_Thread : public CFeature { typedef CFeature TBase;
	public:
		 CFeature_Thread (void); CFeature_Thread (const CFeature_Thread&) = delete; CFeature_Thread (CFeature_Thread&&) = delete;
		~CFeature_Thread (void) = default;

	public:
		const
		TDataThread& Ref (void) const;
		TDataThread& Ref (void) ;
#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif
	private:
		TDataThread m_data;
	};
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_feature_data_format_support ;
	typedef D3D11_FEATURE_DATA_FORMAT_SUPPORT TDataFromat;

	class CFeature_Format : public CFeature { typedef CFeature TBase;
	public:
		 CFeature_Format (void); CFeature_Format (const CFeature_Format&) = delete; CFeature_Format(CFeature_Format&&) = delete;
		~CFeature_Format (void) = default;

	public:
		const
		TDataFromat& Ref (void) const;
		TDataFromat& Ref (void) ;
#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif
	private:
		TDataFromat m_data;
	};
}
	
namespace _11 {
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11device ;
	typedef ::ATL::CComPtr<ID3D11Device> TDevicePtr;

	class CDevice {
	public:
		 CDevice (void); CDevice(const CDevice&) = delete; CDevice (CDevice&&) = delete;
		~CDevice (void);

	public:
		err_code  Get (CFeature& );    // gets input feature data;
		err_code  Get (CAda_Warp&);    // gets warp adapter, i.e. the object that implements IDXGIAdapter interface;

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

	class CDevice_HW : public CDevice { typedef CDevice TBase;
	public:
		 CDevice_HW (void); CDevice_HW (const CDevice_HW&) = delete; CDevice_HW (CDevice_HW&&) = delete;
		~CDevice_HW (void) = default;

	public:
		// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-d3d11createdevice ; 
		err_code  Create (void); // if no adapter pointer is used, the first adapter is applied from IDXGIFactory1::EnumAdapters();

	public:
		CDevice_HW& operator = (const CDevice_HW&) = delete;
		CDevice_HW& operator = (CDevice_HW&&) = delete;
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