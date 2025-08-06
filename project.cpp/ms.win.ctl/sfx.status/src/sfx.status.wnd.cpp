/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Aug-2020 at 12:06:47p, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack Sfx status bar control window interface implementation file.
*/
#include "sfx.status.wnd.h"
#include "sfx.status.ctrl.h"

#include "uix.theme.h"
#include "uix.theme.named.h"

using namespace ex_ui::controls::sfx::status;

/////////////////////////////////////////////////////////////////////////////

CWnd:: CWnd(CControl& _ctrl) : TWindow(), m_ctrl(_ctrl) {
	TWindow::Handlers().Draw().Subscribe (this); TWindow::Handlers().Live().Subscribe(this);
	TWindow::Handlers().Frame().Subscribe(this);
}
CWnd::~CWnd(void) {
	TWindow::Handlers().Draw().Unsubscribe (this); TWindow::Handlers().Live().Unsubscribe(this);
	TWindow::Handlers().Frame().Unsubscribe(this);
}

/////////////////////////////////////////////////////////////////////////////
// https://stackoverflow.com/questions/5213952/erase-window-background-win32api ;
err_code CWnd::IEvtDraw_OnErase (const HDC _dev_ctx) {
	_dev_ctx;
	/*
		this is the really issue: the main window of the test app and this control window have the same window class;
		that means any manipulating with class pointer as it is made below, will affect all windows of such class;
	*/
#if (0)
	static bool  b_fst_time = false;
	if (true == b_fst_time) { // intentionally is set to 'true'; the main window of the app should care about the background brush;
		HBRUSH brush = ::CreateSolidBrush(shared::Get_Theme().Get(TThemePart::e_form, TThemeElement::e_back));
		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setclasslongptra ;
		::SetClassLongPtr(*this, GCLP_HBRBACKGROUND, (LONG_PTR)brush);
		b_fst_time = true;
	}
#endif

	t_rect rc_area = {0};
	TWindow::GetClientRect(&rc_area);
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getupdaterect ;
	t_rect rc_update = {0};
	if (false == !!TWindow::GetUpdateRect(&rc_update)) {
		bool b_break = false;
		b_break = !b_break;
	}

	HDC h_local = nullptr;
	if (_dev_ctx == nullptr)
		h_local = TWindow::GetDC();

	CZBuffer z_buffer(_dev_ctx == nullptr ? h_local : _dev_ctx, rc_area);
#if (0)
	const CComplSet& set_ = shared::ThemeTriplets().Get(TClrPredefined::e_Red_n_Navy_n_Yellow); set_;
	z_buffer.Draw(rc_area, set_.Dark()/*_r_g_b(200, 200, 200)*/);
#elif (1==0)
	z_buffer.Draw(rc_area, shared::Get_Theme().Get(TThemePart::e_form, TThemeElement::e_back));
#else
	z_buffer.Draw(rc_area, this->m_ctrl.Format().Bkgnd().Solid().ToRgb());
#endif
	// (1) draws the glyph;
	CGlyph& glyph = this->m_ctrl.Panes().Glyph();
	if (glyph.Format().Image().Is_set()) {
		this->m_ctrl.Images()().Draw(
				glyph.Format().Image().Index(), z_buffer, glyph.Layout().Image().Anchor().x, glyph.Layout().Image().Anchor().y
			);
	}

	// (2) status bar top border if specified; // TODO: other borders are not considered yet, but such approach is okay for now;

	if (ex_ui::theme::Get_current().Palette().Is_dark()) {

		const rgb_color clr_shadow = ex_ui::theme::Get_current().Form().Border().States().Disabled().Color();

		CBorder shadow = this->m_ctrl.Borders().Top(); shadow.Color() << clr_shadow;
		CBorder top_   = this->m_ctrl.Borders().Top(); top_.Begin() >> top_.Begin().Y() + 1; top_.End() >> top_.End().Y() + 1;

		if (shadow.Is_valid()) { z_buffer.Draw(shadow); }
		if (top_.Is_valid())   { z_buffer.Draw(top_); }
	}
	else {
		const CBorder& top_ = this->m_ctrl.Borders().Top();
		if (top_.Is_valid())   { z_buffer.Draw(top_); }
	}

	// (3) draws panes;
	using TFlags_Horz = ex_ui::draw::text::format::CAlign_Horz::e_value;
	using TFlags_Vert = ex_ui::draw::text::format::CAlign_Vert::e_value;
	using TAlt_Flags  = ex_ui::draw::text::format::CAlterer::e_value;
	using TCut_Flags  = ex_ui::draw::text::format::CCutter::e_value;
	using TOpt_Flags  = ex_ui::draw::text::format::COptimizer::e_value;

	ex_ui::draw::text::CDrawText text;

	text.Format().Set(
		TFlags_Horz::e_left | TFlags_Vert::e_middle | TCut_Flags::e_end | TOpt_Flags::e_no_clip | TOpt_Flags::e_single | TAlt_Flags::e_no_prefix
	);

	const rgb_color clr_fnt_norm = this->m_ctrl.Format().Font().Fore();
	const rgb_color clr_brd_norm = this->m_ctrl.Format().Borders().Normal();

	for (uint16_t i_ = 0; i_ < this->m_ctrl.Panes().Count(); i_++) {
		const CPane& pane = this->m_ctrl.Panes().Pane(i_);
		if (pane.Format().Image().Is_set()) {
			this->m_ctrl.Images()().Draw(
				pane.Format().Image().Index(), z_buffer, pane.Layout().Image().Anchor()
			);
		}
		// each border validity control may be made by draw renderer, but it can be made here too;
		const CBorders& borders = pane.Borders();

		const CBorder& brd_left = borders.Left();
		const CBorder& brd_right = borders.Right();

		if (brd_left.Is_valid() && !!brd_left.Thickness()) z_buffer.Draw(brd_left, clr_brd_norm);
		if (brd_right.Is_valid() && !!brd_right.Thickness()) z_buffer.Draw(brd_right, clr_brd_norm);

		if (pane.Text() && 0 != ::_tcslen(pane.Text())) {

			t_rect rect = pane.Layout().Rect();

			rect.left += pane.Layout().Padding().Left();

			pane.Layout().Padding().ApplyTo(rect); // this must be done not here, but there :-D ;

			text << pane.Text() << rect << clr_fnt_norm;

			z_buffer.Draw(text, this->m_font.Handle());
		}
	}

	if (nullptr != h_local) {
		TWindow::ReleaseDC(h_local); h_local = nullptr;
	}

	err_code n_result = __s_false;  // this message is handled;
	return   n_result;
}

