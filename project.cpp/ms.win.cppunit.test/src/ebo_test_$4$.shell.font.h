#ifndef _EBO_TEST_$4$_SHELL_FONT_H_INCLUDED
#define _EBO_TEST_$4$_SHELL_FONT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Jul-2025 at 17:05:37.484, UTC+4, Batumi, Friday;
	This is Ebo pack system shell installed fonts' list wrapper library unit test declaration file; 
*/
#include "ebo_test_$4$.shell.h"

namespace ebo { namespace boo { namespace test { namespace shell {

	using TFonts = shared::sys_core::shell::CFonts;

	__class (CFonts) {
	public:
		 CFonts (const bool _b_verb = false);
		~CFonts (void) = default;

	public:
		__ctor (_ctor);
		__method (Has);
		__method (GetInstalled);

	private:
		bool    m_b_verb;
		TFonts  m_fonts ;
	};

}}}}

#endif/*_EBO_TEST_$4$_SHELL_FONT_H_INCLUDED*/