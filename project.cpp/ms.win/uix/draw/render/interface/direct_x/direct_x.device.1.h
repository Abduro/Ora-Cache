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
		 CContext (void);
		 CContext (const CContext&); CContext (CContext&&) = delete;
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
		err_code  Ptr (const TCtx4Ptr&);

		TCtxType  Type(void) const;       // just for test the context pointer works;

	public:
		CContext& operator = (const CContext&) ;
		CContext& operator = (CContext&&) = delete;
		CContext& operator <<(const TCtx4Ptr&);

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
		 CDev_Cfg (const CDev_Cfg&);  CDev_Cfg (CDev_Cfg&&) = delete;
		~CDev_Cfg (void) = default;

	public:
		err_code  Default (const HWND hTarget = HWND_DESKTOP); // sets swap and chain description to default data for creating a device;
		const
		TSwapDesc& Desc (void) const;
		TSwapDesc& Desc (void) ;

		const
		CLevels&  Levels (void) const;
		uint32_t  Version(void) const;
#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
		TDrvType  Type (void) const;
		bool      Type (const TDrvType);  // returns true in case of type value change;

	public:
		CDev_Cfg&  operator = (const CDev_Cfg&);
		CDev_Cfg&  operator = (CDev_Cfg&&) = delete;
		CDev_Cfg&  operator <<(const TDrvType);
		CDev_Cfg&  operator <<(const TSwapDesc&);

	private:
		CLevels   m_def_set;
		TSwapDesc m_desc;     // this data is required for creating a device by ::D3D11CreateDeviceAndSwapChain();
		TDrvType  m_type;
	};

	// https://en.wikipedia.org/wiki/List_of_computing_and_IT_abbreviations ;
	// https://learn.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-devices-limitations ;

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11device      ; the base interface;

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11_1/nn-d3d11_1-id3d11device1 ; shared res; blend; cmd list; dx11.1;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11_2/nn-d3d11_2-id3d11device2 ; deferred context; dx11.2;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11_3/nn-d3d11_3-id3d11device3 ; view and texture;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11_4/nn-d3d11_4-id3d11device4 ; removed event;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11_4/nn-d3d11_4-id3d11device5 ; to manage fence;

	class CDevice {
	public:
		 CDevice (void);
		 CDevice (const CDevice&); CDevice (CDevice&&) = delete;
		~CDevice (void);

	public:
		const
		CDev_Cfg& Cfg (void) const;   // it is used for creating a device; in debug mode Cfg().Default() is enough in most cases;
		CDev_Cfg& Cfg (void);         // provides a reference to the config object for setting required options of creating this device;

		err_code  Create (const CDrv_Type::e_type, const bool _b_swap = true);

		const
		CContext& Ctx (void) const;   // gets a reference to immediate context of this device; (ra);
		CContext& Ctx (void) ;        // gets a reference to immediate context of this device; (rw);

		// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-idxgidevice-getadapter ;
		err_code  Get (CAdapter&);    // gets the adapter of this device, i.e. the object that implements IDXGIAdapter interface;
		err_code  Get (CContext&);    // gets device context interface; useful for draw operations;
		err_code  Get (CFeature&);    // gets input feature data;
		err_code  Get (CTex_2D&);     // creates a 2D texture by using its description data; *important*::the desc must be set;

		TError&   Error (void) const;
		bool   Is_valid (void) const;

		uint32_t  Level (void) const; // gets level of functionality that is supported by this device;

#if defined (_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
		const
		TDevicePtr& Ptr (void) const;
		err_code    Ptr (const TDevicePtr&) ; // sets *just* a raw pointer to device interface, *no* context, *no* swap chain;
		const
		CSwapChain& SwapChain (void) const;
		CSwapChain& SwapChain (void) ;
	
	public:
		CDevice& operator = (const CDevice&);
		CDevice& operator = (CDevice&&) = delete;
		CDevice& operator <<(const CContext&);
		CDevice& operator <<(const CDev_Cfg&);
		CDevice& operator <<(const CSwapChain&);
		CDevice& operator <<(const uint32_t _n_lvl);
		CDevice& operator <<(const TDevicePtr&);

	protected:
		CDev_Cfg    m_cfg  ;
		CContext    m_ctx  ; // the immediate context which retrieved by create device function;
		CError      m_error;
		CSwapChain  m_chain; // it is created by D3D11CreateDeviceAndSwapChain;
		TDevicePtr  m_p_dev;
		EFeatureLvl m_level; // the feature level that is supported by this device;
	};

	class CDevice_HW : public CDevice { typedef CDevice TBase;
	public:
		 CDevice_HW (void); CDevice_HW (const CDevice_HW&) = delete; CDevice_HW (CDevice_HW&&) = delete;
		~CDevice_HW (void) = default;

	public:
		err_code Create (const bool _b_with_swap = false);
#if defined (_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
	public:
		CDevice_HW& operator = (const CDevice_HW&) = delete;
		CDevice_HW& operator = (CDevice_HW&&) = delete;
	};

	// https://learn.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-devices-create-ref ;
	class CDevice_Ref : public CDevice { typedef CDevice TBase;
	public:
		 CDevice_Ref (void); CDevice_Ref (const CDevice_Ref&) = delete; CDevice_Ref (CDevice_Ref&&) = delete;
		~CDevice_Ref (void) = default;

	public:
		err_code  Create (const bool _b_with_swap = false);
#if defined (_DEBUG)
		CString   Print (const e_print =  e_print::e_all) const;
#endif
	private:
		CDevice_Ref& operator = (const CDevice_Ref&) = delete;
		CDevice_Ref& operator = (CDevice_Ref&&) = delete;
	};

}}}}

#endif/*_DIRECT_X_DEVICE_1_H_INCLUDED*/