#ifndef __PLATINUMSHAREDGDIPROVIDER_H_INCLUDED
#define __PLATINUMSHAREDGDIPROVIDER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 4-Nov-2007 at 9:57pm, GMT+3, Rostov-on-Don, Sunday;
	This is Sfx Pack owner-drawn related classe(s) declaration file.[proto for GUI components; www.Multicharts.com; on-site] 
	-----------------------------------------------------------------------------[objects made through oDesk.com]
	Adopted to Platinum project on 23-Mar-2014 at 8:45:09pm, GMT+4, Saint-Petersburg, Sunday; (https://platinumpayroll.co.nz)
	Adopted to File Guardian project on 28-May-2018 at 11:07:04p, UTC+7, Phuket, Rawai, Monday; (https://thefileguardian.com/)
	-----------------------------------------------------------------------------[trying to find the work; jobs@cadexchanger.com]
	Adopted to Geometry Curve project on 17-Feb-2024 at 12:14:18.6040620, UTC+7, Novosibirsk, Saturday;
*/
#include <atlbase.h>
#include <atlwin.h>
#include <commctrl.h>

#pragma warning(disable: 4458)  // declaration of 'abcd' hides class member (GDI+);

#include "sys.error.h"
#include "gdi_plus.defs.h"
#include "gdi_plus.err.h"

namespace ex_ui { namespace draw { namespace gdi_pls {

	using TErr_ref = const CErr_Adapter&;
	/*
		to start:
		// https://learn.microsoft.com/en-us/windows/win32/api/gdiplusinit/nf-gdiplusinit-gdiplusstartup      >> inits gdi+ module for a process;
		// https://learn.microsoft.com/en-us/windows/win32/api/gdiplusinit/ns-gdiplusinit-gdiplusstartupinput >> input args for startup func;
		to debug:
		// https://learn.microsoft.com/en-us/windows/win32/api/gdiplusinit/nc-gdiplusinit-debugeventproc      >> callback for getting/setting debug info;
		// https://learn.microsoft.com/en-us/windows/win32/api/gdiplusinit/ne-gdiplusinit-debugeventlevel     >> debug level enumeration;
		to hook :
		// https://learn.microsoft.com/en-us/windows/win32/api/gdiplusinit/ns-gdiplusinit-gdiplusstartupoutput   >> for setting hook func pointers;
		// https://learn.microsoft.com/en-us/windows/win32/api/gdiplusinit/nc-gdiplusinit-notificationhookproc   >> for starting a hook procedure;
		// https://learn.microsoft.com/en-us/windows/win32/api/gdiplusinit/nc-gdiplusinit-notificationunhookproc >> for ending a hook procedure;
		// 
		to stop :
		// https://learn.microsoft.com/en-us/windows/win32/api/gdiplusinit/nf-gdiplusinit-gdiplusshutdown     >> how to unload the gdi+ module;
	*/

	class CGuard {
	public:
		 CGuard (const bool _b_auto_mode = true); // capturing and releasing are automatic;
		 CGuard (const CGuard&) = delete;
		 CGuard (CGuard&&) = delete;
		~CGuard (void);

	public:
		bool     Auto   (void) const; // returns the 'auto-init' mode property value;
		err_code Capture(void);       // https://learn.microsoft.com/en-us/windows/win32/api/gdiplusinit/nf-gdiplusinit-gdiplusstartup ;
		err_code Release(void);       // https://learn.microsoft.com/en-us/windows/win32/api/gdiplusinit/nf-gdiplusinit-gdiplusshutdown ;
		bool     Secured(void) const; // returns true in case when gdi+ token is initialized;
#if defined(_DEBUG)
		CString  Print  (const e_print = e_print::e_all) const;
#endif
		TErr_ref Status (void) const; // gets the last status details;

	protected:
		volatile bool m_auto_mode;    // indicates an automatic using start up and shutdown functions in #{ctor} and #{dtor};
		CErr_Adapter  m_err_ada  ;    // this is current status that is returned by calling one of the functions of the gdi+;

	private:
		CGuard&  operator = (const CGuard&) = delete;
		CGuard&  operator = (CGuard&&) = delete;
	};

#if (0)
	class CGdiPlusPng_Loader
	{
	public:
		static HRESULT     CreateImages (const LPVOID pRawData, const DWORD _data_sz, Gdiplus::Bitmap*&);
		static HRESULT     CreateImages (const LPVOID pRawData, const DWORD _data_sz, HIMAGELIST& hImageList);
	public:
		static HRESULT     CreateImages (const ATL::_U_STRINGorID RID, const HMODULE hModule, HIMAGELIST& hImageList);
		static HRESULT     LoadResource (const ATL::_U_STRINGorID RID, const HMODULE hModule, Gdiplus::Bitmap*&);
		static HRESULT     LoadResource (const ATL::_U_STRINGorID RID, const HMODULE hModule, HBITMAP&);
	public:
		static HRESULT     CreateImages (const HBITMAP&, HIMAGELIST&); // bitmap handle provided must be destroyed by a caller;
		static HRESULT     CreateImages (const HBITMAP&, HIMAGELIST& , const SIZE& _sz_frame);
		static HMODULE     CurrentModule(void);
	};

	class CGdiPlusPng_Loader_lite {
	public:
		 CGdiPlusPng_Loader_lite(void);
		~CGdiPlusPng_Loader_lite(void);
	public:
		HRESULT     LoadImage(const ATL::_U_STRINGorID RID, Gdiplus::Bitmap*&);
		HRESULT     LoadImage(const ATL::_U_STRINGorID RID, HBITMAP&);
		HRESULT     LoadImage(const ATL::_U_STRINGorID RID, const HMODULE hModule, Gdiplus::Bitmap*&);
	};
#endif
#if (0)
#include "uix.gdi.z_buf.h"
	#define _c_clr const COLORREF
	class CGdiPlus_Helper { // TODO: must be re-viewed or deprecated;
	public:
		 CGdiPlus_Helper(void);
		~CGdiPlus_Helper(void);
	public:
		HRESULT     DrawImage(const HDC _h_dc, const RECT& _rc_area, Gdiplus::Bitmap* const);
		HRESULT     Gradient (
		               const HDC& _h_dc, const RECT& _rc_area, _c_clr _from, _c_clr _upto, const bool _b_horz = true
		            ); // no alpha channel at this time;
	};

#endif
}}}

typedef ex_ui::draw::gdi_pls::CGuard TGdiPlsGuard;
#if (0)
typedef ex_ui::draw::CGdiPlusPng_Loader      TPngLoader  ;
typedef ex_ui::draw::CGdiPlusPng_Loader_lite TPngLoaderLite;
#endif
#if (0)
typedef ex_ui::draw::CGdiPlus_Helper         TGdiPlsHelper ;
#endif
#endif/*__PLATINUMSHAREDGDIPROVIDER_H_INCLUDED*/