#ifndef _CTL_BASE_LYT_H_INCLUDED
#define _CTL_BASE_LYT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 24-May-2025 at 23:21:51.177, UTC+4, Batumi, Saturday;
	This is Ebo Pack user control base layout interface declaration file;
*/
#include "ctl.base.defs.h"

namespace ex_ui { namespace controls { namespace layout {

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
}}}

#endif/*_CTL_BASE_LYT_H_INCLUDED*/