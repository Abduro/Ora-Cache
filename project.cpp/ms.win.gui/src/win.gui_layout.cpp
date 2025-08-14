/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-May-2025 at 22:17:34.324, UTC+4, Batumi, Saturday;
	This is Ebo Pack test desktop app GUI layout interface implementation file;
*/
#include "win.gui_layout.h"

using namespace ebo::boo::gui;

#define _what __METHOD__
#ifndef __H
#define __H(rect) (rect.bottom - rect.top)
#endif
#ifndef __W
#define __W(rect) (rect.right - rect.left)
#endif
/////////////////////////////////////////////////////////////////////////////

namespace ebo { namespace boo { namespace gui { namespace _impl {

	class CLayout_Default {
	public:
		class CPane {
		public:
			 CPane (void) {} CPane (const CPane&) = delete; CPane (CPane&&) = delete;
			~CPane (void) {}
		public:
			uint32_t Height (void) const { return 35; } // this is the default height of the status bar control;
		private:
			CPane& operator = (const CPane&) = delete;
			CPane& operator = (CPane&&) = delete;
		};
	public:
		 CLayout_Default (void) { this->m_padding.Set(10,10,-10,-10); } // sets nagative values to the right and the bottom gaps!
		 CLayout_Default (const CLayout_Default&) = delete; CLayout_Default (CLayout_Default&&) = delete;
		~CLayout_Default (void) {}

	public:
		const
		CPadding& Padding(void) const { return this->m_padding; } // this is the padding that is applied to the main window client area;
		const
		CPane&  Pane (void) const { return this->m_pane; }

	private:
		CLayout_Default& operator = (const CLayout_Default&) = delete;
		CLayout_Default& operator = (CLayout_Default&&) = delete;
	private:
		CPadding m_padding;
		CPane    m_pane;
	};

}}}}
using namespace ebo::boo::gui::_impl;
/////////////////////////////////////////////////////////////////////////////

layout::CPage:: CPage (void) { this->m_error >>__CLASS__ << __METHOD__ << __s_ok; }

TError& layout::CPage::Error (void) const { return this->m_error; }

t_rect  layout::CPage::GetTrackerPos (void) const {
	this->m_error << __METHOD__ << __s_ok;

	t_rect rect_track = {0};

	CTabbed& tabbed = shared::Get_View().Pages().Get();

	if (0 == tabbed.Tabs().Count()) {
		this->m_error << __e_not_inited = _T("Tabbed control has no pages");
		return rect_track;
	}
	// it is suppossed the tabbed control always has selected or active tab page;
	if (tabbed.Tabs().Current().Is_fake()) {
		this->m_error << __e_not_inited = _T("Tabbed control has no active tab");
		return rect_track;
	}

	const CTracker* p_tracker = shared::Get_View().Pages().Tracker(tabbed.Tabs().Active());
	if (nullptr == p_tracker) {
		this->m_error << __e_index = _T("Invalid index to trackers' array element");
		return rect_track;
	}

	// (1) gets the tab page rectangle first;
	const t_rect rect_page = tabbed.Tabs().Current().Page().Layout().Rect();
	const t_size pref_size = p_tracker->Get().Layout().Pref_Sz();
	/*
		it is assumed the following:
		(a) the trackball control is aligned to right-bottom corner of the page window client area;
		(b) the preferable size of the tracker control is applied to calculation of the control position;
	*/
	rect_track.left = rect_page.right  - pref_size.cx; rect_track.right  = rect_page.right;
	rect_track.top  = rect_page.bottom - pref_size.cy; rect_track.bottom = rect_page.bottom;

	return rect_track;
}

CLayout:: CLayout (void) : m_draw_area{0} { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }

/////////////////////////////////////////////////////////////////////////////

t_rect    CLayout::DrawArea (void)/* const */{
	this->m_error << __METHOD__ << __s_ok;
#if (0)
	t_rect rc_draw = {0};
	if (false == this->Is_valid()) {
		this->m_error << __e_not_inited;
		return  rc_draw;
	}

	if (!this->m_main.GetClientRect(&rc_draw)) {
		this->m_error.Last();
		return rc_draw;
	}

	CLayout_Default().Padding().ApplyTo(rc_draw);
	return rc_draw;
#else
	this->Update();
	return this->m_draw_area;
#endif
}

TError&   CLayout::Error  (void) const { return this->m_error;}

bool      CLayout::Is_valid (void) const { return !!this->m_main; }

const
CPadding& CLayout::Padding (void) const { return this->m_padding; }
CPadding& CLayout::Padding (void)       { return this->m_padding; }

const
layout::CPage&    CLayout::Page (void) const { return this->m_page; }
layout::CPage&    CLayout::Page (void)       { return this->m_page; }

err_code  CLayout::Update (void) {
	
	if (false == !!this->Window().IsWindow()) {
		return this->m_error << _what << __e_hwnd;
	}

	t_rect rect_ = {0};
	if (false == !!this->Window().GetClientRect(&rect_)) {
		return (this->m_error << _what).Last();
	}

	return this->Update(rect_);
}

err_code  CLayout::Update (const t_rect& _rect) {
	_rect;
	if (::IsRectEmpty(&_rect)) {
		return this->m_error << _what << __e_rect;
	}
	this->m_draw_area = _rect; // assigns the draw area rectangle to the input one;  

#if defined(_test_case_lvl) && (_test_case_lvl == 0)

	this->m_draw_area.bottom -= CLayout_Default().Pane().Height(); // updates the bottom value for reserving the space of pane control;

	t_rect rect_pane = _rect;
	rect_pane.top = rect_pane.bottom - CLayout_Default().Pane().Height();
	/*
		the issue which appears here is this layout works in client area coordinates of the main window,
		but the view components, including this test pane object, use the in-memory device context which draws only in particular area,
		and finally, the clipping being made for better performance gives not proper result due to the components resides outside of
		the draw area of the in-memory device context; for solving this issue the following may be made:
		(a) to re-calculate component points inside of their draw function;
		(b) each component of the view must be windowed for better isolation from each one other; (the better solution than above one);
	*/
	shared::Get_View().Pane().Layout().Update(rect_pane);
#endif
#if defined(_test_case_lvl) && (_test_case_lvl >= 1)
	::shared::Get_View().Status().Get().Layout().Update(_rect);
	this->m_draw_area.bottom -= ::shared::Get_View().Status().Get().Layout().Height();
#endif
	CLayout_Default().Padding().ApplyTo(this->m_draw_area); // applies padding to the draw area rectangle;
#if defined(_test_case_lvl) && (_test_case_lvl >= 2)
	::shared::Get_View().Pages().Get().Layout().Update(this->m_draw_area);
#endif
#if defined(_test_case_lvl) && (_test_case_lvl >= 3)
	// *important* : MoveWindow() does not send WM_MOVE nor WM_MOVING messages to target window;
	if (shared::Get_View().Surface()) {
		shared::Get_View().Surface().MoveWindow(&this->m_draw_area, false); // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-movewindow ; repainted == false;
		shared::Get_View().Surface().IEvtFrame_OnSizing(eEdges::eUndefined, &this->m_draw_area);
	}
#endif
	return __s_ok;
}

const
CWindow&  CLayout::Window (void) const { return this->m_main; }
CWindow&  CLayout::Window (void)       { return this->m_main; }

namespace shared {
	TLayout&  Get_Layout (void) {
		static
		TLayout cs_layout;
		return  cs_layout;
	}
}