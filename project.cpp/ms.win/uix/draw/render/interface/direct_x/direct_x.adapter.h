#ifndef _DIRECT_X_ADAPTER_H_INCLUDED
#define _DIRECT_X_ADAPTER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Dec-2022 at 13:34:44.9689141, UTC+7, Novosibirsk, Thursday;
	This is Yandex Wanderer project graphic adapter wrapper interface declaration file;
	-----------------------------------------------------------------------------
	https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgiadapter  ;
	https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgiadapter1 ;
*/
#include "direct_x._iface.h"

namespace ex_ui { namespace draw { namespace direct_x {
	// generic properties of an adapter of either direct_x 11 or 12;
	class CProps {
	public:
		 CProps (void);
		 CProps (const CProps&);
		 CProps (CProps&&) = delete;
		~CProps (void) = default;

	public:
		bool  Dx_12   (void) const;
		bool  Dx_12   (const bool);
		bool  Hi_Perf (void) const;
		bool  Hi_Perf (const bool);
		bool  Lo_Power(void) const;
		bool  Lo_Power(const bool);
#if defined(_DEBUG)
		CString  Print(const e_print = e_print::e_all) const;
#endif
	public:
		CProps&  operator = (const CProps&);
		CProps&  operator = (CProps&&) = delete;

	private:
		bool  m_hi_perf ;  // high performance;
		bool  m_lo_power;  // low power consumption;
		bool  m_12_vers ;  // support direct_x 12;
	};

namespace _11 {

	using namespace ex_ui::draw::direct_x;

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ns-dxgi-dxgi_adapter_desc  ;
	typedef DXGI_ADAPTER_DESC   TAdapterInfo;
	typedef TAdapterInfo        TAdaInfoWarp; typedef TAdaInfoWarp TInfo; // just playing with names;

	// https://learn.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-devices-create-warp << about WARP;
	// https://learn.microsoft.com/en-us/windows/win32/direct3darticles/directx-warp << that is;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgiadapter ;

	typedef ::ATL::CComPtr<IDXGIAdapter> TWarpAdaPtr; // it represents a display subsystem (including one or more GPUs, DACs and video memory);
	typedef ::ATL::CComPtr<IDXGIFactory> TParentPtr ; // this is the parent object, i.e. a factory, of the warp adapter in DX11;

	typedef TWarpAdaPtr TWarpPtr; // just playing with names;

	class CAda_Warp { // ToDo: the name of this class must be reviewed; possibly 'CAdapter' withing this namespace would be better;
	public:
		class CParent {
		public:
			 CParent (void); CParent (const CParent&) = delete; CParent (CParent&&) = delete;
			~CParent (void) = default;
		public:
			bool   Is_valid (void) const;
			const
			TParentPtr& Ptr (void) const;
			TParentPtr& Ptr (void);

		private:
			CParent&  operator = (const CParent&) = delete;
			CParent&  operator = (CParent&&) = delete;

		private:
			TParentPtr m_p_parent;
		};
	public:
		 CAda_Warp (void);
		 CAda_Warp (const CAda_Warp&); CAda_Warp (CAda_Warp&&) = delete;
		~CAda_Warp (void) = default;

	public:
		TError&  Error (void) const;
		err_code Get (CParent&);         // gets parent object, i.e. the factory that holds and/or creates this adapter;

		const
		TInfo&   Info (void) const;
		TInfo&   Info (void);

		bool Is (void) const;            // returns true if adapter information is initialized;
#if defined(_DEBUG)
		CString  Print(const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
		const
		CProps&  Props(void) const;
		CProps&  Props(void);
		const
		TWarpPtr&  Ptr (void) const;
		err_code   Ptr (const TWarpPtr&);

		err_code   UpdateInfo (void);

	private:
		CAda_Warp& operator = (const CAda_Warp&);
		CAda_Warp& operator = (CAda_Warp&&) = delete;

		CAda_Warp& operator <<(const TWarpPtr&);
		CAda_Warp& operator <<(const TAdaInfoWarp&);

	private:
		CError       m_error;
		TAdaInfoWarp m_info ;
		TWarpAdaPtr  m_object;
		CProps       m_props;  
	};

