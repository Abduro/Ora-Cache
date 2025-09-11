#ifndef _OUT_SECTION_H_B7061AC8_1CA6_4853_85FB_1FB70FC8860F_INCLUDED
#define _OUT_SECTION_H_B7061AC8_1CA6_4853_85FB_1FB70FC8860F_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 12-Dec-2022 at 08:37:39.2526269, UTC+7, Novosibirsk, Monday;
	This is system console output section interface declaration file;
	-----------------------------------------------------------------------------
	This code is the excerpt from console project of Ebo_Pack package static library code;
*/
#include "console.defs.h"

namespace shared { namespace console {
	// base class and base class error attribute is excluded from this version of section code, because error object is not necessary for the time being;
#if (0)
	class CSection : public CWriter_Base
	{               typedef CWriter_Base TBase;
#else
	class CSection {
#endif
	public:
		 CSection (void);
		 CSection (const CSection&);
		 CSection (_pc_sz _lp_sz_caption);
		~CSection (void);

	public:
		bool     Is  (void) const;             // checks a validity of caption string;
		err_code Out (void) const;             // prints out the text;
		err_code Out (_pc_sz _lp_sz_caption); // prints out the given text; TODO: twice checking given caption occurs;
		_pc_sz   Text(void) const;
		err_code Text(_pc_sz);

	public:
		 CSection& operator = (const CSection&); // does not print section caption, but only copies base's error object and text content;
		 CSection& operator <<(_pc_sz _lp_sz_caption);

	public:
		static bool Is (_pc_sz);                // checks a validity of provided text;

	private:
		CString  m_text;
	};

}}

typedef shared::console::CSection TSection;

#endif/*_OUT_SECTION_H_B7061AC8_1CA6_4853_85FB_1FB70FC8860F_INCLUDED*/