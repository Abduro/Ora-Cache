/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Dec-2023 at 10:23:08.2447885, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack draw renderer test app main window interface implementation file;
*/
#include "win.gui_wnd.h"

using namespace ebo::boo::gui;

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
	static bool  b_fst_time = false;
	if (false == b_fst_time) {
		HBRUSH brush = ::CreateSolidBrush(RGB(61, 61, 61)); // ToDo: it requires getting a color from the currently set theme;
		::SetClassLongPtr(*this, GCLP_HBRBACKGROUND, (LONG_PTR)brush);
		b_fst_time = true;
	}

	err_code n_result = __s_false;  // this message is handled;
	return   n_result;
}

// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-beginpaint ;
// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-endpaint ;

err_code CWnd::IEvtDraw_OnPaint (const w_param, const l_param) { // both input args are useless;

	using WTL::CPaintDC;
	using ex_ui::color::rgb::CFloat;
	// this goes first;
	using CUI_Parts = ebo::sha::theme::direct_x::CUI_Parts;
	_render().Target().OnDraw(CUI_Parts().Bkg());

	CPaintDC dc_(*this);
	shared::Get_View().Draw(dc_.m_hDC, dc_.m_ps.rcPaint); // *important*: the rectangle being sent is entire window client area!

	err_code n_result = __s_false;  // this message is handled;
	return   n_result;
}

/////////////////////////////////////////////////////////////////////////////

err_code CWnd::IEvtLife_OnClose  (const w_param, const l_param) {

	err_code n_result = __s_false;
	return   n_result;
}

err_code CWnd::IEvtLife_OnCreate  (const w_param, const l_param) {

	err_code n_result = __s_false;

	m_layout.Window() = *this;     // ATL::CWindow operator is applied here;
	t_rect rc_surface = m_layout.DrawArea();
#if (0)
	HWND h_surface = this->m_surface.Create(TBase::m_hWnd, &rc_surface, TStringEx().Format(_T("%s::%s"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__), WS_CHILD|WS_VISIBLE);
	if ( h_surface ) {
		_render().Init(h_surface); // this view window does not care about renderer init() result;
	}
#else
	n_result = shared::Get_View().Surface().Create(*this, rc_surface);
#endif
	::shared::Get_View().Parent() = *this;
	::shared::Get_View().Status().Create(*this, 0xA); // no error handling is made yet;

	TBase::m_error << __METHOD__ << __s_ok;

	return n_result;
}

err_code CWnd::IEvtLife_OnDestroy (const w_param, const l_param) {

	err_code n_result = __s_false;

	_render().Term();

	if (shared::Get_View().Surface())
		shared::Get_View().Surface().DestroyWindow();

	::shared::Get_View().Status().Destroy(); // no error handling is made yet;

	return   n_result;
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

err_code CWnd::IEvtFrame_OnSize   (const eState _e_state, const SIZE) {

	err_code n_result = __s_false;

	switch (_e_state) {
	case eState::eRestored: {} break;
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
		TBase::m_error << this->Layout().Update(rc_client);
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
	err_code n_result = __s_false;
	return   n_result;
}

/////////////////////////////////////////////////////////////////////////////

const
CLayout& CWnd::Layout (void) const { return this->m_layout; }
CLayout& CWnd::Layout (void)       { return this->m_layout; }