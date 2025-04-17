#ifndef _DIRECT_X_ADAPTER_2_H_INCLUDED
#define _DIRECT_X_ADAPTER_2_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Apr-2025 at 22:15:32.759, UTC+4, Batumi, Monday;
	This is Ebo Pack DirectX 12 adapter wrapper interface declaration file;
*/
#include "direct_x.adapter.h"
#include "direct_x.adapter.2.h"

namespace ex_ui { namespace draw { namespace direct_x { namespace _12 {

	using namespace ex_ui::draw::direct_x;

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ne-dxgi-dxgi_adapter_flag ;
	using TFlag = DXGI_ADAPTER_FLAG; // this enumeration needs to be extended due to it does not reflect the nature of the adapter;

	class CAdapter_Flag {
	public:
		enum e_type : uint32_t {
			e_undef = TFlag::DXGI_ADAPTER_FLAG_NONE, // not set a flag;
			e_soft  = TFlag::DXGI_ADAPTER_FLAG_SOFTWARE,
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
		TInfo&   Info (void) const;          // gets a reference to DXGI_ADAPTER_DESC1 structure; (ra);
		TInfo&   Info (void)      ;          // gets a reference to DXGI_ADAPTER_DESC1 structure; (rw);

		bool Is (void) const;                // returns true if adapter information is initialized and the pointer to object is set;

#if defined(_DEBUG)
		CString  Print(_pc_sz _lp_sz_sep = _T("\n\t\t"), bool _aligned = true) const; // creates a string from adapter information for output;
#endif
		const
		CProps&  Props(void) const;
		CProps&  Props(void);

		const 
		TAdapterPtr&  Ptr (void) const;             // the pointer to IDXGIAdapter1;
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
		TAdapterPtr  m_p_adapter; // IDXGIAdapter1;
		TAdapterInfo m_info ;
		CError       m_error;
		CProps       m_props;
	};

	typedef ::std::vector<CAdapter> TAdapters; // the vector of IDXGIAdapter1 adapters;

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
		err_code   Set (void)      ; // calls ::EnumAdapters1() for IDXGIAdapter1;

		const
		CAdapter&  Get(const TFlag) const;

	public:
		CAdapter_Enum& operator = (const CAdapter_Enum&);
		CAdapter_Enum& operator = (CAdapter_Enum&&) = delete; // not required yet;

	private:
		TAdapters m_adapters;
		CError    m_error;
	};
}}}}

#endif/*_DIRECT_X_ADAPTER_2_H_INCLUDED*/