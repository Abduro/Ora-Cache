#ifndef _EBO_TEST_$D$_IMG_STREAM_H_INCLUDED
#define _EBO_TEST_$D$_IMG_STREAM_H_INCLUDED
/*
	Created by Tech_dog (ebontrop@gmail.com) on 15-Jul-2025 at 21:55:38.702, UTC+4, Batumi, Tuesday;
	This is Ebo Pack image stream wrapper unit test interface declaration file; 
*/
#include "ebo_test_$d$.img.defs.h"

namespace ebo { namespace boo { namespace test { namespace images {

	using TStream = ex_ui::draw::images::CStream;

	__class (CStream) {
	public:
		 CStream (const bool _b_verb = false);
		~CStream (void) = default;

	public:
		__ctor (_ctor);
		__method (Load_image);

	private:
		bool    m_b_verb;
		TStream m_stream;
	};

	// the class below is inteanded to load status bar control images;
	class CTestCase_0 {
	public:
		enum e_images : uint32_t {
		     e_no_0 = 0,
		     e_no_1 = 1,
		};
	public:
		 CTestCase_0 (void);
		~CTestCase_0 (void) = default;

	TError&   Error  (void) const;

	CString   Get_path (const e_images) const; // returns the path to the image file; in case of error the empty string is returned;
	err_code  Set_path (void) ;                // composes the path specific for images of the status bar control;

	private:
		mutable
		CError m_error;
		CString m_folder; // this is the path to images' folder;
	};

}}}}

#endif/*_EBO_TEST_$D$_IMG_STREAM_H_INCLUDED*/