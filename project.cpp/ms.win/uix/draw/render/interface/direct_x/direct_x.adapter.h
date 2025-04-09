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

namespace _11 {

	using namespace ex_ui::draw::direct_x;

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ns-dxgi-dxgi_adapter_desc  ;
	typedef DXGI_ADAPTER_DESC   TAdapterInfo;
	typedef TAdapterInfo        TAdaInfoWarp;

	// https://learn.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-devices-create-warp << about WARP;
	// https://learn.microsoft.com/en-us/windows/win32/direct3darticles/directx-warp << that is;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgiadapter ;

	typedef ::ATL::CComPtr<IDXGIAdapter> TWarpAdaPtr; // it represents a display subsystem (including one or more GPUs, DACs and video memory);
	typedef ::ATL::CComPtr<IDXGIFactory> TParentPtr ; // this is the parent object, i.e. a factory, of the warp adapter in DX11;

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
		TAdaInfoWarp& Info (void) const;
		TAdaInfoWarp& Info (void)      ; // sets info of this adapter by direct assignment; intended for enumerator class only;

		bool Is (void) const;            // returns true if adapter information is initialized;
#if defined(_DEBUG)
		CString  Print(const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
		const
		TWarpAdaPtr& Ptr (void) const;
		TWarpAdaPtr& Ptr (void) ;

		err_code  UpdateInfo (void);

	private:
		CAda_Warp& operator = (const CAda_Warp&);
		CAda_Warp& operator = (CAda_Warp&&) = delete;

		CAda_Warp& operator <<(const TWarpAdaPtr&);
		CAda_Warp& operator <<(const TAdaInfoWarp&);

	private:
		CError       m_error;
		TAdaInfoWarp m_info ;
		TWarpAdaPtr  m_object;
	};

	// https://learn.microsoft.com/en-us/windows/win32/direct3darticles/directx-warp ;
	// it looks like the only one warp adapter may exist in the system;
	class CEnum_Warp {
	public:
		 CEnum_Warp (void);
		 CEnum_Warp (const CEnum_Warp&);
		 CEnum_Warp (CEnum_Warp&&) = delete;
		~CEnum_Warp (void) = default;

	public:
		TErrorRef    Error (void) const;
		const
		CAda_Warp&   Get (void) const;
		err_code     Set (void);

	public:
		CEnum_Warp&  operator = (const CEnum_Warp&);
		CEnum_Warp&  operator = (CEnum_Warp&&) = delete;

	private:
		CAda_Warp m_ada_warp;
		CError    m_error;
	};
}

namespace _12 {
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ne-dxgi-dxgi_adapter_flag ;
	using TFlag = DXGI_ADAPTER_FLAG;

	class CAdapter_Flag {
	public:
		enum e_type : uint32_t {
			 e_undef = TFlag::DXGI_ADAPTER_FLAG_NONE     , // not set a flag;
			 e_soft  = TFlag::DXGI_ADAPTER_FLAG_SOFTWARE ,
		};
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ns-dxgi-dxgi_adapter_desc1 ;
	typedef DXGI_ADAPTER_DESC1  TAdapterInfo;
	// https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/d3d10-graphics-programming-guide-dxgi << about adapter types;
	typedef ::ATL::CComPtr<IDXGIAdapter1> TAdapterPtr;

	class CAdapter
	{
	public:
		 CAdapter (void);
		 CAdapter (const CAdapter&);
		 CAdapter (const TAdapterInfo&);
		 CAdapter (CAdapter&&);
		~CAdapter (void);

	public:
		err_code Info(const TAdapterInfo&);  // sets adapter information from external adapter description; it is used in assign operator mainly;
		const
		TAdapterInfo& Info (void) const;
		TAdapterInfo& Info (void)      ;

		bool Is (void) const;                // returns true if adapter information is initialized and the pointer to object is set;

	public: // TODO: maybe creating adapter attribute class would be better, but not for this version;
		bool Is_12_Supported (void) const;   // returns true in case if this adapter supports Direct3D 12;
		void Is_12_Supported (bool)      ;
		// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_6/ne-dxgi1_6-dxgi_gpu_preference ;
		bool Is_Hi_Performed (void) const;   // returns true in case this adapter is highest performing GPU;
		void Is_Hi_Performed (bool)      ;

#if defined(_DEBUG)
		CString  Print(_pc_sz _lp_sz_sep = _T("\n\t\t"), bool _aligned = true) const; // creates a string from adapter information for output;
#endif
		const 
		TAdapterPtr&  Ptr (void) const;
		TAdapterPtr&  Ptr (void) ;

	public:
		CAdapter& operator = (const CAdapter&);
		CAdapter& operator <<(const TAdapterInfo&); // sets adapter information by copying input structure;
		CAdapter& operator <<(const TAdapterPtr&);

		CAdapter& operator = (CAdapter&&);

		bool operator == (const CAdapter&) const;
		bool operator == (const TAdapterInfo&) const;

	private:
		TAdapterPtr  m_p_adapter;
		TAdapterInfo m_info;
		bool   m_performance; // this flag indicates a preference to high performance GPU;
		bool   m_support_12;  // this flag indicates supporting Direct3D 12;
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