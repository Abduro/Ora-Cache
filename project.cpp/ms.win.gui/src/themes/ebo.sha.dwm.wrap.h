#ifndef _EBO_SHA_DWM_WRAP_H_INCLUDED
#define _EBO_SHA_DWM_WRAP_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Apr-2025 at 02:20:30.810, UTC+4, Batumi, Sunday;
	This is Ebo Pack desktop window manager wrapper interface declaration file.
*/
#include <atlbase.h>
#include <dwmapi.h>
#include <sysinfoapi.h> // for getting OS version, it is required for DwmGetWindowAttribute() & DwmSetWindowAttribute();
#include <winreg.h>     // required to be included after 'atlbase.h', otherwise the error C1189: "No Target Architecture";
#include "sys.error.h"

#pragma comment(lib, "Dwmapi.lib")

namespace ebo { namespace sha { namespace theme {

	using CError = shared::sys_core::CError;
	using TError = const CError;

	using namespace shared::types;

	using CRegKey = ::ATL::CRegKey;
#pragma region __all_about_DWM
	// https://learn.microsoft.com/en-us/windows/win32/dwm/dwm-overview ;
	// https://learn.microsoft.com/en-us/windows/win32/dwm/reference ;
	// https://learn.microsoft.com/en-us/windows/win32/dwm/enums ;
	// https://learn.microsoft.com/en-us/windows/win32/dwm/functions ;
	// https://learn.microsoft.com/en-us/windows/win32/dwm/dwm-messages ;
	// https://learn.microsoft.com/en-us/windows/win32/dwm/structs ;
#pragma endregion

	// https://learn.microsoft.com/en-us/windows/apps/desktop/modernize/ui/apply-windows-themes ;
	// ToDo: this class must be moved to windows popup library project;
	typedef DWMWINDOWATTRIBUTE TWndAtt; // the most of the attributes is supported by Win11 only;

	class CDwmAtt {
	public: // some of the attributes enumerations; Windows Vista and 7 are not taken into account, because they are not supported;
		enum ToWin_10 : uint32_t {
		e_nc_render = DWMWA_NCRENDERING_ENABLED      , // discovers whether non-client rendering is enabled ;
		e_transit   = DWMWA_TRANSITIONS_FORCEDISABLED, // enables or forcibly disables DWM transitions ;
		e_nc_paint  = DWMWA_ALLOW_NCPAINT ,            // enables content rendered in the non-client area to be visible on the frame ;
		e_bt_cap    = DWMWA_CAPTION_BUTTON_BOUNDS    , // retrieves the bounds of the caption button area in the window-relative space ;
		};

	#if (0)  // is not defined under win.10;
		enum ToWin_11 : uint32_t {
		e_dark_mode = DWMWA_USE_IMMERSIVE_DARK_MODE  ,
		};
	#endif
	public:
		 CDwmAtt (const HWND _h_target = nullptr); CDwmAtt (const CDwmAtt&) = delete; CDwmAtt (CDwmAtt&&) = delete;
		~CDwmAtt (void);

	public:
		TError&   Error (void) const;
		bool      Get (const uint32_t _n_att) const;                // gets a current value of the input attribute; not all is accepted;
		err_code  Set (const uint32_t _n_att, const bool _b_value); // sets the specified attribute to true or false;
		const
		HWND      Target (void) const;
		err_code  Target (const HWND);

		static bool Is_valid (const HWND _h_target);

	public:
		CDwmAtt&  operator <<(const HWND _h_target);

	private:
		CDwmAtt&  operator = (const CDwmAtt&) = delete;
		CDwmAtt&  operator = (CDwmAtt&&) = delete;

	private:
		mutable
		CError    m_error;
		HWND      m_target;
	};

	// https://learn.microsoft.com/en-us/cpp/atl/reference/cregkey-class ;
	// this class reads all DWM settings from the system registry by using ATL-based registry related class(es);
	// the operation of writing a new value to the settings has not yet been provided, this class is designed to access read-only data;
	class CDwmSettings {
	public:
		 CDwmSettings (void); CDwmSettings (const CDwmSettings&) = delete; CDwmSettings (CDwmSettings&&) = delete;
		~CDwmSettings (void) = default;

	public:
		TError&   Error (void) const;

		bool EnableTransparency (void) const;
		bool SystemUsesLightTheme (void) const;

	private:
		CDwmSettings& operator = (const CDwmSettings&) = delete;
		CDwmSettings& operator = (CDwmSettings&&) = delete;

	private:
		mutable
		CError  m_error;
	};

}}}

#endif/*_EBO_SHA_DWM_WRAP_H_INCLUDED*/