/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Dec-2023 at 10:23:08.2447885, UTC+7, Novosibirsk, Tuesday;
	This is window popup test app main window interface implementation file;
*/
#include "win.gui_wnd.h"
#include "direct_x.wrap.h"      // ToDo:: if it is placed to header 'win.gui_wnd.h', the compilation is failed;
#include "ebo.sha.gui.theme.h"
#include "win.gui_layout.h"

using namespace ebo::boo::gui;

CLayout m_layout;
/////////////////////////////////////////////////////////////////////////////

CView:: CView(void) : TBase() {
	TBase::Handlers().Draw().Subscribe(this);
	TBase::Handlers().Live().Subscribe(this);
	TBase::Handlers().System().Subscribe(this);
	TBase::Handlers().Frame().Subscribe(this);
}
CView::~CView(void) {
	TBase::Handlers().Draw().Unsubscribe(this);
	TBase::Handlers().Live().Unsubscribe(this);
	TBase::Handlers().System().Unsubscribe(this);
	TBase::Handlers().Frame().Unsubscribe(this);
}

/////////////////////////////////////////////////////////////////////////////

err_code  CView::IEvtDraw_OnErase   (const HDC _dev_ctx) {
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

err_code CView::IEvtDraw_OnPaint (const w_param, const l_param) {

	using ex_ui::color::rgb::CClr_Float;

	using CUI_Parts = ebo::sha::theme::direct_x::CUI_Parts;
	_render().Target().OnDraw(CUI_Parts().Bkg());

	err_code n_result = __s_false;  // this message is handled;
	return   n_result;
}

/////////////////////////////////////////////////////////////////////////////

err_code  CView::IEvtLife_OnClose  (const w_param, const l_param) {

	err_code n_result = __s_false;
	return   n_result;
}

err_code CView::IEvtLife_OnCreate  (const w_param, const l_param) {

	err_code n_result = __s_false;

	m_layout.Window() = TBase::m_hWnd;

	_render().Init(this->m_hWnd); // this view window does not care about renderer init() result;

	return   n_result;
}

err_code CView::IEvtLife_OnDestroy (const w_param, const l_param) {

	err_code n_result = __s_false;

	_render().Term();

	return   n_result;
}

/////////////////////////////////////////////////////////////////////////////

err_code CView::IEvtSys_OnSysCmd (const w_param _w_param, const l_param) {
	
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

err_code CView::IEvtFrame_OnSize   (const eState _e_state, const SIZE) {

	err_code n_result = __s_false;

	switch (_e_state) {
	case eState::eRestored: {
	} break;
	}

	return   n_result;
}

err_code CView::IEvtFrame_OnSizing (const eEdges, LPRECT) {

	_render().Target().OnSize(m_layout.DrawArea());

	err_code n_result = __s_false;
	return   n_result;
}