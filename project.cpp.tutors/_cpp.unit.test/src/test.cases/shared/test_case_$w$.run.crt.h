#ifndef _TEST_CASE_$W$_RUN_CRT_H_INCLUDED
#define _TEST_CASE_$W$_RUN_CRT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Mar-2026 at 12:30:28.601, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' thread pool event wrapper interface declaration file for using in test cases adapters;
*/
#include "test_case_$w$.event.h"
#include "runner.crt.h"

namespace ebo { namespace boo { namespace test { namespace thread {

	using CCrtRunner = shared::runnable::CCrtRunner;
	using TRunnableFunc = shared::runnable::TRunnableFunc;
	using CDelay = shared::runnable::CDelay;

	class CTstRunner {
	public:
		 CTstRunner (void); CTstRunner (const CTstRunner&) = delete; CTstRunner (CTstRunner&&) = delete;
		~CTstRunner (void); // if c-runtime worker thread is still running it should be automatically stopped in its destructor;

		err_code Start (void);
		err_code Stop (const bool _b_forced = false, bool _cls_output = true);

		const
		CCrtRunner& operator ()(void) const;
		CCrtRunner& operator ()(void) ;

		static unsigned int __stdcall Thread_Func(void* pObject);

	private:
		CTstRunner& operator = (const CTstRunner&) = delete; CTstRunner& operator = (CTstRunner&&) = delete;
		CCrtRunner   m_runner;
		CTstListener m_listener;
	};

}}}}

#endif/*_TEST_CASE_$W$_RUN_CRT_H_INCLUDED*/