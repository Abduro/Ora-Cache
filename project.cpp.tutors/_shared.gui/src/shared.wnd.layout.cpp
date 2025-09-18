/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Aug-2025 at 05:00:03.537, UTC+4, Batumi, Wednesday;
	This is Ebo Pack OpenGL tutorial main window layout interface implementation file;
*/
#include "shared.wnd.layout.h"
#include "shared.dbg.h"

using namespace ex_ui::popup::layout;

#ifndef __H
#define __H(rc) (rc.bottom - rc.top)
#define __W(rc) (rc.right - rc.left)
#endif

/////////////////////////////////////////////////////////////////////////////

CPlacement:: CPlacement (void) : m_rect{0} {}
CPlacement:: CPlacement (const CPlacement& _ref) : CPlacement() { *this = _ref; }
CPlacement::~CPlacement (void) {}

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

CPlacement&  CPlacement::operator = (const CPlacement& _ref) { *this << _ref.Rect(); return *this; }
CPlacement&  CPlacement::operator <<(const t_rect& _rect) { this->Rect() = _rect; return *this;  }

CPlacement::operator const t_rect& (void) const { return this->Rect(); }
CPlacement::operator       t_rect& (void)       { return this->Rect(); }

const
t_rect& CPlacement::operator ()(void) const { return this->Rect(); }
t_rect& CPlacement::operator ()(void)       { return this->Rect(); }

/////////////////////////////////////////////////////////////////////////////

CPosition:: CPosition (void) : TBase() {}
CPosition:: CPosition (const CPosition& _src) : CPosition() { *this = _src; }

const
t_point CPosition::Center (void) const {
	return t_point{
		(*this)().Rect().left + __W((*this)().Rect()) / 2,
		(*this)().Rect().top  + __H((*this)().Rect()) / 2
	};
}

CPosition& CPosition::operator = (const CPosition& _src) { (TBase&)*this = (const TBase&)_src; return *this; }
const
CPlacement& CPosition::operator ()(void) const { return (const TBase&)*this; }
CPlacement& CPosition::operator ()(void)       { return (TBase&)*this; }

/////////////////////////////////////////////////////////////////////////////

namespace ex_ui { namespace popup { namespace layout { namespace _impl {

	t_rect PrimaryMonitorArea (CString& _cs_name) {

		const t_point ptZero = {0};
		// https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-monitorfrompoint ;
		const HMONITOR hMonitor = ::MonitorFromPoint(ptZero, MONITOR_DEFAULTTOPRIMARY);
#if (0)
		MONITORINFO mInfo  = {0};
		mInfo.cbSize = sizeof(MONITORINFO); // https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-monitorinfo ;
#else
		MONITORINFOEX mInfo  = {0};         // https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-monitorinfoexa ;
		mInfo.cbSize = sizeof(MONITORINFOEX);
#endif
		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getmonitorinfoa ;
		if (false == !!::GetMonitorInfo(hMonitor, &mInfo)) {
			__trace_err_3(_T("%s\n"), (_pc_sz) (CError()(CError::e_cmds::e_get_last)).Print(TError::e_req));
			_cs_name = _T("#error");
		}
		else _cs_name = mInfo.szDevice;

		return mInfo.rcWork; // the empty rectangle is returned in case of error;
	}

}}}}

using namespace ex_ui::popup::layout::_impl;

CPrimary:: CPrimary (void) : TBase() {
	TBase::Rect() = PrimaryMonitorArea(this->m_name);
}
CPrimary::~CPrimary (void) {}

t_rect  CPrimary::Autosize (void) const {
	
	const t_size_u  sz_req = { static_cast<uint32_t>(abs(__W(TBase().Rect()))) / 2, static_cast<uint32_t>(abs(__H(TBase().Rect()) / 4) * 2) };
	
	return this->Centered(sz_req);
}

t_rect  CPrimary::Centered (const t_size_u & _sz_req) const {
	_sz_req;
	// there is a problem: the size can equal to zero by the width and/or the hight or more than zero, otherwise there is not sense:
	// the size value either width or height cannot be negative;
	// but points and rectangles have its attributes' data type as long, so the mixing unsigned and signed data types' values requires the cast;
	const  t_point pt_center = TBase::Center(); 
	return t_rect {
		pt_center.x - (long)_sz_req.cx / 2, pt_center.y - (long)_sz_req.cy / 2, pt_center.x + (long)_sz_req.cx / 2, pt_center.y + (long)_sz_req.cy / 2 
	};
}

t_size  CPrimary::Default  (const float _coeff) const {

	if (0.0 == _coeff)
		return t_size { _long(__W(TBase().Rect())), _long(__H(TBase().Rect())) };
	else
		return t_size { _long(__W(TBase().Rect())/_coeff), _long(__H(TBase().Rect())/_coeff) };
}

_pc_sz  CPrimary::Name (void) const { return (_pc_sz)this->m_name; }

/////////////////////////////////////////////////////////////////////////////

CRatios:: CRatios (void) {
	/*
		https://en.wikipedia.org/wiki/Advanced_Video_Coding ;
		It looks very like that nothing was made better than H.264;
		Commonly supported resolutions and aspect ratios include:
	*/
	m_ratios.push_back(t_size{ 640,  480}); //  640 x 480  ( 4:3 480p) ;
	m_ratios.push_back(t_size{ 854,  480}); //  854 x 480  (16:9 480p) ;
	m_ratios.push_back(t_size{1280,  720}); // 1280 x 720  (16:9 720p) ;
	m_ratios.push_back(t_size{1280, 1024}); // 1280 x 1024 ( 5:4);
	m_ratios.push_back(t_size{1920, 1080}); // 1920 x 1080 (16:9 1080p);
	m_ratios.push_back(t_size{1920, 1440}); // 1920 x 1440 ( 4:3);
}
CRatios:: CRatios (const CRatios& _ref) : CRatios() { *this = _ref; }
CRatios::~CRatios (void) {}

t_rect    CRatios::Accepted (const t_rect& _work_area) const {
	_work_area;
	t_rect  rc_pos = {0};
	if (!!::IsRectEmpty(&_work_area))
		return rc_pos;

	const SIZE sz_available = {__H(_work_area), __W(_work_area)};
	
	// it requires to analyze both sizes of screen, a width and a height, because system taskbar can be set to vertical position;
	// also the monitor may be set to 'Portrait' position;
	TRatios::const_iterator it_ = ::std::lower_bound(
		m_ratios.begin(), m_ratios.end(), sz_available,
		[&](const t_size& _sz, const t_size& sz_available) { return _sz.cy < sz_available.cy && _sz.cx < sz_available.cx; }
	);
	if (m_ratios.end() == it_) {} // actually it is almost impossible, but nevertheless;
	else
	{
		const t_point pt_anchor = {
			_work_area.left + (__W(_work_area) - it_->cx) / 2,
			_work_area.top  + (__H(_work_area) - it_->cy) / 2,
		};
		::SetRect(&rc_pos, pt_anchor.x, pt_anchor.y, pt_anchor.x + it_->cx, pt_anchor.y + it_->cy);
	}
	return rc_pos;
}

const
TRatios&  CRatios::Get (void) const { return this->m_ratios; }
TRatios&  CRatios::Get (void)       { return this->m_ratios; }

CRatios&  CRatios::operator = (const CRatios& _ref) { this->Get() = _ref.Get(); return *this; }