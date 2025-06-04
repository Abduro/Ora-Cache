/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Aug-2020 at 7:35:47a, UTC+7, Novosibirsk, Sunday;
	This is Ebo Pack shared status bar control layout interface implementation file.
*/
#include "sfx.status.lay.h"
#include "sfx.status.ctrl.h"
#if (0)
using namespace ST_Ctrls;
using namespace ST_Ctrls::layout;

/////////////////////////////////////////////////////////////////////////////

CGlyph:: CGlyph (void) : TBase(), m_img_ndx (0) { }
CGlyph:: CGlyph (const CGlyph& _ref) : CGlyph() { *this = _ref; }
CGlyph::~CGlyph (void) {}

/////////////////////////////////////////////////////////////////////////////

DWORD    CGlyph::Image_Ndx (void) const { return m_img_ndx; }
DWORD&   CGlyph::Image_Ndx (void)       { return m_img_ndx; }
bool     CGlyph::Is        (void) const { return(m_img_ndx >= 0 && TBase::Is()); }

/////////////////////////////////////////////////////////////////////////////

CGlyph&  CGlyph::operator = (const CGlyph&  _ref) { (TBase&)*this = (const TBase&)_ref; *this << _ref.Image_Ndx(); return *this; }
CGlyph&  CGlyph::operator <<(const DWORD _img_ndx) { this->Image_Ndx() = _img_ndx; return *this; }

/////////////////////////////////////////////////////////////////////////////

CLayout_Style:: CLayout_Style (void) : m_e_stick(e_stick::e_left), m_e_width(e_width::e_fixed) {}
CLayout_Style:: CLayout_Style (const CLayout_Style& _ref) : CLayout_Style() { *this = _ref; }
CLayout_Style::~CLayout_Style (void) {}

/////////////////////////////////////////////////////////////////////////////
const
CLayout_Style::e_stick  CLayout_Style::Stick (void) const { return m_e_stick; }
CLayout_Style::e_stick& CLayout_Style::Stick (void)       { return m_e_stick; }
const
CLayout_Style::e_width  CLayout_Style::Width (void) const { return m_e_width; }
CLayout_Style::e_width& CLayout_Style::Width (void)       { return m_e_width; }

/////////////////////////////////////////////////////////////////////////////

CLayout_Style&   CLayout_Style::operator = (const CLayout_Style& _ref) { *this << _ref.Stick() << _ref.Width(); return *this; }
CLayout_Style&   CLayout_Style::operator <<(const e_stick _style) { this->Stick() = _style; return *this; }
CLayout_Style&   CLayout_Style::operator <<(const e_width _style) { this->Width() = _style; return *this; }

/////////////////////////////////////////////////////////////////////////////

CPanel_Layout:: CPanel_Layout (void) : m_rect{0}, m_fixed(0) {}
CPanel_Layout:: CPanel_Layout (const CPanel_Layout& _ref) : CPanel_Layout() { *this = _ref; }
CPanel_Layout::~CPanel_Layout (void) {}

/////////////////////////////////////////////////////////////////////////////
const
TAlign& CPanel_Layout::Align  (void) const { return m_align; }
TAlign& CPanel_Layout::Align  (void)       { return m_align; }
DWORD   CPanel_Layout::Fixed  (void) const { return m_fixed; }
DWORD&  CPanel_Layout::Fixed  (void)       { return m_fixed; }
const
CImage& CPanel_Layout::Image  (void) const { return m_image; }
CImage& CPanel_Layout::Image  (void)       { return m_image; }
const
RECT&   CPanel_Layout::Rect   (void) const { return m_rect ; }
RECT&   CPanel_Layout::Rect   (void)       { return m_rect ; }
const
CLayout_Style&  CPanel_Layout::Style (void) const { return m_style; }
CLayout_Style&  CPanel_Layout::Style (void)       { return m_style; }
const
TTextLayEx&  CPanel_Layout::Text   (void) const { return m_text ; }
TTextLayEx&  CPanel_Layout::Text   (void)       { return m_text ; }

