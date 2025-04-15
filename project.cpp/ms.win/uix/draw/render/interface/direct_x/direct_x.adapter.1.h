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

}}}}

#endif/*_DIRECT_X_ADAPTER_1_H_INCLUDED*/