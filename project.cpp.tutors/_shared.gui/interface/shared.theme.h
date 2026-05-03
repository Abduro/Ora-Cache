#ifndef _SHARED_THEME_H_INCLUDED
#define _SHARED_THEME_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-Nov-2025 at 22:55:12.502, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' shared custom theme interface declaration file;
*/
#include "shared.defs.h"

namespace shared { namespace gui { namespace theme { using namespace shared::defs;

	struct s_flt_clr {
		float  _alpha, _blue, _green, _red;
		s_flt_clr (const float _r = 0.0f, const float _g = 0.0f,  const float _b = 0.0f, const float _a = 0.0f);
		s_flt_clr (const s_flt_clr&);

		s_flt_clr& operator = (const s_flt_clr&);

		CString To_str (void) const;
	};
	/* query: how to set inactive window title bar color win10 :
	(0) settings >> personalization >> colors >> show assent color on the following surfaces: 'title bar and window borders' must be checked;
	(1) color value registry path HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows\DWM ;
	(2) value name AccentColorInactive (DWORD32);
	(3) data in (Blue-Green-Red) hex code format; e.g. b|g|r >> 7FFFD4
	*/

	typedef uint32_t rgb_color;

	class CTheme {
		CTheme (const CTheme&) = delete; CTheme (CTheme&&) = delete;
	public:
		CTheme (void); ~CTheme (void) = default;

		const rgb_color  Bkgnd_rgb (void) const;
		const s_flt_clr& Bkgnd_flt (void) const;

		const rgb_color  Border (void) const;

		TError& Error (void) const;

	private:
		CTheme& operator = (const CTheme&) = delete; CTheme& operator = (CTheme&&) = delete;
		mutable s_flt_clr m_bkgnd;
		mutable bool    m_is_read;
		mutable CError    m_error;
	};

}}}

typedef shared::gui::theme::CTheme TTheme; TTheme&  Get_theme (void);

#endif/*_SHARED_THEME_H_INCLUDED*/