#ifndef _EBO_TEST_$S$_LOG_DEFS_H_INCLUDED
#define _EBO_TEST_$S$_LOG_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 27-Jun-2025 at 12:40:36.810, UTC+4, Batumi, Friday;
	This is Ebo Pack generic events' logger lib unit test interface declaration file; 
*/
#include "_log.h"

#include "shared.log.defs.h"

namespace ebo { namespace boo { namespace test { namespace log {

	using CError  = shared::sys_core::CError;
	using TError  = const CError;
	using TString = TStringEx   ;
#if (0)
	__class (CErr_Desc) {
	public:
		 CErr_Desc (const bool _b_verb = false);
		~CErr_Desc (void) = default;

	public:
		__ctor (_ctor);
		__method (Set); // this is direct setting values to the error details object; no raw parse error interface is applied;

	private:
		bool    m_b_verb;
		TErr_Desc m_err_desc;
	};
#endif

}}}}

#pragma comment(lib, "sys.err.core_v15.lib")  // for using error object;
#pragma comment(lib, "ebo_test_$$$.lib")      // shared unit test library for common definition(s);
#pragma comment(lib, "logger_v15.lib")        // this one must be tested by this unit test project;

#endif/*_EBO_TEST_$S$_LOG_DEFS_H_INCLUDED*/