#ifndef _WIN_GUI_LAYOUT_H_INCLUDED
#define _WIN_GUI_LAYOUT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-May-2025 at 22:13:32.448, UTC+4, Batumi, Saturday;
	This is Ebo Pack test desktop app GUI layout interface declaration file;
*/
#include "win.gui.inc.h"
#include "win.gui_view.h"

namespace ebo { namespace boo { namespace gui {

	using CMrgns = ex_ui::controls::layout::CMargins_of_rect;

	class CLayout {
	public:
		 CLayout (void) ; CLayout (const CLayout&) = delete; CLayout (CLayout&&) = delete;
		~CLayout (void) = default;

	public:
	//	void    Default  (void) ;                // this is a default size(s) and position(s) of the GUI controls;
		t_rect  DrawArea (void) const;
		bool    Is_valid (void) const;

		TError&   Error  (void) const;

		const
		CMrgns&   Margins (void) const;
		CMrgns&   Margins (void) ;

		err_code  Update (void) ;
		err_code  Update (const t_rect* const) ; // recalculates the main view layout; the client rect can be provided on window sizing event;

		const
		CWindow&  Window (void) const;
		CWindow&  Window (void) ;

	private:
		CLayout& operator = (const CLayout&) = delete;
		CLayout& operator = (CLayout&&) = delete;

	private:
		mutable
		CError   m_error;
		CMrgns   m_mrgns;  // main window client rectangle draw area margins;
		CWindow  m_main ;  // main window handle;
	};

}}}

#endif/*_WIN_GUI_LAYOUT_H_INCLUDED*/