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

	const uint32_t n_height = this->m_ctrl.Layout().Ribbon().Tabs().Size().Height().Get();
	const uint32_t n_width  = this->m_ctrl.Layout().Ribbon().Tabs().Size().Width ().Get();
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
	switch (this->m_ctrl.Layout().Ribbon().LocatedOn()) {
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
#pragma region cls::CRibbon{}
using CRibbon  = ex_ui::controls::sfx::tabbed::layout::CRibbon;
using CLayTabs = ex_ui::controls::sfx::tabbed::layout::CTabs;

CRibbon::CRibbon (TabCtrl& _ctrl) : m_ctrl(_ctrl), m_tabs(_ctrl), m_rect{0} {}

TSide    CRibbon::LocatedOn (void) const  { return this->m_sides.Selected(); }
bool     CRibbon::LocatedOn (const TSide _side) {
	_side;
	const bool b_changed = this->LocatedOn() != _side;

	if (b_changed)
		this->m_sides.Selected() = _side;

	return b_changed;
}
const
rect_t&  CRibbon::Rect (void) const { return this->m_rect; }
const
CSides&  CRibbon::Sides (void) const { return this->m_sides; }
CSides&  CRibbon::Sides (void)       { return this->m_sides; }

err_code CRibbon::Update(const rect_t& _rc_area) {
	err_code n_result = __s_ok;

	if (::IsRectEmpty(&_rc_area))
		return n_result = __e_rect;

	this->m_rect = _rc_area;
	// m_tabs.m_ledge is not taken into account for this time;
	switch (this->LocatedOn()) {
	case TSide::e_bottom: { this->m_rect.top    = _rc_area.bottom - this->Tabs().Size().Height().Get(); } break;
	case TSide::e_left  : { this->m_rect.right  = _rc_area.left   + this->Tabs().Size().Height().Get(); } break;
	case TSide::e_right : { this->m_rect.left   = _rc_area.right  - this->Tabs().Size().Height().Get(); } break;
	case TSide::e_top   : { this->m_rect.bottom = _rc_area.top    + this->Tabs().Size().Height().Get(); } break;
	default:
		return n_result = (err_code) TErrCodes::eExecute::eParameter;
	}

	// ToDo:: no gaps between tabs are applied yet; this option is deprecated for this version of the implementation;

	if (this->m_sides.IsHorz()) { // tabs reside in horizontal line;
		if (THorzAlign::eLeft == this->Tabs().Align().Horz().Value())
		{
			long_t n_left = this->m_rect.left;
			for (int16_t i_ = 0; i_ < this->m_ctrl.Tabs().Count(); i_++) {
				this->m_ctrl.Tabs().Tab(i_).Strip() = this->m_rect;
				this->m_ctrl.Tabs().Tab(i_).Strip().left  = n_left; n_left += this->Tabs().Size().Width().Get();
				this->m_ctrl.Tabs().Tab(i_).Strip().right = n_left;
			}
		}
		else if (THorzAlign::eCenter == this->Tabs().Align().Horz().Value()) {
			long_t u_left = this->m_rect.left + (__W(this->m_rect) - this->Tabs().Size().Width().Total()) / 2;
			for (int16_t i_ = 0; i_ < this->m_ctrl.Tabs().Count(); i_++) {
				this->m_ctrl.Tabs().Tab(i_).Strip() = this->m_rect;
				this->m_ctrl.Tabs().Tab(i_).Strip().left  = u_left; u_left += this->Tabs().Size().Width().Get();
				this->m_ctrl.Tabs().Tab(i_).Strip().right = u_left;
			}
		}
		else {
			long_t n_right = this->m_rect.right;
			for (int16_t i_ = this->m_ctrl.Tabs().Count() - 1; -1 < i_; i_--) {
				this->m_ctrl.Tabs().Tab(i_).Strip() = this->m_rect;
				this->m_ctrl.Tabs().Tab(i_).Strip().right  = n_right; n_right -= this->Tabs().Size().Width().Get();
				this->m_ctrl.Tabs().Tab(i_).Strip().left   = n_right;
			}
		}
	}

	if (this->m_sides.IsVert()) { // tabs reside in vertical line;
		if (TVertAlign::eBottom == this->Tabs().Align().Vert().Value()) {
			long_t n_bottom = this->m_rect.bottom;
			for (int16_t i_ = 0; i_ < this->m_ctrl.Tabs().Count(); i_++) {
				this->m_ctrl.Tabs().Tab(i_).Strip() = this->m_rect;
				this->m_ctrl.Tabs().Tab(i_).Strip().bottom = n_bottom; n_bottom -= this->Tabs().Size().Width().Get();
				this->m_ctrl.Tabs().Tab(i_).Strip().top = n_bottom;
			}
		}
		else if (TVertAlign::eMiddle == this->Tabs().Align().Vert().Value()) {
			long_t n_bottom = this->m_rect.bottom - (__H(this->m_rect) - this->Tabs().Size().Width().Total()) / 2;
			for (int16_t i_ = 0; i_ < this->m_ctrl.Tabs().Count(); i_++) {
				this->m_ctrl.Tabs().Tab(i_).Strip() = this->m_rect;
				this->m_ctrl.Tabs().Tab(i_).Strip().bottom  = n_bottom; n_bottom -= this->Tabs().Size().Width().Get();
				this->m_ctrl.Tabs().Tab(i_).Strip().top = n_bottom;
			}
		}
		else {
			long_t n_top = this->m_rect.top;
			for (int16_t i_ = this->m_ctrl.Tabs().Count() - 1; -1 < i_; i_--) {
				this->m_ctrl.Tabs().Tab(i_).Strip() = this->m_rect;
				this->m_ctrl.Tabs().Tab(i_).Strip().top = n_top; n_top += this->Tabs().Size().Width().Get();
				this->m_ctrl.Tabs().Tab(i_).Strip().bottom = n_top;
			}
		}
	}

	return n_result;
}

const
CLayTabs& CRibbon::Tabs (void) const  { return this->m_tabs; }
CLayTabs& CRibbon::Tabs (void)        { return this->m_tabs; }

CRibbon&  CRibbon::operator <<(const TSide _side) { const bool b_changed = this->LocatedOn(_side); b_changed; return *this; }

#pragma endregion

namespace ex_ui { namespace controls { namespace sfx { namespace tabbed { namespace layout {

using CCaps = CTabs::CCaps;
using TSize = CTabs::CSize;

CTabs:: CTabs (CControl& _ctrl) : m_size{_ctrl}, m_gap(0), m_ctrl(_ctrl), m_active(_ctrl) {}
CTabs::~CTabs(void) {}

const
CActiveTab& CTabs::Active (void) const { return this->m_active; }
CActiveTab& CTabs::Active (void)       { return this->m_active; }

const
TAlign&   CTabs::Align (void) const { return this->m_align; }
TAlign&   CTabs::Align (void)       { return this->m_align; }
const
CCaps&    CTabs::Caps (void) const  { return this->m_caps; }
CCaps&    CTabs::Caps (void)        { return this->m_caps; }

uint32_t  CTabs::Gap (void) const { return m_gap; }
bool      CTabs::Gap (const uint32_t _n_value) {
	_n_value;
	const bool b_changed = this->Gap() != _n_value;
	if (b_changed)
		this->m_gap = _n_value;

	return b_changed;
}

const
TSize&    CTabs::Size (void) const { return m_size; }
TSize&    CTabs::Size (void)       { return m_size; }

void      CTabs::Update (void) {

	const rect_t& rc_area = this->m_ctrl.Layout().Rect(); // gets available rectangle to tabbed control;
	const rect_t& rc_ribbon = this->m_ctrl.Layout().Ribbon().Rect(); // this rectangle is expected to be calculated properly in accordance with tabs' side;
	const CSides& sides = this->m_ctrl.Layout().Ribbon().Sides();

	rect_t rc_page = rc_area;
	/* The ribbon rectangle is already updated and has proper values that can be taken into account like as the following conditions:
	*/
	if (sides.IsHorz()) {
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

}}}}}
#pragma region cls::CTabs::Caps{}

using CCaps = ex_ui::controls::sfx::tabbed::layout::CTabs::CCaps;
using e_orient = CCaps::e_orient;

CCaps::CCaps (void) : m_orient(e_orient::e_horz) {}

e_orient CCaps::Get_orient (void) const { return this->m_orient; }
bool     CCaps::Set_orient (const e_orient _value) { const bool b_changed = this->Get_orient() != _value; if (b_changed) this->m_orient = _value; return b_changed; }

bool     CCaps::Is_horz (void) const { return e_orient::e_horz == this->m_orient; }
bool     CCaps::Is_vert (void) const { return e_orient::e_vert == this->m_orient; }

e_orient CCaps::DwordToEnum (const dword_t _value) {
	if (e_orient::e_vert == _value)
	     return e_orient::e_vert;
	else return e_orient::e_horz;
}

#pragma endregion
#pragma region cls::CTabs::CSize{}

using CTabSize  = ex_ui::controls::sfx::tabbed::layout::CTabs::CSize;
using CTabHight = CTabSize::CHeight;
using CTabWidth = CTabSize::CWidth ;

CTabSize::CSize (TabCtrl& _ctrl) : m_ctrl(_ctrl), m_height(_ctrl), m_width(_ctrl) { this->Default(); }

void CTabSize::Default (void) {
	this->Height().Set(CTabHight::Min());
	this->Width ().Set(CTabWidth::Min());
}

const
CTabHight& CTabSize::Height (void) const { return this->m_height; }
CTabHight& CTabSize::Height (void)       { return this->m_height; }
const
CTabWidth& CTabSize::Width (void) const { return this->m_width;  }
CTabWidth& CTabSize::Width (void)       { return this->m_width;  }

bool CTabSize::Set (const uint32_t _w, const uint32_t _h) {
	_w; _h;
	bool b_changed = false;
	const uint32_t w_ = (CTabWidth::Min() < _w ? CTabWidth::Min() : (CTabWidth::Max() < _w ? CTabWidth::Max() : _w));
	const uint32_t h_ = (CTabHight::Min() < _h ? CTabHight::Min() : (CTabHight::Max() < _h ? CTabHight::Max() : _h));

	if (this->Height().Set(h_)) b_changed = true;
	if (this->Width().Set(w_)) b_changed = true;

	return b_changed;
}

#pragma endregion
#pragma region cls::CTabs::CSize::CHight{}

using THeight = ex_ui::controls::sfx::tabbed::layout::CTabs::CSize::CHeight;

THeight::CHeight (TabCtrl& _ctrl) : m_ctrl(_ctrl), m_value(0) {}

uint32_t THeight::Get (void) const { return this->m_value; }
bool     THeight::Set (const uint32_t _value) { const bool b_changed = this->Get() != _value; if (b_changed) this->m_value = _value; return b_changed; }

bool  THeight::Is_valid (void) const { return (THeight::Min() >= this->Get() && this->Get() <= THeight::Max()); }

uint32_t THeight::Max (void) { return 0x0032; }
uint32_t THeight::Min (void) { return 0x001e; }

uint32_t THeight::Total (void) const {
	const CLayout& layout = this->m_ctrl.Layout(); layout;
//	const CRibbon& ribbon = layout.Ribbon();

	uint32_t u_total = this->Get();
	/*
	if (ribbon.Sides().IsHorz()) {
		if (false){}
		else if (ribbon.Tabs().Caps().Is_horz()) { u_total = this->Get(); }
		else if (ribbon.Tabs().Caps().Is_vert()) { u_total = ribbon.Tabs().Size().Width().Get(); }
	}
	else {
		if (false){}
		else if (ribbon.Tabs().Caps().Is_horz()) { u_total = this->m_ctrl.Tabs().Count() * this->Get(); }
		else if (ribbon.Tabs().Caps().Is_vert()) { u_total = this->m_ctrl.Tabs().Count() * ribbon.Tabs().Size().Width().Get(); }
	}*/
	return u_total;
}

#pragma endregion
#pragma region cls::CTabs::CSize::CWidth{}

using TWidth = ex_ui::controls::sfx::tabbed::layout::CTabs::CSize::CWidth;

TWidth::CWidth (TabCtrl& _ctrl) : m_ctrl(_ctrl), m_value(0) {}

uint32_t TWidth::Get (void) const { return this->m_value; }
bool     TWidth::Set (const uint32_t _value) { const bool b_changed = this->Get() != _value; if (b_changed) this->m_value = _value; return b_changed; }

bool TWidth::Is_valid (void) const { return (THeight::Min() >= this->Get() && this->Get() <= THeight::Max()); }

uint32_t TWidth::Max (void) { return 0x00c8; }
uint32_t TWidth::Min (void) { return 0x0064; }

uint32_t TWidth::Total (void) const { return this->m_ctrl.Tabs().Count() * this->Get(); }

#pragma endregion
#pragma region cls::CLayout{}

CLayout:: CLayout (CControl& _ctrl) : m_ctrl(_ctrl), m_rect{0}, m_ribbon(_ctrl), m_padding(5,5,-5,-5) {
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

	n_result = this->Ribbon().Update(rc_area);   // (1) sets the rectangle for tabs itself, aka ribbon of the tabs;
	this->m_ctrl.Borders() << rc_area;           // (2) updates border position(s);
	this->Ribbon().Tabs().Active().Set(rc_area); // (3) updates active tab borders;
	this->Ribbon().Tabs().Update();              // (4) updates each tab page internal window size and position;

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
CRibbon&  CLayout::Ribbon (void) const  { return this->m_ribbon; }
CRibbon&  CLayout::Ribbon (void)        { return this->m_ribbon; }

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