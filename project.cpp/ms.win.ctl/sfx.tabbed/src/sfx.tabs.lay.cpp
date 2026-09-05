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

#pragma region cls::CActiveTab{}

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

err_code CActiveTab::Set (const rect_t& _rect) {
	_rect;
	err_code n_result = __s_ok;

	const uint32_t n_height = this->m_ctrl.Layout().Tabs().Height();
	const uint32_t n_width  = this->m_ctrl.Layout().Tabs().Width ();
	const  int16_t n_active = this->m_ctrl.Tabs().Active();
	if (0 > n_active)
		return n_result = __e_inv_arg;
	const rect_t&  rc_strip = this->m_ctrl.Tabs().Tab(n_active).Strip();
	const uint8_t  u_thick  = this->m_ctrl.Tabs().Tab(n_active).Page().Borders().Bottom().Thickness(); // it is supposed all borders have the same thickness;

	if (::IsRectEmpty(&rc_strip) || 0 == u_thick)
		return n_result = __e_inv_arg;
#if (0)
	const rect_t& rect_ = this->m_ctrl.Layout().Rect();
#else
	rect_t rect_ = _rect;
	/*
		the border thickness is required to be taken into account; it would be better to request this control borders, but not is made yet;
	*/
	rect_.right  -= u_thick;
	rect_.bottom -= u_thick;
#endif
	switch (this->m_ctrl.Layout().Tabs().LocatedOn()) {
	case TSide::e_bottom :{
		// const THorzAlign& h_align = align.Horz();
		/*THorzAlign::eLeft; THorzAlign::eCenter; THorzAlign::eRight;
		  (e)+-------+(f)     (e)+-------+(f)      (e)+-------+(f)
		     |(c) (h)|           |(c) (h)|            |(c) (h)|
		  (d)+   +---+(g)     (d)+-+   +-+(g)      (d)+---+   +(g)
		     |   |                 |   |                  |   |
		  (b)+---+(a)           (b)+---+(a)            (b)+---+(a)

		  in case of left alignment the 'cd' border may have zero length if the active tab index equals to '0';
		  in case of right alignment the 'gh' border may have zero length if the active tab index equals to the count of the tabs - 1;
		*/
		// this is the points of the tab strip:
		CPoint a_(rc_strip.right - u_thick, rc_strip.bottom - u_thick);
		CPoint b_(rc_strip.left           , rc_strip.bottom - u_thick);
		CPoint c_(rc_strip.left           , rc_strip.top);
		CPoint h_(rc_strip.right - u_thick, rc_strip.top);

		CBorder& ab_ = this->Get(_ndx::e_ab); ab_.Begin() = a_; ab_.End() = b_; // the bottom edge of the tab bookmark;
		CBorder& bc_ = this->Get(_ndx::e_bc); bc_.Begin() = b_; bc_.End() = c_; // the left edge of the tab bookmark;
		CBorder& ha_ = this->Get(_ndx::e_ha); ha_.Begin() = h_; ha_.End() = a_; // the right edge of the tab bookmark;

		CPoint d_(rect_.left, c_.Y()); // X-coord of the 'd_' point equals always to the *left* side of the rectangle;
		CBorder& cd_ = this->Get(_ndx::e_cd); cd_.Begin() = c_; cd_.End() = d_; // the left-bottom edge of the tab body;

		CPoint e_(d_.X(), rect_.top); // Y-coord of the 'e_' point equals always to the *top* value of the rectangle;
		CBorder& de_ = this->Get(_ndx::e_de); de_.Begin() = d_; de_.End() = e_; //  the left edge of the tab body;

		CPoint f_(rect_.right, e_.Y()); // X-coord of the 'f_' point equals always to the *right* value of the rectangle;
		CBorder& ef_ = this->Get(_ndx::e_ef); ef_.Begin() = e_; ef_.End() = f_; //  the top edge of the tab body;

		CPoint g_(f_.X(), d_.Y());
		CBorder& fg_ = this->Get(_ndx::e_fg); fg_.Begin() = f_; fg_.End() = g_; //  the right edge of the tab body;
		CBorder& gh_ = this->Get(_ndx::e_gh); gh_.Begin() = g_; gh_.End() = h_; //  the right-bottom edge of the tab body;
	} break;
	case TSide::e_left : {
		/*TVertAlign::eBottom; TVertAlign::eMiddle; TVertAlign::eTop;
		      (d)+-----+(e)        (d)+-----+(e)    (b)+---+-----+(e)
		         |     |         (b)  |(c)  |          | (c)(d)  |   
		         |     |          +---+     |       (a)+---+(h)  |   
		      (c)|     |          |         |              |     |   
		 (b) +---+     |          +---+(h)  |              |     |   
		     | (h)(g)  |         (a)  |     |              |     |   
		 (a) +---+-----+(f)        (g)+-----+(f)        (g)+-----+(f)

		 in case of bottom alignment the 'gh' border may have zero length if the active tab has index '0';
		 in case of the top alignment the 'cd' border may have zero length if the active tab index equals to the count of the tabs - 1;
		*/
		// this is the points of the tab strip:
		CPoint a_(rc_strip.left , rc_strip.bottom - u_thick);
		CPoint b_(rc_strip.left , rc_strip.top + u_thick);
		CPoint c_(rc_strip.right, rc_strip.top + u_thick);
		CPoint h_(rc_strip.right, rc_strip.bottom - u_thick);

		CBorder& ab_ = this->Get(_ndx::e_ab); ab_.Begin() = a_; ab_.End() = b_;
		CBorder& bc_ = this->Get(_ndx::e_bc); bc_.Begin() = b_; bc_.End() = c_;
		CBorder& ha_ = this->Get(_ndx::e_ha); ha_.Begin() = h_; ha_.End() = a_;

		CPoint d_(c_.X(), rect_.top); // Y-coord of 'd' point equals always to the *top* value of the rectangle; 
		CBorder& cd_ = this->Get(_ndx::e_cd); cd_.Begin() = c_; cd_.End() = d_;

		CPoint e_(rect_.right,d_.Y()); // X-coord of 'e' point always equals to the *right* value of the rectnagle;
		CBorder& de_ = this->Get(_ndx::e_de); de_.Begin() = d_; de_.End() = e_;

		CPoint f_(e_.X(), rect_.bottom); // Y-coord of 'f' point equals always to the *bottom* value of the rectangle;
		CBorder& ef_ = this->Get(_ndx::e_ef); ef_.Begin() = e_; ef_.End() = f_;

		CPoint g_(c_.X(), f_.Y());
		CBorder& fg_ = this->Get(_ndx::e_fg); fg_.Begin() = f_; fg_.End() = g_;
		CBorder& gh_ = this->Get(_ndx::e_gh); gh_.Begin() = g_; gh_.End() = h_; // may have '0' length in case of '0' index of active tab;
	} break;
	case TSide::e_right : {
		/*TVertAlign::eBottom; TVertAlign::eMiddle; TVertAlign::eTop;
		 (f)+-----+(g)         (f)+-----+(g)        (f)+-----+---+ (a)
		    |     |               |     |  (a)         |  (g)(h) |    
		    |     |               |  (h)+---+          |  (c)+---+ (b)
		    |     |               |         |          |     |        
		    |  (h)+---+(a)        |  (c)+---+          |     |        
		    |  (d)(c) |           |     |  (b)         |     |        
		 (e)+-----+---+(b)     (e)+-----+(d)        (e)+-----+(d)     
		 in case of the bottom alignment the 'cd' border may have '0' length if active tab index equals to 'tabs.count() - 1';
		 in case of the top alignment the 'gh' border may have '0' length if active tab index equals to '0';
		*/
		// this is the points of the tab strip:
		CPoint a_(rc_strip.right - u_thick, rc_strip.top);
		CPoint b_(rc_strip.right - u_thick, rc_strip.bottom - u_thick);
		CPoint c_(rc_strip.left, rc_strip.bottom - u_thick);
		CPoint h_(rc_strip.left, rc_strip.top);

		CBorder& ab_ = this->Get(_ndx::e_ab); ab_.Begin() = a_; ab_.End() = b_;
		CBorder& bc_ = this->Get(_ndx::e_bc); bc_.Begin() = b_; bc_.End() = c_;
		CBorder& ha_ = this->Get(_ndx::e_ha); ha_.Begin() = h_; ha_.End() = a_;

		CPoint d_(c_.X(), rect_.bottom); // Y-coord value of the 'd' point equals always to the *bottom* value of the rectangle;
		CBorder& cd_ = this->Get(_ndx::e_cd); cd_.Begin() = c_; cd_.End() = d_; // may have '0' length if active tab index equals to 'tabs.count() - 1';

		CPoint e_(rect_.left, d_.Y());  // X-coord value of the 'e' point equals always to the *left* value of the rectangle;
		CBorder& de_ = this->Get(_ndx::e_de); de_.Begin() = d_; de_.End() = e_;

		CPoint f_(e_.X(), rect_.top); // Y-coord value of the 'f' point equals always to the *top* value of the rectangle;
		CBorder& ef_ = this->Get(_ndx::e_ef); ef_.Begin() = e_; ef_.End() = f_;

		CPoint g_(c_.X(), f_.Y());
		CBorder& fg_ = this->Get(_ndx::e_fg); fg_.Begin() = f_; fg_.End() = g_;
		CBorder& gh_ = this->Get(_ndx::e_gh); gh_.Begin() = g_; gh_.End() = h_;
	} break;
	case TSide::e_top : {
		/*THorzAlign::eLeft; THorzAlign::eCenter; THorzAlign::eRight;
		  (a)+---+(b)            (a)+---+(b)           (a)+---+(b)  
		     |   |(c)               |   |                 |   |     
		  (g)+(h)+---+(d)      (g)+-+   +-+(d)     (g)+---+(c)+(d)
		     |       |            |(h) (c)|           |  (h)  |   
		  (f)+-------+(e)      (f)+-------+(e)     (f)+-------+(e)

		  in case of the left alighment the 'gh' line may have '0' length if the active tab index equals to '0';
		  in case of the right alignment the 'cd' line may have '0' length if the active tab index equals to 'tabs.count() - 1';
		*/
		// this is the points of the tab strip:
		CPoint a_(rc_strip.left , rc_strip.top);
		CPoint b_(rc_strip.right - u_thick, rc_strip.top);
		CPoint c_(rc_strip.right - u_thick, rc_strip.bottom);
		CPoint h_(rc_strip.left , rc_strip.bottom);

		CBorder& ab_ = this->Get(_ndx::e_ab); ab_.Begin() = a_; ab_.End() = b_; // the top edge of the tab bookmark;
		CBorder& bc_ = this->Get(_ndx::e_bc); bc_.Begin() = b_; bc_.End() = c_; // the right edge of the tab bookmark;
		CBorder& ha_ = this->Get(_ndx::e_ha); ha_.Begin() = h_; ha_.End() = a_; // the left edge of the tab bookmark;

		CPoint d_(rect_.right, c_.Y()); // X-coord of the 'd' point equals always to the *right* side value of the rectangle;
		CBorder& cd_ = this->Get(_ndx::e_cd); cd_.Begin() = c_; cd_.End() = d_; // the top-right edge of the tab body;

		CPoint e_(d_.X(), rect_.bottom); // Y-coord of the 'e' point equals always to the *bottom* side value of the rectangle;
		CBorder& de_ = this->Get(_ndx::e_de); de_.Begin() = d_; de_.End() = e_; // the right edge of the tab body;

		CPoint f_(rect_.left, e_.Y()); // X-coord of the 'f' point equals always to the *left* side value of the rectangle;
		CBorder& ef_ = this->Get(_ndx::e_ef); ef_.Begin() = e_; ef_.End() = f_; // the bottom edge of the tab body;

		CPoint g_(f_.X(), d_.Y());
		CBorder& fg_ = this->Get(_ndx::e_fg); fg_.Begin() = f_; fg_.End() = g_; // the left edge of the tab body;
		CBorder& gh_ = this->Get(_ndx::e_gh); gh_.Begin() = g_; gh_.End() = h_; // the left-top edge of the tab body;
	} break;
	default:
		n_result = (err_code) TErrCodes::eExecute::eParameter;
	}

	return n_result;
}

