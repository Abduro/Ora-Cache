#ifndef _SHARED_PREPROC_H_INCLUDED
#define _SHARED_PREPROC_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-Apr-2024 09:20:02.3153499, UTC+7, Novosibirsk, Wednesday;
	This is Ebo Pack shared preprocessor parser interface declaration file;
	-----------------------------------------------------------------------------
	Adopted to tutorials' solution(s) on 19-Aug-2025 at 15:21:05.870, UTC+4, Batumi, Tuesday;
*/
#include <atlbase.h>
#include <atlstr.h>
#include <vector>

#include "shared.defs.h"

#if defined(_UNICODE)
#define __SPEC__  __FUNCTIONW__
#else
#define __SPEC__  __FUNCTION__
#endif


namespace shared { namespace common {

	using namespace shared::defs;

	class CPreprocessor {
	public:
		  CPreprocessor (void) = default;
		 ~CPreprocessor (void) = default;

	public:
		static CString Class  (_pc_sz const _p_spec); // gets class name from input spec;
		static CString Method (_pc_sz const _p_spec); // gets method name;
		static CString NameSp (_pc_sz const _p_spec); // gets namespace;
	};
}}

#define __CLASS__ shared::common::CPreprocessor::Class(__SPEC__)
#define __METHOD__ shared::common::CPreprocessor::Method(__SPEC__)
#define __SP_NAME__  shared::common::CPreprocessor::NameSp(__SPEC__)

typedef const shared::common::CPreprocessor TPreproc;

#endif/*_SHARED_PREPROC_H_INCLUDED*/