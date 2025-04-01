/*
	Created by Tech_dog (ebontrop@gmail.com) on 26-Dec-2023 at 10:23:08.2447885, UTC+7, Novosibirsk, Tuesday;
	This is window popup test app main window interface implementation file;
*/
#include "win.gui_wnd.h"

using namespace ebo::boo::gui;
using TWindow = ebo::boo::gui::CWindow;
/////////////////////////////////////////////////////////////////////////////

TWindow:: CWindow(void) : TBase() {
	TBase::Handlers().Draw().Subscribe(this);
	TBase::Handlers().Live().Subscribe(this);
	TBase::Handlers().System().Subscribe(this);
	TBase::Handlers().Frame().Subscribe(this);
}
TWindow::~CWindow(void) {
	TBase::Handlers().Draw().Unsubscribe(this);
	TBase::Handlers().Live().Unsubscribe(this);
	TBase::Handlers().System().Unsubscribe(this);
	TBase::Handlers().Frame().Unsubscribe(this);
}

/////////////////////////////////////////////////////////////////////////////

err_code  TWindow::IEvtDraw_OnErase   (const HDC _dev_ctx) {
	_dev_ctx;
	static bool  b_fst_time = false;
	if (false == b_fst_time) {
		HBRUSH brush = ::CreateSolidBrush(RGB(61, 61, 61));
		::SetClassLongPtr(*this, GCLP_HBRBACKGROUND, (LONG_PTR)brush);
		b_fst_time = true;
	}

	err_code n_result = __s_false;  // this message is handled;
	return   n_result;
}

/////////////////////////////////////////////////////////////////////////////

err_code  TWindow::IEvtLife_OnClose  (const w_param, const l_param) {

	err_code n_result = __s_false;
	return   n_result;
}

err_code TWindow::IEvtLife_OnCreate  (const w_param, const l_param) {

	err_code n_result = __s_false;
	return   n_result;
}

err_code TWindow::IEvtLife_OnDestroy (const w_param, const l_param) {

	err_code n_result = __s_false;
	return   n_result;
}

/////////////////////////////////////////////////////////////////////////////

err_code TWindow::IEvtSys_OnSysCmd (const w_param _w_param, const l_param) {
	
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

err_code TWindow::IEvtFrame_OnSize   (const eState _e_state, const SIZE) {

	err_code n_result = __s_false;

	switch (_e_state) {
	case eState::eRestored: {
	} break;
	}

	return   n_result;
}

err_code TWindow::IEvtFrame_OnSizing (const eEdges, LPRECT) {

	err_code n_result = __s_false;
	return   n_result;
}