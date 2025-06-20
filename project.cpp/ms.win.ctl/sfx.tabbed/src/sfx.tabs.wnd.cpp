/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Jul-2020 at 9:02:30p, UTC+7, Novosibirsk, Sunday;
	This is Ebo Pack Sfx tab control window interface implementation file.
*/
#include "sfx.tabs.wnd.h"
#include "sfx.tabs.ctrl.h"

using namespace ex_ui::controls::sfx::tabbed;

/////////////////////////////////////////////////////////////////////////////

CWnd:: CWnd(CControl& _ctrl) : TWindow(), m_ctrl(_ctrl) {
	TWindow::Handlers().Draw().Subscribe (this); TWindow::Handlers().Live().Subscribe(this);
	TWindow::Handlers().Frame().Subscribe(this);
#if (1)
	TWindow::m_error << m_font.Create(
		this->m_ctrl.Format().Font().Family(), this->m_ctrl.Format().Font().Options(), this->m_ctrl.Format().Font().Size()
	);

	m_font_vert.Angle(90);

	TWindow::m_error << m_font_vert.Create(
		this->m_ctrl.Format().Font().Family(), this->m_ctrl.Format().Font().Options(), this->m_ctrl.Format().Font().Size()
	);

#endif
}
CWnd::~CWnd(void) {
	TWindow::Handlers().Draw().Unsubscribe (this); TWindow::Handlers().Live().Unsubscribe(this);
	TWindow::Handlers().Frame().Unsubscribe(this);
}

/////////////////////////////////////////////////////////////////////////////

err_code CWnd::IEvtDraw_OnErase (const HDC _dev_ctx) {
	_dev_ctx;
	/*
	it is supposed the main window of the test app already sets the background color for the shared window base class;
	*/
#if (0)
	static bool  b_fst_time = true;
	if (false == b_fst_time) { // parent window must care about this;
		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setclasslongptra ;
		HBRUSH brush = ::CreateSolidBrush(shared::Get_Theme().Get(TThemePart::e_form, TThemeElement::e_back));
		::SetClassLongPtr(*this, GCLP_HBRBACKGROUND, (LONG_PTR)brush);
		b_fst_time = true;
	}
#endif
#if (1)
	t_rect rc_area = {0};
	TWindow::GetClientRect(&rc_area);  // perhaps the layout knows about available area better than the window itself;

	CZBuffer z_buffer(_dev_ctx, rc_area);
#if (0)
	const CComplSet& set_ = shared::ThemeTriplets().Get(TClrPredefined::e_Red_n_Navy_n_Yellow); set_;

	z_buffer.Draw(rc_area, set_.Dark());
#elif (1==0)
	z_buffer.Draw(rc_area, shared::Get_Theme().Get(TThemePart::e_form, TThemeElement::e_back));
#else
	// (1) fills the background goes first;
	z_buffer.Draw(rc_area, this->m_ctrl.Format().Bkgnd().Solid().ToRgb()); // ToRgb() must be called, otherwise, black screen due to GDI does not know alpha channel;
#endif
	using ex_ui::controls::borders::TRawBorders;
	// (2) draws tabbed control borders; if no tabs there;
	if (this->m_ctrl.Tabs().Count() == 0) {
		for(TRawBorders::const_iterator iter_ = this->m_ctrl.Borders().Raw().begin(); iter_ != this->m_ctrl.Borders().Raw().end(); ++iter_) {
			const CBorder& border = iter_->second;
			z_buffer.Draw( border );
		}
	}
	// (3) draws active tab borders;
	const TRawBorders& act_tab = this->m_ctrl.Layout().Tabs().Active().Raw();
	const rgb_color act_clr = this->m_ctrl.Format().Border_Clrs().Get(TStateValue::eSelected);
	const rgb_color nrm_clr = this->m_ctrl.Format().Border_Clrs().Get(TStateValue::eNormal);

	for (TRawBorders::const_iterator iter_ = act_tab.begin(); iter_ != act_tab.end(); ++iter_) {
		const CBorder& border = iter_->second;
		z_buffer.Draw( border, act_clr);
	}

	static const dword dw_flags = DT_CENTER|DT_VCENTER|DT_END_ELLIPSIS|DT_NOCLIP|DT_NOPREFIX|DT_SINGLELINE;
	// (4) draws captions of the tabs; the color of the text depends on activity of the tab and the same as tab border color;
	if (this->m_ctrl.Layout().Tabs().Sides().IsHorz()) {

		const TTabArray& tabs = this->m_ctrl.Tabs().Raw();
		for (int16_t i_ = 0; i_ < this->m_ctrl.Tabs().Count(); i_++) {
			const CTab& tab_ = tabs.at(i_);
			z_buffer.Draw(tab_.Caption(), this->m_font.Handle(), tab_.Rect(), i_ == this->m_ctrl.Tabs().Active() ? act_clr : nrm_clr, dw_flags);
		}
	}
	if (this->m_ctrl.Layout().Tabs().Sides().IsVert()) {

		const TTabArray& tabs = this->m_ctrl.Tabs().Raw();
		for (int16_t i_ = 0; i_ < this->m_ctrl.Tabs().Count(); i_++) {
			const CTab& tab_ = tabs.at(i_);
			z_buffer.Draw(tab_.Caption(), this->m_font_vert.Handle(), tab_.Rect(), i_ == this->m_ctrl.Tabs().Active() ? act_clr : nrm_clr, dw_flags);
		}
	}

#endif
	// https://learn.microsoft.com/en-us/windows/win32/winmsg/wm-erasebkgnd ;
	// this message is handled; the handlers of the most windows messages returns 0 to indicate the message is handled,
	// but erase background requires not zero value for doing that;
	err_code n_result = __s_false;
	return   n_result;
}

