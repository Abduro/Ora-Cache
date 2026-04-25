#ifndef _TEST_CASE_$W$_TPL_H_INCLUDED
#define _TEST_CASE_$W$_TPL_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 03-Apr-2026 at 10:23:26.387, UTC+4, Batumi, Friday;
	This is Ebo Pack thread pool wrapper interface declaration file for using in test cases adapters;
*/
#include "test_case_$w$.event.h"
#include "runner.tpl.h"

namespace test { namespace win_api { namespace threads {

	using CTplRunner = shared::runnable::threads::pool::CTplRunner;

	// this class overrides the thread function of CTplRunner for test case purposes;
	class CTstTplExt : public CTplRunner { typedef CTplRunner TBase;
	public:
		 CTstTplExt (void); CTstTplExt (const CTstTplExt&) = delete; CTstTplExt (CTstTplExt&&) = delete;
		~CTstTplExt (void);

		operator const CTplRunner& (void) const;
		operator       CTplRunner& (void) ;

	private:
		CTstTplExt& operator = (const CTstTplExt&) = delete; CTstTplExt& operator = (CTstTplExt&&) = delete;
		void Run_Func (void) override final;
	};

	class CTstTplRunner {
	public:
		 CTstTplRunner (void); CTstTplRunner (const CTstTplRunner&) = delete; CTstTplRunner (CTstTplRunner&&) = delete;
		~CTstTplRunner (void);

		err_code Start (bool _cls_output = true);
		err_code Stop (bool _cls_output = true);

		const
		CTplRunner& operator ()(void) const;
		CTplRunner& operator ()(void) ;

		static unsigned int __stdcall Thread_Func(void* pObject);

	private:
		CTstTplRunner& operator = (const CTstTplRunner&) = delete; CTstTplRunner& operator = (CTstTplRunner&&) = delete;
		CTstTplExt   m_run_ext;
	};

}}}

#endif/*_TEST_CASE_$W$_TPL_H_INCLUDED*/