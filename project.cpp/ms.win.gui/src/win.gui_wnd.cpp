/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Dec-2023 at 10:23:08.2447885, UTC+7, Novosibirsk, Tuesday;
	This is Ebo Pack draw renderer test app main window interface implementation file;
*/
#include "win.gui_wnd.h"

using namespace ebo::boo::gui;

/////////////////////////////////////////////////////////////////////////////

CWnd:: CWnd(void) : TBase() {
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

err_code CWnd::IEvtDraw_OnPaint (const w_param, const l_param) {

	using ex_ui::color::rgb::CFloat;

	using CUI_Parts = ebo::sha::theme::direct_x::CUI_Parts;
	_render().Target().OnDraw(CUI_Parts().Bkg());

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

	m_layout.Window() = TBase::m_hWnd;
	RECT rc_surface = m_layout.DrawArea();

	HWND h_surface = this->m_surface.Create(TBase::m_hWnd, &rc_surface, nullptr, WS_CHILD|WS_VISIBLE);
	if ( h_surface ) {
		_render().Init(h_surface); // this view window does not care about renderer init() result;
	}

	return   n_result;
}

err_code CWnd::IEvtLife_OnDestroy (const w_param, const l_param) {

	err_code n_result = __s_false;

	_render().Term();

	if (this->m_surface)
		this->m_surface.DestroyWindow();

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
	case eState::eRestored: {
	} break;
	}

	return   n_result;
}

err_code CWnd::IEvtFrame_OnSizing (const eEdges, LPRECT) {

	t_rect rc_surface = m_layout.DrawArea();
	if (this->m_surface) {
		this->m_surface.MoveWindow(&rc_surface);
	}
	err_code n_result = __s_false;
	return   n_result;
}

/////////////////////////////////////////////////////////////////////////////

const
CLayout& CWnd::Layout (void) const { return this->m_layout; }
CLayout& CWnd::Layout (void)       { return this->m_layout; }