err_code CWnd::IEvtDraw_OnPaint (const w_param, const l_param) { // both input args are useless;

	using WTL::CPaintDC;

	CPaintDC dc_(*this);
#if (0)
	t_rect rc_area = {0};
	TWindow::GetClientRect(&rc_area);

	CZBuffer z_buffer(dc_.m_hDC, rc_area);

	z_buffer.Draw(rc_area, TRgbQuad(shared::Get_Theme().Get(TThemePart::e_form, TThemeElement::e_back)));

	// (1) status bar top border if specified;
	const CBorder& top_ = this->m_ctrl.Borders().Top();

	if (top_.Is_valid()) {
		z_buffer.Draw(top_);
	}
#endif
	err_code n_result = __s_false;  // this message is handled;
	return   n_result;
}

/////////////////////////////////////////////////////////////////////////////

err_code CWnd::IEvtLife_OnCreate  (const w_param, const l_param) {

	err_code n_result = __s_false;
	return   n_result;
}

err_code CWnd::IEvtLife_OnDestroy (const w_param, const l_param) {

	err_code n_result = __s_false;
	return   n_result;
}

/////////////////////////////////////////////////////////////////////////////

using eState = IFormEvtSink::eState;
using eEdges = IFormEvtSink::eEdges;

err_code CWnd::IEvtFrame_OnSize   (const eState _e_state, const t_size) {
	_e_state;
	err_code n_result = __s_false;
	return   n_result;
}

err_code CWnd::IEvtFrame_OnSizing (const eEdges _edges, t_rect* _p_rect) {
	_edges; _p_rect;
	err_code n_result = __s_false;
	return   n_result;
}

#if (0)
using namespace ST_Ctrls;
using namespace ST_Ctrls::_impl;
using namespace ST_Ctrls::format;

using namespace ex_ui;
using namespace ex_ui::controls;

#include "shared.uix.gdi.provider.h"
#include "shared.uix.gen.hsl.h"
#include "shared.uix.gen.theme.h"

using namespace ex_ui::draw;

/////////////////////////////////////////////////////////////////////////////
#define SAFE_LOCK_RENDER() SAFE_LOCK(this->m_guard);
/////////////////////////////////////////////////////////////////////////////

