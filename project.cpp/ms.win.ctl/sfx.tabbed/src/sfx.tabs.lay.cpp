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
	const TAlign& align = this->m_ctrl.Layout().Tabs().Align();
#endif
	switch (this->m_ctrl.Layout().Tabs().LocatedOn()) {
	case TSide::e_bottom : {
		const THorzAlign& h_align = align.Horz();
		/*THorzAlign::eLeft; THorzAlign::eCenter; THorzAlign::eRight;
		  (e)+-------+(f)     (e)+-------+(f)      (e)+-------+(f)
		     |(c) (h)|           |(c) (h)|            |(c) (h)|
		  (d)+   +---+(g)     (d)+-+   +-+(g)      (d)+---+   +(g)
		     |   |                 |   |                  |   |
		  (b)+---+(a)           (b)+---+(a)            (b)+---+(a)

		  in case of left alignment the 'cd' border may have zero length if the active tab index equals to '0';
		  in case of right alignment the 'gh' border may have zero length if the active tab index equals to the count of the tabs - 1;
		*/
		if (THorzAlign::eLeft == h_align.Value()) { // the start X-coord value == rect_.left and is increased to the right side;

			CPoint a_(rect_.left + (n_active + 1) * n_width, rect_.bottom); // the X-coord of the 'a_' point is greater than 'b_' has;
			CPoint b_(a_.X() - n_width, a_.Y());
			
			CBorder& ab_ = this->Get(_ndx::e_ab); ab_.Begin() = a_; ab_.End() = b_;

			CPoint c_(b_.X(), a_.Y() - n_height);
			CBorder& bc_ = this->Get(_ndx::e_bc); bc_.Begin() = b_; bc_.End() = c_;

			CPoint d_(b_.X(), c_.Y()); // X-coord of the 'd_' point equals always to the *left* side of the rectangle;
			CBorder& cd_ = this->Get(_ndx::e_cd); cd_.Begin() = c_; cd_.End() = d_; // sets '0' length for this border in case if active tab index is zero;

			CPoint e_(d_.X(), rect_.top); // Y-coord of the 'e_' point equals always to the *top* value of the rectangle;
			CBorder& de_ = this->Get(_ndx::e_de); de_.Begin() = d_; de_.End() = e_;

			CPoint f_(rect_.right, e_.Y()); // X-coord of the 'f_' point equals always to the *right* value of the rectangle;
			CBorder& ef_ = this->Get(_ndx::e_ef); ef_.Begin() = e_; ef_.End() = f_;

			CPoint g_(f_.X(), d_.Y());
			CBorder& fg_ = this->Get(_ndx::e_fg); fg_.Begin() = f_; fg_.End() = g_;

			CPoint h_(a_.X(), g_.Y());
			CBorder& gh_ = this->Get(_ndx::e_gh); gh_.Begin() = g_; gh_.End() = h_;

			CBorder& ha_ = this->Get(_ndx::e_ha); ha_.Begin() = h_; ha_.End() = a_;
		}
		else { // the center alignment is ignored for this version of the implementation;
			CPoint a_(rect_.right - (n_active * n_width), rect_.bottom);
			CPoint b_(a_.X() - n_width, a_.Y());
			CBorder& ab_ = this->Get(_ndx::e_ab); ab_.Begin() = a_; ab_.End() = b_;

			CPoint c_(b_.X(), b_.Y() - n_height);
			CBorder& bc_ = this->Get(_ndx::e_bc); bc_.Begin() = b_; bc_.End() = c_;

			CPoint d_(rect_.left, c_.Y()); // X-coord value always equals to the *left* side of the rectangle;
			CBorder& cd_ = this->Get(_ndx::e_cd); cd_.Begin() = c_; cd_.End() = d_;

			CPoint e_(d_.X(), rect_.top);  // Y-coord value always equals to the *top* side of the rectangle;
			CBorder& de_ = this->Get(_ndx::e_de); de_.Begin() = d_; de_.End() = e_;

			CPoint f_(rect_.right, e_.Y()); // X-coord value of the 'f_' point has always the *right* side value of the rectangle;
			CBorder& ef_ = this->Get(_ndx::e_ef); ef_.Begin() = e_; ef_.End() = f_;

			CPoint g_(f_.X(), d_.Y());
			CBorder& fg_ = this->Get(_ndx::e_fg); fg_.Begin() = f_; fg_.End() = g_;

			CPoint h_(a_.X(), g_.Y());
			CBorder& gh_ = this->Get(_ndx::e_gh); gh_.Begin() = g_; gh_.End() = h_;

			CBorder& ha_ = this->Get(_ndx::e_ha); ha_.Begin() = h_; ha_.End() = a_;
		}
	} break;
	case TSide::e_left : {
		const TVertAlign& v_align = align.Vert();
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
		if (TVertAlign::eBottom == v_align.Value()) {

			CPoint a_(rect_.left, rect_.bottom - (n_active * n_width));
			CPoint b_(a_.X(), a_.Y() - n_width);
		
			CBorder& ab_ = this->Get(_ndx::e_ab); ab_.Begin() = a_; ab_.End() = b_;

			CPoint c_(b_.X() + n_height, b_.Y());
			CBorder& bc_ = this->Get(_ndx::e_bc); bc_.Begin() = b_; bc_.End() = c_;

			CPoint d_(c_.X(), rect_.top); // Y-coord of 'd' point equals always to the *top* value of the rectangle; 
			CBorder& cd_ = this->Get(_ndx::e_cd); cd_.Begin() = c_; cd_.End() = d_;

			CPoint e_(rect_.right,d_.Y()); // X-coord of 'e' point always equals to the *right* value of the rectnagle;
			CBorder& de_ = this->Get(_ndx::e_de); de_.Begin() = d_; de_.End() = e_;

			CPoint f_(e_.X(), rect_.bottom); // Y-coord of 'f' point equals always to the *bottom* value of the rectangle;
			CBorder& ef_ = this->Get(_ndx::e_ef); ef_.Begin() = e_; ef_.End() = f_;

			CPoint g_(c_.X(), f_.Y());
			CBorder& fg_ = this->Get(_ndx::e_fg); fg_.Begin() = f_; fg_.End() = g_;

			CPoint h_(c_.X(), a_.Y()); // possibly a.Y() == f.Y() when active tab index equals to '0';
			CBorder& gh_ = this->Get(_ndx::e_gh); gh_.Begin() = g_; gh_.End() = h_; // may have '0' length in case of '0' index of active tab;

			CBorder& ha_ = this->Get(_ndx::e_ha); ha_.Begin() = h_; ha_.End() = a_;
		}
		else { // the middle alignment is not implemented for this version of the software;
			CPoint a_(rect_.left, rect_.top + ((n_active + 1) * n_width));
			CPoint b_(a_.X(), a_.Y() - n_width);
		
			CBorder& ab_ = this->Get(_ndx::e_ab); ab_.Begin() = a_; ab_.End() = b_;

			CPoint c_(b_.X() + n_height, b_.Y());
			CBorder& bc_ = this->Get(_ndx::e_bc); bc_.Begin() = b_; bc_.End() = c_;

			CPoint d_(c_.X(), rect_.top); // Y-coord of 'd' point equals always to the *top* value of the rectangle; 
			CBorder& cd_ = this->Get(_ndx::e_cd); cd_.Begin() = c_; cd_.End() = d_; // may have '0' length if active tab index equals to tabs.count - 1;

			CPoint e_(rect_.right,d_.Y()); // X-coord of 'e' point always equals to the *right* value of the rectnagle;
			CBorder& de_ = this->Get(_ndx::e_de); de_.Begin() = d_; de_.End() = e_;

			CPoint f_(e_.X(), rect_.bottom); // Y-coord of 'f' point equals always to the *bottom* value of the rectangle;
			CBorder& ef_ = this->Get(_ndx::e_ef); ef_.Begin() = e_; ef_.End() = f_;

			CPoint g_(c_.X(), f_.Y());
			CBorder& fg_ = this->Get(_ndx::e_fg); fg_.Begin() = f_; fg_.End() = g_;

			CPoint h_(c_.X(), a_.Y());
			CBorder& gh_ = this->Get(_ndx::e_gh); gh_.Begin() = g_; gh_.End() = h_;

			CBorder& ha_ = this->Get(_ndx::e_ha); ha_.Begin() = h_; ha_.End() = a_;
		}
	} break;
	case TSide::e_right : {
		const TVertAlign& v_align = align.Vert();
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
		if (TVertAlign::eBottom == v_align.Value()) {

			CPoint a_(rect_.right, rect_.bottom - ((n_active + 1) * n_width));
			CPoint b_(a_.X(), a_.Y() + n_width);
		
			CBorder& ab_ = this->Get(_ndx::e_ab); ab_.Begin() = a_; ab_.End() = b_;

			CPoint c_(b_.X() - n_height, b_.Y());
			CBorder& bc_ = this->Get(_ndx::e_bc); bc_.Begin() = b_; bc_.End() = c_;

			CPoint d_(c_.X(), rect_.bottom); // Y-coord value of the 'd' point equals always to the *bottom* value of the rectangle;
			CBorder& cd_ = this->Get(_ndx::e_cd); cd_.Begin() = c_; cd_.End() = d_; // may have '0' length if active tab index equals to 'tabs.count() - 1';

			CPoint e_(rect_.left, d_.Y());  // X-coord value of the 'e' point equals always to the *left* value of the rectangle;
			CBorder& de_ = this->Get(_ndx::e_de); de_.Begin() = d_; de_.End() = e_;

			CPoint f_(e_.X(), rect_.top); // Y-coord value of the 'f' point equals always to the *top* value of the rectangle;
			CBorder& ef_ = this->Get(_ndx::e_ef); ef_.Begin() = e_; ef_.End() = f_;

			CPoint g_(c_.X(), f_.Y());
			CBorder& fg_ = this->Get(_ndx::e_fg); fg_.Begin() = f_; fg_.End() = g_;

			CPoint h_(g_.X(), a_.Y());
			CBorder& gh_ = this->Get(_ndx::e_gh); gh_.Begin() = g_; gh_.End() = h_;

			CBorder& ha_ = this->Get(_ndx::e_ha); ha_.Begin() = h_; ha_.End() = a_;
		}
		else { // the middle vertical alignment is ignored by this version of the user control implementation;
			CPoint a_(rect_.right, rect_.top + (n_active * n_width)); // X-coord value of the 'a' point equals always to the *right* side of the rectangle;
			CPoint b_(a_.X(), a_.Y() + n_width);
		
			CBorder& ab_ = this->Get(_ndx::e_ab); ab_.Begin() = a_; ab_.End() = b_;

			CPoint c_(b_.X() - n_height, b_.Y());
			CBorder& bc_ = this->Get(_ndx::e_bc); bc_.Begin() = b_; bc_.End() = c_;

			CPoint d_(c_.X(), rect_.bottom); // Y-coord value of the 'd' point equals always to the *bottom* value of the rectangle;
			CBorder& cd_ = this->Get(_ndx::e_cd); cd_.Begin() = c_; cd_.End() = d_;

			CPoint e_(rect_.left, d_.Y());  // X-coord value of the 'e' point equals always to the *left* value of the rectangle;
			CBorder& de_ = this->Get(_ndx::e_de); de_.Begin() = d_; de_.End() = e_;

			CPoint f_(e_.X(), rect_.top); // Y-coord value of the 'f' point equals always to the *top* value of the rectangle;
			CBorder& ef_ = this->Get(_ndx::e_ef); ef_.Begin() = e_; ef_.End() = f_;

			CPoint g_(c_.X(), f_.Y());
			CBorder& fg_ = this->Get(_ndx::e_fg); fg_.Begin() = f_; fg_.End() = g_;

			CPoint h_(g_.X(), a_.Y()); // possibly a.Y() == g.Y() if the active tab index equals to '0';
			CBorder& gh_ = this->Get(_ndx::e_gh); gh_.Begin() = g_; gh_.End() = h_;  // may have '0' length if active tab index equals to '0';

			CBorder& ha_ = this->Get(_ndx::e_ha); ha_.Begin() = h_; ha_.End() = a_;
		}
	} break;
	case TSide::e_top : {
		const THorzAlign& h_align = align.Horz();
		/*THorzAlign::eLeft; THorzAlign::eCenter; THorzAlign::eRight;
		  (a)+---+(b)            (a)+---+(b)           (a)+---+(b)  
		     |   |(c)               |   |                 |   |     
		  (g)+(h)+---+(d)      (g)+-+   +-+(d)     (g)+---+(c)+(d)
		     |       |            |(h) (c)|           |  (h)  |   
		  (f)+-------+(e)      (f)+-------+(e)     (f)+-------+(e)

		  in case of the left alighment the 'gh' line may have '0' length if the active tab index equals to '0';
		  in case of the right alignment the 'cd' line may have '0' length if the active tab index equals to 'tabs.count() - 1';
		*/
		if (THorzAlign::eLeft == h_align.Value()) {

			CPoint a_(rect_.left + n_active * n_width, rect_.top); // Y-coord of the 'a' point equals always to the *top* rectangle side;
			CPoint b_(a_.X() + n_width, a_.Y());
		
			CBorder& ab_ = this->Get(_ndx::e_ab); ab_.Begin() = a_; ab_.End() = b_;

			CPoint c_(b_.X(), b_.Y() + n_height);
			CBorder& bc_ = this->Get(_ndx::e_bc); bc_.Begin() = b_; bc_.End() = c_;

			CPoint d_(rect_.right, c_.Y()); // X-coord of the 'd' point equals always to the *right* side value of the rectangle;
			CBorder& cd_ = this->Get(_ndx::e_cd); cd_.Begin() = c_; cd_.End() = d_;

			CPoint e_(d_.X(), rect_.bottom); // Y-coord of the 'e' point equals always to the *bottom* side value of the rectangle;
			CBorder& de_ = this->Get(_ndx::e_de); de_.Begin() = d_; de_.End() = e_;

			CPoint f_(rect_.left, e_.Y()); // X-coord of the 'f' point equals always to the *left* side value of the rectangle;
			CBorder& ef_ = this->Get(_ndx::e_ef); ef_.Begin() = e_; ef_.End() = f_;

			CPoint g_(f_.X(), d_.Y());
			CBorder& fg_ = this->Get(_ndx::e_fg); fg_.Begin() = f_; fg_.End() = g_;

			CPoint h_(a_.X(), g_.Y()); // possible the 'h' point may coincident with the 'g' point if the active tab index equals to '0'; 
			CBorder& gh_ = this->Get(_ndx::e_gh); gh_.Begin() = g_; gh_.End() = h_; // this border may have '0' length;

			CBorder& ha_ = this->Get(_ndx::e_ha); ha_.Begin() = h_; ha_.End() = a_;
		}
		else { // the 'center' alignment is ignored by this version of the user control implementation;
			CPoint a_(rect_.right - ((n_active + 1) * n_width), rect_.top); // Y-coord of the 'a' point equals always to the *top* side of the rectangle;
			CPoint b_(a_.X() + n_width, a_.Y());
		
			CBorder& ab_ = this->Get(_ndx::e_ab); ab_.Begin() = a_; ab_.End() = b_;

			CPoint c_(b_.X(), b_.Y() + n_height);
			CBorder& bc_ = this->Get(_ndx::e_bc); bc_.Begin() = b_; bc_.End() = c_;

			CPoint d_(rect_.right, c_.Y()); // X-coord of the 'd' point equals always to the *right* side value of the rectangle;
			CBorder& cd_ = this->Get(_ndx::e_cd); cd_.Begin() = c_; cd_.End() = d_; // this border may have '0' length if the active tab index equals to 'tabs.count - 1';

			CPoint e_(d_.X(), rect_.bottom); // Y-coord of the 'e' point equals always to the *bottom* side value of the rectangle;
			CBorder& de_ = this->Get(_ndx::e_de); de_.Begin() = d_; de_.End() = e_;

			CPoint f_(rect_.left, e_.Y()); // X-coord of the 'f' point equals always to the *left* side value of the rectangle;
			CBorder& ef_ = this->Get(_ndx::e_ef); ef_.Begin() = e_; ef_.End() = f_;

			CPoint g_(f_.X(), d_.Y());
			CBorder& fg_ = this->Get(_ndx::e_fg); fg_.Begin() = f_; fg_.End() = g_;

			CPoint h_(a_.X(), d_.Y());
			CBorder& gh_ = this->Get(_ndx::e_gh); gh_.Begin() = g_; gh_.End() = h_;

			CBorder& ha_ = this->Get(_ndx::e_ha); ha_.Begin() = h_; ha_.End() = a_;
		}
	} break;
	default:
		n_result = (err_code) TErrCodes::eExecute::eParameter;
	}

	return n_result;
}