err_code CWnd::IEvtDraw_OnPaint (const w_param, const l_param) { // both input args are useless;

	using WTL::CPaintDC;
	
	CPaintDC dc_(*this);

#if (0)

	CZBuffer z_buffer(dc_.m_hDC, dc_.m_ps.rcPaint);

	z_buffer.Draw(dc_.m_ps.rcPaint, TRgbQuad(shared::Get_Theme().Get(TThemePart::e_form, TThemeElement::e_back)));

	// (1) status bar top border if specified; // TODO: other borders are not considered yet, but such approach is okay for now;
	const CBorder& top_ = this->m_ctrl.Borders().Top();

	if (top_.Is_valid()) {
		z_buffer.Draw(top_);
	}
#elif (0==1)

	dc_.SetBkMode(TRANSPARENT);

	CZBuffer z_buffer(dc_.m_hDC, dc_.m_ps.rcPaint);

	const CComplSet& set_ = shared::ThemeTriplets().Get(TClrPredefined::e_Red_n_Navy_n_Yellow);
	z_buffer.Draw(dc_.m_ps.rcPaint, set_.Dark());

	// (1) status bar top border if specified; // TODO: other borders are not considered yet, but such approach is okay for now;
	const CBorder& top_ = this->m_ctrl.Borders().Top();
	if (top_.Is_valid()) {
		z_buffer.Draw(top_);
	}
	
#endif
	err_code n_result = __s_ok;  // this message is handled;
	return   n_result;
}

/////////////////////////////////////////////////////////////////////////////

err_code CWnd::IEvtLife_OnCreate  (const w_param, const l_param) {

	TWindow::m_error << m_font.Create(
		this->m_ctrl.Format().Font().Family(), this->m_ctrl.Format().Font().Options(), this->m_ctrl.Format().Font().Size()
	);

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