CTabs_Wnd:: CTabs_Wnd(CTabbed& _ctrl) : m_parent(NULL), m_control(_ctrl), m__TTips(*this) {
	m_control.Format() = CSymantec_NA_Tab();
	m_control.Format().Borders().Thickness(1);
}

CTabs_Wnd::~CTabs_Wnd(void) {
	if (TWindow::IsWindow())
		TWindow::SendMessage(WM_CLOSE);
}

/////////////////////////////////////////////////////////////////////////////

LRESULT CTabs_Wnd::OnCreate   (UINT _u_msg, WPARAM _wp, LPARAM _lp, BOOL& _b_hand) {
	_u_msg; _wp; _lp; _b_hand = TRUE;
	HRESULT hr__ = m__TTips.Create(*this); hr__;
	m__TTips.SetMultiLineAuto(true);
	return 0;
}

LRESULT CTabs_Wnd::OnDestroy  (UINT _u_msg, WPARAM _wp, LPARAM _lp, BOOL& _b_hand) {
	_u_msg; _wp; _lp; _b_hand = TRUE;
	m__TTips.Destroy();
	return 0;
}

LRESULT CTabs_Wnd::OnErase    (UINT _u_msg, WPARAM _wp, LPARAM _lp, BOOL& _b_hand) {
	_u_msg; _wp; _lp; _b_hand = TRUE;
#if (0)
	if (CTheme::IsEnabled() == false)
		return TCtrlWnd::OnErase(_u_msg, _wp, _lp, _b_hand);

	// https://docs.microsoft.com/en-us/windows/win32/api/uxtheme/nf-uxtheme-openthemedata
	HTHEME hTheme = ::OpenThemeData(*this, L"tab");
	if (NULL == hTheme)
		return TCtrlWnd::OnErase(_u_msg, _wp, _lp, _b_hand);
#endif
	RECT rc_ = {0};
	TWindow::GetClientRect(&rc_);

	const HDC hDC = reinterpret_cast<HDC>(_wp);
	CZBuffer dc_(hDC, rc_);
#if (0)
	// https://docs.microsoft.com/en-us/windows/win32/api/uxtheme/nf-uxtheme-drawthemebackground
	// https://docs.microsoft.com/en-us/windows/win32/controls/parts-and-states
	HRESULT hr_ = ::DrawThemeBackground(hTheme, dc_, TABP_AEROWIZARDBODY, 0, &rc_, NULL);
	if (SUCCEEDED(hr_))
		_b_hand = TRUE;
	::CloseThemeData(hTheme);
#endif
	TTabbedFmt& fmt_ = m_control.Format();
	TTabsLay& lay_ = m_control.Layout();
	// (1) draws entire tab control background by solid color;
	COLORREF clr_solid = fmt_.Bkgnd().Solid();
	dc_.DrawSolidRect(rc_, clr_solid);
	// (2) draws parent background in tabs area ledge;
	{
		RECT rc_parent = rc_; rc_parent.bottom = rc_.top + lay_.Tabs().Ledge();
		SAFE_LOCK_RENDER();
		if (m_parent != NULL) {
			m_parent->DrawParentBackground(*this, dc_, rc_parent);
		}
	}
	// (3) borders of tab control;
	rc_.top += lay_.Tabs().Ledge();
	rc_.top  = lay_.Tabs().Rect().bottom; // this is for top-placed tabs only; other tab placements are not developed yet;
	{
		const CBorder& border = fmt_.Borders().Left();
		dc_.DrawLine(rc_.left, rc_.top, rc_.left, rc_.bottom, border.Color(), border.Thickness());
	}
	{
		const CBorder& border = fmt_.Borders().Right();
		dc_.DrawLine(rc_.right - border.Thickness(), rc_.top, rc_.right - border.Thickness(), rc_.bottom, border.Color(), border.Thickness());
	}
	{
		const CBorder& border = fmt_.Borders().Bottom();
		dc_.DrawLine(rc_.left, rc_.bottom - border.Thickness(), rc_.right, rc_.bottom - border.Thickness(), border.Color(), border.Thickness());
	}
	// dc_.DrawRectangle(rc_, clr_borders, fmt_.Borders().Top().Thickness());

	// (4) tab area background;
	RECT rc_tabs   = lay_.Tabs().Rect();
	if (::IsRectEmpty(&rc_tabs) ==  FALSE) {
		RECT rc_back_g = rc_tabs; rc_back_g.bottom = rc_back_g.top + __H(rc_back_g) / 4;
		RECT rc_back_s = rc_tabs; rc_back_s.top = rc_back_g.bottom;

		dc_.DrawSolidRect(rc_tabs, fmt_.Bkgnd().Gradient().c1());
		dc_.DrawRectangle(
			rc_back_g, fmt_.Bkgnd().Gradient().c0(), fmt_.Bkgnd().Gradient().c1(), true, 255
		);
	}

	const ST_Ctrls::TTabArray& tabs = m_control.Tabs().RawTabs();
	UINT n_active  = m_control.Tabs().Active();
	if ( n_active >= tabs.size())
	     n_active  = 0;

	// (5) draws normal tabs
	for (size_t i_ = 0; i_ < tabs.size(); i_++) {
		const CTab& tab_ = tabs[i_];
		const RECT& rec_ = tab_.Layers().Rect();

		if (n_active == i_)
			continue;

		// (5a) normal tab background;
		dc_.DrawRectangle(
			rec_, fmt_.Tabs().Normal().Bkgnd().Gradient().c0(), fmt_.Tabs().Normal().Bkgnd().Gradient().c1(), true, 255
		);

		CColour_Ex clr_dark = fmt_.Tabs().Normal().Bkgnd().Gradient().c1(); clr_dark.Lighten(20);
		CColour_Ex clr_lite = fmt_.Tabs().Normal().Bkgnd().Gradient().c0(); clr_lite.Darken(20);
		// (5b) normal tab borders;
		dc_.DrawLine( rec_.right - 1, rec_.top + 1, rec_.right - 1, rec_.bottom , clr_dark ); // right side (dark);
		dc_.DrawLine( rec_.left  + 0, rec_.top + 1, rec_.left  + 0, rec_.bottom , clr_dark ); // left side (light);
		dc_.DrawLine( rec_.left  + 0, rec_.top + 0, rec_.right - 0, rec_.top + 0, clr_dark ); // top edge of tab (light);

		// (5c) layer image if any;
		const TCtrlState curr_(tab_.State().Value());
		const ex_ui::controls::layout::CLayersEx& layers  = tab_.Layers();
		if (layers.Images().Is()) {
			if (layers.Images().Cache().Has(curr_)) {
				m_bkg_rnd.Draw(dc_, rec_, layers.Images().Cache().Get(curr_));
			}
		}

		// (5d) tab caption;
		if (NULL == tab_.Caption())
			continue;

		DWORD dw_opts = CFontOptions::eExactSize;
		if (fmt_.Font().Options().Has(CFontOptions::eBold))
			dw_opts |= CFontOptions::eBold ;

		ex_ui::draw::CFont tab_cap_fnt_(
			fmt_.Font().Family(), dw_opts, 18
		);

		RECT rc_cap = rec_; rc_cap.bottom -= 4; // removes some room due to tab bottom horizontal separator;
		dc_.DrawTextExt(
			tab_.Caption (),
			tab_cap_fnt_   ,
			rc_cap         ,
			fmt_.Tabs().Normal().Font().Fore(),
			DT_VCENTER|DT_CENTER|DT_END_ELLIPSIS|DT_NOCLIP|DT_NOPREFIX|DT_SINGLELINE
		);
	}

	// (6) draws active tab;
	for (size_t i_ = 0; i_ < tabs.size(); i_++) {
		const CTab& tab_ = tabs[i_];
		const RECT& rec_ = tab_.Layers().Rect();
		
		if (n_active != i_)
			continue;

		// (6a) active tab background;
		dc_.DrawRectangle(
			rec_, fmt_.Tabs().Active().Bkgnd().Gradient().c0(), fmt_.Tabs().Active().Bkgnd().Gradient().c1(), true, 100
		);

		CColour_Ex clr_dark = fmt_.Tabs().Active().Bkgnd().Gradient().c1(); clr_dark.Darken(10);
		CColour_Ex clr_lite = fmt_.Tabs().Active().Bkgnd().Gradient().c0(); clr_lite.Lighten(10);
#if (0)
		// (6b) active tab borders;
		dc_.DrawLine( rec_.right - 1, rec_.top + 1, rec_.right - 1, rec_.bottom , clr_dark ); // right side (dark);
		dc_.DrawLine( rec_.left  + 0, rec_.top + 1, rec_.left  + 0, rec_.bottom , clr_lite ); // left side (light);
		dc_.DrawLine( rec_.left  + 0, rec_.top + 1, rec_.right - 1, rec_.top + 1, clr_lite ); // top edge of tab (light);
#else
		dc_.DrawLine( rec_.right - 1, rec_.top + 0, rec_.right - 1, rec_.bottom , fmt_.Tabs().Active().Borders().Right().Color());
		dc_.DrawLine( rec_.left  + 0, rec_.top + 1, rec_.left  + 0, rec_.bottom , fmt_.Tabs().Active().Borders().Left().Color());
		dc_.DrawLine( rec_.left  + 0, rec_.top + 0, rec_.right - 0, rec_.top + 0, fmt_.Tabs().Active().Borders().Top().Color());
#endif
#if (0)
		// (6c ) active separator (from top to bottom);
		// (6ca) the lighten top line; it shouldn't cross the bottom of the area of active tab;
		{
			dc_.DrawLine( rc_tabs.left, rc_tabs.bottom - 0x4, rec_.left, rc_tabs.bottom - 0x4, clr_lite );
			dc_.DrawLine( rec_.right, rc_tabs.bottom - 0x4, rc_tabs.right, rc_tabs.bottom - 0x4, clr_lite );
		}
			
		dc_.DrawLine( rc_tabs.left, rc_tabs.bottom - 0x3, rc_tabs.right, rc_tabs.bottom - 0x3, fmt_.Tabs().Active().Bkgnd().Gradient().c1() );
		dc_.DrawLine( rc_tabs.left, rc_tabs.bottom - 0x2, rc_tabs.right, rc_tabs.bottom - 0x2, clr_dark );
		dc_.DrawLine( rc_tabs.left, rc_tabs.bottom - 0x1, rc_tabs.right, rc_tabs.bottom - 0x1, fmt_.Bkgnd().Gradient().c1() );
#else
		{
			dc_.DrawLine( rc_tabs.left, rc_tabs.bottom - 0x1, rec_.left, rc_tabs.bottom - 0x1, fmt_.Borders().Top().Color() );
			dc_.DrawLine( rec_.right, rc_tabs.bottom - 0x1, rc_tabs.right, rc_tabs.bottom - 0x1, fmt_.Borders().Top().Color() );
		}
#endif
		// (6c) layer image if any;
		const TCtrlState curr_(tab_.State().Value());
		const ex_ui::controls::layout::CLayersEx& layers  = tab_.Layers();
		const UINT n_count = layers.Images().Cache().Count(); n_count;
		if (layers.Images().Is()) {
			if (layers.Images().Cache().Has(curr_)) {
				m_bkg_rnd.Draw(dc_, rec_, layers.Images().Cache().Get(curr_));
			}
		}
		// (6d ) tab caption;
		if (NULL == tab_.Caption())
			continue;

		DWORD dw_opts = CFontOptions::eExactSize;
		if (fmt_.Font().Options().Has(CFontOptions::eBold))
			dw_opts |= CFontOptions::eBold ;

		ex_ui::draw::CFont tab_cap_fnt_(
			fmt_.Font().Family(), dw_opts, 18
		);

		RECT rc_cap = rec_; rc_cap.bottom -= 0; // removes some room due to tab bottom horizontal separator;
		dc_.DrawTextExt(
			tab_.Caption (),
			tab_cap_fnt_   ,
			rc_cap         ,
			fmt_.Tabs().Active().Font().Fore(),
			DT_VCENTER|DT_CENTER|DT_END_ELLIPSIS|DT_NOCLIP|DT_NOPREFIX|DT_SINGLELINE
		);
	}
	// (7) draws active tab page borders;
	if (tabs.empty() == false && 0 <= n_active) {
#if (0)
		// (7a) left side border;
		dc_.DrawLine(rc_.left, rc_tabs.bottom - 1, rc_.left, rc_.bottom, fmt_.Tabs().Active().Bkgnd().Gradient().c1());
		// (7b) bottom side border;
		dc_.DrawLine(rc_.left, rc_.bottom - 1, rc_.right, rc_.bottom - 1, fmt_.Tabs().Active().Bkgnd().Gradient().c1());
		// (7c) right side border;
		dc_.DrawLine(rc_.right - 1, rc_tabs.bottom - 1, rc_.right - 1, rc_.bottom, fmt_.Tabs().Active().Bkgnd().Gradient().c1());
#else
		//dc_.DrawLine(rc_.left, rc_tabs.bottom - 1, rc_.left, rc_.bottom, fmt_.Borders().Left().Color());
#endif
	}

	return 0;
}

