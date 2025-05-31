#ifndef _WIN_GUI_VIEW_H_INCLUDED
#define _WIN_GUI_VIEW_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 31-May-2025 at 02:33:20.860, UTC+4, Batumi, Saturday;
	This is Ebo Pack draw renderer test app main view interface declaration file;
*/
#include "win.gui.inc.h"
#include "win.gui_layout.h"

#include "direct_x.surface.h"
#include "direct_x.wrap.h"

// https://learn.microsoft.com/en-us/cpp/preprocessor/hash-if-hash-elif-hash-else-and-hash-endif-directives-c-cpp ;
// https://en.cppreference.com/w/cpp/preprocessor/conditional ; << good example(s);

#define _tst_case_01 1

namespace ebo { namespace boo { namespace gui {

	using CPane = ex_ui::controls::CPane;
	// this is the view of the main window;
	class CView {
	public:
		 CView (void) ; CView (const CView&) = delete; CView (CView&&) = delete;
		~CView (void) ;

	public:
#if defined(_tst_case_01) && (_tst_case_01 > 0)
		const
		CPane&   Pane (void) const;
		CPane&   Pane (void) ;
#endif
		const
		CWindow& Parent (void) const;
		CWindow& Parent (void) ;

	public:
		CView& operator = (const CView&) = delete;
		CView& operator = (CView&&) = delete;

	private:
#if defined(_tst_case_01) && (_tst_case_01 > 0)
		CPane  m_sta_place;
#endif
		CWindow m_parent;  // this is the main window of this app;
	};

}}}

typedef ebo::boo::gui::CView TView;

TView&  _get_view(void);

#endif/*_WIN_GUI_VIEW_H_INCLUDED*/