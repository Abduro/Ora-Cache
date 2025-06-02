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
		 CLayout_Default (void) { this->m_padding.Set(10,10,-10,-10); } // sets nagative values to the right and the bottom gaps!
		 CLayout_Default (const CLayout_Default&) = delete; CLayout_Default (CLayout_Default&&) = delete;
		~CLayout_Default (void) {}

	public:
#if defined(_tst_case_01) && (_tst_case_01 > 0)
		uint32_t GetPaneHeight (void) const { return 35; }
#endif
		const
		CPadding& Padding(void) const { return this->m_padding; }

	private:
		CLayout_Default& operator = (const CLayout_Default&) = delete;
		CLayout_Default& operator = (CLayout_Default&&) = delete;
	private:
		CPadding m_padding;
	};

}}}}
using namespace ebo::boo::gui::_impl;
/////////////////////////////////////////////////////////////////////////////

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

err_code  CLayout::Update (void) {
	
	if (false == !!this->Window().IsWindow()) {
		return this->m_error << _what << __e_hwnd;
	}

	t_rect rect_ = {0};
	if (false == !!this->Window().GetClientRect(&rect_)) {
		return (this->m_error << _what).Last();
	}

	return this->Update(&rect_);
}

err_code  CLayout::Update (const t_rect* const _p_rect) {
	_p_rect;
	if (nullptr == _p_rect || ::IsRectEmpty(_p_rect)) {
		return this->m_error << _what << __e_rect;
	}

	this->m_draw_area = *_p_rect; // assigns the draw area rectangle to the input one;  

#if defined(_tst_case_01) && (_tst_case_01 > 0)

	this->m_draw_area.bottom -= CLayout_Default().GetPaneHeight(); // updates the bottom value for reserving the space of pane control;

	t_rect rect_pane = *_p_rect;
	rect_pane.top = rect_pane.bottom - CLayout_Default().GetPaneHeight();

	CPane& status_bar = _get_view().Pane();
	status_bar.Layout().Update(rect_pane);
#endif
	CLayout_Default().Padding().ApplyTo(this->m_draw_area); // applies padding to the draw area rectangle;

	return __s_ok;
}

const
CWindow&  CLayout::Window (void) const { return this->m_main; }
CWindow&  CLayout::Window (void)       { return this->m_main; }