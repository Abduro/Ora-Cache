/*
	Created by Tech_dog (ebontrop@gmail.com) on 21-Aug-2020 at 6:41:32a, UTC+7, Novosibirsk, Friday;
	This is Ebo Pack shared tabbed control layout interface implementation file;
*/
#include "sfx.tabs.lay.h"
#include "sfx.tabs.ctrl.h"

using namespace ex_ui::controls::sfx::tabbed;
using namespace ex_ui::controls::sfx::tabbed::layout;

#ifndef __H
#define __H(rc) (rc.bottom - rc.top)
#endif

#ifndef __W
#define __W(rc) (rc.right - rc.left)
#endif

/////////////////////////////////////////////////////////////////////////////

CActiveTab:: CActiveTab (CControl& _ctrl) : m_ctrl(_ctrl) {
	// https://stackoverflow.com/questions/64772928/how-to-initialize-stdmap-by-an-array ;
	try {
		this->m_borders.insert(::std::make_pair(_ndx::e_ab, CBorder(_ndx::e_ab)));
		this->m_borders.insert(::std::make_pair(_ndx::e_bc, CBorder(_ndx::e_bc)));
		this->m_borders.insert(::std::make_pair(_ndx::e_cd, CBorder(_ndx::e_cd)));
		this->m_borders.insert(::std::make_pair(_ndx::e_de, CBorder(_ndx::e_de)));
		this->m_borders.insert(::std::make_pair(_ndx::e_ef, CBorder(_ndx::e_ef)));
		this->m_borders.insert(::std::make_pair(_ndx::e_fg, CBorder(_ndx::e_fg)));
		this->m_borders.insert(::std::make_pair(_ndx::e_gh, CBorder(_ndx::e_gh)));
		this->m_borders.insert(::std::make_pair(_ndx::e_ha, CBorder(_ndx::e_ha)));
	} catch (const ::std::bad_alloc&){}

}
CActiveTab::~CActiveTab (void) {}

/////////////////////////////////////////////////////////////////////////////
const
CBorder&  CActiveTab::Get (const _ndx _n_item) const {
	_n_item;
	TRawBorders::const_iterator it_ = this->m_borders.find(_n_item);
	if (it_ == this->m_borders.end()) {
		static CBorder $na;
		return $na;
	}
	else
		return it_->second;
}
CBorder&  CActiveTab::Get (const _ndx _n_item) {
	_n_item;
	TRawBorders::iterator it_ = this->m_borders.find(_n_item);
	if (it_ == this->m_borders.end()) {
		static CBorder $na;
		return $na;
	}
	else
		return it_->second;
}

const
TRawBorders& CActiveTab::Raw (void) const { return this->m_borders; }

