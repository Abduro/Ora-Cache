#ifndef _EBO_SHA_DWM_WRAP_H_INCLUDED
#define _EBO_SHA_DWM_WRAP_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Apr-2025 at 02:20:30.810, UTC+4, Batumi, Sunday;
	This is Ebo Pack desktop window manager wrapper interface declaration file.
*/
#include <atlbase.h>
#include <winreg.h>     // required to be included after 'atlbase.h', otherwise the error C1189: "No Target Architecture";
#include "sys.error.h"

namespace ebo { namespace sha { namespace theme {

	using CError = shared::sys_core::CError;
	using TError = const CError;

	using namespace shared::types;

	using CRegKey = ::ATL::CRegKey;

	// https://learn.microsoft.com/en-us/windows/win32/dwm/dwm-overview ;
	// https://learn.microsoft.com/en-us/windows/win32/dwm/reference ;

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