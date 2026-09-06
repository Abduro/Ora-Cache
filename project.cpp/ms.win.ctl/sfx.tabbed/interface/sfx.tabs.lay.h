#ifndef _SFXTABSLAY_H_INCLUDED
#define _SFXTABSLAY_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 20-Aug-2020 at 7:31:11p, UTC+7, Novosibirsk, Thursday;
	This is Ebo Pack shared tabbed control layout interface declaration file;
*/
#include "sfx.tabs.inc.h"

namespace ex_ui { namespace controls { namespace sfx { namespace tabbed { class CControl; using TabCtrl = CControl;

	using CSides = ex_ui::controls::layout::CMargins_of_rect::CSides;
	using TSide  = ex_ui::controls::layout::CMargins_of_rect::CSides::_part;

	using CPadding = ex_ui::controls::layout::CPadding_of_rect;

	class CLayout;

namespace layout {

	// https://en.wikipedia.org/wiki/Tab_(interface) ;
	// https://www.w3.org/WAI/ARIA/apg/patterns/tabs/ ;
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
		err_code  Set (const rect_t&);     // sets border positions of the active tab;

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
	public:
		/* query to Google AI: abbreviation for caption word in programming?
		In programming, the most common abbreviations for the word 'caption' are 'cap' and 'lbl' (short for 'label').
		(1) 'cap' – Used when you need a direct, literal abbreviation of the word 'caption' itself (e.g., capText, img_cap).
		(2) 'lbl' (Label) – Used most frequently in frontend and UI development (like C#, JavaFX, or HTML).
		    Developers typically use a visual UI component called a "Label" to display a caption
		*/
		class CCaps {
		public:
			enum e_orient : uint32_t {
			e_horz = 0, // a caption text of each tab is oriented horizontally; default for top and bottom sides of the ribbon being attached to;
			e_vert = 1, // a caption text of each tab is oriented vertically; default for left and right sides of the ribbon being attached to;
			};
			CCaps (void); CCaps (const CCaps&) = delete; CCaps (CCaps&&) = delete; ~CCaps (void) = default;

			e_orient Get_orient (void) const;
			bool     Set_orient (const e_orient);

			bool     Is_horz (void) const;
			bool     Is_vert (void) const;

		private:
			CCaps& operator = (const CCaps&) = delete; CCaps& operator = (CCaps&&) = delete;
			e_orient m_orient;
		};

		class CSize : public ::geometry::_2D::base::CSize_U { typedef ::geometry::_2D::base::CSize_U TBase;
		public:
			class CHeight {
			public:
				CHeight (void); CHeight (const CHeight&) = delete; CHeight (CHeight&&) = delete; ~CHeight (void) = default;
			private:
				CHeight& operator = (const CHeight&) = delete; CHeight& operator = (CHeight&&) = delete;
			};
			class CWidth {
			public:
				CWidth (void); CWidth (const CWidth&) = delete; CWidth (CWidth&&) = delete; ~CWidth (void) = default;
			private:
				CWidth& operator = (const CWidth&) = delete; CWidth& operator = (CWidth&&) = delete;
			};
			CSize (void); CSize (const CSize&) = delete; CSize (CSize&&) = delete; ~CSize (void) = default;

			const
			CHeight& Hight (void) const;
			CHeight& Hight (void) ;
			const
			CWidth&  Width (void) const;
			CWidth&  Width (void) ;

		private:
			CSize& operator = (const CSize&) = delete; CSize& operator = (CSize&&) = delete;
			CHeight m_height;
			CWidth  m_width ;
		};

		 CTabs (CControl&); CTabs (void) = delete; CTabs (const CTabs&) = delete; CTabs (CTabs&&) = delete;
		~CTabs (void);
		const
		Selected& Active (void) const;
		Selected& Active (void) ;

		const
		TAlign&   Align (void) const;      // returns a reference to tabs' alignment that may be set differently to vertical and horizontal positions; (ro);
		TAlign&   Align (void) ;           // returns a reference to tabs' alignment that may be set differently to vertical and horizontal positions; (rw);
		const
		CCaps&    Caps (void) const;       // returns a reference to all tabs' captions' settings, especially for tabs' caption orientation either vertical or horizontal; (ro)
		CCaps&    Caps (void) ;            // returns a reference to all tabs' captions' settings, especially for tabs' caption orientation either vertical or horizontal; (rw)

