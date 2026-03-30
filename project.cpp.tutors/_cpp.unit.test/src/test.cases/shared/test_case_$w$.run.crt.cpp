/*
	Created by Tech_dog (ebontrop@gmail.com) on 30-Mar-2026 at 12:34:01.536, UTC+4, Batumi, Monday;
	This is Ebo Pack OpenGL tutorials' thread pool event wrapper interface implementation file for using in test cases adapters;
*/
#include "test_case_$w$.run.crt.h"
#include "shared.preproc.h"

using namespace ebo::boo::test::thread;

#pragma region cls::CTstRunner{}

CTstRunner::CTstRunner (void) : m_runner(CTstRunner::Thread_Func, m_listener, _variant_t(1L)) {}

unsigned int __stdcall CTstRunner::Thread_Func (void* pObject) {
	pObject;
	unsigned int u_result = 1; // sets to 'error' result;

	if (nullptr == pObject) {
		return u_result;
	}

	CCrtRunner* p_runner = 0;
	// try...catch block looks like not necessary because the input parameter data type is guaranteed by this class implementation;
	try {
		p_runner = reinterpret_cast<CCrtRunner*>(pObject);
		if (nullptr == p_runner) {
			return u_result;
		}
	}
	catch(::std::bad_cast&) { return u_result; }

	return (u_result = 0);
}

#pragma endregion