/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Aug-2020 at 6:41:32a, UTC+7, Novosibirsk, Friday;
	This is Ebo Pack shared tabbed control layout interface implementation file;
*/
#include "sfx.tabs.lay.h"
#include "sfx.tabs.ctrl.h"

using namespace ex_ui::controls::sfx::tabbed;
using namespace ex_ui::controls::sfx::tabbed::layout;

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
#if (0)
/////////////////////////////////////////////////////////////////////////////
#if (0)
CTab:: CTab (void) { ::SetRectEmpty(&m_rect); }
CTab:: CTab (const CTab& _ref) : CTab() { *this = _ref; }
CTab::~CTab (void) {}

/////////////////////////////////////////////////////////////////////////////
const
RECT&   CTab::Rect (void) const { return m_rect; }
HRESULT CTab::Rect (const RECT& _rect) { if (::IsRectEmpty(&_rect)) return OLE_E_INVALIDRECT; ::CopyRect(&m_rect, &_rect); return S_OK; } 

/////////////////////////////////////////////////////////////////////////////

CTab&   CTab::operator = (const CTab& _ref) { *this << _ref.Rect(); return *this; }
CTab&   CTab::operator <<(const RECT& _rect) { this->Rect(_rect); return *this; }
#endif
/////////////////////////////////////////////////////////////////////////////

TTabs:: CTabs(void) : m_gap(0), m_ledge(3) {
	::SetRectEmpty(&m_rect); m_size.cy = 31; m_size.cx = m_size.cy * 5; m_gap = m_size.cy / 2;
}
TTabs::~CTabs(void) {}

/////////////////////////////////////////////////////////////////////////////

DWORD    TTabs::Gap   (void) const { return m_gap; }
DWORD&   TTabs::Gap   (void)       { return m_gap; }
DWORD    TTabs::Height(void) const { return (DWORD )m_size.cy; }
DWORD&   TTabs::Height(void)       { return (DWORD&)m_size.cy; }
DWORD    TTabs::Ledge (void) const { return m_ledge; }
DWORD&   TTabs::Ledge (void)       { return m_ledge; }
RECT     TTabs::Rect  (void) const { return m_rect  ; }
TSide    TTabs::Side  (void) const { return m_side.Selected()  ; }
TSide&   TTabs::Side  (void)       { return m_side.Selected()  ; }
const
SIZE&    TTabs::Size  (void) const { return m_size  ; }
DWORD&   TTabs::Width (void)       { return (DWORD&)m_size.cx; }

/////////////////////////////////////////////////////////////////////////////

CTabLayout:: CTabLayout (TTabCtrl& _ctrl) : m_control(_ctrl) { m_error << __MODULE__ << S_OK >> __MODULE__; }
CTabLayout::~CTabLayout (void) {}

/////////////////////////////////////////////////////////////////////////////

TErrorRef   CTabLayout::Error  (void) const { return m_error; }
const
CMargins&   CTabLayout::Margins(void) const { return m_margins; }
CMargins&   CTabLayout::Margins(void)       { return m_margins; }
RECT        CTabLayout::Page   (void) const {
	m_error << __MODULE__ << S_OK;
	RECT rc_page = {0};

	CWindow wnd_ = m_control.Window();
	if (wnd_.IsWindow() == FALSE) {
		m_error << OLE_E_INVALIDHWND;
		return rc_page;
	}

	wnd_.GetClientRect(&rc_page); rc_page.top = m_tabs.m_rect.bottom;
	
	rc_page.left   += m_control.Format().Borders().Left().Thickness();
	rc_page.right  -= m_control.Format().Borders().Right().Thickness();
	rc_page.bottom -= m_control.Format().Borders().Bottom().Thickness();
	
	m_margins.ApplyTo(rc_page);

	return rc_page;
}
const
TTabs&      CTabLayout::Tabs   (void) const { return m_tabs ; }
TTabs&      CTabLayout::Tabs   (void)       { return m_tabs ; }

#endif