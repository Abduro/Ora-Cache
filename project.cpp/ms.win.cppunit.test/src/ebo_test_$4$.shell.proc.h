#ifndef _EBO_TEST_$4$_SHELL_PROC_H_INCLUDED
#define _EBO_TEST_$4$_SHELL_PROC_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 18-Jul-2025 at 16:42:53.010, UTC+4, Batumi, Friday;
	This is Ebo pack system shell processor list wrapper library unit test declaration file; 
*/
#include "ebo_test_$4$.shell.h"

namespace ebo { namespace boo { namespace test { namespace shell {

	using TProcess = shared::sys_core::shell::CProcess;
	using TProc_List = shared::sys_core::shell::CProcess_List;

	__class (CProcess) {
	public:
		 CProcess (const bool _b_verb = false);
		~CProcess (void) = default;

	public:
		__ctor (_ctor);

	private:
		bool     m_b_verb ;
		TProcess m_process;
	};

	using TProc_map = shared::sys_core::shell::TProc_map;

	__class (CProcess_List) {
	public:
		 CProcess_List (const bool _b_verb = false);
		~CProcess_List (void) = default;

	public:
		__ctor (_ctor);
		__method (Get_It);

	private:
		bool        m_b_verb;
		TProc_List  m_proc_list;
	};

}}}}

#endif/*_EBO_TEST_$4$_SHELL_PROC_H_INCLUDED*/