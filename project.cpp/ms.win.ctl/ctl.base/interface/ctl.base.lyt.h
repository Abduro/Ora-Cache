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
	
	class CMargin {
	public:
		 CMargin (const uint16_t _n_id = 0, const int16_t _n_value = 0); CMargin (const CMargin&); CMargin (CMargin&&) = delete;
		~CMargin (void) = default;

	public:
		uint16_t  Id (void) const;
		bool      Id (const uint16_t);   // returns 'true' in case of change;
#if defined(_DEBUG)
		CString   Print (const e_print = e_print::e_all) const;
#endif
		int16_t   Value (void) const;
		bool      Value (const int16_t); // returns 'true' in case of change;

	public:
		CMargin&  operator = (const CMargin&);
		CMargin&  operator = (CMargin&&) = delete;

		CMargin&  operator <<(const uint16_t _n_id);
		CMargin&  operator >>(const  int16_t _n_value);

	private:
		uint16_t  m_id;
		 int16_t  m_value;
	};

	typedef ::std::map<uint16_t, CMargin> TRawMargins;

	class CMargins {
	public:
		 CMargins (void); CMargins (const CMargins&) = delete; CMargins (CMargins&&) = delete;
		~CMargins (void);

	public:
		bool  Is_zero (void) const; // returns true in case when all margins have value 0 (zero) ;
		const
		TRawMargins& Raw (void) const;
		TRawMargins& Raw (void) ;

	public:
		CMargins&  operator = (const CMargins&) = delete;
		CMargins&  operator = (CMargins&&) = delete;

	protected:
		TRawMargins m_raw;
	};

	class CMargins_of_rect : public CMargins { typedef CMargins TBase;
	public:
		enum e_sides : int16_t {
			e_left = 0, e_top, e_right, e_bottom
		};
	public:
		 CMargins_of_rect (void); CMargins_of_rect (const CMargins_of_rect&) = delete; CMargins_of_rect (CMargins_of_rect&&) = delete;
		~CMargins_of_rect (void);
	public:
		bool  ApplyTo(t_rect& _rect) const; // returns true in case of change at least one side of the input rectangle;
		const
		CMargin& Get (const e_sides) const; // returns the reference to margin of input side; if not fount, the reference to fake object is returned;
		CMargin& Get (const e_sides) ;      // returns the reference to margin of input side; if not fount, the reference to fake object is returned;
#if defined(_DEBUG)
		CString  Print (const e_print = e_print::e_all) const;
#endif
	};

}}}

#endif/*_CTL_BASE_LYT_H_INCLUDED*/