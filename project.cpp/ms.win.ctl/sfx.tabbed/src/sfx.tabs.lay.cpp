/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Aug-2020 at 6:41:32a, UTC+7, Novosibirsk, Friday;
	This is Ebo Pack shared tabbed control layout interface implementation file;
*/
#include "sfx.tabs.lay.h"
#include "sfx.tabs.ctrl.h"

using namespace ex_ui::controls::sfx::tabbed;
using namespace ex_ui::controls::sfx::tabbed::layout;

/////////////////////////////////////////////////////////////////////////////

CTabs:: CTabs(void) : m_ledge(3), m_rect{0}, m_size{0}, m_gap(0) {
	this->m_size.cy = 31;
	this->m_size.cx = this->m_size.cy * 5; this->m_gap = this->m_size.cy / 2;
}
CTabs::~CTabs(void) {}

/////////////////////////////////////////////////////////////////////////////

uint32_t  CTabs::Gap (void) const { return m_gap; }
uint32_t& CTabs::Gap (void)       { return m_gap; }
bool      CTabs::Gap (const uint32_t _n_value) {
	_n_value;
	const bool b_changed = this->Gap() != _n_value;
	if (b_changed)
		this->m_gap = _n_value;

	return b_changed;
}

uint32_t  CTabs::Height (void) const { return (uint32_t )m_size.cy; }
uint32_t& CTabs::Height (void)       { return (uint32_t&)m_size.cy; }
bool      CTabs::Height (const uint32_t _n_value) {
	_n_value;
	const bool b_changed = this->Height() != _n_value;
	if (b_changed)
		this->m_size.cy = _n_value;

	return b_changed;
}

uint32_t  CTabs::Ledge (void) const { return m_ledge; }
uint32_t& CTabs::Ledge (void)       { return m_ledge; }
bool      CTabs::Ledge (const uint32_t _n_value) {
	_n_value;
	const bool b_changed = this->Ledge() != _n_value;
	if (b_changed)
		this->m_ledge = _n_value;

	return b_changed;
}

t_rect    CTabs::Rect  (void) const { return m_rect ; }

eSide     CTabs::Side  (void) const { return m_sides.Selected()  ; }
eSide&    CTabs::Side  (void)       { return m_sides.Selected()  ; }

const
t_size&   CTabs::Size  (void) const { return m_size; }
uint32_t& CTabs::Width (void)       { return (uint32_t&)m_size.cx; }

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

CLayout:: CLayout (CControl& _ctrl) : m_ctrl(_ctrl) { m_error >> __CLASS__ << __METHOD__ << __s_ok; }
CLayout::~CLayout (void) {}

/////////////////////////////////////////////////////////////////////////////

TError&   CLayout::Error  (void) const { return m_error ; }

err_code  CLayout::Update (void) {

	err_code n_result = __s_ok;

	CWindow wnd_ = this->m_ctrl.Window();

	if (false == wnd_.IsWindow()) {
		return this->m_error << __METHOD__ << (err_code) TErrCodes::eExecute::eState;
	}

	t_rect rc_area = {0};

	if (false == wnd_.GetClientRect(&rc_area)) {
		return (this->m_error << __METHOD__).Last();
	}
#if (0)
	RECT rc_tabs   = rc_area_;
	rc_tabs.bottom = rc_area_.top + m_tabs.Height(); rc_tabs.top += m_tabs.m_ledge;
	m_tabs.m_rect  = rc_tabs;

	int iLeft = rc_tabs.left + m_tabs.Gap();

	ST_Ctrls::CTabs& tabs = m_control.Tabs();
	for (size_t i_ = 0; i_ < tabs.RawTabs().size(); i_++) {
		ST_Ctrls::CTab& tab_ = tabs.Tab(static_cast<INT>(i_));

		RECT rc_tab = { iLeft, rc_area_.top, iLeft + m_tabs.Size().cx, rc_tabs.bottom }; iLeft += (m_tabs.Gap() + m_tabs.Size().cx);
		::CopyRect(&tab_.Layers().Rect(), &rc_tab);
	}
#endif
	// (1) updates border position(s);
	this->m_ctrl.Borders() << rc_area;

	return n_result;
}

err_code  CLayout::Update (const t_rect& _rc_area) {
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

CLayout&  CLayout::operator<<(const t_rect& _rc_area) { this->Update(*this = _rc_area); return *this; }

t_rect    CLayout::operator =(const t_rect& _rc_area) const {
	
	t_rect rc_ = {0};

	if (::IsRectEmpty(&_rc_area)) {
		this->m_error << __METHOD__ << __e_rect;
		return rc_;
	}

	rc_  = _rc_area;
	return rc_;
}