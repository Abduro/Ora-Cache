#ifndef _DIRECT_X_TEXTURE_H_INCLUDED
#define _DIRECT_X_TEXTURE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Apr-2025 at 02:13:18.338, UTC+4, Batumi, Friday;
	This is Ebo Pack DirectX texture wrapper interface declaration file;
*/
#include "direct_x._iface.h"
#include "direct_x.format.h"
#include "direct_x.res.flag.h"

namespace ex_ui { namespace draw { namespace direct_x {

namespace _11 {}
namespace _11 { namespace _2D {

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/ns-d3d11-d3d11_texture2d_desc ;
	typedef D3D11_TEXTURE2D_DESC TTexDesc;

	class CTexDesc {
	public:
		 CTexDesc (void) ; CTexDesc (const CTexDesc&) = delete;  CTexDesc (CTexDesc&&) = delete;
		~CTexDesc (void) = default;

	public:
#if defined (_DEBUG)
		void  Fake (void) ;   // fills this structure with fake data for testing texture creation by a device;
		static
		CString   Print (const TTexDesc& _raw);
	//	CString   Print (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _p_sz _p_sfx = _T("\n")) const;
#endif
		const
		TTexDesc& Raw (void) const;
		TTexDesc& Raw (void) ;
	private:
		TTexDesc  m_desc;

	private:
		CTexDesc& operator = (const CTexDesc&) = delete;
		CTexDesc& operator = (CTexDesc&&) = delete;
	};

	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11texture2d ;
	// https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nf-d3d11-id3d11texture2d-getdesc ;
	typedef ::ATL::CComPtr<ID3D11Texture2D> TTexPtr;

	typedef ::ATL::CComPtr<ID3D11Resource>  TResPtr;  // it shouldn't be declared here;

	class CTexture {
	public:
		 CTexture (void); CTexture (const CTexture&) = delete; CTexture (CTexture&&) = delete;
		~CTexture (void) = default;

	public:
		const
		CTexDesc& Desc (void) const;
		CTexDesc& Desc (void) ;

		TError&   Error (void) const;
		bool   Is_valid (void) const;
#if defined (_DEBUG)
		CString   Print (const e_print = e_print::e_all, _pc_sz _p_pfx = _T("\t\t"), _pc_sz _p_sfx = _T("\n")) const;
#endif
		err_code  Parent(TResPtr&);
		const
		TTexPtr&  Ptr (void) const;
		err_code  Ptr (const TTexPtr&);

	private:
		CError    m_error;
		TTexPtr   m_p_tex;
		CTexDesc  m_desc ;

	private:
		CTexture& operator = (const CTexture&) = delete;
		CTexture& operator = (CTexture&&) = delete;
	};

}}

namespace _12 {
}

}}}

#endif/*_DIRECT_X_TEXTURE_H_INCLUDED*/