HRESULT CPanel_Layout::Update (void) { HRESULT hr_ = S_OK;

	if (::IsRectEmpty(&this->Rect())) { // makes internal rectangles empty for preventing draw procedure to do anything;
		m_image.Rect().right = m_image.Rect().left;
		m_text.Rect().right = m_text.Rect().left;
	}
	else {
		// takes care about image first;
		if (m_image.Is()) {

			const LONG n_req_width = m_image.Size().cx + m_image.Margins().Left() + m_image.Margins().Right();

			if (__W(this->Rect()) < n_req_width) { // not enough room for drawing an image;
				m_image.Rect().right = m_image.Rect().left;
			}
			else {
				::CopyRect(&m_image.Rect(), &this->Rect());
				m_image.Rect().right = m_image.Rect().left + n_req_width; m_image.Rect().left += m_image.Margins().Left();
				m_image.Rect().top += m_image.Margins().Top();
			}
		}
		else {
			m_image.Rect().right = m_image.Rect().left = this->Rect().left; // just makes zero width;
		}

		// takes care about text;
		if (m_text.Is()) {
			const INT n_left = m_image.Rect().right;
			if (this->Rect().right - n_left <= 0) { // no room for drawing a text;
				m_text.Rect().right = m_text.Rect().left;
			}
			else {
				::CopyRect(&m_text.Rect(), &this->Rect());
				m_text.Rect().left = n_left + m_text.Margins().Left();
				m_text.Rect().right -= m_text.Margins().Right();
			}
		}
	}

	return hr_;
}

/////////////////////////////////////////////////////////////////////////////

CPanel_Layout&  CPanel_Layout::operator = (const CPanel_Layout& _ref) {
	*this << _ref.Align() << _ref.Image() << _ref.Rect() << _ref.Style() << _ref.Text() ; return *this; }
CPanel_Layout&  CPanel_Layout::operator <<(const CImage& _image) { this->Image() = _image; return *this; }
CPanel_Layout&  CPanel_Layout::operator <<(const CLayout_Style& _style) { this->Style() = _style; return *this; }
CPanel_Layout&  CPanel_Layout::operator <<(const TTextLayEx&  _text ) { this->Text () = _text; return *this; }
CPanel_Layout&  CPanel_Layout::operator <<(const RECT &  _rect ) { ::CopyRect(&this->Rect(), &_rect); return *this; }
CPanel_Layout&  CPanel_Layout::operator <<(const TAlign& _align) { this->Align() = _align; return *this; }

/////////////////////////////////////////////////////////////////////////////

TStatusLay:: CStatus_Layout(CStatusBar& _ctrl) : m_control(_ctrl), m_height(28) { m_error << __MODULE__ << S_OK >> __MODULE__; }
TStatusLay::~CStatus_Layout(void) {}

/////////////////////////////////////////////////////////////////////////////

TErrorRef  TStatusLay::Error  (void) const { return m_error ; }
DWORD      TStatusLay::Height (void) const { return m_height; }
DWORD&     TStatusLay::Height (void)       { return m_height; }

const
CGlyph&    TStatusLay::Glyph  (void) const { return m_glyph; }
CGlyph&    TStatusLay::Glyph  (void)       { return m_glyph; }

