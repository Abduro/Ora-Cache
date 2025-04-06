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
		TDevicePtr& Ptr (void) ;

	private:
		CDevice& operator = (const CDevice&) = delete;
		CDevice& operator = (CDevice&&) = delete;

	protected:
		CError     m_error;
		TDevicePtr m_object;
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
	// https://en.wikipedia.org/wiki/List_of_computing_and_IT_abbreviations ;

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
}}}

#endif/*_DIRECT_X_DEVICE_H_INCLUDED*/