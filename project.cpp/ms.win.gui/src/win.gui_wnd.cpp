/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Dec-2023 at 10:23:08.2447885, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack draw renderer test app main window interface implementation file;
*/
#include "win.gui_wnd.h"
#include "win.gui_layout.h"

using namespace ebo::boo::gui;

#ifndef __H
#define __H(rect) (rect.bottom - rect.top)
#endif

#ifndef __W
#define __W(rect) (rect.right - rect.left)
#endif

/////////////////////////////////////////////////////////////////////////////

namespace ebo { namespace boo { namespace gui { namespace _impl {
}}}}
using namespace ebo::boo::gui::_impl;
/////////////////////////////////////////////////////////////////////////////

CWnd:: CWnd(_pc_sz _p_cls_name) : TBase(_p_cls_name) {
	TBase::Handlers().Draw().Subscribe(this); TBase::Handlers().Live().Subscribe(this); TBase::Handlers().System().Subscribe(this);
	TBase::Handlers().Frame().Subscribe(this);
}
CWnd::~CWnd(void) {
	TBase::Handlers().Draw().Unsubscribe(this); TBase::Handlers().Live().Unsubscribe(this); TBase::Handlers().System().Unsubscribe(this);
	TBase::Handlers().Frame().Unsubscribe(this);
}

/////////////////////////////////////////////////////////////////////////////

err_code CWnd::IEvtDraw_OnErase   (const HDC _dev_ctx) {
	_dev_ctx;
#if (1)
	static bool  b_fst_time = false;
	if (false == b_fst_time) {
		HBRUSH brush = nullptr;

		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setclasslongptra ;
		brush = ::CreateSolidBrush(ex_ui::theme::Get_current().Form().Bkgnd().States().Normal().Color());
	#if (0)
		// if setting the background brash is made several times, returned brush handle must be destroyed?
		brush = ::CreateSolidBrush(shared::Get_Theme().Get(TThemePart::e_caption, TThemeElement::e_back));
	#elif (1==0)
		const CComplSet& set_ = shared::ThemeTriplets().Get(TClrPredefined::e_Red_n_Navy_n_Yellow);
		brush = ::CreateSolidBrush(set_.Dark());
	#endif
		::SetClassLongPtr(*this, GCLP_HBRBACKGROUND, (LONG_PTR)brush);
		b_fst_time = true;
	}
#if (0)
	t_rect rc_draw = {0};
	this->GetClientRect(&rc_draw);
	shared::Get_View().OnDraw(_dev_ctx, rc_draw);
#endif
	err_code n_result = __s_ok;  // do not hold this message, otherwise child windows will not be able to draw anything on this one;
	return   n_result;
#else
	return   __s_ok;
#endif
}

// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-beginpaint ;
// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-endpaint ;

err_code CWnd::IEvtDraw_OnPaint (const w_param, const l_param) { // both input args are useless;

	using WTL::CPaintDC;
	using ex_ui::color::rgb::CFloat;
#if defined(_test_case_lvl) && (_test_case_lvl == 3)
	// this goes first;
	using CUI_Parts = ebo::sha::theme::direct_x::CUI_Parts;
	_render().Target().OnDraw(CUI_Parts().Bkg());
#endif
#if (1)
	CPaintDC dc_(*this);
	shared::Get_View().OnDraw(dc_.m_hDC, dc_.m_ps.rcPaint); // *important*: the rectangle being sent is entire window client area!

	err_code n_result = __s_ok;  // this message is handled;
	return   n_result;
#elif (true == false)
	CPaintDC dc_(*this);
	WTL::CBrush brush;

	uint32_t clr_0  = _r_g_b  (0, 0, 255);     clr_0;
	uint32_t clr_1  = _r_g_b_a(0, 0, 255, 0);  clr_1;
	brush.CreateSolidBrush(clr_0);
	::FillRect(dc_.m_hDC, &dc_.m_ps.rcPaint, brush.m_hBrush);
#endif
	return __s_ok;
}

/////////////////////////////////////////////////////////////////////////////

err_code CWnd::IEvtLife_OnClose  (const w_param, const l_param) {

	err_code n_result = __s_false;
	return   n_result;
}

#define _not_used 1

