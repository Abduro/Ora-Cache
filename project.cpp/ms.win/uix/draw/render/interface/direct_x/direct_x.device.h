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
	private:
		CDrv_Type (void) = delete; CDrv_Type (const CDrv_Type&) = delete; CDrv_Type (CDrv_Type&&) = delete; ~CDrv_Type (void) = delete;
	private:
		CDrv_Type& operator = (const CDrv_Type&) = delete;
		CDrv_Type& operator = (CDrv_Type&&) = delete;
	};

}}}

#endif/*_DIRECT_X_DEVICE_H_INCLUDED*/