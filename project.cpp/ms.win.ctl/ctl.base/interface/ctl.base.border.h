#ifndef _CTL_BASE_BORDER_H_INCLUDED
#define _CTL_BASE_BORDER_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-May-2012 at 9:36:22am, GMT+3, Rostov-on-Don, Friday;
	This is Pulsepay Project Shared Skinned Control Base class declaration file.
	-----------------------------------------------------------------------------
	Adopted to Ebo Pack project on 25-May-2025 at 17:25:55.155, UTC+4, Batumi, Sunday;
*/
#include "ctl.base.defs.h"
#include "ctl.base.lyt.h"
#include "uix.gdi.zbuf.h"

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
		 COne (uint16_t _n_id = 0); COne(const COne&) ; COne (COne&&);
		~COne (void);

	public:
		const bool  IsClear  (void) const;  // this border visibility actually is expressed through alpha channel of the color and border thickness;
		const bool  IsLimpid (void) const;  // this border visibility actually is expressed through alpha channel of the color and border thickness; just playing with names;
		const
		CMargin& Margin (void) const;       // this is for layout of the border container, for example, a panel control; (ro);
		CMargin& Margin (void) ;            // this is for layout of the border container, for example, a panel control; (rw);
#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif
	public:
		COne& operator = (const COne&);
		COne& operator = (COne&&);    // no move operation is used here;

		COne& operator <<(const CMargin&);

	private:
		CMargin  m_margin;
	};

	typedef ::std::map<uint16_t, COne> TRawBorders;  // a key is a margin identifier, a value is a border class object;

	class CSet {
	public:
		 CSet (void); CSet (const CSet&) ; CSet (CSet&&);
		~CSet (void) ;

	public:
		err_code  Add (const COne&); // returns 's_ok' in case of success, otherwise error code; an identifier value must be set in margin class;
		const
		COne&  Get (const uint16_t _n_id) const;  // returns a reference to fake object in case if not found; (ro);
		COne&  Get (const uint16_t _n_id);        // returns a reference to fake object in case if not found; (rw);
		err_code  Rem (const uint16_t _n_id);

#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all, _pc_sz _pfx = _T("\t\t"), _pc_sz _sfx = _T("\n")) const;
#endif
		const
		TRawBorders& Raw (void) const;
		TRawBorders& Raw (void) ;
		
	public:
		CSet& operator = (const CSet&);
		CSet& operator = (CSet&&);
		CSet& operator <<(const TRawBorders&);

		CSet& operator +=(const COne&);
		CSet& operator -=(const uint16_t _n_id);

		const
		COne& operator [](const uint16_t _n_id) const;
		COne& operator [](const uint16_t _n_id) ;

	private:
		TRawBorders m_borders;
	};

}}}

#endif/*_CTL_BASE_BORDER_H_INCLUDED*/