/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-May-2025 at 22:17:34.324, UTC+4, Batumi, Saturday;
	This is Ebo Pack test desktop app GUI layout interface implementation file;
*/
#include "win.gui_layout.h"

using namespace ebo::boo::gui;

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
CWindow&  CLayout::Window (void) const { return this->m_main; }
CWindow&  CLayout::Window (void)       { return this->m_main; }