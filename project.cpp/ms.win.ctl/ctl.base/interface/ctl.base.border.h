#ifndef _CTL_BASE_BORDER_H_INCLUDED
#define _CTL_BASE_BORDER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-May-2012 at 9:36:22am, GMT+3, Rostov-on-Don, Friday;
	This is Pulsepay Project Shared Skinned Control Base class declaration file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack project on 25-May-2025 at 17:25:55.155, UTC+4, Batumi, Sunday;
*/
#include "ctl.base.defs.h"
#include "ctl.base.layout.h"

/*
	there is a lot of games in this reality; frankly speaking, a human life is a particular game too;
	regarding the playing with names within programming and trying to make some sort of program architecture which has readable names;
	what are options for that exist:
		(1) COne; CSet; CBordersOfRect; CBordersOfTriangle; and so on...
		(2) namespace ex_ui::controls::borders >> COne; CSet; CSetForRect; CSetForTria... perhaps it is a little bit more readable;
*/
namespace ex_ui { namespace controls { namespace borders {

	using namespace ex_ui::controls;

	using CLine = geometry::_2D::base::CLine;
	using CMargin = ex_ui::controls::layout::CMargin;
	// ToDo: a border identification through margine identifier is not good approach and must be reviewed;
	class COne : public CLine { typedef CLine TBase;
	public:
		 COne (uint32_t _n_id = 0); COne(const COne&) ; COne (COne&&);
		~COne (void);

	public:
		uint32_t    Id (void) const;
		bool        Id (const uint32_t _n_id);

		const bool  IsClear  (void) const;  // this border visibility actually is expressed through alpha channel of the color and border thickness;
		const bool  IsLimpid (void) const;  // this border visibility actually is expressed through alpha channel of the color and border thickness; just playing with names;
#if (0) // margins may be assigned to a container that requires a some space around it, but not to a container element, for example, to a border;
		const
		CMargin& Margin (void) const;       // this is for layout of the border container, for example, a panel control; (ro);
		CMargin& Margin (void) ;            // this is for layout of the border container, for example, a panel control; (rw);
#endif
#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif
	public:
		COne& operator = (const COne&);
		COne& operator = (COne&&);    // no move operation is used here;
#if (0)
		COne& operator <<(const CMargin&);
#else
		COne& operator <<(const uint32_t _n_id);
#endif
	private:
		uint32_t m_Id;
#if (0)
		CMargin  m_margin;
#endif
	};

	typedef COne CBorder;
	typedef ::std::map<uint32_t, CBorder> TRawBorders; // a key is a border identifier, a value is a border class itself;

	class CSet {
	public:
		 CSet (void); CSet (const CSet&) ; CSet (CSet&&);
		~CSet (void) ;

	public:
		err_code   Add (const COne&);      // returns 's_ok' in case of success, otherwise error code; an identifier value must be set in margin class;
		bool     Color (const TRgbQuad&);  // returns 'true' in case if at least one border's color is changed; input color quad is set to all borders;
		uint32_t Count (void) const;       // https://en.cppreference.com/w/cpp/container/map/size ;
		const
		CBorder&   Get (const uint32_t _n_id) const;   // returns a reference to fake object in case if not found; (ro);
		CBorder&   Get (const uint32_t _n_id);         // returns a reference to fake object in case if not found; (rw);
		err_code   Rem (const uint32_t _n_id);

#if defined(_DEBUG)
		CString    Print (const e_print = e_print::e_all, _pc_sz _pfx = _T("\t\t"), _pc_sz _sfx = _T("\n")) const;
#endif
		const
		TRawBorders& Raw (void) const;
		TRawBorders& Raw (void) ;

		bool   Thickness (const uint8_t); // sets the same thickness to all borders; returns 'true' in case of thickness value at least of one border is changed;
		
	public:
		CSet& operator = (const CSet&);
		CSet& operator = (CSet&&);
		CSet& operator <<(const TRawBorders&);
		CSet& operator <<(const TRgbQuad&);
		CSet& operator <<(const uint8_t _n_thickness);

		CSet& operator +=(const CBorder&);
		CSet& operator -=(const uint32_t _n_id);

		const
		COne& operator [](const uint32_t _n_id) const;
		COne& operator [](const uint32_t _n_id) ;

	protected:
		TRawBorders m_borders;
	};
	/*
		// https://learn.microsoft.com/en-us/windows/win32/gdi/drawing-rectangles ;
		// https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-framerect ;

		of course, rectangle borders can be created by using rectangle structure itself and applying the ::FrameRect() WinAPI function;
		at the same time, the management of the border colors is not easy when using above approach, for example, how to make borders of
		different colors: playing with output rectangle may produce overlaps in drawing several shapes or controls in complex layout;
	*/
	class CSet_for_rect : public CSet { typedef CSet TBase;
	public: using e_sides = layout::CGaps_of_rect::e_sides;
	public:
		 CSet_for_rect (void); /*CSet_for_rect (const CSet_for_rect&); CSet_for_rect (CSet_for_rect&&);*/
		~CSet_for_rect (void);

	public:
		const
		CSet&    Base (void) const { return (const TBase&)*this; }
		CSet&    Base (void)       { return (TBase&)*this; }
		const
		CBorder& Get (const e_sides) const;
		CBorder& Get (const e_sides) ;

		const CBorder& Bottom (void) const; const CBorder&  Left (void) const; const CBorder& Right (void) const; const CBorder& Top (void) const;
		      CBorder& Bottom (void)      ;       CBorder&  Left (void) ;            CBorder& Right (void)      ;       CBorder& Top (void) ;

		bool  Set (const t_rect&); // sets borders' points of all sides; empty rectangle is applicable; returns true in case if at least on side coords is changed;

	public:
		CSet_for_rect& operator <<(const t_rect&); // calls this::Set(const t_rect&);
		CSet_for_rect& operator <<(const uint8_t _n_thickness);
	};
	typedef CSet_for_rect CBorders_for_rect;
}}}

#endif/*_CTL_BASE_BORDER_H_INCLUDED*/