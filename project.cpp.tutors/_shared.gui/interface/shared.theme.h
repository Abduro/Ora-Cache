#ifndef _SHARED_THEME_H_INCLUDED
#define _SHARED_THEME_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-Nov-2025 at 22:55:12.502, UTC+4, Batumi, Tuesday;
	This is Ebo Pack OpenGL tutorials' shared custom theme interface declaration file;
*/
#include "shared.defs.h"
#include "color._defs.h"

namespace shared { namespace gui { namespace theme {

	using namespace shared::defs;

	class CTheme {
		CTheme (const CTheme&) = delete; CTheme (CTheme&&) = delete;
	public:
		CTheme (void); ~CTheme (void) = default;

		const rgb_color Bkgnd_rgb (void) const;
		const v_color&  Bkgnd_flt (void) const;

		const rgb_color Border (void) const;

		TError& Error (void) const;

	private:
		CTheme& operator = (const CTheme&) = delete; CTheme& operator = (CTheme&&) = delete;
		mutable v_color m_bkgnd;
		mutable CError  m_error;
	};

}}}

typedef shared::gui::theme::CTheme TTheme; TTheme&  Get_theme (void);

#endif/*_SHARED_THEME_H_INCLUDED*/