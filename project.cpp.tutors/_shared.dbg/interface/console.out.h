#ifndef _CONSOLE_OUT_H_INCLUDED
#define _CONSOLE_OUT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 13-Sep-2025 at 02:19:04.497,UTC+4, Batumi, Saturday;
	This is Ebo Pack console output text blocks interface declaration files;
*/
#include "console.defs.h"

namespace shared { namespace console {

	// https://learn.microsoft.com/en-us/windows/console/console-screen-buffers ;

	class COut {
	COut (void) = delete; COut (const COut&) = delete; COut (COut&&) = delete; ~COut (void) = delete;
	COut& operator = (const COut&) = delete; COut& operator = (COut&&) = delete;
	public:
		static void Error (_pc_sz);
		static void Impt  (_pc_sz); // https://www.allacronyms.com/important/abbreviated ;
		static void Info  (_pc_sz);
		static void Warn  (_pc_sz);
	};

}}

#endif/*_CONSOLE_OUT_H_INCLUDED*/