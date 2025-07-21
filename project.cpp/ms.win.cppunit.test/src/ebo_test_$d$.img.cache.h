#ifndef _EBO_TEST_$D$_IMG_CACHE_H_INCLUDED
#define _EBO_TEST_$D$_IMG_CACHE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 07-Jul-2025 at 10:48:07.749, UTC+4, Batumi, Saturday;
	This is Ebo Pack WinAPI GDI image cache unit test interface declaration file;
*/
#include "ebo_test_$d$.img.defs.h"

namespace ebo { namespace boo { namespace test { namespace cache {

	using namespace ebo::boo::test::images;

	using TCache   = ex_ui::draw::images::CCache;
	using TImgType = ex_ui::draw::images::TImgType;
	using TImgFmt  = ex_ui::draw::images::TImgFmt;

	__class (CCache) {
	public:
		 CCache (const bool _b_verb = false);
		~CCache (void) = default;

	public:
		__ctor (_ctor);
		__method (Append); // appends all images from specified directory; the directory is read from registry for theme test cases;
		__method (Has);    // checks an existance of the image list of particular image size; if not found, new list is created in the cache;
		__method (List);   // tries to get the reference to the image list; if not found the reference to fake list returned; it is checked by the error state;

	private:
		bool   m_b_verb;
		TCache m_cache ;
	};

	using TList = ex_ui::draw::images::CList;

	__class (CList) {
	public:
		 CList (const bool _b_verb = false);
		~CList (void) = default;

	public:
		__ctor (_ctor);
		__method (Create);

	private:
		bool   m_b_verb;
		TList  m_list;
	};

}}}}

#endif/*_EBO_TEST_$D$_IMG_CACHE_H_INCLUDED*/