#ifndef _TEST_$01_SEH_EXCEPT_H_INCLUDED
#define _TEST_$01_SEH_EXCEPT_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 8-May-2024 at 23:22:02.4231171, UTC+7, Novosibirsk, Wednesday;
	This is Ebo Pack system structured exception handling (SEH) unit test case interface declaration file;
*/
#include "ms.con.out.h"

#include "sys.err.codes.h"
#include "sys.error.h"

#include "sys.seh.code.h"
#include "sys.seh.except.h"
#include "sys.seh.flag.h"
#include "sys.seh.record.h"

namespace ebo { namespace boo { namespace test {

	using CError = shared::sys_core::CError;
	using TError = const CError;
	// https://stackoverflow.com/questions/51261071/suppress-divide-or-mod-by-zero-compiler-error-in-c ;
	// https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/set-se-translator ;
	using CTranslator = shared::sys_core::seh::CTranslator;
	using CException  = shared::sys_core::seh::CException ;

	class CThrow {
	public:
		class CCases {
		public:
			 CCases (void);
			 CCases (const CCases&) = delete;
			 CCases (CCases&&) = delete;
			~CCases (void);

		public:
			void  _0 (void) const; // division by zero;
			void  _1 (void) const; // incorrect format specification;
		
		public:
			CCases&  operator = (const CCases&) = delete;
			CCases&  operator = (CCases&&) = delete;
		};

	public:
		 CThrow (void);
		 CThrow (const CThrow&) = delete;
		 CThrow (CThrow&&) = delete;
		~CThrow (void);

	public:
		err_code Do (void);
		TError&  Error (void) const;

		const
		CCases&  Cases (void) const;
		CCases&  Cases (void) ;

	public:
		CThrow& operator = (const CThrow&) = delete;
		CThrow& operator = (CThrow&&) = delete;
	public:
		static void Case_0 (void);

	private:
		CCases m_cases;  // test cases for producing an error during executing a peace of code in one of them;
		CError m_error;
	};
}}}

typedef ebo::boo::test::CThrow::CCases TTestCases;

#endif/*_TEST_$01_SEH_EXCEPT_H_INCLUDED*/