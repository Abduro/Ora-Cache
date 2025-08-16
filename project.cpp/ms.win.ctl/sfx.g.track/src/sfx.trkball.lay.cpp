/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Aug-2025 at 23:51:59.009,(UTC+4), Batumi, Monday;
	This is Ebo Pack trackball user control layout interface implementation file;
*/
#include "sfx.trkball.lay.h"
#include "sfx.trkball.ctrl.h"

using namespace ex_ui::controls::sfx::track;
using namespace ex_ui::controls::sfx::track::layout;

#ifndef __H
#define __H(rc) (rc.bottom - rc.top)
#endif

#ifndef __W
#define __W(rc) (rc.right - rc.left)
#endif

namespace ex_ui { namespace controls { namespace sfx { namespace track { namespace _impl {

	const t_size& Get_req_size (void) {
		static t_size req_size {64, 64};
		return req_size;
	}

}}}}}
using namespace ex_ui::controls::sfx::track::_impl;

CLayout:: CLayout (CControl& _ctrl) : m_ctrl(_ctrl), m_padding(5,5,-5,-5), m_pref_sz{64,64}, m_rect{0} { m_error >> __CLASS__ << __METHOD__ << __s_ok; }
CLayout::~CLayout (void) {}

TError&   CLayout::Error   (void) const { return this->m_error ; }

const
CPadding& CLayout::Padding (void) const { return this->m_padding; }
CPadding& CLayout::Padding (void)       { return this->m_padding; }

const
t_size&   CLayout::Pref_Sz (void) const { return this->m_pref_sz; }
err_code  CLayout::Pref_Sz (const t_size& _pref_sz) {
	_pref_sz;
	m_error << __METHOD__ << __s_ok;

	if (_pref_sz.cx < Get_req_size().cx || _pref_sz.cy < Get_req_size().cy)
		return this->m_error << __e_inv_arg = TString().Format(_T("The min.size is req: w=%u;h=%u"), Get_req_size().cx, Get_req_size().cy);
	if (_pref_sz.cx != _pref_sz.cy)
		return this->m_error << __e_inv_arg = _T("The size must be a square");

	this->m_pref_sz = _pref_sz;

	return this->Error();
}

/*
	this::Update() expects that the control window is already created and its (window) size and position are set;
	that means this::Update(rect) is already called before and sets cached rectangle;
*/
err_code  CLayout::Update (void) {

	err_code n_result = __s_ok;

	if (::IsRectEmpty(&this->m_rect)) { // the Update(rect) is not called yet, just checks the window validity and gets client area rect;
		CWindow wnd_ = this->m_ctrl.Window();

		if (false == wnd_.IsWindow()) {
			return this->m_error << __METHOD__ << (err_code) TErrCodes::eExecute::eState;
		}
		t_rect rc_area = {0};

		if (false == wnd_.GetClientRect(&rc_area)) {
			return (this->m_error << __METHOD__).Last();
		}
		else
			this->m_rect = rc_area;
	}

	this->m_ctrl.Borders() << this->m_rect;

	return n_result;
}

/* the input rectangle is in parent window client area coords; it is expected the call comes from the test app;
    but actually it does not matter, ::OffsetRect takes the care of that;
*/
err_code  CLayout::Update (const t_rect& _rc_area) {
	_rc_area;
	if (::IsRectEmpty(&_rc_area))
		return this->m_error << __METHOD__ << __e_rect;

	CWindow wnd_ = this->m_ctrl.Window();
	if (false == wnd_.IsWindow())
		return this->m_error << __METHOD__ << (err_code) TErrCodes::eExecute::eState;

#if defined(_DEBUG)
	__trace_info(
		_T("[%s::%s] >> {_rc_area:%d;%d;%d;%d}\n"), (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, _rc_area.left, _rc_area.top, _rc_area.right, _rc_area.bottom
	);
#endif

	if (false == wnd_.SetWindowPos(0, &_rc_area, SWP_NOACTIVATE|SWP_NOZORDER))
		return (this->m_error << __METHOD__).Last();

	this->m_rect = _rc_area; // the cached rectangle is the client area of this control window, so it requires making the offset;

	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-offsetrect ;
	::OffsetRect(&this->m_rect, -this->m_rect.left, -this->m_rect.top);

	return this->Update(); // it uses the cached rectangle; if the cache is not set, GetClientRect() is called;
}