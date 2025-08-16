/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Aug-2025 at 22:08:10.750, UTC+4, Batumi, Monday;
	This is Ebo Pack thackball control window interface implementatio file;
*/
#include "sfx.trkball.wnd.h"
#include "sfx.trkball.ctrl.h"

using namespace ex_ui::controls::sfx::track;
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
	err_code n_result = __s_false; // this message is handled; nothing is done;
	return   n_result;
}

err_code CWnd::IEvtDraw_OnPaint (const w_param, const l_param) { // both input args are useless;

	using WTL::CPaintDC;

	CPaintDC dc_(*this);

	err_code n_result = __s_ok;  // this message is handled;
	t_rect& rc_paint  = dc_.m_ps.rcPaint;

	ex_ui::draw::memory::CMode(dc_).Set(ex_ui::draw::memory::CMode::e_advanced);
	CZBuffer z_buffer(dc_, rc_paint);
	// (1) fills the background by the theme color;
	z_buffer.Draw(rc_paint, this->m_ctrl.Format().Bkgnd().Solid().ToRgb());

	// (2) draws the control borders;
	const rgb_color clr_border = this->m_ctrl.Format().Border().Color().Normal();

	using ex_ui::controls::borders::TRawBorders;

	for (TRawBorders::const_iterator iter_ = this->m_ctrl.Borders().Raw().begin(); iter_ != this->m_ctrl.Borders().Raw().end(); ++iter_) {
		const CBorder& border = iter_->second;
		z_buffer.Draw( border, clr_border);
	}

	return n_result;
}

err_code CWnd::IEvtLife_OnCreate  (const w_param, const l_param) {
	err_code n_result = __s_false;
	return   n_result;
}

err_code CWnd::IEvtLife_OnDestroy (const w_param, const l_param) {

	err_code n_result = __s_false;
	return   n_result;
}

using eState = IFormEvtSink::eState;
using eEdges = IFormEvtSink::eEdges;

err_code CWnd::IEvtFrame_OnSize   (const eState _e_state, const t_size _size) {
	_e_state; _size;
#if (0) // this control layout must take care about this;
	t_rect rc_area = {0, 0, _size.cx, _size.cy};

	this->m_ctrl.Borders() << rc_area;
#endif
	err_code n_result = __s_false;
	return   n_result;
}

err_code CWnd::IEvtFrame_OnSizing (const eEdges _edges, t_rect* _p_rect) {
	_edges; _p_rect;
#if (0) // this control layout must take care about this; 
	if (_p_rect)
		this->m_ctrl.Borders() << *_p_rect;
	else {
		bool b_break_point = false;
		b_break_point = !b_break_point;
	}
#endif
	err_code n_result = __s_false;
	return   n_result;
}

err_code CWnd::IEvtButton_OnReceive(const CEvent& _event) {
	_event;
	err_code n_result = __s_false; // this message event is not handled yet;

	return n_result; // in case of success __s_ok is expected, otherwise error code, in any case this event message is handled;
}