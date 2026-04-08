#ifndef _EBO_TEST_$DAT$_DEFS_H_INCLUDED
#define _EBO_TEST_$DAT$_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Apr-2026 at 16:17:17.544, UTC+4, Batumi, Tuesday;
	Ebo Pack OpenGL tutorials' data providers' common declaration file;
*/
#include "_log.h"
#include "shared.dbg.h"
#include "shared.preproc.h"
#include "sys.com.svc.h"     // com-init() is required for working with MSXML;
#include "sys.registry.h"

namespace ebo { namespace boo { namespace test { namespace data {
	using namespace ebo::boo::test;

	/**important*: the main rules of error trace:
	(1) if a test case object throws the error, it should trace it itself;
	(2) if an error occurs outside the object, it must be tracked by that object, otherwise the error trace may be duplicated;
	*/

}}}}

#pragma comment(lib, "ebo_test_$$$.lib")    // shared unit test library for common definition(s);
#pragma comment(lib, "ms.xml.6_v15.lib")    // MSXML service wrapper library;
#pragma comment(lib, "shared.dbg_v15.lib")  // it is required for usage of the debug output;
#pragma comment(lib, "shared.trim_v15.lib") // it is required for usage of the error base API;

#endif/*_EBO_TEST_$DAT$_DEFS_H_INCLUDED*/