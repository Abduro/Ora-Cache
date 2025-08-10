/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Jul-2020 at 9:02:30p, UTC+7, Novosibirsk, Sunday;
	This is Ebo Pack Sfx tab control window interface implementation file.
*/
#include "sfx.tabs.wnd.h"
#include "sfx.tabs.ctrl.h"

using namespace ex_ui::controls::sfx::tabbed;
using namespace ex_ui::message::handlers::mouse::buttons;

/////////////////////////////////////////////////////////////////////////////

CWnd:: CWnd(CControl& _ctrl) : TWindow(), m_ctrl(_ctrl) {
	TWindow::Handlers().Draw().Subscribe (this); TWindow::Handlers().Live().Subscribe(this);
	TWindow::Handlers().Frame().Subscribe(this);
	TWindow::Handlers().Mouse().Buttons().Subscribe(CPlace::e_Left, CAction::e_pressed, this);
}
CWnd::~CWnd(void) {
	TWindow::Handlers().Draw().Unsubscribe (this); TWindow::Handlers().Live().Unsubscribe(this);
	TWindow::Handlers().Frame().Unsubscribe(this);
	TWindow::Handlers().Mouse().Buttons().Unsubscribe(CPlace::e_Left, CAction::e_pressed, this);
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
#if (0)
	t_rect rc_area = {0};
	TWindow::GetClientRect(&rc_area);  // perhaps the layout knows about available area better than the window itself;
#else
	t_rect rc_area = this->m_ctrl.Layout().Rect();
#endif
	ex_ui::draw::memory::CMode(_dev_ctx).Set(ex_ui::draw::memory::CMode::e_advanced);
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
	const rgb_color clr_active = this->m_ctrl.Format().Border().Color().Selected();
	const rgb_color clr_normal = this->m_ctrl.Format().Border().Color().Normal();

	for (TRawBorders::const_iterator iter_ = act_tab.begin(); iter_ != act_tab.end(); ++iter_) {
		const CBorder& border = iter_->second;
		z_buffer.Draw( border, clr_active);
	}

	// (4) draws captions of the tabs; the color of the text depends on activity of the tab and the same as tab border color;
	if (this->m_ctrl.Layout().Tabs().Sides().IsHorz()) {
		// ToDo: using the same names with classes, but of other namespace must be solved, otherwise the compiler generates the warning;
		using TFlags_Horz = ex_ui::draw::text::format::CAlign_Horz::e_value;
		using TFlags_Vert = ex_ui::draw::text::format::CAlign_Vert::e_value;
		using TAlt_Flags  = ex_ui::draw::text::format::CAlterer::e_value;
		using TCut_Flags  = ex_ui::draw::text::format::CCutter::e_value;
		using TOpt_Flags  = ex_ui::draw::text::format::COptimizer::e_value;

		ex_ui::draw::text::CDrawText text;

		text.Format().Set(
			TFlags_Horz::e_center | TFlags_Vert::e_middle | TCut_Flags::e_end | TOpt_Flags::e_no_clip | TOpt_Flags::e_single | TAlt_Flags::e_no_prefix
		);

		const TTabArray& tabs = this->m_ctrl.Tabs().Raw();

		for (int16_t i_ = 0; i_ < this->m_ctrl.Tabs().Count(); i_++) {
			const CTab& tab_ = tabs.at(i_);

			text << tab_.Caption() << tab_.Strip() << (i_ == this->m_ctrl.Tabs().Active() ? clr_active : clr_normal);

			z_buffer.Draw(text, this->m_font.Handle());
		}
	}
	if (this->m_ctrl.Layout().Tabs().Sides().IsVert()) {
#if (0)
		const HFONT h_prev = z_buffer.SelectFont(this->m_font_vert.Handle());
		CAlign align; align << z_buffer; align.Set(TVert_Flags::e_center); // no check of error yet; does not work: the text still is trimmed;
#else
		ex_ui::draw::text::CTextOut text;
		text.Align().Horz().Set(THorz_Flags::e_center);
		text.Align().Vert().Set(TVert_Flags::e_center);
		text.Align() >> z_buffer;
		text << z_buffer;  // it is required for correct calculation text position;
#endif
		const TTabArray& tabs = this->m_ctrl.Tabs().Raw();
		for (int16_t i_ = 0; i_ < this->m_ctrl.Tabs().Count(); i_++) {
			const CTab& tab_ = tabs.at(i_);
#if (0)
			z_buffer.Draw(tab_.Caption(), this->m_font_vert.Handle(), tab_.Rect(), i_ == this->m_ctrl.Tabs().Active() ? act_clr : nrm_clr, dw_flags);
#else
			((ex_ui::draw::text::CText_Base&)text) << tab_.Caption()  << (i_ == this->m_ctrl.Tabs().Active() ? clr_active : clr_normal);
			text << tab_.Strip();
			z_buffer.Draw(text, this->m_font_vert.Handle(), 0);
#endif
		}
#if (0)
		z_buffer.SelectFont(h_prev);
#endif
	}

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

#if (1)
	TWindow::m_error << m_font.Create(
		this->m_ctrl.Format().Font().Family(), this->m_ctrl.Format().Font().Options(), this->m_ctrl.Format().Font().Size()
	);
	// ToDo: it must be made in format class of this tabbed control;
	//       also, taking into account a user may change the tab position side, it should be dynamically updated;
	if (this->m_ctrl.Layout().Tabs().LocatedOn() == TSide::e_left)
		m_font_vert.Angle(90);
	else if (this->m_ctrl.Layout().Tabs().LocatedOn() == TSide::e_right)
		m_font_vert.Angle(270);

	TWindow::m_error << m_font_vert.Create(
		this->m_ctrl.Format().Font().Family(), this->m_ctrl.Format().Font().Options(), this->m_ctrl.Format().Font().Size()
	);

#endif

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

/////////////////////////////////////////////////////////////////////////////

err_code CWnd::IEvtButton_OnReceive(const CEvent& _event) {
	_event;
	err_code n_result = __s_false; // this message event is not handled yet;

	if (CAction::e_pressed != _event.Action().Type() || CPlace::e_Left != _event.Button().Place().Where())
		return n_result;

	const t_point& pt_ = _event.Point();
	const int16_t ndx_ = this->m_ctrl.Tabs().Has(pt_);
	if (-1 < ndx_) {
		n_result = this->m_ctrl.Tabs().Active(ndx_);
		if (__succeeded(n_result)) n_result = this->m_ctrl.Layout().Update();
		if (__succeeded(n_result)) n_result = this->m_ctrl.Refresh();
	}

	return n_result; // in case of success __s_ok is expected, otherwise error code, in any case this event message is handled;
}

#if (0)

#include "shared.uix.gdi.provider.h"
#include "shared.uix.gen.hsl.h"
#include "shared.uix.gen.theme.h"

/////////////////////////////////////////////////////////////////////////////
#define SAFE_LOCK_RENDER() SAFE_LOCK(this->m_guard);
/////////////////////////////////////////////////////////////////////////////

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
#endif