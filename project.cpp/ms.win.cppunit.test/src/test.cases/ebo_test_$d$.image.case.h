#ifndef _EBO_TEST_$D$_IMAGE_CASE_H_INCLUDED
#define _EBO_TEST_$D$_IMAGE_CASE_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 25-Jul-2025 at 12:50:23.028, UTC+4, Batumi, Friday;
	This is Ebo Pack custom image load and draw helpers' interface declaration file; 
*/
#include "_log.h"
#include "ebo_test_$d$.theme.case.h"

#include "uix.image.cache.h"
#include "uix.image.prov.h"

namespace ebo { namespace boo { namespace test { namespace cases {

	using namespace ebo::boo::test;

	using e_images = CTestCase_0::e_images;
	using HBitmap  = HBITMAP;

	using TResult  = ex_ui::draw::images::CResult;
	using TImgList = ex_ui::draw::images::CList;

	// this test case class is intended for loading images and get their handles for further processing;
	class CTestCase_01 : public CNot_copyable { typedef CNot_copyable TBase;
	public:
		 CTestCase_01 (void);
		~CTestCase_01 (void) = default;

	public:
		err_code Create_list(const t_size& , TImgList& _result) const; // creates an empty image list of specified frame size;
		err_code Load_image (const e_images, TResult&  _result) const; // the result object takes care of incapsulated bitmap;
	};

}}}}

#endif/*_EBO_TEST_$D$_IMAGE_CASE_H_INCLUDED*/