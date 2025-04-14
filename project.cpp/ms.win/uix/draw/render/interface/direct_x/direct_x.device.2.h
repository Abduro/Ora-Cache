#ifndef _DIRECT_X_DEVICE_2_H_INCLUDED
#define _DIRECT_X_DEVICE_2_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Apr-2025 at 15:51:04.635, UTC+4, Batumi, Thursday;
	This is Ebo Pack Direct2 11 device base wrapper interface declaration file;
*/
#include "direct_x.device.h"

namespace ex_ui { namespace draw { namespace direct_x { namespace _12 {

	using namespace ex_ui::draw::direct_x;

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
		err_code    Ptr (const TDevicePtr&);

	private:
		CDevice& operator = (const CDevice&) = delete;
		CDevice& operator = (CDevice&&) = delete;

	protected:
		CError     m_error;
		TDevicePtr m_p_dev;
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
		err_code Create (const CAda_Warp&); // creates this device object by using input warp-adapter;

	private:
		CDevice_Warp& operator = (const CDevice_Warp&) = delete;
		CDevice_Warp& operator = (CDevice_Warp&&) = delete;
	};
}}}}

#endif/*_DIRECT_X_DEVICE_2_H_INCLUDED*/