LRESULT CTabs_Wnd::OnLButtonDn(UINT _u_msg, WPARAM _wp, LPARAM _lp, BOOL& _b_hand) {
	_u_msg; _wp; _lp; _b_hand = TRUE;
	LRESULT l_res   = 0;
	const POINT pt_ = {
		LOWORD(_lp), HIWORD(_lp)
	};
	const INT n_clicked = m_control.Tabs().Has(pt_);
	if (n_clicked < 0)
		return l_res;
	else if (n_clicked != m_control.Tabs().Active() && SUCCEEDED(m_control.Tabs().Active(n_clicked))) {
		m_control.Refresh();
		((ITabEvents&)m_control).ITabEvent_OnSelect(n_clicked);
		((IControlEvent&)m_control).IControlEvent_OnClick(m_control.Tabs().Tab(n_clicked).Id());
	}
	return  l_res;
}

LRESULT CTabs_Wnd::OnLButtonUp(UINT _u_msg, WPARAM _wp, LPARAM _lp, BOOL& _b_hand) {
	_u_msg; _wp; _lp; _b_hand;
	LRESULT l_res = 0;
	return  l_res;
}

LRESULT CTabs_Wnd::OnMouseMove(UINT _u_msg, WPARAM _wp, LPARAM _lp, BOOL& _b_hand) {
	_u_msg; _wp; _lp; _b_hand;
	LRESULT l_res = 0;
	return  l_res;
}