#pragma endregion

namespace ex_ui { namespace controls { namespace sfx { namespace tabbed { namespace layout {

CTabs:: CTabs (CControl& _ctrl) : m_ribbon{0}, m_size{0}, m_gap(0), m_ctrl(_ctrl), m_active(_ctrl), m_txt_orient(e_txt_orient::e_horz) {
	this->m_size.cy = 31;
	this->m_size.cx = this->m_size.cy * 5; this->m_gap = this->m_size.cy / 2;
}
CTabs::~CTabs(void) {}

const
CActiveTab& CTabs::Active (void) const { return this->m_active; }
CActiveTab& CTabs::Active (void)       { return this->m_active; }

const
TAlign&   CTabs::Align (void) const { return this->m_align; }
TAlign&   CTabs::Align (void)       { return this->m_align; }

using e_txt_orient = CTabs::e_txt_orient;

e_txt_orient CTabs::Cap_orient (void) const { return this->m_txt_orient; }
bool         CTabs::Cap_orient (const e_txt_orient _value) {
	const bool b_changed = this->Cap_orient() != _value; if (b_changed) this->m_txt_orient = _value; return b_changed;
}

uint32_t  CTabs::Gap (void) const { return m_gap; }
bool      CTabs::Gap (const uint32_t _n_value) {
	_n_value;
	const bool b_changed = this->Gap() != _n_value;
	if (b_changed)
		this->m_gap = _n_value;

	return b_changed;
}

uint32_t  CTabs::Height (void) const { return (uint32_t )m_size.cy; }
bool      CTabs::Height (const uint32_t _n_value) {
	_n_value;
	const bool b_changed = this->Height() != _n_value;
	if (b_changed)
		this->m_size.cy = _n_value;

	return b_changed;
}

const
rect_t&   CTabs::Ribbon (void) const { return m_ribbon ; }
err_code  CTabs::Ribbon (const rect_t& _rc_area) {

	err_code n_result = __s_ok;

	if (::IsRectEmpty(&_rc_area))
		return n_result = __e_rect;

	this->m_ribbon = _rc_area;
	// m_tabs.m_ledge is not taken into account for this time;
	switch (this->LocatedOn()) {
	case TSide::e_bottom: { this->m_ribbon.top = _rc_area.bottom - this->Height(); } break;
	case TSide::e_left  : { this->m_ribbon.right = _rc_area.left + this->Height(); } break;
	case TSide::e_right : { this->m_ribbon.left = _rc_area.right - this->Height(); } break;
	case TSide::e_top   : { this->m_ribbon.bottom = _rc_area.top + this->Height(); } break;
	default:
		return n_result = (err_code) TErrCodes::eExecute::eParameter;
	}

	// ToDo:: no gaps between tabs are applied yet; this option is deprecated for this version of the implementation;

	if (this->m_sides.IsHorz()) { // tabs reside in horizontal line;
		if (THorzAlign::eLeft == this->Align().Horz().Value())
		{
			long_t n_left = this->m_ribbon.left;
			for (int16_t i_ = 0; i_ < this->m_ctrl.Tabs().Count(); i_++) {
				this->m_ctrl.Tabs().Tab(i_).Strip() = this->m_ribbon;
				this->m_ctrl.Tabs().Tab(i_).Strip().left  = n_left; n_left += this->Width();
				this->m_ctrl.Tabs().Tab(i_).Strip().right = n_left;
			}
		}
		else if (THorzAlign::eCenter == this->Align().Horz().Value()) {
			long_t u_left = this->m_ribbon.left + (__W(this->m_ribbon) - this->TotalWidth()) / 2;
			for (int16_t i_ = 0; i_ < this->m_ctrl.Tabs().Count(); i_++) {
				this->m_ctrl.Tabs().Tab(i_).Strip() = this->m_ribbon;
				this->m_ctrl.Tabs().Tab(i_).Strip().left  = u_left; u_left += this->Width();
				this->m_ctrl.Tabs().Tab(i_).Strip().right = u_left;
			}
		}
		else {
			long_t n_right = this->m_ribbon.right;
			for (int16_t i_ = this->m_ctrl.Tabs().Count() - 1; -1 < i_; i_--) {
				this->m_ctrl.Tabs().Tab(i_).Strip() = this->m_ribbon;
				this->m_ctrl.Tabs().Tab(i_).Strip().right  = n_right; n_right -= this->Width();
				this->m_ctrl.Tabs().Tab(i_).Strip().left   = n_right;
			}
		}
	}

	if (this->m_sides.IsVert()) { // tabs reside in vertical line;
		if (TVertAlign::eBottom == this->Align().Vert().Value()) {
			long_t n_bottom = this->m_ribbon.bottom;
			for (int16_t i_ = 0; i_ < this->m_ctrl.Tabs().Count(); i_++) {
				this->m_ctrl.Tabs().Tab(i_).Strip() = this->m_ribbon;
				this->m_ctrl.Tabs().Tab(i_).Strip().bottom = n_bottom; n_bottom -= this->Width();
				this->m_ctrl.Tabs().Tab(i_).Strip().top = n_bottom;
			}
		}
		else if (TVertAlign::eMiddle == this->Align().Vert().Value()) {
			long_t n_bottom = this->m_ribbon.bottom - (__H(this->m_ribbon) - this->TotalHeight()) / 2;
			for (int16_t i_ = 0; i_ < this->m_ctrl.Tabs().Count(); i_++) {
				this->m_ctrl.Tabs().Tab(i_).Strip() = this->m_ribbon;
				this->m_ctrl.Tabs().Tab(i_).Strip().bottom  = n_bottom; n_bottom -= this->Width();
				this->m_ctrl.Tabs().Tab(i_).Strip().top = n_bottom;
			}
		}
		else {
			long_t n_top = this->m_ribbon.top;
			for (int16_t i_ = this->m_ctrl.Tabs().Count() - 1; -1 < i_; i_--) {
				this->m_ctrl.Tabs().Tab(i_).Strip() = this->m_ribbon;
				this->m_ctrl.Tabs().Tab(i_).Strip().top = n_top; n_top += this->Width();
				this->m_ctrl.Tabs().Tab(i_).Strip().bottom = n_top;
			}
		}
	}

	return n_result;
}

TSide     CTabs::LocatedOn (void) const  { return this->m_sides.Selected(); }
bool      CTabs::LocatedOn (const TSide _side) {
	_side;
	const bool b_changed = this->LocatedOn() != _side;

	if (b_changed)
		this->m_sides.Selected() = _side;

	return b_changed;
}
const
CSides&   CTabs::Sides (void) const { return this->m_sides; }
CSides&   CTabs::Sides (void)       { return this->m_sides; }

const
t_size&   CTabs::Size  (void) const { return m_size; }

uint32_t  CTabs::TotalHeight(void) const { 
	
	uint32_t u_height = 0;
	for (uint16_t i_ = 0; i_ < this->m_ctrl.Tabs().Count(); i_++) u_height += this->m_ctrl.Layout().Tabs().Height();
	return u_height;
}
uint32_t  CTabs::TotalWidth (void) const {

	uint32_t u_width = 0;
	for (uint16_t i_ = 0; i_ < this->m_ctrl.Tabs().Count(); i_++) u_width += this->m_ctrl.Layout().Tabs().Width();
	return u_width;
}

void      CTabs::Update(void) {

	const rect_t& rc_area = this->m_ctrl.Layout().Rect(); // gets available rectangle to tabbed control;
	const rect_t& rc_ribbon = this->Ribbon(); // this rectangle is expected to be calculated properly in accordance with tabs' side;

	rect_t rc_page = rc_area;
	/* The ribbon rectangle is already updated and has proper values that can be taken into account like as the following conditions:
	*/
	if (this->Sides().IsHorz()) {
		if (rc_ribbon.top == rc_area.top) { // the ribbon resides on the top side of the control;
			rc_page.top = rc_ribbon.bottom;
		}
		else { // otherwise the ribbon on the bottom side of the control;
			rc_page.bottom = rc_ribbon.top;
		}
	}
	else {
		if (rc_ribbon.left == rc_area.left) { // the ribbon resides on the left side of the control;
			rc_page.left = rc_ribbon.right;
		}
		else { // otherwise the ribbon on the right side of the control;
			rc_page.right = rc_ribbon.left;
		}
	}

	this->m_ctrl.Layout().Padding().ApplyTo(rc_page);

#if defined(_DEBUG) && defined(_use_track)
	__trace_info_3(
		_T("{_rc_area:l:%d;t:%d;r:%d;b:%d}"), rc_page.left, rc_page.top, rc_page.right, rc_page.bottom
	);
#endif

	for (int16_t i_ = 0; i_ < this->m_ctrl.Tabs().Count(); i_++) {

		CPage& page = this->m_ctrl.Tabs().Tab(i_).Page();
		if (page.Is_valid() == false)
			continue;
#if (0) // this leads to the bug: the layout of the page is not updated by proper rectangle that is applied right here;
		::ATL::CWindow(page.Handle()).MoveWindow(&rc_page, true);
#else
		page.MoveTo(rc_page, true);
#endif
	}
}

uint32_t& CTabs::Width (void)       { return (uint32_t&)m_size.cx; }

}}}}}