/////////////////////////////////////////////////////////////////////////////
namespace ex_ui { namespace controls { namespace sfx { namespace tabbed { namespace layout {

CTabs:: CTabs (CControl& _ctrl) : m_ribbon{0}, m_size{0}, m_gap(0), m_ctrl(_ctrl), m_active(_ctrl) {
	this->m_size.cy = 31;
	this->m_size.cx = this->m_size.cy * 5; this->m_gap = this->m_size.cy / 2;
}
CTabs::~CTabs(void) {}

/////////////////////////////////////////////////////////////////////////////
const
CActiveTab& CTabs::Active (void) const { return this->m_active; }
CActiveTab& CTabs::Active (void)       { return this->m_active; }

const
TAlign&   CTabs::Align (void) const { return this->m_align; }
TAlign&   CTabs::Align (void)       { return this->m_align; }

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
t_rect&   CTabs::Ribbon (void) const { return m_ribbon ; }
err_code  CTabs::Ribbon (const t_rect& _rc_area) {

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
			_long n_left = this->m_ribbon.left;
			for (int16_t i_ = 0; i_ < this->m_ctrl.Tabs().Count(); i_++) {
				this->m_ctrl.Tabs().Tab(i_).Strip() = this->m_ribbon;
				this->m_ctrl.Tabs().Tab(i_).Strip().left  = n_left; n_left += this->Width();
				this->m_ctrl.Tabs().Tab(i_).Strip().right = n_left;
			}
		}
		else { // the 'center' alignment is ignored by this version of the user control implementation;
			_long n_right = this->m_ribbon.right;
			for (int16_t i_ = this->m_ctrl.Tabs().Count() - 1; -1 < i_; i_--) {
				this->m_ctrl.Tabs().Tab(i_).Strip() = this->m_ribbon;
				this->m_ctrl.Tabs().Tab(i_).Strip().right  = n_right; n_right -= this->Width();
				this->m_ctrl.Tabs().Tab(i_).Strip().left   = n_right;
			}
		}
	}

