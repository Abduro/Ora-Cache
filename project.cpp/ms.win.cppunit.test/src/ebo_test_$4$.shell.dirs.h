#ifndef _EBO_TEST_$4$_SHELL_DIRS_H_INCLUDED
#define _EBO_TEST_$4$_SHELL_DIRS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Jul-2025 at 17:16:48.791, UTC+4, Batumi, Friday;
	This is Ebo pack system shell generic folder wrapper library unit test declaration file; 
*/
#include "ebo_test_$4$.shell.h"

namespace ebo { namespace boo { namespace test { namespace shell {

	using TFolder = shared::user_32::ntfs::CFolder;

	__class (CFolder) {
	public:
		 CFolder (const bool _b_verb = false);
		~CFolder (void) = default;

	public:
		__ctor (_ctor);
		__method (EnumItems);

	private:
		bool     m_b_verb;
		TFolder  m_folder;
	};
}}}}

#endif/*_EBO_TEST_$4$_SHELL_DIRS_H_INCLUDED*/