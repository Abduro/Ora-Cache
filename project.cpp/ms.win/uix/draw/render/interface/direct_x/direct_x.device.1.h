#ifndef _DIRECT_X_DEVICE_1_H_INCLUDED
#define _DIRECT_X_DEVICE_1_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Apr-2025 at 15:46:11.517, UTC+4, Batumi, Thursday;
	This is Ebo Pack DirectX 11 device base wrapper interface declaration file;
*/
#include "direct_x.device.h"
#include "direct_x.swap.1.h"
#include "direct_x.texture.h"

namespace ex_ui { namespace draw { namespace direct_x { namespace _11 {

	using namespace ex_ui::draw::direct_x;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_create_device_flag ;
	typedef D3D11_CREATE_DEVICE_FLAG EDevFlag;

	class CDev_Flag {
#define D3D11_CREATE_DEVICE_NO_OPTIMIZE  D3D11_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS
#define D3D11_CREATE_DEVICE_NO_REGISTRY  D3D11_CREATE_DEVICE_PREVENT_ALTERING_LAYER_SETTINGS_FROM_REGISTRY
#define D3D11_CREATE_DEVICE_NO_TIMEOUT   D3D11_CREATE_DEVICE_DISABLE_GPU_TIMEOUT
	public:
		enum e_flag : uint32_t {
		     e__undef  = 0x0,
		     e_bgra    = EDevFlag::D3D11_CREATE_DEVICE_BGRA_SUPPORT  , // creates a device that supports BGRA formats;
		     e_debug   = EDevFlag::D3D11_CREATE_DEVICE_DEBUG         , // creates a device that supports the debug layer; D3D11*SDKLayers.dll is required;
		     e_ref     = EDevFlag::D3D11_CREATE_DEVICE_SWITCH_TO_REF , // not supported in DX11;
		     e_shader  = EDevFlag::D3D11_CREATE_DEVICE_DEBUGGABLE    , // for shader debugging; D3D11_1SDKLayers.dll is required;
		     e_single  = EDevFlag::D3D11_CREATE_DEVICE_SINGLETHREADED, // for improving the performance, but if interfaces are called from multiple threads, undefined behavior might result;
		     e_warp    = EDevFlag::D3D11_CREATE_DEVICE_NO_OPTIMIZE   , // creates warp-device;
		     e_no_dbg  = EDevFlag::D3D11_CREATE_DEVICE_NO_REGISTRY   , // D3D runtime ignores registry settings that turn on the debug layer;
		     e_no_time = EDevFlag::D3D11_CREATE_DEVICE_NO_TIMEOUT    , // for GPU workloads that take more than two seconds;
		     e_wddm    = EDevFlag::D3D11_CREATE_DEVICE_VIDEO_SUPPORT , // leads to fail if the display driver is not implemented by WDDM driver;
		};
	private:
		CDev_Flag (void) = delete; CDev_Flag (const CDev_Flag&) = delete; CDev_Flag (CDev_Flag&&) = delete; ~CDev_Flag (void) = delete;
		CDev_Flag& operator = (const CDev_Flag&) = delete;
		CDev_Flag& operator = (CDev_Flag&&) = delete;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11devicecontext      ; << draw and views;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11_1/nn-d3d11_1-id3d11devicecontext1 ; << shader buffers;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11_2/nn-d3d11_2-id3d11devicecontext2 ; << context;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11_3/nn-d3d11_3-id3d11devicecontext3 ; << HW protect;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11_3/nn-d3d11_3-id3d11devicecontext4 ; << fence;

	typedef ::ATL::CComPtr<ID3D11DeviceContext > TCtx0Ptr;
	typedef ::ATL::CComPtr<ID3D11DeviceContext4> TCtx4Ptr; // << d3d11_3.h is required;

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_device_context_type ;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11devicecontext ;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11devicecontext-gettype ;

	typedef D3D11_DEVICE_CONTEXT_TYPE TCtxType;
	class CCtx_Type {
	public:
		enum e_value : uint32_t {
		     e_deferred  = TCtxType::D3D11_DEVICE_CONTEXT_DEFERRED ,
		     e_immediate = TCtxType::D3D11_DEVICE_CONTEXT_IMMEDIATE,
		};
	public:
		 CCtx_Type (void) = default; CCtx_Type (const CCtx_Type&) = delete; CCtx_Type (CCtx_Type&&) = delete;
		~CCtx_Type (void) = default;

#if defined(_DEBUG)
	public:
		static
		CString   Print (const uint32_t _n_type);
#endif

	private:
		CCtx_Type& operator = (const CCtx_Type&) = delete;
		CCtx_Type& operator = (CCtx_Type&&) = delete;
	};

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
		err_code  Ptr (const TCtx0Ptr&);  // tries to retrieve this context pointer from the pointer to base object;

		TCtxType  Type(void) const;       // just for test the context pointer works;

	private:
		CContext& operator = (const CContext&) = delete;
		CContext& operator = (CContext&&) = delete;

	private:
		TCtx4Ptr  m_p_ctx;
		CError    m_error;
		TCtxType  m_type ;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11device ; this is the base device;
	
