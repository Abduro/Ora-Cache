#ifndef _CTL_BASE_LYT_H_INCLUDED
#define _CTL_BASE_LYT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-May-2025 at 23:21:51.177, UTC+4, Batumi, Saturday;
	This is Ebo Pack user control base layout interface declaration file;
*/
#include "ctl.base.defs.h"

namespace ex_ui { namespace controls { namespace layout {

	using namespace ex_ui::controls;

	// https://www.abbreviations.com/abbreviation/layout ;
	// https://erik-engheim.medium.com/understanding-visual-layout-in-gui-design-2fa91792edef ;
	
	/*
		https://medium.com/@uiuxzee/ultimate-spacing-guide-for-ui-designers-342f4c61bd70 : (excerpt)
		Gaps, also known as whitespace or padding, create visual separation, making the interface easier to understand and navigate ; 
	*/

	class CGap {
	public:
		 CGap (const int16_t _n_id = 0, const int16_t _n_value = 0); CGap (const CGap&); CGap (CGap&&) = delete;
		~CGap (void) = default;

	public:
		int16_t   Id (void) const;
		bool      Id (const int16_t);    // returns 'true' in case of change;
#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
		int16_t   Value (void) const;
		bool      Value (const int16_t); // returns 'true' in case of change;

	public:
		CGap&  operator = (const CGap&);
		CGap&  operator = (CGap&&) = delete;

		CGap&  operator <<(const int16_t _n_id);
		CGap&  operator >>(const int16_t _n_value);

		operator int16_t (void) const; // for output a gap's value;

	protected:
		int16_t  m_id;     // a gap identifier can be either positive or negative;
		int16_t  m_value;  // a value can be also either positive or negative;
	};

	typedef ::std::map<int16_t, CGap> TRawGaps;

	class CGapSet {
	public:
		 CGapSet (void); CGapSet (const CGapSet&); CGapSet (CGapSet&&);
		~CGapSet (void);

	public:
		bool  Is_zero (void) const;       // returns true in case when all gaps have value 0 (zero) ;
		const
		TRawGaps& Raw (void) const;
		TRawGaps& Raw (void) ;

		err_code  Set (const TRawGaps&);  // sets/replaces this class raw gaps' map by the external/input one;

	public:
		CGapSet&  operator = (const CGapSet&);
		CGapSet&  operator = (CGapSet&&); // no swap operation is used yet;

		CGapSet&  operator <<(const TRawGaps&);

	protected:
		TRawGaps m_raw;
	};

	/*
		https://learn.microsoft.com/en-us/windows/apps/design/layout/alignment-margin-padding?source=docs : (excerpts)
		- Alignment makes your UI look neat, organized, and balanced and can also be used to establish visual hierarchy and relationships ;
		- Margin controls the amount of empty space around an element ;
		- Padding controls the amount of space between the inner border of an element and its child content or elements ;
	*/

	typedef CGap CMargin;
#if (0)
	class CMargin : public CGap { typedef CGap TBase;
	public:
		 CMargin (const int16_t _n_id = 0, const int16_t _n_value = 0); CMargin (const CMargin&); CMargin (CMargin&&) = delete;
		~CMargin (void) = default;

	public:
#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif

	public:
		CMargin&  operator = (const CMargin&);
		CMargin&  operator = (CMargin&&) = delete;

		CMargin&  operator <<(const int16_t _n_id);
		CMargin&  operator >>(const int16_t _n_value);
	};
#endif
#if (0)
	using TRawMargins = TRawGaps;

	class CMargins : public CGapSet { typedef CGapSet TBase;
	public:
		 CMargins (void); CMargins (const CMargins&); CMargins (CMargins&&);
		~CMargins (void);

	public:
		CMargins&  operator = (const CMargins&);
		CMargins&  operator = (CMargins&&);   // no swap operation is used yet;
		CMargins&  operator <<(const TRawMargins&);
	};
#endif

	class CGaps_of_rect : public CGapSet { typedef CGapSet TBase;
	public:
		class CSides { // it is not good to use class declaration inside of other one, because the 'container' class looks like a namespace very often;
		public:
			enum _part : int16_t {
				e_left = 0x0,  e_top = 0x1, e_right = 0x2, e_bottom = 0x3, e_default = e_top
			};
			static const int16_t n_count = 4;
		public:
			 CSides (void);
			 CSides (const _part _selected); CSides (CSides&&) = delete;
			 CSides (const CSides&);
			~CSides (void);

		public:
			bool  IsHorz (void) const;  // returns 'true' if selected part is either 'top' or 'bottom';
			bool  IsVert (void) const;  // returns 'true' if selected part is either 'left' or 'right';

			_part   Selected(void) const;
			_part&  Selected(void)      ;