		uint32_t  Gap (void) const;
		bool      Gap (const uint32_t _u_value);

		uint32_t  Height (void) const;
		bool      Height (const uint32_t); // sets a height of all tabs; returns 'true' in case if the height value is changed;
		
		// ToDo: t_size must be replaced to geometry::_2D::base::CSize_U;
		const
		t_size&   Size  (void) const;      // gets a size of each tab; TODO: needs to be reviewed;

		uint32_t  TotalHeight(void) const; // returns total height of all tabs;
		uint32_t  TotalWidth (void) const; // returns total width of all tabs;

		void      Update(void) ;           // updates pages' window position especially;

		uint32_t& Width (void) ;           // sets a width of each tab;
		bool      Width (const uint32_t&); // sets a width for all tabs the same;

	private:
		CTabs&  operator = (const CTabs&) = delete;
		CTabs&  operator = (CTabs&&) =  delete;

	private:
		CControl&  m_ctrl  ;
		CCaps      m_caps  ;
		t_size     m_size  ;   // a size of each tab;
		uint32_t   m_gap   ;   // a gap between tabs;
		Selected   m_active;
		TAlign     m_align ;
	};

	class CRibbon {
	public:
		CRibbon (TabCtrl&);
		CRibbon (void) = delete; CRibbon (const CRibbon&) = delete; CRibbon (CRibbon&&) = delete; ~CRibbon (void) = default;

		TSide     LocatedOn(void) const ;   // gets a side where all tabs reside;
		bool      LocatedOn(const TSide);   // sets the side of the control on which the tabs will be located;
		const
		rect_t&   Rect (void) const;
		const
		CSides&   Sides (void) const;       // gets a reference to all sides collection; (ro);
		CSides&   Sides (void) ;            // gets a reference to all sides collection; (rw);

		err_code  Update(const rect_t& _rc_area); // calculates a rectangle for tabs for available client area rectangle;
		const
		CTabs&    Tabs (void) const;
		CTabs&    Tabs (void) ;

		CRibbon&  operator <<(const TSide); // sets the control side which this ribbon is glued to;

	private:
		CRibbon&  operator = (const CRibbon&) = delete; CRibbon& operator = (CRibbon&&) = delete;
		CSides    m_sides;   // sides of ribbon location; the top side is default;
		rect_t    m_rect ;   // the rectangle of the ribbon;
		CTabs     m_tabs ;
		TabCtrl&  m_ctrl ;
	};
}
	class CLayout {
	friend class  CControl;
	private:
		 CLayout (CControl&); CLayout (void) = delete; CLayout (const CLayout&) = delete; CLayout (CLayout&&) = delete;
		~CLayout (void);

	public:
		using CTabs = layout::CTabs;
		using CRibbon = layout::CRibbon;

		TError&   Error  (void) const;
		const
		CPadding& Padding(void) const;
		CPadding& Padding(void) ;
		const
		rect_t&   Rect (void) const;                 // returns the cashed rectangle of the tabbed control;
		const
		CRibbon&  Ribbon (void) const;
		CRibbon&  Ribbon (void) ;

		err_code  Update (void) ;                    // updates the internal components' layout by using this control window client area;
		err_code  Update (const rect_t& _rc_area);   // updates tabbed control window *position* into an area provided;

	public:
		CLayout&  operator <<(const rect_t& _rc_area);        // updates tabbed control window position in accordance with area  ;
		rect_t    operator = (const rect_t& _rc_area) const;  // returns calculated rectangle of tabbed control for area provided;

	private:
		CLayout&  operator = (const CLayout&) = delete;
		CLayout&  operator = (CLayout&&) = delete;

	private:
		mutable
		CError    m_error ;
		CControl& m_ctrl  ;
		CPadding  m_padding;
		rect_t    m_rect  ;  // cached client area rectangle;
		CRibbon   m_ribbon;
	};

}}}}
#endif/*_SFXTABSLAY_H_ED51B0CD_0B83_4607_923A_CC1046DCD60A_INCLUDED*/