err_code CActiveTab::Set (const t_rect& _rect) {
	_rect;
	err_code n_result = __s_ok;

	const uint32_t n_height = this->m_ctrl.Layout().Tabs().Height();
	const uint32_t n_width  = this->m_ctrl.Layout().Tabs().Width ();
	const  int16_t n_active = this->m_ctrl.Tabs().Active();

	if (0 == n_height || 0 == n_width || 0 > n_active)
		return n_result = __e_inv_arg;
#if (0)
	const t_rect& rect_ = this->m_ctrl.Layout().Rect();
#else
	t_rect rect_ = _rect;
	/*
		the border thickness is required to be taken into account; it would be better to request this control borders, but not is made yet;
	*/
	rect_.right -= 1;
	rect_.bottom -= 1;
#endif
	switch (this->m_ctrl.Layout().Tabs().Side()) {
	case TSide::e_bottom : {
		/*
		 (e)+-------+(f)
		    |(c) (h)|
		 (d)+-+   +-+(g)
		      |   |
		   (b)+---+(a)
		*/
		CPoint b_(rect_.left + n_active * n_width, rect_.bottom);
		CPoint a_(b_.X() + n_width, b_.Y());
		CBorder& ab_ = this->Get(_ndx::e_ab); ab_.Begin() = a_; ab_.End() = b_;

		CPoint c_(b_.X(), rect_.bottom - n_height);
		CBorder& bc_ = this->Get(_ndx::e_bc); bc_.Begin() = b_; bc_.End() = c_;

		CPoint d_(rect_.left, c_.Y());
		CBorder& cd_ = this->Get(_ndx::e_cd); cd_.Begin() = c_; cd_.End() = d_;

		CPoint e_(d_.X(), rect_.top);
		CBorder& de_ = this->Get(_ndx::e_de); de_.Begin() = d_; de_.End() = e_;

		CPoint f_(rect_.right, e_.Y());
		CBorder& ef_ = this->Get(_ndx::e_ef); ef_.Begin() = e_; ef_.End() = f_;

		CPoint g_(f_.X(), d_.Y());
		CBorder& fg_ = this->Get(_ndx::e_fg); fg_.Begin() = f_; fg_.End() = g_;

		CPoint h_(a_.X(), g_.Y());
		CBorder& gh_ = this->Get(_ndx::e_gh); gh_.Begin() = g_; gh_.End() = h_;

		CBorder& ha_ = this->Get(_ndx::e_ha); ha_.Begin() = h_; ha_.End() = a_;

	} break;
	case TSide::e_left : {
		/*
		   (d)+-----+(e)
		 (b)  |(c)  |
		  +---+     |
		  |    (h)  |
		  +---+     |
		 (a)  |(g)  |
		      +-----+(f)
		*/
		CPoint b_(rect_.left, rect_.top + n_active * n_width);
		CPoint a_(b_.X(), b_.Y() + n_width);
		
		CBorder& ab_ = this->Get(_ndx::e_ab); ab_.Begin() = a_; ab_.End() = b_;

		CPoint c_(b_.X() + n_height, b_.Y());
		CBorder& bc_ = this->Get(_ndx::e_bc); bc_.Begin() = b_; bc_.End() = c_;

		CPoint d_(c_.X(), rect_.top);
		CBorder& cd_ = this->Get(_ndx::e_cd); cd_.Begin() = c_; cd_.End() = d_;

		CPoint e_(rect_.right,d_.Y());
		CBorder& de_ = this->Get(_ndx::e_de); de_.Begin() = d_; de_.End() = e_;

		CPoint f_(e_.X(), rect_.bottom);
		CBorder& ef_ = this->Get(_ndx::e_ef); ef_.Begin() = e_; ef_.End() = f_;

		CPoint g_(c_.X(), f_.Y());
		CBorder& fg_ = this->Get(_ndx::e_fg); fg_.Begin() = f_; fg_.End() = g_;

		CPoint h_(g_.X(), a_.Y());
		CBorder& gh_ = this->Get(_ndx::e_gh); gh_.Begin() = g_; gh_.End() = h_;

		CBorder& ha_ = this->Get(_ndx::e_ha); ha_.Begin() = h_; ha_.End() = a_;
	} break;
	case TSide::e_right : {
		/*
		 (f)+-----+(g)
		    |     |  (a)
		    |  (h)+---+
		    |         |
		    |  (c)+---+
		    |     |  (b)
		 (e)+-----+(d)
		*/
		CPoint a_(rect_.right, rect_.top + n_active * n_width);
		CPoint b_(rect_.right, a_.Y() + n_width);
		
		CBorder& ab_ = this->Get(_ndx::e_ab); ab_.Begin() = a_; ab_.End() = b_;

		CPoint c_(b_.X() - n_height, b_.Y());
		CBorder& bc_ = this->Get(_ndx::e_bc); bc_.Begin() = b_; bc_.End() = c_;

		CPoint d_(c_.X(), rect_.bottom);
		CBorder& cd_ = this->Get(_ndx::e_cd); cd_.Begin() = c_; cd_.End() = d_;

		CPoint e_(rect_.left, d_.Y());
		CBorder& de_ = this->Get(_ndx::e_de); de_.Begin() = d_; de_.End() = e_;

		CPoint f_(e_.X(), rect_.top);
		CBorder& ef_ = this->Get(_ndx::e_ef); ef_.Begin() = e_; ef_.End() = f_;

		CPoint g_(c_.X(), f_.Y());
		CBorder& fg_ = this->Get(_ndx::e_fg); fg_.Begin() = f_; fg_.End() = g_;

		CPoint h_(g_.X(), a_.Y());
		CBorder& gh_ = this->Get(_ndx::e_gh); gh_.Begin() = g_; gh_.End() = h_;

		CBorder& ha_ = this->Get(_ndx::e_ha); ha_.Begin() = h_; ha_.End() = a_;
	} break;
	case TSide::e_top : {
		/*
		   (a)+---+(b)
		      |   |
		 (g)+-+   +-+(d)
		    |(h) (c)|
		 (f)+-------+(e)
		*/
		CPoint a_(rect_.left + n_active * n_width, rect_.top);
		CPoint b_(a_.X() + n_width, a_.Y());
		
		CBorder& ab_ = this->Get(_ndx::e_ab); ab_.Begin() = a_; ab_.End() = b_;

		CPoint c_(b_.X(), b_.Y() + n_height);
		CBorder& bc_ = this->Get(_ndx::e_bc); bc_.Begin() = b_; bc_.End() = c_;

		CPoint d_(rect_.right, c_.Y());
		CBorder& cd_ = this->Get(_ndx::e_cd); cd_.Begin() = c_; cd_.End() = d_;

		CPoint e_(d_.X(), rect_.bottom);
		CBorder& de_ = this->Get(_ndx::e_de); de_.Begin() = d_; de_.End() = e_;

		CPoint f_(rect_.left, e_.Y());
		CBorder& ef_ = this->Get(_ndx::e_ef); ef_.Begin() = e_; ef_.End() = f_;

		CPoint g_(f_.X(), d_.Y());
		CBorder& fg_ = this->Get(_ndx::e_fg); fg_.Begin() = f_; fg_.End() = g_;

		CPoint h_(g_.X(), a_.Y());
		CBorder& gh_ = this->Get(_ndx::e_gh); gh_.Begin() = g_; gh_.End() = h_;

		CBorder& ha_ = this->Get(_ndx::e_ha); ha_.Begin() = h_; ha_.End() = a_;
	} break;
	default:
		n_result = (err_code) TErrCodes::eExecute::eParameter;
	}

	return n_result;
}

