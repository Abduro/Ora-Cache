#ifndef _DIRECT_X_OUTPUT_H_INCLUDED
#define _DIRECT_X_OUTPUT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 16-Apr-2025 at 20:16:55.975, UTC+4, Batumi, Wednesday;
	This is Ebo Pack DirectX adapter output wrapper interface declaration file;
*/
//#include <atltypes.h> not applicable otherwise mixing CSize declarations; may be removed by proper specifying the namespaces;
#include "direct_x._iface.h"
#include "direct_x.format.h"

namespace ex_ui { namespace draw { namespace direct_x {

	// https://learn.microsoft.com/en-us/cpp/atl-mfc-shared/reference/crect-class ;
	// https://learn.microsoft.com/en-us/previous-versions/windows/desktop/legacy/bb173065(v=vs.85) ;
	// https://learn.microsoft.com/en-us/windows/win32/gdi/hmonitor-and-the-device-context ;

	typedef DXGI_MODE_ROTATION TRotate;
#pragma region __defs_8
#define RotUnspec DXGI_MODE_ROTATION_UNSPECIFIED //
#define RotNone   DXGI_MODE_ROTATION_IDENTITY    //
#define Rot_090   DXGI_MODE_ROTATION_ROTATE90    //
#define Rot_180   DXGI_MODE_ROTATION_ROTATE180   //
#define Rot_270nn DXGI_MODE_ROTATION_ROTATE270   //
#pragma endregion

	class CRotateMode {
	public:
		enum e_rotate  : uint32_t {
		     e__unspec = TRotate::RotUnspec, // unspecified rotation;
			 e_none    = TRotate::RotNone  , // specifies no rotation;
			 e_090     = TRotate::Rot_090  , // 
			 e_180     = TRotate::Rot_180  , // 
			 e_270     = TRotate::Rot_270nn, // 
		};
	public:
		CRotateMode (void) = default; CRotateMode (const CRotateMode&) = delete; CRotateMode (CRotateMode&&) = delete;
#if defined(_DEBUG)
	public:
		CString Print (const uint32_t _n_flag, _pc_sz _p_sep = _T("|")) const;
#endif

	private:
		CRotateMode& operator = (const CRotateMode&) = delete;
		CRotateMode& operator = (CRotateMode&&) = delete;
	};

namespace _11 {

	using namespace ex_ui::draw::direct_x;

	// https://learn.microsoft.com/en-us/windows/win32/api/dxgi/ns-dxgi-dxgi_output_desc ;
	typedef DXGI_OUTPUT_DESC TOutDesc;

	typedef ::ATL::CComPtr<IDXGIOutput> TOutputPtr;

	class COutput {
	public:
		 COutput (void);
		 COutput (const COutput&);
		 COutput (COutput&&);
		~COutput (void) = default;
	public:
		const
		TOutDesc&  GetDesc (void) const;
		err_code   SetDesc (void);
		
		TError&    Error (void) const;
		bool    Is_valid (void) const;
		const
		TModeDesc& GetMode (void) const;
		err_code   SetMode (const uint32_t _n_format = CClrBits::e_rgba_norm);
#if defined(_DEBUG)
		CString    Print (const e_print = e_print::e_all) const;
#endif
		const
		TOutputPtr& Ptr (void) const;
		err_code    Ptr (const TOutputPtr&);

	public:
		COutput&  operator = (const COutput&);
		COutput&  operator = (COutput&&);         // no move assignment, just copying;
		COutput&  operator <<(const TOutDesc&);
		COutput&  operator <<(const TOutputPtr&);

	private:
		CError     m_error;
		TOutputPtr m_p_out;
		TOutDesc   m_desc ;
		TModeDesc  m_mode ; // if this output has several modes the first one is taken into account;
	};

	typedef ::std::vector<COutput> TOutputs;
}
namespace _12 {
}

}}}

#endif/*_DIRECT_X_OUTPUT_H_INCLUDED*/