	if (this->m_sides.IsVert()) { // tabs reside in vertical line;
		if (TVertAlign::eBottom == this->Align().Vert().Value()) {
			_long n_bottom = this->m_ribbon.bottom;
			for (int16_t i_ = 0; i_ < this->m_ctrl.Tabs().Count(); i_++) {
				this->m_ctrl.Tabs().Tab(i_).Strip() = this->m_ribbon;
				this->m_ctrl.Tabs().Tab(i_).Strip().bottom = n_bottom; n_bottom -= this->Width();
				this->m_ctrl.Tabs().Tab(i_).Strip().top = n_bottom;
			}
		}
		else { // the 'middle' alignment is ignored by this version of this user control implementation;
			_long n_top = this->m_ribbon.top;
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

void      CTabs::Update(void) {

	const t_rect& rc_area = this->m_ctrl.Layout().Rect(); // gets available rectangle to tabbed control;
	const t_rect& rc_ribbon = this->Ribbon(); // this rectangle is expected to be calculated properly in accordance with tabs' side;

	t_rect rc_page = rc_area;

	if (this->Sides().IsHorz()) {
		if (TVertAlign::eBottom == this->Align().Vert().Value()) {
			rc_page.bottom = rc_ribbon.top;
		}
		else {
			rc_page.top = rc_ribbon.bottom;
		}
	}
	else {
		if (THorzAlign::eLeft == this->Align().Horz().Value()) {
			rc_page.left = rc_ribbon.right;
		}
		else {
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

/////////////////////////////////////////////////////////////////////////////
}}}}}
/////////////////////////////////////////////////////////////////////////////

CLayout:: CLayout (CControl& _ctrl) : m_ctrl(_ctrl), m_rect{0}, m_tabs(_ctrl), m_padding(5,5,-5,-5) {
	m_error >> __CLASS__ << __METHOD__ << __s_ok;
}
CLayout::~CLayout (void) {}

/////////////////////////////////////////////////////////////////////////////

TError&   CLayout::Error  (void) const { return this->m_error ; }

const
CPadding& CLayout::Padding(void) const { return this->m_padding; }
CPadding& CLayout::Padding(void)       { return this->m_padding; }

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

	n_result = this->Tabs().Ribbon(rc_area); // (1) sets the rectangle for tabs itself, aka ribbon of the tabs;
	this->m_ctrl.Borders() << rc_area;       // (2) updates border position(s);
	this->m_tabs.Active().Set(rc_area);      // (3) updates active tab borders;
	this->m_tabs.Update();                   // (4) updates each tab page internal window size and position;

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