	typedef ::ATL::CComPtr<IDXGIDevice>  TDevBasePtr;
	typedef ::ATL::CComPtr<ID3D11Device> TDevicePtr;

	using CTex_2D = ex_ui::draw::direct_x::_11::_2D::CTexture;

	class CDev_Cfg {
	public:
		typedef CFeature_Lvl::CDefault TLevels;
		typedef EFeatureLvl* TLevelsPtr;
	public:
		class CLevels {
		public:
			 CLevels (void) = default; CLevels (const CLevels&) = delete; CLevels (CLevels&&) = delete;
			~CLevels (void) = default;

		public:
			uint32_t Count (void) const;
			TLevelsPtr const Ptr (void) const;

		private:
			CLevels& operator = (const CLevels&) = delete;
			CLevels& operator = (CLevels&&) = delete;
		};

	public:
		 CDev_Cfg (void);
		 CDev_Cfg (const CDev_Cfg&) = delete;  CDev_Cfg (CDev_Cfg&&) = delete;
		~CDev_Cfg (void) = default;

	public:
		err_code  Default (const HWND hTarget = HWND_DESKTOP); // sets swap and chain description to default data for creating a device;
		const
		TSwapDesc& Desc (void) const;
		TSwapDesc& Desc (void) ;

		const
		CLevels&  Levels (void) const;
		uint32_t  Version(void) const;

	private:
		CLevels   m_def_set;
		TSwapDesc m_desc;     // this data is required for creating a device by ::D3D11CreateDeviceAndSwapChain();
	private:
		CDev_Cfg&  operator = (const CDev_Cfg&) = delete;
		CDev_Cfg&  operator = (CDev_Cfg&&) = delete;
	};

	class CDevice {
	public:
		 CDevice (void); CDevice(const CDevice&) = delete; CDevice (CDevice&&) = delete;
		~CDevice (void);

	public:
		const
		CDev_Cfg& Cfg (void) const;   // it is used for creating a device; in debug mode Cfg().Default() is enough in most cases;
		CDev_Cfg& Cfg (void);         // provides a reference to the config object for setting required options of creating this device;

		const
		CContext& Ctx (void) const;   // gets a reference to immediate context of this device; (ra);
		CContext& Ctx (void) ;        // gets a reference to immediate context of this device; (rw);

		// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-idxgidevice-getadapter ;
		err_code  Get (CAdapter&);    // gets the adapter of this device, i.e. the object that implements IDXGIAdapter interface;
		err_code  Get (CContext&);    // gets device context interface; useful for draw operations;
		err_code  Get (CFeature&);    // gets input feature data;
		err_code  Get (CTex_2D&);     // creates a 2D texture by using its description data;

		TError&   Error (void) const;
		bool   Is_valid (void) const;
	
		const
		TDevicePtr& Ptr (void) const;
		err_code    Ptr (const TDevicePtr&) ;
		const
		CSwapChain& SwapChain (void) const;
		CSwapChain& SwapChain (void) ;
	
	private:
		CDevice& operator = (const CDevice&) = delete;
		CDevice& operator = (CDevice&&) = delete;

	protected:
		CDev_Cfg   m_cfg  ;
		CContext   m_ctx  ; // the immediate context which retrieved by create device function;
		CError     m_error;
		CSwapChain m_chain; // it is created by D3D11CreateDeviceAndSwapChain;
		TDevicePtr m_p_dev;
	};

	// https://en.wikipedia.org/wiki/List_of_computing_and_IT_abbreviations ;
	// https://learn.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-devices-limitations ;

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

		err_code Create (const bool _b_with_swap = false);

		// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-d3d11createdevice ; << some create rules are here;
		//err_code  Create(void);       // if no adapter pointer is used, the first adapter is applied from IDXGIFactory1::EnumAdapters();
		// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-d3d11createdeviceandswapchain ;
		// this is the method of creating a device by D3D11CreateDeviceAndSwapChain(); does not create swap chain;
		//err_code  CreateWithSwapChain (void);
#if defined (_DEBUG)
#endif
		uint32_t  Level (void) const; // gets level of functionality that is supported by this device;
#if defined (_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
	public:
		CDevice_HW& operator = (const CDevice_HW&) = delete;
		CDevice_HW& operator = (CDevice_HW&&) = delete;

	private:
		EFeatureLvl m_level  ;  // the feature level that is supported by this device;
	};

	// https://learn.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-devices-create-ref ;
	class CDevice_Ref : public CDevice { typedef CDevice TBase;
	public:
		 CDevice_Ref (void); CDevice_Ref (const CDevice_Ref&) = delete; CDevice_Ref (CDevice_Ref&&) = delete;
		~CDevice_Ref (void) = default;

	public:
		err_code  Create (void) ; // created by 
#if defined (_DEBUG)
		void      Default(const HWND _output = HWND_DESKTOP) ; // sets default values for the swap chain desc structure;
		CString   Print (const e_print =  e_print::e_all) const;
#endif
	private:
		CDevice_Ref& operator = (const CDevice_Ref&) = delete;
		CDevice_Ref& operator = (CDevice_Ref&&) = delete;
	};

}}}}

#endif/*_DIRECT_X_DEVICE_1_H_INCLUDED*/