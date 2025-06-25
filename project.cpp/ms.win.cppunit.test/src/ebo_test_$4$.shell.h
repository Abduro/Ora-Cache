#ifndef _EBO_TEST_$4$_SHELL_H_INCLUDED
#define _EBO_TEST_$4$_SHELL_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 14-Jun-2025 at 09:24:15.525, UTC+4, Batumi, Saturday;
	This is Ebo pack system shell base wrapper library unit test declaration file; 
*/
#include "_log.h"

#include "sys.procs.list.h"
#include "sys.shell.dwm.h"
#include "sys.shell.font.h"

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

#pragma comment(lib, "sys.err.core_v15.lib") // system error handling wrapper lib;
#pragma comment(lib, "sys.com.core_v15.lib") // comp-obj-model library;
#pragma comment(lib, "sys.shell_v15.lib")    // this one must be tested by this unit test project;

#pragma comment(lib, "ebo_test_$$$.lib")     // shared unit test library for common definition(s);

#endif/*_EBO_TEST_$4$_SHELL_H_INCLUDED*/