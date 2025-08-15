#ifndef _WIN_GUI_LAYOUT_H_INCLUDED
#define _WIN_GUI_LAYOUT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-May-2025 at 22:13:32.448, UTC+4, Batumi, Saturday;
	This is Ebo Pack test desktop app GUI layout interface declaration file;
*/
#include "win.gui.inc.h"
#include "win.gui_view.h"
#include "sfx.tabs.ctrl.h"   // is required for getting ex_ui::controls::sfx::tabbed::CTab class interface;

namespace ebo { namespace boo { namespace gui {

	using CPadding = ex_ui::controls::layout::CPadding_of_rect;

	using IFormEvtSink = ex_ui::message::handlers::frame::IFrameEventSink;
	using eState = IFormEvtSink::eState;
	using eEdges = IFormEvtSink::eEdges;

namespace layout {
	class CPage {
	public:
		CPage (void); CPage (const CPage&) = delete; CPage (CPage&&) = delete; ~CPage (void) = default;

		TError&   Error (void) const;

	private:
		CPage& operator = (const CPage&) = delete; CPage& operator = (CPage&&) = delete;
		mutable
		CError m_error;
	};

	class CTrack {
	using CTab = ex_ui::controls::sfx::tabbed::CTab;
	public:
		CTrack (void); CTrack (const CTrack&) = delete; CTrack (CTrack&&) = delete; ~CTrack (void) = default;

		TError&   Error  (void) const;
		t_rect    GetPos (const CTab&) const; // gets a position of the tracker window for tab page provided as input argument;

	private:
		CTrack& operator = (const CTrack&) = delete; CTrack& operator = (CTrack&&) = delete;
		mutable
		CError m_error;
	};

	class CTracks {
	public:
		CTracks (void); CTracks (const CTracks&) = delete; CTracks (CTracks&&) = delete; ~CTracks (void) = default;

		TError&   Error  (void) const;
		const
		CTrack&  Get (const uint16_t _ndx) const; // in case of input index value out of range; returned the reference to fake object; (ro)
		CTrack&  Get (const uint16_t _ndx) ;      // in case of input index value out of range; returned the reference to fake object; (rw)

		// gets a position for the tracker window which resides into *currently* selected page, i.e. the *active* page of the tab control;
		t_rect    GetPos (void) const;

		err_code  Update (void) ;  // updates the window position of each tracker; it is assumed the tab pages' layout is already updated;

	private:
		CTracks& operator = (const CTracks&) = delete; CTracks& operator = (CTracks&&) = delete;
		mutable
		CError m_error;
		CTrack m_tracks[cfg::n_page_count];
	};
}

	class CLayout {
	public:
		 CLayout (void) ; CLayout (const CLayout&) = delete; CLayout (CLayout&&) = delete;
		~CLayout (void) = default;

	public:
		t_rect  DrawArea (void) /*const*/;       // const is temporarilly removed due to this::Update() sets or changes value of the draw area;
		bool    Is_valid (void) const;

		TError&   Error  (void) const;

		const
		CPadding& Padding(void) const;
		CPadding& Padding(void) ;
		const
		layout::CPage& Page (void) const;
		layout::CPage& Page (void) ;
		const
		layout::CTracks&  Tracks (void) const;
		layout::CTracks&  Tracks (void) ;

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
		layout::CPage    m_page  ;
		layout::CTracks  m_tracks;
		CWindow  m_main ;   // main window handle;
		t_rect   m_draw_area;
	};

}}}

typedef ebo::boo::gui::CLayout TLayout;

namespace shared {
	TLayout&  Get_Layout (void);
}

#endif/*_WIN_GUI_LAYOUT_H_INCLUDED*/