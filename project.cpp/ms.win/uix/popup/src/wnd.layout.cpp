/*
	Created by Tech_dog (ebontrop@gmail.com) on 11-Dec-2021 at 3:13:24.2838827 pm, UTC+7, Novosibirsk, Saturday;
	This is base window layout interface implementation file;
*/
#include "wnd.layout.h"

using namespace ex_ui::popup::layout;

#define __H(rc) (rc.bottom - rc.top)
#define __W(rc) (rc.right - rc.left)

/////////////////////////////////////////////////////////////////////////////

CPosition:: CPosition (void) {}
CPosition:: CPosition (const TPoint& _anchor, const TSize & _size) : CPosition() { *this << _anchor << _size; }
CPosition:: CPosition (const CPosition& _src) : CPosition() { *this =  _src; }
CPosition:: CPosition (CPosition&& _victim) : CPosition() { *this = _victim; }
CPosition::~CPosition (void) {}

/////////////////////////////////////////////////////////////////////////////
const
TPoint&  CPosition::Anchor (void) const { return this->m_anchor; }
TPoint&  CPosition::Anchor (void)       { return this->m_anchor; }

const
t_point  CPosition::Center (void) const {

	return t_point{this->Anchor().X() + this->Size().W() / 2, this->Anchor().Y() + this->Size().H() / 2};

}
#if defined(_DEBUG)

CString  CPosition::Print (const e_print e_opt) const {
	e_opt;

	static _pc_sz pc_sz_pat_a = _T("cls::[%s::%s]>>{anchor=%s;size=%s}");
	static _pc_sz pc_sz_pat_n = _T("cls::[%s]>>{anchor=%s;size=%s}");
	static _pc_sz pc_sz_pat_r = _T("{anchor=%s;size=%s}");

	CString cs_anch = this->Anchor().Print(e_print::e_req);
	CString cs_size = this->Size().Print(e_print::e_req);

	CString cs_out;
	
	if (e_print::e_all   == e_opt) { cs_out.Format(pc_sz_pat_a, (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz) cs_anch, (_pc_sz)cs_size); }
	if (e_print::e_no_ns == e_opt) { cs_out.Format(pc_sz_pat_n, (_pc_sz)__CLASS__, (_pc_sz) cs_anch, (_pc_sz)cs_size); }
	if (e_print::e_req   == e_opt) { cs_out.Format(pc_sz_pat_r, (_pc_sz) cs_anch, (_pc_sz)cs_size); }

	if (cs_out.IsEmpty())
		cs_out.Format(_T("cls::[%s::%s].%s(#inv_arg==%u)"), (_pc_sz)__SP_NAME__, (_pc_sz)__CLASS__, (_pc_sz)__METHOD__, e_opt);

	return  cs_out;
}

#endif
const
TSize &  CPosition::Size (void) const { return this->m_size; }
TSize &  CPosition::Size (void)       { return this->m_size; }

/////////////////////////////////////////////////////////////////////////////

CPosition&  CPosition::operator = (const CPosition& _src) { *this << _src.Anchor() << _src.Size(); return *this; }
CPosition&  CPosition::operator = (CPosition&& _victim) {
	*this = _victim; _victim.Anchor().X(0); _victim.Anchor().Y(0); _victim.Size().H(0); _victim.Size().W(0); // ToDo: no reason to play with victim object; 
	return *this;
}

CPosition&  CPosition::operator << (const TPoint& _anchor) { this->Anchor() = _anchor; return *this; }
CPosition&  CPosition::operator << (const TSize & _size) { this->Size() = _size;  return *this; }

CPosition&  CPosition::operator << (const t_rect& _rect) {
	_rect;

	return *this;
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
	
	const TSize  sz_wnd = { TBase::Size().W() / 2, (TBase::Size().H() / 4) * 2};
	
	return this->Centered(sz_wnd);
}

t_rect  CPrimary::Centered (const TSize & _size) const {
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
//	const t_rect center_ = {pt_at.x - _size.W() / 2, pt_at.y - _size.H() / 2, pt_at.x + _size.W() / 2, pt_at.y + _size.H() / 2};  // 4 (four) dividings;
	const t_rect center_ = {pt_at.x - _size.W() / 2, pt_at.y - _size.H() / 2, center_.left + _size.W(), center_.top + _size.H()}; // 2 (two ) dividings;
#endif
	return center_;
}

t_size  CPrimary::Default  (const float _coeff) const {

	if (0.0 == _coeff)
		return t_size {TBase::Size().W(), TBase::Size().H()};
	else
		return t_size{_long(TBase::Size().W()/_coeff), _long(TBase::Size().H()/_coeff)};
}

/////////////////////////////////////////////////////////////////////////////

CWndLayout:: CWndLayout (void) : TBase() { m_error >> __CLASS__ << __METHOD__ << __e_not_inited; }
CWndLayout::~CWndLayout (void) {}

/////////////////////////////////////////////////////////////////////////////

TErrorRef    CWndLayout::Error (void) const { return m_error; }