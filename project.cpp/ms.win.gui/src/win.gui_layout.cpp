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

	class CMargins { // ToDo: the class of such functionality is already defined in ctl.base.lyt.h ;
	public:
		 CMargins (void) {} CMargins (const CMargins&) = delete; CMargins (CMargins&&) = delete;
		~CMargins (void) {}

	public:
		RECT  DrawArea (void) const { return RECT{10, 10, 10, 10}; }

	private:
		CMargins& operator = (const CMargins&) = delete;
		CMargins& operator = (CMargins&&) = delete;
	};

	class CLayout_Default {
	public:
		 CLayout_Default (void) {} CLayout_Default (const CLayout_Default&) = delete; CLayout_Default (CLayout_Default&&) = delete;
		~CLayout_Default (void) {}

	public:
#if defined(_tst_case_01) && (_tst_case_01 > 0)
		uint32_t GetPaneHeight (void) const { return 35; }
#endif

	private:
		CLayout_Default& operator = (const CLayout_Default&) = delete;
		CLayout_Default& operator = (CLayout_Default&&) = delete;
	
	};

}}}}
using namespace ebo::boo::gui::_impl;
/////////////////////////////////////////////////////////////////////////////

CLayout:: CLayout (void) { this->m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }

/////////////////////////////////////////////////////////////////////////////

t_rect    CLayout::DrawArea (void) const {
	this->m_error << __METHOD__ << __s_ok;

	RECT rc_draw = {0};
	if (false == this->Is_valid()) {
		this->m_error << __e_not_inited;
		return  rc_draw;
	}

	if (!this->m_main.GetClientRect(&rc_draw)) {
		this->m_error.Last();
		return rc_draw;
	}

	const t_rect rc_margins = CMargins().DrawArea();

	rc_draw.left   += rc_margins.left ;
	rc_draw.top    += rc_margins.top  ;
	rc_draw.right  -= rc_margins.right;
	rc_draw.bottom -= rc_margins.bottom;

	return rc_draw;
}

TError&   CLayout::Error  (void) const { return this->m_error;}

bool      CLayout::Is_valid (void) const { return !!this->m_main; }

const
CMrgns&   CLayout::Margins (void) const { return this->m_mrgns; }
CMrgns&   CLayout::Margins (void)       { return this->m_mrgns; }

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

	t_rect rect_ = *_p_rect;

#if defined(_tst_case_01) && (_tst_case_01 > 0)

	rect_.top = rect_.bottom - CLayout_Default().GetPaneHeight();

	CPane& status_bar = _get_view().Pane();
	status_bar.Layout().Position() << rect_;

#endif

	return __s_ok;
}

const
CWindow&  CLayout::Window (void) const { return this->m_main; }
CWindow&  CLayout::Window (void)       { return this->m_main; }