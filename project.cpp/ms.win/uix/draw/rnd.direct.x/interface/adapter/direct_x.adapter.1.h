#ifndef _DIRECT_X_ADAPTER_1_H_INCLUDED
#define _DIRECT_X_ADAPTER_1_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Apr-2025 at 22:14:50.198, UTC+4, Batumi, Monday;
	This is Ebo Pack DirectX 11 adapter wrapper interface declaration file;
*/
#include "direct_x.adapter.h"

namespace ex_ui { namespace draw { namespace direct_x { namespace _11 {

	using namespace ex_ui::draw::direct_x;

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ns-dxgi-dxgi_adapter_desc  ;
	typedef DXGI_ADAPTER_DESC   TAdapterInfo;
	typedef TAdapterInfo        TAdaInfoWarp; typedef TAdaInfoWarp TInfo; // just playing with names;

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgiadapter ;
	typedef ::ATL::CComPtr<IDXGIAdapter> TAdaptDxgPtr;

	// https://learn.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-devices-create-warp << about WARP;
	// https://learn.microsoft.com/en-us/windows/win32/direct3darticles/directx-warp << that is;
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgiadapter ;

	typedef ::ATL::CComPtr<IDXGIAdapter> TAdapterPtr; // it represents a display subsystem (including one or more GPUs, DACs and video memory);
	typedef ::ATL::CComPtr<IDXGIFactory> TParentPtr ; // this is the parent object, i.e. a factory, of the warp adapter in DX11;

	typedef TAdapterPtr TWarpPtr; // just playing with names;

	class CAdapter {
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
		 CAdapter (void);
		 CAdapter (const CAdapter&);
		 CAdapter (CAdapter&&);
		~CAdapter (void) = default;

	public:
		TError&  Error (void) const;
		err_code Get (CParent&);         // gets parent object, i.e. the factory that holds and/or creates this adapter;

		const
		TInfo&   Info (void) const;
		TInfo&   Info (void);

		bool Is (void) const;            // returns true if adapter information is initialized;
		// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-idxgiadapter-enumoutputs ;
		const
		TOutputs& Outputs (void) const;  // returns a reference to outputs of this adapter; 
		err_code  Outputs (void);        // retrieves outputs of this adapter;

#if defined(_DEBUG)
		CString  Print(const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
		const
		CProps&  Props(void) const;
		CProps&  Props(void);
		const
		TAdapterPtr&  Ptr (void) const;
		err_code      Ptr (const TAdapterPtr&);

		err_code  UpdateInfo (void);

	private:
		CAdapter& operator = (const CAdapter&);
		CAdapter& operator = (CAdapter&&);      // no move assignment here, just copying;

		CAdapter& operator <<(const TAdapterPtr&);
		CAdapter& operator <<(const TAdaInfoWarp&);

	private:
		CError       m_error;
		TAdaInfoWarp m_info ;
		TAdapterPtr  m_p_obj;
		CProps       m_props;
		TOutputs     m_outs ;
	};

	typedef ::std::vector<CAdapter> TAdapters;

	/*
	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nf-dxgi-createdxgifactory1 :
	*Important*
	The enumeration order of adapters, which are retrieved by IDXGIFactory::EnumAdapters() or IDXGIFactory1::EnumAdapters1():
	- an adapter with the output on which the desktop primary is displayed; this adapter corresponds with an index of zero;
	- adapters with outputs;
	- adapters without outputs;
	*/

	// https://learn.microsoft.com/en-us/windows/win32/direct3darticles/directx-warp ;
	// it looks like the only one warp adapter may exist in the system;
	class CAdapter_Enum {
	public:
		 CAdapter_Enum (void);
		 CAdapter_Enum (const CAdapter_Enum&);
		 CAdapter_Enum (CAdapter_Enum&&) = delete;
		~CAdapter_Enum (void) = default;

	public:
		const
		TAdapters& Cached (void) const; // returns a reference to result of enumearion of adapters;
		TErrorRef  Error  (void) const;
		err_code   GetWarp(CAdapter&) ; // gets warp adapter by calling EnumWarpAdapter() for IDXGIAdapter;
		err_code   Set (void);          // enumerates adapters by calling  EnumAdapters() for IDXGIAdapter; puts result to m_cached;

	public:
		CAdapter_Enum&  operator = (const CAdapter_Enum&); // not implemented yet;
		CAdapter_Enum&  operator = (CAdapter_Enum&&) = delete;

	private:
		CError    m_error;
		TAdapters m_cached; // the result set of enumerating adapters by calling EnumAdapters() for IDXGIAdapter;
	};

}}}}

#endif/*_DIRECT_X_ADAPTER_1_H_INCLUDED*/