		public:
			CSides& operator = (const CSides&);
			CSides& operator = (CSides&&) = delete;
			CSides& operator <<(const _part _selected) ;

		protected:
			_part  m_selected;

		public:
			typedef	_part  _e;
			static size_t     EnumToIndex(const CSides::_part);
			static CString    EnumToName (const CSides::_part);
			static CSides::_e IndexToEnum(const size_t);        // if given index is greater than e_bottom, default e_top is returned;
		};
	public:
		using e_sides = CSides::_part;
		
	public:
		 CGaps_of_rect (void); CGaps_of_rect (const CGaps_of_rect&); CGaps_of_rect (CGaps_of_rect&&) = delete;
		 CGaps_of_rect (const int16_t _left, const int16_t _top, const int16_t _right, const int16_t _bottom);
		~CGaps_of_rect (void);

	public:
		/* this::ApplyTo(): possibly the second parameter is required for indicating how to apply gaps for calculating margins or padding,
		   but it can be made by specifying appropriate sign for particular gap value, because gaps' values are always added to sides of input rectangle;
			for example >>
				for applying margins: gaps={left:-10;top:-10;right:+10;bottom:+10};
				for applying padding: gaps={left:+10;top:+10;right:-10;bottom:-10};
		   but at the same time such approach is not consistent with defininitions of what margins and padding mean:
		    (a) the margins mean extending an object area;
		    (b) the padding means decreasing an object area;
		   thus applying a negative values to either margins or padding sides is not coincident with meaning what those notations/definitions have;
		*/
		/*
			ToDo: ApplyTo() affects the target rectangle in difference ways in case of 'margins' and 'padding'; must be reviewed;
		*/
		bool  ApplyTo(t_rect& _rect) const; // returns true in case of change at least one side of the input rectangle;
		const
		CGap& Get (const e_sides) const;    // returns the reference to margin of input side; if not fount, the reference to fake object is returned;
		CGap& Get (const e_sides) ;         // returns the reference to margin of input side; if not fount, the reference to fake object is returned;
#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif
		bool  Set (const int16_t _all);     // sets input value to all margin sides; returns 'true' in case when at least one side margin is changed;
		bool  Set (const int16_t _left, const int16_t _top, const int16_t _right, const int16_t _bottom); // returns 'true' if at least one of the gaps is changed;

#pragma region __try_to_get_things_easy

		int16_t Bottom (void) const;
		bool    Bottom (const int16_t);

		int16_t Left (void) const;
		bool    Left (const int16_t);

		int16_t Right (void) const;
		bool    Right (const int16_t);

		int16_t Top (void) const;
		bool    Top (const int16_t);

#pragma endregion
	public:
		CGaps_of_rect&  operator = (const CGaps_of_rect&);
		CGaps_of_rect&  operator = (CGaps_of_rect&&) = delete;
	};

	typedef CGaps_of_rect CMargins_of_rect; using CMargins = CMargins_of_rect;
	typedef CGaps_of_rect CPadding_of_rect; using CPadding = CPadding_of_rect;

	class CImage {
	public:
		 CImage (void); CImage (const CImage&); CImage (CImage&&) = delete;
		~CImage (void) = default;

		const
		t_point&   Anchor  (void) const ; // this is the anchor point which is used to draw the image by image list;
		t_point&   Anchor  (void)       ;
		bool       Anchor  (const int32_t _n_x, const int32_t _n_y); // returns 'true' in case of change value of either 'x' or 'y';

		const bool Is_valid(void) const ; // returns 'true' if size exists, i.e. cx and cy are not equal to zero (0); otherwise, false;
		const bool IsSquare(void) const ; // returns 'true' if size is set (valid) and cx == cy;
		const
		CMargins&  Margins (void) const ;
		CMargins&  Margins (void)       ;
#if defined(_DEBUG)
		CString    Print (const e_print = e_print::e_all) const;
#endif
		const
		t_size&    Size  (void) const ;
		t_size&    Size  (void)       ;
		err_code   Size  (const HIMAGELIST);
		// https://www.quora.com/What-are-the-differences-between-whole-total-full-and-entire ;
		t_size     Total (void) const ; // gets entire size of the image area including image frame size and margins around it;

	public:
		CImage& operator = (const CImage&); CImage& operator = (CImage&&) = delete;
		CImage& operator <<(const CMargins&);
		CImage& operator <<(const t_point&);    // the point of the anchor;
		CImage& operator <<(const t_size&);     // the image size;

	private:
		CMargins   m_margins ; // image rectangle magins; is used for creating a gap between an image and item text;
		t_point    m_anchor  ; // this is the point of the anchor for drawing the image by image list;
		t_size     m_size    ; // image size; by default it's calculated by means of image list control, but can be set manually;
	};
}}}

#endif/*_CTL_BASE_LYT_H_INCLUDED*/