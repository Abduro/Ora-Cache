/*
	Created by Tech_dog (ebontrop@gmail.com) on 22-Aug-2020 at 12:06:47p, UTC+7, Novosibirsk, Saturday;
	This is Ebo Pack Sfx status bar control window interface implementation file.
*/
#include "sfx.status.wnd.h"
#include "sfx.status.ctrl.h"

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
#if (1)
	t_rect rc_area = {0};
	TWindow::GetClientRect(&rc_area);

	CZBuffer z_buffer(_dev_ctx, rc_area);
#if (0)
	const CComplSet& set_ = shared::ThemeTriplets().Get(TClrPredefined::e_Red_n_Navy_n_Yellow); set_;

	z_buffer.Draw(rc_area, set_.Dark()/*_r_g_b(200, 200, 200)*/);
#elif (1==0)
	z_buffer.Draw(rc_area, shared::Get_Theme().Get(TThemePart::e_form, TThemeElement::e_back));
#else
	z_buffer.Draw(rc_area, this->m_ctrl.Format().Bkgnd().Solid().ToRgb());
#endif
	// (1) status bar top border if specified; // TODO: other borders are not considered yet, but such approach is okay for now;
	const CBorder& top_ = this->m_ctrl.Borders().Top();
#if (0)
	CBorder border = top_;
	border.Color().A(0);
#endif
	if (top_.Is_valid()) {
		z_buffer.Draw(top_);
	}
#endif
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
using namespace ST_Ctrls::layout;

using namespace ex_ui;
using namespace ex_ui::controls;

#include "shared.uix.gdi.provider.h"
#include "shared.uix.gen.hsl.h"
#include "shared.uix.gen.theme.h"

using namespace ex_ui::draw;

/////////////////////////////////////////////////////////////////////////////
#define SAFE_LOCK_RENDER() SAFE_LOCK(this->m_guard);
/////////////////////////////////////////////////////////////////////////////

CStatus_Wnd:: CStatus_Wnd(CStatusBar& _ctrl, IControlEvent& _evt) :
	TCtrlWnd(m_crt, _evt, m_rnd), m_parent(NULL), m_rnd(m_crt), m_control(_ctrl), m__TTips(*this), m_images(NULL) {
	m_control.Format() = CSymantec_NA_Sta();
}

CStatus_Wnd::~CStatus_Wnd(void) {
	if (m_images) {
		::ImageList_Destroy(m_images); m_images = NULL;
	}
	if (TCtrlWnd::IsWindow())
		TCtrlWnd::SendMessage(WM_CLOSE);
}

/////////////////////////////////////////////////////////////////////////////

VOID       CStatus_Wnd::ParentRenderer(IRenderer* const _renderer) { SAFE_LOCK_RENDER(); m_parent = _renderer; }

/////////////////////////////////////////////////////////////////////////////