/////////////////////////////////////////////////////////////////////////////

CPage:: CPage (CControl& _ctrl) : m_ctrl(_ctrl), m_rc_page{0} {}
CPage::~CPage (void) {}

/////////////////////////////////////////////////////////////////////////////
const
t_rect&  CPage::Get (void) const { return this->m_rc_page; }
err_code CPage::Set (const t_rect& _rc_from) {
	_rc_from;
	err_code n_result = __s_ok;

	if (::IsRectEmpty(&_rc_from))
		return n_result = __e_rect;

	this->m_rc_page = _rc_from; // preliminary assigning the page rectangle to input one is not good approach, due to possible succeeded errors;

	const t_rect& rc_tabs = this->m_ctrl.Layout().Tabs().Rect();
	const CPadding& pads  = this->m_ctrl.Layout().Padding();

	switch (this->m_ctrl.Layout().Tabs().Side()) {
	case TSide::e_bottom: { this->m_rc_page.bottom -= __H(rc_tabs); } break;
	case TSide::e_left  : { this->m_rc_page.left   += __W(rc_tabs); } break;
	case TSide::e_right : { this->m_rc_page.right  -= __W(rc_tabs); } break;
	case TSide::e_top   : { this->m_rc_page.top    += __H(rc_tabs); } break;
	default:
		return n_result = (err_code) TErrCodes::eExecute::eParameter;
	}

	n_result = pads.ApplyTo(this->m_rc_page) ? __s_ok : __s_false;

	return n_result;
}

