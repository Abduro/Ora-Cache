/*
	Created by Tech_dog (ebontrop@gmail.com) on 04=May-2025 at 20:00:31.249, UTC+4, Batumi, Sunday;
	This is Ebo Pack DirectX draw render surface window interface implementation file;
*/
#include "direct_x.surface.h"

using namespace ebo::boo::gui::render;

/////////////////////////////////////////////////////////////////////////////

CSurface:: CSurface(void) : TBase() {
	TBase::Handlers().Draw().Subscribe(this);
	TBase::Handlers().Frame().Subscribe(this);
}
CSurface::~CSurface(void) {
	TBase::Handlers().Draw().Unsubscribe(this);
	TBase::Handlers().Frame().Unsubscribe(this);
}

/////////////////////////////////////////////////////////////////////////////

err_code CSurface::IEvtDraw_OnPaint (const w_param, const l_param) {

	using ex_ui::color::rgb::CFloat;

	using CUI_Parts = ebo::sha::theme::direct_x::CUI_Parts;
	_render().Target().OnDraw(CUI_Parts().Bkg());

	err_code n_result = __s_false;  // this message is handled;
	return   n_result;
}

/////////////////////////////////////////////////////////////////////////////

err_code CSurface::IEvtFrame_OnMove   (const t_point& _top_left_client_area) {
	_top_left_client_area;
	err_code n_result = __s_false;
	return   n_result;

}
err_code CSurface::IEvtFrame_OnMoving (const t_rect* _p_wnd_coords){
	_p_wnd_coords;
	err_code n_result = __s_false;
	return   n_result;
}

using eState = IFormEvtSink::eState;
using eEdges = IFormEvtSink::eEdges;

err_code CSurface::IEvtFrame_OnSize   (const eState _e_state, const SIZE) {

	err_code n_result = __s_false;

	switch (_e_state) {
	case eState::eRestored: {
	} break;
	}

	return   n_result;
}

err_code CSurface::IEvtFrame_OnSizing (const eEdges, LPRECT _p_rect_applied) {

	t_rect rc_applied = *_p_rect_applied;  // *attention*: this rectangle in parent window client area coordinates;
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-offsetrect ;
	::OffsetRect(&rc_applied, -rc_applied.left, -rc_applied.top);

	_render().Target().OnSize(rc_applied); // error code is not useful yet;

	err_code n_result = __s_false;
	return   n_result;
}