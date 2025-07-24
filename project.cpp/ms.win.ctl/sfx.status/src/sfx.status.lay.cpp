/*
	Created by Tech_dog (ebontrop@gmail.com) on 23-Aug-2020 at 7:35:47a, UTC+7, Novosibirsk, Sunday;
	This is Ebo Pack shared status bar control layout interface implementation file.
*/
#include "sfx.status.lay.h"
#include "sfx.status.ctrl.h" // this header is included here due to exclude cyclic dependencies through header files;

using namespace ex_ui::controls::sfx::status;
using namespace ex_ui::controls::sfx::status::layout;

/////////////////////////////////////////////////////////////////////////////

CStyle:: CStyle (void) : m_e_stick(e_stick::e_left), m_e_width(e_width::e_fixed) {}
CStyle:: CStyle (const CStyle& _src) : CStyle() { *this = _src; }
CStyle::~CStyle (void) {}

/////////////////////////////////////////////////////////////////////////////
const
CStyle::e_stick  CStyle::Stick (void) const { return m_e_stick; }
CStyle::e_stick& CStyle::Stick (void)       { return m_e_stick; }
const
CStyle::e_width  CStyle::Width (void) const { return m_e_width; }
CStyle::e_width& CStyle::Width (void)       { return m_e_width; }

/////////////////////////////////////////////////////////////////////////////

CStyle&   CStyle::operator = (const CStyle& _src) { *this << _src.Stick() << _src.Width(); return *this; }
CStyle&   CStyle::operator <<(const e_stick _style) { this->Stick() = _style; return *this; }
CStyle&   CStyle::operator <<(const e_width _style) { this->Width() = _style; return *this; }

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
		return this->m_error << __METHOD__ << (err_code) TErrCodes::eExecute::eState;
	}

	t_rect rc_area = {0};

	if (false == wnd_.GetClientRect(&rc_area)) {
		return (this->m_error << __METHOD__).Last();
	}

	// (1) updates border position(s);
	CBorder& top_ = this->m_ctrl.Format().Borders().Top();
	top_.Set(CPoint(rc_area.left, rc_area.top), CPoint(rc_area.right, rc_area.top));

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