/////////////////////////////////////////////////////////////////////////////
namespace ex_ui { namespace controls { namespace sfx { namespace tabbed { namespace layout {

CTabs:: CTabs (CControl& _ctrl) : m_ledge(3), m_rect{0}, m_size{0}, m_gap(0), m_ctrl(_ctrl), m_active(_ctrl) {
	this->m_size.cy = 31;
	this->m_size.cx = this->m_size.cy * 5; this->m_gap = this->m_size.cy / 2;
}
CTabs::~CTabs(void) {}

/////////////////////////////////////////////////////////////////////////////
const
CActiveTab& CTabs::Active (void) const { return this->m_active; }
CActiveTab& CTabs::Active (void)       { return this->m_active; }

uint32_t  CTabs::Gap (void) const { return m_gap; }
uint32_t& CTabs::Gap (void)       { return m_gap; }
bool      CTabs::Gap (const uint32_t _n_value) {
	_n_value;
	const bool b_changed = this->Gap() != _n_value;
	if (b_changed)
		this->m_gap = _n_value;

	return b_changed;
}

uint32_t  CTabs::Height (void) const { return (uint32_t )m_size.cy; }
uint32_t& CTabs::Height (void)       { return (uint32_t&)m_size.cy; }
bool      CTabs::Height (const uint32_t _n_value) {
	_n_value;
	const bool b_changed = this->Height() != _n_value;
	if (b_changed)
		this->m_size.cy = _n_value;

	return b_changed;
}

uint32_t  CTabs::Ledge (void) const { return m_ledge; }
uint32_t& CTabs::Ledge (void)       { return m_ledge; }
bool      CTabs::Ledge (const uint32_t _n_value) {
	_n_value;
	const bool b_changed = this->Ledge() != _n_value;
	if (b_changed)
		this->m_ledge = _n_value;

	return b_changed;
}
const
t_rect&   CTabs::Rect  (void) const { return m_rect ; }
err_code  CTabs::Rect  (const t_rect& _rc_area) {

	err_code n_result = __s_ok;

	if (::IsRectEmpty(&_rc_area))
		return n_result = __e_rect;

	this->m_rect = _rc_area;
	// m_tabs.m_ledge is not taken into account for this time;
	switch (this->Side()) {
	case TSide::e_bottom: { this->m_rect.top = _rc_area.bottom - this->Height(); } break;
	case TSide::e_left  : { this->m_rect.right = _rc_area.left - this->Height(); } break;
	case TSide::e_right : { this->m_rect.left = _rc_area.right - this->Height(); } break;
	case TSide::e_top   : { this->m_rect.bottom = _rc_area.top - this->Height(); } break;
	default:
		n_result = (err_code) TErrCodes::eExecute::eParameter;
	}

	return n_result;
}

TSide     CTabs::Side  (void) const { return m_sides.Selected()  ; }
TSide&    CTabs::Side  (void)       { return m_sides.Selected()  ; }

bool      CTabs::Side  (const TSide _side) {
	_side;
	const bool b_changed = this->Side() != _side;

	if (b_changed)
		this->m_sides.Selected() = _side;

	return b_changed;
}

const
t_size&   CTabs::Size  (void) const { return m_size; }
uint32_t& CTabs::Width (void)       { return (uint32_t&)m_size.cx; }

/////////////////////////////////////////////////////////////////////////////
}}}}}
/////////////////////////////////////////////////////////////////////////////

CLayout:: CLayout (CControl& _ctrl) : m_ctrl(_ctrl), m_rect{0}, m_page(_ctrl), m_tabs(_ctrl) { m_error >> __CLASS__ << __METHOD__ << __s_ok; }
CLayout::~CLayout (void) {}

/////////////////////////////////////////////////////////////////////////////

TError&   CLayout::Error  (void) const { return this->m_error ; }

const
CPadding& CLayout::Padding(void) const { return this->m_padding; }
CPadding& CLayout::Padding(void)       { return this->m_padding; }

const
CPage&    CLayout::Page (void) const { return this->m_page; }
CPage&    CLayout::Page (void)       { return this->m_page; }
const
t_rect&   CLayout::Rect (void) const { return this->m_rect; }

err_code  CLayout::Update (void) {

	err_code n_result = __s_ok;

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

	// (1) sets the rectangle for tabs itself;
	n_result = this->Tabs().Rect(rc_area);
	// (2) updates border position(s);
	this->m_ctrl.Borders() << rc_area;
	// (3) updates active tab borders;
	this->m_tabs.Active().Set(rc_area);
	// (4) updates page rectangle;
	this->Page().Set(rc_area);

	return n_result;
}

err_code  CLayout::Update (const t_rect& _rc_area) {
	_rc_area;

	if (::IsRectEmpty(&_rc_area))
		return this->m_error << __METHOD__ << __e_rect;

	CWindow wnd_ = this->m_ctrl.Window();
	if (false == wnd_.IsWindow())
		return this->m_error << __METHOD__ << (err_code) TErrCodes::eExecute::eState;

	t_rect rc_area_ = ((*this) = _rc_area);

	if (false == wnd_.SetWindowPos(0, &rc_area_, SWP_NOACTIVATE|SWP_NOZORDER))
		return (this->m_error << __METHOD__).Last();

	return this->Update();
}

const
ex_ui::controls::sfx::tabbed::layout::CTabs&    CLayout::Tabs (void) const  { return this->m_tabs; }
ex_ui::controls::sfx::tabbed::layout::CTabs&    CLayout::Tabs (void)        { return this->m_tabs; }

/////////////////////////////////////////////////////////////////////////////

CLayout&  CLayout::operator<<(const t_rect& _rc_area) { this->Update(*this = _rc_area); return *this; }

t_rect    CLayout::operator =(const t_rect& _rc_area) const {
	
	t_rect rc_ = {0};

	if (::IsRectEmpty(&_rc_area)) {
		this->m_error << __METHOD__ << __e_rect;
		return rc_;
	}

	rc_  = _rc_area;
	return rc_;
}