LRESULT CTabs_Wnd::OnMouseOut (UINT _u_msg, WPARAM _wp, LPARAM _lp, BOOL& _b_hand) {
	_u_msg; _wp; _lp; _b_hand;
	LRESULT l_res = 0;
	return  l_res;
}

LRESULT CTabs_Wnd::OnPaint    (UINT _u_msg, WPARAM _wp, LPARAM _lp, BOOL& _b_hand) {
	_u_msg; _wp; _lp; _b_hand;
	WTL::CPaintDC dc_(m_hWnd);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////

LRESULT CTabs_Wnd::OnDispInfo (INT _ctl_id, LPNMHDR lpHead, BOOL& _b_hand) {
	return m__TTips.OnGetDispInfo( _ctl_id, lpHead, _b_hand );
}

LPCTSTR CTabs_Wnd::OnToolTipTextRequest(void) {
	POINT pt_ = {0}; // https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getcursorpos
	const BOOL b_result = ::GetCursorPos(&pt_); if (FALSE == b_result) return NULL;

	::MapWindowPoints(HWND_DESKTOP, *this, &pt_, 0x1);

	const INT n_clicked = m_control.Tabs().Has(pt_);
	return (n_clicked > -1 ? m__tips.GetString() : NULL);
}

/////////////////////////////////////////////////////////////////////////////

VOID    CTabs_Wnd::ParentRenderer(IRenderer* const _renderer) { SAFE_LOCK_RENDER(); m_parent = _renderer; }
#endif