#ifndef _DIRECT_X_FEATURE_H_INCLUDED
#define _DIRECT_X_FEATURE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-Apr-2025 at 19:48:31.943, UTC+4, Batumi, Thursday;
	This is Ebo pack DirectX data feature support interface declaration file;
*/
#include "direct_x._iface.h"
#include "direct_x.format.h"

namespace ex_ui { namespace draw { namespace direct_x {

	using TError = const shared::sys_core::CError;

	typedef D3D_FEATURE_LEVEL EFeatureLvl; // https://learn.microsoft.com/en-us/windows/win32/api/d3dcommon/ne-d3dcommon-d3d_feature_level ;

	class CFeature_Lvl {
	public:
		class CDefault { // this class is a defalt set of feature levels for creating a device;
		public:
			 CDefault (void) = default; CDefault (const CDefault&) = delete; CDefault (CDefault&&) = delete;
			~CDefault (void) = default;
		public:
			uint32_t  Count (void) const;           // gets count of elements in the levels array; 
			EFeatureLvl* const Levels (void) const; // the pointer to feature levels array;

		private:
			CDefault& operator = (const CDefault&) = delete;
			CDefault& operator = (CDefault&&) = delete;
		};
	public:
		 CFeature_Lvl (void) = default; CFeature_Lvl (const CFeature_Lvl&) = delete; CFeature_Lvl (CFeature_Lvl&&) = delete;
		~CFeature_Lvl (void) = default;
	public:
		const
		CDefault&  Default (void) const;  // gets a default set of the levels that may be used in a device creation;
#if defined(_DEBUG)
	public:
		CString Print (const uint32_t _n_level) const;
#endif
	private:
		CFeature_Lvl& operator = (const CFeature_Lvl&) = delete;
		CFeature_Lvl& operator = (CFeature_Lvl&&) = delete;
	private:
		CDefault m_def_set;
	};

namespace _11 {
	typedef D3D11_FEATURE EFeature; // https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ne-d3d11-d3d11_feature ;

	class CFeature {
	public:
		 CFeature (void);                     // by default feature type is set to D3D11_FEATURE_THREADING (0);
		 CFeature (const CFeature&) = delete; // not is required yet;
		 CFeature (CFeature&&) = delete;      // not required yet;
		~CFeature (void) = default;

	public:
		err_code  Clear(void) ;          // just sets the data block bytes to zero;
		const
		void* const Data (void) const;   // no management of data lyfe cycle is provided by this class;
		void* const Data (void) ;

		bool Is_valid (void) const;      // no memory address validation is made; it is supposed the pointer is of actual data structire;

		uint32_t Size (void) const;      // returns the size of the memory block;
		bool     Size (const uint32_t);  // no check is made for input value; any value is accepted; returs 'true' in case of size value change;

		EFeature Type (void) const;
		bool     Type (const EFeature);

	public:
		CFeature& operator = (const CFeature&) = delete; // is not required yet;
		CFeature& operator = (CFeature&&) = delete;      // is not required yet;

		CFeature& operator <<(const EFeature _e_type);
		CFeature& operator <<(const uint32_t _n_size);

	protected:
		void*     m_p_data;  // points to data structure that is defined by child class;
		uint32_t  m_size;    // the size of data structure being retrieved from the device;
		EFeature  m_type;    // feature type that is requested from the device;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_feature_data_threading ;
	typedef D3D11_FEATURE_DATA_THREADING TDataThread;

	class CFeature_Thread : public CFeature { typedef CFeature TBase;
	public:
		 CFeature_Thread (void); CFeature_Thread (const CFeature_Thread&) = delete; CFeature_Thread (CFeature_Thread&&) = delete;
		~CFeature_Thread (void) = default;

	public:
		const
		TDataThread& Ref (void) const;
		TDataThread& Ref (void) ;
#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif
	private:
		TDataThread m_data;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_feature_data_format_support ;
	typedef D3D11_FEATURE_DATA_FORMAT_SUPPORT TDataFromat;

	class CFeature_Format : public CFeature { typedef CFeature TBase;
	public:
		 CFeature_Format (void); CFeature_Format (const CFeature_Format&) = delete; CFeature_Format(CFeature_Format&&) = delete;
		~CFeature_Format (void) = default;

	public:
		const
		TDataFromat& Ref (void) const;
		TDataFromat& Ref (void) ;
#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
	private:
		TDataFromat m_data;
	};
}
namespace _12 {
}
}}}

#endif/*_DIRECT_X_FEATURE_H_INCLUDED*/