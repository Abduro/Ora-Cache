#ifndef _WIN_GUI_LAYOUT_H_INCLUDED
#define _WIN_GUI_LAYOUT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-May-2025 at 22:13:32.448, UTC+4, Batumi, Saturday;
	This is Ebo Pack test desktop app GUI layout interface declaration file;
*/
#include "win.gui_module.h"
namespace ebo { namespace boo { namespace gui {

	using CWindow = ::ATL::CWindow;

	class CLayout {
	public:
		 CLayout (void) ; CLayout (const CLayout&) = delete; CLayout (CLayout&&) = delete;
		~CLayout (void) = default;

	public:
		RECT      DrawArea (void) const;

		TError&   Error  (void) const;

		bool    Is_valid (void) const;

		const
		CWindow&  Window (void) const;
		CWindow&  Window (void) ;

	private:
		CLayout& operator = (const CLayout&) = delete;
		CLayout& operator = (CLayout&&) = delete;

	private:
		mutable
		CError   m_error;
		CWindow  m_main;
	};

}}}

#endif/*_WIN_GUI_LAYOUT_H_INCLUDED*/