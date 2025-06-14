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
		class CSides {
		public:
			enum _part : int16_t {
				e_left   = 0x0,
				e_top    = 0x1, // by default;
				e_right  = 0x2,
				e_bottom = 0x3,
			};
			static const int16_t n_count = 4;
		public:
			 CSides (void);
			 CSides (const _part _selected); CSides (CSides&&) = delete;
			 CSides (const CSides&);
			~CSides (void);

		public:
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
		~CGaps_of_rect (void);

	public:
		/* this::ApplyTo(): possibly the second parameter is required for indicating how to apply gaps for calculating margins or padding,
		   but it can be made by specifying appropriate sign for particular gap value, because gaps' values are always added to sides of input rectangle;
			for example >>
				for applying margins: gaps={left:-10;top:-10;right:+10;bottom:+10};
				for applying padding: gaps={left:+10;top:+10;right:-10;bottom:-10};
		*/
		bool  ApplyTo(t_rect& _rect) const; // returns true in case of change at least one side of the input rectangle;
		const
		CGap& Get (const e_sides) const;    // returns the reference to margin of input side; if not fount, the reference to fake object is returned;
		CGap& Get (const e_sides) ;         // returns the reference to margin of input side; if not fount, the reference to fake object is returned;
#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif
		bool  Set (const int16_t _left, const int16_t _top, const int16_t _right, const int16_t _bottom); // returns 'true' if at least one of the gaps is changed;

	public:
		CGaps_of_rect&  operator = (const CGaps_of_rect&);
		CGaps_of_rect&  operator = (CGaps_of_rect&&) = delete;
	};

	typedef CGaps_of_rect CMargins_of_rect;
	typedef CGaps_of_rect CPadding_of_rect;
}}}

#endif/*_CTL_BASE_LYT_H_INCLUDED*/