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