	// https://learn.microsoft.com/en-us/windows/win32/direct3darticles/directx-warp ;
	// it looks like the only one warp adapter may exist in the system;
	class CWarp_Enum {
	public:
		 CWarp_Enum (void);
		 CWarp_Enum (const CWarp_Enum&);
		 CWarp_Enum (CWarp_Enum&&) = delete;
		~CWarp_Enum (void) = default;

	public:
		TErrorRef    Error (void) const;
		const
		CAda_Warp&   Get (void) const;
		err_code     Set (void);

	public:
		CWarp_Enum&  operator = (const CWarp_Enum&);
		CWarp_Enum&  operator = (CWarp_Enum&&) = delete;

	private:
		CAda_Warp m_ada_warp;
		CError    m_error;
	};
}

namespace _12 {
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ne-dxgi-dxgi_adapter_flag ;
	using TFlag = DXGI_ADAPTER_FLAG; // this enumeration needs to be extended due to it does not reflect the nature of the adapter;

	class CAdapter_Flag {
	public:
		enum e_type : uint32_t {
			 e_undef = TFlag::DXGI_ADAPTER_FLAG_NONE     , // not set a flag;
			 e_soft  = TFlag::DXGI_ADAPTER_FLAG_SOFTWARE ,
		};
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ns-dxgi-dxgi_adapter_desc1 ;
	typedef DXGI_ADAPTER_DESC1  TAdapterInfo;
	typedef TAdapterInfo TInfo; // just playing with names;
	// https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/d3d10-graphics-programming-guide-dxgi << about adapter types;
	typedef ::ATL::CComPtr<IDXGIAdapter1> TAdapterPtr;

	class CAdapter {
	public:
		 CAdapter (void);
		 CAdapter (const CAdapter&);
		 CAdapter (CAdapter&&);
		~CAdapter (void);

	public:
		TError&  Error(void) const;
		err_code Info (const TInfo&);        // sets adapter information from external adapter description;
		const
		TInfo&   Info (void) const;
		TInfo&   Info (void)      ;

		bool Is (void) const;                // returns true if adapter information is initialized and the pointer to object is set;

#if defined(_DEBUG)
		CString  Print(_pc_sz _lp_sz_sep = _T("\n\t\t"), bool _aligned = true) const; // creates a string from adapter information for output;
#endif
		const
		CProps&  Props(void) const;
		CProps&  Props(void);

		const 
		TAdapterPtr&  Ptr (void) const;
		err_code      Ptr (const TAdapterPtr&) ;    // sets adapter pointer, updates its description and properties;

	public:
		CAdapter& operator = (const CAdapter&);
		CAdapter& operator <<(const CProps&);
		CAdapter& operator <<(const TAdapterInfo&); // sets adapter information by copying input structure;
		CAdapter& operator <<(const TAdapterPtr&);

		CAdapter& operator = (CAdapter&&);

		bool operator == (const CAdapter&) const;
		bool operator == (const TAdapterInfo&) const;

	private:
		TAdapterPtr  m_p_adapter;
		TAdapterInfo m_info ;
		CError       m_error;
		CProps       m_props;
	};

	typedef ::std::vector<CAdapter> TAdapters;

	class CAdapter_Enum
	{
	public:
		 CAdapter_Enum (void);
		 CAdapter_Enum (const CAdapter_Enum&);
		 CAdapter_Enum (CAdapter_Enum&&) = delete; // not required yet;
		~CAdapter_Enum (void);

	public: // for simplicity, get() and set() method names are used; TODO: maybe such approach requires to be reviewed in the next versions;
		TErrorRef Error(void) const; // returns a reference to internal error object;
		const
		TAdapters& Get (void) const; // gets a reference to collection;
		err_code   Set (void)      ; // enumerates *all* available hardware/video adapters that are installed on OS;

		const
		CAdapter&  Get(const TFlag) const;

	public:
		CAdapter_Enum& operator = (const CAdapter_Enum&);
		CAdapter_Enum& operator = (CAdapter_Enum&&) = delete; // not required yet;

	private:
		TAdapters m_adapters;
		CError    m_error;
	};
}

}}}

#endif/*_DIRECT_X_ADAPTER_H_INCLUDED*/