const bool TStatusLay::Is     (void) const { return m_height > 0; }
const
CMargins&  TStatusLay::Margins(void) const { return m_margins; }
CMargins&  TStatusLay::Margins(void)       { return m_margins; }
HRESULT    TStatusLay::Update (void)       {
	m_error << __MODULE__ << S_OK;

	CWindow wnd_ = m_control.Window();
	if (wnd_.IsWindow() == FALSE)
		return (m_error = __DwordToHresult(ERROR_INVALID_STATE));

	RECT rc_area  = {0};
	const BOOL b_result = wnd_.GetClientRect(&rc_area);
	if (FALSE == b_result) {
		return m_error = ::GetLastError();
	}
	// (1) updates border position(s);
	m_control.Borders().Top().Position().Start().x = rc_area.left;
	m_control.Borders().Top().Position().Start().y = rc_area.top ;

	m_control.Borders().Top().Position().End().x = rc_area.right;
	m_control.Borders().Top().Position().End().y = rc_area.top  ;

	// (2) sets left and right side values for calculating auto-size-style-width panel(s);
	INT n_left = rc_area.left;
	INT n_right = rc_area.right;

	// (3) calculates glyph rectangle if necessary;
	if (m_glyph.Is()) {
		(ex_ui::controls::layout::CPlacement&)m_glyph << rc_area;
		m_glyph.Rect().left = rc_area.right - m_glyph.Size().cx - m_glyph.Margins().Right() - m_glyph.Margins().Left();

		n_right = m_glyph.Rect().left;
	}

	// (4) updates panel(s) rectangle(s);
	CPanels& panels = m_control.Panels();
	if (panels.Count() == 0)
		return m_error;

	for (size_t i_ = panels.Count(); 0 < i_; i_--) { // backward iteration is required for making proper calculation of auto-width panels;
		CPanel& pan_ = panels.Panel(static_cast<DWORD>(i_ - 1));

		RECT& rc_pan = pan_.Layout().Rect(); rc_pan.top = rc_area.top; rc_pan.bottom = rc_area.bottom;

		const TLayStyle& style = pan_.Layout().Style();
		const bool b_auto = style.Width() == TLayStyle::e_width::e_auto;

		if (style.Stick() == TLayStyle::e_stick::e_right) {

			rc_pan.right = n_right;
			rc_pan.left = b_auto ? n_left : rc_pan.right - pan_.Layout().Fixed();

			if (rc_pan.left < n_left)
				rc_pan.left = n_left;
			if (b_auto == false)
				n_right = rc_pan.left;
		}
		else
		if (style.Stick() == TLayStyle::e_stick::e_left) {

			rc_pan.left = n_left;
			rc_pan.right = b_auto ? n_right : rc_pan.left + pan_.Layout().Fixed();

			if (rc_pan.right > n_right)
				rc_pan.right = n_right;

			if (b_auto == false) {
				n_left = rc_pan.right;
			}
		}
		else
			continue;

		if (pan_.Borders().Left().Is()) {
			pan_.Borders().Left().Position().Start().x = pan_.Borders().Left().Position().End().x = rc_pan.left;
			pan_.Borders().Left().Position().Start().y = rc_pan.top + m_control.Borders().Top().Thickness();
			pan_.Borders().Left().Position().End  ().y = rc_pan.bottom;
		}
		if (pan_.Borders().Right().Is()) {
			pan_.Borders().Right().Position().Start().x = pan_.Borders().Right().Position().End().x = rc_pan.right;
			pan_.Borders().Right().Position().Start().y = rc_pan.top + m_control.Borders().Top().Thickness();
			pan_.Borders().Right().Position().End  ().y = rc_pan.bottom;
		}

		pan_.Layout().Update(); // updates internal layout in accordance with new rectangle of a panel;
		if (pan_.Child().Is()) {

			const bool b_nosize = (0 != pan_.Child().Style());
			// make child window rectangle in accordance with child alignment, status bar top border;
			RECT rc_child = {rc_pan.left, rc_pan.top + static_cast<LONG>(m_control.Borders().Top().Thickness()), rc_pan.right, rc_pan.bottom };
			if (b_nosize) {
				RECT rc_wnd = {0};
				::GetWindowRect(pan_.Child().Handle(), &rc_wnd);
				::MapWindowPoints(HWND_DESKTOP, m_control.Window(), (LPPOINT)&rc_wnd, 0x2);

				switch (pan_.Child().Align().Horz()) {
				case THorzAlign::eLeft  : { rc_child.right = rc_child.left  + __W(rc_wnd); } break;
				case THorzAlign::eRight : { rc_child.left  = rc_child.right - __W(rc_wnd); } break;
				default:
					const INT n_left_loc = rc_child.left + (__W(rc_child) - __W(rc_wnd)) / 2;
					rc_child.left = n_left_loc;
					rc_child.right = n_left_loc + __W(rc_wnd);
				}

				switch (pan_.Child().Align().Vert()) {
				case TVertAlign::eBottom : { rc_child.top = rc_child.bottom - __H(rc_wnd); } break;
				case TVertAlign::eTop    : { rc_child.bottom = rc_child.top + __H(rc_wnd); } break;
				default:
					const LONG n_top = rc_child.top + (__H(rc_child) - __H(rc_wnd)) / 2;
					rc_child.top = n_top;
					rc_child.bottom = n_top + __H(rc_wnd);
				}
			}
			::SetWindowPos(pan_.Child().Handle(), NULL,
				rc_child.left, rc_child.top, __W(rc_child), __H(rc_child), pan_.Child().Style().Value());
		}
	}
	
	return m_error;
}

HRESULT    TStatusLay::Update (const RECT& _rc_area) {
	m_error << __MODULE__ << S_OK;

	if (::IsRectEmpty(&_rc_area))
		return (m_error = OLE_E_INVALIDRECT);

	CWindow wnd_ = m_control.Window();
	if (wnd_.IsWindow() == FALSE)
		return (m_error = __DwordToHresult(ERROR_INVALID_STATE));

	RECT rc_area_  = ((*this) = _rc_area);
	const BOOL b_result = wnd_.SetWindowPos(0, &rc_area_, SWP_NOACTIVATE|SWP_NOZORDER);
	if (FALSE == b_result)
		m_error.Last();
	else
		this->Update();

	return m_error;
}

/////////////////////////////////////////////////////////////////////////////

TStatusLay&  TStatusLay::operator<<(const RECT& _rc_area) {
	this->Update(*this = _rc_area);
	return *this;
}

const RECT   TStatusLay::operator =(const RECT& _rc_area) const {
	m_error << __MODULE__ << S_OK;

	RECT rc_ = {0};

	if (::IsRectEmpty(&_rc_area)) {
		(m_error = OLE_E_INVALIDRECT);
		return rc_;
	}

	rc_  = _rc_area;
	rc_.top = rc_.bottom - this->Height();
	return rc_;
}
#endif