#ifndef _WIN_GUI_LAYOUT_H_INCLUDED
#define _WIN_GUI_LAYOUT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-May-2025 at 22:13:32.448, UTC+4, Batumi, Saturday;
	This is Ebo Pack test desktop app GUI layout interface declaration file;
*/
#include "win.gui.inc.h"
#include "win.gui_view.h"

namespace ebo { namespace boo { namespace gui {

	using CPadding = ex_ui::controls::layout::CPadding_of_rect;

	using IFormEvtSink = ex_ui::message::handlers::frame::IFrameEventSink;
	using eState = IFormEvtSink::eState;
	using eEdges = IFormEvtSink::eEdges;

	class CLayout {
	public:
		 CLayout (void) ; CLayout (const CLayout&) = delete; CLayout (CLayout&&) = delete;
		~CLayout (void) = default;

	public:
	//	void    Default  (void) ;                // this is a default size(s) and position(s) of the GUI controls;
		t_rect  DrawArea (void) /*const*/;       // const is temporarilly removed due to this::Update() sets or changes value of the draw area;
		bool    Is_valid (void) const;

		TError&   Error  (void) const;

		const
		CPadding& Padding(void) const;
		CPadding& Padding(void) ;

		err_code  Update (void) ;                // gets main window client area rectangle and calls this::Update(rect);
		err_code  Update (const t_rect&);        // recalculates the main view layout; the client rect can be provided on window sizing event;

		const
		CWindow&  Window (void) const;
		CWindow&  Window (void) ;

	private:
		CLayout& operator = (const CLayout&) = delete;
		CLayout& operator = (CLayout&&) = delete;

	private:
		mutable
		CError   m_error;
		CPadding m_padding; // main window client rectangle draw area padding;
		CWindow  m_main ;   // main window handle;
		t_rect   m_draw_area;
	};

}}}

#endif/*_WIN_GUI_LAYOUT_H_INCLUDED*/