err_code CWnd::IEvtLife_OnCreate  (const w_param, const l_param) {

	err_code n_result = __s_false;
	
#if (0)
	t_rect rc_surface = m_layout.DrawArea();
	HWND h_surface = this->m_surface.Create(TBase::m_hWnd, &rc_surface, TStringEx().Format(_T("%s::%s"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__), WS_CHILD|WS_VISIBLE);
	if ( h_surface ) {
		_render().Init(h_surface); // this view window does not care about renderer init() result;
	}
#endif
#if defined(_test_case_lvl) && (_test_case_lvl >= 1)
	::shared::Get_View().Parent() = *this;
#endif
#if defined(_test_case_lvl) && (_test_case_lvl >= 2) && !defined(_not_used)
	::shared::Get_View().Tabbed().Create(*this, 0xB);
#endif
#if defined(_test_case_lvl) && (_test_case_lvl >= 3)
	t_rect rc_surface = m_layout.DrawArea();
	n_result = shared::Get_View().Surface().Create(*this, rc_surface);
#endif

	::shared::Get_View().OnCreate();

	t_rect rc_client = {0};
	this->GetClientRect(&rc_client);

	::shared::Get_Layout().Window() = *this;     // ATL::CWindow operator is applied here;
	::shared::Get_Layout().Update(rc_client);

	TBase::m_error << __METHOD__ << __s_ok;

	return n_result;
}

err_code CWnd::IEvtLife_OnDestroy (const w_param, const l_param) {

	err_code n_result = __s_false;

	_render().Term();
#if defined(_test_case_lvl) && (_test_case_lvl >= 3)
	if (shared::Get_View().Surface())
		shared::Get_View().Surface().DestroyWindow();
#endif

	::shared::Get_View().OnDestroy();

	return n_result;
}

/////////////////////////////////////////////////////////////////////////////

err_code CWnd::IEvtSys_OnSysCmd (const w_param _w_param, const l_param) {
	
	err_code n_result = __s_false;
	switch (_w_param)
	{
	case IMsgSysEventSink::eSysCmd::eClose: {
			::PostQuitMessage(0);
		} break;
	}
	return  n_result;
}

/////////////////////////////////////////////////////////////////////////////

using eState = IFormEvtSink::eState;
using eEdges = IFormEvtSink::eEdges;

err_code CWnd::IEvtFrame_OnSize (const eState _e_state, const SIZE) {

	err_code n_result = __s_false;

	switch (_e_state) {
	case eState::eRestored :
	case eState::eMaximized: {
		bool b_break = false;
		if (!b_break)
			 b_break = true ;

		t_rect rect = {0};
		this->GetClientRect(&rect);
		// ToDo: does not work properly yet, needs to be checked;
		::shared::Get_Layout().Update(rect);
		::shared::Get_View().OnDraw(nullptr, rect); // calling the draw function for specific client area rectangle must be reviewed;

	} break;
	}

	return   n_result;
}

err_code CWnd::IEvtFrame_OnSizing (const eEdges _edges, LPRECT _p_rect) {
	_edges; _p_rect;     // this rectangle is in screen coordinates of entire window, including non-client area;
#if (1)
	t_rect rc_client = {0};
	if (_p_rect && false) { // it doesn't work as expected because the input rectangle contains non-client area dimensions;
		rc_client = {0, 0, _p_rect->right - _p_rect->left, _p_rect->bottom - _p_rect->top};
		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-mapwindowpoints ;
		 if (0 == ::MapWindowPoints(HWND_DESKTOP, *this, (t_point*)&rc_client, sizeof(t_rect)/sizeof(t_point)))
			TBase::m_error.Last();
	}
	else
		if (0 == this->GetClientRect(&rc_client)) // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getclientrect ;
			(TBase::m_error << __METHOD__).Last();

	if (TBase::m_error == false)
		TBase::m_error << ::shared::Get_Layout().Update(rc_client);
	if (TBase::m_error == false)
		::shared::Get_View().OnDraw(nullptr, rc_client);
#else
	t_rect rc_surface = m_layout.DrawArea();
	// *important* : MoveWindow() does not send WM_MOVE nor WM_MOVING messages to target window;
	if (::shared::Get_View().Surface()) {
		::shared::Get_View().Surface().MoveWindow(&rc_surface, false);
		::shared::Get_View().Surface().IEvtFrame_OnSizing(_edges, &rc_surface);
	}
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-mapwindowpoints ;
	// ::MapWindowPoints(HWND_DESKTOP, *this, (LPPOINT)_p_rect, 2);
	t_rect rc_client = {0};
	TBase::GetClientRect(&rc_client);

	::shared::Get_View().Status().Layout().Update(rc_client);

#endif
#if (1)
	// this was made for testing of dynamic update of the status pane text; (passed)
	shared::Get_View().Status().SetText(TString().Format(_T("Ready [%dx%d]"), __W(rc_client), __H(rc_client)));
#endif
	err_code n_result = __s_false;
	return   n_result;
}