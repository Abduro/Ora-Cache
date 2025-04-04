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
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ns-dxgi-dxgi_adapter_desc  ;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ns-dxgi-dxgi_adapter_desc1 ;
	typedef DXGI_ADAPTER_DESC1  TAdapterInfo;
	typedef DXGI_ADAPTER_DESC   TAdapterInfo_Base; // the difference between these descriptions is flags field only; good! :(

	typedef TAdapterInfo_Base   TAdaInfoWarp;

	using namespace shared::types;
	using TFlag = DXGI_ADAPTER_FLAG; // https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ne-dxgi-dxgi_adapter_flag ;

	class CAdapter_Flag {
	public:
		enum e_type : uint32_t {
			 e_undef = TFlag::DXGI_ADAPTER_FLAG_NONE     , // not set a flag;
			 e_soft  = TFlag::DXGI_ADAPTER_FLAG_SOFTWARE ,
		};

	};
	// https://learn.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-devices-create-warp << about WARP;
	// https://learn.microsoft.com/en-us/windows/win32/direct3darticles/directx-warp << that is;

	typedef ::ATL::CComPtr<IDXGIAdapter> TWarpAdaPtr; // otherwise a class without a pointer to real object is not useful;

	class CAda_Warp {
	public:
		 CAda_Warp (void);
		 CAda_Warp (const CAda_Warp&) = delete; CAda_Warp (CAda_Warp&&) = delete;
		~CAda_Warp (void) = default;

	public:
		const
		TAdaInfoWarp& Info (void) const;
		TAdaInfoWarp& Info (void)      ; // sets info of this adapter by direct assignment; intended for enumerator class only;

		bool Is (void) const;            // returns true if adapter information is initialized;

		const
		TWarpAdaPtr& Ptr (void) const;
		TWarpAdaPtr& Ptr (void) ;

	private:
		CAda_Warp& operator = (const CAda_Warp&) = delete;
		CAda_Warp& operator = (CAda_Warp&&) = delete;

	private:
		TAdaInfoWarp m_info;
		TWarpAdaPtr  m_object;
	};
	// https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/d3d10-graphics-programming-guide-dxgi << about adapter types;
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

		bool Is (void) const;                // returns true if adapter information is initialized;
#if defined(_DEBUG)
		CString  Print(_pc_sz _lp_sz_sep = _T("\n\t\t"), bool _aligned = true) const; // creates a string from adapter information for output;
#endif
	public: // TODO: maybe creating adapter attribute class would be better, but not for this version;
		bool Is_12_Supported (void) const;   // returns true in case if this adapter supports Direct3D 12;
		void Is_12_Supported (bool)      ;
		// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_6/ne-dxgi1_6-dxgi_gpu_preference ;
		bool Is_Hi_Performed (void) const;   // returns true in case this adapter is highest performing GPU;
		void Is_Hi_Performed (bool)      ;

	public:
		CAdapter& operator = (const CAdapter&);
		CAdapter& operator <<(const TAdapterInfo&); // sets adapter information by copying input structure;

		CAdapter& operator = (CAdapter&&);

		bool operator == (const CAdapter&) const;
		bool operator == (const TAdapterInfo&) const;

	private:
		TAdapterInfo m_info;
		bool   m_performance; // this flag indicates a preference to high performance GPU;
		bool   m_support_12;  // this flag indicates supporting Direct3D 12;
	};

	typedef ::std::vector<CAdapter> TAdapters;

#pragma region __refs
	// this class for enumerating *all* adapters uses method IDXGIFactory1::EnumAdapters1();
	// https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/d3d10-graphics-programming-guide-dxgi#new-info-about-enumerating-adapters-for-windows-8 ;
	// actually, DXGIFactories have their own interface hirachy, like this:
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgifactory1 (enumerates both adapters (video cards) with or without outputs);
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_2/nn-dxgi1_2-idxgifactory2 (introduces a lot of methods for controlling swap chain creation);
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_3/nn-dxgi1_3-idxgifactory3 (introduces the method for getting flags of graphic object creation);
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi1_5/nn-dxgi1_5-idxgifactory5 (introduces checking feature support);
#pragma endregion
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

		const CAdapter& Get(const TFlag) const;

	public:
		CAdapter_Enum& operator = (const CAdapter_Enum&);
		CAdapter_Enum& operator = (CAdapter_Enum&&) = delete; // not required yet;

	private:
		TAdapters m_adapters;
		CError    m_error;
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
}}}

#endif/*_DIRECT_X_ADAPTER_H_INCLUDED*/