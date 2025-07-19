#ifndef _EBO_TEST_$D$_IMG_DEFS_H_INCLUDED
#define _EBO_TEST_$D$_IMG_DEFS_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 10-Jul-2025 at 14:34:11.369, UTC+4, Batumi, Thursday;
	This is Ebo Pack image wrappers' lib unit test declaration file; 
*/
#include "_log.h"

#include "uix.bitmap.h"
#include "uix.image.cache.h"
#include "uix.image.defs.h"
#include "uix.image.prov.h"
#include "uix.image.stream.h"

namespace ebo { namespace boo { namespace test { namespace images {

	using namespace ebo::boo::test;

}}}}

#pragma comment(lib, "ebo_test_$$$.lib")      // shared unit test library for common definition(s);
#pragma comment(lib, "image_v15.lib")         // this one must be tested by this unit test project;
#pragma comment(lib, "theme_v15.lib")         // the theme project is required for getting theme registry keys;
#pragma comment(lib, "ebo_test_$$t.case.theme.lib") // test cases for theme project of loading images from disk file;

#endif/*_EBO_TEST_$D$_IMG_DEFS_H_INCLUDED*/