#pragma region cls::CLayout{}

CLayout:: CLayout (CControl& _ctrl) : m_ctrl(_ctrl), m_rect{0}, m_tabs(_ctrl), m_padding(5,5,-5,-5) {
	m_error >> __CLASS__ << __METHOD__ << __s_ok;
}
CLayout::~CLayout (void) {}

TError&   CLayout::Error  (void) const { return this->m_error ; }

const
CPadding& CLayout::Padding(void) const { return this->m_padding; }
CPadding& CLayout::Padding(void)       { return this->m_padding; }

const
rect_t&   CLayout::Rect (void) const { return this->m_rect; }

err_code  CLayout::Update (void) {

	err_code n_result = __s_ok;

	CWindow wnd_ = this->m_ctrl.Window();

	if (false == wnd_.IsWindow()) {
		return this->m_error << __METHOD__ << (err_code) TErrCodes::eExecute::eState;
	}

	rect_t rc_area = {0};

	if (false == wnd_.GetClientRect(&rc_area)) {
		return (this->m_error << __METHOD__).Last();
	}
	else
		this->m_rect = rc_area;

	n_result = this->Tabs().Ribbon(rc_area); // (1) sets the rectangle for tabs itself, aka ribbon of the tabs;
	this->m_ctrl.Borders() << rc_area;       // (2) updates border position(s);
	this->m_tabs.Active().Set(rc_area);      // (3) updates active tab borders;
	this->m_tabs.Update();                   // (4) updates each tab page internal window size and position;

	return n_result;
}

