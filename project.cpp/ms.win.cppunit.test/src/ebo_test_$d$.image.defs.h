#ifndef _EBO_TEST_$D$_IMAGE_DEFS_H_INCLUDED
#define _EBO_TEST_$D$_IMAGE_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-Jul-2025 at 14:34:11.369, UTC+4, Batumi, Thursday;
	This is Ebo Pack image wrappers' lib unit test declaration file; 
*/
#include "_log.h"

#include "uix.image.defs.h"
#include "uix.picture.h"

namespace ebo { namespace boo { namespace test { namespace images {

	using CError  = shared::sys_core::CError;
	using TError  = const CError;
	using TString = TStringEx   ;
}}}}

#pragma comment(lib, "sys.err.core_v15.lib")  // for using error object;
#pragma comment(lib, "ebo_test_$$$.lib")      // shared unit test library for common definition(s);
#pragma comment(lib, "image_v15.lib")         // this one must be tested by this unit test project;
#pragma comment(lib, "theme_v15.lib")         // the theme project is required for getting theme registry keys;

#endif/*_EBO_TEST_$D$_IMAGE_DEFS_H_INCLUDED*/