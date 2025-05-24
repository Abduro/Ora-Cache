/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Dec-2021 at 3:13:24.2838827 pm, UTC+7, Novosibirsk, Saturday;
	This is base window layout interface implementation file;
*/
#include "wnd.layout.h"

using namespace ex_ui::popup::layout;

#ifndef __H
#define __H(rc) (rc.bottom - rc.top)
#define __W(rc) (rc.right - rc.left)
#endif

/////////////////////////////////////////////////////////////////////////////

CPlacement:: CPlacement (void) : m_rect{0} {}
CPlacement:: CPlacement (const CPlacement& _ref) : CPlacement() { *this = _ref; }
CPlacement::~CPlacement (void) {}

/////////////////////////////////////////////////////////////////////////////

bool   CPlacement::DoNormal (void) {
	
	bool b_result = !!!::IsRectEmpty(&this->Rect());
	if (!b_result)
		return b_result;

	if (this->Rect().left > this->Rect().right) {
		const long left = this->Rect().left; this->Rect().left = this->Rect().right; this->Rect().right =  left; b_result = true;
	}
	if (this->Rect().top > this->Rect().bottom) {
		const long top = this->Rect().top; this->Rect().top = this->Rect().bottom; this->Rect().bottom = top; b_result = true;
	}

	return b_result;
}

bool   CPlacement::IsNormal (void) const { return (this->Rect().left < this->Rect().right && this->Rect().top < this->Rect().bottom); }

bool   CPlacement::Includes (const t_point& _pt) const {
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-ptinrect ;
	bool b_result = this->IsNormal();
	if (!b_result)
		return b_result;

	return !!::PtInRect(&this->Rect(), _pt);
}

bool   CPlacement::Intercepts (const t_rect& _rect) const {
	// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-intersectrect ;
	bool b_result = !(::IsRectEmpty(&this->Rect()) || ::IsRectEmpty(&_rect));
	if (!b_result)
		return b_result;

	t_rect rc_result = {0};
	b_result = !!::IntersectRect(&rc_result, &this->Rect(), &_rect);

	return b_result;
}

const
t_rect&  CPlacement::Rect (void) const { return this->m_rect; }
t_rect&  CPlacement::Rect (void)       { return this->m_rect; }

/////////////////////////////////////////////////////////////////////////////

CPlacement&  CPlacement::operator = (const CPlacement& _ref) { *this << _ref.Rect(); return *this; }
CPlacement&  CPlacement::operator <<(const t_rect& _rect) { this->Rect() = _rect; return *this;  }

/////////////////////////////////////////////////////////////////////////////

CPosition:: CPosition (void) {}

/////////////////////////////////////////////////////////////////////////////
const
t_point  CPosition::Center (void) const {
	return t_point{
		this->Anchor().X() + static_cast<_long>(this->Size().W() / 2),
		this->Anchor().Y() + static_cast<_long>(this->Size().H() / 2)
	};
}
/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace popup { namespace layout { namespace _impl {

	void PrimaryMonitorArea (CPosition& _pos) {

		const POINT ptZero = {0};
		// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-monitorfrompoint ;
		const HMONITOR hMonitor = ::MonitorFromPoint(ptZero, MONITOR_DEFAULTTOPRIMARY);

		MONITORINFO mInfo  = {0};
		mInfo.cbSize = sizeof(MONITORINFO); // https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-monitorinfo ;
		::GetMonitorInfo(hMonitor, &mInfo); // https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmonitorinfoa ;

		_pos.Anchor().X(mInfo.rcWork.left);
		_pos.Anchor().Y(mInfo.rcWork.top );

		_pos.Size().W(__W(mInfo.rcWork));
		_pos.Size().H(__H(mInfo.rcWork));
	}

}}}}

using namespace ex_ui::popup::layout::_impl;

/////////////////////////////////////////////////////////////////////////////

CPrimary:: CPrimary (void) : TBase() {  PrimaryMonitorArea(*this); }
CPrimary::~CPrimary (void) {}

/////////////////////////////////////////////////////////////////////////////

t_rect  CPrimary::Autosize (void) const {
	
	const TSizeU  sz_wnd = { TBase::Size().W() / 2, (TBase::Size().H() / 4) * 2};
	
	return this->Centered(sz_wnd);
}

t_rect  CPrimary::Centered (const TSizeU & _size) const {
#if (0)
	const t_point left_top = {
		TBase::Size().W() / 2  - _size.W() / 2, // 4 (four) dividings;
		TBase::Size().H() / 2  - _size.H() / 2,
	};

	t_rect center_ = {
		left_top.x,
		left_top.y,
		left_top.x + _size.W(),
		left_top.y + _size.H()
	};
#else
	const t_point pt_at  = TBase::Center();
//	const t_rect center_ = {pt_at.x - _size.W()/ 2, pt_at.y - _size.H() / 2, pt_at.x + _size.W() / 2, pt_at.y + _size.H() / 2};  // 4 (four) dividings;
	const t_rect center_ = {
		pt_at.x - static_cast<_long>(_size.W() / 2),
		pt_at.y - static_cast<_long>(_size.H() / 2), center_.left + (_long)_size.W(), center_.top + (_long)_size.H()}; // 2 (two ) dividings;
#endif
	return center_;
}

t_size  CPrimary::Default  (const float _coeff) const {

	if (0.0 == _coeff)
		return t_size { _long(TBase::Size().W()), _long(TBase::Size().H()) };
	else
		return t_size { _long(TBase::Size().W()/_coeff), _long(TBase::Size().H()/_coeff) };
}

/////////////////////////////////////////////////////////////////////////////

CWndLayout:: CWndLayout (void) : TBase() { m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CWndLayout::~CWndLayout (void) {}

/////////////////////////////////////////////////////////////////////////////

TErrorRef    CWndLayout::Error (void) const { return m_error; }