err_code  CLayout::Update (const rect_t& _rc_area) {
	_rc_area;
	if (::IsRectEmpty(&_rc_area))
		return this->m_error << __METHOD__ << __e_rect;

	CWindow wnd_ = this->m_ctrl.Window();
	if (false == wnd_.IsWindow())
		return this->m_error << __METHOD__ << (err_code) TErrCodes::eExecute::eState;

	rect_t rc_area_ = ((*this) = _rc_area);

	if (false == wnd_.SetWindowPos(0, &rc_area_, SWP_NOACTIVATE|SWP_NOZORDER))
		return (this->m_error << __METHOD__).Last();

	return this->Update();
}

const
ex_ui::controls::sfx::tabbed::layout::CTabs&    CLayout::Tabs (void) const  { return this->m_tabs; }
ex_ui::controls::sfx::tabbed::layout::CTabs&    CLayout::Tabs (void)        { return this->m_tabs; }

CLayout&  CLayout::operator<<(const rect_t& _rc_area) { this->Update(*this = _rc_area); return *this; }

rect_t    CLayout::operator =(const rect_t& _rc_area) const {
	
	rect_t rc_ = {0};

	if (::IsRectEmpty(&_rc_area)) {
		this->m_error << __METHOD__ << __e_rect;
		return rc_;
	}

	rc_  = _rc_area;
	return rc_;
}

#pragma endregion