LRESULT CStatus_Wnd::OnErase (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	uMsg; wParam; lParam; bHandled = TRUE;
	RECT rc_area = {0};
	TCtrlWnd::GetClientRect(&rc_area);

	LRESULT l_result = TRUE;// TCtrlWnd::OnErase(uMsg, wParam, lParam, bHandled);

	const HDC hDC = reinterpret_cast<HDC>(wParam);
	CZBuffer dc_(hDC, rc_area);

	// TODO: loading an image to image list control may compete with caching images, but need a review anyway;
	TStatusFmt& sta_fmt = m_control.Format();
	if (sta_fmt.Images() && NULL == m_images) {

		const HMODULE hModule = ::ATL::_AtlBaseModule.GetModuleInstance();
		HBITMAP h_bmp_ = NULL;
		HRESULT hr_    = CGdiPlusPng_Loader::LoadResource(sta_fmt.Images(), hModule, h_bmp_);
		if (SUCCEEDED(hr_)) {
			hr_ = CGdiPlusPng_Loader::CreateImages(
				h_bmp_, m_images
			);
			::DeleteObject(h_bmp_); h_bmp_ = NULL;
		}
	}
	else if (sta_fmt.Images() == 0 && NULL != m_images) {
		::ImageList_Destroy(m_images); m_images = NULL;
	}

	// (0) status bar background at first step;
	COLORREF clr_solid = sta_fmt.Bkgnd().Solid();
	dc_.DrawSolidRect(rc_area, clr_solid);

	CColour_Ex clr_lite = sta_fmt.Borders().Top().Color();
	CColour_Ex clr_dark = sta_fmt.Borders().Top().Shadow();

	const INT n_thickness =  sta_fmt.Borders().Top().Thickness();
	INT n_top_sft = 0;
	// (1) status bar top border if specified; // TODO: other borders are not considered yet, but such approach needs a review;
	if (sta_fmt.Borders().Top().Is()) {
		// TODO: some mess appears here: layout calculates a position of 'real' border(s); but format borders have not their positions calculated;
		const TPosition& pos_ = m_control.Borders().Top().Position();
		if (clr_lite.Is()) dc_.DrawLine( pos_.Start().x, pos_.Start().y + n_thickness * 0, pos_.End().x, pos_.End().y + n_thickness * 0, clr_lite );
		if (clr_dark.Is()) dc_.DrawLine( pos_.Start().x, pos_.Start().y + n_thickness * 1, pos_.End().x, pos_.End().y + n_thickness * 1, clr_dark );

		n_top_sft +=  n_thickness * 2;
	}

	const CPanels& pans = m_control.Panels();

	DWORD dw_opts = CFontOptions::eExactSize; if (sta_fmt.Font().Options().Has(CFontOptions::eBold)) dw_opts |= CFontOptions::eBold ;

	ex_ui::draw::CFont sta_cap_fnt_(
		sta_fmt.Font().Family(), dw_opts, sta_fmt.Font().Size()
	);

	// (2) draws a text of panel(s);
	for (size_t i_ = 0; i_ < pans.Raw().size(); i_++) {
		const CPanel& pan  = pans.Raw()[i_];

		if (m_images && pan.Image_Ndx() > -1) {

			INT n_left = pan.Layout().Image().Rect().left + 0;
			INT n_top  = pan.Layout().Image().Rect().top  + n_top_sft;

			ImageList_Draw(m_images, pan.Image_Ndx(), dc_, n_left, n_top, ILD_NORMAL);
		}

		if (pan.Layout().Text().Is() == false)
			continue;
		
	//	RECT rc_cap = rc_pan; rc_cap.top += n_top_sft; rc_cap.left += sz_img.cx + sta_lay.Image().Margins().Left() + sta_lay.Image().Margins().Right();

		const DWORD h_align = static_cast<DWORD>(pan.Layout().Text().Align().Horz());
		CStringW cs_cap = pan.Text(); // otherwise, modifying string does not work and no ellipsis is applied;

		const CText_Ext& text = pan.Layout().Text();

		const RECT& rc_cap = text.Rect();

		dc_.DrawTextExt(
			cs_cap.GetBuffer()   ,
			sta_cap_fnt_         ,
			rc_cap,
			sta_fmt.Font().Fore(),
			DT_MODIFYSTRING|DT_VCENTER|h_align|DT_END_ELLIPSIS|DT_NOCLIP|DT_NOPREFIX|DT_SINGLELINE
		);
	}
	// (3) draws panel borders
	for (size_t i_ = 0; i_ < pans.Raw().size(); i_++) {
		const CPanel& pan  = pans.Raw()[i_];

		if (pan.Borders().Left().Is()) {
			CBorders_Helper::Draw(dc_, pan.Borders().Left());
		}

		if (pan.Borders().Right().Is()) {
			CBorders_Helper::Draw(dc_, pan.Borders().Right());
		}
	}

	// (4) draws glyph image if any;
	const CGlyph& glyph = m_control.Layout().Glyph();
	if (glyph.Is()) {
		const INT n_top = rc_area.top + (__H(rc_area) - glyph.Size().cy) / 2 + n_top_sft + glyph.Margins().Top();
		ImageList_Draw(m_images, glyph.Image_Ndx(), dc_, glyph.Rect().left + glyph.Margins().Left(), n_top, ILD_NORMAL);
	}
	return l_result;
}

/////////////////////////////////////////////////////////////////////////////

LPCTSTR CStatus_Wnd::OnToolTipTextRequest(void) {
	return (TCtrlWnd::m_crt.State().IsHovered() ? m__tips.GetString() : NULL);
}
#endif