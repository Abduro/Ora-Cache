#ifndef _SFXTABSLAY_H_INCLUDED
#define _SFXTABSLAY_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-Aug-2020 at 7:31:11p, UTC+7, Novosibirsk, Thursday;
	This is Ebo Pack shared tabbed control layout interface declaration file;
*/
#include "sfx.tabs.inc.h"

namespace ex_ui { namespace controls { namespace sfx { namespace tabbed { class CControl;

	using CSides = ex_ui::controls::layout::CMargins_of_rect::CSides;
	using TSide  = ex_ui::controls::layout::CMargins_of_rect::CSides::_part;

	using CPadding = ex_ui::controls::layout::CPadding_of_rect;

	class CLayout;

namespace layout {

	// https://learn.microsoft.com/en-us/previous-versions/visualstudio/aa228484(v=vs.60)?redirectedfrom=MSDN&source=docs ;

	using namespace ex_ui::controls::sfx::tabbed;
	using CLayout = ex_ui::controls::sfx::tabbed::CLayout;

	/*         (a) (b)       (ab) - the first border; (bc) - the second one; (cd),(de),(ef),(fg),(gh)(ha) - totally 8 borders;
		        +---+         taking into account the horizontal and vertical alignment of the tabs, such as:
		     (h)|   |(c)      for top-bottom sides, if the tabs' horizontal alignment - to left, such borders as (ha) and (fg) will exclude or hide (gh) border;
		 (g)+---+   +---+ (d) because, they will form the one vertical line, but for this time it is not so important, no optimization is considered to be made yet;
		    |           |
		 (f)+-----------+ (e)
	*/
#if (0)
	typedef ::std::map<uint32_t, CBorder> TRawBorders; // it is not probably optimal container for borders, but it's selected for the draft version of this control;
#else
	using ex_ui::controls::borders::TRawBorders;
#endif
	/*
		tabs layout must be the following:
		(a) at top and bottom sides: from left to right (by default); otherwise, in accordance with alignment of the tabs sequence (not implemented yet);
		(b) at left and right sides: for the left side tabs reside from bottom to top; for the right side from the top to bottom; (by default)
		    otherwise in accordance with tab sequence alignement value (not implemented yet);
	*/
	class CActiveTab {
	public:
		enum _ndx : uint32_t {
			e_ab = 0x0, e_bc = 0x1, e_cd = 0x2, e_de = 0x3, e_ef = 0x4, e_fg = 0x5, e_gh = 0x6, e_ha = 0x7,
		};
	public:
		 CActiveTab (CControl&); CActiveTab (void) = delete; CActiveTab (const CActiveTab&) = delete; CActiveTab (CActiveTab&&) = delete;
		~CActiveTab (void) ;

	public:
		const
		CBorder&  Get (const _ndx) const;  // if the index is out of acceptable range, the reference to fake object is returned;
		CBorder&  Get (const _ndx) ;       // if the index is out of acceptable range, the reference to fake object is returned;
		const
		TRawBorders& Raw (void) const;
		err_code  Set (const t_rect&);     // sets border positions of the active tab;

	private:
		CActiveTab&  operator = (const CActiveTab&) = delete;
		CActiveTab&  operator = (CActiveTab&&) = delete;

	private:
		CControl&   m_ctrl;
		TRawBorders m_borders;
	};

	using Selected = CActiveTab;

	// for this version of the implementation, all tabs have fixed value width and height, the text of tab is trimmed by '...' if necessary;
	class CTabs { friend class ex_ui::controls::sfx::tabbed::CLayout;
	public :
		 CTabs (CControl&); CTabs (void) = delete; CTabs (const CTabs&) = delete; CTabs (CTabs&&) = delete;
		~CTabs (void);

	public:
		const
		Selected& Active (void) const;
		Selected& Active (void) ;

		const
		TAlign&   Align (void) const;     // returns a reference to tabs' alignment that may be set differently to vertical and horizontal positions; (ro);
		TAlign&   Align (void) ;          // returns a reference to tabs' alignment that may be set differently to vertical and horizontal positions; (rw);

		uint32_t  Gap (void) const;
		bool      Gap (const uint32_t _u_value);

		uint32_t  Height (void) const;
		bool      Height (const uint32_t);// sets a height of all tabs; returns 'true' in case if the height value is changed;
		const
		t_rect&   Ribbon (void) const;               // gets a rectangle of tabs area; in other words, it is tabs' ribbon or bookmarks' band;
		err_code  Ribbon (const t_rect& _rc_client); // calculates a rectangle for tabs for available client area rectangle;

		TSide     LocatedOn(void) const ; // gets a side where all tabs reside;
		bool      LocatedOn(const TSide); // sets the side of the control on which the tabs will be located;
		const
		CSides&   Sides (void) const;     // gets a reference to all sides collection; (ro);
		CSides&   Sides (void) ;          // gets a reference to all sides collection; (rw);
		
		// ToDo: t_size must be replaced to geometry::_2D::base::CSize_U;
		const
		t_size&   Size  (void) const;     // gets a size of each tab; TODO: needs to be reviewed;

		void      Update(void) ;          // updates pages' window position especially;

		uint32_t& Width (void) ;          // sets a width of each tab;
		bool      Width (const uint32_t&);

	private:
		CTabs&  operator = (const CTabs&) = delete;
		CTabs&  operator = (CTabs&&) =  delete;

	private:
		CSides     m_sides ;   // sides of tab control where tabs can be located; the top side is default;
		t_size     m_size  ;   // a size of each tab;
		t_rect     m_ribbon;   // entire area of tabs, including free space of the background that is inline with tabs;
		uint32_t   m_gap   ;   // a gap between tabs;
		CControl&  m_ctrl  ;
		Selected   m_active;
		TAlign     m_align ;
	};
}
	class CLayout {
	using  CTabs = layout::CTabs;
	friend class  CControl;
	private:
		 CLayout (CControl&); CLayout (void) = delete; CLayout (const CLayout&) = delete; CLayout (CLayout&&) = delete;
		~CLayout (void);

	public:
		TError&   Error  (void) const;
		const
		CPadding& Padding(void) const;
		CPadding& Padding(void) ;
		const
		t_rect&   Rect (void) const;                 // returns the cashed rectangle of the tabbed control;

		err_code  Update (void) ;                    // updates the internal components' layout by using this control window client area;
		err_code  Update (const t_rect& _rc_area);   // updates tabbed control window *position* into an area provided;
		const
		CTabs&    Tabs (void) const;
		CTabs&    Tabs (void) ;

	public:
		CLayout&  operator <<(const t_rect& _rc_area);        // updates tabbed control window position in accordance with area  ;
		t_rect    operator = (const t_rect& _rc_area) const;  // returns calculated rectangle of tabbed control for area provided;

	private:
		CLayout&  operator = (const CLayout&) = delete;
		CLayout&  operator = (CLayout&&) = delete;

	private:
		mutable
		CError    m_error ;
		CControl& m_ctrl  ;
		CPadding  m_padding;
		CTabs     m_tabs  ;
		t_rect    m_rect  ;  // cached client area rectangle;
	};

}}}}
#endif/*_SFXTABSLAY_H_ED51B0CD_0B83_4607_923A_CC1046DCD60A_INCLUDED*/