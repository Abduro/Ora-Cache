/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Aug-2020 at 7:35:47a, UTC+7, Novosibirsk, Sunday;
	This is Ebo Pack shared status bar control layout interface implementation file.
*/
#include "sfx.status.lay.h"
#include "sfx.status.ctrl.h" // this header is included here due to exclude cyclic dependencies through header files;

using namespace ex_ui::controls::sfx::status;
using namespace ex_ui::controls::sfx::status::layout;

#ifndef __W
#define __W(rect) (rect.right - rect.left)
#endif

/////////////////////////////////////////////////////////////////////////////

CLayout:: CLayout (CControl& _ctrl) : m_ctrl(_ctrl), m_height(28) { m_error >> __CLASS__ << __METHOD__ << __s_ok; }
CLayout::~CLayout (void) {}

/////////////////////////////////////////////////////////////////////////////

TError&  CLayout::Error  (void) const { return m_error ; }
uint32_t CLayout::Height (void) const { return m_height; }
bool     CLayout::Height (const uint32_t _u_value) {
	_u_value;
	const bool b_changed = (this->Height() != _u_value);
	if (b_changed)
		this->m_height = _u_value; // ToDo: perhaps auto-update of this layout would be useful;

	return b_changed;
}

bool     CLayout::Is (void) const { return m_height > 0; }

err_code CLayout::Update (void) {

	err_code n_result = __s_ok;

	CWindow wnd_ = this->m_ctrl.Window();

	if (false == wnd_.IsWindow()) {
		return this->m_error << __METHOD__ << __e_hwnd = _T("The control window is not valid");
	}

	t_rect rc_area = {0};
	// it is possible to get the same rectangle as it was in the previous call of this method;
	// it looks like there's no reason to recalculate this status bar control layout, but some settings may be changed, so no options;
	if (false == wnd_.GetClientRect(&rc_area)) {
		return (this->m_error << __METHOD__).Last();
	}

	// (1) updates border position(s); the border thickness is not important, because the renderer takes into account it;
#if (1)
	CBorders& borders = this->m_ctrl.Borders();
	n_result = borders.Set(rc_area); // advanced mode of the device context being used is not considered yet;
#else
	CBorder& top_ = this->m_ctrl.Format().Borders().Top();
	top_.Set(CPoint(rc_area.left, rc_area.top), CPoint(rc_area.right, rc_area.top));
#endif

	using ex_ui::controls::pane::CFormat;
	using ex_ui::controls::pane::CLayout;

	const t_size& frm_sz = this->m_ctrl.Images()().Size(); frm_sz;      // image list frame size;
	const bool b_valid   = this->m_ctrl.Images()().Is_valid(); b_valid; // image list validity, perhaps is not necessary: the size may exist after destroying somehow the list;

	// ToDo: the sticking that is applied has default side left; no sticking to right side is considered yet; 
	// (2) reducing the status bar available rectangle by removing borders thickness from its area;
	bool b_applied = borders.Reduce(rc_area); b_applied;

	long n_left  = rc_area.left ; // left side start point;
	long n_right = rc_area.right; // right side of the available area for panes, it is necessary for glyph;

	// (3) sets glyph's position;
	CGlyph& glyph = this->m_ctrl.Panes().Glyph();
	// it is assumed the glyph always has the fixed width;
	{
		TPn_Lay& lay = glyph.Layout();
		t_rect& rect = glyph.Layout().Rect(); rect = rc_area; rect.left = rect.right - lay.Fixed(); // takes into account fixed width;

		// calculates the required length of the glyph pane; no borders are taken into account, it is supposed there is no border;
		const int32_t req_width = lay.Image().Margins().Left() + lay.Image().Margins().Right() + frm_sz.cx;

		// checks the fixed size against image area, if the image has the width greater than fixed once, it is necessary to take into account;
		if (req_width > __W(rect)) {
			rect.left = rect.right - req_width; // decreases the value of the left side; 
		}

		// takes into account the image margins; left side of the pane rectangle is already set above;
		t_point pt_image = {
			n_left + lay.Image().Margins().Left(), rc_area.top + lay.Image().Margins().Top()
		};

		lay.Image().Anchor(pt_image.x, pt_image.y); // sets the image anchor point for image list draw function;
		lay.Image().Size() = frm_sz;

		n_right = rect.left; // limits the right side of the available area;
	}

	// (4) recalculates each pane of the status bar;
	for (uint16_t i_ = 0; i_ < this->m_ctrl.Panes().Count(); i_++) {
		CPane&  pane = this->m_ctrl.Panes().Pane(i_);

		CFormat& fmt = pane.Format(); fmt;
		TPn_Lay& lay = pane.Layout(); lay;

		t_rect& rect = pane.Layout().Rect(); rect = rc_area; rect.left = n_left; // sets the left side of the pane rect;

		// ToDo: no alignment setting is taken into account, just set the image output point to left-top corner;
		if (pane.Format().Image_Ndx() > -1) {

			// takes into account the image margins;
			t_point pt_image = {
				n_left + lay.Image().Margins().Left(), rc_area.top + lay.Image().Margins().Top()
			};

			lay.Image().Anchor(pt_image.x, pt_image.y); // sets the image anchor point for image list draw function;
			lay.Image().Size() = frm_sz;

			// calculates the required length of the glyph pane; no borders are taken into account, it is supposed there is no one;
			const int32_t req_width = lay.Image().Margins().Left() + lay.Image().Margins().Right() + frm_sz.cx;

			n_left += (frm_sz.cx + lay.Image().Margins().Right()); // takes into account an image width;

			rect.right = n_left; // ToDo: no consideration regarding pane width style option yet;

			if (__W(rect) < static_cast<int32_t>(lay.Fixed()))
				rect.right += lay.Fixed() - __W(rect);
		}
		else { // there is no image; just fixed width is applied;
			rect.right = rect.left + lay.Fixed();

			n_left = rect.right;
		}
	} 
	return n_result;
}

err_code CLayout::Update (const t_rect& _rc_area) {
	_rc_area;

	if (::IsRectEmpty(&_rc_area))
		return this->m_error << __METHOD__ << __e_rect;

	CWindow wnd_ = this->m_ctrl.Window();
	if (false == wnd_.IsWindow())
		return this->m_error << __METHOD__ << (err_code) TErrCodes::eExecute::eState;

	t_rect rc_area_ = ((*this) = _rc_area);

	if (false == wnd_.SetWindowPos(0, &rc_area_, SWP_NOACTIVATE|SWP_NOZORDER))
		return (this->m_error << __METHOD__).Last();

	return this->Update();
}

/////////////////////////////////////////////////////////////////////////////

CLayout&  CLayout::operator <<(const t_rect& _rc_area) {
	this->Update(*this = _rc_area);
	return *this;
}

t_rect    CLayout::operator = (const t_rect& _rc_area) const {
	
	t_rect rc_ = {0};

	if (::IsRectEmpty(&_rc_area)) {
		this->m_error << __METHOD__ << __e_rect;
		return rc_;
	}

	rc_  = _rc_area;
	rc_.top = rc_.bottom - this->Height();
	return rc_;
}